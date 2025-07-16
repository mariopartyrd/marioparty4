#include "game/sprite.h"
#include "game/memory.h"
#include "game/init.h"

#include "dolphin/mtx.h"

#include "port/byteswap.h"
#ifndef __MWERKS__
#include "game/hsfdraw.h"
#endif

#define SPRITE_DIRTY_ATTR 0x1
#define SPRITE_DIRTY_XFORM 0x2
#define SPRITE_DIRTY_COLOR 0x4

typedef struct sprite_order {
    u16 group;
    u16 sprite;
    u16 prio;
    u16 next;
} SpriteOrder;

SHARED_SYM HuSprite HuSprData[HUSPR_MAX];
SHARED_SYM HuSprGrp HuSprGrpData[HUSPR_GRP_MAX];
static SpriteOrder HuSprOrder[HUSPR_MAX*2];

static s16 HuSprOrderNum;
static s16 HuSprOrderNo;
static BOOL HuSprPauseF;

static void HuSprOrderEntry(s16 group, s16 sprite);


void HuSprInit(void)
{
    s16 i;
    HuSprite *sprite;
    HuSprGrp *group;
    for(sprite = &HuSprData[1], i=1; i<HUSPR_MAX; i++, sprite++) {
        sprite->data = NULL;
    }
    for(group = HuSprGrpData, i=0; i<HUSPR_GRP_MAX; i++, group++) {
        group->capacity = 0;
    }
    sprite = &HuSprData[0];
    sprite->prio = 0;
    sprite->data = (void *)1;
    HuSprPauseF = FALSE;
}

void HuSprClose(void)
{
    s16 i;
    HuSprGrp *group;
    HuSprite *sprite;
    
    for(group = HuSprGrpData, i=0; i<HUSPR_GRP_MAX; i++, group++) {
        if(group->capacity != 0) {
            HuSprGrpKill(i);
        }
    }
    for(sprite = &HuSprData[1], i=1; i<HUSPR_MAX; i++, sprite++) {
        if(sprite->data) {
            HuSprKill(i);
        }
    }
    HuSprPauseF = FALSE;
}

void HuSprExec(s16 draw_no)
{
    HuSprite *sprite;
    while(sprite = HuSprCall()) {
        if(!(sprite->attr & HUSPR_ATTR_DISPOFF) && sprite->draw_no == draw_no) {
            HuSprDisp(sprite);
        }
    }
}

void HuSprBegin(void)
{
    Mtx temp, rot;
    s16 i, j;
    Vec axis = {0, 0, 1};
    HuSprGrp *group;
    group = HuSprGrpData;
    HuSprOrderNum = 1;
    HuSprOrder[0].next = 0;
    HuSprOrder[0].prio = -1;
    for(i=0; i<HUSPR_GRP_MAX; i++, group++) {
        if(group->capacity != 0) {
            MTXTrans(temp, group->center_x*group->scale_x, group->center_y*group->scale_y, 0.0f);
            MTXRotAxisDeg(rot, &axis, group->z_rot);
            MTXConcat(rot, temp, group->mtx);
            MTXScale(temp, group->scale_x, group->scale_y, 1.0f);
            MTXConcat(group->mtx, temp, group->mtx);
            mtxTransCat(group->mtx, group->x, group->y, 0);
            for(j=0; j<group->capacity; j++) {
                if(group->members[j] != -1) {
                    HuSprOrderEntry(i, group->members[j]);
                }
            }
        }
    }
    HuSprOrderNo = 0;
}

static void HuSprOrderEntry(s16 group, s16 sprite)
{
    SpriteOrder *order = &HuSprOrder[HuSprOrderNum];
    s16 prio = HuSprData[sprite].prio;
    s16 prev, next;
    if(HuSprOrderNum >= HUSPR_MAX*2) {
        OSReport("Order Max Over!\n");
        return;
    }
    next = HuSprOrder[0].next;
    for(prev = 0; next != 0; prev = next, next = HuSprOrder[next].next) {
        if(HuSprOrder[next].prio < prio) {
            break;
        }
    }
    order->next = HuSprOrder[prev].next;
    HuSprOrder[prev].next = HuSprOrderNum;
    order->prio = prio;
    order->group = group;
    order->sprite = sprite;
    HuSprOrderNum++;
}

HuSprite *HuSprCall(void)
{
    HuSprOrderNo = HuSprOrder[HuSprOrderNo].next;
    if(HuSprOrderNo != 0) {
        SpriteOrder *order = &HuSprOrder[HuSprOrderNo];
        HuSprite *sprite = &HuSprData[order->sprite];
        sprite->group_mtx = &HuSprGrpData[order->group].mtx;
        if(sprite->attr & HUSPR_ATTR_FUNC) {
            return sprite;
        }
        sprite->frame_data = &sprite->data->bank[sprite->bank].frame[sprite->frame];
        sprite->pat_data = &sprite->data->pat[sprite->frame_data->pat];
        return sprite;
    } else {
        return NULL;
    }
}

static inline void SpriteCalcFrame(HuSprite *sprite, AnimBankData *bank, AnimFrameData **frame, s16 loop)
{
    if(sprite->time >= (*frame)->time) {
        sprite->frame++;
        sprite->time -= (*frame)->time;
        if(sprite->frame >= bank->timeNum || (*frame)[1].time == -1) {
            if(loop) {
                sprite->frame = 0;
            } else {
                sprite->frame = bank->timeNum-1;
            }
        }
        *frame = &bank->frame[sprite->frame];
    } else if(sprite->time < 0) {
        sprite->frame--;
        if(sprite->frame < 0) {
            if(loop) {
                sprite->frame = bank->timeNum-1;
            } else {
                sprite->frame = 0;
            }
        }
        *frame = &bank->frame[sprite->frame];
        sprite->time += (*frame)->time;
    }
}

void HuSprFinish(void)
{
    AnimData *anim;
    AnimBankData *bank;
    AnimFrameData *frame;
    HuSprite *sprite;
    s16 i;
    s16 j;
    s16 loop;
    s16 dir;
    
    for(sprite = &HuSprData[1], i=1; i<HUSPR_MAX; i++, sprite++) {
        if(sprite->data && !(sprite->attr & HUSPR_ATTR_FUNC)) {
            if(!HuSprPauseF || (sprite->attr & HUSPR_ATTR_NOPAUSE)) {
                anim = sprite->data;
                bank = &anim->bank[sprite->bank];
                frame = &bank->frame[sprite->frame];
                loop = (sprite->attr & HUSPR_ATTR_LOOP) ? 0 : 1;
                if(!(sprite->attr & HUSPR_ATTR_NOANIM)) {
                    dir = (sprite->attr & HUSPR_ATTR_REVERSE) ? -1 : 1;
                    for(j=0; j<(s32)sprite->speed*minimumVcount; j++) {
                        sprite->time += dir;
                        SpriteCalcFrame(sprite, bank, &frame, loop);
                    }
                    sprite->time += (sprite->speed*(float)minimumVcount)-j;
                    SpriteCalcFrame(sprite, bank, &frame, loop);
                }
                sprite->dirty_flag = 0;
            }
        }
    }
}

void HuSprPauseSet(BOOL value)
{
    HuSprPauseF = value;
}

AnimData *HuSprAnimRead(void *data)
{
    s16 i;
    AnimBmpData *bmp;
    AnimBankData *bank;
    AnimPatData *pat;

    AnimData *anim = data;
#ifdef TARGET_PC
    s16 j;
    if (anim->valid == ANIM_DATA_ALLOCATION_VALID) {
        anim->useNum++;
        return anim;
    }
    anim = HuMemDirectMalloc(HEAP_DATA, sizeof(AnimData));
    byteswap_animdata(data, anim);
    anim->valid = ANIM_DATA_ALLOCATION_VALID;
#else
    if((uintptr_t)anim->bank & ~0xFFFF) {
        anim->useNum++;
        return anim;
    }
#endif
    bank = (void *)((uintptr_t)anim->bank+(uintptr_t)data);
#ifdef TARGET_PC
    bank = HuMemDirectMalloc(HEAP_DATA, anim->bankNum * sizeof(AnimBankData));
    for(i=0; i<anim->bankNum; i++) {
        byteswap_animbankdata(&((AnimBankData32b*)((uintptr_t)anim->bank+(uintptr_t)data))[i], &bank[i]);
    }
#endif
    anim->bank = bank;
    pat = (void *)((uintptr_t)anim->pat+(uintptr_t)data);
#ifdef TARGET_PC
    pat = HuMemDirectMalloc(HEAP_DATA, anim->patNum * sizeof(AnimPatData));
    for(i=0; i<anim->patNum; i++) {
        byteswap_animpatdata(&((AnimPatData32b*)((uintptr_t)anim->pat+(uintptr_t)data))[i], &pat[i]);
    }
#endif
    anim->pat = pat;
    bmp = (void *)((uintptr_t)anim->bmp+(uintptr_t)data);
#ifdef TARGET_PC
    bmp = HuMemDirectMalloc(HEAP_DATA, anim->bmpNum * sizeof(AnimBmpData));
    for(i=0; i<anim->bmpNum; i++) {
        byteswap_animbmpdata(&((AnimBmpData32b*)((uintptr_t)anim->bmp+(uintptr_t)data))[i], &bmp[i]);
    }
#endif
    anim->bmp = bmp;
    for(i=0; i<anim->bankNum; i++, bank++) {
        bank->frame = (AnimFrameData *)((uintptr_t)bank->frame+(uintptr_t)data);
#ifdef TARGET_PC
        byteswap_animframedata(bank->frame);
#endif
    }
    for(i=0; i<anim->patNum; i++, pat++) {
        pat->layer = (AnimLayerData *)((uintptr_t)pat->layer+(uintptr_t)data);
#ifdef TARGET_PC
        for (j = 0; j < pat->layerNum; j++) {
            byteswap_animlayerdata(&pat->layer[j]);
        }
#endif
    }
    for(i=0; i<anim->bmpNum; i++, bmp++) {
        bmp->palData = (void *)((uintptr_t)bmp->palData+(uintptr_t)data);
        bmp->data = (void *)((uintptr_t)bmp->data+(uintptr_t)data);
    }
    anim->useNum = 0;
    return anim;
}

void HuSprAnimLock(AnimData *anim)
{
    anim->useNum++;
}

s16 HuSprCreate(AnimData *anim, s16 prio, s16 bank)
{
    HuSprite *sprite;
    s16 i;
    for(sprite = &HuSprData[1], i=1; i<HUSPR_MAX; i++, sprite++) {
        if(!sprite->data) {
            break;
        }
    }
    if(i == HUSPR_MAX) {
        return HUSPR_NONE;
    }
    sprite->data = anim;
    sprite->speed = 1.0f;
    sprite->frame = 0;
    sprite->bank = bank;
    sprite->time = 0.0f;
    sprite->attr = 0;
    sprite->draw_no = 0;
    sprite->r = sprite->g = sprite->b = sprite->a = 255;
    sprite->x = sprite->y = sprite->z_rot = 0.0f;
    sprite->prio = prio;
    sprite->scale_x = sprite->scale_y = 1.0f;
    sprite->wrap_s = sprite->wrap_t = GX_CLAMP;
    sprite->tex_scale_x = sprite->tex_scale_y = 1;
    sprite->bg = NULL;
    sprite->scissor_x = sprite->scissor_y = 0;
    sprite->scissor_w = 640;
    sprite->scissor_h = 480;
    if(anim) {
        HuSprAnimLock(anim);
    }
    return i;
}

s16 HuSprFuncCreate(HuSprFunc func, s16 prio)
{
    HuSprite *sprite;
    s16 index = HuSprCreate(NULL, prio, 0);
    if(index == HUSPR_NONE) {
        return HUSPR_NONE;
    }
    sprite = &HuSprData[index];
    sprite->func = func;
    sprite->attr |= HUSPR_ATTR_FUNC;
    return index;
}

s16 HuSprGrpCreate(s16 capacity)
{
    HuSprGrp *group;
    s16 i, j;
    for(group = HuSprGrpData, i=0; i<HUSPR_GRP_MAX; i++, group++) {
        if(group->capacity == 0) {
            break;
        }
    }
    if(i == HUSPR_GRP_MAX) {
        return HUSPR_GRP_NONE;
    }
    group->members = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s16)*capacity);
    for(j=0; j<capacity; j++) {
        group->members[j] = HUSPR_NONE;
    }
    group->capacity = capacity;
    group->x = group->y = group->z_rot = group->center_x = group->center_y = 0.0f;
    group->scale_x = group->scale_y = 1.0f;
    return i;
}

s16 HuSprGrpCopy(s16 group)
{
    HuSprGrp *new_group_ptr;
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    s16 new_group = HuSprGrpCreate(group_ptr->capacity);
    s16 i;
    if(new_group == HUSPR_GRP_NONE) {
        return HUSPR_GRP_NONE;
    }
    new_group_ptr = &HuSprGrpData[new_group];
    new_group_ptr->x = group_ptr->x;
    new_group_ptr->y = group_ptr->y;
    new_group_ptr->z_rot = group_ptr->z_rot;
    new_group_ptr->scale_x = group_ptr->scale_x;
    new_group_ptr->scale_y = group_ptr->scale_y;
    new_group_ptr->center_x = group_ptr->center_x;
    new_group_ptr->center_y = group_ptr->center_y;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != HUSPR_NONE) {
            HuSprite *old_sprite = &HuSprData[group_ptr->members[i]];
            s16 new_sprite = HuSprCreate(old_sprite->data, old_sprite->prio, old_sprite->bank);
            HuSprData[new_sprite] = *old_sprite;
            HuSprGrpMemberSet(new_group, i, new_sprite);
        }
    }
    return new_group;
}

void HuSprGrpMemberSet(s16 group, s16 member, s16 sprite)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    HuSprite *sprite_ptr = &HuSprData[sprite];
    if(group_ptr->capacity == 0 || group_ptr->capacity <= member || group_ptr->members[member] != HUSPR_NONE) {
        return;
    }
    group_ptr->members[member] = sprite;
}

void HuSprGrpMemberKill(s16 group, s16 member)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    if(group_ptr->capacity == 0 || group_ptr->capacity <= member || group_ptr->members[member] == HUSPR_NONE) {
        return;
    }
    HuSprKill(group_ptr->members[member]);
    group_ptr->members[member] = HUSPR_NONE;
}

void HuSprGrpKill(s16 group)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    s16 i;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != HUSPR_NONE) {
            HuSprKill(group_ptr->members[i]);
        }
    }
    group_ptr->capacity = 0;
    HuMemDirectFree(group_ptr->members);
}

void HuSprKill(s16 sprite)
{
    HuSprite *sprite_ptr = &HuSprData[sprite];
    if(!sprite_ptr->data) {
        return;
    }
    if(!(sprite_ptr->attr & HUSPR_ATTR_FUNC)) {
        HuSprAnimKill(sprite_ptr->data);
        if(sprite_ptr->bg) {
            HuSprAnimKill(sprite_ptr->bg);
            sprite_ptr->bg = NULL;
        }
    }
    sprite_ptr->data = NULL;
}

void HuSprAnimKill(AnimData *anim)
{
    if(--anim->useNum <= 0) {
        if(anim->bmpNum & ANIM_BMP_ALLOC) {
            if(anim->bmp->data) {
                HuMemDirectFree(anim->bmp->data);
            }
            if(anim->bmp->palData) {
                HuMemDirectFree(anim->bmp->palData);
            }
        }
#ifdef TARGET_PC
        HuMemDirectFree(anim->bank);
        HuMemDirectFree(anim->pat);
        HuMemDirectFree(anim->bmp);
#endif
        HuMemDirectFree(anim);
    }
}

void HuSprAttrSet(s16 group, s16 member, s32 attr)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    HuSprite *sprite_ptr;
    if(group_ptr->capacity == 0 || group_ptr->capacity <= member || group_ptr->members[member] == HUSPR_NONE) {
        return;
    }
    sprite_ptr = &HuSprData[group_ptr->members[member]];
    sprite_ptr->attr |= attr;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_ATTR;
}

void HuSprAttrReset(s16 group, s16 member, s32 attr)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    HuSprite *sprite_ptr;
    if(group_ptr->capacity == 0 || group_ptr->capacity <= member || group_ptr->members[member] == HUSPR_NONE) {
        return;
    }
    sprite_ptr = &HuSprData[group_ptr->members[member]];
    sprite_ptr->attr &= ~attr;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_ATTR;
}

void HuSprPosSet(s16 group, s16 member, float x, float y)
{
    HuSprite *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->x = x;
    sprite_ptr->y = y;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_XFORM;
}

void HuSprZRotSet(s16 group, s16 member, float z_rot)
{
    HuSprite *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->z_rot = z_rot;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_XFORM;
}

void HuSprScaleSet(s16 group, s16 member, float x, float y)
{
    HuSprite *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->scale_x = x;
    sprite_ptr->scale_y = y;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_XFORM;
}

void HuSprTPLvlSet(s16 group, s16 member, float tp_lvl)
{
    HuSprite *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->a = tp_lvl*255;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_COLOR;
}

void HuSprColorSet(s16 group, s16 member, u8 r, u8 g, u8 b)
{
    HuSprite *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->r = r;
    sprite_ptr->g = g;
    sprite_ptr->b = b;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_COLOR;
}

void HuSprSpeedSet(s16 group, s16 member, float speed)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    HuSprData[group_ptr->members[member]].speed = speed;
}

void HuSprBankSet(s16 group, s16 member, s16 bank)
{
    HuSprite *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    AnimData *anim = sprite_ptr->data;
    AnimBankData *bank_ptr = &anim->bank[sprite_ptr->bank];
    AnimFrameData *frame_ptr = &bank_ptr->frame[sprite_ptr->frame];
    sprite_ptr->bank = bank;
    if(sprite_ptr->attr & HUSPR_ATTR_REVERSE) {
        sprite_ptr->frame = bank_ptr->timeNum-1;
        frame_ptr = &bank_ptr->frame[sprite_ptr->frame];
        sprite_ptr->time = frame_ptr->time;
    } else {
        sprite_ptr->time = 0;
        sprite_ptr->frame = 0;
    }
}

void HuSprGrpPosSet(s16 group, float x, float y)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    s16 i;
    group_ptr->x = x;
    group_ptr->y = y;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != -1) {
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_XFORM;
        }
    }
}

void HuSprGrpCenterSet(s16 group, float x, float y)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    s16 i;
    group_ptr->center_x = x;
    group_ptr->center_y = y;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != HUSPR_NONE) {
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_XFORM;
        }
    }
}

void HuSprGrpZRotSet(s16 group, float z_rot)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    s16 i;
    group_ptr->z_rot = z_rot;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != HUSPR_NONE) {
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_XFORM;
        }
    }
}

void HuSprGrpScaleSet(s16 group, float x, float y)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    s16 i;
    group_ptr->scale_x = x;
    group_ptr->scale_y = y;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != HUSPR_NONE) {
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_XFORM;
        }
    }
}

void HuSprGrpTPLvlSet(s16 group, float tp_lvl)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    s16 i;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != HUSPR_NONE) {
            HuSprData[group_ptr->members[i]].a = tp_lvl*255;
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_COLOR;
        }
    }
}

void HuSprGrpDrawNoSet(s16 group, s32 draw_no)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    s16 i;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != HUSPR_NONE) {
            HuSprData[group_ptr->members[i]].draw_no = draw_no;
        }
    }
}

void HuSprDrawNoSet(s16 group, s16 member, s32 draw_no)
{
    HuSprite *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->draw_no = draw_no;
}

void HuSprPriSet(s16 group, s16 member, s16 prio)
{
    HuSprite *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->prio = prio;
}

void HuSprGrpScissorSet(s16 group, s16 x, s16 y, s16 w, s16 h)
{
    HuSprGrp *group_ptr = &HuSprGrpData[group];
    s16 i;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != HUSPR_NONE) {
            HuSprScissorSet(group, i, x, y, w, h);
        }
    }
}

void HuSprScissorSet(s16 group, s16 member, s16 x, s16 y, s16 w, s16 h)
{
    HuSprite *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->scissor_x = x;
    sprite_ptr->scissor_y = y;
    sprite_ptr->scissor_w = w;
    sprite_ptr->scissor_h = h;
}

static s16 bitSizeTbl[11] = { 32, 24, 16, 8, 4, 16, 8, 8, 4, 8, 4 };

AnimData *HuSprAnimMake(s16 sizeX, s16 sizeY, s16 dataFmt)
{
    AnimLayerData *layer;
    AnimBmpData *bmp;
    AnimData *anim;
    AnimPatData *pat;
    AnimFrameData *frame;
    void *temp;
    AnimBankData *bank;
    AnimData *new_anim;

#ifdef TARGET_PC
    // as these are allocated in HuSprAnimRead, we need to do so here too so we don't get issues when freeing
    anim = HuMemDirectMalloc(HEAP_DATA, sizeof(AnimData));
    anim->bank = bank = HuMemDirectMalloc(HEAP_DATA, sizeof(AnimBankData));
    bank->frame = frame = HuMemDirectMalloc(HEAP_DATA, sizeof(AnimFrameData));
    anim->pat = pat = HuMemDirectMalloc(HEAP_DATA, sizeof(AnimPatData));
    pat->layer = layer = HuMemDirectMalloc(HEAP_DATA, sizeof(AnimLayerData));
    anim->bmp = bmp = HuMemDirectMalloc(HEAP_DATA, sizeof(AnimBmpData));
#else
    anim = new_anim = HuMemDirectMalloc(HEAP_DATA, sizeof(AnimData)+sizeof(AnimBankData)+sizeof(AnimFrameData)
                                            +sizeof(AnimPatData)+sizeof(AnimLayerData)+sizeof(AnimBmpData));

    bank = temp = &new_anim[1];
    anim->bank = bank;
    frame = temp = ((char *)temp+sizeof(AnimBankData));
    bank->frame = frame;
    pat = temp = ((char *)temp+sizeof(AnimFrameData));
    anim->pat = pat;
    layer = temp = ((char *)temp+sizeof(AnimPatData));
    pat->layer = layer;
    bmp = temp = ((char *)temp+sizeof(AnimLayerData));
    anim->bmp = bmp;
#endif
    anim->useNum = 0;
    anim->bankNum = 1;
    anim->patNum = 1;
    anim->bmpNum = (1|ANIM_BMP_ALLOC);
    bank->timeNum = 1;
    bank->unk = 10;
    frame->pat = 0;
    frame->time = 10;
    frame->shiftX = frame->shiftY = frame->flip = 0;
    pat->layerNum = 1;
    pat->centerX = sizeX/2;
    pat->centerY = sizeY/2;
    pat->sizeX = sizeX;
    pat->sizeY = sizeY;
    layer->alpha = 255;
    layer->flip = 0;
    layer->bmpNo = 0;
    layer->startX = layer->startY = 0;
    layer->sizeX = sizeX;
    layer->sizeY = sizeY;
    layer->shiftX = layer->shiftY = 0;
    layer->vtx[0] = layer->vtx[1] = 0;
    layer->vtx[2] = sizeX;
    layer->vtx[3] = 0;
    layer->vtx[4] = sizeX;
    layer->vtx[5] = sizeY;
    layer->vtx[6] = 0;
    layer->vtx[7] = sizeY;
    bmp->pixSize = bitSizeTbl[dataFmt];
    bmp->dataFmt = dataFmt;
    bmp->palNum = 0;
    bmp->sizeX = sizeX;
    bmp->sizeY = sizeY;
    bmp->dataSize = sizeX*sizeY*bitSizeTbl[dataFmt]/8;
    bmp->palData = NULL;
    bmp->data = NULL;
    return anim;
}

void HuSprBGSet(s16 group, s16 member,  AnimData *bg, s16 bg_bank)
{
    s16 sprite = HuSprGrpData[group].members[member];
    HuSprSprBGSet(sprite, bg, bg_bank);
}

void HuSprSprBGSet(s16 sprite, AnimData *bg, s16 bg_bank)
{
    HuSprite *sprite_ptr = &HuSprData[sprite];
    sprite_ptr->bg = bg;
    sprite_ptr->bg_bank = bg_bank;
    sprite_ptr->wrap_t = sprite_ptr->wrap_s = GX_REPEAT;
    sprite_ptr->attr &= ~HUSPR_ATTR_LINEAR;
}

void AnimDebug(AnimData *anim)
{
    AnimPatData *pat;
    AnimLayerData *layer;
    s16 i;
    s16 j;
    AnimFrameData *frame;
    AnimBankData *bank;
    AnimBmpData *bmp;
    
    OSReport("patNum %d,bankNum %d,bmpNum %d\n", anim->patNum, anim->bankNum, anim->bmpNum & ANIM_BMP_NUM_MASK);
    pat = anim->pat;
    for(i=0; i<anim->patNum; i++) {
        OSReport("PATTERN%d:\n", i);
        OSReport("\tlayerNum %d,center (%d,%d),size (%d,%d)\n", pat->layerNum, pat->centerX, pat->centerX, pat->sizeX, pat->sizeY);
        layer = pat->layer;
        for(j=0; j<pat->layerNum; j++) {
            OSReport("\t\tfileNo %d,flip %x\n", layer->bmpNo, layer->flip);
            OSReport("\t\tstart (%d,%d),size (%d,%d),shift (%d,%d)\n", layer->startX, layer->startY, layer->sizeX, layer->sizeY, layer->shiftX, layer->shiftY);
            if(j != pat->layerNum-1) {
                OSReport("\n");
            }
            layer++;
        }
        pat++;
    }
    bank = anim->bank;
    for(i=0; i<anim->bankNum; i++) {
        OSReport("BANK%d:\n", i);
        OSReport("\ttimeNum %d\n", bank->timeNum);
        frame = bank->frame;
        for(j=0; j<bank->timeNum; j++) {
            OSReport("\t\tpat %d,time %d,shift(%d,%d),flip %x\n", frame->pat, frame->time, frame->shiftX, frame->shiftY, frame->flip);
            frame++;
        }
        bank++;
    }
    bmp = anim->bmp;
    for(i = 0; i < anim->bmpNum & ANIM_BMP_NUM_MASK; i++) {
        OSReport("BMP%d:\n", i);
        OSReport("\tpixSize %d,palNum %d,size (%d,%d)\n", bmp->pixSize, bmp->palNum, bmp->sizeX, bmp->sizeY);
        bmp++;
    }
}

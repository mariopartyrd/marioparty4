#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/object.h"
#include <game/sprite.h>
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/minigame_seq.h"
#include "game/window.h"


#define OM_OVL_HIS_MAX 16
#define OM_MAX_GROUPS 10

typedef struct om_obj_group {
    u16 next_idx;
    u16 max_objs;
    u16 num_objs;
    u16 *next;
    omObjData **obj;
} omObjGroup;

typedef struct om_obj_man {
    s16 max_objs;
    s16 num_objs;
    s16 next_idx;
    s16 obj_last;
    s16 obj_first;
    s16 unkA;
    omObjData *obj;
    omObjGroup *group;
} omObjMan;

omObjData *omDBGSysKeyObj;
Process *omwatchproc;
OverlayID omnextovl;
SHARED_SYM OverlayID omcurovl;
s32 omcurdll;
SHARED_SYM s32 omovlhisidx;
SHARED_SYM s32 omovlevtno;
s32 omnextovlevtno;
SHARED_SYM u32 omovlstat;
static s32 omnextovlstat;
char omUPauseFlag;
SHARED_SYM s16 omSysExitReq;
s16 omdispinfo;

#ifdef TARGET_PC
OverlayID pcOvlToKill = OVL_INVALID;
s16 pcOvlKillArg = 0;
#endif

static omOvlHisData omovlhis[OM_OVL_HIS_MAX];

u8 omSysPauseEnableFlag = TRUE;
OverlayID omprevovl = OVL_INVALID;

static void omWatchOverlayProc(void);
static void omInsertObj(Process *objman_process, omObjData *object);

void omMasterInit(s32 prio, FileListEntry *ovl_list, s32 ovl_count, OverlayID start_ovl)
{
    omDLLInit(ovl_list);
    omwatchproc = HuPrcCreate(omWatchOverlayProc, prio, 8192, 0);
    HuPrcSetStat(omwatchproc, 12);
    omcurovl = OVL_INVALID;
    omovlhisidx = -1;
    omOvlCallEx(start_ovl, 1, 0, 0);
    omDBGSysKeyObj = NULL;
    omSysPauseEnable(TRUE);
}

static void omWatchOverlayProc(void)
{
    while (1) {
        if (omcurovl == OVL_INVALID) {
#ifdef TARGET_PC
            if (pcOvlToKill >= 0) {
                omDLLNumEnd(pcOvlToKill, pcOvlKillArg);
                pcOvlToKill = OVL_INVALID;
            }
#endif
            if (omnextovl >= 0 && fadeStat == 0) {
                HuPrcSleep(0);
                OSReport("++++++++++++++++++++ Start New OVL %d (EVT:%d STAT:0x%08x) ++++++++++++++++++\n", omnextovl, omnextovlevtno, omnextovlstat);
                HuMemHeapDump(HuMemHeapPtrGet(HEAP_SYSTEM), -1);
                HuMemHeapDump(HuMemHeapPtrGet(HEAP_DATA), -1);
                HuMemHeapDump(HuMemHeapPtrGet(HEAP_DVD), -1);
                OSReport("objman>Used Memory Size:%08x\n", HuMemUsedMallocSizeGet(HEAP_SYSTEM));
                OSReport("objman>Used Memory Cnt:%d\n", HuMemUsedMallocBlockGet(HEAP_SYSTEM));
                OSReport("objman>Init esp\n");
                espInit();
                OSReport("objman>Call objectsetup\n");
                HuAudVoiceInit(omnextovl);
                HuAudDllSndGrpSet(omnextovl);
                omcurovl = omnextovl;
                omovlevtno = omnextovlevtno;
                omovlstat = omnextovlstat;
                omnextovl = OVL_INVALID;
                if (_CheckFlag(FLAG_ID_MAKE(1, 12))) {
                    MGSeqPracticeInit();
                }
                omSysPauseEnable(TRUE);
                omcurdll = omDLLStart(omcurovl, 0);
                OSReport("objman>ObjectSetup end\n");
                if (omcurovl != OVL_INVALID) {
                    goto watch_child;
                }
                else {
                    continue;
                }
            }
            else {
                HuPrcVSleep();
            }
        }
        else {
        watch_child:
            HuPrcChildWatch();
        }
    }
}

void omOvlCallEx(OverlayID overlay, s16 arg2, s32 event, s32 stat)
{
    OSReport("objman>Call New Ovl %d(%d)\n", overlay, arg2);
    if (omovlhisidx >= OM_OVL_HIS_MAX) {
        OSReport("objman>OVL Call over error\n");
        return;
    }
    omovlhis[++omovlhisidx].overlay = overlay;
    omovlhis[omovlhisidx].event = event;
    omovlhis[omovlhisidx].stat = stat;

    omOvlGotoEx(overlay, arg2, event, stat);
}

void omOvlGotoEx(OverlayID overlay, s16 arg2, s32 event, s32 stat)
{
    omprevovl = omcurovl;
    if (omcurovl >= 0) {
        omOvlKill(arg2);
    }
    omnextovl = overlay;
    omnextovlevtno = event;
    omnextovlstat = stat;
}

void omOvlReturnEx(s16 level, s16 arg2)
{
    omovlhisidx -= level;
    OSReport("objman>Ovl Return %d=%d(%d)\n", level, omovlhisidx, arg2);
    if (omovlhisidx < 0) {
        OSReport("objman>OVL under error\n");
        omovlhisidx = 0;
    }
    omOvlGotoEx(omovlhis[omovlhisidx].overlay, arg2, omovlhis[omovlhisidx].event, omovlhis[omovlhisidx].stat);
}

void omOvlKill(s16 arg)
{
    CharModelKill(-1);
    MGSeqKillAll();
    Hu3DAllKill();
    HuWinAllKill();
    HuSprClose();
    HuPrcChildKill(omwatchproc);
    HuMemDirectFreeNum(HEAP_SYSTEM, MEMORY_DEFAULT_NUM);
    HuDataDirCloseNum(MEMORY_DEFAULT_NUM);
    HuMemDirectFreeNum(HEAP_DVD, MEMORY_DEFAULT_NUM);
    HuMemDirectFreeNum(HEAP_DATA, MEMORY_DEFAULT_NUM);
    HuPadRumbleAllStop();
    HuAudFXListnerKill();
    OSReport("OvlKill %d\n", arg);
    omSysExitReq = FALSE;
#ifdef TARGET_PC
    // this function is called from the DLL, we can't kill it directly here
    pcOvlToKill = omcurovl;
    pcOvlKillArg = arg;
#else
    omDLLNumEnd(omcurovl, arg);
#endif
    omcurovl = OVL_INVALID;
    omDBGSysKeyObj = NULL;
}

void omOvlHisChg(s32 level, OverlayID overlay, s32 event, s32 stat)
{
    omOvlHisData *history;
    if (omovlhisidx - level < 0 || omovlhisidx - level >= OM_OVL_HIS_MAX) {
        OSReport("objman> omOvlHisChg: overlay 実行履歴の範囲外を変更しようとしました\n");
        return;
    }
    history = &omovlhis[omovlhisidx - level];
    history->overlay = overlay;
    history->event = event;
    history->stat = stat;
}

omOvlHisData *omOvlHisGet(s32 level)
{
    if (omovlhisidx - level < 0 || omovlhisidx - level >= OM_OVL_HIS_MAX) {
        OSReport("objman> omOvlHisGet: overlay 実行履歴の範囲外を参照しようとしました\n");
        return NULL;
    }
    return &omovlhis[omovlhisidx - level];
}

Process *omInitObjMan(s16 max_objs, s32 prio)
{
    omObjGroup *group_all;
    omObjData *obj_all;
    omObjData *obj;
    s32 i;
    omObjMan *objman;
    Process *process;
    OSReport("objman>InitObjMan start\n");
    max_objs += 2;
    omSysExitReq = FALSE;
    process = HuPrcChildCreate(omMain, prio, 16384, 0, omwatchproc);
    HuPrcSetStat(process, PROCESS_STAT_PAUSE_EN | PROCESS_STAT_UPAUSE_EN);
    objman = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(omObjMan), MEMORY_DEFAULT_NUM);
    objman->max_objs = max_objs;
    process->user_data = objman;
    process->dtor = omDestroyObjMan;
    objman->num_objs = 0;
    objman->next_idx = 0;
    objman->obj_last = -1;
    objman->obj_first = -1;
    obj_all = HuMemDirectMallocNum(HEAP_SYSTEM, max_objs * sizeof(omObjData), MEMORY_DEFAULT_NUM);
    objman->obj = obj_all;
    group_all = HuMemDirectMallocNum(HEAP_SYSTEM, OM_MAX_GROUPS * sizeof(omObjGroup), MEMORY_DEFAULT_NUM);
    objman->group = group_all;
    for (i = 0; i < max_objs; i++) {
        obj = &obj_all[i];
        obj->stat = 1;
        obj->prio = obj->prev = obj->next = -1;
        obj->unk10 = 0;
        obj->trans.x = obj->trans.y = obj->trans.z = obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
        obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        obj->model = obj->motion = NULL;
        obj->func = obj->data = NULL;
        obj->next_idx = i + 1;
        obj->mtncnt = 0;
        obj->motion = NULL;
    }
    for (i = 0; i < OM_MAX_GROUPS; i++) {
        group_all[i].max_objs = 0;
        group_all[i].num_objs = 0;
        group_all[i].next_idx = 0;
        group_all[i].obj = NULL;
        group_all[i].next = NULL;
    }
    OSReport("objman>InitObjMan end\n");
    omUPauseFlag = FALSE;
    HuPrcAllUPause(0);
    return process;
}

void omDestroyObjMan(void)
{
    Process *process = HuPrcCurrentGet();
    omObjMan *objman = process->user_data;
    objman->obj_last = -1;
    OSReport("objman>Destory ObjMan\n");
}

omObjData *omAddObjEx(Process *objman_process, s16 prio, u16 mdlcnt, u16 mtncnt, s16 group, void (*func)(omObjData *))
{
    s32 i;
    omObjData *object;
    s16 next_idx;
    omObjMan *objman = objman_process->user_data;
    omObjData *obj_base = objman->obj;
    if (objman->num_objs == objman->max_objs) {
        return NULL;
    }
    next_idx = objman->next_idx;
    object = &obj_base[next_idx];
    object->next_idx_alloc = next_idx;
    object->prio = prio;
    omInsertObj(objman_process, object);
    if (mdlcnt) {
        object->model = HuMemDirectMallocNum(HEAP_SYSTEM, mdlcnt * sizeof(s16), MEMORY_DEFAULT_NUM);
        object->mdlcnt = mdlcnt;
        for (i = 0; i < mdlcnt; i++) {
            object->model[i] = -1;
        }
    }
    else {
        object->model = NULL;
        object->mdlcnt = 0;
    }
    if (mtncnt) {
        object->motion = HuMemDirectMallocNum(HEAP_SYSTEM, mtncnt * sizeof(s16), MEMORY_DEFAULT_NUM);
        object->mtncnt = mtncnt;
    }
    else {
        object->motion = NULL;
        object->mtncnt = 0;
    }
    if (group >= 0) {
        omAddMember(objman_process, group, object);
    }
    else {
        object->group = group;
        object->group_idx = 0;
    }
    object->stat = OM_STAT_ACTIVE;
    object->unk10 = 0;
    object->func = func;
    object->work[0] = object->work[1] = object->work[2] = object->work[3] = 0;
    objman->next_idx = object->next_idx;
    objman->num_objs++;
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    return object;
}

static void omInsertObj(Process *objman_process, omObjData *object)
{
    omObjData *obj_new;
    omObjMan *objman = objman_process->user_data;
    omObjData *obj_all = objman->obj;
    s16 next_idx_alloc = object->next_idx_alloc;
    s16 prio = object->prio;
    s16 obj_idx;
    s16 prev_idx;
    if (objman->obj_first == -1) {
        object->prev = -1;
        object->next = -1;
        objman->obj_first = next_idx_alloc;
        objman->obj_last = next_idx_alloc;
        (void)objman; // HACK for matching
        return;
    }
    for (obj_idx = objman->obj_first; obj_idx != -1; obj_idx = obj_new->next) {
        obj_new = &obj_all[obj_idx];
        if (obj_new->prio <= prio) {
            break;
        }
        prev_idx = obj_idx;
    }
    if (obj_idx != -1) {
        object->prev = obj_new->prev;
        object->next = obj_idx;
        if (obj_new->prev != -1) {
            obj_all[obj_new->prev].next = next_idx_alloc;
        }
        else {
            objman->obj_first = next_idx_alloc;
        }
        obj_new->prev = next_idx_alloc;
    }
    else {
        object->next = -1;
        object->prev = prev_idx;
        obj_new->next = next_idx_alloc;
        objman->obj_last = next_idx_alloc;
    }
}

void omAddMember(Process *objman_process, u16 group, omObjData *object)
{
    omObjMan *objman = objman_process->user_data;
    omObjGroup *group_ptr = &objman->group[group];
    if (group_ptr->num_objs != group_ptr->max_objs) {
        object->group = group;
        object->group_idx = group_ptr->next_idx;
        group_ptr->obj[group_ptr->next_idx] = object;
        group_ptr->next_idx = group_ptr->next[group_ptr->next_idx];
        group_ptr->num_objs++;
    }
}

void omDelObjEx(Process *objman_process, omObjData *object)
{
    omObjMan *objman = objman_process->user_data;
    omObjData *obj_all = objman->obj;
    s16 next_idx_alloc = object->next_idx_alloc;
    if (objman->num_objs == 0 || object->stat == 1) {
        return;
    }
    objman->num_objs--;
    if (object->group >= 0) {
        omDelMember(objman_process, object);
    }
    if (object->motion != NULL) {
        HuMemDirectFree(object->motion);
        object->motion = NULL;
    }
    if (object->model != NULL) {
        HuMemDirectFree(object->model);
        object->model = NULL;
    }
    if (object->data != NULL) {
        HuMemDirectFree(object->data);
        object->data = NULL;
    }
    object->stat = OM_STAT_DELETED;
    if (object->next >= 0) {
        obj_all[object->next].prev = object->prev;
    }
    if (object->prev >= 0) {
        obj_all[object->prev].next = object->next;
    }
    if (objman->num_objs != 0) {
        if (object->prev < 0) {
            objman->obj_first = obj_all[object->next].next_idx_alloc;
        }
        if (object->next < 0) {
            objman->obj_last = obj_all[object->prev].next_idx_alloc;
        }
    }
    else {
        objman->obj_first = objman->obj_last = -1;
    }
    object->next_idx = objman->next_idx;
    objman->next_idx = next_idx_alloc;
}

void omDelMember(Process *objman_process, omObjData *object)
{
    if (object->group != -1) {
        omObjMan *objman = objman_process->user_data;
        omObjData *obj_all = objman->obj;
        omObjGroup *group = &objman->group[object->group];
        group->obj[object->group_idx] = NULL;
        group->next[object->group_idx] = group->next_idx;
        group->next_idx = object->group_idx;
        object->group = -1;
        group->num_objs--;
    }
}

void omMakeGroupEx(Process *objman_process, u16 group, u16 max_objs)
{
    s32 i;
    omObjMan *objman = objman_process->user_data;
    omObjGroup *group_ptr = &objman->group[group];
    if (group_ptr->obj != NULL) {
        HuMemDirectFree(group_ptr->obj);
    }
    if (group_ptr->next != NULL) {
        HuMemDirectFree(group_ptr->next);
    }
    group_ptr->next_idx = 0;
    group_ptr->max_objs = max_objs;
    group_ptr->num_objs = 0;
    group_ptr->obj = HuMemDirectMallocNum(HEAP_SYSTEM, max_objs * sizeof(omObjData *), MEMORY_DEFAULT_NUM);
    group_ptr->next = HuMemDirectMallocNum(HEAP_SYSTEM, max_objs * sizeof(u16), MEMORY_DEFAULT_NUM);
    for (i = 0; i < max_objs; i++) {
        group_ptr->obj[i] = NULL;
        group_ptr->next[i] = i + 1;
    }
}

omObjData **omGetGroupMemberListEx(Process *objman_process, s16 group)
{
    omObjMan *objman = objman_process->user_data;
    return objman->group[group].obj;
}

void omSetStatBit(omObjData *obj, u16 stat)
{
    obj->stat |= stat;
}

void omResetStatBit(omObjData *obj, u16 stat)
{
    obj->stat &= ~stat;
}

void omSetTra(omObjData *obj, float x, float y, float z)
{
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
}

void omSetRot(omObjData *obj, float x, float y, float z)
{
    obj->rot.x = x;
    obj->rot.y = y;
    obj->rot.z = z;
}

void omSetSca(omObjData *obj, float x, float y, float z)
{
    obj->scale.x = x;
    obj->scale.y = y;
    obj->scale.z = z;
}

void omMain(void)
{
    Process *process = HuPrcCurrentGet();
    omObjMan *objman = process->user_data;
    omObjData *obj_all = objman->obj;
    omObjData *object;
    s16 obj_index;
    omDLLDBGOut();
    while (1) {
        if (omdispinfo) {
            float scale = 1.5f;
            GXColor color;
            color.a = 96;
            color.r = 0;
            color.g = 0;
            color.b = 255;
            printWin(7, 23, 128 * scale, 40 * scale, &color);
            fontcolor = FONT_COLOR_YELLOW;
            print8(8, 24, scale, "\xFD\x01H:%08lX(%ld)", HuMemUsedMallocSizeGet(HEAP_SYSTEM), HuMemUsedMallocBlockGet(HEAP_SYSTEM));
            print8(8, 24 + (8 * scale), scale, "\xFD\x01M:%08lX(%ld)", HuMemUsedMallocSizeGet(HEAP_DATA), HuMemUsedMallocBlockGet(HEAP_DATA));
            print8(8, 24 + (16 * scale), scale, "\xFD\x01OBJ:%d/%d", objman->num_objs, objman->max_objs);
            print8(8, 24 + (24 * scale), scale, "\xFD\x01OVL:%ld(%ld<%ld)", omovlhisidx, omcurovl, omprevovl);
            print8(8, 24 + (32 * scale), scale, "\xFD\x01POL:%ld", totalPolyCnted);
        }
        obj_index = objman->obj_last;
        while (obj_index != -1) {
            object = &obj_all[obj_index];
            obj_index = object->prev;
            if ((object->stat & (OM_STAT_DELETED | OM_STAT_DISABLED)) == 0) {
                if (object->func != NULL && (object->stat & (0x40 | 0x8 | OM_STAT_PAUSED)) == 0) {
                    object->func(object);
                }
                if (omcurovl == -1 || objman->obj_last == -1) {
                    break;
                }
                if ((object->stat & (OM_STAT_DELETED | OM_STAT_DISABLED)) == 0) {
                    if ((obj_all[obj_index].stat & (OM_STAT_DELETED | OM_STAT_DISABLED)) != 0) {
                        obj_index = object->prev;
                    }
                    if (object->model != NULL && object->model[0] != -1 && !(object->stat & OM_STAT_MODEL_PAUSED)) {
                        Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
                        Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
                        Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
                    }
                }
            }
        }
        HuPrcVSleep();
    }
}

// Dummy function to force string literals in binary
static void omDumpObj(Process *objman_process)
{
    omObjMan *objman = objman_process->user_data;
    omObjData *obj_all = objman->obj;
    s32 i;
    OSReport("=================== 現在登録されている OBJECT ==================\n");
    OSReport("STAT PRI GRPN MEMN PROG (TRA) (ROT) (SCA) mdlcnt mtncnt work[0] work[1] work[2] work[3] *data\n");
    for (i = 0; i < objman->max_objs; i++) {
        omObjData *object = &obj_all[i];
        OSReport("%04d:%04X %04X %d %d %08X (%.2f %.2f %.2f) (%.2f %.2f %.2f) (%.2f %.2f %.2f) %d %d %08X %08X %08X %08X %08X\n", object->stat,
            object->stat, object->prio, object->group, object->unk10, object->func, object->trans.x, object->trans.y, object->trans.z, object->rot.x,
            object->rot.y, object->rot.z, object->scale.x, object->scale.y, object->scale.z, object->mdlcnt, object->mtncnt, object->work[0],
            object->work[1], object->work[2], object->work[3], object->data);
    }
    OSReport("================================================================\n");
}

void omAllPause(BOOL pause)
{
    Process *objman_process = HuPrcCurrentGet();
    omObjMan *objman = objman_process->user_data;
    s32 i;
    if (pause) {
        for (i = 0; i < objman->max_objs; i++) {
            if ((objman->obj[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE)) == 0) {
                omSetStatBit(&objman->obj[i], OM_STAT_PAUSED);
            }
        }
    }
    else {
        for (i = 0; i < objman->max_objs; i++) {
            if ((objman->obj[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE)) == 0) {
                omResetStatBit(&objman->obj[i], OM_STAT_PAUSED);
            }
        }
    }
}

char omPauseChk(void)
{
    if (omDBGSysKeyObj == NULL) {
        return 0;
    }
    else {
        return omDBGSysKeyObj->work[0] & 0x1;
    }
}

OverlayID omCurrentOvlGet(void)
{
    return omcurovl;
}

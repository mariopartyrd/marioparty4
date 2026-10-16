#include "game/audio.h"
#include "game/frand.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"

#include "ext_math.h"

#include "REL/m401Dll.h"

#ifndef __MWERKS__
extern s32 rand8(void);
#endif

struct ScoreParticlePoolEntry {
    s16 is_allocated;
    s16 particle_model_ids[3];
};

ANIMDATA *score_particle_animation_a;
ANIMDATA *score_particle_animation_b;
ANIMDATA *score_particle_animation_c;
ANIMDATA *score_particle_bonus_animation;
ANIMDATA *score_particle_animation_d;
ANIMDATA *score_particle_animation_e;
ANIMDATA *score_particle_animation_f;
ANIMDATA *score_particle_animation_table[2][3];
struct ScoreParticlePoolEntry score_particle_pool[28];
s16 score_particle_model_ids[4];
s16 next_score_particle_pool_slot;
float unused_particle_parameter;
float camera_field_of_view;
float camera_near_plane;
float camera_far_plane;
s16 camera_aspect_ratio;

void project_world_position_to_screen(Vec *world_position, Vec *screen_position)
{
    HU3DCAMERA *camera;
    Mtx lookat;
    Mtx44 proj;
    float coord[4];
    world_position->y = -world_position->y;
    camera = &Hu3DCamera[0];
    MTXLookAt(lookat, &camera->pos, &camera->up, &camera->target);
    MTXMultVec(lookat, world_position, world_position);
    MTXPerspective(proj, camera->fov, camera->aspect, camera->near, camera->far);
    coord[0] = (world_position->x * proj[0][0]) + (world_position->y * proj[0][1]) + (world_position->z * proj[0][2]) + proj[0][3];
    coord[1] = (world_position->x * proj[1][0]) + (world_position->y * proj[1][1]) + (world_position->z * proj[1][2]) + proj[1][3];
    coord[2] = (world_position->x * proj[2][0]) + (world_position->y * proj[2][1]) + (world_position->z * proj[2][2]) + proj[2][3];
    coord[3] = (world_position->x * proj[3][0]) + (world_position->y * proj[3][1]) + (world_position->z * proj[3][2]) + proj[3][3];
    screen_position->x = ((coord[0] / coord[3]) * 320.0f) + 320.0f;
    screen_position->y = ((coord[1] / coord[3]) * 240.0f) + 240.0f;
    screen_position->z = coord[2] / coord[3];
}

void load_score_particle_resources(void)
{
    s32 i;
    score_particle_animation_a = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x11));
    score_particle_animation_b = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x12));
    score_particle_animation_c = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x13));
    score_particle_animation_d = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x14));
    score_particle_animation_e = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x15));
    score_particle_animation_f = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x16));
    HuSprAnimLock(score_particle_animation_a);
    HuSprAnimLock(score_particle_animation_b);
    HuSprAnimLock(score_particle_animation_c);
    HuSprAnimLock(score_particle_animation_d);
    HuSprAnimLock(score_particle_animation_e);
    HuSprAnimLock(score_particle_animation_f);
    score_particle_bonus_animation = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x26));
    HuSprAnimLock(score_particle_bonus_animation);
    score_particle_animation_table[0][0] = score_particle_animation_a;
    score_particle_animation_table[0][1] = score_particle_animation_b;
    score_particle_animation_table[0][2] = score_particle_animation_c;
    score_particle_animation_table[1][0] = score_particle_animation_d;
    score_particle_animation_table[1][1] = score_particle_animation_e;
    score_particle_animation_table[1][2] = score_particle_animation_f;
    for (i = 0; i < 4; i++) {
        score_particle_model_ids[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x17));
        Hu3DModelAttrSet(score_particle_model_ids[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(score_particle_model_ids[i], HU3D_MOTATTR_LOOP);
        Hu3DModelScaleSet(score_particle_model_ids[i], 1.5f, 1.5f, 1.0f);
        Hu3DModelLayerSet(score_particle_model_ids[i], 2);
    }
}

void free_score_particle_resources(void)
{
    HuSprAnimKill(score_particle_animation_a);
    HuSprAnimKill(score_particle_animation_b);
    HuSprAnimKill(score_particle_animation_c);
    HuSprAnimKill(score_particle_animation_d);
    HuSprAnimKill(score_particle_animation_e);
    HuSprAnimKill(score_particle_animation_f);
    HuSprAnimKill(score_particle_bonus_animation);
}

void create_score_particle_model_pool(void)
{
    s32 i;
    for (i = 0; i < 28; i++) {
        score_particle_pool[i].is_allocated = 0;
        score_particle_pool[i].particle_model_ids[0] = Hu3DParticleCreate(score_particle_animation_a, 80);
        score_particle_pool[i].particle_model_ids[1] = Hu3DParticleCreate(score_particle_animation_b, 80);
        score_particle_pool[i].particle_model_ids[2] = Hu3DParticleCreate(score_particle_animation_c, 80);
        Hu3DModelAttrSet(score_particle_pool[i].particle_model_ids[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(score_particle_pool[i].particle_model_ids[1], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(score_particle_pool[i].particle_model_ids[2], HU3D_ATTR_DISPOFF);
    }
    next_score_particle_pool_slot = 0;
}

s16 acquire_score_particle_pool_slot(void)
{
    s32 i;
    s32 j;
    for (i = 0; i < 28; i++) {
        if (!score_particle_pool[i].is_allocated) {
            for (j = 0; j < 3; j++) {
                Hu3DModelAttrReset(score_particle_pool[i].particle_model_ids[j], HU3D_ATTR_DISPOFF);
            }
            score_particle_pool[i].is_allocated = 1;
            return i;
        }
    }
    return -1;
}

void release_score_particle_pool_slot(s16 pool_slot_index)
{
    s32 i;
    score_particle_pool[pool_slot_index].is_allocated = 0;
    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(score_particle_pool[pool_slot_index].particle_model_ids[i], HU3D_ATTR_DISPOFF);
    }
}

s16 acquire_score_particle_model(void)
{
    s16 particle_model_id = score_particle_model_ids[next_score_particle_pool_slot];
    next_score_particle_pool_slot = (next_score_particle_pool_slot + 1) & 0x3;
    Hu3DModelTPLvlSet(particle_model_id, 1.0f);
    return particle_model_id;
}

void update_score_particle_effect(OMOBJ *object);
void update_score_particle_layer_one(OMOBJ *object);
void update_score_particle_layer_two(OMOBJ *object);
void update_score_particle_layer_three(OMOBJ *object);
void update_score_particle_layer_four(OMOBJ *object);
void update_score_particle_layer_five(OMOBJ *object);
void update_score_particle_layer_six(OMOBJ *object);

void update_score_particle_model(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void update_score_particle_model_visibility(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void update_score_particle_model_motion(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void update_score_particle_sparkle(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void update_score_particle_trail(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void update_score_particle_burst(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void update_score_particle_fade(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);

OMOBJ *create_score_particle_effect(Vec *spawn_position, s16 particle_variant)
{
    OMOBJ *particle_object;
    s32 particle_index;
    HU3DPARTICLE *particle_data;
    ScoreParticleWork *particle_work;
    s16 particle_pool_index = acquire_score_particle_pool_slot();
    if (particle_pool_index < 0) {
        return NULL;
    }
    {
        s16 priority = -1;
        if (particle_variant == 0) {
            priority = 1;
        }
        particle_object = omAddObjEx(HuPrcCurrentGet(), 0x514, 3, 0, priority, NULL);
    }

    particle_object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(ScoreParticleWork), HU_MEMNUM_OVL);
    particle_work = particle_object->data;
    particle_work->particle_position = *spawn_position;
    for (particle_index = 0; particle_index < 3; particle_index++) {
        particle_object->mdlId[particle_index] = score_particle_pool[particle_pool_index].particle_model_ids[particle_index];
        particle_data = Hu3DData[particle_object->mdlId[particle_index]].hookData;
        Hu3DParticleCntSet(particle_object->mdlId[particle_index], 0);
        Hu3DParticleAnimModeSet(particle_object->mdlId[particle_index], 0);
        Hu3DModelLayerSet(particle_object->mdlId[particle_index], 1);
        if (particle_variant == 1) {
            particle_object->mode = acquire_score_particle_model();
            Hu3DModelAttrReset(particle_object->mode, HU3D_ATTR_DISPOFF);
            particle_data->anim = score_particle_animation_table[1][particle_index];
            particle_work->opacity = 1.0f;
            particle_object->work[3] = 45;
            Hu3DModelTPLvlSet(particle_object->mode, particle_work->opacity);
        }
        else {
            particle_data->anim = score_particle_animation_table[0][particle_index];
        }
    }
    particle_work->active_model_callbacks = 3;
    particle_work->pool_slot_index = particle_pool_index;
    particle_work->particle_variant = particle_variant;
    switch (particle_variant) {
        case 1:
            Hu3DModelPosSet(particle_object->mode, spawn_position->x, spawn_position->y, camera_target.z + spawn_position->z);

        case 0:
            particle_object->trans.x = spawn_position->x;
            particle_object->trans.y = spawn_position->y;
            particle_object->trans.z = camera_target.z + spawn_position->z;
            for (particle_index = 0; particle_index < 3; particle_index++) {
                Hu3DParticleHookSet(particle_object->mdlId[particle_index], update_score_particle_model);
                Hu3DParticleColSet(particle_object->mdlId[particle_index], 255, 255, 255);
                Hu3DModelPosSet(particle_object->mdlId[particle_index], particle_object->trans.x, particle_object->trans.y, particle_object->trans.z);
                particle_data = Hu3DData[particle_object->mdlId[particle_index]].hookData;
                Hu3DParticleBlendModeSet(particle_object->mdlId[particle_index], 0);
                particle_data->dataCnt = (particle_index * 4.5f) / 3.0f;
                particle_data->emitCnt = 0;
                particle_data->work = particle_object;
            }
            particle_work->fade_out_requested = 0;
            particle_object->objFunc = update_score_particle_effect;
            break;

        case 2:
            set_object_position(particle_object, spawn_position->x, spawn_position->y, spawn_position->z);
            for (particle_index = 0; particle_index < 3; particle_index++) {
                Hu3DParticleHookSet(particle_object->mdlId[particle_index], update_score_particle_model_visibility);
                Hu3DParticleColSet(particle_object->mdlId[particle_index], 255, 255, 255);
                Hu3DModelPosSet(particle_object->mdlId[particle_index], particle_object->trans.x, particle_object->trans.y, particle_object->trans.z);
                Hu3DParticleBlendModeSet(particle_object->mdlId[particle_index], 0);
                particle_data = Hu3DData[particle_object->mdlId[particle_index]].hookData;
                particle_data->dataCnt = (particle_index * 2) + (frand() & 0x7);
                particle_data->work = particle_object;
            }
            particle_object->objFunc = update_score_particle_layer_one;
            break;

        case 3:
            for (particle_index = 0; particle_index < 3; particle_index++) {
                Hu3DParticleHookSet(particle_object->mdlId[particle_index], update_score_particle_model_motion);
                Hu3DParticleColSet(particle_object->mdlId[particle_index], 255, 255, 255);
                Hu3DModelPosSet(particle_object->mdlId[particle_index], spawn_position->x, spawn_position->y, spawn_position->z);
                Hu3DParticleBlendModeSet(particle_object->mdlId[particle_index], 0);
                particle_data = Hu3DData[particle_object->mdlId[particle_index]].hookData;
                particle_data->dataCnt = (particle_index * 2) + (frand() & 0x7);
                particle_data->work = particle_object;
            }
            particle_object->objFunc = update_score_particle_layer_two;
            break;

        case 4:
            set_object_position(particle_object, spawn_position->x, spawn_position->y, spawn_position->z);
            for (particle_index = 0; particle_index < 3; particle_index++) {
                Hu3DParticleHookSet(particle_object->mdlId[particle_index], update_score_particle_sparkle);
                Hu3DParticleColSet(particle_object->mdlId[particle_index], 255, 255, 255);
                Hu3DModelPosSet(particle_object->mdlId[particle_index], particle_object->trans.x, particle_object->trans.y, particle_object->trans.z);
                Hu3DParticleBlendModeSet(particle_object->mdlId[particle_index], 0);
                particle_data = Hu3DData[particle_object->mdlId[particle_index]].hookData;
                particle_data->dataCnt = (particle_index * 2) + (frand() & 0x7);
                particle_data->work = particle_object;
            }
            particle_object->objFunc = update_score_particle_layer_three;
            break;

        case 5:
            set_object_position(particle_object, spawn_position->x, spawn_position->y, spawn_position->z);
            for (particle_index = 0; particle_index < 3; particle_index++) {
                Hu3DParticleHookSet(particle_object->mdlId[particle_index], update_score_particle_trail);
                Hu3DParticleColSet(particle_object->mdlId[particle_index], 255, 255, 255);
                Hu3DModelPosSet(particle_object->mdlId[particle_index], particle_object->trans.x, particle_object->trans.y, particle_object->trans.z);
                Hu3DParticleBlendModeSet(particle_object->mdlId[particle_index], 1);
                particle_data = Hu3DData[particle_object->mdlId[particle_index]].hookData;
                particle_data->dataCnt = (particle_index * 2) + (frand() & 0x7);
                particle_data->work = particle_object;
            }
            particle_object->objFunc = update_score_particle_layer_four;
            break;

        case 6:
            omSetTra(particle_object, spawn_position->x, spawn_position->y, spawn_position->z);
            for (particle_index = 0; particle_index < 3; particle_index++) {
                Hu3DParticleHookSet(particle_object->mdlId[particle_index], update_score_particle_burst);
                Hu3DParticleColSet(particle_object->mdlId[particle_index], 255, 255, 255);
                Hu3DModelPosSet(particle_object->mdlId[particle_index], particle_object->trans.x, particle_object->trans.y, particle_object->trans.z);
                particle_data = Hu3DData[particle_object->mdlId[particle_index]].hookData;
                Hu3DParticleBlendModeSet(particle_object->mdlId[particle_index], 1);
            }
            particle_object->objFunc = update_score_particle_layer_five;
            break;

        case 7:
            omSetTra(particle_object, spawn_position->x, spawn_position->y, spawn_position->z);
            for (particle_index = 0; particle_index < 3; particle_index++) {
                Hu3DParticleHookSet(particle_object->mdlId[particle_index], update_score_particle_fade);
                Hu3DParticleColSet(particle_object->mdlId[particle_index], 255, 255, 255);
                Hu3DModelPosSet(particle_object->mdlId[particle_index], particle_object->trans.x, particle_object->trans.y, particle_object->trans.z);
                particle_data = Hu3DData[particle_object->mdlId[particle_index]].hookData;
                Hu3DParticleBlendModeSet(particle_object->mdlId[particle_index], 1);
            }
            particle_object->objFunc = update_score_particle_layer_six;
            break;

        default:
            break;
    }
    return particle_object;
}

void fade_score_particle_effect(OMOBJ *object);
void update_score_particle_bonus_model(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);

void update_score_particle_effect(OMOBJ *object)
{
    ScoreParticleWork *particle_work;
    s32 particle_index;
    M401WorkPlayer *player_work;
    OMOBJ *player_object;
    HU3DPARTICLE *particle_data;
    s16 player_id;
    particle_work = object->data;
    particle_work->particle_position.z += (camera_move_distance * 0.5f);
    object->trans.x = particle_work->particle_position.x;
    object->trans.y = particle_work->particle_position.y;
    object->trans.z = camera_target.z + particle_work->particle_position.z;
    if (object->mode != 0) {
        Hu3DModelPosSet(object->mode, object->trans.x, object->trans.y, object->trans.z);
    }
    for (particle_index = 1; particle_index < 3; particle_index++) {
        Hu3DModelRotSet(object->mdlId[particle_index], object->rot.x, object->rot.y, object->rot.z);
        Hu3DModelPosSet(object->mdlId[particle_index], object->trans.x, object->trans.y, object->trans.z);
    }
    for (particle_index = 0; particle_index < 4; particle_index++) {
        float dist;
        player_object = player_objects[particle_index];
        player_work = player_object->data;
        if (player_work->is_stunned != 0) {
            continue;
        }
        dist = VECDistanceXYZ(&object->trans, &player_object->trans);
        if (dist < 108.00001f) {
            Hu3DMotionShiftSet(player_objects[particle_index]->mdlId[0], player_objects[particle_index]->mtnId[6], 0, 10, HU3D_MOTATTR_NONE);
            HuAudFXPlay(1288);
            if (particle_work->particle_variant == 0) {
                HuAudFXPlay(9);
                player_work->score++;
                omVibrate(player_work->player_index, 12, 6, 6);
            }
            else {
                HuAudFXPlay(1292);
                player_work->score_popup_value = 3;
                player_work->score += 3;
                show_score_gain_popup(player_work->player_index);
                omVibrate(player_work->player_index, 12, 4, 2);
            }
            player_work->collision_cooldown = 50;
            for (particle_index = 0; particle_index < 3; particle_index++) {
                particle_data = Hu3DData[object->mdlId[particle_index]].hookData;
                particle_data->emitCnt = 0;
                Hu3DParticleHookSet(object->mdlId[particle_index], update_score_particle_bonus_model);
            }
            object->objFunc = fade_score_particle_effect;
            break;
        }
    }
    if (particle_work->particle_position.z > 850.0f) {
        particle_work->fade_out_requested = 1;
    }
    if (object->mode) {
        if (object->work[3] != 0) {
            object->work[3]--;
        }
        else {
            particle_work->opacity -= 0.033333335f;
            if (particle_work->opacity < 0) {
                particle_work->opacity = 0;
            }
            Hu3DModelTPLvlSet(object->mode, particle_work->opacity);
        }
    }
    if (particle_work->active_model_callbacks == 0) {
        if (object->mode) {
            Hu3DModelAttrSet(object->mode, HU3D_ATTR_DISPOFF);
        }
        release_score_particle_pool_slot(particle_work->pool_slot_index);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fade_score_particle_effect(OMOBJ *object)
{
    ScoreParticleWork *particle_work;
    s32 particle_index;

    particle_work = object->data;
    particle_work->particle_position.z += (camera_move_distance * 0.5f);
    object->trans.x = particle_work->particle_position.x;
    object->trans.y = particle_work->particle_position.y;
    object->trans.z = camera_target.z + particle_work->particle_position.z;
    for (particle_index = 1; particle_index < 3; particle_index++) {
        Hu3DModelPosSet(object->mdlId[particle_index], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->mode != 0) {
        Hu3DModelPosSet(object->mode, object->trans.x, object->trans.y, object->trans.z);
        particle_work->opacity -= 0.033333335f;
        if (particle_work->opacity < 0) {
            particle_work->opacity = 0;
        }
        Hu3DModelTPLvlSet(object->mode, particle_work->opacity);
    }

    if (particle_work->active_model_callbacks == 0) {
        if (object->mode) {
            Hu3DModelAttrSet(object->mode, HU3D_ATTR_DISPOFF);
        }
        release_score_particle_pool_slot(particle_work->pool_slot_index);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void update_score_particle_layer_one(OMOBJ *object)
{
    s32 model_index;
    ScoreParticleWork *particle_work;
    ScoreParticleWork *parent_particle_work;
    particle_work = object->data;
    parent_particle_work = particle_work->owner_object->data;
    omSetTra(object, 0, 0, 0);
    for (model_index = 1; model_index < 3; model_index++) {
        Hu3DModelPosSet(object->mdlId[model_index], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->work[0] == 1) {
        release_score_particle_pool_slot(particle_work->pool_slot_index);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void update_score_particle_layer_two(OMOBJ *object)
{
    ScoreParticleWork *particle_index;
    particle_index = object->data;
    if (object->work[0] == 1) {
        release_score_particle_pool_slot(particle_index->pool_slot_index);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void update_score_particle_layer_three(OMOBJ *object)
{
    s32 model_index;
    ScoreParticleWork *particle_work;
    ScoreParticleWork *parent_particle_work;
    particle_work = object->data;
    parent_particle_work = particle_work->owner_object->data;
    omSetTra(object, 0, 0, 0);
    for (model_index = 1; model_index < 3; model_index++) {
        Hu3DModelPosSet(object->mdlId[model_index], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->work[1] == 1) {
        release_score_particle_pool_slot(particle_work->pool_slot_index);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void update_score_particle_layer_four(OMOBJ *object)
{
    s32 model_index;
    ScoreParticleWork *particle_work;
    ScoreParticleWork *parent_particle_work;
    particle_work = object->data;
    parent_particle_work = particle_work->owner_object->data;
    omSetTra(object, particle_work->owner_object->trans.x, particle_work->owner_object->trans.y, particle_work->owner_object->trans.z);
    for (model_index = 1; model_index < 3; model_index++) {
        Hu3DModelPosSet(object->mdlId[model_index], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->work[1] == 1) {
        release_score_particle_pool_slot(particle_work->pool_slot_index);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void update_score_particle_layer_five(OMOBJ *object)
{
    ScoreParticleWork *particle_index;
    particle_index = object->data;
    if (object->work[0] == 1) {
        release_score_particle_pool_slot(particle_index->pool_slot_index);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void update_score_particle_layer_six(OMOBJ *object)
{
    ScoreParticleWork *particle_index;
    particle_index = object->data;
    if (object->work[0] == 1) {
        release_score_particle_pool_slot(particle_index->pool_slot_index);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void update_score_particle_model(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float particle_alpha;
    float particle_height;
    float particle_angle_step;
    HU3DPARTICLEDATA *particle_data;
    s32 particle_index;
    ScoreParticleWork *active_particle_count;
    s32 particle_work;
    active_particle_count = ((OMOBJ *)(particle->work))->data;
    if (particle->count == 0) {
        particle_data = particle->data;
        particle_angle_step = 360.0f / (particle->maxCnt / 2);
        particle_alpha = particle->dataCnt;
        for (particle_index = 0; particle_index < particle->maxCnt / 2; particle_index++, particle_data++) {
            particle_height = (0.1f * (rand8() % 50)) + 50;
            particle_data->scale = (0.1f * (rand8() % 41)) + 8.0f;
            particle_data->vel.x = particle_alpha;
            particle_data->vel.y = particle_height;
            particle_data->vel.z = 0;
            particle_data->accel.x = (10.0f / 255.0f) * ((u8)frand());
            particle_data->color.a = 180;
            particle_alpha += particle_angle_step;
            particle_data->pos.z = 0;
        }
        for (particle_index = 0; particle_index < particle->maxCnt / 2; particle_index++, particle_data++) {
            particle_data->scale = 0;
            particle_data->color.a = 0;
        }
    }
    particle_data = particle->data;
    particle_work = 0;
    for (particle_index = 0; particle_index < particle->maxCnt / 2; particle_index++, particle_data++) {
        if (particle_data->color.a != 0) {
            particle_work++;
            particle_height = (6.0 * sind(particle_data->vel.z)) + particle_data->vel.y;
            particle_data->pos.x = particle_height * cosd(particle_data->vel.x);
            particle_data->pos.y = particle_height * sind(particle_data->vel.x);
            particle_data->vel.z += particle_data->accel.x;
            if (particle_data->vel.z >= 360.0f) {
                particle_data->vel.z -= 360.0f;
            }
            particle_alpha = particle_data->color.a;
            if (active_particle_count->fade_out_requested) {
                particle_alpha -= 3.0f;
                if (particle_alpha < 0.0f) {
                    particle_alpha = 0.0f;
                }
            }
            particle_data->color.a = particle_alpha;
        }
    }
    if (!particle_work) {
        active_particle_count->active_model_callbacks--;
    }
}

void update_score_particle_bonus_model(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float particle_alpha;
    HU3DPARTICLEDATA *particle_data;
    s32 particle_index;
    s32 active_particle_count;
    ScoreParticleWork *particle_work;
    if (!particle->emitCnt) {
        particle->emitCnt = 1;
        particle_data = particle->data;
        for (particle_index = 0; particle_index < particle->maxCnt / 2; particle_index++, particle_data++) {
            particle_data->vel.x = particle_data->pos.x;
            particle_data->accel.x = 0;
            particle_data->accel.y = 5.0f + ((35.0f / 255.0f) * ((u8)frand()));
            particle_data->accel.z = 8.0f + ((8.0f / 255.0f) * ((u8)frand()));
            particle_data->colorIdx = 3.0f + ((5.0f / 255.0f) * ((u8)frand()));
        }
    }
    particle_data = particle->data;
    active_particle_count = 0;
    for (particle_index = 0; particle_index < particle->maxCnt / 2; particle_index++, particle_data++) {
        if (particle_data->color.a != 0) {
            active_particle_count++;
            particle_data->pos.x = particle_data->vel.x + (particle_data->accel.z * sind(particle_data->accel.x));
            particle_data->accel.x += particle_data->accel.y;
            if (particle_data->accel.x >= 360.0f) {
                particle_data->accel.x -= 360.0f;
            }
            particle_data->pos.y += particle_data->colorIdx;
            particle_alpha = particle_data->color.a;
            particle_alpha -= 3.0f;
            if (particle_alpha < 0.0f) {
                particle_alpha = 0.0f;
            }
            particle_data->color.a = particle_alpha;
        }
    }
    if (active_particle_count == 0) {
        ScoreParticleWork *particle_work = ((OMOBJ *)(particle->work))->data;
        particle_work->active_model_callbacks--;
    }
}

// Here exclusively to match update_score_particle_model_visibility
static inline void preserve_particle_callback_match(s32 value)
{
    s32 temp1, temp2, temp3, temp4, temp5;
    if (value != 0) {
        temp1 = 1;
        temp2 = temp1 * 2;
        temp3 = temp2 * 3;
        temp4 = temp3 * 4;
        temp5 = temp4 * 5;
        temp5 = temp5 / 2;
    }
}

void update_score_particle_model_visibility(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    preserve_particle_callback_match(0);
}

void update_score_particle_model_motion(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    HU3DPARTICLEDATA *particle_data;
    s32 particle_index;
    s32 free_particle_index;
    if (particle->count == 0) {
        particle_data = particle->data;
        for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
            particle_data->color.a = 0;
            particle_data->scale = 0;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0) {
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle_data = particle->data;
            for (free_particle_index = 0; free_particle_index < particle->maxCnt; free_particle_index++, particle_data++) {
                if (particle_data->color.a == 0) {
                    break;
                }
            }
            if (free_particle_index == particle->maxCnt) {
                continue;
            }
            particle_data->vel.x = -50.0f + (0.3921569f * ((u8)frand()));
            particle_data->vel.y = 0.058823533f * ((u8)frand());
            particle_data->accel.x = (90.0f / 255.0f) * ((u8)frand());
            particle_data->accel.y = 5.0f + (0.098039225f * ((u8)frand()));
            particle_data->accel.z = (float)(frand() % 10) + 8.0f;
            particle_data->pos.z = -5.0f + ((11.0f / 255.0f) * ((u8)frand()));
            particle_data->pos.y = (float)(frand() % 31) + -5.0f;
            particle_data->scale = particle_data->vel.y + 35.0f;
            particle_data->color.a = 210;
            particle_data->vel.y = (0.2 * particle_data->vel.y) + 5.0;
            particle->dataCnt = (frand() % 10) + 10;
        }
    }
    else {
        particle->dataCnt--;
    }
    particle_data = particle->data;
    for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
        if (particle_data->color.a == 0) {
            continue;
        }
        particle_data->pos.x = (particle_data->accel.z * sind(particle_data->accel.x)) + particle_data->vel.x;
        particle_data->accel.x += particle_data->accel.y;
        if (particle_data->accel.x >= 360.0f) {
            particle_data->accel.x -= 360.0f;
        }
        particle_data->pos.y += particle_data->vel.y;
        particle_data->color.a--;
    }
}

void update_score_particle_sparkle(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    HU3DPARTICLEDATA *particle_data;
    s32 particle_index;
    M401WorkPlayer *player_work;
    OMOBJ *particle_object;
    s32 free_particle_index;
    s32 active_particle_count;
    ScoreParticleWork *particle_work;
    particle_object = particle->work;
    particle_work = ((OMOBJ *)(particle->work))->data;
    player_work = particle_work->owner_object->data;
    if (particle->count == 0) {
        particle_data = particle->data;
        for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
            particle_data->color.a = 0;
            particle_data->scale = 0;
            particle_data->speedDecay = 0;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0 && particle_object->work[0] == 0) {
        for (particle_index = 0; particle_index < 10; particle_index++) {
            particle_data = particle->data;
            for (free_particle_index = 0; free_particle_index < particle->maxCnt; free_particle_index++, particle_data++) {
                if (particle_data->speedDecay == 0) {
                    break;
                }
            }
            if (free_particle_index == particle->maxCnt) {
                continue;
            }
            particle_data->vel.x = (((40.0f / 255.0f) * ((u8)frand())) + (player_work->effect_anchor_position.x - 20.0f));
            particle_data->vel.y = (frand() % 5) + 3;
            particle_data->accel.x = ((90.0f / 255.0f) * ((u8)frand()));
            particle_data->accel.y = 5.0f + ((45.0f / 255.0f) * ((u8)frand()));
            particle_data->accel.z = 2.0f + (0.011764707f * ((u8)frand()));
            particle_data->color.a = 180;
            particle_data->pos.z = ((0.121568635f * ((u8)frand())) + (player_work->effect_anchor_position.z + 70.0f));
            particle_data->pos.y = ((0.20000002f * ((u8)frand())) + (player_work->effect_anchor_position.y - 25.0f));
            particle->dataCnt = (frand() % 6) + 5;
            particle_data->speedDecay = 1;
            particle_data->scale = 11;
        }
    }
    else {
        particle->dataCnt--;
    }
    particle_data = particle->data;
    active_particle_count = 0;
    for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
        if (particle_data->color.a != 0) {
            float remaining_alpha;
            particle_data->pos.x = (particle_data->accel.z * sind(particle_data->accel.x)) + particle_data->vel.x;
            particle_data->accel.x += particle_data->accel.y;
            if (particle_data->accel.x >= 360.0f) {
                particle_data->accel.x -= 360.0f;
            }
            particle_data->pos.y += 3.0f;
            remaining_alpha = particle_data->color.a;
            remaining_alpha -= particle_data->vel.y;
            if (remaining_alpha < 0.0f) {
                remaining_alpha = 0.0f;
                particle_data->speedDecay = 0;
            }

            particle_data->color.a = remaining_alpha;
            active_particle_count++;
        }
    }
    if (active_particle_count == 0 && particle_object->work[0] == 1) {
        particle_object->work[1] = 1;
    }
}

void update_score_particle_trail(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    HU3DPARTICLEDATA *particle_data;
    s32 particle_index;
    M401WorkPlayer *player_work;
    OMOBJ *particle_object;
    s32 free_particle_index;
    s32 active_particle_count;
    ScoreParticleWork *particle_work;
    particle_object = particle->work;
    particle_work = (particle_object)->data;
    player_work = particle_work->owner_object->data;
    if (particle->count == 0) {
        particle_data = particle->data;
        for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
            particle_data->color.a = 0;
            particle_data->scale = 0;
            particle_data->speedDecay = 0;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0 && particle_object->work[0] == 0) {
        for (particle_index = 0; particle_index < 10; particle_index++) {
            particle_data = particle->data;
            for (free_particle_index = 0; free_particle_index < particle->maxCnt; free_particle_index++, particle_data++) {
                if (particle_data->speedDecay == 0) {
                    break;
                }
            }
            if (free_particle_index == particle->maxCnt) {
                continue;
            }
            particle_data->vel.x = (((80.0f / 255.0f) * ((u8)frand())) + (-40.0f));
            particle_data->vel.y = (frand() % 10) + 7;
            particle_data->accel.x = ((90.0f / 255.0f) * ((u8)frand()));
            particle_data->accel.y = 5.0f + ((45.0f / 255.0f) * ((u8)frand()));
            particle_data->accel.z = 2.0f + (frand() % 3);
            particle_data->color.a = 180;
            particle_data->pos.z = ((0.121568635f * ((u8)frand())) + (85.0f));
            particle_data->pos.y = ((0.2392157f * ((u8)frand())) + (-30.0f));
            particle->dataCnt = (frand() % 3) + 3;
            particle_data->speedDecay = 1;
            particle_data->scale = 11;
        }
    }
    else {
        particle->dataCnt--;
    }
    particle_data = particle->data;
    active_particle_count = 0;
    for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
        if (particle_data->color.a != 0) {
            float remaining_alpha;
            particle_data->pos.x = (particle_data->accel.z * sind(particle_data->accel.x)) + particle_data->vel.x;
            particle_data->accel.x += particle_data->accel.y;
            if (particle_data->accel.x >= 360.0f) {
                particle_data->accel.x -= 360.0f;
            }
            particle_data->pos.y += 3.0f;
            particle_data->pos.z -= 1.0f;
            remaining_alpha = particle_data->color.a;
            remaining_alpha -= particle_data->vel.y;
            if (remaining_alpha < 0.0f) {
                remaining_alpha = 0.0f;
                particle_data->speedDecay = 0;
            }

            particle_data->color.a = remaining_alpha;
            active_particle_count++;
        }
    }
    if (active_particle_count == 0 && particle_object->work[0] == 1) {
        particle_object->work[1] = 1;
    }
}

void update_score_particle_burst(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float particle_lifetime;
    float horizontal_angle;
    float launch_speed;
    float vertical_angle;
    HU3DPARTICLEDATA *particle_data;
    s32 particle_index;
    s32 free_particle_index;
    if (particle->count == 0) {
        particle_data = particle->data;
        for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
            particle_data->scale = 0;
        }
        particle->work = (void *)1;
        particle->emitCnt = 0;
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0) {
        for (particle_index = 0; particle_index < 16; particle_index++) {
            particle_data = particle->data;
            for (free_particle_index = 0; free_particle_index < particle->maxCnt; free_particle_index++, particle_data++) {
                if (particle_data->scale == 0) {
                    break;
                }
            }
            if (free_particle_index == particle->maxCnt) {
                continue;
            }
            horizontal_angle = (360.0f / 255.0f) * ((u8)frand());
            particle_data->speedDecay = 45 * sind(horizontal_angle);
            particle_data->scaleBase = 45 * cosd(horizontal_angle);
            particle_data->colorIdx = 0;
            vertical_angle = 0.098039225f * ((u8)frand()) + 50.0f;
            launch_speed = (2.0f / 255.0f) * ((u8)frand()) + 2.5f;
            particle_data->vel.x = launch_speed * sind(horizontal_angle) * cosd(vertical_angle);
            particle_data->vel.y = 0.8f * (launch_speed * sind(vertical_angle));
            particle_data->vel.z = launch_speed * cosd(horizontal_angle) * cosd(vertical_angle);
            particle_data->accel.x = 1;
            particle_data->accel.y = 255;
            particle_data->scale = (4.0f / 255.0f) * ((u8)frand()) + 3.0f;
            particle_data->color.r = (155.0f / 255.0f) * ((u8)frand()) + 100.0f;
            particle_data->color.g = 0.21568629f * ((u8)frand()) + 200.0f;
            particle_data->color.b = 255;
            particle_data->color.a = particle_data->accel.y;
        }
        particle->dataCnt = 0.058823533f * ((u8)frand()) + 30.0f;
    }
    else {
        particle->dataCnt--;
    }
    particle_data = particle->data;
    for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
        if (particle_data->scale != 0) {
            particle_lifetime = particle_data->accel.x;
            particle_data->pos.x = (particle_data->vel.x * particle_lifetime) + particle_data->speedDecay;
            particle_data->pos.z = (particle_data->vel.z * particle_lifetime) + particle_data->scaleBase;
            particle_data->pos.y = ((particle_data->vel.y * particle_lifetime) + particle_data->colorIdx) - (0.2 * particle_lifetime * particle_lifetime);
            particle_data->accel.y -= 3.5f;
            particle_data->color.a = particle_data->accel.y;
            if (particle_data->scale < 0 || particle_data->accel.y < 10.0f || particle_data->pos.y <= 0.0f) {
                particle_data->scale = 0;
                particle->emitCnt++;
            }

            particle_data->accel.x += 0.7f;
        }
    }
}

void update_score_particle_fade(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float particle_lifetime;
    float horizontal_angle;
    float launch_speed;
    float vertical_angle;
    HU3DPARTICLEDATA *particle_data;
    s32 particle_index;
    s32 free_particle_index;
    if (particle->count == 0) {
        particle_data = particle->data;
        for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
            particle_data->scale = 0;
        }
        particle->work = (void *)1;
        particle->emitCnt = 0;
        particle->dataCnt = 0;
    }
    if (particle->work) {
        for (particle_index = 0; particle_index < 20; particle_index++) {
            particle_data = particle->data;
            for (free_particle_index = 0; free_particle_index < particle->maxCnt; free_particle_index++, particle_data++) {
                if (particle_data->scale == 0) {
                    break;
                }
            }
            if (free_particle_index != particle->maxCnt) {
                horizontal_angle = (360.0f / 255.0f) * ((u8)frand());
                particle_data->speedDecay = 40 * sind(horizontal_angle);
                particle_data->scaleBase = 40 * cosd(horizontal_angle);
                particle_data->colorIdx = 0;
                vertical_angle = (20.0f / 255.0f) * ((u8)frand()) + 70.0f;
                launch_speed = (4.0f / 255.0f) * ((u8)frand()) + 5.0f;
                particle_data->vel.x = launch_speed * sind(horizontal_angle) * cosd(vertical_angle);
                particle_data->vel.y = launch_speed * sind(vertical_angle);
                particle_data->vel.z = launch_speed * cosd(horizontal_angle) * cosd(vertical_angle);
                particle_data->accel.x = 1;
                particle_data->accel.y = 255;
                particle_data->scale = (4.0f / 255.0f) * ((u8)frand()) + 5.0f;
                particle_data->color.r = (155.0f / 255.0f) * ((u8)frand()) + 100.0f;
                particle_data->color.g = 0.21568629f * ((u8)frand()) + 200.0f;
                particle_data->color.b = 255;
                particle_data->color.a = particle_data->accel.y;
            }
            else {
                particle->work = NULL;
                break;
            }
        }
    }
    particle_data = particle->data;
    for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
        if (particle_data->scale != 0) {
            particle_lifetime = particle_data->accel.x;
            particle_data->pos.x = (particle_data->vel.x * particle_lifetime) + particle_data->speedDecay;
            particle_data->pos.z = (particle_data->vel.z * particle_lifetime) + particle_data->scaleBase;
            particle_data->pos.y = ((particle_data->vel.y * particle_lifetime) + particle_data->colorIdx) - (0.2 * particle_lifetime * particle_lifetime);
            particle_data->accel.y -= 3.5f;
            particle_data->color.a = particle_data->accel.y;
            if (particle_data->scale < 0 || particle_data->accel.y < 10.0f || particle_data->pos.y <= 0.0f) {
                particle_data->scale = 0;
                particle->emitCnt++;
            }
            particle_data->accel.x += 1.0f;
        }
    }
    if (particle->emitCnt >= particle->maxCnt && particle->work == NULL) {
        particle->dataCnt = 1;
    }
}

void empty_score_particle_callback(OMOBJ *object);
void update_score_particle_display_model(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);

OMOBJ *create_particle_effect_controller(void)
{
    OMOBJ *object = omAddObjEx(HuPrcCurrentGet(), 1300, 5, 0, -1, empty_score_particle_callback);
    HU3DPARTICLE *particle;
    omSetStatBit(object, 0x100);
    object->mdlId[0] = Hu3DParticleCreate(score_particle_bonus_animation, 200);
    Hu3DParticleHookSet(object->mdlId[0], update_score_particle_display_model);
    Hu3DParticleColSet(object->mdlId[0], 255, 255, 255);
    Hu3DModelPosSet(object->mdlId[0], 0, 0, 0);
    Hu3DParticleAnimModeSet(object->mdlId[0], 0);
    Hu3DModelLayerSet(object->mdlId[0], 1);
    Hu3DParticleBlendModeSet(object->mdlId[0], 1);
    particle = Hu3DData[object->mdlId[0]].hookData;
    return object;
}

void empty_score_particle_callback(OMOBJ *object) { }

void update_score_particle_display_model(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    HU3DPARTICLEDATA *particle_data;
    s32 particle_index;
    s32 free_particle_index;
    if (particle->count == 0) {
        particle_data = particle->data;
        for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
            particle_data->scale = 0;
            particle_data->pos.y = 950;
        }
    }
    if (particle->dataCnt == 0) {
        for (particle_index = 0; particle_index < 30; particle_index++) {
            particle_data = particle->data;
            for (free_particle_index = 0; free_particle_index < particle->maxCnt; free_particle_index++, particle_data++) {
                if (particle_data->scale == 0) {
                    break;
                }
            }
            if (free_particle_index == particle->maxCnt) {
                continue;
            }
            particle_data->scale = 1;
            particle_data->color.a = 150;
            particle_data->pos.x = ((11.764707f * ((u8)frand())) + (-1500.0f));
            particle_data->pos.z = ((6.666667f * ((u8)frand())) + (-2000.0f));
            particle_data->vel.x = 0;
            particle_data->vel.y = (((5.0f / 255.0f) * ((u8)frand())) + (5.0f));
            particle_data->vel.z = ((0.011764707f * ((u8)frand())) + (18.0f));
        }
        particle->dataCnt = (frand() % 5) + 4;
    }
    else {
        particle->dataCnt--;
    }
    particle_data = particle->data;
    for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
        if (particle_data->scale != 0) {
            particle_data->pos.x += 1.1f;
            particle_data->pos.z += 1.1f;
            particle_data->scale = (particle_data->vel.z * sind(particle_data->vel.x)) + 1.0;
            particle_data->vel.x += particle_data->vel.y;
            if (particle_data->vel.x >= 180.0f) {
                particle_data->scale = 0.0f;
            }
        }
    }
}

void update_score_particle_display(OMOBJ *object);
void update_score_particle_display_model_motion(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);

OMOBJ *create_particle_model_manager(HUPROCESS *objman)
{
    OMOBJ *object;
    object = omAddObjEx(objman, 1300, 1, 0, -1, update_score_particle_display);
    object->mdlId[0] = Hu3DParticleCreate(score_particle_animation_a, 450);
    Hu3DParticleHookSet(object->mdlId[0], update_score_particle_display_model_motion);
    Hu3DParticleColSet(object->mdlId[0], 255, 255, 255);
    Hu3DModelPosSet(object->mdlId[0], 0, -6000, -21000);
    Hu3DParticleAnimModeSet(object->mdlId[0], 0);
    Hu3DModelLayerSet(object->mdlId[0], 1);
    Hu3DParticleBlendModeSet(object->mdlId[0], 1);
    return object;
}

void update_score_particle_display(OMOBJ *object)
{
    omSetTra(object, camera_position.x, camera_position.y, camera_position.z);
    if (object->work[0] == 1) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void update_score_particle_display_model_motion(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float remaining_alpha;
    float particle_angle;
    HU3DPARTICLEDATA *particle_data;
    s32 particle_index;
    s32 free_particle_index;
    if (particle->count == 0) {
        particle_data = particle->data;
        for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
            particle_data->color.a = 180;
            particle_data->vel.x = ((3.9215689f * ((u8)frand())) + (-500.0f));
            particle_data->vel.y = ((3.529412f * ((u8)frand())) + (-500.0f));
            particle_data->vel.z = (-300.0f) - ((3.9215689f * ((u8)frand())));
            particle_data->accel.x = (360.0f / 255.0f) * ((u8)frand());
            particle_data->accel.y = (4.0f / 255.0f) * ((u8)frand());
            particle_data->scale = 2;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0) {
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle_data = particle->data;
            for (free_particle_index = 0; free_particle_index < particle->maxCnt; free_particle_index++, particle_data++) {
                if (particle_data->color.a == 0) {
                    break;
                }
            }
            if (free_particle_index == particle->maxCnt) {
                continue;
            }
            particle_data->color.a = 180;
            particle_data->vel.x = -50.0f + (0.3921569f * ((u8)frand()));
            particle_data->vel.y = 0.058823533f * ((u8)frand());
            particle_data->accel.x = (90.0f / 255.0f) * ((u8)frand());
            particle_data->accel.y = 5.0f + (0.098039225f * ((u8)frand()));
            particle_data->accel.z = (float)(frand() % 10) + 8.0f;
            particle_data->pos.z = -5.0f + ((11.0f / 255.0f) * ((u8)frand()));
            particle_data->pos.y = (float)(frand() % 31) + -5.0f;
            particle_data->scale = particle_data->vel.y + 35.0f;
            particle_data->color.a = 210;
            particle_data->vel.y = (0.2 * particle_data->vel.y) + 5.0;
            particle->dataCnt = (frand() % 10) + 10;
        }
    }
    else {
        particle->dataCnt--;
    }
    particle_data = particle->data;
    particle_angle = camera_move_distance * 0.3f;
    for (particle_index = 0; particle_index < particle->maxCnt; particle_index++, particle_data++) {
        if (particle_data->color.a == 0) {
            continue;
        }
        particle_data->pos.x = particle_data->vel.x;
        particle_data->pos.y = particle_data->vel.y;
        particle_data->pos.z = particle_data->vel.z;
        particle_data->vel.x -= 0.5 * sind(particle_data->accel.x);
        particle_data->vel.z -= -particle_angle;
        particle_data->accel.x += particle_data->accel.y;
        if (particle_data->accel.x >= 360.0f) {
            particle_data->accel.x -= 360.0f;
        }
        if (particle_data->vel.z >= 0.0f) {
            remaining_alpha = 800.0f + ((300.0f / 255.0f) * ((u8)frand()));
            particle_data->vel.z -= remaining_alpha;
        }
    }
}

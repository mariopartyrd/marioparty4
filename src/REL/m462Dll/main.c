#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06[8];
    /* 0x16 */ s16 unk16[4];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ char unk38[4];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ char unk40[4];
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ Vec unk4C;
    /* 0x58 */ float unk58;
    /* 0x5C */ float unk5C;
    /* 0x60 */ Vec unk60;
    /* 0x6C */ float unk6C;
    /* 0x70 */ float unk70;
    /* 0x74 */ float unk74;
    /* 0x78 */ Vec unk78;
    /* 0x84 */ float unk84;
    /* 0x88 */ float unk88;
    /* 0x8C */ float unk8C;
    /* 0x90 */ float unk90;
    /* 0x94 */ float unk94;
} StructBss340; // Size 0x98

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04[3];
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ Vec unk14;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ float unk44;
} StructBss70; // Size 0x48

void fn_1_4A0(void);
float fn_1_14B4(float arg0);
void fn_1_174C(void);
void fn_1_17A0(s32 arg0, s32 arg1);
void fn_1_44D8(void);
void fn_1_4BC4(void);
void fn_1_69C0(void);
void fn_1_7D40(void);
void fn_1_545C(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_594C(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_5DE4(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_7DA0(void);
s32 fn_1_1880(float arg0, float arg1, float arg2, s32 arg3, s32 arg4);

s16 lbl_1_bss_3EA;
s16 lbl_1_bss_3E8;
s32 lbl_1_bss_3E4;
s32 lbl_1_bss_3E0;
s32 lbl_1_bss_3DC;
s32 lbl_1_bss_3D8;
StructBss340 lbl_1_bss_340[1];
StructBss70 lbl_1_bss_70[10];
StructBss70 lbl_1_bss_28;
omObjData *lbl_1_bss_24;
Vec lbl_1_bss_18;
Vec lbl_1_bss_C;
Vec lbl_1_bss_0;

s32 lbl_1_data_0[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

s32 lbl_1_data_20[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MARIOMOT, 27), DATA_MAKE_NUM(DATADIR_MARIOMOT, 75),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 22) };

Vec lbl_1_data_30[] = { { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f },
    { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f } };

Vec lbl_1_data_90[] = { { -900.0f, 143.0f, -1020.0f }, { -677.0f, 143.0f, -1020.0f }, { 900.0f, 0.0f, -1150.0f }, { -307.0f, 182.0f, -1575.0f } };

s32 lbl_1_data_C0[][5] = { { 50, 80, 90, 95, 100 }, { 5, 55, 85, 95, 100 }, { 0, 5, 55, 90, 100 } };

float lbl_1_data_FC[] = { 0.3f, 0.5f, 0.7f, 0.9f, 1.0f };

void ObjectSetup(void)
{
    Process *temp_r3;

    temp_r3 = omInitObjMan(50, 0x2000);
    omGameSysInit(temp_r3);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    lbl_1_bss_24 = omAddObjEx(temp_r3, 0x7FDA, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_24->work[0] = 1;
    CRotM->x = -26.0f;
    CRotM->y = 0.0f;
    CRotM->z = 0.0f;
    CenterM->x = 0.0f;
    CenterM->y = 0.0f;
    CenterM->z = -295.0f;
    CZoomM[0] = 3030.0f;
    Hu3DLighInit();
    lbl_1_bss_3EA = Hu3DGLightCreate(10000.0f, 0.0f, 10000.0f, -1.0f, 0.0f, -1.0f, 255, 50, 0);
    Hu3DGLightPosAimSet(lbl_1_bss_3EA, -2500.0f, 3535.5f, 2500.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(lbl_1_bss_3EA);
    lbl_1_bss_18.x = -2500.0f;
    lbl_1_bss_18.y = 3535.5f;
    lbl_1_bss_18.z = 2500.0f;
    lbl_1_bss_C.x = lbl_1_bss_C.z = 0.0f;
    lbl_1_bss_C.y = 1.0f;
    lbl_1_bss_0.x = 0.0f;
    lbl_1_bss_0.y = 0.0f;
    lbl_1_bss_0.z = 0.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_bss_18, &lbl_1_bss_C, &lbl_1_bss_0);
    Hu3DBGColorSet(0, 0, 0);
    fn_1_4A0();
    HuPrcChildCreate(fn_1_7DA0, 0x1000, 0x2000, 0, HuPrcCurrentGet());
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
}

void fn_1_4A0(void)
{
    float temp_f31;
    float temp_f30;
    void *var_r27;
    StructBss340 *temp_r31;
    StructBss70 *temp_r29;
    Process *var_r25;
    AnimData *var_r24;
    AnimData *spC[4];
    s16 var_r30;
    s16 var_r23;
    s16 sp8;
    s32 i;
    s32 j;

    lbl_1_bss_3E0 = 0;
    lbl_1_bss_3D8 = 0;
    HuAudSndGrpSet(0x2C);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 0), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r27);
    lbl_1_bss_3E8 = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelShadowMapSet(var_r30);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    i = 0;
    temp_r31 = &lbl_1_bss_340[i];
    temp_r31->unk20 = i;
    temp_r31->unk24 = i;
    temp_r31->unk28 = GWPlayerCfg[i].pad_idx;
    temp_r31->unk02 = CharModelCreate(lbl_1_data_0[GWPlayerCfg[i].character], 2);
    Hu3DModelLayerSet(temp_r31->unk00, 1);
    CharModelLayerSetAll(2);
    temp_r31->unk78.x = lbl_1_data_30[GWPlayerCfg[i].character].x;
    temp_r31->unk78.y = lbl_1_data_30[GWPlayerCfg[i].character].y;
    temp_r31->unk78.z = lbl_1_data_30[GWPlayerCfg[i].character].z;
    Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk78.x, temp_r31->unk78.y, temp_r31->unk78.z);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 1), MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r31->unk00 = Hu3DModelCreate(var_r27);
    Hu3DModelLayerSet(temp_r31->unk00, 1);
    temp_r31->unk60.x = temp_r31->unk60.z = 0.0f;
    temp_r31->unk60.y = 180.0f;
    temp_r31->unk4C.x = 0.0f;
    temp_r31->unk4C.y = 0.0f;
    temp_r31->unk4C.z = 0.0f;
    temp_r31->unk60.y = fn_1_14B4(temp_r31->unk60.y + 180.0f);
    temp_r31->unk94 = temp_r31->unk60.y;
    temp_r31->unk84 = 200.0f;
    temp_r31->unk88 = 6.75f;
    temp_r31->unk8C = 1.0f;
    temp_r31->unk90 = 1.0f;
    Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
    Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk60.x, temp_r31->unk60.y, temp_r31->unk60.z);
    Hu3DModelShadowSet(temp_r31->unk00);
    Hu3DModelHookSet(temp_r31->unk00, "itemhook_c", temp_r31->unk02);
    for (j = 0; j < 4; j++) {
        temp_r31->unk16[j] = CharModelMotionCreate(lbl_1_data_0[GWPlayerCfg[i].character], lbl_1_data_20[j]);
    }
    CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[i].character], temp_r31->unk16[0]);
    CharModelMotionTimeSet(lbl_1_data_0[GWPlayerCfg[i].character], 60.0f);
    CharModelVoiceEnableSet(lbl_1_data_0[GWPlayerCfg[i].character], temp_r31->unk16[2], 0);
    for (j = 0; j < 8; j++) {
        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 2 + j), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk06[j] = Hu3DJointMotion(temp_r31->unk00, var_r27);
    }
    Hu3DMotionSet(temp_r31->unk00, temp_r31->unk06[0]);
    Hu3DMotionShiftSpeedSet(temp_r31->unk00, 1.0f);
    Hu3DMotionSpeedSet(temp_r31->unk00, 1.0f);
    Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_LOOP);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 10), MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r31->unk04 = Hu3DModelCreate(var_r27);
    Hu3DModelLayerSet(temp_r31->unk04, 1);
    Hu3DModelAttrSet(temp_r31->unk04, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r31->unk04, HU3D_MOTATTR_PAUSE);
    CharModelMotionDataClose(lbl_1_data_0[GWPlayerCfg[i].character]);
    var_r25 = HuPrcChildCreate(fn_1_69C0, 0x2000, 0x3000, 0, HuPrcCurrentGet());
    var_r25->user_data = temp_r31;
    var_r24 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 2), MEMORY_DEFAULT_NUM));
    var_r30 = Hu3DParticleCreate(var_r24, 50);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r30, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r30, 3);
    Hu3DParticleColSet(var_r30, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r30, 0.0f);
    Hu3DParticleHookSet(var_r30, fn_1_545C);
    var_r24 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 2), MEMORY_DEFAULT_NUM));
    var_r30 = Hu3DParticleCreate(var_r24, 50);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r30, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r30, 3);
    Hu3DParticleColSet(var_r30, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r30, 0.0f);
    Hu3DParticleHookSet(var_r30, fn_1_594C);
    var_r24 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 2), MEMORY_DEFAULT_NUM));
    var_r30 = Hu3DParticleCreate(var_r24, 50);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r30, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r30, 3);
    Hu3DParticleColSet(var_r30, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r30, 0.0f);
    Hu3DParticleHookSet(var_r30, fn_1_5DE4);
    HuDataDirClose(DATADIR_EFFECT);
    for (i = 0; i < 10; i++) {
        temp_r29 = &lbl_1_bss_70[i];
        temp_r29->unk30 = 50.0f;
        do {
            temp_f31 = 1380.0f * frandf() - 690.0f;
            temp_f30 = 1380.0f * frandf() - 690.0f;
        } while (fn_1_1880(temp_f31, temp_f30, 50.0f, i, -1) != 0);
        temp_r29->unk24 = temp_f31;
        temp_r29->unk14.x = temp_f31;
        temp_r29->unk14.y = 0.0f;
        temp_r29->unk28 = temp_f30;
        temp_r29->unk14.z = temp_f30;
    }
    for (i = 0; i < 10; i++) {
        temp_r29 = &lbl_1_bss_70[i];
        if (i == 0) {
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 12), MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r30 = Hu3DModelCreate(var_r27);
            var_r23 = var_r30;
        }
        else {
            var_r30 = Hu3DModelLink(var_r23);
        }
        temp_r29->unk00 = var_r30;
        temp_r29->unk0C = i;
        temp_r29->unk30 = 50.0f;
        temp_r29->unk10 = 0;
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DModelShadowSet(var_r30);
        Hu3DModelPosSet(var_r30, temp_r29->unk14.x, temp_r29->unk14.y, temp_r29->unk14.z);
        temp_r29->unk20 = 0.0f;
        temp_r29->unk34 = 6.75f * lbl_1_data_FC[0];
        for (j = 0; j < 3; j++) {
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 13 + j), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r29->unk04[j] = Hu3DJointMotion(var_r30, var_r27);
        }
        Hu3DMotionSet(var_r30, temp_r29->unk04[1]);
        Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 11), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r27);
        sp8 = var_r30;
        temp_r29->unk02 = var_r30;
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(var_r30, 3);
        var_r25 = HuPrcChildCreate(fn_1_4BC4, 0x1000, 0x3000, 0, HuPrcCurrentGet());
        var_r25->user_data = temp_r29;
    }
    for (i = 0; i < 2; i++) {
        var_r30 = Hu3DModelLink(var_r23);
        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 16), MEMORY_DEFAULT_NUM, HEAP_DATA);
        Hu3DMotionSet(var_r30, Hu3DJointMotion(var_r30, var_r27));
        Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
        Hu3DModelShadowSet(var_r30);
        Hu3DModelPosSet(var_r30, lbl_1_data_90[i].x, lbl_1_data_90[i].y, lbl_1_data_90[i].z);
        if (i != 0) {
            Hu3DMotionTimeSet(var_r30, Hu3DMotionMaxTimeGet(var_r30) / 2.0f);
        }
    }
    var_r30 = Hu3DModelLink(var_r23);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 19), MEMORY_DEFAULT_NUM, HEAP_DATA);
    Hu3DMotionSet(var_r30, Hu3DJointMotion(var_r30, var_r27));
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r30);
    Hu3DModelPosSet(var_r30, lbl_1_data_90[3].x, lbl_1_data_90[3].y, lbl_1_data_90[3].z);
    Hu3DMotionSpeedSet(var_r30, 0.7f);
    temp_r29 = &lbl_1_bss_28;
    var_r30 = Hu3DModelLink(var_r23);
    temp_r29->unk00 = var_r30;
    for (j = 0; j < 2; j++) {
        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M462, 17 + j), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r29->unk04[j] = Hu3DJointMotion(var_r30, var_r27);
    }
    Hu3DMotionSet(var_r30, temp_r29->unk04[0]);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r30);
    temp_r29->unk14.x = lbl_1_data_90[2].x;
    temp_r29->unk14.y = lbl_1_data_90[2].y;
    temp_r29->unk14.z = lbl_1_data_90[2].z;
    Hu3DModelPosSet(var_r30, temp_r29->unk14.x, temp_r29->unk14.y, temp_r29->unk14.z);
    var_r25 = HuPrcChildCreate(fn_1_44D8, 0x1000, 0x2000, 0, HuPrcCurrentGet());
    var_r25->user_data = temp_r29;
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 44), MEMORY_DEFAULT_NUM, HEAP_DATA);
    spC[0] = HuSprAnimRead(var_r27);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 55), MEMORY_DEFAULT_NUM, HEAP_DATA);
    spC[1] = HuSprAnimRead(var_r27);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 48), MEMORY_DEFAULT_NUM, HEAP_DATA);
    spC[2] = HuSprAnimRead(var_r27);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 49), MEMORY_DEFAULT_NUM, HEAP_DATA);
    spC[3] = HuSprAnimRead(var_r27);
    lbl_1_bss_3DC = HuSprGrpCreate(6);
    var_r30 = HuSprCreate(spC[0], 0x4000, 0);
    HuSprGrpMemberSet(lbl_1_bss_3DC, 0, var_r30);
    HuSprPosSet(lbl_1_bss_3DC, 0, 0.0f, 0.0f);
    HuSprTPLvlSet(lbl_1_bss_3DC, 0, 0.5f);
    HuSprColorSet(lbl_1_bss_3DC, 0, 0, 0, 0);
    var_r30 = HuSprCreate(spC[1], 0x4000, 0);
    HuSprGrpMemberSet(lbl_1_bss_3DC, 1, var_r30);
    HuSprPosSet(lbl_1_bss_3DC, 1, -19.0f, -9.0f);
    var_r30 = HuSprCreate(spC[2], 0x4000, 0);
    HuSprGrpMemberSet(lbl_1_bss_3DC, 2, var_r30);
    HuSprPosSet(lbl_1_bss_3DC, 2, 20.0f, -8.0f);
    var_r30 = HuSprCreate(spC[2], 0x4000, 0);
    HuSprGrpMemberSet(lbl_1_bss_3DC, 3, var_r30);
    HuSprPosSet(lbl_1_bss_3DC, 3, 2.0f, -8.0f);
    var_r30 = HuSprCreate(spC[3], 0x4000, 0);
    HuSprGrpMemberSet(lbl_1_bss_3DC, 4, var_r30);
    HuSprPosSet(lbl_1_bss_3DC, 4, 20.0f, 8.0f);
    var_r30 = HuSprCreate(spC[3], 0x4000, 0);
    HuSprGrpMemberSet(lbl_1_bss_3DC, 5, var_r30);
    HuSprPosSet(lbl_1_bss_3DC, 5, 2.0f, 8.0f);
    HuSprGrpPosSet(lbl_1_bss_3DC, 511.0f, 61.0f);
    fn_1_17A0(lbl_1_bss_3D8, 0);
    fn_1_17A0(GWMGRecordGet(14), 1);
    fn_1_174C();
    HuPrcChildCreate(fn_1_7D40, 0x1000, 0x1000, 0, HuPrcCurrentGet());
}

float fn_1_14B4(float arg0)
{
    while (arg0 >= 360.0f || arg0 < 0.0f) {
        if (arg0 >= 360.0f) {
            arg0 -= 360.0f;
        }
        if (arg0 < 0.0f) {
            arg0 += 360.0f;
        }
    }
    return arg0;
}

float fn_1_1534(float arg0, float arg1)
{
    float var_f31;

    if (arg0 > 750.0f - arg1) {
        var_f31 = 750.0f;
    }
    else if (arg0 < -(750.0f - arg1)) {
        var_f31 = 750.0f;
    }
    else {
        var_f31 = 750.0f;
    }
    return var_f31;
}

float fn_1_15B4(float arg0, float arg1)
{
    return fn_1_1534(arg0, arg1);
}

void fn_1_1634(void)
{
    float var_f31;
    float temp_f30;
    s32 i;

    var_f31 = 0.0f;
    while (TRUE) {
        var_f31 += 16.0f;
        temp_f30 = 1.0 + 0.2f * sind(var_f31);
        for (i = 0; i < 3; i++) {
            HuSprScaleSet(lbl_1_bss_3DC, i + 1, temp_f30, temp_f30);
        }
        HuPrcVSleep();
    }
}

void fn_1_16F8(void)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        HuSprAttrReset(lbl_1_bss_3DC, i, HUSPR_ATTR_DISPOFF);
    }
}

void fn_1_174C(void)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        HuSprAttrSet(lbl_1_bss_3DC, i, HUSPR_ATTR_DISPOFF);
    }
}

void fn_1_17A0(s32 arg0, s32 arg1)
{
    s32 var_r31;

    if (arg1 != 0) {
        var_r31 = 2;
    }
    else {
        var_r31 = 4;
    }
    HuSprBankSet(lbl_1_bss_3DC, var_r31, arg0 % 10);
    HuSprBankSet(lbl_1_bss_3DC, var_r31 + 1, arg0 / 10);
    HuSprAttrReset(lbl_1_bss_3DC, var_r31 + 1, HUSPR_ATTR_DISPOFF);
}

s32 fn_1_1880(float arg0, float arg1, float arg2, s32 arg3, s32 arg4)
{
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    s32 i;
    StructBss70 *temp_r30;
    StructBss340 *var_r29;

    if (arg3 > 10) {
        arg3 = 10;
    }
    HuSetVecF(&sp34, arg0, 0.0, arg1);
    for (i = 0; i < arg3; i++) {
        if (arg4 == i) {
            continue;
        }
        temp_r30 = &lbl_1_bss_70[i];
        HuSetVecF(&sp28, temp_r30->unk14.x, 0.0, temp_r30->unk14.z);
        HuSubVecF(&sp1C, &sp34, &sp28);
        if (VECMagXZ(&sp1C) < temp_r30->unk30 + arg2) {
            break;
        }
    }
    if (i < arg3) {
        return 1;
    }
    var_r29 = &lbl_1_bss_340[0];
    HuSetVecF(&sp28, var_r29->unk4C.x, 0.0, var_r29->unk4C.z);
    HuSubVecF(&sp1C, &sp34, &sp28);
    if (VECMagXZ(&sp1C) < var_r29->unk84 + arg2) {
        return 1;
    }
    return 0;
}

s32 fn_1_1BD4(StructBss70 *arg0)
{
    float var_f31;
    float var_f30;
    s32 var_r31;

    var_r31 = 0;
    var_f31 = fn_1_1534(arg0->unk14.z, arg0->unk30);
    var_f30 = fn_1_1534(arg0->unk14.x, arg0->unk30);
    if (arg0->unk14.x > var_f31 - arg0->unk30) {
        var_r31 = 1;
        arg0->unk14.x = var_f31 - arg0->unk30;
    }
    if (arg0->unk14.x < -(var_f31 - arg0->unk30)) {
        var_r31 = 1;
        arg0->unk14.x = -(var_f31 - arg0->unk30);
    }
    if (arg0->unk14.z > var_f30 - arg0->unk30) {
        var_r31 = 1;
        arg0->unk14.z = var_f30 - arg0->unk30;
    }
    if (arg0->unk14.z < -(var_f30 - arg0->unk30)) {
        var_r31 = 1;
        arg0->unk14.z = -(var_f30 - arg0->unk30);
    }
    return var_r31;
}

void fn_1_1E10(StructBss70 *arg0)
{
    Vec sp104;
    Vec spF8;
    Vec spEC;
    float temp_f21;
    float temp_f20;
    float var_f19;
    float var_f26;
    float spC4;
    float spC0;
    float spBC;
    float spB8;
    float spB4;
    float spB0;
    float spAC;
    float spA0;
    StructBss70 *var_r30;
    StructBss70 *temp_r28;
    s32 temp_r19;
    s32 var_r21;
    s32 i;

    if (fn_1_1880(arg0->unk14.x, arg0->unk14.z, 50.0f, 10, arg0->unk0C) == 0) {
        return;
    }
    var_f19 = fn_1_14B4(atan2d(arg0->unk14.x - arg0->unk24, arg0->unk14.z - arg0->unk28));
    temp_f21 = spB8 = arg0->unk24;
    temp_f20 = spB4 = arg0->unk28;
    spAC = 1.0f;
    for (var_r21 = 1.0f + arg0->unk34 / spAC; var_r21 != 0; var_r21--) {
        temp_f21 += spAC * sind(var_f19);
        temp_f20 += spAC * cosd(var_f19);
        HuSetVecF(&sp104, temp_f21, arg0->unk14.y, temp_f20);
        for (i = 0; i < 10; i++) {
            if (i == arg0->unk0C) {
                continue;
            }
            var_r30 = &lbl_1_bss_70[i];
            HuSetVecF(&spF8, var_r30->unk14.x, var_r30->unk14.y, var_r30->unk14.z);
            HuSubVecF(&spEC, &sp104, &spF8);
            if (VECMagXYZ(&spEC) < arg0->unk30 + var_r30->unk30) {
                break;
            }
        }
        if (i < 10) {
            break;
        }
        if (fn_1_1BD4(arg0)) {
            goto block_end;
        }
        spB8 = temp_f21;
        spB4 = temp_f20;
    }
    var_f19 = fn_1_14B4(atan2d(arg0->unk14.x - arg0->unk24, arg0->unk14.z - arg0->unk28));
    var_f26 = fn_1_14B4(atan2d(var_r30->unk14.x - arg0->unk24, var_r30->unk14.z - arg0->unk28));
    spC0 = var_f19 - var_f26;
    if (spC0 > 0.0f) {
        spBC = -0.5f;
    }
    else {
        spBC = 0.5f;
    }
    if (ABS_INV(var_f19 - var_f26) > 180.0f) {
        spBC = -spBC;
    }
    var_f26 = fn_1_14B4(atan2d(arg0->unk24 - var_r30->unk14.x, arg0->unk28 - var_r30->unk14.z));
    spB0 = 0.8f * arg0->unk34;
    temp_r19 = var_r30->unk0C;
    spC4 = arg0->unk30 + var_r30->unk30 + 1.0f;
    while (TRUE) {
        temp_f21 = var_r30->unk14.x + spC4 * sind(var_f26);
        temp_f20 = var_r30->unk14.z + spC4 * cosd(var_f26);
        HuSetVecF(&sp104, temp_f21, 0.0, temp_f20);
        for (i = 0; i < 10; i++) {
            if (i == arg0->unk0C || i == temp_r19) {
                continue;
            }
            temp_r28 = &lbl_1_bss_70[i];
            HuSetVecF(&spF8, temp_r28->unk14.x, 0.0, temp_r28->unk14.z);
            HuSubVecF(&spEC, &sp104, &spF8);
            if (VECMagXZ(&spEC) < arg0->unk30 + temp_r28->unk30) {
                break;
            }
        }
        if (i < 10 || fn_1_1BD4(arg0)) {
            break;
        }
        spB8 = temp_f21;
        spB4 = temp_f20;
        HuSetVecF(&sp104, arg0->unk24, 0.0, arg0->unk28);
        HuSetVecF(&spF8, temp_f21, 0.0, temp_f20);
        HuSubVecF(&spEC, &sp104, &spF8);
        if (VECMagXZ(&spEC) > spB0) {
            break;
        }
        var_f26 += spBC;
    }
block_end:
    arg0->unk14.x = spB8;
    arg0->unk14.z = spB4;
}

void fn_1_2FDC(StructBss70 *arg0)
{
    Vec spF0;
    Vec spE4;
    Vec spD8;
    s32 i;
    StructBss340 *var_r30;
    StructBss70 *temp_r25;
    float var_f31;
    s32 var_r23;
    s32 var_r20;
    s32 spAC[2];

    var_r30 = &lbl_1_bss_340[0];
    arg0->unk24 = arg0->unk14.x;
    arg0->unk28 = arg0->unk14.z;
    switch (arg0->unk38) {
        case 0:
            var_r20 = 0;
            HuSetVecF(&spF0, var_r30->unk4C.x, 0.0, var_r30->unk4C.z);
            HuSetVecF(&spE4, arg0->unk14.x, 0.0, arg0->unk14.z);
            HuSubVecF(&spD8, &spF0, &spE4);
            if (VECMagXZ(&spD8) < var_r30->unk84 + arg0->unk30 + 100.0f) {
                var_r20 = 80;
            }
            if (frandmod(100) < var_r20) {
                var_f31 = fn_1_14B4(atan2d(arg0->unk14.x - var_r30->unk4C.x, arg0->unk14.z - var_r30->unk4C.z));
                var_f31 += 30.0f * frandf() - 60.0f;
                var_f31 = fn_1_14B4(var_f31);
                arg0->unk20 = var_f31;
            }
            else if (ABS_INV(arg0->unk14.x) > 550.0f) {
                var_f31 = fn_1_14B4(180.0 + atan2d(arg0->unk14.x, 0.0));
                var_f31 += 10.0f * frandf() - 20.0f;
                var_f31 = fn_1_14B4(var_f31);
                arg0->unk20 = var_f31;
            }
            else if (frandmod(3) != 0) {
                for (i = 0, var_r23 = 0; i < 10; i++) {
                    if (i == arg0->unk0C) {
                        continue;
                    }
                    temp_r25 = &lbl_1_bss_70[i];
                    HuSetVecF(&spF0, temp_r25->unk14.x, 0.0, temp_r25->unk14.z);
                    HuSetVecF(&spE4, arg0->unk14.x, 0.0, arg0->unk14.z);
                    HuSubVecF(&spD8, &spF0, &spE4);
                    if (VECMagXZ(&spD8) < 150.0f) {
                        spAC[var_r23++] = arg0->unk0C;
                        if (var_r23 >= 2) {
                            break;
                        }
                    }
                }
                if (var_r23 == 1 && ABS_INV(var_r30->unk4C.x) < 650.0f) {
                    temp_r25 = &lbl_1_bss_70[spAC[0]];
                    var_f31 = fn_1_14B4(atan2d(arg0->unk40 - arg0->unk14.x, arg0->unk44 - arg0->unk14.z));
                }
                else {
                    var_f31 = fn_1_14B4(180.0 + atan2d(arg0->unk14.x, arg0->unk14.z));
                    var_f31 += 30.0f * frandf() - 60.0f;
                    var_f31 = fn_1_14B4(var_f31);
                    arg0->unk20 = var_f31;
                }
            }
            else {
                var_f31 = 360.0f * frandf();
                arg0->unk20 = var_f31;
            }
            arg0->unk40 = arg0->unk14.x + 100.0 * sind(var_f31);
            arg0->unk44 = arg0->unk14.z + 100.0 * cosd(var_f31);
            arg0->unk38 = 10;
            arg0->unk3C = 60;
            break;
        case 10:
            if (arg0->unk3C-- == 0) {
                arg0->unk38 = 0;
            }
            if (arg0->unk3C < 50) {
                HuSetVecF(&spF0, var_r30->unk4C.x, 0.0, var_r30->unk4C.z);
                HuSetVecF(&spE4, arg0->unk14.x, 0.0, arg0->unk14.z);
                HuSubVecF(&spD8, &spF0, &spE4);
                if (VECMagXZ(&spD8) < var_r30->unk84 + arg0->unk30 + 100.0f) {
                    arg0->unk38 = 0;
                }
            }
            HuSetVecF(&spF0, arg0->unk40, 0.0, arg0->unk44);
            HuSetVecF(&spE4, arg0->unk14.x, 0.0, arg0->unk14.z);
            HuSubVecF(&spD8, &spF0, &spE4);
            if (VECMagXZ(&spD8) > 10.0f) {
                var_f31 = fn_1_14B4(atan2d(arg0->unk40 - arg0->unk14.x, arg0->unk44 - arg0->unk14.z));
                arg0->unk14.x += arg0->unk34 * sind(var_f31);
                arg0->unk14.z += arg0->unk34 * cosd(var_f31);
                if (fn_1_1BD4(arg0)) { }
                if (fn_1_1880(arg0->unk14.x, arg0->unk14.z, 50.0f, 10, arg0->unk0C) != 0) {
                    arg0->unk14.x = arg0->unk24;
                    arg0->unk14.z = arg0->unk28;
                    arg0->unk38 = 100;
                    arg0->unk3C = 0;
                }
            }
            else {
                arg0->unk38 = 100;
                arg0->unk3C = 0;
            }
            break;
        case 100:
            if (arg0->unk3C == 0) {
                arg0->unk38 = 0;
            }
            arg0->unk3C--;
            break;
    }
}

void fn_1_44D8(void)
{
    StructBss70 *temp_r31;
    float temp_f30;
    float var_f31;
    s32 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_f30 = temp_r31->unk14.x;
    while (TRUE) {
        Hu3DMotionSet(temp_r31->unk00, temp_r31->unk04[0]);
        for (i = 0, var_f31 = 0.0f; i < 60; i++) {
            temp_r31->unk14.x = temp_f30 - 300.0 * sind(var_f31);
            var_f31 += 1.5f;
            Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk14.x, temp_r31->unk14.y, temp_r31->unk14.z);
            HuPrcVSleep();
        }
        HuPrcSleep(30);
        Hu3DMotionSet(temp_r31->unk00, temp_r31->unk04[1]);
        for (i = 0, var_f31 = 90.0f; i < 60; i++) {
            temp_r31->unk14.x = temp_f30 - 300.0 * sind(var_f31);
            var_f31 -= 1.5f;
            Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk14.x, temp_r31->unk14.y, temp_r31->unk14.z);
            HuPrcVSleep();
        }
        HuPrcSleep(30);
    }
}

void fn_1_4644(StructBss70 *arg0)
{
    float temp_f26;
    float temp_f25;
    float var_f27;
    float var_f24;
    float temp_f23;
    s32 i;

    do {
        temp_f26 = 5.0f;
        if (frandmod(2) != 0) {
            arg0->unk14.x = -700.0f + temp_f26;
            arg0->unk20 = 90.0f;
            var_f27 = -700.0f + temp_f26 - 500.0f;
            var_f24 = 8.333333f;
        }
        else {
            arg0->unk14.x = 700.0f - temp_f26;
            arg0->unk20 = 270.0f;
            var_f27 = 700.0f - temp_f26 + 500.0f;
            var_f24 = -8.333333f;
        }
        arg0->unk14.y = 0.0f;
        temp_f23 = 550.0f;
        temp_f25 = temp_f23 * frandf() * 2.0f - temp_f23;
        arg0->unk14.z = temp_f25;
        arg0->unk24 = arg0->unk14.x;
        arg0->unk28 = arg0->unk14.z;
    } while (fn_1_1880(arg0->unk14.x, arg0->unk14.z, 50.0f, 10, arg0->unk0C) != 0);
    Hu3DMotionSet(arg0->unk00, arg0->unk04[2]);
    Hu3DModelRotSet(arg0->unk00, 0.0f, arg0->unk20, 0.0f);
    for (i = 0; i < 60; i++) {
        var_f27 += var_f24;
        Hu3DModelPosSet(arg0->unk00, var_f27, 0.0f, temp_f25);
        if (lbl_1_bss_3E4 >= 4) {
            break;
        }
        HuPrcVSleep();
    }
    if (lbl_1_bss_3E4 >= 4) {
        arg0->unk14.x = var_f27;
        arg0->unk14.z = temp_f25;
    }
    Hu3DModelPosSet(arg0->unk00, arg0->unk14.x, 0.0f, arg0->unk14.z);
}

void fn_1_4BC4(void)
{
    s32 spC;
    float sp8;
    float temp_f23;
    float var_f27;
    float var_f28;
    float var_f30;
    float var_f29;
    StructBss70 *temp_r31;
    StructBss340 *var_r28;
    StructBss340 *var_r30;
    s32 temp_r27;
    s32 temp_r24;
    s32 var_r26;
    s32 var_r25;
    s32 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk10 = 0;
loop_1:
    temp_r27 = lbl_1_bss_3E0 / REFRESH_RATE;
    var_r25 = 0;
    if (temp_r27 > 10) {
        var_r25 = 1;
    }
    if (temp_r27 > 20) {
        var_r25 = 2;
    }
    temp_r27 = frandmod(100);
    for (i = 0; i < 5; i++) {
        if (lbl_1_data_C0[var_r25][i] > temp_r27) {
            break;
        }
    }
    if (i > 4) {
        while (TRUE)
            ;
    }
    temp_r31->unk34 = 6.75f * lbl_1_data_FC[i];
    temp_r31->unk38 = 0;
    while (TRUE) {
        switch (temp_r31->unk10) {
            case 2:
                Hu3DMotionSet(temp_r31->unk00, temp_r31->unk04[1]);
                fn_1_4644(temp_r31);
                temp_r31->unk10 = 0;
                if (FALSE) {
                    default:
                        fn_1_2FDC(temp_r31);
                }
                Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk14.x, temp_r31->unk14.y, temp_r31->unk14.z);
                Hu3DModelRotSet(temp_r31->unk00, 0.0f, temp_r31->unk20, 0.0f);
                if (lbl_1_bss_3E4 < 4) {
                    HuPrcVSleep();
                    break;
                }
                Hu3DMotionSet(temp_r31->unk00, temp_r31->unk04[0]);
                HuPrcSleep(60);
                var_r28 = &lbl_1_bss_340[0];
                if (ABS_INV(var_r28->unk4C.z - temp_r31->unk14.z) > 250.0f) {
                    if (temp_r31->unk14.x > 0.0f) {
                        var_f30 = 10.0f;
                    }
                    else {
                        var_f30 = -10.0f;
                    }
                }
                else {
                    if (var_r28->unk4C.x > temp_r31->unk14.x) {
                        var_f30 = -10.0f;
                    }
                    else {
                        var_f30 = 10.0f;
                    }
                }
                if (var_f30 > 0.0f) {
                    Hu3DModelRotSet(temp_r31->unk00, 0.0f, 90.0f, 0.0f);
                }
                else {
                    Hu3DModelRotSet(temp_r31->unk00, 0.0f, 270.0f, 0.0f);
                }
                Hu3DMotionSet(temp_r31->unk00, temp_r31->unk04[1]);
                while (ABS_INV(temp_r31->unk14.x) < 1500.0f) {
                    temp_r31->unk14.x += var_f30;
                    Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk14.x, temp_r31->unk14.y, temp_r31->unk14.z);
                    HuPrcVSleep();
                }
                while (TRUE) {
                    HuPrcVSleep();
                }
                break;
            case 3:
                lbl_1_bss_3D8++;
                if (lbl_1_bss_3D8 > 99) {
                    lbl_1_bss_3D8 = 99;
                }
                temp_r24 = lbl_1_bss_3D8;
                var_r26 = 4;
                HuSprBankSet(lbl_1_bss_3DC, var_r26, temp_r24 % 10);
                HuSprBankSet(lbl_1_bss_3DC, var_r26 + 1, temp_r24 / 10);
                HuSprAttrReset(lbl_1_bss_3DC, var_r26 + 1, HUSPR_ATTR_DISPOFF);
                omVibrate(0, 12, 6, 6);
                HuAudFXPlay(0x45);
                HuAudFXPlay(0x5EE);
                var_r30 = &lbl_1_bss_340[0];
                temp_r31->unk2C = fn_1_14B4(atan2d(temp_r31->unk14.x - var_r30->unk4C.x, temp_r31->unk14.z - var_r30->unk4C.z));
                Hu3DMotionTimeSet(temp_r31->unk02, 0.0f);
                Hu3DModelAttrReset(temp_r31->unk02, HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(temp_r31->unk02, var_r30->unk4C.x + var_r30->unk84 * sind(temp_r31->unk2C), temp_r31->unk14.y + 50.0f,
                    var_r30->unk4C.z + var_r30->unk84 * cosd(temp_r31->unk2C));
                i = 0;
                var_f29 = temp_r31->unk14.x;
                var_f28 = temp_r31->unk14.z;
                while (TRUE) {
                    var_f29 += 30.0 * sind(var_r30->unk94);
                    var_f28 += 30.0 * cosd(var_r30->unk94);
                    if (ABS_INV(var_f29) > 1500.0f || var_f28 > 1300.0f || var_f28 < -2000.0f) {
                        break;
                    }
                    i++;
                }
                sp8 = temp_r31->unk14.y;
                var_f27 = 0.0f;
                temp_f23 = 180.0f / i;
                spC = 0;
                for (; i != 0; i--) {
                    temp_r31->unk14.x += 30.0 * sind(temp_r31->unk2C);
                    temp_r31->unk14.y = 400.0 * sind(var_f27);
                    temp_r31->unk14.z += 30.0 * cosd(temp_r31->unk2C);
                    var_f27 += temp_f23;
                    Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk14.x, temp_r31->unk14.y, temp_r31->unk14.z);
                    HuPrcVSleep();
                }
                Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk14.x, -1000.0f, temp_r31->unk14.z);
                temp_r31->unk10 = 2;
                Hu3DModelAttrSet(temp_r31->unk02, HU3D_ATTR_DISPOFF);
                goto loop_1;
        }
    }
}

void fn_1_545C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    StructBss340 *temp_r28;
    float var_f30;
    float var_f31;
    float temp_f29;
    s32 var_r27;
    s16 i;
    s16 j;
    s16 k;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (k = 0; k < particle->unk_30; k++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < 1; i++) {
        temp_r28 = &lbl_1_bss_340[i];
        if (!(temp_r28->unk30 & 1)) {
            continue;
        }
        for (j = 0, var_f30 = 0.0f; j < 16; j++, var_f30 += 22.5f) {
            for (k = 0; k < particle->unk_30; k++, var_r31++) {
                if (var_r31->unk14.x == 0.0f) {
                    break;
                }
            }
            if (k == particle->unk_30) {
                break;
            }
            var_f31 = var_f30;
            temp_f29 = 125.0f + 70.0f * frandf();
            var_r31->unk34.x = temp_r28->unk6C + temp_f29 * sind(var_f31);
            var_r31->unk34.y = temp_r28->unk70 + 50.0f * frandf();
            var_r31->unk34.z = temp_r28->unk74 + temp_f29 * cosd(var_f31);
            var_r31->unk08.x = 5.0 * sind(var_f31);
            var_r31->unk08.y = 9.0f + 2.0f * frandf();
            var_r31->unk08.z = 5.0 * cosd(var_f31);
            var_r31->unk14.x = 30.0f;
            var_r31->unk2C = 80.0f + 20.0f * frandf();
            var_r31->unk14.y = 15.0f;
            var_r31->unk40.a = 0xC8;
            var_r31->unk14.z = 17.0f;
        }
        temp_r28->unk30 &= ~1;
    }
    var_r31 = particle->unk_48;
    for (k = 0; k < particle->unk_30; k++, var_r31++) {
        if (var_r31->unk14.x == 0.0f) {
            continue;
        }
        VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
        var_r31->unk08.x *= 0.95f;
        var_r31->unk08.z *= 0.95f;
        if (var_r31->unk08.y > 0.1f) {
            var_r31->unk08.y -= 0.2f;
        }
        if (var_r31->unk08.y < 0.0f) {
            var_r31->unk08.y = 0.0f;
        }
        var_r31->unk2C += var_r31->unk14.y;
        if (var_r31->unk14.y > 2.0f) {
            var_r31->unk14.y -= 1.5f;
        }
        var_r27 = var_r31->unk40.a;
        var_r27 -= var_r31->unk14.z;
        if (var_r31->unk14.z > 3.0f) {
            var_r31->unk14.z -= 1.0f;
        }
        if (var_r27 < 0) {
            var_r27 = 0;
            var_r31->unk14.x = 0.0f;
        }
        var_r31->unk40.a = var_r27;
        if (var_r31->unk14.x == 0.0f) {
            var_r31->unk2C = 0.0f;
        }
    }
}

void fn_1_594C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    StructBss340 *temp_r28;
    float temp_f31;
    float temp_f30;
    s32 var_r27;
    s16 i;
    s16 j;
    s16 k;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (k = 0; k < particle->unk_30; k++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
            var_r31->unk20 = -1.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < 1; i++) {
        temp_r28 = &lbl_1_bss_340[i];
        if (!(temp_r28->unk30 & 2)) {
            continue;
        }
        for (j = 0; j < 10; j++) {
            for (k = 0; k < particle->unk_30; k++, var_r31++) {
                if (var_r31->unk14.x == 0.0f) {
                    break;
                }
            }
            if (k == particle->unk_30) {
                break;
            }
            temp_f31 = 400.0f * frandf() - 200.0f;
            temp_f30 = 400.0f * frandf() - 200.0f;
            var_r31->unk34.x = temp_r28->unk6C + temp_f31;
            var_r31->unk34.y = temp_r28->unk70 + 50.0f;
            var_r31->unk34.z = temp_r28->unk74 + temp_f30;
            var_r31->unk08.x = 0.0f;
            var_r31->unk08.y = 7.0f;
            var_r31->unk08.z = 0.0f;
            var_r31->unk20 = frandmod(10);
            var_r31->unk24 = 0.0f;
            var_r31->unk14.x = 100.0f;
            var_r31->unk2C = 0.0f;
            var_r31->unk14.y = 7.0f;
            var_r31->unk40.a = 0xFF;
            var_r31->unk14.z = 10.0f;
        }
        temp_r28->unk30 &= ~2;
    }
    var_r31 = particle->unk_48;
    for (k = 0; k < particle->unk_30; k++, var_r31++) {
        if (var_r31->unk20 > 0.0f) {
            var_r31->unk20 -= 1.0f;
        }
        if (var_r31->unk20 == 0.0f) {
            var_r31->unk24 = 1.0f;
            var_r31->unk2C = 100.0f + 100.0f * frandf();
            var_r31->unk20 = -1.0f;
        }
        if (var_r31->unk14.x == 0.0f || var_r31->unk24 == 0.0f) {
            continue;
        }
        VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
        if (var_r31->unk08.y > 1.0f) {
            var_r31->unk08.y -= 0.3f;
        }
        var_r31->unk2C += var_r31->unk14.y;
        if (var_r31->unk14.y > 2.0f) {
            var_r31->unk14.y -= 0.4f;
        }
        var_r27 = var_r31->unk40.a;
        var_r27 -= var_r31->unk14.z;
        if (var_r31->unk14.z > 3.0f) {
            var_r31->unk14.z -= 1.0f;
        }
        if (var_r27 < 0) {
            var_r27 = 0;
            var_r31->unk14.x = 0.0f;
        }
        var_r31->unk40.a = var_r27;
        if (var_r31->unk14.x == 0.0f) {
            var_r31->unk2C = 0.0f;
        }
    }
}

void fn_1_5DE4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    StructBss340 *temp_r28;
    float temp_f31;
    float temp_f30;
    s32 var_r27;
    s16 i;
    s16 j;
    s16 k;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (k = 0; k < particle->unk_30; k++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
            var_r31->unk20 = -1.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < 1; i++) {
        temp_r28 = &lbl_1_bss_340[i];
        if (!(temp_r28->unk30 & 4)) {
            continue;
        }
        for (j = 0; j < 10; j++) {
            for (k = 0; k < particle->unk_30; k++, var_r31++) {
                if (var_r31->unk14.x == 0.0f) {
                    break;
                }
            }
            if (k == particle->unk_30) {
                break;
            }
            temp_f31 = 400.0f * frandf() - 200.0f;
            temp_f30 = 400.0f * frandf() - 200.0f;
            var_r31->unk34.x = temp_r28->unk6C + temp_f31;
            var_r31->unk34.y = temp_r28->unk70 + 50.0f;
            var_r31->unk34.z = temp_r28->unk74 + temp_f30;
            var_r31->unk08.x = 0.0f;
            var_r31->unk08.y = 7.0f;
            var_r31->unk08.z = 0.0f;
            var_r31->unk20 = frandmod(10);
            var_r31->unk24 = 0.0f;
            var_r31->unk14.x = 100.0f;
            var_r31->unk2C = 0.0f;
            var_r31->unk14.y = 7.0f;
            var_r31->unk40.a = 0xFF;
            var_r31->unk14.z = 10.0f;
        }
        temp_r28->unk30 &= ~4;
    }
    var_r31 = particle->unk_48;
    for (k = 0; k < particle->unk_30; k++, var_r31++) {
        if (var_r31->unk20 > 0.0f) {
            var_r31->unk20 -= 1.0f;
        }
        if (var_r31->unk20 == 0.0f) {
            var_r31->unk24 = 1.0f;
            var_r31->unk2C = 100.0f + 100.0f * frandf();
            var_r31->unk20 = -1.0f;
        }
        if (var_r31->unk14.x == 0.0f || var_r31->unk24 == 0.0f) {
            continue;
        }
        VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
        if (var_r31->unk08.y > 1.0f) {
            var_r31->unk08.y -= 0.3f;
        }
        var_r31->unk2C += var_r31->unk14.y;
        if (var_r31->unk14.y > 2.0f) {
            var_r31->unk14.y -= 0.4f;
        }
        var_r27 = var_r31->unk40.a;
        var_r27 -= var_r31->unk14.z;
        if (var_r31->unk14.z > 3.0f) {
            var_r31->unk14.z -= 1.0f;
        }
        if (var_r27 < 0) {
            var_r27 = 0;
            var_r31->unk14.x = 0.0f;
        }
        var_r31->unk40.a = var_r27;
        if (var_r31->unk14.x == 0.0f) {
            var_r31->unk2C = 0.0f;
        }
    }
}

s8 fn_1_627C(s32 arg0, s32 arg1)
{
    StructBss340 *temp_r31;
    s8 var_r30;

    temp_r31 = &lbl_1_bss_340[arg0];
    (arg1 != 0) ? (var_r30 = HuPadStkY[temp_r31->unk28]) : (var_r30 = HuPadStkX[temp_r31->unk28]);
    return var_r30;
}

u8 fn_1_62F0(s32 arg0, s32 arg1)
{
    StructBss340 *temp_r31;
    s8 var_r30;

    temp_r31 = &lbl_1_bss_340[arg0];
    (arg1 != 0) ? (var_r30 = HuPadTrigR[temp_r31->unk28]) : (var_r30 = HuPadTrigL[temp_r31->unk28]);
    return var_r30;
}

u16 fn_1_636C(s32 arg0)
{
    StructBss340 *temp_r31;
    u16 var_r30;

    temp_r31 = &lbl_1_bss_340[arg0];
    var_r30 = HuPadBtnDown[temp_r31->unk28];
    return var_r30;
}

u16 fn_1_63B4(s32 arg0)
{
    StructBss340 *temp_r31;
    u16 var_r30;

    temp_r31 = &lbl_1_bss_340[arg0];
    var_r30 = HuPadBtn[temp_r31->unk28];
    return var_r30;
}

s32 fn_1_63FC(StructBss340 *arg0)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    StructBss70 *temp_r31;
    s32 var_r28;
    s32 i;

    var_r28 = -1;
    HuSetVecF(&sp24, arg0->unk4C.x, arg0->unk4C.y, arg0->unk4C.z);
    for (i = 0; i < 10; i++) {
        temp_r31 = &lbl_1_bss_70[i];
        HuSetVecF(&sp18, temp_r31->unk14.x, temp_r31->unk14.y, temp_r31->unk14.z);
        HuSubVecF(&spC, &sp24, &sp18);
        if (VECMagXYZ(&spC) < arg0->unk84 + temp_r31->unk30) {
            temp_r31->unk10 = 3;
            var_r28 = i;
        }
    }
    return var_r28;
}

s32 fn_1_65D0(StructBss340 *arg0)
{
    float var_f31;
    float var_f30;
    s32 sp8; // ! - uninitialized

    var_f31 = fn_1_1534(arg0->unk4C.z, arg0->unk84);
    var_f30 = fn_1_1534(arg0->unk4C.x, arg0->unk84);
    if (arg0->unk4C.x > var_f31 - arg0->unk84) {
        arg0->unk4C.x = var_f31 - arg0->unk84;
    }
    if (arg0->unk4C.x < -(var_f31 - arg0->unk84)) {
        arg0->unk4C.x = -(var_f31 - arg0->unk84);
    }
    if (arg0->unk4C.z > var_f30 - arg0->unk84) {
        arg0->unk4C.z = var_f30 - arg0->unk84;
    }
    if (arg0->unk4C.z < -(var_f30 - arg0->unk84)) {
        arg0->unk4C.z = -(var_f30 - arg0->unk84);
    }
    return sp8;
}

float fn_1_67F0(float arg0, float arg1, float arg2)
{
    float var_f30;
    float var_f31;

    var_f31 = fmod(arg1 - arg0, 360.0);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg0 + var_f31 * arg2, 360.0);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

void fn_1_68F4(void)
{
    StructBss340 *temp_r31;
    s32 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    for (i = 0; i < 20; i++) {
        temp_r31->unk78.z -= 4.0f;
        Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk78.x, temp_r31->unk78.y, temp_r31->unk78.z);
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 fn_1_6964(StructBss340 *arg0)
{
    return (arg0->unk2C == 4 || arg0->unk2C == 5 || arg0->unk2C == 6);
}

void fn_1_69C0(void)
{
    float var_f23;
    float var_f27;
    float var_f26;
    StructBss340 *temp_r31;
    s16 var_r29;
    s32 var_r24;
    s32 var_r23;
    Process *var_r22;
    s32 var_r26;
    s32 var_r25;
    s32 var_r28;
    s32 spA4;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk2C = 0;
    temp_r31->unk48 = 0;
    temp_r31->unk30 = 0;
    while (lbl_1_bss_3E4 == 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_3E4 = 2;
    while (lbl_1_bss_3E4 == 2) {
        HuPrcVSleep();
    }
    var_r29 = -1;
    while (TRUE) {
        temp_r31->unk58 = temp_r31->unk4C.x;
        temp_r31->unk5C = temp_r31->unk4C.z;
        if (temp_r31->unk16[4] != 0) {
            break;
        }
        switch (temp_r31->unk2C) {
            case 8:
                if (temp_r31->unk3C != 0) {
                    temp_r31->unk3C--;
                }
                else {
                    Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
                    temp_r31->unk2C = 0;
                }
                break;
            case 4:
                omVibrate(temp_r31->unk20, 12, 4, 2);
                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
                temp_r31->unk3C = 90;
                temp_r31->unk44 = 30;
                temp_r31->unk2C = 5;
                break;
            case 5:
                if (temp_r31->unk44-- == 0) {
                    temp_r31->unk6C = temp_r31->unk4C.x;
                    temp_r31->unk70 = temp_r31->unk4C.y;
                    temp_r31->unk74 = temp_r31->unk4C.z;
                    temp_r31->unk30 |= 1;
                }
                if (temp_r31->unk3C != 0) {
                    temp_r31->unk3C--;
                }
                else {
                    Hu3DMotionSet(temp_r31->unk00, temp_r31->unk06[5]);
                    Hu3DModelAttrReset(temp_r31->unk00, HU3D_MOTATTR_LOOP);
                    temp_r31->unk2C = 6;
                }
                break;
            case 6:
                if (Hu3DMotionEndCheck(temp_r31->unk00) == TRUE) {
                    Hu3DMotionSet(temp_r31->unk00, temp_r31->unk06[0]);
                    temp_r31->unk2C = 0;
                }
                break;
            default:
                if (fn_1_627C(temp_r31->unk20, 0) > 20) {
                    temp_r31->unk94 -= temp_r31->unk90;
                    if (temp_r31->unk94 < 0.0f) {
                        temp_r31->unk94 += 360.0f;
                    }
                    temp_r31->unk60.y = temp_r31->unk94;
                }
                if (fn_1_627C(temp_r31->unk20, 0) < -20) {
                    temp_r31->unk94 += temp_r31->unk90;
                    if (temp_r31->unk94 > 360.0f) {
                        temp_r31->unk94 -= 360.0f;
                    }
                    temp_r31->unk60.y = temp_r31->unk94;
                }
                if (fn_1_63B4(temp_r31->unk20) & PAD_BUTTON_A) {
                    temp_r31->unk4C.x += temp_r31->unk88 * sind(temp_r31->unk94);
                    temp_r31->unk4C.z += temp_r31->unk88 * cosd(temp_r31->unk94);
                }
                if (fn_1_63B4(temp_r31->unk20) & PAD_BUTTON_B) {
                    temp_r31->unk4C.x -= temp_r31->unk88 * sind(temp_r31->unk94);
                    temp_r31->unk4C.z -= temp_r31->unk88 * cosd(temp_r31->unk94);
                }
                if (fn_1_63B4(temp_r31->unk20) & (PAD_BUTTON_A | PAD_BUTTON_B)) {
                    if (temp_r31->unk34 != 1) {
                        if (temp_r31->unk2C != 2) {
                            temp_r31->unk2C = 2;
                            if (fn_1_63B4(temp_r31->unk20) & PAD_BUTTON_A) {
                                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                                Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                            }
                            else {
                                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV);
                                Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                            }
                            if (var_r29 != -1) {
                                HuAudFXStop(var_r29);
                            }
                        }
                    }
                    else {
                        if (temp_r31->unk2C != 3) {
                            temp_r31->unk2C = 3;
                            temp_r31->unk48 = 0;
                            if (fn_1_63B4(temp_r31->unk20) & PAD_BUTTON_A) {
                                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                                Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                            }
                            else {
                                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV);
                                Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                            }
                            if (var_r29 != -1) {
                                HuAudFXStop(var_r29);
                            }
                        }
                    }
                    if (temp_r31->unk34 != 1) {
                        var_r24 = 8;
                        var_r23 = 32;
                    }
                    else {
                        var_r24 = 7;
                        var_r23 = 22;
                    }
                    if (temp_r31->unk48 == var_r24) {
                        HuAudFXPlay(0x5E0);
                    }
                    if (temp_r31->unk48 == var_r23) {
                        HuAudFXPlay(0x5E0);
                    }
                    temp_r31->unk48++;
                    if (temp_r31->unk34 != 1) {
                        if (temp_r31->unk48 >= 50) {
                            temp_r31->unk48 -= 50;
                        }
                    }
                    else {
                        if (temp_r31->unk48 >= 30) {
                            temp_r31->unk48 -= 30;
                        }
                    }
                }
                else {
                    if (ABS_INV(fn_1_627C(temp_r31->unk20, 0)) <= 20) {
                        if (temp_r31->unk2C != 0) {
                            temp_r31->unk2C = 0;
                            Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                            if (var_r29 != -1) {
                                HuAudFXStop(var_r29);
                            }
                        }
                    }
                    else {
                        if (temp_r31->unk2C != 1) {
                            temp_r31->unk2C = 1;
                            Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[3], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                            Hu3DMotionShiftSpeedSet(temp_r31->unk00, 1.5f);
                            var_r29 = HuAudFXPlay(0x5EB);
                        }
                    }
                }
                if (fn_1_63FC(temp_r31) != -1) { }
                if ((spA4 = fn_1_65D0(temp_r31)) != -1) { }
                break;
        }
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk60.x, temp_r31->unk60.y, temp_r31->unk60.z);
        HuPrcVSleep();
    }
    if (var_r29 != -1) {
        HuAudFXStop(var_r29);
    }
    if (lbl_1_bss_3D8 == 0) {
        HuAudFXPlay(0x5EA);
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[0], 0.0f, 2.0f, HU3D_MOTATTR_LOOP);
        HuPrcSleep(90);
        Hu3DModelAttrReset(temp_r31->unk04, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(temp_r31->unk04, HU3D_MOTATTR_PAUSE);
        Hu3DModelPosSet(temp_r31->unk04, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[7], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        HuAudFXPlay(0x5E3);
        HuPrcSleep(15);
        HuPrcSleep(30);
        temp_r31->unk6C = temp_r31->unk4C.x;
        temp_r31->unk70 = temp_r31->unk4C.y;
        temp_r31->unk74 = temp_r31->unk4C.z;
        temp_r31->unk30 |= 2;
        while (!Hu3DMotionEndCheck(temp_r31->unk00)) {
            HuPrcVSleep();
        }
        CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk20].character], temp_r31->unk16[3], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        Hu3DModelHookReset(temp_r31->unk00);
        Hu3DModelShadowSet(temp_r31->unk02);
        var_f27 = 50.0f;
        Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk4C.x, temp_r31->unk4C.y + var_f27, temp_r31->unk4C.z);
        HuPrcSleep(60);
        for (var_r26 = 0, var_r25 = 0; var_r26 < 90; var_r26++) {
            if (var_r25 & 1) {
                Hu3DModelAttrReset(temp_r31->unk00, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(temp_r31->unk04, HU3D_ATTR_DISPOFF);
            }
            else {
                Hu3DModelAttrSet(temp_r31->unk00, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(temp_r31->unk04, HU3D_ATTR_DISPOFF);
            }
            var_r25++;
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(temp_r31->unk04, HU3D_ATTR_DISPOFF);
        for (var_r28 = 0, var_f23 = 1.0f; var_r28 < 30; var_r28++) {
            var_f23 -= 0.033333335f;
            Hu3DModelTPLvlSet(temp_r31->unk00, var_f23);
            if (var_f27 > 0.0f) {
                var_f27 -= 5.0f;
                Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk4C.x, temp_r31->unk4C.y + var_f27, temp_r31->unk4C.z);
            }
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(temp_r31->unk00, HU3D_ATTR_DISPOFF);
        HuAudSStreamPlay(4);
        HuPrcSleep(REFRESH_RATE*3);
    }
    else {
        var_f26 = temp_r31->unk90;
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[3], 0.0f, 2.0f, HU3D_MOTATTR_LOOP);
        if (fn_1_14B4(temp_r31->unk60.y) != 0.0f) {
            var_r28 = (360.0f - fn_1_14B4(temp_r31->unk60.y)) / var_f26;
            if (temp_r31->unk60.y < 180.0f) {
                var_r28 = temp_r31->unk60.y / var_f26;
                var_f26 = -var_f26;
            }
            for (; var_r28 != 0; var_r28--) {
                temp_r31->unk60.y += var_f26;
                Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk60.x, temp_r31->unk60.y, temp_r31->unk60.z);
                HuPrcVSleep();
            }
            Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk60.x, 0.0f, temp_r31->unk60.z);
        }
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[0], 0.0f, 2.0f, HU3D_MOTATTR_LOOP);
        while (lbl_1_bss_3E4 < 5) {
            HuPrcVSleep();
        }
        HuAudSStreamPlay(1);
        var_r22 = HuPrcChildCreate(fn_1_68F4, 0x2000, 0x1000, 0, HuPrcCurrentGet());
        var_r22->user_data = temp_r31;
        HuAudPlayerVoicePlay(temp_r31->unk20, 0x122);
        CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk20].character], temp_r31->unk16[2], 0.0f, 2.0f, HU3D_MOTATTR_NONE);
        temp_r31->unk2C = 10;
        HuPrcSleep(REFRESH_RATE*3);
    }
    lbl_1_bss_3E4 = 6;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_7D3C(void) { }

void fn_1_7D40(void)
{
    while (TRUE) {
        if (omSysExitReq == 1) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            HuPrcSleep(60);
            MGSeqKillAll();
            omOvlReturnEx(1, 1);
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_7DA0(void)
{
    s16 temp_r31;
    s16 var_r30;
    s16 temp_r26;
    s32 var_r24;
    s32 i;

    lbl_1_bss_3E4 = 0;
    lbl_1_bss_3E4 = 1;
    while (lbl_1_bss_3E4 == 1) {
        HuPrcVSleep();
    }
    var_r24 = HuAudSeqPlay(0x46);
    temp_r31 = MGSeqStartCreate();
    while (MGSeqStatGet(temp_r31) != 0) {
        HuPrcVSleep();
    }
    fn_1_16F8();
    var_r30 = (REFRESH_RATE*31)-1;
    temp_r26 = MGSeqTimerCreate(var_r30 / REFRESH_RATE);
    lbl_1_bss_3E4 = 3;
    while (TRUE) {
        if (var_r30 < REFRESH_RATE-1) {
            break;
        }
        MGSeqParamSet(temp_r26, 1, var_r30-- / REFRESH_RATE);
        lbl_1_bss_3E0++;
        HuPrcVSleep();
    }
    for (i = 0; i < 1; i++) {
        lbl_1_bss_340[i].unk1E = 1;
    }
    lbl_1_bss_3E4 = 4;
    HuAudSeqFadeOut(var_r24, 6);
    MGSeqParamSet(temp_r26, 2, -1);
    temp_r31 = MGSeqFinishCreate();
    while (MGSeqStatGet(temp_r31) != 0) {
        HuPrcVSleep();
    }
    mgRecordExtra = lbl_1_bss_3D8;
    if (GWMGRecordGet(14) < lbl_1_bss_3D8) {
        GWMGRecordSet(14, lbl_1_bss_3D8);
        temp_r31 = MGSeqRecordCreate(lbl_1_bss_3D8);
        HuPrcChildCreate(fn_1_1634, 0x1000, 0x1000, 0, HuPrcCurrentGet());
        fn_1_17A0(lbl_1_bss_3D8, 1);
        while (MGSeqStatGet(temp_r31) != 0) {
            HuPrcVSleep();
        }
        lbl_1_bss_3E4 = 5;
    }
    else {
        lbl_1_bss_3E4 = 5;
    }
    while (lbl_1_bss_3E4 < 6) {
        HuPrcVSleep();
    }
    HuPrcSleep(REFRESH_RATE/2);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuPrcSleep(60);
    HuAudFadeOut(1);
    MGSeqKillAll();
    omOvlReturnEx(1, 1);
    while (TRUE) {
        HuPrcVSleep();
    }
}

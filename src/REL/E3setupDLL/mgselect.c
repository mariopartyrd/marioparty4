#include "ext_math.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/init.h"
#include "game/objsub.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/E3SetupDLL.h"

#ifndef __MWERKS__
void HuSysVWaitSet(s16 vcount);
#endif

static s16 mgDefault;
static omObjData *mgInterfaceObj;
static omObjData *mgSelectObj;
static omObjData *mgPicObj;

s32 lbl_2_bss_14;
s16 lbl_2_bss_10;
s16 lbl_2_bss_E;
s16 lbl_2_bss_C;
s16 lbl_2_bss_A;
static s16 lbl_2_bss_0[5];

float lbl_2_data_0[] = { 0, 12000, 0, 0, 0, 0, 0, 0, -1 };

static void StartMGSelect(omObjData *object);
static void UpdatePad(omObjData *object);
static void CreateMGSelect(omObjData *object);
static void CreateMGPic(omObjData *object);
static void UpdateMGInterface(omObjData *object);
static void CreateMGInterface(omObjData *object);

void E3MGSelectInit()
{
    s32 var_r29;
    s32 var_r30;
    Process *var_r31;

    for (var_r29 = 0, var_r30 = 0; var_r29 < 4; var_r29++) {
        if (HuPadStatGet(var_r29) == 0) {
            var_r30++;
        }
    }
    e3ConfigPlayerCnt = var_r30;
    if (var_r30 <= 0) {
        OSReport("No pad detected\n");
        var_r30++;
    }
    mgDefault = 0;
    HuSysVWaitSet(1);
    var_r31 = omInitObjMan(0x50, 0x2000);
    HuWinInit(1);
    CRot.x = -4.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 160.0f;
    Center.z = 0.0f;
    CZoom = 1960.0;
    e3CameraFov = 40.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, e3CameraFov, 100.0f, 25000.0f, 4.0f / 3.0f);
    e3ViewObj = omAddObjEx(var_r31, 32730, 0, 0, -1, omOutView);
    e3OvlWatchObj = omAddObjEx(var_r31, 200, 0, 0, -1, E3OvlWatchInit);
    e3MenuMainObj = omAddObjEx(var_r31, 10, 0, 0, -1, StartMGSelect);
    e3BGObj = omAddObjEx(var_r31, 0x14, 0, 0, -1, E3BGCreate);
    mgInterfaceObj = omAddObjEx(var_r31, 20, 0, 0, -1, CreateMGInterface);
    mgSelectObj = omAddObjEx(var_r31, 30, 0, 0, -1, CreateMGSelect);
    mgPicObj = omAddObjEx(var_r31, 31, 0, 0, -1, CreateMGPic);
    mgPicObj->work[0] = mgDefault;
    E3LightInit();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
}

s16 lbl_2_data_36[] = { 0x0023, 0x0026, 0x0029, 0x002C };

static s16 mgOvlTbl[] = {
    11,
    12,
    15,
    18,
    20,
    23,
    26,
    27,
    33,
    34,
    39,
    44,
    46,
};

static s16 mgIdTbl[] = { 403, 404, 407, 410, 412, 415, 418, 419, 425, 426, 431, 436, 438, 0 };

static s32 mgNameTbl[] = {
    MAKE_MESSID(0x17, 0x03),
    MAKE_MESSID(0x17, 0x04),
    MAKE_MESSID(0x17, 0x07),
    MAKE_MESSID(0x17, 0x0A),
    MAKE_MESSID(0x17, 0x0C),
    MAKE_MESSID(0x17, 0x0F),
    MAKE_MESSID(0x17, 0x12),
    MAKE_MESSID(0x17, 0x13),
    MAKE_MESSID(0x17, 0x19),
    MAKE_MESSID(0x17, 0x1A),
    MAKE_MESSID(0x17, 0x1F),
    MAKE_MESSID(0x17, 0x24),
    MAKE_MESSID(0x17, 0x26),
};

char lbl_2_data_A8[] = "\013TEST MINIGAME NAME01\n      test";
char lbl_2_data_C9[] = "\013TEST MINIGAME NAME02";
char lbl_2_data_DF[] = "\013TEST MINIGAME NAME03";
char lbl_2_data_F5[] = "\013TEST MINIGAME NAME04";
char lbl_2_data_10B[] = "\013TEST NAME05";
char lbl_2_data_118[] = "\013TEST MINIGAME NAME06";
char lbl_2_data_12E[] = "\013TEST NAME07";
char lbl_2_data_13B[] = "\013TEST MINIGAME NAME08";
char lbl_2_data_151[] = "\013TEST MINIGAME NAME09";
char lbl_2_data_167[] = "\013TEST MINIGAME NAME10";
char lbl_2_data_17D[] = "\013TEST MINIGAME NAME11";
char lbl_2_data_193[] = "\013TEST MINIGAME NAME12";
char lbl_2_data_1A9[] = "\013TEST MINIGAME NAME13";

static char *mgNameTestTbl[] = {
    lbl_2_data_A8,
    lbl_2_data_C9,
    lbl_2_data_DF,
    lbl_2_data_F5,
    lbl_2_data_10B,
    lbl_2_data_118,
    lbl_2_data_12E,
    lbl_2_data_13B,
    lbl_2_data_151,
    lbl_2_data_167,
    lbl_2_data_17D,
    lbl_2_data_193,
    lbl_2_data_1A9,
};

static float cursorYOfsTbl[] = { -100.0f, -50.0f, 0.0f, 50.0f, 100.0f };

static s32 mgPicTbl[] = { 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52 };

static void StartMGSelect(omObjData *object)
{
    HuAudSeqPlay(0x2B);
    lbl_2_bss_14 = 0;
    lbl_2_bss_10 = -1;
    lbl_2_bss_C = 0x1E;
    lbl_2_bss_A = 0;
    object->func = UpdatePad;
    worstVcount = 0;
    object->work[0] = 0;
    object->work[1] = 0;
}

static void UpdatePad(omObjData *object)
{
    s32 i;
    s32 players;

    if (e3ExitEnableF == 0) {
        for (i = 0, players = 0; i < 4; i++) {
            E3PadUpdate(i, &e3PadData[i]);
            if (!e3PadData[i].enable) {
                players++;
            }
        }
        e3ConfigPlayerCnt = players;
    }
}

static void UpdateMGSelect(omObjData *object)
{
    mgSelect *var_r31;
    s32 var_r30;
    u32 var_r28;
    s16 var_r27;
    s16 var_r26;
    s16 var_r25;
    s16 var_r24;
    u16 var_r23;
    s16 var_r22;
    s32 var_r21;
    float sp8[2];

    var_r31 = object->data;
    var_r23 = e3PadData[e3PadCtrl].btnDown;
    if (object->work[3] != 0) {
        if ((var_r23 & 0x1100) != 0) {
            HuAudFXPlay(1);
            mgDefault = var_r31->unk_44;
            var_r21 = mgIdTbl[var_r31->unk_44];
            GWMGAvailSet(var_r21);
            GWSystem.mg_next = var_r21 - 401;
            e3NextOvl = 3;
            e3NextEvent = 0;
            e3ExitMode = 2;
            e3ExitEnableF = 1;
            var_r28 = mgOvlTbl[var_r31->unk_44];

            for (var_r30 = 0; var_r30 < 50; var_r30++) {
                if (var_r28 == mgInfoTbl[var_r30].ovl) {
                    break;
                }
            }
            if (var_r30 >= 50) {
                e3ExitMode = 0;
                e3NextOvl = 0;
            };
            switch (mgInfoTbl[var_r30].type) {
            case 0:
            case 3:
            case 4:
            case 5:
            case 6:
                for (var_r30 = 0; var_r30 < 4; var_r30++) {
                    GWPlayerCfg[var_r30].group = var_r30;
                }
                break;
            case 1:
                var_r28 = frand();
                var_r28 &= 3;
                for (var_r30 = 0; var_r30 < 4; var_r30++) {
                    if (var_r28 == var_r30) {
                        GWPlayerCfg[var_r30].group = 0;
                    } else {
                        GWPlayerCfg[var_r30].group = 1;
                    }
                }
                break;
            case 2:
                for (var_r30 = 0; var_r30 < 2; var_r30++) {
                    GWPlayerCfg[var_r30].group = 0;
                }
                for (var_r30 = 2; var_r30 < 4; var_r30++) {
                    GWPlayerCfg[var_r30].group = 1;
                }
                break;
            }
            object->work[3] = 0;
            return;
        }
        if ((var_r23 & 0x200) != 0) {
            HuAudFXPlay(3);
            e3ExitMode = 0;
            e3NextOvl = 0;
            e3NextEvent = 0;
            e3ExitEnableF = 1;
            object->work[3] = 0;
            return;
        }
        if (object->work[3] != 0) {
            if ((var_r23 & 8) != 0) {
                HuAudFXPlay(0);
                var_r31->unk_44--;
                if (var_r31->unk_44 < 0) {
                    var_r31->unk_44 = 0xC;
                }
            } else if ((var_r23 & 4) != 0) {
                HuAudFXPlay(0);
                var_r31->unk_44++;
                if (var_r31->unk_44 >= 13) {
                    var_r31->unk_44 = 0;
                }
            }
            if (var_r31->unk_46 != var_r31->unk_44) {
                mgPicObj->work[0] = var_r31->unk_44;
                var_r27 = var_r31->unk_44 - var_r31->unk_46;
                if ((var_r27 > 1) || (var_r27 < -1)) {
                    if (var_r27 < 0) {
                        var_r27 = 1;
                    } else {
                        var_r27 = -1;
                    }
                }
                var_r25 = var_r31->unk_42 + var_r27;
                if ((var_r25 < 0) || (var_r25 >= 5)) {
                    for (var_r30 = 0; var_r30 < 5; var_r30++) {
                        var_r22 = var_r31->unk_2E[var_r30];
                        var_r26 = var_r31->unk_38[var_r30];
                        var_r24 = var_r26 - var_r27;
                        if ((var_r24 < 0) || (var_r24 >= 5)) {
                            var_r28 = mgNameTbl[var_r31->unk_44];
                            HuWinMesSizeCancelCRSet(1);
                            HuWinMesMaxSizeGet(1, sp8, var_r28);
                            HuWinCenterPosSet(var_r22, (296.0f - sp8[0]) / -2.0f, (68.0f - sp8[1]) / -2.0f);
                            HuWinMesSet(var_r22, var_r28);
                            if (var_r24 < 0) {
                                var_r26 = 4;
                            } else {
                                var_r26 = 0;
                            }
                        } else {
                            var_r26 = var_r24;
                        }
                        HuWinPosSet(var_r22, 36.0f, 237.0f + cursorYOfsTbl[var_r26]);
                        var_r31->unk_38[var_r30] = var_r26;
                    }
                } else {
                    var_r31->unk_42 = var_r25;
                    HuSprPosSet(var_r31->unk_1C, 1, 0.0f, cursorYOfsTbl[var_r25]);
                }
                var_r31->unk_46 = var_r31->unk_44;
            }
        }
    }
}

static void CreateMGSelect(omObjData *object)
{
    mgSelect *temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s32 var_r28;
    s16 var_r26;
    s16 index2;
    u32 temp_r22;
    s32 temp_r21;
    AnimData *temp_r25;
    AnimData *temp_r23;
    float sp8[2];

    omSetStatBit(object, OM_STAT_MODEL_PAUSED);
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x48, MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    index2 = 0;
    temp_r30 = HuSprGrpCreate(3);
    temp_r31->unk_1C = temp_r30;
    HuSprGrpPosSet(temp_r30, 174.0f, 271.0f);
    temp_r25 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_E3SETUP, 0x21), MEMORY_DEFAULT_NUM));
    temp_r31->unk_00[index2] = temp_r25;
    temp_r29 = HuSprCreate(temp_r25, 0x7540, 0);
    HuSprGrpMemberSet(temp_r30, index2, temp_r29);
    index2++;
    temp_r25 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_E3SETUP, 0x27), MEMORY_DEFAULT_NUM));
    temp_r31->unk_00[index2] = temp_r25;
    temp_r29 = HuSprCreate(temp_r25, 0x64, 0);
    HuSprGrpMemberSet(temp_r30, index2, temp_r29);
    HuSprScaleSet(temp_r30, index2, 1.1f, 1.0f);
    HuSprTPLvlSet(temp_r30, index2, 0.5f);
    temp_r31->unk_42 = 0;
    HuSprPosSet(temp_r30, index2, 0.0f, cursorYOfsTbl[temp_r31->unk_42]);
    index2++;
    temp_r25 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_E3SETUP, 0x35), MEMORY_DEFAULT_NUM));
    temp_r31->unk_00[index2++] = temp_r25;
    temp_r23 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_E3SETUP, 0x36), MEMORY_DEFAULT_NUM));
    temp_r31->unk_00[index2++] = temp_r23;
    temp_r30 = HuSprGrpCreate(2);
    temp_r31->unk_1E = temp_r30;
    HuSprGrpPosSet(temp_r30, 174.0f, 128.0f);
    temp_r29 = HuSprCreate(temp_r25, 4, 0);
    HuSprGrpMemberSet(temp_r30, 0, temp_r29);
    temp_r29 = HuSprCreate(temp_r23, 6, 0);
    HuSprGrpMemberSet(temp_r30, 1, temp_r29);
    HuSprTPLvlSet(temp_r30, 1, 0.7f);
    HuSprPosSet(temp_r30, 1, 0.0f, -4.0f);
    temp_r30 = HuSprGrpCreate(2);
    temp_r31->unk_20 = temp_r30;
    HuSprGrpPosSet(temp_r30, 174.0f, 414.0f);
    temp_r29 = HuSprCreate(temp_r25, 4, 1);
    HuSprGrpMemberSet(temp_r30, 0, temp_r29);
    temp_r29 = HuSprCreate(temp_r23, 6, 1);
    HuSprGrpMemberSet(temp_r30, 1, temp_r29);
    HuSprTPLvlSet(temp_r30, 1, 0.7f);
    HuSprPosSet(temp_r30, 1, 0.0f, -4.0f);

    temp_r21 = GWSystem.mg_next + 401;
    var_r26 = temp_r21;
    for (var_r28 = 0; var_r28 < 13;) {
        if (var_r26 != mgIdTbl[var_r28]) {
            var_r28++;
        } else {
            break;
        }
    }
    if (var_r28 >= 13) {
        var_r28 = 0;
    }
    mgDefault = var_r28;
    var_r26 = mgDefault;
    mgPicObj->work[0] = var_r26;
    temp_r31->unk_44 = var_r26;
    temp_r31->unk_46 = var_r26;

    for (var_r28 = 0; var_r28 < 5;) {
        if (var_r26 >= 13) {
            var_r26 = 0;
        }
        temp_r29 = HuWinCreate(36.0f, 237.0f + cursorYOfsTbl[var_r28], 0x128, 0x44, 0x4E20);
        temp_r31->unk_2E[var_r28] = temp_r29;
        temp_r31->unk_38[var_r28] = var_r28;
        HuWinBGTPLvlSet(temp_r29, 0.0f);
        HuWinMesSpeedSet(temp_r29, 0);
        temp_r22 = mgNameTbl[var_r26];
        HuWinAttrSet(temp_r29, 0x100);
        HuWinMesSizeCancelCRSet(1);
        HuWinMesMaxSizeGet(1, sp8, temp_r22);
        HuWinCenterPosSet(temp_r29, (296.0f - sp8[0]) / -2.0f, (68.0f - sp8[1]) / -2.0f);
        HuWinMesSet(temp_r29, temp_r22);
        var_r28++;
        var_r26++;
    }
    object->work[3] = 1;
    object->func = UpdateMGSelect;
}

static void UpdateMGPic(omObjData *object)
{
    mgPic *temp_r30 = (mgPic *)object->data;
    s16 temp_r29;

    if (object->work[1] != object->work[0]) {
        temp_r29 = temp_r30->unk_40;
        HuSprAttrSet(temp_r29, object->work[1], HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(temp_r29, object->work[0], HUSPR_ATTR_DISPOFF);
        object->work[1] = object->work[0];
    }
}

static void CreateMGPic(omObjData *object)
{
    mgPic *temp_r28;
    AnimData *temp_r3_2;
    s16 temp_r3;
    s32 var_r30;
    s32 index;
    s16 index2;
    s16 group;

    omSetStatBit(object, OM_STAT_MODEL_PAUSED);
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(mgPic), MEMORY_DEFAULT_NUM);
    temp_r28 = object->data;
    index2 = 0;
    temp_r3 = HuSprGrpCreate(14);
    temp_r28->unk_40 = temp_r3;
    HuSprGrpPosSet(temp_r3, 444.0f, 228.0f);

    for (var_r30 = 0; var_r30 < 13; var_r30++) {
        temp_r3_2 = HuSprAnimRead(HuDataReadNum(mgPicTbl[var_r30], MEMORY_DEFAULT_NUM));
        temp_r28->unk_00[var_r30] = temp_r3_2;
        group = HuSprCreate(temp_r3_2, 0x2710, 0);
        HuSprGrpMemberSet(temp_r3, var_r30, group);
        HuSprScaleSet(temp_r3, var_r30, 0.6f, 0.6f);
        HuSprAttrSet(temp_r3, var_r30, 4);
    }
    index2 = var_r30;
    temp_r3_2 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_E3SETUP, 0x22), MEMORY_DEFAULT_NUM));
    temp_r28->unk_00[index2] = temp_r3_2;
    group = HuSprCreate(temp_r3_2, 0x7540, 0);
    HuSprGrpMemberSet(temp_r3, index2, group);
    HuSprTPLvlSet(temp_r3, index2, 0.7f);
    index2++;
    object->work[1] = object->work[0];
    HuSprAttrReset(temp_r3, object->work[1], HUSPR_ATTR_DISPOFF);
    object->func = UpdateMGPic;
}

static void UpdateMGInterface(omObjData *object) { void *sp8 = object->data; }

static void CreateMGInterface(omObjData *object)
{
    mgInterface *unkStruct;
    s16 index;
    s16 group;
    s16 index2;
    AnimData *temp_r3_2;
    float sp8[2];

    omSetStatBit(object, OM_STAT_MODEL_PAUSED);
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(mgInterface), MEMORY_DEFAULT_NUM);
    unkStruct = object->data;
    index2 = 0;
    group = HuSprGrpCreate(1);
    unkStruct->group = group;
    HuSprGrpPosSet(group, 288.0f, 64.0f);
    temp_r3_2 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_E3SETUP, 0x24), MEMORY_DEFAULT_NUM));
    unkStruct->unk_00[index2] = temp_r3_2;
    index = HuSprCreate(temp_r3_2, 0x2710, 0);
    HuSprGrpMemberSet(group, 0, index);
    index2++;
    group = HuSprGrpCreate(1);
    unkStruct->group2 = group;
    HuSprGrpPosSet(group, 444.0f, 384.0f);
    temp_r3_2 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_E3SETUP, 0x23), MEMORY_DEFAULT_NUM));
    unkStruct->unk_00[index2] = temp_r3_2;
    index = HuSprCreate(temp_r3_2, 0x271A, 0);
    HuSprGrpMemberSet(group, 0, index);
    index2++;
    HuWinMesMaxSizeGet(1, sp8, "\013\016\r PRESS START");
    index = HuWinCreate(340.0f, 362.0f, sp8[0], sp8[1], 0);
    unkStruct->unk_2C = index;
    HuWinMesColSet(index, 0);
    HuWinBGTPLvlSet(index, 0.0f);
    HuWinMesSpeedSet(index, 0);
    HU_WIN_MES_SET_PTR(index, MAKE_MESSID_PTR("\013\016\r PRESS START"));
    object->func = UpdateMGInterface;
}

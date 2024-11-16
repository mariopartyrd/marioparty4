#include "game/board/char_wheel.h"
#include "game/audio.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/tutorial.h"
#include "game/board/ui.h"

#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        u8 unk00_field2 : 1;
        u8 unk00_field3 : 4;
    };
    s8 unk01;
    s8 unk02;
    u8 unk03;
    s16 unk04;
    s16 unk06;
    s16 unk08;
} CharWheelWork;

static void ExecCharWheel(omObjData *arg0);
static void InitCharWheel(CharWheelWork *arg0);
static void UpdateCharWheel(CharWheelWork *arg0);
static void StopCharWheel(CharWheelWork *arg0);
static void GrowCharWheel(CharWheelWork *arg0);
static void ShrinkCharWheel(CharWheelWork *arg0);
static void KillCharWheelSpr(void);
static void SetCharWheelChars(s32 arg0, s32 arg1, s8 *arg2);
static s32 GetInput(CharWheelWork *arg0);
static s16 GetComDelay(s32 arg0, s32 arg1);
static s32 GetComInput(CharWheelWork *arg0);

static s8 wheelChars[4];
static s16 comDelay;
static s16 wheelTimer;
static float wheelSpeed;
static s16 targetVal;
static float angleOfs;
static s16 targetF;
static omObjData *charWheelObj;

static s8 wheelPos = -1;
static s16 wheelSprGrp = -1;
static s32 wheelFXStat = -1;

static s32 wheelSprTbl[] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x36),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x38),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x38),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x38),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x37),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x37),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x37),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x37),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x3A),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x39)
};

static s8 wheelSprPrio[] = {
    0x3C, 0x50, 0x50, 0x50,
    0x50, 0x50, 0x50, 0x50,
    0x14, 0x1E,
    // wheelCharIconPrioTbl
    0x46, 0x46, 0x46, 0x46
};

static s32 wheelCharIconTbl[] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x3B),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x3C),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x3D),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x3E),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x3F),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x40),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x41),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x42)
};

s32 BoardCharWheelInit(s32 arg0, s32 arg1) {
    CharWheelWork *temp_r31;

    arg1 = 3;
    charWheelObj = omAddObjEx(boardObjMan, 0x104, 0, 0, -1, ExecCharWheel);
    temp_r31 = OM_GET_WORK_PTR(charWheelObj, CharWheelWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field2 = 0;
    temp_r31->unk00_field1 = (arg1 == 3) ? 0 : 1;
    temp_r31->unk01 = arg0;
    temp_r31->unk02 = 0;
    temp_r31->unk03 = 0;
    temp_r31->unk06 = 0;
    wheelSpeed = 18.0f;
    if (GWPlayer[temp_r31->unk01].com) {
        temp_r31->unk04 = 360;
    } else {
        temp_r31->unk04 = 3600;
    }
}

BOOL BoardCharWheelCheck(void) {
    return (charWheelObj != NULL) ? FALSE : TRUE;
}

void BoardCharWheelWait(void) {
    while (!BoardCharWheelCheck()) {
        HuPrcVSleep();
    }
}

s32 BoardCharWheelResultGet(void) {
    return wheelChars[wheelPos];
}

void BoardCharWheelSpeedSet(float arg0) {
    if (arg0 <= 0.0f) {
        arg0 = 18.0f;
    }
    wheelSpeed = arg0;
}

static void ExecCharWheel(omObjData *arg0) {
    CharWheelWork *temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, CharWheelWork);;
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        KillCharWheelSpr();
        #if VERSION_PAL
        if (wheelFXStat != -1) {
            HuAudFXStop(wheelFXStat);
            wheelFXStat = -1;
        }
        #endif
        charWheelObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (wheelTimer < temp_r31->unk04) {
        wheelTimer++;
    }
    switch (temp_r31->unk00_field3) {
        case 0:
            InitCharWheel(temp_r31);
            break;
        case 1:
            GrowCharWheel(temp_r31);
            break;
        case 2:
            UpdateCharWheel(temp_r31);
            break;
        case 3:
            StopCharWheel(temp_r31);
            break;
        case 4:
            ShrinkCharWheel(temp_r31);
            break;
    }
}

static void InitCharWheel(CharWheelWork *arg0) {
    GXColor spE;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    s32 var_r26;
    s16 var_r27;
    s16 var_r25;
    s16 i;
    s16 spA;
    s16 sp8;

    wheelChars[0] = wheelChars[1] = wheelChars[2] = wheelChars[3] = -1;
    wheelFXStat = -1;
    wheelTimer = 0;
    if (arg0->unk00_field1 != 0) {
        spA = 4;
        var_r26 = 4;
        temp_f27 = 45.0f;
    } else {
        spA = 3;
        var_r26 = 1;
        temp_f27 = 60.0f;
    }
    wheelSprGrp = HuSprGrpCreate(spA + 14);
    SetCharWheelChars(arg0->unk00_field1, arg0->unk01, wheelChars);
    if (GWPlayer[arg0->unk01].com) {
        comDelay = GetComDelay(arg0->unk01, arg0->unk00_field1);
        switch (GWPlayer[arg0->unk01].diff) {
            case 0:
                var_r27 = BoardRandMod(120);
                break;
            case 1:
                var_r27 = BoardRandMod(60);
                break;
            case 2:
                var_r27 = BoardRandMod(30);
                break;
            case 3:
                var_r27 = 0;
                break;
        }
        comDelay += var_r27;
        if (comDelay > 360.0f) {
            comDelay -= 360.0f;
        }
        if (comDelay < 0) {
            comDelay += 360.0f;
        }
    } else {
        comDelay = 0;
    }
    for (i = 0; i <= 9; i++) {
        BoardSpriteCreate(wheelSprTbl[i], wheelSprPrio[i], 0, &sp8);
        HuSprGrpMemberSet(wheelSprGrp, i, sp8);
        HuSprAttrSet(wheelSprGrp, i, 8);
    }
    if (arg0->unk00_field1 == 0) {
        for (i = 0; i < 4; i++) {
            HuSprAttrSet(wheelSprGrp, i + 4, 4);
        }
    } else {
        for (i = 0; i < 3; i++) {
            HuSprAttrSet(wheelSprGrp, i + 1, 4);
        }
    }
    for (i = 0; i < spA; i++) {
        var_r25 = GWPlayer[wheelChars[i]].character;
        BoardSpriteCreate(wheelCharIconTbl[var_r25], wheelSprPrio[i + 10], 0, &sp8);
        HuSprGrpMemberSet(wheelSprGrp, i + 10, sp8);
        HuSprAttrSet(wheelSprGrp, i + 10, 8);
    }
    HuSprPosSet(wheelSprGrp, 9, 3.0f, 3.0f);
    HuSprColorSet(wheelSprGrp, 9, 0x40, 0x40, 0x40);
    HuSprGrpPosSet(wheelSprGrp, 288.0f, 240.0f);
    HuSprGrpScaleSet(wheelSprGrp, 0.01f, 0.01f);
    OSs16tof32(&spA, &temp_f29);
    temp_f29 = 360.0f / temp_f29;
    for (i = 0; i < spA; i++) {
        if (arg0->unk00_field1 != 0) {
            switch (i) {
                case 0:
                    HuSprPosSet(wheelSprGrp, i + 10, 50.0f, -57.0f);
                    break;
                case 1:
                    HuSprPosSet(wheelSprGrp, i + 10, -50.0f, -57.0f);
                    break;
                case 2:
                    HuSprPosSet(wheelSprGrp, i + 10, 50.0f, 57.0f);
                    break;
                case 3:
                    HuSprPosSet(wheelSprGrp, i + 10, -50.0f, 57.0f);
                    break;
            }
        } else {
            switch (i) {
                case 0:
                    HuSprPosSet(wheelSprGrp, i + 10, 50.0f, -35.0f);
                    break;
                case 1:
                    HuSprPosSet(wheelSprGrp, i + 10, 0.0f, 57.0f);
                    break;
                case 2:
                    HuSprPosSet(wheelSprGrp, i + 10, -50.0f, -35.0f);
                    break;
            }
        }
        OSs16tof32(&i, &temp_f28);
        HuSprZRotSet(wheelSprGrp, var_r26 + i, temp_f29 * temp_f28);
        GWCharColorGet(GWPlayer[wheelChars[i]].character, &spE);
        HuSprColorSet(wheelSprGrp, var_r26 + i, spE.r, spE.g, spE.b);
    }
    for (i = 0; i < 3; i++) {
        if (wheelChars[i] == targetVal) {
            break;
        }
    }
    angleOfs = 120.0f * i;
    if (angleOfs > 180.0f) {
        angleOfs -= 360.0f;
    }
    arg0->unk00_field3 = 1;
}

static void UpdateCharWheel(CharWheelWork *arg0) {
    float var_f24;
    float var_f25;
    float var_f23;
    u32 var_r18;
    s16 temp_r20;
    s16 var_r19;
    s16 var_r17;

    OSs16tof32(&arg0->unk06, &var_f24);
    OSs16tof32(&arg0->unk08, &var_f25);
    var_f24 = var_f24 * 0.0625f;
    var_f25 = var_f25 * 0.0625f;
    if (arg0->unk00_field2 == 0) {
        if (var_f25 < 18.0f) {
            var_f25 += 0.7f;
            if (var_f25 > wheelSpeed) {
                var_f25 = wheelSpeed;
            }
        } else {
            var_r18 = GetInput(arg0);
            if (var_r18 & 0x100) {
                arg0->unk00_field2 = 1;
            }
        }
    } else {
        OSf32tos16(&var_f24, &temp_r20);
        if (arg0->unk00_field1 == 0) {
            var_r19 = 120;
        } else {
            var_r19 = 90;
        }
        temp_r20 %= var_r19;
        if (var_f25 < 0.5f && (temp_r20 < 2 || temp_r20 >= var_r19 - 2)) {
            var_f25 += var_f25 / 2;
        }
        var_f25 *= 0.92f;
    }
    var_f23 = 8191.0f - 8191.0f * (var_f25 / wheelSpeed);
    OSf32tos16(&var_f23, &var_r17);
    #if VERSION_PAL
    if(wheelFXStat != -1) {
        HuAudFXPitchSet(wheelFXStat, -var_r17);
    }
    #else
    HuAudFXPitchSet(wheelFXStat, -var_r17);
    #endif
    if (var_f25 > -0.0000001f && var_f25 < 0.0000001f) {
        arg0->unk00_field3 = 3;
        if (wheelFXStat != -1) {
            HuAudFXStop(wheelFXStat);
            wheelFXStat = -1;
        }
        HuAudFXPlay(0x30B);
    }
    var_f24 += var_f25;
    if (var_f24 > 360.0f) {
        var_f24 -= 360.0f;
    }
    HuSprZRotSet(wheelSprGrp, 8, var_f24);
    HuSprZRotSet(wheelSprGrp, 9, var_f24);
    var_f24 *= 16.0f;
    var_f25 *= 16.0f;
    OSf32tos16(&var_f24, &arg0->unk06);
    OSf32tos16(&var_f25, &arg0->unk08);
}

static void StopCharWheel(CharWheelWork *arg0) {
    u8 var_r30;

    if (arg0->unk03 == 0) {
        arg0->unk06 >>= 4;
        if (arg0->unk00_field1 == 0) {
            wheelPos = arg0->unk06 / 120;
        } else {
            wheelPos = arg0->unk06 / 90;
        }
    }
    var_r30 = arg0->unk03 % 6;
    if (var_r30 < 3) {
        HuSprAttrSet(wheelSprGrp, wheelPos + 10, 4);
    } else {
        HuSprAttrReset(wheelSprGrp, wheelPos + 10, 4);
    }
    if (arg0->unk03 < 90) {
        arg0->unk03++;
    } else {
        HuSprAttrReset(wheelSprGrp, wheelPos + 10, 4);
        arg0->unk00_field3 = 4;
    }
}

static void GrowCharWheel(CharWheelWork *arg0) {
    float temp_f30;

    if (arg0->unk02 < 90) {
        arg0->unk02 += 3;
    } else {
        if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
            BoardTutorialHookExec(0x14, 0);
        }
        arg0->unk02 = 90;
        arg0->unk00_field3 = 2;
        #if VERSION_PAL
        if(!BoardIsKill()) {
            wheelFXStat = HuAudFXPlay(0x30A);
        }
        #else
        wheelFXStat = HuAudFXPlay(0x30A);
        #endif
        
    }
    OSs8tof32(&arg0->unk02, &temp_f30);
    HuSprGrpScaleSet(wheelSprGrp, sind(temp_f30), sind(temp_f30));
}

static void ShrinkCharWheel(CharWheelWork *arg0) {
    float temp_f30;

    if (arg0->unk02 > 0) {
        arg0->unk02 -= 3;
    } else {
        arg0->unk02 = 0;
        arg0->unk00_field0 = 1;
        arg0->unk00_field3 = -1;
        targetF = 0;
    }
    OSs8tof32(&arg0->unk02, &temp_f30);
    HuSprGrpScaleSet(wheelSprGrp, sind(temp_f30), sind(temp_f30));
}

static void KillCharWheelSpr(void) {
    if (wheelSprGrp != -1) {
        HuSprGrpKill(wheelSprGrp);
        wheelSprGrp = -1;
    }
}

static void SetCharWheelChars(s32 arg0, s32 arg1, s8 *arg2) {
    s32 var_r29;
    s32 var_r28;
    s32 var_r31;
    s32 var_r30;

    for (var_r28 = var_r29 = 0; var_r29 < 4; var_r29++) {
        if (var_r29 == arg1 && arg0 == 0) {
            continue;
        }
        do {
            do {
                var_r30 = BoardRandMod(4);
            } while (var_r30 == arg1 && arg0 == 0);
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (var_r30 == arg2[var_r31]) {
                    var_r30 = -1;
                    break;
                }
            }
        } while (var_r30 == -1);
        arg2[var_r28] = var_r30;
        var_r28++;
    }
}

static s32 GetInput(CharWheelWork *arg0) {
    CharWheelWork *var_r27;
    float temp_f26;
    float temp_f27;
    float var_f28;
    float var_f29;
    s32 var_r28;

    if (wheelTimer >= arg0->unk04) {
        return 0x100;
    }
    if (!GWPlayer[arg0->unk01].com) {
        var_r28 = HuPadBtnDown[GWPlayer[arg0->unk01].port];
        return  var_r28;
    }
    var_r28 = GetComInput(arg0);
    if (targetF != 0) {
        var_r27 = OM_GET_WORK_PTR(charWheelObj, CharWheelWork);
        OSs16tof32(&var_r27->unk06, &temp_f26);
        OSs16tof32(&var_r27->unk08, &temp_f27);
        temp_f26 = temp_f26 * 0.0625f;
        temp_f27 = temp_f27 * 0.0625f;
        var_f29 = temp_f26 + 46.0f * temp_f27;
        var_f29 = fmod(var_f29, 360.0);
        if (var_f29 > 180.0f) {
            var_f29 -= 360.0f;
        }
        var_f28 = angleOfs - var_f29;
        if (var_f28 >= 360.0f) {
            var_f28 += 360.0f;
        }
        if (var_f28 >= 0.0f && var_f28 < 120.0f - 2.0f * temp_f27) {
            var_r28 = 0x100;
        } else {
            var_r28 = 0;
        }
        OSReport("%f %f : %f %f\n", temp_f26, temp_f27, var_f29, var_f28);
    }
    return var_r28;
}

void BoardCharWheelTargetSet(s16 arg0) {
    targetF = 1;
    targetVal = arg0;
}

static s16 GetComDelay(s32 arg0, s32 arg1) {
    float var_f30;
    s16 var_r26;
    s32 var_r27;
    s32 var_r28;
    s32 i;

    var_r28 = BoardComFarPlayerFind();
    if (var_r28 == -1 || var_r28 == arg0) {
        do {
            var_r28 = BoardRandMod(4);
        } while (var_r28 == arg0);
    }
    if (arg1 != 0) {
        var_r27 = 4;
    } else {
        var_r27 = 3;
    }
    for (var_r26 = i = 0; i < var_r27; i++) {
        if (var_r28 == wheelChars[i]) {
            var_f30 = i * (360 / var_r27);
            var_f30 += 45.0f;
            var_f30 -= 180.0f;
            if (var_f30 < 0.0f) {
                var_f30 += 360.0f;
            }
            if (var_f30 >= 360.0f) {
                var_f30 -= 360.0f;
            }
            OSf32tos16(&var_f30, &var_r26);
            break;
        }
    }
    return var_r26;
}

static s32 GetComInput(CharWheelWork *arg0) {
    s16 temp_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    temp_r31 = (arg0->unk06 >> 4);
    var_r27 = (arg0->unk00_field1 != 0) ? 90 : 120;
    var_r28 = comDelay;
    var_r29 = comDelay + var_r27;
    if (temp_r31 >= var_r28 && temp_r31 < var_r29) {
        return 0x100;
    } else {
        return 0;
    }
}

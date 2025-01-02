#include "REL/m424Dll.h"

#include "ext_math.h"
#include "string.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/pad.h"
#include "game/sprite.h"

// STRUCT
typedef struct _M424DllBallStruct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    char unkB[0x1];
    u8 unkC;
    u8 unkD;
    u8 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    Vec unk34;
    Vec unk40;
    Vec unk4C;
    Vec unk58;
    void* unk64; // sizeof 0x40
    char unk68[0x3C];
    u8 unkA4;
    void* unkA8; // sizeof 0x40
    char unkAC[0x3C];
    s32 unkE8;
    s32 unkEC;
} M424DllBallStruct; // sizeof 0xF0

typedef struct _M424DllBallStruct2 {
    omObjData* unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u16 unk8;
    u16 unkA;
    Mtx unkC;
    Vec unk3C;
    Vec unk48;
    Vec unk54;
    Vec unk60;
    Vec unk6C;
    Vec unk78;
    Vec unk84;
    u8 unk90;
    u8 unk91;
} M424DllBallStruct2; // sizeof 0x94

typedef struct _M424DllBallStruct3 {
    u8 unk0;
    M424DllBallStruct2* unk4;
    M424DllBallStruct2* unk8;
} M424DllBallStruct3;

// BSS
omObjData* lbl_1_bss_5AC[4];
omObjData* lbl_1_bss_594[6];
M424DllBallStruct2 lbl_1_bss_60[9];
s32 lbl_1_data_5C;
u8 lbl_1_bss_58;

// PROTO
f32 fn_1_25C0(void);
void fn_1_28A0(omObjData* object);
void fn_1_2E3C(omObjData* object);
void fn_1_31C0(omObjData* object);
void fn_1_37FC(omObjData* object);
void fn_1_4220(omObjData* object);
void fn_1_469C(omObjData* object);
u8 fn_1_48D0(omObjData* object, u8, u8);
void fn_1_4A90(s16);
void fn_1_6038(void);
void* fn_1_6078(s32);
void fn_1_61AC(void);
s32 fn_1_627C(void);
void fn_1_6230(s16, f32*);
void fn_1_62D0(s32, u32*);
f32 fn_1_640C(f32, f32, f32);
f32 fn_1_6D10(Vec, Vec, f32, Vec, Vec, f32);
f32 fn_1_709C(Vec, Vec, f32, f32);
f32 fn_1_7420(Vec, Vec, f32, f32);
void fn_1_77C4(Vec, Vec, Vec, f32, Vec*, Vec*);
void fn_1_79FC(Vec*, Vec*, f32, Vec*, Vec*, f32, f32);
void fn_1_7CA0(Vec, Vec, f32, Vec*);
void fn_1_8924(u8, s32);
void fn_1_8AA8(s32, s32);


void fn_1_2720(Process* arg0) {
    u32 sp8[10];
    omObjData* var_r30;
    s32 temp_r28;
    s32 var_r29;
    s32 var_r31;

    temp_r28 = frand() & 0x1F;
    for (var_r31 = 0; var_r31 < temp_r28; var_r31++) {
        fn_1_627C();
    }
    fn_1_62D0(8, sp8);
    sp8[8] = 8;
    
    for (var_r31 = 0, var_r29 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayerCfg[var_r31].group != 0) {
            var_r30 = omAddObjEx(arg0, 0x3E, 3, 11, 0, fn_1_28A0);
            lbl_1_bss_5AC[var_r29] = var_r30;
            var_r30->work[0] = var_r31;
            var_r30->work[1] = sp8[var_r29];
            var_r29++;
        }
    }
    
    for (var_r31 = 0; var_r31 < 6; var_r29++, var_r31++) {
        var_r30 = omAddObjEx(arg0, 0x3F, 2U, 5U, 0, fn_1_4220);
        lbl_1_bss_594[var_r31] = var_r30;
        var_r30->work[0] = var_r31;
        var_r30->work[1] = sp8[var_r29];
    }
    Hu3DLayerHookSet(7, fn_1_4A90);
    fn_1_6038();
}

void fn_1_2880(void) {
    fn_1_61AC();
}

u32 lbl_1_data_150[11] = {
    0, 2,  3,  8,  10,
    9, 20, 22, 23, 24,
    0x370021
};

void fn_1_28A0(omObjData* object) {
    Vec sp8;
    f32 temp_f31;
    f32 temp_f30;
    M424DllBallStruct* var_r31;
    s32 var_r29;
    s32 temp_r28;
    s32 var_r27;

    object->data = var_r31 = fn_1_6078(0xF0);
    memset(var_r31, 0, 0xF0);
    var_r31->unk0 = object->work[0];
    var_r31->unk1 = GWPlayerCfg[var_r31->unk0].character;
    var_r31->unk2 = GWPlayerCfg[var_r31->unk0].group;
    var_r31->unk3 = 0;
    var_r31->unk4 = GWPlayerCfg[var_r31->unk0].pad_idx;
    var_r31->unk5 = GWPlayerCfg[var_r31->unk0].iscom;
    var_r31->unk6 = GWPlayerCfg[var_r31->unk0].diff;
    var_r31->unk18 = var_r31->unk1A = 0;
    var_r31->unk30 = 1.0f;
    var_r31->unk7 = 1;
    var_r31->unkC = 1;
    var_r31->unkD = 0;
    var_r31->unkA = 0;
    var_r31->unkA4 = 0;
    var_r31->unkE = 0;
    memset(&var_r31->unk64, 0, 0x40);
    var_r31->unkE8 = 0;
    var_r31->unkEC = -1;
    temp_r28 = object->work[1];
    temp_f31 = 40.0f;
    temp_f31 = (temp_f31 * temp_r28) + (temp_f31 * (fn_1_627C() / 65536.0f)) + 105.0f;
    temp_f30 = 125.0f;
    temp_f30 = (temp_f30 * (temp_r28 & 1)) + (100.0f + (250.0f + (temp_f30 * (fn_1_627C() / 65536.0f))));
    sp8.x = temp_f30 * sind(temp_f31);
    sp8.y = 200.0f;
    sp8.z = temp_f30 * cosd(temp_f31);
    var_r31->unk34 = sp8;
    var_r31->unk4C.x = var_r31->unk4C.y = var_r31->unk4C.z = 0.0f;
    var_r31->unk40.x = var_r31->unk40.y = var_r31->unk40.z = 0.0f;
    var_r31->unk1C = 0.8f;
    var_r31->unk24 = var_r31->unk40.y;
    var_r31->unk2C = 1.0f;
    var_r31->unk28 = 0.0f;
    var_r31->unk20 = 0.0f;
    memset(&var_r31->unkA8, 0, 0x40);
    object->model[0] = var_r27 = CharModelCreate(var_r31->unk1, 8);
    Hu3DModelAttrSet(var_r27, 0x40000001);
    CharModelStepTypeSet(var_r31->unk1, 1);
    CharModelLayerSetAll(2);
    for (var_r29 = 0; var_r29 < 11; var_r29++) {
        if (lbl_1_data_150[var_r29] + 0xFFC90000 != 0x21) {
            object->motion[var_r29] = CharModelMotionCreate(var_r31->unk1, lbl_1_data_150[var_r29]);
        } else if (var_r31->unk1 == 5) {
            object->motion[var_r29] = Hu3DJointMotion(object->model[0], HuDataSelHeapReadNum(var_r31->unk1 + lbl_1_data_150[var_r29], 0x10000000, HEAP_DATA));
        } else {
            object->motion[var_r29] = object->motion[0];
        }
        if (lbl_1_data_150[var_r29] == 0x16 || lbl_1_data_150[var_r29] == 0x14) {
            CharModelVoiceEnableSet(var_r31->unk1, object->motion[var_r29], 0);
        }
    }
    CharModelMotionDataClose(var_r31->unk1);
    CharModelMotionSet(var_r31->unk1, object->motion[var_r31->unk18]);
    omSetTra(object, var_r31->unk34.x, var_r31->unk34.y, var_r31->unk34.z);
    omSetRot(object, var_r31->unk40.x, var_r31->unk40.y, var_r31->unk40.z);
    omSetSca(object, var_r31->unk1C, var_r31->unk1C, var_r31->unk1C);
    object->model[1] = fn_1_48D0(object, var_r31->unk1, 1);
    object->func = fn_1_2E3C;
}

void fn_1_2E38(void) {}

void fn_1_2E3C(omObjData* object) {
    s32 temp_r29;
    M424DllBallStruct* temp_r31;

    temp_r29 = object->model[0];
    temp_r31 = object->data;
    if (temp_r31->unk7 != 0) {
        if ((fn_1_FE0() == 4) && ((temp_r31->unk7 & 2) == 0)) {
            if (temp_r31->unk5 != 0) {
                fn_1_31C0(object);
            } else {
                temp_r31->unk10 = HuPadStkX[temp_r31->unk4];
                temp_r31->unk12 = HuPadStkY[temp_r31->unk4];
                temp_r31->unk14 = HuPadBtnDown[temp_r31->unk4];
                temp_r31->unk16 = HuPadBtn[temp_r31->unk4];
            }
        } else {
            temp_r31->unk10 = temp_r31->unk12 = 0;
            temp_r31->unk14 = temp_r31->unk16 = 0;
        }
        switch (temp_r31->unk8) {
            case 1:
                temp_r31->unkC = 1;
                if (fn_1_FE0() == 6) {
                    fn_1_8924(object->model[1], 5);
                }
                break;
            case 5:
                temp_r31->unkC = 0;
                temp_r31->unk1C *= 1.1f;
                if (temp_r31->unk1C >= 1.0f) {
                    temp_r31->unk1C = 1.0f;
                }
                temp_r31->unk40.y = fn_1_640C(temp_r31->unk40.y, 0.0f, 0.9f);
                if (temp_r31->unk34.y <= 200.0f) {
                    temp_r31->unk34.y = 200.0f;
                    temp_r31->unkC = 1;
                }
                Hu3DModelShadowSet(temp_r29);
                break;
            case 4:
                temp_r31->unk20 = 0.0f;
                temp_r31->unk4C.y = 0.0f;
                temp_r31->unk7 |= 2;
                break;
            case 6:
                temp_r31->unk10 = temp_r31->unk12 = 0;
                temp_r31->unk14 = temp_r31->unk16 = 0;
                temp_r31->unk1C = 1.0f;
                temp_r31->unk40.y = temp_r31->unk24 = 0.0f;
                if (temp_r31->unk34.y <= 50.0f) {
                    temp_r31->unkC = 1;
                    temp_r31->unk20 = 0.0f;
                    temp_r31->unk4C.y = 0.0f;
                    temp_r31->unk18 = 7;
                    temp_r31->unk34.x += fn_1_25C0();
                    temp_r31->unk34.y = 50.0f;
                } else {
                    temp_r31->unkC = 0;
                    temp_r31->unk20 += 3.0f;
                    temp_r31->unk4C.y += -1.46f;
                    if (temp_r31->unk1 != 5) {
                        temp_r31->unk18 = 6;
                    } else {
                        temp_r31->unk18 = 0xA;
                    }
                }
                break;
        }
        if ((fn_1_FE0() == 7) && ((temp_r31->unk7 & 2) == 0)) {
            temp_r31->unk18 = 8;
        }
        fn_1_37FC(object);
    }
}

void fn_1_31C0(omObjData* object) {
    Vec sp10;
    s32 spC;
    s16 sp8;
    f32 temp_f31;
    f32 temp_f30;
    M424DllBallStruct* temp_r31;
    s16 temp_r30;
    s16 var_r29;
    s16 var_r28;
    s16 var_r26;
    s16 var_r25;

    temp_r31 = object->data;
    spC = object->model[0];
    sp8 = temp_r31->unk18;
    temp_r30 = temp_r31->unk6;
    
    var_r29 = var_r28 = var_r26 = var_r25 = 0;
    switch (temp_r31->unk8) {
        case 2:
            break;
        case 1:
            if ((fn_1_627C() & 0x1F) == 0) {
                temp_f31 = atan2d(temp_r31->unk34.x, temp_r31->unk34.z);
                temp_f31 += ((30.0f - (5.0f * temp_r30)) * ((fn_1_627C() - 0x8000) / 32768.0f));
                sp10.x = sind(temp_f31);
                sp10.z = cosd(temp_f31);
                temp_f30 = fn_1_213C();
                if ((temp_f31 > 70.0f) && (temp_f31 < 100.0f)) {
                    if (temp_f30 < 0.0f) {
                        var_r29 = (-sp10.z * (48.0f + (6.0f * temp_r30)));
                        var_r28 = (-sp10.x * (48.0f + (6.0f * temp_r30)));
                    } else {
                        var_r29 = (sp10.z * (48.0f + (6.0f * temp_r30)));
                        var_r28 = (sp10.x * (48.0f + (6.0f * temp_r30)));
                    }
                } else if (temp_f30 < 0.0f) {
                    var_r29 = (sp10.z * (48.0f + (6.0f * temp_r30)));
                    var_r28 = (sp10.x * (48.0f + (6.0f * temp_r30)));
                } else {
                    var_r29 = (-sp10.z * (48.0f + (6.0f * temp_r30)));
                    var_r28 = (-sp10.x * (48.0f + (6.0f * temp_r30)));
                }
            } else {
                var_r29 = temp_r31->unk10;
                var_r28 = temp_r31->unk12;
            }
            break;
        case 3:
            if ((fn_1_627C() & 0x1F) == 0) {
                temp_f31 = 180.0f * ((fn_1_627C() - 0x8000) / 32768.0f);
                sp10.x = sind(temp_f31);
                sp10.z = cosd(temp_f31);
                var_r29 = (48.0f * sp10.x);
                var_r28 = (48.0f * sp10.z);
            } else {
                var_r29 = temp_r31->unk10;
                var_r28 = temp_r31->unk12;
            }
            break;
    }
    temp_r31->unk10 = var_r29;
    temp_r31->unk12 = var_r28;
    temp_r31->unk14 = var_r26;
    temp_r31->unk16 = var_r25;
}

void fn_1_37FC(omObjData* object) {
    s16 spA;
    s16 sp8;
    f32 var_f30;
    f32 var_f28;
    f32 temp_f27;
    M424DllBallStruct* temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 var_r28;
    s16 var_r27;
    s32 temp_r25;

    var_f30 = 1.0f;
    temp_r31 = object->data;
    temp_r25 = object->model[0];
    var_r28 = temp_r31->unk18;
    temp_r31->unk58 = temp_r31->unk34;
    temp_r30 = temp_r31->unk10;
    temp_r29 = temp_r31->unk12;
    spA = temp_r31->unk14;
    sp8 = temp_r31->unk16;
    switch (temp_r31->unk18) {
        case 0:
        case 1:
        case 2:
            temp_r31->unk20 = (0.025f * sqrtf((temp_r30 * temp_r30) + (temp_r29 * temp_r29)));
            if (temp_r31->unk20 > 0.01f) {
                if (temp_r31->unk20 >= 6.0f) {
                    var_r28 = 2;
                    var_r27 = 1;
                } else {
                    var_r28 = 1;
                    var_r27 = 1;
                }
                var_f28 = atan2d(temp_r30, -temp_r29);
                temp_r31->unk40.y = fn_1_640C(temp_r31->unk40.y, var_f28, 0.5f);
                temp_r31->unk24 = temp_r31->unk40.y;
                temp_r31->unk28++;
                if (temp_r31->unk28 >= (0.5f * temp_r31->unk2C)) {
                    temp_r31->unk28 -= 0.5f * temp_r31->unk2C;
                }
                temp_r31->unk20 *= 1.0 + 0.25 * cosd(90.0f * (temp_r31->unk28 / (0.5f * temp_r31->unk2C)));
            } else {
                temp_r31->unk28 = 0.0f;
                temp_r31->unk20 = 0.0f;
                var_r28 = 0;
                var_r27 = 1;
            }
            if (temp_r31->unkC != 0) {
                temp_r31->unk4C.y = -2.4333334f;
            } else {
                temp_r31->unk4C.y += -2.4333334f;
            }
            break;
        case 3:
            var_r27 = 0;
            if ((Hu3DData[temp_r25].unk_0C == -1) && (CharModelMotionEndCheck(temp_r31->unk1) != 0)) {
                temp_r31->unk4C.y += -2.4333334f;
            } else {
                temp_r31->unk4C.y = 0.0f;
            }
            if (temp_r31->unkC != 0) {
                if (temp_r31->unkD != 0) {
                    temp_r31->unk4C.y = 0.0f;
                    temp_r31->unkD = 0U;
                    var_r28 = 5;
                    var_r27 = 0;
                } else {
                    temp_r31->unk4C.y *= -0.1f;
                    temp_r31->unkC = 0U;
                    var_r28 = 4;
                    var_r27 = 0;
                }
            }
            break;
        case 4:
            temp_r31->unk4C.y += -2.4333334f;
            if ((temp_r31->unkC != 0) && (CharModelMotionEndCheck(temp_r31->unk1) != 0)) {
                var_r28 = 5;
                var_r27 = 0;
            }
            break;
        case 5:
            if (CharModelMotionEndCheck(temp_r31->unk1) != 0) {
                var_r28 = 0;
                var_r27 = 1;
            }
            break;
        case 6:
            var_r28 = 6;
            var_r27 = 0;
            if (temp_r31->unk1 == 7) {
                var_f30 = 0.85f;
                temp_r31->unk30 = 0.9f;
            }
            break;
        case 7:
            var_r28 = 7;
            var_r27 = 1;
            if (temp_r31->unkE8 == 1) {
                temp_r31->unkEC = HuAudCharVoicePlay(temp_r31->unk1, 0x11A);
            } else if ((temp_r31->unkE8 > 90.0f) && (temp_r31->unkEC != -1)) {
                HuAudFXStop(temp_r31->unkEC);
                temp_r31->unkEC = -1;
            }
            temp_r31->unkE8++;
            break;
        case 8:
        case 9:
            var_r27 = 0;
            temp_r31->unk4C.y = -2.4333334f;
            break;
        case 10:
            var_r28 = 10;
            var_r27 = 4;
            var_f30 = 0.8f;
            temp_r31->unk30 = 0.85f;
            if ((var_r28 == temp_r31->unk18) && (Hu3DMotionShiftIDGet(temp_r25) != -1)) {
                temp_f27 = Hu3DMotionMaxTimeGet(temp_r25);
                if (Hu3DMotionTimeGet(temp_r25) >= temp_f27) {
                    var_r28 = 7;
                    var_r27 = 1;
                }
            }
            break;
    }
    if ((temp_r31->unk7 & 4) != 0) {
        if ((temp_r31->unkA & 2) != 0) {
            Hu3DModelAttrSet(temp_r25, 1);
        } else {
            Hu3DModelAttrReset(temp_r25, 1);
        }
        if (--temp_r31->unkA == 0) {
            temp_r31->unk7 &= ~4;
        }
    }
    temp_r31->unk4C.x = temp_r31->unk20 * sind(temp_r31->unk24);
    temp_r31->unk4C.z = temp_r31->unk20 * cosd(temp_r31->unk24);
    temp_r31->unk34.x += temp_r31->unk4C.x;
    if (temp_r31->unkC == 0) {
        temp_r31->unk34.y += temp_r31->unk4C.y;
    }
    temp_r31->unk34.z += temp_r31->unk4C.z;
    if (var_r28 != temp_r31->unk1A) {
        temp_r31->unk1A = var_r28;
        temp_r31->unk18 = var_r28;
        CharModelMotionShiftSet(temp_r31->unk1, object->motion[temp_r31->unk18], 0.0f, 8.0f, var_r27);
        temp_r31->unk2C = CharModelMotionMaxTimeGet(temp_r31->unk1);
    }
    if (temp_r31->unk30 != var_f30) {
        if (var_f30 > temp_r31->unk30) {
            if ((temp_r31->unk30 += 0.05f) > var_f30) {
                temp_r31->unk30 = var_f30;
            }
        }
        if (var_f30 < temp_r31->unk30) {
            if ((temp_r31->unk30 -= 0.05f) < var_f30) {
                temp_r31->unk30 = var_f30;
            }
        }
        temp_r31->unk1C = temp_r31->unk30;
    }
    omSetTra(object, temp_r31->unk34.x, temp_r31->unk34.y, temp_r31->unk34.z);
    omSetRot(object, temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z);
    omSetSca(object, temp_r31->unk1C, temp_r31->unk1C, temp_r31->unk1C);
}

void fn_1_4220(omObjData* object) {
    s32 sp14[3] = { 0x370013, 0x370014, 0x370015 };
    Vec sp8;
    f32 temp_f31;
    f32 temp_f30;
    M424DllBallStruct* var_r31;
    s32 var_r29;
    s32 temp_r28;
    s32 var_r27;

    object->model[0] = var_r27 = Hu3DModelCreateFile(0x370012);
    
    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        object->motion[var_r29] = Hu3DJointMotion(var_r27, HuDataSelHeapReadNum(sp14[var_r29], 0x10000000, HEAP_DATA));
    }
    Hu3DMotionSet(var_r27, object->motion[0]);
    Hu3DModelAttrSet(var_r27, 0x40000001);
    var_r31 = fn_1_6078(0xF0);
    object->data = var_r31;
    memset(var_r31, 0, 0xF0);
    var_r31->unk0 = object->work[0];
    var_r31->unk1 = 0xFF;
    var_r31->unk2 = 0xFF;
    var_r31->unk3 = 0;
    var_r31->unk4 = 0xFF;
    var_r31->unk5 = 0xFF;
    var_r31->unk6 = 0xFF;
    var_r31->unk18 = var_r31->unk1A = 0;
    var_r31->unk7 = 1;
    var_r31->unkC = 1;
    var_r31->unkD = 0;
    var_r31->unkA = 0;
    var_r31->unkA4 = 0;
    var_r31->unkE = 0;
    memset(&var_r31->unk64, 0, 0x40);
    temp_r28 = object->work[1];
    if (temp_r28 == 8) {
        sp8.x = 350.0f;
        sp8.y = 200.0f;
        sp8.z = 50.0f;
    } else {
        temp_f31 = 40.0f;
        temp_f31 = 105.0f + ((temp_f31 * temp_r28) + (temp_f31 * (fn_1_627C() / 65536.0f)));
        temp_f30 = 125.0f;
        temp_f30 = (temp_f30 * (temp_r28 & 1)) + (100.0f + (250.0f + (temp_f30 * (fn_1_627C() / 65536.0f))));
        sp8.x = temp_f30 * sind(temp_f31);
        sp8.y = 200.0f;
        sp8.z = temp_f30 * cosd(temp_f31);
    }
    var_r31->unk34 = sp8;
    var_r31->unk4C.x = var_r31->unk4C.y = var_r31->unk4C.z = 0.0f;
    var_r31->unk40.x = var_r31->unk40.y = var_r31->unk40.z = 0.0f;
    var_r31->unk24 = var_r31->unk40.y;
    var_r31->unk2C = 1.0f;
    var_r31->unk28 = 0.0f;
    var_r31->unk20 = 0.0f;
    memset(&var_r31->unkA8, 0, 0x40);
    omSetTra(object, var_r31->unk34.x, var_r31->unk34.y, var_r31->unk34.z);
    omSetRot(object, var_r31->unk40.x, var_r31->unk40.y, var_r31->unk40.z);
    omSetSca(object, 0.8f, 0.8f, 0.8f);
    object->model[1] = fn_1_48D0(object, 8, 0);
    object->func = fn_1_469C;
}

fn_1_4698(void) {}

void fn_1_469C(omObjData* object) {
    s32 temp_r27;
    s16 var_r28;
    s16 var_r30;
    M424DllBallStruct* temp_r31;

    temp_r31 = object->data;
    temp_r27 = object->model[0];
    var_r30 = temp_r31->unk18;
    temp_r31->unk58 = temp_r31->unk34;
    
    temp_r31->unk4C.x = temp_r31->unk4C.z = 0.0f;
    switch (temp_r31->unk8) {                        /* irregular */
        case 3:
            var_r30 = 2;
            var_r28 = 1;
            temp_r31->unk4C.y = -2.4333334f;
            if ((fn_1_627C() & 0xF) == 0) {
                temp_r31->unk24 = (180.0f * ((fn_1_627C() - 0x8000) / 32768.0f));
            }
            break;
        case 1:
            var_r30 = 1;
            var_r28 = 1;
            temp_r31->unk4C.y = -2.4333334f;
            if ((fn_1_627C() & 0x3F) == 0) {
                temp_r31->unk24 = (180.0f * ((fn_1_627C() - 0x8000) / 32768.0f));
            }
            break;
        case 2:
            var_r30 = 0;
            var_r28 = 1;
            
            temp_r31->unk4C.x = temp_r31->unk4C.z = 0.0f;
            temp_r31->unk4C.y += -0.97333336f;
            break;
    }
    temp_r31->unk40.y = fn_1_640C(temp_r31->unk40.y, temp_r31->unk24, 0.95f);
    if (var_r30 != temp_r31->unk1A) {
        temp_r31->unk1A = var_r30;
        temp_r31->unk18 = var_r30;
        Hu3DMotionShiftSet(temp_r27, object->motion[temp_r31->unk18], 0.0f, 8.0f, (u32) var_r28);
        temp_r31->unk2C = Hu3DMotionMaxTimeGet(temp_r31->unk1);
    }
}

u8 fn_1_48D0(omObjData* object, u8 arg1, u8 arg2) {
    M424DllBallStruct2* temp_r31;
    s32 var_r30;
    s32 var_r28;

    var_r28 = lbl_1_bss_58;
    lbl_1_bss_58++;
    temp_r31 = &lbl_1_bss_60[var_r28];
    memset(temp_r31, 0, 0x94);
    temp_r31->unk0 = object;
    var_r30 = Hu3DModelCreate(HuDataSelHeapReadNum((arg1 * 2) + 0x370000, 0x10000000, HEAP_DATA));
    temp_r31->unk8 = var_r30;
    Hu3DModelLayerSet(var_r30, 2);
    Hu3DModelShadowMapSet(var_r30);
    Hu3DModelAttrSet(var_r30, 0x20000U);
    Hu3DModelHiliteMapSet(var_r30, HuSprAnimRead(HuDataReadNum(0x370016, 0x10000000)));
    var_r30 = Hu3DModelCreate(HuDataSelHeapReadNum((arg1 * 2) + 0x370001, 0x10000000, HEAP_DATA));
    temp_r31->unkA = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelShadowSet(var_r30);
    PSMTXIdentity(temp_r31->unkC);
    temp_r31->unk3C.x = object->trans.x;
    temp_r31->unk3C.y = 100.0f + object->trans.y;
    temp_r31->unk3C.z = object->trans.z;
    temp_r31->unk54 = temp_r31->unk3C;
    temp_r31->unk6C.x = temp_r31->unk6C.y = temp_r31->unk6C.z = 0.0f;
    temp_r31->unk5 = arg2;
    temp_r31->unk4 = 2;
    temp_r31->unk6 = 0;
    if (arg2 != 0) {
        temp_r31->unk91 = arg1;
    } else {
        temp_r31->unk91 = 0xFFU;
    }
    return var_r28;
}

void fn_1_4A90(s16 arg0) {
    Mtx sp50;
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    f32 var_f31;
    f32 var_f30;
    M424DllBallStruct2* var_r31;
    M424DllBallStruct* temp_r30;
    s32 var_r29;

    if (omPauseChk() == 0) {
        var_r31 = lbl_1_bss_60;
        var_f31 = fn_1_213C();
        mtxRot(sp20, 0.0f, var_f31, 0.0f);
        
        for (var_r29 = 0; var_r29 < lbl_1_bss_58; var_r29++, var_r31++) {
            temp_r30 = var_r31->unk0->data;
            var_r31->unk48 = var_r31->unk54;
            var_r31->unk60 = var_r31->unk48;
            var_r31->unk78.x = var_r31->unk78.y = var_r31->unk78.z = 0.0f;
            switch (var_r31->unk4) {
                case 1:
                    PSMTXTrans(sp50, var_r31->unk3C.x, var_r31->unk3C.y, var_r31->unk3C.z);
                    PSMTXConcat(sp20, sp50, sp50);
                    var_r31->unk48.x = sp50[0][3];
                    var_r31->unk48.y = sp50[1][3];
                    var_r31->unk48.z = sp50[2][3];
                    PSVECSubtract(&var_r31->unk48, &var_r31->unk3C, &var_r31->unk78);
                    PSVECSubtract(&var_r31->unk3C, &var_r31->unk54, &sp14);
                    PSVECAdd(&temp_r30->unk4C, &sp14, &var_r31->unk84);
                    PSVECAdd(&var_r31->unk84, &var_r31->unk78, &var_r31->unk6C);
                    var_r31->unk84.y = 0.0f;
                    var_r31->unk4 = 2;
                    break;
                case 3:
                    PSVECSubtract(&var_r31->unk3C, &var_r31->unk60, &var_r31->unk6C);
                    var_r31->unk84 = var_r31->unk6C;
                    break;
                case 4:
                    var_r31->unk6C.y += -2.4333334f;
                    var_r31->unk6C.x = var_r31->unk6C.z = 0.0f;
                    var_r31->unk84 = var_r31->unk6C;
                    break;
                case 2:
                    var_r31->unk6C.y = 0.0f;
                    var_r31->unk6C.x = var_r31->unk6C.z = 0.0f;
                    PSVECSubtract(&var_r31->unk3C, &var_r31->unk54, &sp14);
                    PSVECAdd(&temp_r30->unk4C, &sp14, &var_r31->unk84);
                    var_r31->unk6C = var_r31->unk84;
                    break;
                case 5:
                    if ((var_r31->unk6 & 2) != 0) {
                        Hu3DModelAttrSet(var_r31->unk8, 1);
                        Hu3DModelAttrSet(var_r31->unkA, 1);
                    } else {
                        Hu3DModelAttrReset(var_r31->unk8, 1);
                        Hu3DModelAttrReset(var_r31->unkA, 1);
                    }
                    if (++var_r31->unk6 >= 0x3C) {
                        var_r31->unk4 = 6;
                    }
                    break;
                default:
                    var_r31->unk6C.x = var_r31->unk6C.y = var_r31->unk6C.z = 0.0f;
                    break;
            }
        }
        fn_1_8AA8(0x20, 1);
        var_r31 = lbl_1_bss_60;
        for (var_r29 = 0; var_r29 < lbl_1_bss_58; var_r29++, var_r31++) {
            if (var_r31->unk4 != 6) {
                if (var_r31->unk4 == 1) {
                    PSVECSubtract(&var_r31->unk3C, &var_r31->unk48, &sp14);
                    sp8.x = sp14.z;
                    sp8.y = 0.0f;
                    sp8.z = -sp14.x;
                    var_f30 = PSVECMag(&sp8);
                    if (var_f30 > 0.01f) {
                        PSMTXRotAxisRad(sp50, &sp8, MTXDegToRad(var_f30));
                        PSMTXConcat(sp20, sp50, sp50);
                    } else {
                        PSMTXCopy(sp20, sp50);
                    }
                    PSMTXConcat(sp50, var_r31->unkC, var_r31->unkC);
                    fn_1_6230(var_r31->unk8, var_r31->unkC[0]);
                    fn_1_6230(var_r31->unkA, var_r31->unkC[0]);
                }
                if (var_r31->unk3C.y < 250.0f) {
                    var_r31->unk3C.y = 250.0f;
                    var_r31->unk4 = 6;
                    Hu3DModelAttrSet(var_r31->unk8, 1);
                    Hu3DModelAttrSet(var_r31->unkA, 1);
                }
                Hu3DModelPosSet(var_r31->unk8, var_r31->unk3C.x, var_r31->unk3C.y, var_r31->unk3C.z);
                Hu3DModelPosSet(var_r31->unkA, var_r31->unk3C.x, var_r31->unk3C.y, var_r31->unk3C.z);
                PSVECSubtract(&var_r31->unk3C, &var_r31->unk54, &sp14);
                var_r31->unk6C = sp14;
                var_r31->unk54 = var_r31->unk3C;
                temp_r30 = var_r31->unk0->data;
                temp_r30->unk8 = var_r31->unk4;
                temp_r30->unk40.y += var_f31;
                if (var_r31->unk4 != 5) {
                    temp_r30->unk34 = var_r31->unk3C;
                    temp_r30->unk34.y -= 80.0f;
                    omSetTra(var_r31->unk0, temp_r30->unk34.x, temp_r30->unk34.y, temp_r30->unk34.z);
                    omSetRot(var_r31->unk0, temp_r30->unk40.x, temp_r30->unk40.y, temp_r30->unk40.z);
                }
            }
        }
    }
}

void fn_1_5018(void) {
    M424DllBallStruct3 sp27C[32];
    Vec sp270;
    Vec sp264;
    Vec sp258;
    Vec sp24C;
    Vec sp240;
    Vec sp234;
    Vec sp228;
    f32 var_f31;
    f32 var_f30;
    f32 var_f29;
    f32 temp_f28;
    M424DllBallStruct2* var_r31;
    M424DllBallStruct2* var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    var_r31 = &lbl_1_bss_60[0];
    for (var_r28 = 0; var_r28 < lbl_1_bss_58; var_r28++, var_r31++) {
        var_r31->unk90 = 1;
    }
    
    for (var_r26 = 0, var_f29 = 1.0f; var_r26 < 0x80; var_f29 -= var_f30, var_r26++) {
        var_r29 = 0;
        var_f30 = var_f29;
        var_r31 = &lbl_1_bss_60[0];
        for (var_r28 = 0; var_r28 < lbl_1_bss_58; var_r28++, var_r31++) {
            if ((var_r31->unk90 != 0) && (var_r31->unk4 < 4U)) {
                var_r31->unk90 = 0;
                if (var_r31->unk4 < 3) {
                    if (var_r31->unk6C.y < 0.0f) {
                        var_f31 = (200.0f - (var_r31->unk60.y - 100.0f)) / var_r31->unk6C.y;
                        if (var_f31 <= var_f29) {
                            if (var_f31 < 0.0f) {
                                var_f31 = 0.0f;
                            }
                            var_r31->unk90 = 1;
                            if (var_f31 <= var_f30) {
                                if (var_f31 < var_f30) {
                                    var_r29 = 0;
                                }
                                sp27C[var_r29].unk0 = 0;
                                sp27C[var_r29].unk4 = var_r31;
                                sp27C[var_r29].unk8 = 0;
                                var_r29++;
                                var_f30 = var_f31;
                            }
                        }
                    }
                    if (var_r31->unk4 == 1) {
                        var_f31 = fn_1_7420(var_r31->unk60, var_r31->unk84, 100.0f, 700.0f);
                    } else {
                        var_f31 = fn_1_7420(var_r31->unk60, var_r31->unk6C, 100.0f, 700.0f);
                    }
                    if (var_f31 >= 0.0f && var_f31 <= var_f29) {
                        var_r31->unk90 = 1;
                        if (var_f31 <= var_f30) {
                            if (var_f31 < var_f30) {
                                var_r29 = 0;
                            }
                            sp27C[var_r29].unk0 = 1;
                            sp27C[var_r29].unk4 = var_r31;
                            sp27C[var_r29].unk8 = 0;
                            var_r29++;
                            var_f30 = var_f31;
                        }
                    }
                    if (var_r31->unk4 == 1) {
                        var_f31 = fn_1_709C(var_r31->unk60, var_r31->unk84, 100.0f, 250.0f);
                    } else {
                        var_f31 = fn_1_709C(var_r31->unk60, var_r31->unk6C, 100.0f, 250.0f);
                    }
                    if (var_f31 >= 0.0f && var_f31 <= var_f29) {
                        var_r31->unk90 = 1;
                        if (var_f31 <= var_f30) {
                            if (var_f31 < var_f30) {
                                var_r29 = 0;
                            }
                            sp27C[var_r29].unk0 = 2;
                            sp27C[var_r29].unk4 = var_r31;
                            sp27C[var_r29].unk8 = 0;
                            var_r29++;
                            var_f30 = var_f31;
                        }
                    }
                }
                
                var_r30 = lbl_1_bss_60;
                for (var_r25 = 0; var_r25 < lbl_1_bss_58; var_r25++, var_r30++) {
                    if ((var_r31 != var_r30) && (var_r30->unk4 < 4)) {
                        if ((var_r31->unk4 == 1) && (var_r30->unk4 == 1)) {
                            var_f31 = fn_1_6D10(var_r31->unk60, var_r31->unk84, 100.0f, var_r30->unk60, var_r30->unk84, 100.0f);
                        } else {
                            var_f31 = fn_1_6D10(var_r31->unk60, var_r31->unk6C, 100.0f, var_r30->unk60, var_r30->unk6C, 100.0f);
                        }
                        if ((var_f31 < 0.0f) || (var_f31 > var_f29)) continue;
                        var_r31->unk90 = 1;
                        var_r30->unk90 = 1;
                        if (var_f31 > var_f30) continue;
                        if (var_f31 < var_f30) {
                            var_r29 = 0;
                        } else {
                            for (var_r27 = 0; var_r27 < var_r29; var_r27++) {
                                if ((sp27C[var_r27].unk4 == var_r30) && (sp27C[var_r27].unk8 == var_r31)) break;
                            }
                            if (var_r27 < var_r29) continue;
                        }
                        sp27C[var_r29].unk0 = 3;
                        sp27C[var_r29].unk4 = var_r31;
                        sp27C[var_r29].unk8 = var_r30;
                        var_r29++;
                        var_f30 = var_f31;
                    }
                }
            }
        }
        if (var_r29 == 0) break;
        var_r31 = lbl_1_bss_60;
        for (var_r28 = 0; var_r28 < lbl_1_bss_58; var_r28++, var_r31++) {
            var_r31->unk60.x += var_r31->unk6C.x * var_f30;
            var_r31->unk60.y += var_r31->unk6C.y * var_f30;
            var_r31->unk60.z += var_r31->unk6C.z * var_f30;
        }
        for (var_r28 = 0; var_r28 < var_r29; var_r28++) {
            switch (sp27C[var_r28].unk0) {
                case 0:
                    var_r31 = sp27C[var_r28].unk4;
                    var_r31->unk4 = 1;
                    sp234.y = 300.0f - var_r31->unk60.y;
                    var_r31->unk60.y = 300.0f;
                    var_r31->unk6C.y = sp234.y;
                    var_r31->unk84.y = sp234.y;
                    break;
                case 1:
                    var_r31 = sp27C[var_r28].unk4;
                    sp240 = var_r31->unk60;
                    sp240.y = 0.0f;
                    PSVECNormalize(&sp240, &sp228);
                    sp228.x = -sp228.x;
                    sp228.y = 0.0f;
                    sp228.z = -sp228.z;
                    temp_f28 = PSVECMag(&sp240);
                    temp_f28 -= 600.0f;
                    var_r31->unk60.x += temp_f28 * sp228.x;
                    var_r31->unk60.z += temp_f28 * sp228.z;
                    sp240 = var_r31->unk60;
                    sp240.y = 0.0f;
                    if (var_r31->unk4 == 1) {
                        fn_1_7CA0(var_r31->unk84, sp228, 0.8f, &sp24C);
                        var_r31->unk84 = sp24C;
                        PSVECAdd(&var_r31->unk84, &var_r31->unk78, &var_r31->unk6C);
                    } else {
                        fn_1_7CA0(var_r31->unk6C, sp228, 0.8f, &sp24C);
                        var_r31->unk6C = sp24C;
                        var_r31->unk84 = var_r31->unk6C;
                    }
                    break;
                case 2:
                    var_r31 = sp27C[var_r28].unk4;
                    sp240 = var_r31->unk60;
                    sp240.y = 0.0f;
                    PSVECNormalize(&sp240, &sp228);
                    temp_f28 = PSVECMag(&sp240);
                    temp_f28 = 350.0f;
                    var_r31->unk60.x = temp_f28 * sp228.x;
                    var_r31->unk60.z = temp_f28 * sp228.z;
                    sp240 = var_r31->unk60;
                    sp240.y = 0.0f;
                    if (var_r31->unk4 == 1) {
                        fn_1_7CA0(var_r31->unk84, sp228, 0.8f, &sp24C);
                        var_r31->unk84 = sp24C;
                        PSVECAdd(&var_r31->unk84, &var_r31->unk78, &var_r31->unk6C);
                    } else {
                        fn_1_7CA0(var_r31->unk6C, sp228, 0.8f, &sp24C);
                        var_r31->unk6C = sp24C;
                        var_r31->unk84 = var_r31->unk6C;
                    }
                    break;
                case 3:
                    var_r31 = sp27C[var_r28].unk4;
                    var_r30 = sp27C[var_r28].unk8;
                    if (var_r31->unk4 == 3) {
                        fn_1_79FC(&var_r30->unk3C, &var_r30->unk6C, 100.0f, &var_r31->unk3C, &var_r31->unk6C, 100.0f, 0.8f);
                        var_r31->unk84 = var_r31->unk6C;
                        var_r30->unk84 = var_r30->unk6C;
                    } else if (var_r30->unk4 == 3) {
                        fn_1_79FC(&var_r31->unk3C, &var_r31->unk6C, 100.0f, &var_r30->unk3C, &var_r30->unk6C, 100.0f, 0.8f);
                        var_r31->unk84 = var_r31->unk6C;
                        var_r30->unk84 = var_r30->unk6C;
                    } else if ((var_r31->unk4 == 1) && (var_r30->unk4 == 1)) {
                        fn_1_77C4(var_r31->unk60, var_r31->unk84, var_r30->unk60, 0.8f, &sp24C, &sp258);
                        fn_1_77C4(var_r30->unk60, var_r30->unk84, var_r31->unk60, 0.8f, &sp270, &sp264);
                        PSVECAdd(&sp24C, &sp264, &var_r31->unk84);
                        PSVECAdd(&sp258, &sp270, &var_r30->unk84);
                        PSVECAdd(&var_r31->unk84, &var_r31->unk78, &var_r31->unk6C);
                        PSVECAdd(&var_r30->unk84, &var_r30->unk78, &var_r30->unk6C);
                    } else {
                        fn_1_77C4(var_r31->unk60, var_r31->unk6C, var_r30->unk60, 0.8f, &sp24C, &sp258);
                        fn_1_77C4(var_r30->unk60, var_r30->unk6C, var_r31->unk60, 0.8f, &sp270, &sp264);
                        PSVECAdd(&sp24C, &sp264, &var_r31->unk6C);
                        PSVECAdd(&sp258, &sp270, &var_r30->unk6C);
                        var_r31->unk84 = var_r31->unk6C;
                        var_r30->unk84 = var_r30->unk6C;
                    }
                    break;
            }
        }
    }
    var_r31 = lbl_1_bss_60;
    for (var_r28 = 0; var_r28 < lbl_1_bss_58; var_r28++, var_r31++) {
        var_r31->unk3C.x = var_r31->unk60.x + (var_r31->unk6C.x * var_f29);
        var_r31->unk3C.y = var_r31->unk60.y + (var_r31->unk6C.y * var_f29);
        var_r31->unk3C.z = var_r31->unk60.z + (var_r31->unk6C.z * var_f29);
    }
}

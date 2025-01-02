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

typedef struct _M424DllBallStruct3 {
    u8 unk0;
    M424DllBallStruct2* unk4;
    M424DllBallStruct2* unk8;
} M424DllBallStruct3;

typedef struct _M424BallStruct4 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char unkC[0x8];
    f32 unk14;
    f32 unk18;
    char unk1C[0x8];
    f32 unk24;
    f32 unk28;
} M424BallStruct4;

// BSS
void* lbl_1_bss_5BC[0x20];
omObjData* lbl_1_bss_5AC[4];
omObjData* lbl_1_bss_594[6];
M424DllBallStruct2 lbl_1_bss_60[9];
s32 lbl_1_bss_5C;
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
void fn_1_6230(s16, Mtx);
void fn_1_62D0(s32, u32*);
f32 fn_1_640C(f32, f32, f32);
f32 fn_1_6D10(Vec, Vec, f32, Vec, Vec, f32);
f32 fn_1_709C(Vec, Vec, f32, f32);
f32 fn_1_7420(Vec, Vec, f32, f32);
void fn_1_77C4(Vec, Vec, Vec, f32, Vec*, Vec*);
void fn_1_79FC(Vec*, Vec*, f32, Vec*, Vec*, f32, f32);
void fn_1_7CA0(Vec, Vec, f32, Vec*);
void fn_1_8924(u8, u8);
void fn_1_8AA8(s32, s32);
s32 fn_1_8C78(s32, s32);
s32 fn_1_907C(Vec*, Vec*);


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
Vec lbl_1_data_17C[4] = {
    { -100.0f, 200.0f, -100.0f },
    {  300.0f, 200.0f, -100.0f },
    { -300.0f, 200.0f,  300.0f },
    {  300.0f, 200.0f,    0.0f }
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
                    fn_1_6230(var_r31->unk8, var_r31->unkC);
                    fn_1_6230(var_r31->unkA, var_r31->unkC);
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

void fn_1_6038(void) {
    s32 var_r31;
    
    for (var_r31 = 0; var_r31 < 0x20; var_r31++) {
        lbl_1_bss_5BC[var_r31] = 0;
    }
}

void* fn_1_6078(s32 arg0) {
    s32 var_r31;
    
    for (var_r31 = 0; var_r31 < 0x20; var_r31++) {
        if (lbl_1_bss_5BC[var_r31] == 0) break;
    }
    if (var_r31 == 0x20) {
        return NULL;
    }
    lbl_1_bss_5BC[var_r31] = HuMemDirectMallocNum(HEAP_SYSTEM, arg0, 0x10000000);
    return lbl_1_bss_5BC[var_r31];
}

void fn_1_6118(void* arg0) {
    s32 var_r31;
    
    for (var_r31 = 0; var_r31 < 0x20; var_r31++) {
        if (lbl_1_bss_5BC[var_r31] == arg0) break;
    }
    if (var_r31 != 0x20) {
        HuMemDirectFree(lbl_1_bss_5BC[var_r31]);
        lbl_1_bss_5BC[var_r31] = NULL;
    }
}

void fn_1_61AC(void) {
    s32 var_r31;
    
    for (var_r31 = 0; var_r31 < 0x20; var_r31++) {
        if (lbl_1_bss_5BC[var_r31]) {
            HuMemDirectFree(lbl_1_bss_5BC[var_r31]);
            lbl_1_bss_5BC[var_r31] = NULL;
        }
    }
}

void fn_1_6230(s16 arg0, Mtx arg1) {
    ModelData* var_r31;

    var_r31 = &Hu3DData[arg0];
    PSMTXCopy(arg1, var_r31->unk_F0);
}

u32 lbl_1_data_1D8 = 0x41C64E6D;

s32 fn_1_627C(void) {
    lbl_1_data_1D8 *= 0x41C64E6D;
    lbl_1_data_1D8 += 0x3039;
    return lbl_1_data_1D8 >> 0x10;
}

void fn_1_62D0(s32 arg0, u32* arg1) {
    s32 var_r31;
    s32 temp_r30;
    u32 temp_r29;

    for (var_r31 = 0; var_r31 < arg0; var_r31++) {
        arg1[var_r31] = var_r31;
    }
    
    for (var_r31 = 0; var_r31 < arg0 - 1; var_r31++) {
        temp_r30 = (arg0 * (fn_1_627C() / 65536.0f));
        temp_r29 = arg1[var_r31];
        arg1[var_r31] = arg1[temp_r30];
        arg1[temp_r30] = temp_r29;
    }
}

f32 fn_1_640C(f32 arg0, f32 arg1, f32 arg2) {
    f32 var_f31;

    if (arg0 > 180.0f) {
        arg0 -= 360.0f;
    } else {
        if (arg0 <= -180.0f) {
            arg0 += 360.0f;
        }
    }
    if (arg1 > 180.0f) {
        arg1 -= 360.0f;
    } else {
        if (arg1 <= -180.0f) {
            arg1 += 360.0f;
        }
    }
    var_f31 = arg0 - arg1;
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    } else {
        if (var_f31 <= -180.0f) {
            var_f31 += 360.0f;
        }
    }
    arg0 = arg1 + (var_f31 * arg2);
    if (arg0 > 180.0f) {
        return arg0 - 360.0f;
    }
    if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    }
    return arg0;
}

void fn_1_6574(Mtx arg0, f32 arg8, f32 arg9, f32 argA) {
    Mtx sp38;
    Mtx sp8;
    
    if (argA != 0.0f) {
        PSMTXRotRad(arg0, 0x5A, MTXDegToRad(argA));
    } else {
        PSMTXIdentity(arg0);
    }
    if (arg8 != 0.0f) {
        PSMTXRotRad(sp38, 0x58, MTXDegToRad(arg8));
        PSMTXConcat(sp38, arg0, arg0);
    }
    if (arg9 != 0.0f) {
        PSMTXRotRad(sp8, 0x59, MTXDegToRad(arg9));
        PSMTXConcat(sp8, arg0, arg0);
    }
}

void fn_1_6694(M424BallStruct4* arg0, Vec* arg1) {
    f32 temp_f29;
    f32 var_f28;

    arg1->x = atan2d(arg0->unk18, arg0->unk28);
    if (arg1->x < 0.0f) {
        arg1->x += 360.0f;
    }
    arg1->z = atan2d(arg0->unk4, arg0->unk0);
    if (arg1->z < 0.0f) {
        arg1->z += 360.0f;
    }
    temp_f29 = -arg0->unk8;
    var_f28 = sqrtf(ABS(1.0 - (temp_f29 * temp_f29)));
    if ((arg1->x > 90.0f) && (arg1->x < 270.0f) && (arg1->z > 90.0f) && (arg1->z < 270.0f)) {
        arg1->x = fmod((180.0f + arg1->x), 360.0);
        arg1->z = fmod((180.0f + arg1->z), 360.0);
        var_f28 = -var_f28;
    }
    arg1->y = atan2d(temp_f29, var_f28);
    if (arg1->y < 0.0f) {
        arg1->y += 360.0f;
    }
}

void fn_1_6A30(M424BallStruct4* arg0, Vec* arg1) {
    f32 temp_f29;
    f32 var_f27;

    arg1->z = atan2d(arg0->unk4, arg0->unk14);
    if (arg1->z < 0.0f) {
        arg1->z += 360.0f;
    }
    arg1->y = atan2d(arg0->unk8, arg0->unk28);
    if (arg1->y < 0.0f) {
        arg1->y += 360.0f;
    }
    temp_f29 = -arg0->unk24;
    var_f27 = sqrtf(ABS(1.0 - (temp_f29 * temp_f29)));
    arg1->x = atan2d(temp_f29, var_f27);
    if (arg1->x < 0.0f) {
        arg1->x += 360.0f;
    }
}

f32 fn_1_6D10(Vec arg0, Vec arg1, f32 arg2, Vec arg3, Vec arg4, f32 arg5) {
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;
    f32 temp_f27;
    f32 temp_f26;
    f32 temp_f25;
    f32 var_f23;

    PSVECSubtract(&arg3, &arg0, &arg3);
    PSVECSubtract(&arg4, &arg1, &arg4);
    temp_f29 = arg2 + arg5;
    if (PSVECMag(&arg3) > temp_f29 + PSVECMag(&arg4)) {
        return -1.0f;
    }
    temp_f29 *= temp_f29;
    temp_f27 = (arg4.z * arg4.z) + ((arg4.x * arg4.x) + (arg4.y * arg4.y));
    temp_f26 = 2.0f * ((arg4.z * arg3.z) + ((arg4.x * arg3.x) + (arg4.y * arg3.y)));
    var_f23 = ((arg3.z * arg3.z) + ((arg3.x * arg3.x) + (arg3.y * arg3.y))) - temp_f29;
    if (temp_f27 == 0.0f) {
        return -1.0f;
    }
    temp_f30 = (temp_f26 * temp_f26) - (4.0f * temp_f27 * var_f23);
    if (temp_f30 <= 0.0f) {
        return -1.0f;
    }
    temp_f30 = sqrtf(temp_f30);
    temp_f25 = (-temp_f26 + temp_f30) / (2.0f * temp_f27);
    temp_f28 = (-temp_f26 - temp_f30) / (2.0f * temp_f27);
    if (((temp_f25 * temp_f28) < 0.0f) && (temp_f28 < 0.0f) && (temp_f25 > fabs(temp_f28))) {
        return 0.0f;
    }
    return temp_f28;
}

f32 fn_1_709C(Vec arg0, Vec arg1, f32 arg2, f32 arg3) {
    Vec sp20;
    Vec sp14;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;
    f32 temp_f27;
    f32 temp_f26;
    f32 temp_f25;
    f32 var_f23;

    sp20 = arg0;
    sp20.y = 0.0f;
    sp14 = arg1;
    sp14.y = 0.0f;
    temp_f29 = arg3 + arg2;
    if (PSVECMag(&sp20) > temp_f29 + PSVECMag(&sp14)) {
        return -1.0f;
    }
    temp_f29 *= temp_f29;
    temp_f27 = (arg1.x * arg1.x) + (arg1.z * arg1.z);
    temp_f26 = 2.0f * ((arg1.x * arg0.x) + (arg1.z * arg0.z));
    var_f23 = (((arg0.x * arg0.x) + (arg0.z * arg0.z)) - temp_f29);
    if (0.0f == temp_f27) {
        return -1.0f;
    }
    temp_f30 = (temp_f26 * temp_f26) - (4.0f * temp_f27 * var_f23);
    if (temp_f30 <= 0.0f) {
        return -1.0f;
    }
    temp_f30 = sqrtf(temp_f30);
    temp_f25 = (-temp_f26 + temp_f30) / (2.0f * temp_f27);
    temp_f28 = (-temp_f26 - temp_f30) / (2.0f * temp_f27);
    if (((temp_f25 * temp_f28) < 0.0f) && (temp_f28 < 0.0f) && (temp_f25 > fabs(temp_f28))) {
        return 0.0f;
    }
    return temp_f28;
}

f32 fn_1_7420(Vec arg0, Vec arg1, f32 arg2, f32 arg3) {
    Vec sp20;
    Vec sp14;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;
    f32 temp_f27;
    f32 temp_f26;
    f32 temp_f25;
    f32 var_f23;
    
    sp20 = arg0;
    sp20.y = 0.0f;
    sp14 = arg1;
    sp14.y = 0.0f;
    temp_f29 = arg3 - arg2;
    if (PSVECMag(&sp20) > temp_f29) {
        return 0.0f;
    }
    if (PSVECMag(&sp20) > temp_f29 + PSVECMag(&sp14)) {
        return -1.0f;
    }
    temp_f29 *= temp_f29;
    temp_f27 = (arg1.x * arg1.x) + (arg1.z * arg1.z);
    temp_f26 = 2.0f * ((arg1.x * arg0.x) + (arg1.z * arg0.z));
    var_f23 = (arg0.x * arg0.x) + (arg0.z * arg0.z) - temp_f29;
    if (0.0f == temp_f27) {
        return -1.0f;
    }
    temp_f30 = (temp_f26 * temp_f26) - (4.0f * temp_f27 * var_f23);
    if (temp_f30 <= 0.0f) {
        return -1.0f;
    }
    temp_f30 = sqrtf(temp_f30);
    temp_f25 = (-temp_f26 - temp_f30) / (2.0f * temp_f27);
    temp_f28 = (-temp_f26 + temp_f30) / (2.0f * temp_f27);
    if (((temp_f25 * temp_f28) < 0.0f) && (temp_f28 < 0.0f) && (temp_f25 > fabs(temp_f28))) {
        return 0.0f;
    }
    return temp_f28;
}

void fn_1_77C4(Vec arg0, Vec arg1, Vec arg2, f32 arg3, Vec* arg4, Vec* arg5) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    f32 var_f31;
    f32 temp_f30;
    f32 temp_f29;
    f32 var_f28;

    sp38 = arg1;
    var_f31 = PSVECMag(&sp38);
    if (var_f31 < 0.01f) {
        arg4->x = arg4->y = arg4->z = 0.0f;
        arg5->x = arg5->y = arg5->z = 0.0f;
        return;
    }
    PSVECNormalize(&sp38, &sp38);
    var_f31 = var_f31 * arg3;
    PSVECSubtract(&arg2, &arg0, &sp2C);
    PSVECNormalize(&sp2C, &sp2C);
    var_f28 = PSVECDotProduct(&sp38, &sp2C);
    if (var_f28 < 0.0f) {
        arg4->x = arg1.x;
        arg4->y = arg1.y;
        arg4->z = arg1.z;
        arg5->x = arg5->y = arg5->z = 0.0f;
        return;
    }
    temp_f29 = var_f31 * var_f28;
    temp_f30 = var_f31 - temp_f29;
    if (temp_f30 < 0.01f) {
        arg4->x = arg4->y = arg4->z = 0.0f;
    } else {
        PSVECCrossProduct(&sp38, &sp2C, &sp14);
        PSVECNormalize(&sp14, &sp14);
        PSVECCrossProduct(&sp2C, &sp14, &sp20);
        PSVECNormalize(&sp20, &sp20);
        arg4->x = sp20.x * temp_f30;
        arg4->y = sp20.y * temp_f30;
        arg4->z = sp20.z * temp_f30;
    }
    arg5->x = sp2C.x * temp_f29;
    arg5->y = sp2C.y * temp_f29;
    arg5->z = sp2C.z * temp_f29;
}

void fn_1_79FC(Vec* arg0, Vec* arg1, f32 arg2, Vec* arg3, Vec* arg4, f32 arg5, f32 arg6) {
    Vec sp38;
    Vec sp2C;
    f32 temp_f31;
    f32 var_f30;
    f32 var_f29;

    arg1->x *= arg6;
    arg1->y *= arg6;
    arg1->z *= arg6;
    PSVECSubtract(arg0, arg3, &sp38);
    PSVECNormalize(&sp38, &sp2C);
    temp_f31 = (arg2 + arg5) - PSVECMag(&sp38);
    if (temp_f31 > 0.01f) {
        PSVECSubtract(arg1, arg4, &sp38);
        if (PSVECMag(&sp38) < 0.01f) {
            arg0->x += sp2C.x * temp_f31;
            arg0->y += sp2C.y * temp_f31;
            arg0->z += sp2C.z * temp_f31;
        } else {
            PSVECNormalize(&sp38, &sp38);
            arg0->x -= sp38.x * temp_f31;
            arg0->y -= sp38.y * temp_f31;
            arg0->z -= sp38.z * temp_f31;
        }
    }
    fn_1_7CA0(*arg1, sp2C, 1.0f, arg1);
    PSVECSubtract(arg4, arg1, &sp38);
    var_f30 = PSVECMag(&sp38);
    if (var_f30 < 0.01f) return;
    PSVECNormalize(&sp38, &sp38);
    var_f29 = PSVECDotProduct(&sp2C, &sp38);
    if (var_f29 > 0.0f) {
        arg1->x += var_f30 * (sp2C.x * var_f29);
        arg1->y += var_f30 * (sp2C.y * var_f29);
        arg1->z += var_f30 * (sp2C.z * var_f29);
    }
}

void fn_1_7CA0(Vec arg0, Vec arg1, f32 arg2, Point3d* arg3) {
    f32 var_f31;

    *arg3 = arg0;
    arg3->x *= arg2;
    arg3->y *= arg2;
    arg3->z *= arg2;
    var_f31 = PSVECDotProduct(&arg1, arg3);
    if (var_f31 < 0.0f) {
        arg3->x -= 2.0f * arg1.x * var_f31;
        arg3->y -= 2.0f * arg1.y * var_f31;
        arg3->z -= 2.0f * arg1.z * var_f31;
    }
}

f32 fn_1_7DD0(Vec* arg0) {
    f32 temp_f30;
    f32 temp_f29;

    temp_f30 = (arg0->x * arg0->x) + (arg0->y * arg0->y) + (arg0->z * arg0->z);
    temp_f30 = sqrtf(temp_f30);
    if (temp_f30 != 0.0f) {
        temp_f29 = 1.0f / temp_f30;
        arg0->x *= temp_f29;
        arg0->y *= temp_f29;
        arg0->z *= temp_f29;
    } else {
        arg0->x = arg0->y = arg0->z = 0.0f;
    }
    return temp_f30;
}

f32 fn_1_7F68(Vec arg0, Vec arg1, Vec* arg2, f32 arg8) {
    if (arg8 <= 0.0f) {
        arg2->x = arg0.x;
        arg2->y = arg0.y;
        arg2->z = arg0.z;
        arg8 = 0.0f;
    } else  if (arg8 >= 1.0f) {
        arg2->x = (arg0.x + arg1.x);
        arg2->y = (arg0.y + arg1.y);
        arg2->z = (arg0.z + arg1.z);
        arg8 = 1.0f;
    } else {
        arg2->x = (arg0.x + (arg8 * arg1.x));
        arg2->y = (arg0.y + (arg8 * arg1.y));
        arg2->z = (arg0.z + (arg8 * arg1.z));
    }
    return arg8;
}

f32 fn_1_8040(Vec arg0, Vec arg1, Vec arg2) {
    f32 temp_f30;
    f32 var_f31;

    var_f31 = (arg2.z * (arg1.z - arg0.z)) + ((arg2.x * (arg1.x - arg0.x)) + (arg2.y * (arg1.y - arg0.y)));
    temp_f30 = -((arg2.z * arg2.z) + ((arg2.x * arg2.x) + (arg2.y * arg2.y)));
    if (temp_f30 != 0.0f) {
        var_f31 /= temp_f30;
    }
    return var_f31;
}

f32 fn_1_80FC(Vec* arg0, Vec* arg1, Vec* arg2) {
    Vec sp44;
    f32 var_f30;

    if (0.0f == (arg2->x * arg2->x) + (arg2->y * arg2->y) + (arg2->z * arg2->z)) {
        return ((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)) + ((arg0->z - arg1->z) * (arg0->z - arg1->z));
    }
    var_f30 = fn_1_8040(*arg0, *arg1, *arg2);
    fn_1_7F68(*arg1, *arg2, &sp44, var_f30);
    return ((arg0->x - sp44.x) * (arg0->x - sp44.x)) + ((arg0->y - sp44.y) * (arg0->y - sp44.y)) + ((arg0->z - sp44.z) * (arg0->z - sp44.z));
}

f32 fn_1_8438(Vec* arg0, Vec* arg1, Vec* arg2, Vec* arg3, Vec* arg4) {
    f32 var_f27;

    if (0.0f == ((arg2->z * arg2->z) + ((arg2->x * arg2->x) + (arg2->y * arg2->y)))) {
        return ((arg0->z - arg1->z) * (arg0->z - arg1->z)) + (((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)));
    }
    var_f27 = fn_1_8040(*arg0, *arg1, *arg2);
    fn_1_7F68(*arg1, *arg2, arg3, var_f27);
    arg4->x = arg0->x - arg3->x;
    arg4->y = arg0->y - arg3->y;
    arg4->z = arg0->z - arg3->z;
    return fn_1_7DD0(arg4);
}

void fn_1_88E8(u8 arg0, f32 arg8, f32 arg9, f32 argA) {
    M424DllBallStruct2* temp_r31;

    temp_r31 = &lbl_1_bss_60[arg0];
    temp_r31->unk4 = 3;
    temp_r31->unk3C.x = arg8;
    temp_r31->unk3C.y = arg9;
    temp_r31->unk3C.z = argA;
}

void fn_1_8924(u8 arg0, u8 arg1) {
    M424DllBallStruct2* temp_r31;

    temp_r31 = &lbl_1_bss_60[arg0];
    temp_r31->unk4 = arg1;
}

u8 fn_1_8950(u8 arg0) {
    M424DllBallStruct2* temp_r31;

    temp_r31 = &lbl_1_bss_60[arg0];
    return temp_r31->unk4;
}

u8 fn_1_897C(u8 arg0) {
    M424DllBallStruct2* temp_r31;

    temp_r31 = &lbl_1_bss_60[arg0];
    return temp_r31->unk5;
}

u8 fn_1_89A8(u8 arg0) {
    M424DllBallStruct2* temp_r31;

    temp_r31 = &lbl_1_bss_60[arg0];
    return temp_r31->unk91;
}

Vec* fn_1_89D4(u8 arg0) {
    M424DllBallStruct2* temp_r31;

    temp_r31 = &lbl_1_bss_60[arg0];
    return &temp_r31->unk3C;
}

Vec* fn_1_8A00(u8 arg0) {
    M424DllBallStruct2* temp_r31;

    temp_r31 = &lbl_1_bss_60[arg0];
    return &temp_r31->unk6C;
}

s32 fn_1_8A2C(void) {
    M424DllBallStruct2* var_r31;
    M424DllBallStruct* temp_r30;
    s32 var_r29;

    var_r31 = lbl_1_bss_60;
    for (var_r29 = 0; var_r29 < lbl_1_bss_58; var_r29++, var_r31++) {
        temp_r30 = var_r31->unk0->data;
        if ((temp_r30->unk8 == 3) || (temp_r30->unk8 == 2)) {
            return 0;
        }
    }
    return 1;
}

void fn_1_8AA8(s32 arg0, s32 arg1) {
    Vec spC;
    M424DllBallStruct2* temp_r31;
    s32 var_r27;
    s32 var_r29;
    s32 var_r30;

    if (arg1 != 0) {
        for (var_r30 = 0; var_r30 < lbl_1_bss_58; var_r30++) {
            temp_r31 = &lbl_1_bss_60[var_r30];
            if (temp_r31->unk4 != 6) {
                PSVECAdd(&temp_r31->unk60, &temp_r31->unk6C, &temp_r31->unk3C);
                if ((temp_r31->unk4 < 3) && (fn_1_907C(&temp_r31->unk3C, &spC) != 0)) {
                    temp_r31->unk3C = spC;
                }
                if ((temp_r31->unk6C.y < 0.0f) && (temp_r31->unk4 != 4) && (temp_r31->unk4 != 6) && (temp_r31->unk3C.y < 300.0f)) {
                    temp_r31->unk3C.y = 300.0f;
                    if (temp_r31->unk4 == 2) {
                        temp_r31->unk4 = 1;
                    }
                }
            }
        }
    }
    
    for (var_r30 = 0, var_r29 = arg0; var_r30 < lbl_1_bss_58; var_r30++) {
        temp_r31 = &lbl_1_bss_60[var_r30];
        var_r27 = 0;
        if (fn_1_8950(var_r30) < 4) {
            if (fn_1_8C78(var_r30, arg0) < arg0) {
                var_r27 = 1;
            }
            if ((var_r27 != 0) && (var_r29 > 0)) {
                var_r29 -= 1;
                var_r30 -= 1;
            } else {
                var_r29 = arg0;
            }
        }
    }
    fn_1_C2E0(0);
}

s32 fn_1_8C78(s32 arg0, s32 arg1) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec* sp10;
    f32 temp_f31;
    f32 var_f30;
    s32 var_r31;
    M424DllBallStruct2* temp_r30;
    M424DllBallStruct2* temp_r29;
    Vec* var_r28;
    Vec* var_r27;
    M424DllBallStruct* temp_r26;
    M424DllBallStruct* temp_r25;

    temp_r30 = &lbl_1_bss_60[arg0];
    temp_r26 = temp_r30->unk0->data;
    var_r28 = fn_1_89D4(arg0);
    sp38 = *var_r28;
    
    for (var_r31 = 0; var_r31 < lbl_1_bss_58; var_r31++) {
        if (var_r31 != arg0) {
            if (fn_1_8950(var_r31) < 3) {
                temp_r29 = &lbl_1_bss_60[var_r31];
                temp_r25 = temp_r29->unk0->data;
                var_r27 = fn_1_89D4(var_r31);
                sp2C = *var_r27;
                PSVECSubtract(&sp2C, &sp38, &sp20);
                var_f30 = PSVECMag(&sp20);
                if (var_f30 < 200.0f) {
                    if (var_f30 > 0.0f) {
                        temp_f31 = 1.0f / var_f30;
                        sp20.x *= temp_f31;
                        sp20.y *= temp_f31;
                        sp20.z *= temp_f31;
                    } else {
                        sp20.x = 0.0f;
                        sp20.y = 0.0f;
                        sp20.z = 1.0f;
                    }
                    temp_f31 = 1.0f + (0.5f * (200.0f - var_f30));
                    if (temp_f31 > 0.0f) {
                        PSVECScale(&sp20, &sp20, temp_f31);
                        PSVECAdd(&sp2C, &sp20, &sp2C);
                        *var_r27 = sp2C;
                        if ((temp_r29->unk4 < 3) && (fn_1_907C(&sp2C, &sp14) != 0)) {
                            sp2C = sp14;
                            *var_r27 = sp14;
                        }
                        if ((temp_r29->unk4 == 2) && (temp_r25->unk4C.y < 0.0f)) {
                            temp_r25->unk4C.y += 0.1f * temp_f31;
                        }
                    }
                    if (temp_f31 > 0.0f) {
                        PSVECScale(&sp20, &sp20, -1.0f);
                        PSVECAdd(&sp38, &sp20, &sp38);
                        *var_r28 = sp38;
                        if ((temp_r30->unk4 < 3) && (fn_1_907C(&sp38, &sp14) != 0)) {
                            sp38 = sp14;
                            *var_r28 = sp14;
                        }
                        if ((temp_r30->unk4 == 2) && (temp_r26->unk4C.y < 0.0f)) {
                            temp_r26->unk4C.y += 0.1f * temp_f31;
                        }
                    }
                    if (arg1 > 0) {
                        arg1--;
                        fn_1_8C78(var_r31, arg1);
                    }
                }
            }
        }
    }
    return arg1;
}

s32 fn_1_907C(Vec* arg0, Vec* arg1) {
    Vec sp10;
    f32 temp_f29;
    f32 temp_f28;
    f32 var_f27;
    f32 temp_f26;

    sp10 = *arg0;
    *arg1 = *arg0;
    temp_f29 = (sp10.x * sp10.x) + (sp10.z * sp10.z);
    var_f27 = sqrtf(temp_f29);
    if (var_f27 < 350.0f) {
        if (var_f27 > 0.0f) {
            temp_f26 = 1.0f / var_f27;
            sp10.x *= temp_f26;
            sp10.z *= temp_f26;
        } else {
            sp10.x = 1.0f;
            sp10.z = 0.0f;
        }
        arg1->x = 350.0f * sp10.x;
        arg1->z = 350.0f * sp10.z;
    }
    temp_f28 = (sp10.x * sp10.x) + (sp10.z * sp10.z);
    var_f27 = sqrtf(temp_f28);
    if (var_f27 > 600.0f) {
        temp_f26 = 1.0f / var_f27;
        sp10.x *= temp_f26;
        sp10.z *= temp_f26;
        arg1->x = 600.0f * sp10.x;
        arg1->z = 600.0f * sp10.z;
    }
    return (s32)arg0;
}

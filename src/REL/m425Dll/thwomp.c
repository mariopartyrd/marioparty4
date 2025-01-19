#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/mtx/GeoTypes.h"
#include "ext_math.h"
#include "game/animdata.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

#include "REL/m425Dll.h"

extern u32 GlobalCounter;
extern LightData Hu3DLocalLight[0x20];

typedef struct M425DllUnkStruct4 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    float unk_08;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    float unk_20;
    float unk_24;
    s32 unk_28;
    s32 unk_2C;
    float unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C[5];
    s32 unk_50;
    float unk_54[6];
    s32 unk_6C[6];
    s32 unk_84[6];
    float unk_9C[6];
    s32 unk_B4[6];
    Vec unk_CC;
    float unk_D8;
    float unk_DC;
    float unk_E0;
    float unk_E4;
    float unk_E8;
    float unk_EC;
    s32 unk_F0[3];
    float unk_FC;
    float unk_100;
    char unk104[0x8];
    s16 unk_10C;
    s16 unk_10E;
    s16 unk_110;
    s16 unk_112[0x19];
    s16 unk_144[0x1A];
    s16 *unk_178;
    Vec *unk_17C;
    Vec *unk_180;
    Vec2f *unk_184;
    Vec *unk_188;
    Vec *unk_18C;
    s16 (*unk_190)[3];
    Vec *unk_194;
    Vec *unk_198;
    s32 unk_19C;
    u8 *unk_1A0;
    s16 *unk_1A4[0x19];
    s16 unk_208[0x19];
    GXColor unk_23A;
    s32 unk_240;
    u32 unk_244[0x19];
    void *unk_2A8[0x19];
} M425DllUnkStruct4; /* size = 0x30C */

typedef struct M425DllUnkStruct5 {
    char unk00[4];
    Vec unk_04;
    Vec unk_10;
    float unk_1C;
    char unk20[8];
    float unk_28;
    float unk_2C;
    Vec unk_30;
    GXColor unk_3C;
    s32 unk_40;
} M425DllUnkStruct5; /* size = 0x44 */

typedef void (*UnkHook)(ModelData *model, struct M425DllUnkStruct6 *particle, Mtx matrix);

typedef struct M425DllUnkStruct6 {
    s16 unk_00;
    s16 unk_02;
    char unk04[0x1C];
    u8 unk_20;
    u8 unk_21;
    char unk22[2];
    s16 unk_24;
    s32 unk_28;
    s32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    AnimData *unk_38;
    M425DllUnkStruct5 *unk_3C;
    Vec *unk_40;
    Vec2f *unk_44;
    void *unk_48;
    UnkHook unk_4C;
} M425DllUnkStruct6; /* size = 0x50 */

void fn_1_6BD8(omObjData *object);
s32 fn_1_6EC4(float arg8, float arg9, s16 arg0, s16 arg1);
void fn_1_6DFC(s32 arg0, float arg8);
void fn_1_E210(s32 arg0);
void fn_1_E914(ModelData *arg0, Mtx matrix);
void fn_1_D9A8(M425DllUnkStruct4 *var_r31, ModelData *var_r24, s32 var_r30, s32 var_r26, s32 var_r25);
void fn_1_DB44(M425DllUnkStruct4 *arg0, ModelData *model);
void fn_1_DE3C(M425DllUnkStruct4 *arg0, ModelData *model);
void fn_1_101C4(ModelData *model, Mtx matrix);
void fn_1_11284(void);
void fn_1_112FC(void);
void fn_1_11418(void);
s32 fn_1_11454(Vec *arg0, Vec *arg1, float arg8, float arg9);
s16 fn_1_115D4(ModelData *arg0, Mtx arg1, Mtx arg2, float arg8);
void fn_1_116E4(ModelData *arg1, LightData *arg2, s16 arg3, Mtx arg4, Mtx arg5, float arg8);
s16 fn_1_11A74(AnimData *arg0, s16 arg1);
void fn_1_11EE0(ModelData *model, Mtx matrix);

Vec lbl_1_data_118[2] = {
    { -300.0f, 1.0f, 0.0f },
    { 300.0f, 1.0f, 0.0f },
};

Process *lbl_1_bss_6F0;
omObjData *lbl_1_bss_6EC;
s32 lbl_1_bss_6E8;
u8 *lbl_1_bss_6E4;
AnimData *lbl_1_bss_6E0;
AnimData *lbl_1_bss_6DC;
AnimData *lbl_1_bss_6D8;
// M425DllUnkStruct6
s32 lbl_1_bss_6D4;
u8 lbl_1_bss_6D0;
s32 lbl_1_bss_6CC;
GXColor lbl_1_bss_6C8;
GXLightObj lbl_1_bss_688;
Vec lbl_1_bss_67C;
Vec lbl_1_bss_670;

omObjData *fn_1_6A0C(Process *process, s32 sp8)
{
    omObjData *object;

    lbl_1_bss_6F0 = process;
    object = omAddObjEx(process, sp8, 6, 0, -1, fn_1_6BD8);
    lbl_1_bss_6EC = object;
    object->stat |= 0x100;
    lbl_1_bss_6E8 = 0;
    lbl_1_bss_6D0 = 0x40;
    lbl_1_bss_6CC = 0;
    object->model[0] = fn_1_6EC4(350.0f, 350.0f, 0x10, 0x10);
    object->model[1] = fn_1_6EC4(350.0f, 350.0f, 0x10, 0x10);
    fn_1_6CD0(0, &lbl_1_data_118[0]);
    fn_1_6CD0(1, &lbl_1_data_118[1]);
    fn_1_6DFC(0, 30.0f);
    fn_1_6DFC(1, -30.0f);
    lbl_1_bss_6E4 = HuDataReadNum(0x38000A, MEMORY_DEFAULT_NUM);
    lbl_1_bss_6E0 = HuSprAnimRead(HuDataReadNum(0x38000B, MEMORY_DEFAULT_NUM));
    lbl_1_bss_6DC = HuSprAnimRead(HuDataReadNum(0x38000C, MEMORY_DEFAULT_NUM));
    fn_1_11284();
    return lbl_1_bss_6EC;
}

void fn_1_6BD8(omObjData *object)
{
    fn_1_E210(0);
    fn_1_E210(1);
    fn_1_112FC();
}

void fn_1_6C08(void)
{
    omObjData *object = lbl_1_bss_6EC;
    if (object) {
        HuMemDirectFree(lbl_1_bss_6E4);
        lbl_1_bss_6E4 = NULL;
        HuSprAnimKill(lbl_1_bss_6E0);
        lbl_1_bss_6E0 = NULL;
        HuSprAnimKill(lbl_1_bss_6DC);
        lbl_1_bss_6DC = NULL;
        fn_1_11418();
        lbl_1_bss_6EC = NULL;
        object->func = NULL;
        omDelObjEx(lbl_1_bss_6F0, object);
    }
}

void fn_1_6CD0(s32 arg0, Vec *arg1)
{
    M425DllUnkStruct4 *var_r30;
    s32 var_r29;
    ModelData *var_r28;

    if (lbl_1_bss_6EC) {
        var_r28 = &Hu3DData[lbl_1_bss_6EC->model[arg0]];
        var_r30 = var_r28->unk_120;
        var_r30->unk_CC.x = arg1->x;
        var_r30->unk_CC.y = arg1->y;
        var_r30->unk_CC.z = arg1->z;
        Hu3DModelPosSet(lbl_1_bss_6EC->model[arg0], arg1->x, arg1->y, arg1->z);
        if ((lbl_1_bss_6CC == 0) && (arg0 == 0) && (arg1->y <= 0.0f)) {
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                omVibrate(0, 0xC, 6, 6);
            }
            HuAudFXPlay(0x62E);
            lbl_1_bss_6CC = 1;
        }
    }
}

void fn_1_6DFC(s32 arg0, float arg8)
{
    ModelData *var_r31;
    M425DllUnkStruct4 *var_r30;

    if (lbl_1_bss_6EC) {
        var_r31 = &Hu3DData[lbl_1_bss_6EC->model[arg0]];
        var_r30 = var_r31->unk_120;
        var_r30->unk_D8 = arg8;
        Hu3DModelRotSet(lbl_1_bss_6EC->model[arg0], 0.0f, arg8, 0.0f);
    }
}

s32 fn_1_6EC4(float var_f24, float sp8, s16 var_r22, s16 var_r24)
{
    float sp24;
    float sp20;
    float sp1C;
    float sp18;
    float sp14;
    float sp10;
    void *spC;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f20;
    float var_f19;
    float var_f18;

    M425DllUnkStruct4 *var_r31;
    s32 var_r30;
    Vec *var_r29;
    Vec2f *var_r28;
    s32 var_r27;
    Vec *var_r26;
    s16 *var_r25;
    ModelData *var_r23;
    s32 var_r21;
    s16 *var_r20;
    s32 var_r19;
    s16 var_r18;
    void *var_r17;

    var_r19 = Hu3DHookFuncCreate(fn_1_101C4);
    var_r23 = &Hu3DData[var_r19];
    Hu3DModelLayerSet(var_r19, 5);
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(M425DllUnkStruct4), var_r23->unk_48);
    var_r23->unk_120 = var_r31;
    memset(var_r31, 0, sizeof(M425DllUnkStruct4));
    var_r31->unk_00 = lbl_1_bss_6E8;
    lbl_1_bss_6E8++;
    var_r31->unk_02 = 0;
    var_r31->unk_04 = Hu3DModelCreateFile(0x38000D);
    Hu3DModelLayerSet(var_r31->unk_04, 6);
    var_r31->unk_06 = 0;
    var_r31->unk_08 = 1000.0f;
    var_r31->unk_0C = 1000.0f;
    var_r31->unk_10 = 1000.0f;
    var_r31->unk_14 = 0.0f;
    var_r31->unk_18 = 0.0f;
    var_r31->unk_1C = 0.0f;
    var_r31->unk_20 = 0.0f;
    var_r31->unk_24 = sp8;
    var_r31->unk_FC = var_f24;
    var_r31->unk_100 = sp8;
    var_r31->unk_28 = 0;
    var_r31->unk_2C = 0;
    var_r31->unk_30 = 0.0f;
    for (var_r30 = 0; var_r30 < 6; var_r30++) {
        var_r31->unk_3C[var_r30] = -1;
        var_r31->unk_54[var_r30] = 0.0f;
        var_r31->unk_84[var_r30] = -1;
        var_r31->unk_9C[var_r30] = 0.0f;
    }
    var_r31->unk_CC.x = var_r31->unk_CC.y = var_r31->unk_CC.z = 0.0f;
    var_r31->unk_D8 = 0.0f;
    var_r31->unk_DC = 1.0f;
    var_r31->unk_F0[0] = -1;
    var_r31->unk_F0[1] = -1;
    var_r31->unk_F0[2] = -1;
    lbl_1_bss_6EC->model[var_r31->unk_00 + 2] = var_r31->unk_04;
    if (var_r31->unk_00 == 0) {
        var_r31->unk_E0 = var_f22 = 302.0f;
        var_r31->unk_E4 = var_f27 = 193.0f;
    }
    else {
        var_r31->unk_E0 = var_f22 = 302.0f;
        var_r31->unk_E4 = var_f27 = 150.0f;
    }
    var_r31->unk_E8 = var_r31->unk_EC = 0.0f;
    var_f30 = sind(var_f27) * cosd(var_f22);
    var_f26 = cosd(var_f27) * cosd(var_f22);
    var_f28 = sind(var_f22);
    sp24 = sqrtf((var_f26 * var_f26) + ((var_f30 * var_f30) + (var_f28 * var_f28)));
    if (sp24 != 0.0f) {
        sp24 = 1.0f / sp24;
    }
    else {
        sp24 = 0.0f;
    }
    var_f30 *= sp24;
    var_f28 *= sp24;
    var_f26 *= sp24;
    var_r30 = Hu3DLLightCreate(var_r19, 1000.0f * var_f30, 1000.0f * var_f28, 1000.0f * var_f26, var_f30, var_f28, var_f26, 0xFF, 0xFF, 0xFF);
    Hu3DLLightInfinitytSet(var_r19, var_r30);
    Hu3DLLightStaticSet(var_r19, var_r30, 1);
    var_r22++;
    var_r24++;
    sp14 = var_f24 - 50.0f;
    sp10 = sp8 - 50.0f;
    var_r31->unk_112[0] = var_r24 * var_r24;
    var_r31->unk_144[0] = 0;
    var_r31->unk_112[1] = var_r22 * var_r24;
    var_r31->unk_144[1] = var_r31->unk_144[0] + var_r31->unk_112[0];
    if (var_r31->unk_00 != 0) {
        var_r31->unk_112[2] = 0;
    }
    else {
        var_r31->unk_112[2] = var_r22 * var_r24;
    }
    var_r31->unk_144[2] = var_r31->unk_144[1] + var_r31->unk_112[1];
    if (var_r31->unk_00 == 0) {
        var_r31->unk_112[3] = 0;
    }
    else {
        var_r31->unk_112[3] = var_r22 * var_r24;
    }
    var_r31->unk_144[3] = var_r31->unk_144[2] + var_r31->unk_112[2];
    var_r31->unk_112[4] = var_r24 * 5;
    var_r31->unk_144[4] = var_r31->unk_144[3] + var_r31->unk_112[3];
    var_r31->unk_112[5] = var_r24 * 5;
    var_r31->unk_144[5] = var_r31->unk_144[4] + var_r31->unk_112[4];
    var_r31->unk_112[6] = var_r22 * 5;
    var_r31->unk_144[6] = var_r31->unk_144[5] + var_r31->unk_112[5];
    var_r31->unk_112[7] = var_r22 * 5;
    var_r31->unk_144[7] = var_r31->unk_144[6] + var_r31->unk_112[6];
    var_r31->unk_112[8] = var_r24 * 5;
    var_r31->unk_144[8] = var_r31->unk_144[7] + var_r31->unk_112[7];
    var_r31->unk_112[9] = var_r24 * 5;
    var_r31->unk_144[9] = var_r31->unk_144[8] + var_r31->unk_112[8];
    var_r31->unk_112[10] = var_r24 * 5;
    var_r31->unk_144[10] = var_r31->unk_144[9] + var_r31->unk_112[9];
    var_r31->unk_112[11] = var_r24 * 5;
    var_r31->unk_144[11] = var_r31->unk_144[10] + var_r31->unk_112[10];
    var_r31->unk_112[12] = var_r24 * 5;
    var_r31->unk_144[12] = var_r31->unk_144[11] + var_r31->unk_112[11];
    var_r31->unk_112[13] = var_r24 * 5;
    var_r31->unk_144[13] = var_r31->unk_144[12] + var_r31->unk_112[12];
    if (var_r31->unk_00 == 0) {
        var_r31->unk_112[14] = 0;
    }
    else {
        var_r31->unk_112[14] = var_r22 * 5;
    }
    var_r31->unk_144[14] = var_r31->unk_144[13] + var_r31->unk_112[13];
    if (var_r31->unk_00 != 0) {
        var_r31->unk_112[15] = 0;
    }
    else {
        var_r31->unk_112[15] = var_r22 * 5;
    }
    var_r31->unk_144[15] = var_r31->unk_144[14] + var_r31->unk_112[14];
    var_r31->unk_112[16] = 0x19;
    var_r31->unk_144[16] = var_r31->unk_144[15] + var_r31->unk_112[15];
    var_r31->unk_112[17] = 0x19;
    var_r31->unk_144[17] = var_r31->unk_144[16] + var_r31->unk_112[16];
    var_r31->unk_112[18] = 0x19;
    var_r31->unk_144[18] = var_r31->unk_144[17] + var_r31->unk_112[17];
    var_r31->unk_112[19] = 0x19;
    var_r31->unk_144[19] = var_r31->unk_144[18] + var_r31->unk_112[18];
    var_r31->unk_112[20] = 0x19;
    var_r31->unk_144[20] = var_r31->unk_144[19] + var_r31->unk_112[19];
    var_r31->unk_112[21] = 0x19;
    var_r31->unk_144[21] = var_r31->unk_144[20] + var_r31->unk_112[20];
    var_r31->unk_112[22] = 0x19;
    var_r31->unk_144[22] = var_r31->unk_144[21] + var_r31->unk_112[21];
    var_r31->unk_112[23] = 0x19;
    var_r31->unk_144[23] = var_r31->unk_144[22] + var_r31->unk_112[22];
    var_r31->unk_112[24] = var_r24 * var_r24;
    var_r31->unk_144[24] = var_r31->unk_144[23] + var_r31->unk_112[23];
    if (var_r31->unk_00 == 0) {
        var_r31->unk_06 = var_r31->unk_144[17] + (var_r31->unk_112[17] / 2) + 1;
    }
    else {
        var_r31->unk_06 = var_r31->unk_144[16] + (var_r31->unk_112[16] / 2) - 1;
    }
    var_r31->unk_10C = var_r22;
    var_r31->unk_10E = var_r24;
    var_r31->unk_110 = var_r31->unk_144[24] + var_r31->unk_112[24];
    var_r31->unk_240 = 0x19;
    var_r31->unk_178 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_110 * 2, var_r23->unk_48);
    memset(var_r31->unk_178, 0, var_r31->unk_110 * 2);
    var_r31->unk_17C = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_110 * 0xC, var_r23->unk_48);
    memset(var_r31->unk_17C, 0, var_r31->unk_110 * 0xC);
    var_r31->unk_180 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_110 * 0xC, var_r23->unk_48);
    memset(var_r31->unk_180, 0, var_r31->unk_110 * 0xC);
    var_r31->unk_184 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_110 * 8, var_r23->unk_48);
    memset(var_r31->unk_184, 0, var_r31->unk_110 * 8);
    var_r31->unk_188 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_110 * 0xC, var_r23->unk_48);
    memset(var_r31->unk_188, 0, var_r31->unk_110 * 0xC);
    var_r31->unk_18C = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_110 * 0xC, var_r23->unk_48);
    memset(var_r31->unk_18C, 0, var_r31->unk_110 * 0xC);
    var_r31->unk_190 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_110 * 6, var_r23->unk_48);
    memset(var_r31->unk_190, 0, var_r31->unk_110 * 6);
    var_r31->unk_194 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_110 * 0xC, var_r23->unk_48);
    memset(var_r31->unk_194, 0, var_r31->unk_110 * 0xC);
    var_r31->unk_198 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_112[0] * 0xC, var_r23->unk_48);
    memset(var_r31->unk_198, 0, var_r31->unk_112[0] * 0xC);
    var_r31->unk_1A0 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_110, var_r23->unk_48);
    memset(var_r31->unk_1A0, 0, var_r31->unk_110);
    for (var_r30 = 0; var_r30 < var_r31->unk_110; var_r30++) {
        if (((var_r31->unk_112[0] > 0) && (var_r30 >= var_r31->unk_144[0]) && (var_r30 < (var_r31->unk_144[0] + var_r31->unk_112[0])))
            || ((var_r31->unk_112[4] > 0) && (var_r30 >= var_r31->unk_144[4]) && (var_r30 < (var_r31->unk_144[4] + var_r31->unk_112[4])))
            || ((var_r31->unk_112[8] > 0) && (var_r30 >= var_r31->unk_144[8]) && (var_r30 < (var_r31->unk_144[8] + var_r31->unk_112[8])))
            || ((var_r31->unk_112[10] > 0) && (var_r30 >= var_r31->unk_144[10]) && (var_r30 < (var_r31->unk_144[10] + var_r31->unk_112[10])))
            || ((var_r31->unk_112[12] > 0) && (var_r30 >= var_r31->unk_144[12]) && (var_r30 < (var_r31->unk_144[12] + var_r31->unk_112[12])))
            || ((var_r31->unk_112[16] > 0) && (var_r30 >= var_r31->unk_144[16]) && (var_r30 < (var_r31->unk_144[16] + var_r31->unk_112[16])))
            || ((var_r31->unk_112[17] > 0) && (var_r30 >= var_r31->unk_144[17]) && (var_r30 < (var_r31->unk_144[17] + var_r31->unk_112[17])))
            || ((var_r31->unk_112[20] > 0) && (var_r30 >= var_r31->unk_144[20]) && (var_r30 < (var_r31->unk_144[20] + var_r31->unk_112[20])))
            || ((var_r31->unk_112[21] > 0) && (var_r30 >= var_r31->unk_144[21]) && (var_r30 < (var_r31->unk_144[21] + var_r31->unk_112[21])))) {
            var_r31->unk_1A0[var_r30] = 1;
        }
        else {
            var_r31->unk_1A0[var_r30] = 0;
        }
    }
    var_r31->unk_23A.r = 0;
    var_r31->unk_23A.g = 0;
    var_r31->unk_23A.b = 0xFF;
    var_r31->unk_23A.a = 0x40;
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[0]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[0]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[0]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[0]];
    var_f25 = var_f30 = -((0.5f * var_f24) - 25.0f);
    sp20 = var_f28 = sp8;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp14 / (var_r24 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[0] != 0) {
        for (var_r30 = 0; var_r30 < var_r31->unk_10E; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_r29->x = var_f30;
                var_r29->y = var_f28;
                var_r29->z = var_f26;
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f26 = var_f26 + var_f23;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0, var_r24 - 1, var_r24 - 1);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[1]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[1]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[1]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[1]];
    var_f25 = var_f30 = -((0.5f * var_f24) - 25.0f);
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = 0.5f * var_f24;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[1] != 0) {
        for (var_r30 = 0; var_r30 < var_r31->unk_10E; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_r29->x = var_f30;
                var_r29->y = var_f28;
                var_r29->z = var_f26;
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 1, var_r24 - 1, var_r22 - 1);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[2]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[2]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[2]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[2]];
    var_f25 = var_f30 = -(0.5f * var_f24);
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[2] != 0) {
        for (var_r30 = 0; var_r30 < var_r31->unk_10E; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_r29->x = var_f30;
                var_r29->y = var_f28;
                var_r29->z = var_f26;
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f26 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f26 = sp1C;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 2, var_r24 - 1, var_r22 - 1);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[3]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[3]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[3]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[3]];
    var_f25 = var_f30 = 0.5f * var_f24;
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[3] != 0) {
        for (var_r30 = 0; var_r30 < var_r31->unk_10E; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_r29->x = var_f30;
                var_r29->y = var_f28;
                var_r29->z = var_f26;
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f26 -= var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f26 = sp1C;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 3, var_r24 - 1, var_r22 - 1);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[4]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[4]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[4]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[4]];
    var_f25 = var_f30 = -((0.5f * var_f24) - 25.0f);
    sp20 = var_f28 = sp8;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[4] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_f27 = 90.0f * (var_r30 / 4.0f);
                var_r29->x = var_f30;
                var_r29->y = sp20 + (25.0 * (cosd(var_f27) - 1.0));
                var_r29->z = sp1C + (25.0 * sind(var_f27));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 4, var_r24 - 1, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[5]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[5]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[5]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[5]];
    var_f25 = var_f30 = -((0.5f * var_f24) - 25.0f);
    sp20 = var_f28 = 25.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[5] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_f27 = 90.0f + (90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f30;
                var_r29->y = sp20 + (25.0 * cosd(var_f27));
                var_r29->z = sp1C + (25.0 * sind(var_f27));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 5, var_r24 - 1, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[6]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[6]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[6]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[6]];
    var_f25 = var_f30 = -(0.5f * var_f24);
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[6] != 0) {
        for (var_r30 = 0; var_r30 < var_r31->unk_10C; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 90.0f * (var_r27 / 4.0f);
                var_r29->x = var_f25 - (25.0 * (cosd(var_f27) - 1.0));
                var_r29->y = var_f28;
                var_r29->z = sp1C + (25.0 * sind(var_f27));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 6, 4, var_r22 - 1);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[7]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[7]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[7]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[7]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = 0.5f * var_f24;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[7] != 0) {
        for (var_r30 = 0; var_r30 < var_r31->unk_10C; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 90.0f - (90.0f * (var_r27 / 4.0f));
                var_r29->x = var_f25 + (25.0 * cosd(var_f27));
                var_r29->y = var_f28;
                var_r29->z = sp1C + (25.0 * (sind(var_f27) - 1.0));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 7, 4, var_r22 - 1);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[8]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[8]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[8]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[8]];
    var_f25 = var_f30 = -((0.5f * var_f24) - 25.0f);
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[8] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_f27 = 90.0f + (90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f25 + 25.0 * cosd(var_f27);
                var_r29->y = sp20 + (25.0 * sind(var_f27));
                var_r29->z = var_f26;
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f26 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f26 = sp1C;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 8, var_r24 - 1, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[9]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[9]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[9]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[9]];
    var_f25 = var_f30 = -(0.5f * var_f24 - 25.0f);
    sp20 = var_f28 = 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[9] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_f27 = 180.0f + (90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f25 + (25.0 * cosd(var_f27));
                var_r29->y = sp20 + (25.0 * sind(var_f27));
                var_r29->z = var_f26;
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f26 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f26 = sp1C;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 9, var_r24 - 1, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[10]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[10]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[10]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[10]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[10] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_f27 = 90.0f - (90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f25 + (25.0 * cosd(var_f27));
                var_r29->y = sp20 + (25.0 * sind(var_f27));
                var_r29->z = var_f26;
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f26 -= var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f26 = sp1C;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0xA, var_r24 - 1, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[11]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[11]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[11]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[11]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = 25.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[11] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_f27 = -(90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f25 + (25.0 * cosd(var_f27));
                var_r29->y = sp20 + (25.0 * sind(var_f27));
                var_r29->z = var_f26;
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f26 -= var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f26 = sp1C;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0xB, var_r24 - 1, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[12]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[12]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[12]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[12]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[12] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_f27 = 90.0f + (90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f30;
                var_r29->y = sp20 + (25.0 * sind(var_f27));
                var_r29->z = sp1C + (25.0 * cosd(var_f27));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 -= var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0xC, var_r24 - 1, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[13]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[13]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[13]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[13]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[13] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_f27 = 180.0f + (90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f30;
                var_r29->y = sp20 + (25.0 * sind(var_f27));
                var_r29->z = sp1C + (25.0 * cosd(var_f27));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 -= var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0xD, var_r24 - 1, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[14]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[14]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[14]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[14]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[14] != 0) {
        for (var_r30 = 0; var_r30 < var_r31->unk_10C; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = -(90.0f * (var_r27 / 4.0f));
                var_r29->x = var_f25 + (25.0 * cosd(var_f27));
                var_r29->y = var_f28;
                var_r29->z = sp1C + (25.0 * sind(var_f27));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0xE, 4, var_r22 - 1);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[15]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[15]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[15]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[15]];
    var_f25 = var_f30 = -((0.5f * var_f24) - 25.0f);
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[15] != 0) {
        for (var_r30 = 0; var_r30 < var_r31->unk_10C; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = -90.0f - (90.0f * (var_r27 / 4.0f));
                var_r29->x = var_f25 + (25.0 * cosd(var_f27));
                var_r29->y = var_f28;
                var_r29->z = sp1C + (25.0 * sind(var_f27));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0xF, 4, var_r22 - 1);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[16]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[16]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[16]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[16]];
    var_f25 = var_f30 = -((0.5f * var_f24) - 25.0f);
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[16] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 90.0f * (var_r27 / 4.0f);
                var_f22 = 90.0f * (var_r30 / 4.0f);
                var_r29->x = var_f25 - (25.0 * cosd(var_f27) * sind(var_f22));
                var_r29->y = sp20 + (25.0 * cosd(var_f22));
                var_r29->z = sp1C + (25.0 * sind(var_f27) * sind(var_f22));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0x10, 4, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[17]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[17]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[17]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[17]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[17] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 90.0f - (90.0f * (var_r27 / 4.0f));
                var_f22 = -(90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f25 + (25.0 * cosd(var_f27) * -sind(var_f22));
                var_r29->y = sp20 + (25.0 * cosd(var_f22));
                var_r29->z = sp1C + (25.0 * sind(var_f27) * -sind(var_f22));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0x11, 4, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[18]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[18]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[18]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[18]];
    var_f25 = var_f30 = -((0.5f * var_f24) - 25.0f);
    sp20 = var_f28 = 25.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[18] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 90.0f * (var_r27 / 4.0f);
                var_f22 = 90.0f + (90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f25 - (25.0 * cosd(var_f27) * sind(var_f22));
                var_r29->y = sp20 + (25.0 * cosd(var_f22));
                var_r29->z = sp1C + (25.0 * sind(var_f27) * sind(var_f22));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0x12, 4, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[19]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[19]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[19]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[19]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = 25.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[19] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 90.0f * (var_r27 / 4.0f);
                var_f22 = 90.0f * (var_r30 / 4.0f);
                var_r29->x = var_f25 + (25.0 * cosd(var_f27) * sind(var_f22));
                var_r29->y = sp20 - (25.0 * cosd(var_f22));
                var_r29->z = sp1C + (25.0 * sind(var_f27) * sind(var_f22));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0x13, 4, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[20]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[20]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[20]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[20]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[20] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 180.0f + (90.0f * (var_r27 / 4.0f));
                var_f22 = 90.0f * (var_r30 / 4.0f);
                var_r29->x = var_f25 - (25.0 * cosd(var_f27) * sind(var_f22));
                var_r29->y = sp20 + (25.0 * cosd(var_f22));
                var_r29->z = sp1C + (25.0 * sind(var_f27) * sind(var_f22));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0x14, 4, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[21]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[21]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[21]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[21]];
    var_f25 = var_f30 = -(0.5f * var_f24 - 25.0f);
    sp20 = var_f28 = sp8 - 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[21] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 270.0f - (90.0f * (var_r27 / 4.0f));
                var_f22 = -(90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f25 + (cosd(var_f27) * 25.0 * -sind(var_f22));
                var_r29->y = sp20 + 25.0 * cosd(var_f22);
                var_r29->z = sp1C + (25.0 * sind(var_f27) * -sind(var_f22));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0x15, 4, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[22]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[22]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[22]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[22]];
    var_f25 = var_f30 = (0.5f * var_f24) - 25.0f;
    sp20 = var_f28 = 25.0f;
    sp1C = var_f26 = -((0.5f * var_f24) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[22] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 180.0f + (90.0f * (var_r27 / 4.0f));
                var_f22 = 90.0f + (90.0f * (var_r30 / 4.0f));
                var_r29->x = var_f25 - (25.0 * cosd(var_f27) * sind(var_f22));
                var_r29->y = sp20 + (25.0 * cosd(var_f22));
                var_r29->z = sp1C + (25.0 * sind(var_f27) * sind(var_f22));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0x16, 4, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[23]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[23]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[23]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[23]];
    var_f25 = var_f30 = -((var_f24 * 0.5f) - 25.0f);
    sp20 = var_f28 = 25.0f;
    sp1C = var_f26 = -((var_f24 * 0.5f) - 25.0f);
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp10 / (var_r22 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[23] != 0) {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            for (var_r27 = 0; var_r27 < 5; var_r27++) {
                var_f27 = 180.0f + (90.0f * (var_r27 / 4.0f));
                var_f22 = 90.0f * (var_r30 / 4.0f);
                var_r29->x = var_f25 + (25.0 * cosd(var_f27) * sind(var_f22));
                var_r29->y = sp20 - (25.0 * cosd(var_f22));
                var_r29->z = sp1C + (25.0 * sind(var_f27) * sind(var_f22));
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f28 -= var_f18;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0x17, 4, 4);
    }
    var_r29 = &var_r31->unk_17C[var_r31->unk_144[24]];
    var_r26 = &var_r31->unk_188[var_r31->unk_144[24]];
    var_r28 = &var_r31->unk_184[var_r31->unk_144[24]];
    var_r25 = &var_r31->unk_178[var_r31->unk_144[24]];
    var_f25 = var_f30 = -((0.5f * var_f24) - 25.0f);
    sp20 = var_f28 = 0.0f;
    sp1C = var_f26 = (0.5f * var_f24) - 25.0f;
    var_f19 = var_f31 = 0.0f;
    sp18 = var_f29 = 0.0f;
    var_f23 = sp14 / (var_r24 - 1);
    var_f18 = sp14 / (var_r24 - 1);
    var_f21 = 1.0f / (var_r31->unk_10E - 1);
    var_f20 = 1.0f / (var_r31->unk_10E - 1);
    if (var_r31->unk_112[0x18] != 0) {
        for (var_r30 = 0; var_r30 < var_r31->unk_10E; var_r30++) {
            for (var_r27 = 0; var_r27 < var_r31->unk_10E; var_r27++) {
                var_r29->x = var_f30;
                var_r29->y = var_f28;
                var_r29->z = var_f26;
                var_r28->x = var_f31;
                var_r28->y = var_f29;
                var_f30 += var_f23;
                var_f31 += var_f21;
                var_r29++;
                var_r26++;
                var_r28++;
                var_r25++;
            }
            var_f30 = var_f25;
            var_f31 = var_f19;
            var_f26 = var_f26 - var_f23;
            var_f29 += var_f20;
        }
        fn_1_D9A8(var_r31, var_r23, 0x18, var_r24 - 1, var_r24 - 1);
    }
    for (var_r30 = 0; var_r30 < var_r31->unk_110; var_r30++) {
        for (var_r27 = 0; var_r27 < var_r30; var_r27++) {
            var_f30 = var_r31->unk_17C[var_r30].x - var_r31->unk_17C[var_r27].x;
            var_f28 = var_r31->unk_17C[var_r30].y - var_r31->unk_17C[var_r27].y;
            var_f26 = var_r31->unk_17C[var_r30].z - var_r31->unk_17C[var_r27].z;
            sp24 = (var_f26 * var_f26) + ((var_f30 * var_f30) + (var_f28 * var_f28));
            if (sp24 < 10.0f) {
                var_r31->unk_178[var_r30] = var_r27;
                if (var_r31->unk_178[var_r27] != -1) {
                    var_r31->unk_178[var_r30] = var_r31->unk_178[var_r27];
                }
                break;
            }
        }
        if (var_r27 >= var_r30) {
            var_r31->unk_178[var_r30] = -1;
        }
    }
    memcpy(var_r31->unk_180, var_r31->unk_17C, var_r31->unk_110 * 0xC);
    memcpy(var_r31->unk_198, &var_r31->unk_180[var_r31->unk_144[0]], var_r31->unk_112[0] * 0xC);
    var_r31->unk_19C = 0;
    fn_1_DB44(var_r31, var_r23);
    fn_1_DE3C(var_r31, var_r23);
    var_f31 = sqrtf((0.5f * sp8 * (0.5f * sp8)) + ((0.5f * var_f24 * (0.5f * var_f24)) + (0.5f * var_f24 * (0.5f * var_f24))));
    for (var_r30 = 0; var_r30 < var_r31->unk_110; var_r30++) {
        var_f30 = var_r31->unk_17C[var_r30].x;
        var_f28 = var_r31->unk_17C[var_r30].y - (0.5f * sp8);
        var_f26 = var_r31->unk_17C[var_r30].z;
        sp24 = sqrtf((var_f26 * var_f26) + ((var_f30 * var_f30) + (var_f28 * var_f28)));
        var_f27 = sp24;
        sp24 = 1.0f - (sp24 / var_f31);
        if (var_f27 != 0.0f) {
            var_f22 = 1.0f / var_f27;
        }
        else {
            var_f22 = 0.0;
        }
        var_r31->unk_194[var_r30].x = sp24 * (var_f22 * var_r31->unk_17C[var_r30].x);
        var_r31->unk_194[var_r30].y = sp24 * (var_f22 * var_r31->unk_17C[var_r30].y);
        var_r31->unk_194[var_r30].z = sp24 * (var_f22 * var_r31->unk_17C[var_r30].z);
    }
    for (var_r30 = 0; var_r30 < var_r31->unk_110; var_r30++) {
        if ((((var_r31->unk_112[6] <= 0) || (var_r30 < var_r31->unk_144[6]) || (var_r30 >= (var_r31->unk_144[6] + var_r31->unk_112[6])))
                && ((var_r31->unk_112[7] <= 0) || (var_r30 < var_r31->unk_144[7]) || (var_r30 >= (var_r31->unk_144[7] + var_r31->unk_112[7])))
                && ((var_r31->unk_112[0xE] <= 0) || (var_r30 < var_r31->unk_144[0xE]) || (var_r30 >= (var_r31->unk_144[0xE] + var_r31->unk_112[0xE])))
                && ((var_r31->unk_112[0xF] <= 0) || (var_r30 < var_r31->unk_144[0xF]) || (var_r30 >= (var_r31->unk_144[0xF] + var_r31->unk_112[0xF])))
                && ((var_r31->unk_112[4] <= 0) || (var_r30 < var_r31->unk_144[4]) || (var_r30 >= (var_r31->unk_144[4] + var_r31->unk_112[4])))
                && ((var_r31->unk_112[8] <= 0) || (var_r30 < var_r31->unk_144[8]) || (var_r30 >= (var_r31->unk_144[8] + var_r31->unk_112[8])))
                && ((var_r31->unk_112[0xA] <= 0) || (var_r30 < var_r31->unk_144[0xA]) || (var_r30 >= (var_r31->unk_144[0xA] + var_r31->unk_112[0xA])))
                && ((var_r31->unk_112[0xC] <= 0) || (var_r30 < var_r31->unk_144[0xC]) || (var_r30 >= (var_r31->unk_144[0xC] + var_r31->unk_112[0xC])))
                && ((var_r31->unk_112[0x10] <= 0) || (var_r30 < var_r31->unk_144[0x10])
                    || (var_r30 >= (var_r31->unk_144[0x10] + var_r31->unk_112[0x10])))
                && ((var_r31->unk_112[0x11] <= 0) || (var_r30 < var_r31->unk_144[0x11])
                    || (var_r30 >= (var_r31->unk_144[0x11] + var_r31->unk_112[0x11])))
                && ((var_r31->unk_112[0x14] <= 0) || (var_r30 < var_r31->unk_144[0x14])
                    || (var_r30 >= (var_r31->unk_144[0x14] + var_r31->unk_112[0x14])))
                && ((var_r31->unk_112[0x15] <= 0) || (var_r30 < var_r31->unk_144[0x15])
                    || (var_r30 >= (var_r31->unk_144[0x15] + var_r31->unk_112[0x15])))
                && (var_r30 >= var_r31->unk_144[4]))
            || (var_r31->unk_178[var_r30] != -1)) {
            var_r31->unk_18C[var_r30].x = var_r31->unk_18C[var_r30].y = var_r31->unk_18C[var_r30].z = 0.0;
            var_r31->unk_190[var_r30][0] = var_r31->unk_190[var_r30][1] = 0;
            var_r31->unk_190[var_r30][2] = 0;
        }
        else if (((var_r31->unk_112[0] > 0) && (var_r30 >= var_r31->unk_144[0]) && (var_r30 < (var_r31->unk_144[0] + var_r31->unk_112[0])))
            || ((var_r31->unk_112[4] > 0) && (var_r30 >= var_r31->unk_144[4]) && (var_r30 < (var_r31->unk_144[4] + var_r31->unk_112[4])))
            || ((var_r31->unk_112[8] > 0) && (var_r30 >= var_r31->unk_144[8]) && (var_r30 < (var_r31->unk_144[8] + var_r31->unk_112[8])))
            || ((var_r31->unk_112[0xA] > 0) && (var_r30 >= var_r31->unk_144[0xA]) && (var_r30 < (var_r31->unk_144[0xA] + var_r31->unk_112[0xA])))
            || ((var_r31->unk_112[0xC] > 0) && (var_r30 >= var_r31->unk_144[0xC]) && (var_r30 < (var_r31->unk_144[0xC] + var_r31->unk_112[0xC])))
            || ((var_r31->unk_112[0x10] > 0) && (var_r30 >= var_r31->unk_144[0x10]) && (var_r30 < (var_r31->unk_144[0x10] + var_r31->unk_112[0x10])))
            || ((var_r31->unk_112[0x11] > 0) && (var_r30 >= var_r31->unk_144[0x11]) && (var_r30 < (var_r31->unk_144[0x11] + var_r31->unk_112[0x11])))
            || ((var_r31->unk_112[0x14] > 0) && (var_r30 >= var_r31->unk_144[0x14]) && (var_r30 < (var_r31->unk_144[0x14] + var_r31->unk_112[0x14])))
            || ((var_r31->unk_112[0x15] > 0) && (var_r30 >= var_r31->unk_144[0x15])
                && (var_r30 < (var_r31->unk_144[0x15] + var_r31->unk_112[0x15])))) {
            *var_r31->unk_190[var_r30] = var_r31->unk_190[var_r30][1] = 0;
            sp24 = sqrtf((var_r31->unk_17C[var_r30].x * var_r31->unk_17C[var_r30].x) + (var_r31->unk_17C[var_r30].z * var_r31->unk_17C[var_r30].z));
            var_f27 = sp24;
            sp24 = 1.0f - (sp24 / sqrtf(var_f24 * var_f24));
            var_r31->unk_18C[var_r30].y = -(180.0f * sp24);
            var_f27 = sqrtf(var_f27);
            if (var_f27 != 0.0f) {
                var_f22 = 1.0f / var_f27;
            }
            else {
                var_f22 = 0.0;
            }
            var_r31->unk_18C[var_r30].x = sind((180.0f * (var_f22 * var_r31->unk_17C[var_r30].x)));
            var_r31->unk_18C[var_r30].z = sind((180.0f * (var_f22 * var_r31->unk_17C[var_r30].z)));
            var_r31->unk_18C[var_r30].x *= 20.0f * -(1.0f - sp24);
            var_r31->unk_18C[var_r30].z *= (20.0f * -(1.0f - sp24));
            var_r31->unk_190[var_r30][2] = 1;
        }
        else {
            sp24 = sqrtf((var_r31->unk_17C[var_r30].x * var_r31->unk_17C[var_r30].x) + (var_r31->unk_17C[var_r30].z * var_r31->unk_17C[var_r30].z));
            if (sp24 != 0.0f) {
                sp24 = 1.0f / sp24;
            }
            else {
                sp24 = 0.0f;
            }
            var_r31->unk_18C[var_r30].x = -(sp24 * var_r31->unk_17C[var_r30].x);
            var_r31->unk_18C[var_r30].z = -(sp24 * var_r31->unk_17C[var_r30].z);
            var_r31->unk_18C[var_r30].y = 0.0;
            var_f27 = 180.0 + atan2d(var_r31->unk_17C[var_r30].x, var_r31->unk_17C[var_r30].z);
            if (var_f27 > 360.0f) {
                var_f27 = fmod(var_f27, 360.0);
            }
            else if (var_f27 < 0.0f) {
                var_f27 += 360.0f;
            }
            var_f27 = 255.0f * (0.0027777778f * var_f27);
            if (var_f27 >= 255.0f) {
                var_f27 = 255.0f;
            }
            else if (var_f27 < 0.0f) {
                var_f27 = 0.0;
            }
            var_f22 = 64.0f * (var_r31->unk_17C[var_r30].y / sp8);
            if (var_f22 >= 63.0f) {
                var_f22 = 63.0f;
            }
            else if (var_f22 < 0.0f) {
                var_f22 = 0.0;
            }
            var_r31->unk_190[var_r30][0] = var_f27;
            var_r31->unk_190[var_r30][1] = var_f22;
            var_r31->unk_190[var_r30][2] = 2;
        }
    }
    DCFlushRangeNoSync(var_r31->unk_180, var_r31->unk_110 * 0xC);
    DCFlushRangeNoSync(var_r31->unk_17C, var_r31->unk_110 * 0xC);
    DCFlushRangeNoSync(var_r31->unk_188, var_r31->unk_110 * 0xC);
    DCFlushRangeNoSync(var_r31->unk_184, var_r31->unk_110 * 8);
    DCFlushRangeNoSync(var_r31->unk_178, var_r31->unk_110 * 2);
    PPCSync();
    for (var_r21 = 0; var_r21 < 0x19; var_r21++) {
        if ((var_r31->unk_208[var_r21] != 0) && var_r31->unk_1A4[var_r21] && (var_r31->unk_112[var_r21] != 0)) {
            var_r17 = HuMemDirectMallocNum(HEAP_DATA, 0x4000, var_r23->unk_48);
            spC = var_r17;
            (void)var_r18;
            DCFlushRange(var_r17, 0x4000);
            GXBeginDisplayList(spC, 0x4000);
            GXBegin(GX_QUADS, GX_VTXFMT0, var_r31->unk_208[var_r21] * 4);
            var_r20 = var_r31->unk_1A4[var_r21];
            for (var_r30 = 0; var_r30 < var_r31->unk_208[var_r21]; var_r30++) {
                for (var_r27 = 0; var_r27 < 4; var_r27++) {
                    if (var_r31->unk_178[var_r20[var_r27]] == -1) {
                        var_r18 = var_r20[var_r27];
                    }
                    else {
                        var_r18 = var_r31->unk_178[var_r20[var_r27]];
                    }
                    GXPosition1x16(var_r18);
                    GXNormal1x16(var_r18);
                    GXColor1x16(0);
                    GXTexCoord1x16(var_r20[var_r27]);
                }
                var_r20 += 5;
            }
            var_r31->unk_244[var_r21] = GXEndDisplayList();
            if (var_r31->unk_244[var_r21] >= 0x4000) {
                OSReport("ERROR! GList test size over! \n");
            }
            var_r31->unk_2A8[var_r21] = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_244[var_r21], var_r23->unk_48);
            memcpy(var_r31->unk_2A8[var_r21], var_r17, var_r31->unk_244[var_r21]);
            DCFlushRange(var_r31->unk_2A8[var_r21], var_r31->unk_244[var_r21]);
            HuMemDirectFree(var_r17);
        }
    }
    return var_r19;
}

void fn_1_D9A8(M425DllUnkStruct4 *var_r31, ModelData *var_r24, s32 var_r30, s32 var_r26, s32 var_r25)
{
    s16 *var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r31->unk_208[var_r30] = var_r26 * var_r25;
    var_r31->unk_1A4[var_r30] = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_208[var_r30] * 0xA, var_r24->unk_48);
    memset(var_r31->unk_1A4[var_r30], 0, var_r31->unk_208[var_r30] * 0xA);
    var_r29 = var_r31->unk_1A4[var_r30];
    for (var_r28 = 0; var_r28 < var_r25; var_r28++) {
        for (var_r27 = 0; var_r27 < var_r26; var_r27++) {
            var_r29[0] = var_r31->unk_144[var_r30] + (var_r26 + 1) * var_r28 + var_r27;
            var_r29[1] = var_r31->unk_144[var_r30] + (var_r26 + 1) * var_r28 + (var_r27 + 1);
            var_r29[2] = var_r31->unk_144[var_r30] + (var_r26 + 1) * (var_r28 + 1) + (var_r27 + 1);
            var_r29[3] = var_r31->unk_144[var_r30] + (var_r26 + 1) * (var_r28 + 1) + var_r27;
            var_r29 += 5;
        }
    }
    DCFlushRangeNoSync(var_r31->unk_1A4[var_r30], var_r31->unk_208[var_r30] * 0xA);
    PPCSync();
}

void fn_1_DB44(M425DllUnkStruct4 *arg0, ModelData *model)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    s16 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    for (var_r30 = 0; var_r30 < 0x19; var_r30++) {
        if ((arg0->unk_208[var_r30] != 0) && arg0->unk_1A4[var_r30]) {
            for (var_r31 = arg0->unk_1A4[var_r30], var_r29 = 0; var_r29 < arg0->unk_208[var_r30]; var_r29++, var_r31 += 0x5) {
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    if (arg0->unk_178[var_r31[var_r28]] != -1) {
                        var_r31[var_r28] = arg0->unk_178[var_r31[var_r28]];
                    }
                }
            }
        }
    }
    for (var_r30 = 0; var_r30 < 0x19; var_r30++) {
        if ((arg0->unk_208[var_r30] != 0) && arg0->unk_1A4[var_r30]) {
            for (var_r31 = arg0->unk_1A4[var_r30], var_r29 = 0; var_r29 < arg0->unk_208[var_r30]; var_r29++, var_r31 += 0x5) {
                var_f31 = arg0->unk_17C[var_r31[0]].x - arg0->unk_17C[var_r31[1]].x;
                var_f30 = arg0->unk_17C[var_r31[0]].y - arg0->unk_17C[var_r31[1]].y;
                var_f29 = arg0->unk_17C[var_r31[0]].z - arg0->unk_17C[var_r31[1]].z;
                var_f28 = (var_f29 * var_f29) + ((var_f31 * var_f31) + (var_f30 * var_f30));
                if (var_f28 < 10.0f) {
                    var_r31[4] = 1;
                }
                else {
                    var_f31 = arg0->unk_17C[var_r31[0]].x - arg0->unk_17C[var_r31[2]].x;
                    var_f30 = arg0->unk_17C[var_r31[0]].y - arg0->unk_17C[var_r31[2]].y;
                    var_f29 = arg0->unk_17C[var_r31[0]].z - arg0->unk_17C[var_r31[2]].z;
                    var_f28 = (var_f29 * var_f29) + ((var_f31 * var_f31) + (var_f30 * var_f30));
                    if (var_f28 < 10.0f) {
                        var_r31[4] = 2;
                    }
                    else {
                        var_r31[4] = 0;
                    }
                }
            }
        }
    }
}

void fn_1_DE3C(M425DllUnkStruct4 *arg0, ModelData *model)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 var_r30;
    s32 var_r29;
    s16 *var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    memset(arg0->unk_188, 0, arg0->unk_110 * sizeof(Vec));
    for (var_r30 = 0; var_r30 < arg0->unk_240; var_r30++) {
        if ((arg0->unk_208[var_r30] != 0) && arg0->unk_1A4[var_r30]) {
            for (var_r28 = arg0->unk_1A4[var_r30], var_r24 = 0; var_r24 < arg0->unk_208[var_r30]; var_r24++, var_r28 += 5) {
                switch (var_r28[4]) {
                    case 1:
                        var_r27 = 0;
                        var_r29 = 2;
                        var_r26 = 3;
                        var_r25 = 1;
                        break;
                    case 2:
                        var_r27 = 0;
                        var_r29 = 1;
                        var_r26 = 3;
                        var_r25 = 2;
                        break;
                    default:
                        var_r27 = 0;
                        var_r29 = 1;
                        var_r26 = 2;
                        var_r25 = 3;
                        break;
                }
                var_r27 = var_r28[var_r27];
                var_r29 = var_r28[var_r29];
                var_r26 = var_r28[var_r26];
                var_r25 = var_r28[var_r25];
                sp14.x = arg0->unk_180[var_r29].x - arg0->unk_180[var_r27].x;
                sp14.y = arg0->unk_180[var_r29].y - arg0->unk_180[var_r27].y;
                sp14.z = arg0->unk_180[var_r29].z - arg0->unk_180[var_r27].z;
                sp8.x = arg0->unk_180[var_r26].x - arg0->unk_180[var_r29].x;
                sp8.y = arg0->unk_180[var_r26].y - arg0->unk_180[var_r29].y;
                sp8.z = arg0->unk_180[var_r26].z - arg0->unk_180[var_r29].z;
                VECCrossProduct(&sp14, &sp8, &sp20);
                sp20.x *= -1.0f;
                sp20.y *= -1.0f;
                sp20.z *= -1.0f;
                arg0->unk_188[var_r27].x += sp20.x;
                arg0->unk_188[var_r27].y += sp20.y;
                arg0->unk_188[var_r27].z += sp20.z;
                arg0->unk_188[var_r29].x += sp20.x;
                arg0->unk_188[var_r29].y += sp20.y;
                arg0->unk_188[var_r29].z += sp20.z;
                arg0->unk_188[var_r26].x += sp20.x;
                arg0->unk_188[var_r26].y += sp20.y;
                arg0->unk_188[var_r26].z += sp20.z;
                arg0->unk_188[var_r25].x += sp20.x;
                arg0->unk_188[var_r25].y += sp20.y;
                arg0->unk_188[var_r25].z += sp20.z;
            }
        }
    }
    for (var_r30 = 0; var_r30 < arg0->unk_110; var_r30++) {
        VECNormalize(&arg0->unk_188[var_r30], &arg0->unk_188[var_r30]);
    }
}

s32 lbl_1_data_150[3][2] = { { 0x638, 0x63B }, { 0x639, 0x63C }, { 0x63A, 0x63D } };
GXColor lbl_1_data_168 = { 255, 255, 255, 255 };
Mtx lbl_1_data_16C = {
    { 0.5f, 0.0f, 0.0f, -0.5f },
    { 0.0f, 0.5f, 0.0f, -0.5f },
    { 0.0f, 0.0f, 0.5f, -0.5f },
};
Vec lbl_1_data_19C[4] = {
    { -0.5f, 0.5f, 0.0f },
    { 0.5f, 0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f },
};
Vec2f lbl_1_data_1CC[4] = {
    { 0.0f, 0.0f },
    { 0.25f, 0.0f },
    { 0.25f, 0.25f },
    { 0.0f, 0.25f },
};

void fn_1_E210(s32 arg0)
{
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    M425DllUnkStruct4 *var_r31;
    s32 var_r30;
    s32 var_r29;
    LightData *var_r28;
    ModelData *var_r27;
    s32 var_r26;

    if (lbl_1_bss_6EC) {
        var_r27 = &Hu3DData[lbl_1_bss_6EC->model[arg0]];
        var_r31 = var_r27->unk_120;
        for (var_r30 = 0, var_f31 = 0.0f; var_r30 < 6; var_r30++) {
            if ((var_r31->unk_84[var_r30] == -1) || (var_r31->unk_9C[var_r30] < 0.0f)) {
                var_r31->unk_84[var_r30] = -1;
                var_r31->unk_9C[var_r30] = 0.0f;
            }
            else {
                var_f31 += var_r31->unk_9C[var_r30];
                for (var_r29 = 0; var_r29 < 5; var_r29++) {
                    if (var_r31->unk_3C[var_r29] == var_r31->unk_84[var_r30]) {
                        break;
                    }
                }
                if (var_r29 >= 5) {
                    for (var_r29 = 0; var_r29 < 5; var_r29++) {
                        if ((var_r31->unk_3C[var_r29] == -1) && (var_r31->unk_54[var_r29] <= 0.0f)) {
                            break;
                        }
                    }
                }
                if ((var_r29 < 5) && (var_r31->unk_54[var_r29] < var_r31->unk_9C[var_r30])) {
                    var_r31->unk_3C[var_r29] = var_r31->unk_84[var_r30];
                    var_r31->unk_54[var_r29] = var_r31->unk_9C[var_r30];
                    var_r31->unk_6C[var_r29] = var_r31->unk_B4[var_r30];
                }
                var_r31->unk_84[var_r30] = -1;
                var_r31->unk_9C[var_r30] = 0.0f;
                var_r31->unk_B4[var_r30] = 0;
            }
        }
        for (var_r30 = 0, var_r29 = 0, var_r31->unk_14 = 0.0f; var_r30 < 6; var_r30++) {
            if ((var_r31->unk_3C[var_r30] != -1) && (var_r31->unk_54[var_r30] > 0.0f)) {
                var_r31->unk_14 += 0.8f * var_r31->unk_54[var_r30];
                var_r29++;
            }
        }

        for (var_r30 = 0, var_r29 = 0, var_r31->unk_20 = 0.0f; var_r30 < 6; var_r30++) {
            if ((var_r31->unk_3C[var_r30] != -1) && (var_r31->unk_54[var_r30] > 0.0f) && (var_r31->unk_6C[var_r30] != 0)) {
                var_r31->unk_20 += 0.8f * var_r31->unk_54[var_r30];
                var_r29++;
            }
        }
        if (var_r29 != 0) {
            var_r31->unk_18 = 20.0f * (var_r31->unk_20 * var_r31->unk_20);
            var_r31->unk_08 -= var_r31->unk_18;
            if (var_r31->unk_08 < 0.0f) {
                var_r31->unk_08 = 0.0f;
            }
            if ((var_r31->unk_18 > var_r31->unk_1C) && (var_r31->unk_18 >= 0.0f)) {
                if (var_r31->unk_18 >= 13.200000000000001) {
                    var_r26 = HuAudFXPlay(lbl_1_data_150[2][arg0]);
                }
                else if (var_r31->unk_18 >= 6.6000000000000005) {
                    var_r26 = HuAudFXPlay(lbl_1_data_150[1][arg0]);
                }
                else {
                    var_r26 = HuAudFXPlay(lbl_1_data_150[0][arg0]);
                }
                var_f30 = var_r31->unk_08 / 1000.0f;
                if (var_r26 != -1) {
                    HuAudFXPitchSet(var_r26, (s32)(8191.0f * (1.0f - var_f30)));
                }
            }
        }
        else {
            var_r31->unk_18 = 0.0f;
        }
        var_r31->unk_1C = var_r31->unk_18;
        if (var_r31->unk_2C != 0) {
            if (++var_r31->unk_28 >= var_r31->unk_2C) {
                var_r31->unk_2C = var_r31->unk_28 = 0;
                var_r31->unk_30 = 0.0f;
            }
        }
        if ((var_r31->unk_E0 != var_r31->unk_E8) || (var_r31->unk_E4 != var_r31->unk_EC)) {
            sp8.x = sind(var_r31->unk_E4) * cosd(var_r31->unk_E0);
            sp8.z = cosd(var_r31->unk_E4) * cosd(var_r31->unk_E0);
            sp8.y = sind(var_r31->unk_E0);
            VECNormalize(&sp8, &sp8);
            var_r28 = &Hu3DLocalLight[var_r27->unk_38[0]];
            var_r28->unk_1C.x = 1000.0f * sp8.x;
            var_r28->unk_1C.y = 1000.0f * sp8.y;
            var_r28->unk_1C.z = 1000.0f * sp8.z;
            var_r28->unk_28.x = sp8.x;
            var_r28->unk_28.y = sp8.y;
            var_r28->unk_28.z = sp8.z;
            var_r31->unk_E8 = var_r31->unk_E0;
            var_r31->unk_EC = var_r31->unk_E4;
        }
        var_r31->unk_20 = 0.0f;
    }
}

void fn_1_E914(ModelData *var_r27, Mtx matrix)
{
    s32 spB4;
    s32 spB0;
    Mtx sp70;
    Vec sp64;
    Vec sp58;
    float sp48;
    float sp44;
    float sp40;
    float sp3C;
    float sp38;
    float sp34;
    float sp30;
    float sp2C;
    float sp28;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f19;
    float var_f18;

    M425DllUnkStruct4 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s16 var_r28;
    s32 var_r26;

    var_r31 = var_r27->unk_120;
    if (var_r31->unk_2C != 0) {
        var_f24 = (float)var_r31->unk_28 / var_r31->unk_2C;
        var_r31->unk_30 = 0.30000001192092896 * cosd((90.0f * var_f24));
        sp40 = var_r31->unk_30 * (0.5 * sind((720.0f * var_f24)));
    }
    else {
        sp40 = 0.0f;
    }
    if (var_r31->unk_0C != 0.0f) {
        var_f19 = var_r31->unk_08 / var_r31->unk_0C;
    }
    else {
        var_f19 = 1.0f;
    }
    var_r27->scale.y = var_r31->unk_DC = (0.100000024f + (0.9f * var_f19)) - sp40;
    if (var_r31->unk_DC > 0.3f) {
        sp3C = 1.0f - (-0.39999998f * ((var_r31->unk_DC - 0.3f) / 0.7f));
    }
    else {
        sp3C = 0.6f * (var_r31->unk_DC / 0.3f);
    }
    if (var_r31->unk_DC != 0.0f) {
        sp3C /= var_r31->unk_DC;
    }
    else {
        sp3C = 0.0f;
    }
    if (var_r31->unk_08 < 0.0f) {
        sp3C = 0.0f;
    }
    if (var_f19 <= 0.3f) {
        var_f24 = var_f19 / 0.3f;
        var_r31->unk_E0 = 222.0f + (80.0f * var_f24);
    }
    var_f18 = 100.0f * var_r31->unk_14;
    if (var_f19 > 0.85f) {
        var_f18 += 100.0f * (4.0f * (var_f19 - 0.85f));
    }
    if (var_f18 > 150.0f) {
        var_f18 = 150.0f;
    }
    sp38 = 1.0f - var_f19;
    if (var_f18 >= 0.0f) {
        for (var_r30 = 0; var_r30 < var_r31->unk_110; var_r30++) {
            if (var_r31->unk_178[var_r30] == -1) {
                var_r31->unk_180[var_r30].x = var_r31->unk_17C[var_r30].x + (var_f18 * var_r31->unk_194[var_r30].x);
                var_r31->unk_180[var_r30].y = var_r31->unk_17C[var_r30].y + (var_f18 * var_r31->unk_194[var_r30].y);
                var_r31->unk_180[var_r30].z = var_r31->unk_17C[var_r30].z + (var_f18 * var_r31->unk_194[var_r30].z);
            }
        }
    }
    else {
        memcpy(var_r31->unk_180, var_r31->unk_17C, var_r31->unk_110 * 0xC);
    }
    var_r31->unk_14 = 0.0f;
    for (var_r30 = 0; var_r30 < var_r31->unk_110; var_r30++) {
        if (!(var_f19 >= 1.0f) && (var_r31->unk_190[var_r30][2] != 0)) {
            switch (var_r31->unk_190[var_r30][2]) {
                case 1:
                    var_r31->unk_180[var_r30].x += sp38 * var_r31->unk_18C[var_r30].x;
                    var_r31->unk_180[var_r30].y += sp38 * var_r31->unk_18C[var_r30].y;
                    var_r31->unk_180[var_r30].z += sp38 * var_r31->unk_18C[var_r30].z;
                    break;
                case 2:
                    var_f24 = lbl_1_bss_6E4[var_r31->unk_190[var_r30][0] + (var_r31->unk_190[var_r30][1] << 8)];
                    var_f24 = 80.0f * (0.003921569f * (255.0f - var_f24) * sp38);
                    var_r31->unk_180[var_r30].x += var_f24 * var_r31->unk_18C[var_r30].x;
                    var_r31->unk_180[var_r30].y += var_f24 * var_r31->unk_18C[var_r30].y;
                    var_r31->unk_180[var_r30].z += var_f24 * var_r31->unk_18C[var_r30].z;
                    break;
            }
        }
    }
    for (var_r29 = 0, var_r28 = 0, var_f27 = var_f26 = var_f25 = 0.0f; var_r29 < 6; var_r29++) {
        if ((var_r31->unk_54[var_r29] > 0.0f) || (var_r31->unk_3C[var_r29] != -1)) {
            var_f27 += var_r31->unk_180[var_r31->unk_3C[var_r29]].x;
            var_f25 += var_r31->unk_180[var_r31->unk_3C[var_r29]].z;
            var_f26 += var_r31->unk_54[var_r29];
            var_r28++;
        }
    }
    if (var_r28 >= 2) {
        var_f27 /= var_r28;
        var_f25 /= var_r28;
        var_f26 /= var_r28;
        mtxRot(sp70, 0.0f, var_r31->unk_D8, 0.0f);
        var_f30 = var_r31->unk_CC.x + ((sp70[0][0] * var_f27) + (sp70[0][2] * var_f25));
        var_f31 = var_r31->unk_CC.z + ((sp70[2][0] * var_f27) + (sp70[2][2] * var_f25));
        fn_1_10EF8(var_r31->unk_00, 2, var_f30, var_f31);
        var_r31->unk_50 = var_r31->unk_34;
        var_r31->unk_54[5] = var_f26;
        var_r31->unk_6C[5] = 0;
    }
    else {
        var_r31->unk_50 = -1;
        var_r31->unk_54[5] = 0.0f;
        var_r31->unk_6C[5] = 0;
    }
    for (var_r29 = 0; var_r29 < 6; var_r29++) {
        if ((var_r31->unk_54[var_r29] <= 0.0f) || (var_r31->unk_3C[var_r29] == -1)) {
            var_r31->unk_3C[var_r29] = -1;
            var_r31->unk_54[var_r29] = 0.0f;
            var_r31->unk_6C[var_r29] = 0;
        }
        else {
            var_f24 = 150.0f * var_r31->unk_54[var_r29] * sp3C;
            sp44 = 50.0f * var_r31->unk_54[var_r29];
            if (sp44 > 15.000001f) {
                sp44 = 15.000001f;
            }
            var_f27 = var_r31->unk_180[var_r31->unk_3C[var_r29]].x;
            var_f26 = var_r31->unk_180[var_r31->unk_3C[var_r29]].y;
            var_f25 = var_r31->unk_180[var_r31->unk_3C[var_r29]].z;
            if (var_r29 != 5) {
                for (var_r30 = 0; var_r30 < var_r31->unk_110; var_r30++) {
                    if (var_r31->unk_178[var_r30] == -1) {
                        var_f30 = var_r31->unk_180[var_r30].x - var_f27;
                        var_f29 = var_r31->unk_DC * (var_r31->unk_180[var_r30].y - var_f26);
                        var_f31 = 0.425f * (var_r31->unk_180[var_r30].z - var_f25);
                        var_f28 = (var_f31 * var_f31) + ((var_f30 * var_f30) + (var_f29 * var_f29));
                        if (var_f28 < 10000.0f) {
                            var_f28 = sqrtf((var_f31 * var_f31) + ((var_f30 * var_f30) + (var_f29 * var_f29)));
                            var_f28 = var_f28 * 0.01f;
                            var_r31->unk_180[var_r30].y -= (1.0f - var_f28) * var_f24;
                            if (var_r31->unk_180[var_r30].y < 1.0f) {
                                var_r31->unk_180[var_r30].y = 1.0f;
                            }
                        }
                        if (var_r31->unk_1A0[var_r30] != 0) {
                            var_f31 = var_r31->unk_180[var_r30].z - var_f25;
                            if (!(fabs(var_f31) > 100.0)) {
                                var_f28 = sqrtf((var_f30 * var_f30) + (var_f31 * var_f31));
                                if (var_f28 < 200.0f) {
                                    var_f28 = var_f28 * 0.005f;
                                    var_r31->unk_180[var_r30].y += (sp44 * sind((90.0f * var_f28))); // is this right?
                                }
                                else if (var_f28 < 400.0f) {
                                    var_f28 -= 200.0f;
                                    var_f28 = var_f28 * 0.005f;
                                    var_r31->unk_180[var_r30].y += (sp44 * cosd((90.0f * var_f28)));
                                }
                            }
                        }
                    }
                }
            }
            else {
                for (var_r30 = 0; var_r30 < var_r31->unk_110; var_r30++) {
                    if ((var_r31->unk_178[var_r30] == -1) && ((var_r31->unk_F0[0] != var_r30) || (var_r31->unk_F0[1] != var_r30))) {
                        var_f30 = var_r31->unk_180[var_r30].x - var_f27;
                        var_f29 = var_r31->unk_DC * (var_r31->unk_180[var_r30].y - var_f26);
                        var_f31 = 0.425f * (var_r31->unk_180[var_r30].z - var_f25);
                        var_f28 = (var_f31 * var_f31) + ((var_f30 * var_f30) + (var_f29 * var_f29));
                        if (var_f28 < 10000.0f) {
                            var_f28 = sqrtf((var_f31 * var_f31) + ((var_f30 * var_f30) + (var_f29 * var_f29)));
                            var_f28 = var_f28 * 0.01f;
                            var_r31->unk_180[var_r30].y -= (1.0f - var_f28) * var_f24;
                            if (var_r31->unk_180[var_r30].y < 1.0f) {
                                var_r31->unk_180[var_r30].y = 1.0f;
                            }
                        }
                    }
                }
            }
            if (var_r29 < 5) {
                if ((var_r31->unk_54[var_r29] -= 0.075f) <= 0.0f) {
                    var_r31->unk_54[var_r29] = 0.0f;
                    var_r31->unk_3C[var_r29] = -1;
                    var_r31->unk_6C[var_r29] = 0;
                }
            }
            else {
                var_r31->unk_54[var_r29] = 0.0f;
                var_r31->unk_3C[var_r29] = -1;
                var_r31->unk_6C[var_r29] = 0;
            }
        }
    }
    var_r31->unk_38 = 0;
    memcpy(var_r31->unk_198, &var_r31->unk_180[var_r31->unk_144[0]], var_r31->unk_112[0] * 0xC);
    var_r31->unk_19C = 0;
    fn_1_DE3C(var_r31, var_r27);
    if ((var_r31->unk_04 != -1) && (var_r31->unk_06 != -1)) {
        mtxRot(sp70, 0.0f, var_r31->unk_D8, 0.0f);
        sp70[1][0] *= var_r31->unk_DC;
        sp70[1][1] *= var_r31->unk_DC;
        sp70[1][2] *= var_r31->unk_DC;
        var_f30 = var_r31->unk_180[var_r31->unk_06].x;
        var_f29 = var_r31->unk_180[var_r31->unk_06].y;
        var_f31 = var_r31->unk_180[var_r31->unk_06].z;
        var_f27 = var_r31->unk_CC.x + ((sp70[0][2] * var_f31) + ((sp70[0][0] * var_f30) + (sp70[0][1] * var_f29)));
        var_f26 = var_r31->unk_CC.y + ((sp70[1][2] * var_f31) + ((sp70[1][0] * var_f30) + (sp70[1][1] * var_f29)));
        var_f25 = var_r31->unk_CC.z + ((sp70[2][2] * var_f31) + ((sp70[2][0] * var_f30) + (sp70[2][1] * var_f29)));
        Hu3DModelPosSet(var_r31->unk_04, var_f27, var_f26, var_f25);
        var_f30 = var_r31->unk_188[var_r31->unk_06].x;
        var_f29 = var_r31->unk_188[var_r31->unk_06].y;
        var_f31 = var_r31->unk_188[var_r31->unk_06].z;
        sp64.x = var_f27 + (20.0f * var_f30);
        sp64.y = var_f26 + (20.0f * var_f29);
        sp64.z = var_f25 + (20.0f * var_f31);
        sp48 = sqrtf((var_f30 * var_f30) + (var_f31 * var_f31));
        var_f27 = sp34 = atan2d(sp48, var_f29);
        var_f26 = sp30 = atan2d(var_f30, var_f31);
        var_f25 = sp2C = 0.0f;
        Hu3DModelRotSet(var_r31->unk_04, var_f27, var_f26, var_f25);
        var_r30 = (s32)(10.0f * var_r31->unk_18) / 40;
        if (var_r30 > 0x10) {
            var_r30 = 0x10;
        }
        for (var_r26 = 0; var_r26 < var_r30; var_r26++) {
            var_f27 = sp34;
            var_f26 = sp30;
            var_f25 = sp2C;
            var_f27 += 0.5f * ((s32)frand() % 48);
            var_f30 = sind(var_f26) * sind(var_f27);
            var_f31 = cosd(var_f26) * sind(var_f27);
            var_f29 = cosd(var_f27);
            sp28 = 12.0f - ((s32)frand() % 6);
            sp58.x = var_f30;
            sp58.y = var_f29;
            sp58.z = var_f31;
            fn_1_11454(&sp64, &sp58, 50.0f + (5.0f * var_r30), sp28);
        }
    }
    DCFlushRangeNoSync(var_r31->unk_180, var_r31->unk_110 * 0xC);
    DCFlushRangeNoSync(var_r31->unk_188, var_r31->unk_110 * 0xC);
    PPCSync();
}

void fn_1_101C4(ModelData *var_r29, Mtx var_r28)
{
    Mtx sp50;
    ROMtx sp20;
    GXColor sp1C;
    M425DllUnkStruct4 *var_r31;
    s32 var_r30;
    s16 var_r27;

    var_r31 = var_r29->unk_120;
    GXLoadPosMtxImm(var_r28, 0);
    MTXInvXpose(var_r28, sp50);
    GXLoadNrmMtxImm(sp50, 0);
    var_r27 = fn_1_115D4(var_r29, Hu3DCameraMtx, Hu3DCameraMtxXPose, 4.0f);
    if (omPauseChk() == 0) {
        fn_1_E914(var_r29, var_r28);
    }
    var_r29->scale.y = var_r31->unk_DC;
    memcpy(sp50, lbl_1_data_16C, sizeof(lbl_1_data_16C));
    mtxRotCat(&sp50[0], CRot.x, CRot.y + var_r31->unk_D8, 180.0f);
    GXLoadTexMtxImm(sp50, 0x36, GX_MTX2x4);
    sp1C.a = lbl_1_bss_6D0;
    GXSetTevColor(GX_TEVREG2, sp1C);
    HuSprTexLoad(lbl_1_bss_6E0, 0, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_6DC, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_NRM, 0x36, GX_FALSE, 0x7D);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_TEXC, GX_CC_A2, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    lbl_1_bss_6C8.r = var_r31->unk_23A.r;
    lbl_1_bss_6C8.g = var_r31->unk_23A.g;
    lbl_1_bss_6C8.b = var_r31->unk_23A.b;
    lbl_1_bss_6C8.a = var_r31->unk_23A.a;
    GXSetChanAmbColor(GX_COLOR0A0, lbl_1_bss_6C8);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_168);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, var_r27, GX_DF_CLAMP, GX_AF_SPEC);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZMode(1, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    if (HmfInverseMtxF3X3(var_r28, sp50) == 0) {
        MTXIdentity(sp50);
    }
    PSMTXReorder(sp50, sp20);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, var_r31->unk_180, 0xC);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_NRM, var_r31->unk_188, 0xC);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, &var_r31->unk_23A, 4);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetArray(GX_VA_TEX0, var_r31->unk_184, 8);
    for (var_r30 = 0; var_r30 < var_r31->unk_240; var_r30++) {
        if (var_r31->unk_2A8[var_r30] && var_r31->unk_244[var_r30] != 0 && var_r30 != 1) {
            GXCallDisplayList(var_r31->unk_2A8[var_r30], var_r31->unk_244[var_r30]);
        }
    }
    GXSetNumTevStages(2);
    GXSetNumTexGens(2);
    GXSetNumChans(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_NRM, 0x36, GX_FALSE, 0x7D);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOp(GX_TEVSTAGE1, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A2, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    lbl_1_bss_6C8.r = var_r31->unk_23A.r;
    lbl_1_bss_6C8.g = var_r31->unk_23A.g;
    lbl_1_bss_6C8.b = var_r31->unk_23A.b;
    lbl_1_bss_6C8.a = var_r31->unk_23A.a;
    GXSetChanAmbColor(GX_COLOR0A0, lbl_1_bss_6C8);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_168);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, var_r27, GX_DF_CLAMP, GX_AF_SPEC);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetArray(GX_VA_POS, var_r31->unk_180, 0xC);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
    GXSetArray(GX_VA_NRM, var_r31->unk_188, 0xC);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetArray(GX_VA_CLR0, &var_r31->unk_23A, 4);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetArray(GX_VA_TEX0, var_r31->unk_184, 8);
    if (var_r31->unk_2A8[1] && (var_r31->unk_244[1] != 0)) {
        GXCallDisplayList(var_r31->unk_2A8[1], var_r31->unk_244[1]);
    }
}

s32 fn_1_109EC(s32 arg0, s32 arg1, Vec *arg2, Vec *arg3, Vec *arg4, s32 arg5)
{
    float var_f31;
    float var_f30;
    M425DllUnkStruct4 *var_r31;
    s32 var_r29;
    ModelData *var_r26;

    if (!lbl_1_bss_6EC) {
        return;
    }
    var_r26 = &Hu3DData[lbl_1_bss_6EC->model[arg0]];
    var_r31 = var_r26->unk_120;
    if (var_r31->unk_0C != 0.0f) {
        var_f30 = var_r31->unk_08 / var_r31->unk_0C;
    }
    else {
        var_f30 = 1.0f;
    }
    var_r31->unk_24 = fn_1_10EF8(arg0, arg1, arg2->x, arg2->z);
    arg4->x = arg2->x + arg3->x;
    arg4->y = arg2->y + arg3->y;
    arg4->z = arg2->z + arg3->z;
    if ((arg4->y < var_r31->unk_24) && (arg3->y < 0.0f) && (var_r31->unk_34 >= 0)) {
        var_f31 = -arg3->y;
        if (var_f31 > 50.0f) {
            var_f31 = 50.0f;
        }
        else if (var_f31 < 10.0f) {
            var_f31 = 0.0f;
        }
        if ((var_f31 > 0.0f) && (arg5 != 0)) {
            var_f31 = (var_f31 - 10.0f) / 40.0f;
            var_r31->unk_20 += var_f31;
        }
        var_f31 = -arg3->y;
        var_f31 = var_f31 * 0.02f;
        if (var_r31->unk_34 >= 0) {
            for (var_r29 = 0; var_r29 < var_r31->unk_38; var_r29++) {
                if (var_r31->unk_84[var_r29] == var_r31->unk_34) {
                    break;
                }
            }
            if (var_r29 >= var_r31->unk_38) {
                var_r29 = var_r31->unk_38;
            }
            if (var_r29 < 6) {
                var_r31->unk_84[var_r29] = var_r31->unk_34;
                if (var_r31->unk_9C[var_r29] < var_f31) {
                    var_r31->unk_9C[var_r29] = var_f31;
                    var_r31->unk_B4[var_r29] = arg5;
                }
                var_r31->unk_38++;
            }
        }
        arg4->y = var_r31->unk_24 - (150.0f * (var_f30 * var_f31));
        if (arg4->y < 1.0f) {
            arg4->y = 1.0f;
        }
        return 1;
    }
    if (arg4->y < var_r31->unk_24) {
        arg4->y = var_r31->unk_24;
    }
    return 0;
}

float fn_1_10CF4(s32 arg0)
{
    ModelData *var_r31;
    M425DllUnkStruct4 *var_r30;

    if (!lbl_1_bss_6EC) {
        return;
    }
    var_r31 = &Hu3DData[lbl_1_bss_6EC->model[arg0]];
    var_r30 = var_r31->unk_120;
    return var_r30->unk_08;
}

void fn_1_10D54(s32 arg0, float arg8)
{
    ModelData *var_r31;
    M425DllUnkStruct4 *var_r30;

    if (lbl_1_bss_6EC) {
        var_r31 = &Hu3DData[lbl_1_bss_6EC->model[arg0]];
        var_r30 = var_r31->unk_120;
        var_r30->unk_08 = arg8;
    }
}

void fn_1_10DB4(s32 arg0)
{
    M425DllUnkStruct4 *var_r31;
    ModelData *var_r30;

    if (lbl_1_bss_6EC) {
        var_r30 = &Hu3DData[lbl_1_bss_6EC->model[arg0]];
        var_r31 = var_r30->unk_120;
        if (var_r31->unk_2C == 0) {
            var_r31->unk_28 = 0;
            var_r31->unk_2C = 0x28;
            var_r31->unk_30 = 0.3f;
        }
    }
}

void fn_1_10E3C(s32 arg0)
{
    M425DllUnkStruct4 *var_r31;
    s32 var_r30;
    ModelData *var_r29;

    if (lbl_1_bss_6EC) {
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            var_r29 = &Hu3DData[lbl_1_bss_6EC->model[var_r30]];
            var_r31 = var_r29->unk_120;
            if (arg0 != 0) {
                var_r31->unk_110 = var_r31->unk_144[0x18] + var_r31->unk_112[24];
                var_r31->unk_240 = 0x19;
            }
            else {
                var_r31->unk_110 = var_r31->unk_144[0x17] + var_r31->unk_112[23];
                var_r31->unk_240 = 0x18;
            }
        }
    }
}

float fn_1_10EF8(s32 arg0, s32 arg1, float arg8, float arg9)
{
    Mtx spC;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f25;
    M425DllUnkStruct4 *var_r31;
    Vec *var_r30;
    s32 var_r29;
    s32 var_r28;
    ModelData *var_r26;

    if (!lbl_1_bss_6EC) {
        return 0.0f;
    }
    var_r26 = &Hu3DData[lbl_1_bss_6EC->model[arg0]];
    var_r31 = var_r26->unk_120;
    if ((arg1 >= 0) && (arg1 <= 2) && (var_r31->unk_F0[arg1] != -1)) {
        var_r28 = var_r31->unk_F0[arg1];
        var_r31->unk_34 = var_r28;
        if (var_r31->unk_19C == 0) {
            return var_r31->unk_DC * var_r31->unk_198[var_r28].y;
        }
        return var_r31->unk_198[var_r28].y;
    }
    if (var_r31->unk_19C == 0) {
        mtxRot(spC, 0.0f, var_r31->unk_D8, 0.0f);
        spC[1][0] *= var_r31->unk_DC;
        spC[1][1] *= var_r31->unk_DC;
        spC[1][2] *= var_r31->unk_DC;
        for (var_r29 = 0, var_r30 = var_r31->unk_198; var_r29 < var_r31->unk_112[0]; var_r29++, var_r30++) {
            var_f31 = (spC[0][2] * var_r30->z) + ((spC[0][0] * var_r30->x) + (spC[0][1] * var_r30->y));
            var_f25 = (spC[1][2] * var_r30->z) + ((spC[1][0] * var_r30->x) + (spC[1][1] * var_r30->y));
            var_f30 = (spC[2][2] * var_r30->z) + ((spC[2][0] * var_r30->x) + (spC[2][1] * var_r30->y));
            var_r30->x = var_f31;
            var_r30->y = var_f25;
            var_r30->z = var_f30;
        }
        var_r31->unk_19C = 1;
    }
    arg8 -= var_r31->unk_CC.x;
    arg9 -= var_r31->unk_CC.z;
    var_f28 = 10000.0f;
    var_r28 = -1;
    for (var_r29 = 0, var_r30 = var_r31->unk_198; var_r29 < var_r31->unk_112[0]; var_r29++, var_r30++) {
        var_f31 = arg8 - var_r30->x;
        var_f30 = arg9 - var_r30->z;
        if (!(fabs(var_f31) > 100.0)) {
            if (!(fabs(var_f30) > 100.0)) {
                var_f29 = (var_f31 * var_f31) + (var_f30 * var_f30);
                if (var_f29 < var_f28) {
                    var_r28 = var_r29;
                    var_f28 = var_f29;
                }
            }
        }
    }
    (void)var_r29;
    var_r31->unk_34 = var_r28;
    if ((arg1 >= 0) && (arg1 <= 2)) {
        var_r31->unk_F0[arg1] = var_r28;
    }
    if (var_r28 >= 0) {
        return var_r31->unk_198[var_r28].y;
    }
    return 0.0f;
}

void fn_1_11284(void)
{
    lbl_1_bss_6D8 = HuSprAnimRead(HuDataReadNum(0x38000E, 0x10000000));
    lbl_1_bss_6D4 = fn_1_11A74(lbl_1_bss_6D8, 0x40);
    Hu3DModelLayerSet(lbl_1_bss_6D4, 6);
}

void fn_1_112FC(void)
{
    M425DllUnkStruct5 *var_r31;
    M425DllUnkStruct6 *var_r30;
    s32 var_r29;
    ModelData *var_r28;

    var_r28 = &Hu3DData[lbl_1_bss_6D4];
    var_r30 = var_r28->unk_120;
    for (var_r31 = var_r30->unk_3C, var_r29 = 0; var_r29 < var_r30->unk_24; var_r29++, var_r31++) {
        if (!(var_r31->unk_28 <= 0.0f)) {
            var_r31->unk_04.x = var_r31->unk_10.x * var_r31->unk_1C;
            var_r31->unk_04.y = var_r31->unk_10.y * var_r31->unk_1C;
            var_r31->unk_04.z = var_r31->unk_10.z * var_r31->unk_1C;
            var_r31->unk_1C *= 0.95f;
            VECAdd(&var_r31->unk_30, &var_r31->unk_04, &var_r31->unk_30);
            if (++var_r31->unk_40 >= 0xF) {
                var_r31->unk_40 = 0;
                var_r31->unk_28 = 0.0f;
            }
        }
    }
}

void fn_1_11418(void)
{
    HuSprAnimKill(lbl_1_bss_6D8);
    lbl_1_bss_6D8 = NULL;
}

s32 fn_1_11454(Vec *arg0, Vec *arg1, float arg8, float arg9)
{
    M425DllUnkStruct5 *var_r31;
    M425DllUnkStruct6 *var_r29;
    s32 var_r28;
    ModelData *var_r26;

    var_r26 = &Hu3DData[lbl_1_bss_6D4];
    var_r29 = var_r26->unk_120;
    for (var_r31 = var_r29->unk_3C, var_r28 = 0; var_r28 < var_r29->unk_24; var_r28++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {
            break;
        }
    }
    if (var_r28 >= var_r29->unk_24) {
        return -1;
    }
    var_r31->unk_30.x = arg0->x;
    var_r31->unk_30.y = arg0->y;
    var_r31->unk_30.z = arg0->z;
    var_r31->unk_10.x = arg1->x;
    var_r31->unk_10.y = arg1->y;
    var_r31->unk_10.z = arg1->z;
    var_r31->unk_04.x = arg1->x * arg9;
    var_r31->unk_04.y = arg1->y * arg9;
    var_r31->unk_04.z = arg1->z * arg9;
    var_r31->unk_1C = arg9;
    var_r31->unk_28 = arg8;
    var_r31->unk_2C = (s32)frand() % 360;
    var_r31->unk_3C.a = 0x40;
    var_r31->unk_40 = 0;
    return var_r28;
}

s16 fn_1_115D4(ModelData *arg0, Mtx arg1, Mtx arg2, float arg8)
{
    s16 var_r31;
    s16 var_r30;
    LightData *var_r29;
    s16 var_r27;

    var_r27 = 0;
    var_r30 = 1;
    for (var_r29 = Hu3DGlobalLight, var_r31 = 0; var_r31 < 8; var_r31++, var_r29++) {
        if (var_r29->unk_00 != -1) {
            var_r30 <<= 1;
        }
    }
    if ((arg0->attr & 0x1000) != 0) {
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            if (arg0->unk_38[var_r31] != -1) {
                var_r29 = &Hu3DLocalLight[arg0->unk_38[var_r31]];
                fn_1_116E4(arg0, var_r29, var_r30, arg2, arg1, arg8);
                var_r27 |= var_r30;
                var_r30 <<= 1;
            }
        }
    }
    return var_r27;
}

void fn_1_116E4(ModelData *arg1, LightData *var_r31, s16 sp8, Mtx spC, Mtx sp10, float var_f31)
{
    switch ((u8)var_r31->unk_00) {
        case 0:
            GXInitLightAttn(&lbl_1_bss_688, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            GXInitLightSpot(&lbl_1_bss_688, var_r31->unk_04, var_r31->unk_02);
            break;
        case 1:
            GXInitLightAttn(&lbl_1_bss_688, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            VECScale(&var_r31->unk_28, &var_r31->unk_1C, -100000.0f);
            break;
        case 2:
            GXInitLightAttn(&lbl_1_bss_688, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            GXInitLightDistAttn(&lbl_1_bss_688, var_r31->unk_04, var_r31->unk_08, var_r31->unk_02);
            break;
    }
    if ((var_r31->unk_00 & 0x8000) != 0) {
        MTXMultVec(spC, &var_r31->unk_28, &lbl_1_bss_67C);
        MTXMultVec(sp10, &var_r31->unk_1C, &lbl_1_bss_670);
        GXInitLightPos(&lbl_1_bss_688, lbl_1_bss_670.x, lbl_1_bss_670.y, lbl_1_bss_670.z);
    }
    else {
        GXInitLightPos(&lbl_1_bss_688, var_r31->unk_1C.x, var_r31->unk_1C.y, var_r31->unk_1C.z);
        lbl_1_bss_67C = var_r31->unk_28;
    }
    if (var_f31 == 0.0f) {
        GXInitLightDir(&lbl_1_bss_688, lbl_1_bss_67C.x, lbl_1_bss_67C.y, lbl_1_bss_67C.z);
    }
    else {
        GXInitSpecularDir(&lbl_1_bss_688, lbl_1_bss_67C.x, lbl_1_bss_67C.y, lbl_1_bss_67C.z);
        GXInitLightAttn(&lbl_1_bss_688, 0.0f, 0.0f, 1.0f, var_f31 / 2, 0.0f, 1.0f - (var_f31 / 2));
    }
    GXInitLightColor(&lbl_1_bss_688, var_r31->color);
    GXLoadLightObjImm(&lbl_1_bss_688, sp8);
}

s16 fn_1_11A74(AnimData *arg0, s16 arg1)
{
    M425DllUnkStruct6 *var_r31;
    s16 var_r30;
    Vec2f *var_r29;
    M425DllUnkStruct5 *var_r28;
    ModelData *var_r27;
    Vec *var_r26;
    void *var_r24;
    s16 var_r23;
    void *var_r21;

    var_r23 = Hu3DHookFuncCreate(fn_1_11EE0);
    var_r27 = &Hu3DData[var_r23];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(M425DllUnkStruct6), var_r27->unk_48);
    var_r27->unk_120 = var_r31;
    var_r31->unk_38 = arg0;
    arg0->useNum++;
    var_r31->unk_24 = arg1;
    var_r31->unk_20 = 0;
    var_r31->unk_4C = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_21 = 0;
    var_r31->unk_30 = 0;
    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r28 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(M425DllUnkStruct5), var_r27->unk_48);
    var_r31->unk_3C = var_r28;
    for (var_r30 = 0; var_r30 < arg1; var_r30++, var_r28++) {
        var_r28->unk_28 = 0.0f;
        var_r28->unk_2C = 0.0f;
        var_r28->unk_30.x = (s32)((frand() & 0x7F) - 0x40) * 0x14;
        var_r28->unk_30.y = (s32)((frand() & 0x7F) - 0x40) * 0x1E;
        var_r28->unk_30.z = (s32)((frand() & 0x7F) - 0x40) * 0x14;
        var_r28->unk_3C.r = var_r28->unk_3C.g = var_r28->unk_3C.b = var_r28->unk_3C.a = 0xFF;
        var_r28->unk_40 = 0;
    }
    var_r26 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec) * 4, var_r27->unk_48);
    var_r31->unk_40 = var_r26;
    for (var_r30 = 0; var_r30 < (arg1 * 4); var_r30++, var_r26++) {
        var_r26->x = var_r26->y = var_r26->z = 0.0f;
    }
    var_r29 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec2f) * 4, var_r27->unk_48);
    var_r31->unk_44 = var_r29;
    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        var_r29->x = 0.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 1.0f;
        var_r29++;
        var_r29->x = 0.0f;
        var_r29->y = 1.0f;
        var_r29++;
    }
    var_r24 = HuMemDirectMallocNum(HEAP_DATA, 0x4000, var_r27->unk_48);
    var_r21 = var_r24;
    DCFlushRange(var_r24, 0x4000);
    GXBeginDisplayList(var_r21, 0x4000);
    GXBegin(GX_QUADS, GX_VTXFMT0, arg1 * 4);
    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        GXUnknownu16(var_r30 * 4);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4);
        GXUnknownu16(var_r30 * 4 + 1);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4 + 1);
        GXUnknownu16(var_r30 * 4 + 2);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4 + 2);
        GXUnknownu16(var_r30 * 4 + 3);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4 + 3);
    }
    var_r31->unk_34 = GXEndDisplayList();
    var_r31->unk_48 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_34, var_r27->unk_48);
    memcpy(var_r31->unk_48, var_r24, var_r31->unk_34);
    DCFlushRange(var_r31->unk_48, var_r31->unk_34);
    HuMemDirectFree(var_r24);
    return var_r23;
}

void fn_1_11EE0(ModelData *var_r24, Mtx var_r21)
{
    Mtx sp128;
    Mtx spF8;
    Mtx spC8;
    Vec sp98[4];
    Vec sp68[4];
    Vec sp38[4];
    ROMtx sp8;
    M425DllUnkStruct6 *var_r31;
    Vec *var_r30;
    M425DllUnkStruct5 *var_r29;
    Vec *var_r28;
    Vec *var_r27;
    Vec2f *var_r26;
    s16 var_r25;
    s16 var_r23;
    s16 var_r22;
    s16 var_r20;
    s16 var_r19;
    UnkHook var_r18;

    var_r31 = var_r24->unk_120;
    if ((var_r31->unk_2C != GlobalCounter) || (shadowModelDrawF != 0)) {
        GXLoadPosMtxImm(var_r21, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        if (shadowModelDrawF != 0) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetZMode(0, GX_LEQUAL, 0);
        }
        else {
            var_r22 = var_r31->unk_38->bmp->dataFmt & 0xF;
            if ((var_r22 == 7) || (var_r22 == 8)) {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            }
            else {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            }
            if ((var_r24->attr & 2) != 0) {
                GXSetZMode(1, GX_LEQUAL, GX_TRUE);
            }
            else {
                GXSetZMode(1, GX_LEQUAL, GX_FALSE);
            }
        }
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
        HuSprTexLoad(var_r31->unk_38, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(0);
        switch (var_r31->unk_20) {
            case 0:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
                break;
            case 1:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
                break;
            case 2:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
                break;
        }
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
        GXSetArray(GX_VA_POS, var_r31->unk_40, 0xC);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
        GXSetArray(GX_VA_CLR0, &var_r31->unk_3C->unk_3C, 0x44);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
        GXSetArray(GX_VA_TEX0, var_r31->unk_44, 8);
        if (HmfInverseMtxF3X3(var_r21, sp128) == 0) {
            MTXIdentity(sp128);
        }
        PSMTXReorder(sp128, &sp8[0]);
        if (var_r31->unk_4C) {
            var_r18 = var_r31->unk_4C;
            var_r18(var_r24, var_r31, var_r21);
        }
        var_r29 = var_r31->unk_3C;
        var_r30 = var_r31->unk_40;
        var_r26 = var_r31->unk_44;
        PSMTXROMultVecArray(sp8, lbl_1_data_19C, &sp38[0], 4);
        for (var_r23 = 0; var_r23 < var_r31->unk_24; var_r23++, var_r29++) {
            if (!var_r29->unk_28) {
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
            }
            else {
                if (!var_r29->unk_2C) {
                    var_r28 = &sp98[0];
                    var_r27 = &sp38[0];
                    VECScale(var_r27++, var_r28, var_r29->unk_28);
                    VECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                    VECScale(var_r27++, var_r28, var_r29->unk_28);
                    VECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                    VECScale(var_r27++, var_r28, var_r29->unk_28);
                    VECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                    VECScale(var_r27++, var_r28, var_r29->unk_28);
                    VECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                }
                else {
                    VECScale(lbl_1_data_19C, &sp98[0], var_r29->unk_28);
                    VECScale(&lbl_1_data_19C[1], &sp98[1], var_r29->unk_28);
                    VECScale(&lbl_1_data_19C[2], &sp98[2], var_r29->unk_28);
                    VECScale(&lbl_1_data_19C[3], &sp98[3], var_r29->unk_28);
                    MTXRotRad(spC8, 0x5A, var_r29->unk_2C);
                    MTXConcat(sp128, spC8, spF8);
                    MTXMultVecArray(spF8, &sp98[0], &sp68[0], 4);
                    VECAdd(&sp68[0], &var_r29->unk_30, var_r30++);
                    VECAdd(&sp68[1], &var_r29->unk_30, var_r30++);
                    VECAdd(&sp68[2], &var_r29->unk_30, var_r30++);
                    VECAdd(&sp68[3], &var_r29->unk_30, var_r30++);
                }
                var_r20 = var_r29->unk_40 & 3;
                var_r19 = (var_r29->unk_40 >> 2) & 3;
                for (var_r25 = 0; var_r25 < 4; var_r25++, var_r26++) {
                    var_r26->x = (0.25f * var_r20) + lbl_1_data_1CC[var_r25].x;
                    var_r26->y = (0.25f * var_r19) + lbl_1_data_1CC[var_r25].y;
                }
            }
        }
        DCFlushRangeNoSync(var_r31->unk_40, var_r31->unk_24 * 0xC * 4);
        DCFlushRangeNoSync(var_r31->unk_44, var_r31->unk_24 * 8 * 4);
        PPCSync();
        GXCallDisplayList(var_r31->unk_48, var_r31->unk_34);
        if (shadowModelDrawF == 0) {
            if ((var_r31->unk_21 & 2) == 0) {
                var_r31->unk_28++;
            }
            if ((var_r31->unk_30 != 0) && (var_r31->unk_30 <= var_r31->unk_28)) {
                if ((var_r31->unk_21 & 1) != 0) {
                    var_r31->unk_28 = 0;
                }
                var_r31->unk_28 = var_r31->unk_30;
            }
            var_r31->unk_2C = GlobalCounter;
        }
    }
}

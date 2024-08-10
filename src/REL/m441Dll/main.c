#include "REL/executor.h"
#include "game/chrman.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/frand.h"
#include "game/wipe.h"
#include "game/minigame_seq.h"

#include "game/gamework_data.h"

#include "game/pad.h"
#include "game/printfunc.h"
#include "game/mapspace.h"

#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"

#include "game/esprite.h"
#include "game/sprite.h"

#include "ext_math.h"
#include "rel_sqrt_consts.h"


#undef ABS
#define ABS(x) ((0 > (x)) ? -(x) : (x))

typedef struct unk_bss_1F8_struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ struct unk_bss_1F8_struct *unk04;
    /* 0x08 */ struct unk_bss_1F8_struct *unk08;
} UnkBss1F8Struct; // Size 0xC

typedef struct unk_bss_1E0_struct {
    /* 0x00 */ HsfanimStruct00 *unk00;
    /* 0x04 */ s32 *unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ struct unk_bss_1E0_struct *unk10;
    /* 0x14 */ struct unk_bss_1E0_struct *unk14;
} UnkBss1E0Struct; // Size 0x18

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ s16 unk04;
} UnkBss1B0Struct; // Size 8

UnkBss1F8Struct lbl_1_bss_1F8;
UnkBss1E0Struct lbl_1_bss_1E0;
Process *lbl_1_bss_1DC;
Vec lbl_1_bss_1D0;
Vec lbl_1_bss_1C4;
Vec lbl_1_bss_1B8;
Vec lbl_1_bss_1AC;
u32 lbl_1_bss_1A8;
s32 lbl_1_bss_1A4;
u32 lbl_1_bss_1A0;
s16 lbl_1_bss_19E;
s16 lbl_1_bss_19C;
s32 lbl_1_bss_198;
s32 lbl_1_bss_194;
float lbl_1_bss_190;
s32 lbl_1_bss_150[16];
UnkBss1B0Struct lbl_1_bss_50[32];

void fn_1_0(void) {
    lbl_1_bss_1F8.unk04 = NULL;
    lbl_1_bss_1F8.unk08 = NULL;
}

void fn_1_24(u16 arg0, s16 arg1) {
    UnkBss1F8Struct *temp_r31;
    UnkBss1F8Struct *temp_r30;
    UnkBss1F8Struct *temp_r29;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r31), MEMORY_DEFAULT_NUM);
    temp_r31->unk00 = arg0;
    temp_r31->unk02 = arg1;
    temp_r30 = &lbl_1_bss_1F8;
    temp_r29 = temp_r30->unk08;
    temp_r30->unk08 = temp_r31;
    if (NULL != temp_r29) {
        temp_r29->unk04 = temp_r31;
    }
    temp_r31->unk04 = temp_r30;
    temp_r31->unk08 = temp_r29;
}

s16 fn_1_AC(s16 arg0) {
    UnkBss1F8Struct *var_r31;
    UnkBss1F8Struct *temp_r29;
    UnkBss1F8Struct *temp_r30;
    s16 temp_r28;

    var_r31 = lbl_1_bss_1F8.unk08;
    while (NULL != var_r31) {
        if (arg0 == var_r31->unk00) {
            temp_r28 = var_r31->unk02;
            temp_r29 = var_r31->unk04;
            temp_r30 = var_r31->unk08;
            temp_r29->unk08 = temp_r30;
            if (NULL != temp_r30) {
                temp_r30->unk04 = temp_r29;
            }
            HuMemDirectFree(var_r31);
            return temp_r28;
        }
        var_r31 = var_r31->unk08;
    }
    return -1;
}

void fn_1_150(void) {
    lbl_1_bss_1E0.unk10 = NULL;
    lbl_1_bss_1E0.unk14 = NULL;
}

void fn_1_174(s16 arg0, HsfanimStruct00 *arg1, s32 arg2, s32 arg3, s32 arg4, Vec *arg5, u8 arg6) {
    UnkBss1E0Struct *temp_r27;
    UnkBss1E0Struct *var_r31;
    UnkBss1E0Struct *temp_r28;
    s32 i;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*var_r31), MEMORY_DEFAULT_NUM);
    var_r31->unk00 = arg1;
    var_r31->unk08 = arg3;
    var_r31->unk0C = arg4;
    var_r31->unk04 = HuMemDirectMallocNum(HEAP_SYSTEM, arg4 * sizeof(*var_r31->unk04), MEMORY_DEFAULT_NUM);
    for (i = 0; i < arg4; i++, arg5++) {
        var_r31->unk04[i] = Hu3DParManLink(arg0, arg1);
        if (var_r31->unk04[i] >= 0) {
            Hu3DParManAttrReset(var_r31->unk04[i], 1);
            Hu3DParManPosSet(var_r31->unk04[i], arg5->x, arg5->y, arg5->z);
            Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(var_r31->unk04[i]), arg6);
            Hu3DModelLayerSet(Hu3DParManModelIDGet(var_r31->unk04[i]), arg2);
        }
    }
    temp_r28 = &lbl_1_bss_1E0;
    temp_r27 = temp_r28->unk14;
    temp_r28->unk14 = var_r31;
    if (NULL != temp_r27) {
        temp_r27->unk10 = var_r31;
    }
    var_r31->unk10 = temp_r28;
    var_r31->unk14 = temp_r27;
}

void fn_1_2D8(void) {
    UnkBss1E0Struct *var_r31;
    UnkBss1E0Struct *temp_r28;
    UnkBss1E0Struct *temp_r29;
    s32 i;

    var_r31 = lbl_1_bss_1E0.unk14;
    while (NULL != var_r31) {
        var_r31->unk08--;
        if (var_r31->unk08 == 0) {
            for (i = 0; i < var_r31->unk0C; i++) {
                if (var_r31->unk04[i] >= 0) {
                    Hu3DParManAttrSet(var_r31->unk04[i], 1);
                }
            }
        }
        temp_r28 = var_r31->unk10;
        temp_r29 = var_r31->unk14;
        if (-var_r31->unk00->unk00 > var_r31->unk08) {
            for (i = 0; i < var_r31->unk0C; i++) {
                if (var_r31->unk04[i] >= 0) {
                    Hu3DParManKill(var_r31->unk04[i]);
                }
            }
            temp_r28->unk14 = temp_r29;
            if (NULL != temp_r29) {
                temp_r29->unk10 = temp_r28;
            }
            HuMemDirectFree(var_r31->unk04);
            HuMemDirectFree(var_r31);
        }
        var_r31 = temp_r29;
    }
}

void fn_1_414(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        lbl_1_bss_50[i].unk00 = 0;
        lbl_1_bss_50[i].unk04 = -1;
    }
}

s16 fn_1_46C(s32 arg0) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (arg0 == lbl_1_bss_50[i].unk00) {
            return Hu3DModelLink(lbl_1_bss_50[i].unk04);
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_1_bss_50[i].unk00 == 0) {
            lbl_1_bss_50[i].unk00 = arg0;
            lbl_1_bss_50[i].unk04 = Hu3DModelCreateFile(arg0);
            return lbl_1_bss_50[i].unk04;
        }
    }
    return Hu3DModelCreateFile(arg0);
}

void fn_1_580(s32 *arg0, s32 arg1, s32 arg2) {
    s32 var_r30;

    espBankSet(arg0[arg1 + 1], 10);
    espBankSet(arg0[arg1 + 4], 11);
    if (36000 <= arg2) {
        arg2 = 35999;
    }
    var_r30 = arg2 / 3600;
    arg2 -= var_r30 * 3600;
    if (var_r30 > 9) {
        var_r30 = 9;
    }
    espBankSet(arg0[arg1], var_r30);
    var_r30 = arg2 / 60;
    arg2 -= var_r30 * 60;
    espBankSet(arg0[arg1 + 2], var_r30 / 10);
    espBankSet(arg0[arg1 + 3], var_r30 % 10);
    var_r30 = 101.5f * arg2 / 60.0f;
    espBankSet(arg0[arg1 + 5], var_r30 / 10);
    espBankSet(arg0[arg1 + 6], var_r30 % 10);
}

void fn_1_798(s32 arg0) {
    lbl_1_bss_190 = 0.0f;
    lbl_1_bss_1A0 = lbl_1_bss_1A4;
    GWMGRecordSet(arg0, lbl_1_bss_1A0);
    fn_1_580(lbl_1_bss_150, 7, lbl_1_bss_1A4);
}

void fn_1_9EC(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        espDispOn(lbl_1_bss_150[i]);
    }
}

void fn_1_A40(void) {
    float temp_f31;
    s32 i;

    if (0.0f <= lbl_1_bss_190) {
        lbl_1_bss_190 += 16.0f;
        temp_f31 = 1.0 + 0.2f * sind(lbl_1_bss_190);
        for (i = 7; i <= 14; i++) {
            espScaleSet(lbl_1_bss_150[i], temp_f31, temp_f31);
        }
    }
}

void fn_1_B4C(float arg0, s32 arg1) {
    float temp_f30;
    float temp_f31;
    s32 i;

    temp_f31 = 288.0f;
    temp_f30 = arg0;
    lbl_1_bss_150[15] = espEntry(arg1, 0, 0);
    espTPLvlSet(lbl_1_bss_150[15], 0.5f);
    espColorSet(lbl_1_bss_150[15], 0, 0, 0);
    espPosSet(lbl_1_bss_150[15], temp_f31, temp_f30);
    temp_f31 = 248.0f;
    temp_f30 = arg0 - 8.0f;
    lbl_1_bss_150[14] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 55), 0, 0);
    espPosSet(lbl_1_bss_150[14], temp_f31 - 18.0f, temp_f30);
    for (i = 7; i <= 13; i++) {
        lbl_1_bss_150[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 48), 0, 0);
        espPosSet(lbl_1_bss_150[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_150, 7, lbl_1_bss_1A0);
    temp_f31 = 248.0f;
    temp_f30 = arg0 + 8.0f;
    for (i = 0; i <= 6; i++) {
        lbl_1_bss_150[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 49), 0, 0);
        espPosSet(lbl_1_bss_150[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_150, 0, 0);
    for (i = 0; i < 16; i++) {
        espDrawNoSet(lbl_1_bss_150[i], 0);
        espDispOff(lbl_1_bss_150[i]);
        espAttrSet(lbl_1_bss_150[i], HUSPR_ATTR_NOANIM);
        espPriSet(lbl_1_bss_150[i], 0x80 + i);
    }
}

void fn_1_11F4(float arg0, Vec *arg1, Vec *arg2, Vec *arg3) {
    float temp_f31;

    if (1.0f < arg0) {
        arg0 = 1.0f;
    }
    temp_f31 = sind(90.0f * arg0) * sind(90.0f * arg0);
    arg3->x = arg1->x + temp_f31 * (arg2->x - arg1->x);
    arg3->y = arg1->y + temp_f31 * (arg2->y - arg1->y);
    arg3->z = arg1->z + temp_f31 * (arg2->z - arg1->z);
}

void fn_1_1350(Vec *arg0, Vec *arg1, Vec *arg2) {
    Hu3DCameraPosSetV(1, arg0, arg1, arg2);
    lbl_1_bss_1D0 = *arg0;
    lbl_1_bss_1B8 = *arg2;
}

s32 fn_1_13DC(float arg0, Vec *arg1) {
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_1D0, &lbl_1_bss_1C4, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_1B8, &lbl_1_bss_1AC, &spC);
    Hu3DCameraPosSetV(1, &sp18, arg1, &spC);
    if (1.0f <= arg0) {
        return 1;
    } else {
        lbl_1_bss_194 = 1;
        return 0;
    }
}

void fn_1_1710(float arg0, Vec *arg1) {
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_1D0, &lbl_1_bss_1C4, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_1B8, &lbl_1_bss_1AC, &spC);
    fn_1_1350(&sp18, arg1, &spC);
    lbl_1_bss_194 = 1;
}

void fn_1_1A60(Vec *arg0, s16 arg1, Vec *arg2) {
    Mtx sp1C;
    Vec sp10;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f31;
    CameraData *temp_r31;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            break;
        }
    }
    temp_r31 = &Hu3DCamera[i];
    MTXLookAt(sp1C, &temp_r31->pos, &temp_r31->up, &temp_r31->target);
    MTXMultVec(sp1C, arg0, &sp10);
    temp_f30 = sp10.z * (sind(temp_r31->fov / 2) / cosd(temp_r31->fov / 2)) * temp_r31->aspect;
    temp_f29 = sp10.z * (sind(temp_r31->fov / 2) / cosd(temp_r31->fov / 2));
    temp_f28 = 0.9f * temp_r31->viewport_x;
    temp_f31 = 0.9f * temp_r31->viewport_w;
    arg2->x = temp_f31 / 2 + sp10.x * ((temp_f31 / 2) / -temp_f30) + temp_f28;
    arg2->y = temp_r31->viewport_h / 2 + sp10.y * ((temp_r31->viewport_h / 2) / temp_f29) + temp_r31->viewport_y;
    arg2->z = 0.0f;
}

void fn_1_1D18(s16 arg0, char *arg1, Vec *arg2) {
    Mtx sp10;

    Hu3DModelObjMtxGet(arg0, arg1, sp10);
    arg2->x = sp10[0][3];
    arg2->y = sp10[1][3];
    arg2->z = sp10[2][3];
}

void fn_1_1D70(s16 arg0, char *arg1, Vec *arg2, Mtx arg3) {
    Mtx spC;
    ModelData *var_r30;

    var_r30 = &Hu3DData[arg0];
    Hu3DModelObjMtxGet(arg0, arg1, spC);
    PSMTXConcat(var_r30->unk_F0, spC, spC);
    if (NULL != arg3) {
        PSMTXCopy(spC, arg3);
    }
    arg2->x = spC[0][3];
    arg2->y = spC[1][3];
    arg2->z = spC[2][3];
}

float fn_1_1E20(float arg0, float arg1, float arg2) {
    float var_f31;
    float var_f30;

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

void fn_1_1F24(s32 arg0) {
    lbl_1_bss_198 = HuAudSeqPlay((s32)arg0);
}

void fn_1_1F58(s32 arg0) {
    if (lbl_1_bss_198 >= 0) {
        if (arg0 < 0) {
            arg0 = 1000;
        }
        HuAudSeqFadeOut(lbl_1_bss_198, arg0);
    }
    lbl_1_bss_198 = -1;
}

void fn_1_1FC4(Vec *arg0, float *arg1, s32 arg2, s32 arg3) {
    Vec sp18;
    float var_f28;
    s32 var_r30;

    sp18.x = 0.0f;
    sp18.y = 0.0f;
    sp18.z = 0.0f;
    sp18.x = arg2 / 4.0f;
    sp18.z = -(float) arg3 / 4.0f;
    var_r30 = 0;
    var_f28 = VECMagXZ(&sp18);
    if (0.5f <= var_f28) {
        if (10.0f <= var_f28) {
            sp18.x /= var_f28;
            sp18.z /= var_f28;
            var_f28 = 10.0f;
            sp18.x = 10.0f * sp18.x;
            sp18.z = 10.0f * sp18.z;
        }
        *arg1 = fn_1_1E20(*arg1, atan2d(sp18.x, sp18.z), 0.4f);
        if (8.0f <= var_f28) {
            var_r30 = 2;
        } else {
            var_r30 = 1;
        }
    }
    PSVECAdd((Vec*) &arg0, &sp18, (Vec*) &arg0);
}

omObjData *lbl_1_bss_4C;
omObjData **lbl_1_bss_48;
omObjData **lbl_1_bss_44;
omObjData **lbl_1_bss_40;
s32 lbl_1_bss_3C;
AnimData *lbl_1_bss_38;
s16 lbl_1_bss_34;
AnimData *lbl_1_bss_30;
s16 lbl_1_bss_2C;
float lbl_1_bss_28;
float lbl_1_bss_24;
s16 lbl_1_bss_20;
s16 lbl_1_bss_1E;
s16 lbl_1_bss_18[3];
s16 lbl_1_bss_12[3];
s16 lbl_1_bss_10[1];
s32 lbl_1_bss_C;
float lbl_1_bss_8;
float lbl_1_bss_4;
float lbl_1_bss_0;

s16 lbl_1_data_0[8] = {
	0, 1, 2, 3,
	4, 5, 6, 7
};

Vec lbl_1_data_10 = { 0, 100, 400 };
Vec lbl_1_data_1C = { 0, 1, 0 };
Vec lbl_1_data_28 = { 0, 100, 0 };
Vec lbl_1_data_34 = { 0, 1200, 2100 };
Vec lbl_1_data_40 = { 0, 1, 0 };
Vec lbl_1_data_4C = { 0, 0, 0 };
Vec lbl_1_data_58 = { 0, 200, 1000 };
Vec lbl_1_data_64 = { 0, 1, 0 };
Vec lbl_1_data_70 = { 0, 150, 0 };
Vec lbl_1_data_7C = { 0, 3000, 1000 };
Vec lbl_1_data_88 = { 0, -3, -1 };
GXColor lbl_1_data_94 = { 255, 255, 255, 255 };
Vec lbl_1_data_98 = { 0, 3000, 1000 };
Vec lbl_1_data_A4 = { 0, 0, 0 };

s32 lbl_1_data_B0[8][16] = {
	{
		0x005F0000, 
		0x00480000,
		0x00480008, 
		0x00480010, 
		0x00480018, 
		0x00480020, 
		0x005F0000, 
		0x00480030, 
		0x00480028, 
		0x005F0017, 
		0x005F0018
	},
	{
		0x001A0000,
		0x00480001,
		0x00480009,
		0x00480011,
		0x00480019,
		0x00480021,
		0x001A0000,
		0x00480031,
		0x00480029,
		0x001A0017,
		0x001A0018
	},
	{
		0x006D0000,
		0x00480002,
		0x0048000A,
		0x00480012,
		0x0048001A,
		0x00480022,
		0x006D0000,
		0x00480032,
		0x0048002A,
		0x006D0017,
		0x006D0018
	},
	{
		0x008A0000,
		0x00480003,
		0x0048000B,
		0x00480013,
		0x0048001B,
		0x00480023,
		0x008A0000,
		0x00480033,
		0x0048002B,
		0x008A0017,
		0x008A0018
	},
	{
		0x00850000,
		0x00480004,
		0x0048000C,
		0x00480014,
		0x0048001C,
		0x00480024,
		0x00850000,
		0x00480034,
		0x0048002C,
		0x00850017,
		0x00850018
	},
	{
		0x00110000,
		0x00480005,
		0x0048000D,
		0x00480015,
		0x0048001D,
		0x00480025,
		0x00110000,
		0x00480035,
		0x0048002D,
		0x00110017,
		0x00110018
	},
	{
		0x000D0000,
		0x00480006,
		0x0048000E,
		0x00480016,
		0x0048001E,
		0x00480026,
		0x000D0000,
		0x00480036,
		0x0048002E,
		0x000D0017,
		0x000D0018
	},
	{
		0x00810000,
		0x00480007,
		0x0048000F,
		0x00480017,
		0x0048001F,
		0x00480027,
		0x00810000,
		0x00480037,
		0x0048002F,
		0x00810017,
		0x00810018
	}
};

s32 lbl_1_data_2B0[2] = {
	0x00480040,
	0x00480041
};

s32 lbl_1_data_2B8[3] = {
	0x00480043,
	0x00480044,
	0x00480045
};

s32 lbl_1_data_2C4[4] = {
	0x00610022,
	0x00610021,
	0x0061002F,
	0x0061002F
};

float lbl_1_data_2D4[4][4] = {
	-350, 0, 350, 135,
	350, 0, 350, 225,
	350, 0, -350, 315,
	-350, 0, -350, 45
};

s32 lbl_1_data_314[3] = {
	0x0048003D,
	0x0048003C,
	0x0048003B
};

s16 lbl_1_data_320[3] = { 10, 5, 2 };
s16 lbl_1_data_326[3] = { 1, 2, 3 };
Vec lbl_1_data_32C[3] = {
	{ 0.5f, 0.5f, 0.5f },
	{ 0.7f, 0.7f, 0.7f },
	{ 0.9f, 0.9f, 0.9f }
};

float lbl_1_data_350[3][2] = {
	0.5f, 4.0f,
	0.5f, 4.0f,
	2.0f, 6.0f
};

s32 lbl_1_data_368[1] = { 0x0048003E };

float lbl_1_data_36C[3] = { 0.7f, 85.0f, 22.0f };
float lbl_1_data_378[3] = { 0.8f, 70.0f, 27.0f };
float lbl_1_data_384[3] = { 0.9f, 55.0f, 32.0f };
float lbl_1_data_390[3] = { 1.0f, 40.0f, 37.0f };

HsfanimStruct00 lbl_1_data_39C = {
	20,
	{ 0, 0 },
	1,
	30,
	0,
	{ 0, -0.05f, 0 },
	1.0f,
	0.99f,
	20.0f,
	0.98f,
	4,
	{
		{ 128, 128, 128, 255 },
		{ 255, 0, 255, 255 },
		{ 0, 255, 255, 255 },
		{ 255, 255, 255, 255 }
	},
	{
		{ 128, 128, 128, 0 },
		{ 255, 0, 255, 0 },
		{ 0, 255, 255, 0 },
		{ 255, 255, 255, 0 }
	}
};

HsfanimStruct00 lbl_1_data_3EC = {
	30,
	{ 0, 0 },
	1,
	0,
	360,
	{ 0, -0.05f, 0 },
	10.0f,
	0.98f,
	20.0f,
	1.05f,
	4,
	{
		{ 128, 128, 128, 255 },
		{ 255, 0, 255, 255 },
		{ 0, 255, 255, 255 },
		{ 255, 255, 255, 255 }
	},
	{
		{ 128, 128, 128, 0 },
		{ 255, 0, 255, 0 },
		{ 0, 255, 255, 0 },
		{ 255, 255, 255, 0 }
	}
};

HsfanimStruct00 lbl_1_data_43C = {
	60,
	{ 0, 0 },
	1,
	0,
	360,
	{ 0, -0.05f, 0 },
	10.0f,
	0.99f,
	30.0f,
	0.98f,
	1,
	{
		{ 255, 255, 255, 255 },
		{ 255, 255, 255, 255 },
		{ 255, 255, 255, 255 },
		{ 255, 255, 255, 255 }
	},
	{
		{ 255, 255, 255, 0 },
		{ 255, 255, 255, 0 },
		{ 255, 255, 255, 0 },
		{ 255, 255, 255, 0 }
	},
};

HsfanimStruct00 lbl_1_data_48C = {
	30,
	{ 0, 0 },
	1,
	10,
	360,
	{ 0, 0.1f, 0 },
	1.0f,
	1.0f,
	30.0f,
	1.05f,
	1,
	{
		{ 255, 255, 255, 255 },
		{ 255, 255, 255, 255 },
		{ 255, 255, 255, 255 },
		{ 255, 255, 255, 255 }
	},
	{
		{ 255, 255, 255, 0 },
		{ 255, 255, 255, 0 },
		{ 255, 255, 255, 0 },
		{ 255, 255, 255, 0 }
	},
};

#include "src/REL/executor.c"

void fn_1_2454(omObjData *object)
{
	HuSysVWaitSet(1);
	if(HuPadBtn[0] & PAD_BUTTON_X) {
		lbl_1_bss_1A4 = -1;
	}
	print8(24, 32, 1.5f, "COUNT:%d MODE:%d MES:%d", lbl_1_bss_1A8, lbl_1_bss_4C->work[0], lbl_1_bss_19E);
	print8(24, 48, 1.5f, "%f %f %f", lbl_1_bss_0, lbl_1_bss_8, lbl_1_bss_4);
	print8(24, 64, 1.5f, "%x %x", HuMemHeapSizeGet(HEAP_SYSTEM)-HuMemUsedMallocSizeGet(HEAP_SYSTEM), HuMemHeapSizeGet(HEAP_DATA)-HuMemUsedMallocSizeGet(HEAP_DATA));
	lbl_1_bss_4 -= HuPadSubStkX[0]/59.0f;
	lbl_1_bss_8 -= 4.0f*(HuPadSubStkY[0]/59.0f);
	lbl_1_bss_0 -= (HuPadTrigL[0]/150.0f)*4.0f;
	lbl_1_bss_0 += (HuPadTrigR[0]/150.0f)*4.0f;
}

typedef struct work_53E8 {
	float *unk0;
	Vec unk4;
	Vec unk10;
	Vec unk1C;
	Vec unk28;
	Vec unk34;
	Vec unk40;
	Vec unk4C;
	float unk58;
	float unk5C;
	float unk60;
	Vec unk64;
	Vec unk70;
	Vec unk7C;
	float unk88;
	float unk8C;
	s32 unk90;
	s32 unk94;
	s32 unk98;
	s32 unk9C;
	s32 unkA0;
	s32 unkA4;
	s32 unkA8;
	s32 unkAC;
	s32 unkB0;
	s32 unkB4;
	s32 unkB8;
	s32 unkBC;
	s32 unkC0;
	s32 unkC4[3];
	s32 unkD0[4];
	s16 unkE0;
	float unkE4;
} Work53E8;


void fn_1_273C(Work53E8 *arg0)
{
	float temp_f31 = arg0->unk4.x;
	float temp_f30 = arg0->unk4.z;
	float temp_f28 = sqrtf((temp_f31*temp_f31)+(temp_f30*temp_f30));
	if(600.0f-arg0->unk60 < temp_f28) {
		temp_f31 /= temp_f28;
		temp_f30 /= temp_f28;
		arg0->unk4.x = temp_f31*(600.0f-arg0->unk60);
		arg0->unk4.z = temp_f30*(600.0f-arg0->unk60);
	}
}

void fn_1_2904(Work53E8 *arg0, s32 arg1)
{
	s32 i;
	for(i=0; i<4; i++) {
		Work53E8 *temp_r31 = lbl_1_bss_48[i]->data;
		if(arg0->unkB0 != temp_r31->unkB0) {
			float temp_f31 = arg0->unk4.x-temp_r31->unk4.x;
			float temp_f30 = arg0->unk4.z-temp_r31->unk4.z;
			float temp_f28 = sqrtf((temp_f31*temp_f31)+(temp_f30*temp_f30));
			if(temp_f28 < arg0->unk60+temp_r31->unk60) {
				if(arg1 && arg0->unk1C.z == temp_r31->unk1C.z) {
					arg0->unk1C.z += 55.0f*((0 > arg0->unk4.z) ? -1 : 1);
				}
				if(0.0f == temp_f28) {
					temp_f31 = 0.0f;
					temp_f30 = -1.0f;
				} else {
					temp_f31 /= temp_f28;
					temp_f30 /= temp_f28;
				}
				arg0->unk4.x = temp_r31->unk4.x+(temp_f31*(arg0->unk60+temp_r31->unk60));
				arg0->unk4.z = temp_r31->unk4.z+(temp_f30*(arg0->unk60+temp_r31->unk60));
			}
		}
		
	}
}

void fn_1_2BD4(Work53E8 *arg0, omObjData *arg1, s32 arg2)
{
	s32 temp_r29;
	if(!arg2) {
		arg0->unk10.x = 0;
		arg0->unk10.y = 0;
		arg0->unk10.z = 0;
		arg0->unk10.x = arg0->unkA4/4.0f;
		arg0->unk10.z = -((float)arg0->unkA8)/4.0f;
	}
	temp_r29 = 1;
	arg0->unk5C = VECMagXZ(&arg0->unk10);
	if(0.5f <= arg0->unk5C) {
		if(10.0f <= arg0->unk5C) {
			arg0->unk10.x /= arg0->unk5C;
			arg0->unk10.z /= arg0->unk5C;
			arg0->unk5C = 10.0f;
			arg0->unk10.x = 10.0f*arg0->unk10.x;
			arg0->unk10.z = 10.0f*arg0->unk10.z;
		}
		arg0->unk58 = fn_1_1E20(arg0->unk58, atan2d(arg0->unk10.x, arg0->unk10.z), 0.4f);
		if(8.0f <= arg0->unk5C) {
			temp_r29 = 3;
		} else {
			temp_r29 = 2;
		}
	}
	VECAdd(&arg0->unk4, &arg0->unk10, &arg0->unk4);
	fn_1_273C(arg0);
	fn_1_2904(arg0, arg2);
	if(arg2) {
		temp_r29 += 6;
		if(temp_r29 > 6) {
			temp_r29 = 7;
		}
	}
	if(temp_r29 >= 0 && arg0->unk9C != temp_r29) {
		arg0->unk9C = temp_r29;
		Hu3DMotionShiftSet(arg1->model[0], arg1->motion[arg0->unk9C], 0, 8, 0x40000001);
	}
}

void fn_1_3404(Work53E8 *arg0)
{
	float temp_f31;
	float temp_f30;
	float temp_f27;
	float temp_f26;
	float temp_f25;
	
	if(NULL == arg0->unk0) {
		return;
	}
	temp_f31 = 0;
	temp_f30 = 0;
	if(arg0->unk94 == 0) {
		temp_f31 = arg0->unk7C.x-arg0->unk4.x;
		temp_f30 = arg0->unk7C.z-arg0->unk4.z;
		temp_f27 = sqrtf((temp_f31*temp_f31)+(temp_f30*temp_f30));
		if(10.0f <= temp_f27) {
			temp_f31 /= temp_f27;
			temp_f30 /= temp_f27;
		} else {
			temp_f31 = 0;
			temp_f30 = 0;
		}
		if(170.0f < temp_f27 && 224.0f > temp_f27) {
			if(200.0f > arg0->unk7C.y) {
				arg0->unkAC |= PAD_BUTTON_B;
			} else {
				arg0->unkAC |= PAD_BUTTON_A;
			}
			arg0->unk94 = 1;
			arg0->unk8C = arg0->unk0[1]+((frandf()*arg0->unk0[1])/2);
			temp_f25 = 1.0f-(lbl_1_bss_1A4/3600.0f);
			if(0.25f < temp_f25) {
				arg0->unk8C *= arg0->unk90/(arg0->unk0[2]*temp_f25);
			}
			if(arg0->unk8C < frandmod(100)) {
				arg0->unk94 = 0;
			}
		}
	} else {
		if(arg0->unk94 == 1) {
			arg0->unk94 = 2;
			temp_f26 = 360.0f*frandf();
			temp_f27 = (600.0f-arg0->unk60)*frandf();
			arg0->unk70.x = temp_f27*sind(temp_f26);
			arg0->unk70.y = 0;
			arg0->unk70.z = temp_f27*cosd(temp_f26);
		}
		temp_f31 = arg0->unk70.x-arg0->unk4.x;
		temp_f30 = arg0->unk70.z-arg0->unk4.z;
		temp_f27 = sqrtf((temp_f31*temp_f31)+(temp_f30*temp_f30));
		if(10.0f <= temp_f27) {
			temp_f31 /= temp_f27;
			temp_f30 /= temp_f27;
		} else {
			temp_f31 = 0;
			temp_f30 = 0;
			arg0->unk94 = 1;
		}
		arg0->unk8C--;
		if(0.0f > arg0->unk8C) {
			arg0->unk94 = 0;
		}
	}
	arg0->unkA4 = (72.0f*temp_f31)*arg0->unk0[0];
	arg0->unkA8 = (72.0f*-temp_f30)*arg0->unk0[0];
	if(ABS(arg0->unkA4) > 72) {
		arg0->unkA4 = ((arg0->unkA4 < 0) ? -1 : 1)*72;
	}
	if(ABS(arg0->unkA8) > 72) {
		arg0->unkA8 = ((arg0->unkA8 < 0) ? -1 : 1)*72;
	}
}

void fn_1_3B04(Work53E8 *arg0, omObjData *arg1)
{
	arg0->unk64.z++;
	if(10.0f >= arg0->unk64.z) {
		float temp_f31 = (0.3f*sind(180.0f*(arg0->unk64.z/10.0f)))+1.5f;
		Hu3DModelScaleSet(arg1->model[2], temp_f31, temp_f31, temp_f31);
	}
}

void fn_1_40A8(omObjData *object);

void fn_1_3C00(omObjData *object)
{
	Work53E8 *work = object->data;
	Mtx hookMtx;
	Vec netOfs;
	if(work->unk98 == 2004 && lbl_1_bss_4C->work[0] >= 1005) {
		work->unk98 = 2007;
		work->unk64.x = 20;
		Hu3DMotionShiftSet(object->model[0], object->motion[1], 0, 20, 0x40000001);
		object->func = fn_1_40A8;
		return;
	}
	work->unk88 = 10000;
	if(GWPlayerCfg[work->unkB0].iscom) {
		work->unkA4 = 0;
		work->unkA8 = 0;
		work->unkAC = 0;
		fn_1_3404(work);
	} else {
		work->unkA4 = HuPadStkX[work->unkB8];
		work->unkA8 = HuPadStkY[work->unkB8];
		work->unkAC = HuPadBtnDown[work->unkB8];
	}
	switch(work->unk98) {
		case 2004:
			fn_1_2BD4(work, object, 0);
			if(work->unkAC & PAD_BUTTON_A) {
				work->unk98 = 2005;
				work->unk64.x = 10;
				work->unkE4 = 0;
				Hu3DModelAttrReset(object->model[0], 0x40000001);
				Hu3DMotionShiftSet(object->model[0], object->motion[4], 0, 8, 0);
				Hu3DMotionSet(object->model[1], object->motion[11]);
				HuAudFXEmiterPlay(1814, &work->unk4);
			}
			if(work->unkAC & PAD_BUTTON_B) {
				work->unk98 = 2005;
				work->unk64.x = 10;
				work->unkE4 = 0;
				Hu3DModelAttrReset(object->model[0], 0x40000001);
				Hu3DMotionShiftSet(object->model[0], object->motion[5], 0, 8, 0);
				Hu3DMotionSet(object->model[1], object->motion[11]);
				HuAudFXEmiterPlay(1814, &work->unk4);
			}
			break;
			
		case 2005:
			work->unk64.x--;
			if(0.0f > work->unk64.x && 20.0f < Hu3DMotionTimeGet(object->model[0])) {
				work->unk98++;
			}
			work->unkE4++;
			if(240.0f < work->unkE4) {
				work->unk98 = 2006;
			}
			break;
			
		case 2006:
			work->unkE4++;
			if(240.0f < work->unkE4 || Hu3DMotionEndCheck(object->model[0])) {
				work->unk98 = 2004;
				work->unk9C = 1;
				Hu3DMotionShiftSet(object->model[0], object->motion[1], 0, 8, 0x40000001);
			}
			break;
			
		default:
			OSReport("*** player mode error(%d)!!\n", work->unk98);
			break;
	}
	omSetTra(object, work->unk4.x, work->unk4.y, work->unk4.z);
	omSetRot(object, 0, work->unk58, 0);
	netOfs.x = 0;
	netOfs.y = 0;
	netOfs.z = 170;
	Hu3DModelObjMtxGet(object->model[0], CharModelHookNameGet(work->unkB4, 2, 0), hookMtx);
	MTXMultVec(hookMtx, &netOfs, &work->unk28);
	
}

static inline void fn_1_40A8InlineFunc(Vec *arg0, float arg1, float arg2, float arg3) {
    arg0->x = arg1;
    arg0->y = arg2;
    arg0->z = arg3;
}

void fn_1_892C(s16 arg0, s16 arg1, Vec *arg2);

void fn_1_40A8(omObjData *object)
{
	float angle;
	Mtx hookMtx;
	Vec pos3D;
	Vec pos2D;
	Work53E8 *work = object->data;
	s32 i;
	
	switch(work->unk98) {
		case 2000:
			if(lbl_1_bss_4C->work[0] == 1002 && 90.0f < lbl_1_bss_28) {
				work->unk98++;
				work->unk64.x = 10.0f;
				Hu3DModelAttrReset(object->model[0], 0x40000003);
				Hu3DMotionShiftSet(object->model[0], object->motion[4], 0, 10, 0);
				Hu3DMotionSet(object->model[1], object->motion[11]);
				HuAudFXEmiterPlay(1814, &work->unk4);
			}
			break;
			
		case 2001:
			work->unk64.x--;
			if(0.0f > work->unk64.x && Hu3DMotionEndCheck(object->model[0])) {
				work->unk98++;
				work->unk64.x = 10.0f;
				Hu3DMotionShiftSet(object->model[0], object->motion[5], 0, 10, 0);
				Hu3DMotionSet(object->model[1], object->motion[11]);
				HuAudFXEmiterPlay(1814, &work->unk4);
			}
			break;
			
		case 2002:
			work->unk64.x--;
			if(0.0f > work->unk64.x && Hu3DMotionEndCheck(object->model[0])) {
				work->unk98++;
				Hu3DMotionShiftSet(object->model[0], object->motion[1], 0, 10, 0x40000001);
			}
			break;
			
		case 2003:
			if(lbl_1_bss_4C->work[0] >= 1004) {
				work->unk98++;
				object->func = fn_1_3C00;
			}
			break;
			
		case 2007:
			work->unk64.x--;
			if(0.0f > work->unk64.x && lbl_1_bss_4C->work[0] == 1006) {
				work->unk98++;
				work->unk64.x = 40;
				Hu3DModelObjMtxGet(object->model[0], CharModelHookNameGet(work->unkB4, 2, 0), hookMtx);
				Hu3DMtxTransGet(hookMtx, &work->unk28);
				Hu3DMtxRotGet(hookMtx, &work->unk34);
				Hu3DMtxScaleGet(hookMtx, &work->unk40);
				Hu3DModelPosSet(object->model[1], work->unk28.x, work->unk28.y, work->unk28.z);
				Hu3DModelRotSet(object->model[1], work->unk34.x, work->unk34.y, work->unk34.z);
				Hu3DModelScaleSet(object->model[1], work->unk40.x, work->unk40.y, work->unk40.z);
				Hu3DModelHookObjReset(object->model[0], CharModelHookNameGet(work->unkB4, 2, 0));
			}
			break;
			
		case 2008:
			work->unk28.y += 4;
			work->unk34.x += 24.0f;
			work->unk40.x *= 0.95f;
			work->unk40.y *= 0.95f;
			work->unk40.z *= 0.95f;
			Hu3DModelPosSet(object->model[1], work->unk28.x, work->unk28.y, work->unk28.z);
			Hu3DModelRotSet(object->model[1], work->unk34.x, work->unk34.y, work->unk34.z);
			Hu3DModelScaleSet(object->model[1], work->unk40.x, work->unk40.y, work->unk40.z);
			work->unk64.x--;
			if(0.0f > work->unk64.x) {
				float temp_f24;
				work->unk98++;
				work->unk64.x = 0;
				temp_f24 = (work->unkB0*160.0f)-240.0f;
				work->unk1C.x = temp_f24;
				work->unk1C.y = 0;
				work->unk1C.z = 0;
				Hu3DModelAttrSet(object->model[1], 1);
				work->unkE0 = Hu3DParManLink(lbl_1_bss_2C, &lbl_1_data_48C);
				Hu3DParManPosSet(work->unkE0, work->unk28.x, work->unk28.y, work->unk28.z);
				Hu3DParManAttrReset(work->unkE0, 1);
				Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(work->unkE0), 1);
				Hu3DModelLayerSet(Hu3DParManModelIDGet(work->unkE0), 4);
				HuAudFXPlay(1815);
				
			}
			break;
			
		case 2009:
			work->unk64.x++;
			if(10.0f == work->unk64.x) {
				Hu3DParManAttrSet(work->unkE0, 1);
			}
			work->unk10.x = 0;
			work->unk10.y = 0;
			work->unk10.z = 0;
			work->unk10.x = work->unk1C.x-work->unk4.x;
			work->unk10.z = work->unk1C.z-work->unk4.z;
			if(10.0f < work->unk64.x && 0.0f == work->unk10.x && 0.0f == work->unk10.z && 0.0f == work->unk1C.z) {
				work->unk98++;
				work->unkA0 = 1;
			} else {
				fn_1_2BD4(work, object, 1);
				if(0.0f != work->unk1C.z) {
					work->unk1C.z -= ((0.0f > work->unk1C.z) ? -1 : 1)*5.0f;
				}
			}
			break;
			
		case 2010:
			work->unk58 = fn_1_1E20(work->unk58, 0.0f, 0.5f);
			angle = fmod(-work->unk58, 360.0f);
			if(-180.0f > angle) {
				angle += 360.0f;
			}
			if(work->unkA0) {
				if(8.0f > ABS(angle)) {
					work->unkA0 = 0;
					Hu3DModelPosSet(object->model[2], 0, 0, -10);
					Hu3DMotionShiftSet(object->model[0], object->motion[6], 0, 4, 0x40000001);
				}
			}
			if(lbl_1_bss_4C->work[0] == 1007) {
				work->unk98++;
				work->unk64.x = 10.0f;
				Hu3DModelAttrReset(object->model[0], 0x40000001);
				Hu3DMotionShiftSet(object->model[0], object->motion[8], 0, 8, 0);
				work->unk64.y = -90;
				fn_1_40A8InlineFunc(&pos3D, work->unk4.x, 250, work->unk4.z);
				Hu3D3Dto2D(&pos3D, 1, &pos2D);
				espTPLvlSet(work->unkD0[0], 0.5f);
				espPosSet(work->unkD0[0], pos2D.x, pos2D.y);
				espPosSet(work->unkD0[1], pos2D.x, pos2D.y);
				espPosSet(work->unkD0[2], pos2D.x-14, 10+pos2D.y);
				espPosSet(work->unkD0[3], (pos2D.x-14)+28, 10+pos2D.y);
				for(i=0; i<4; i++) {
					espScaleSet(work->unkD0[i], 0.1f, 0.1f);
					espBankSet(work->unkD0[i], 0);
					espDispOn(work->unkD0[i]);
				}
				work->unkE0 = Hu3DParManLink(lbl_1_bss_34, &lbl_1_data_43C);
				Hu3DParManPosSet(work->unkE0, pos3D.x, pos3D.y, pos3D.z);
			}
			break;
			
		case 2011:
			work->unk64.y += 18.0f;
			if(180.0f >= work->unk64.y) {
				for(i=0; i<4; i++) {
					espScaleSet(work->unkD0[i], sind(work->unk64.y)+1, sind(work->unk64.y)+1);
				}
			}
			work->unk64.x--;
			if(0.0f > work->unk64.x) {
				float motTime = Hu3DMotionTimeGet(object->model[0]);
				if(18.0f == motTime) {
					Hu3DParManAttrSet(work->unkE0, 1);
					Hu3DModelPosSet(object->model[2], 0, 0, 0);
					Hu3DModelHookObjReset(object->model[0], CharModelHookNameGet(work->unkB4, 2, 4));
					Hu3DModelHookSet(object->model[0], CharModelHookNameGet(work->unkB4, 2, 0), object->model[2]);
				}
				if(40.0f == motTime) {
					work->unk64.z = 0;
					Hu3DModelHookObjReset(object->model[0], CharModelHookNameGet(work->unkB4, 2, 0));
					fn_1_1D18(object->model[0], CharModelHookNameGet(work->unkB4, 2, 0), &work->unk4C);
					work->unk4C.z += 20.0f;
					Hu3DModelPosSet(object->model[2], work->unk4C.x, work->unk4C.y, work->unk4C.z);
				}
				if(40.0f <= motTime) {
					work->unk64.z++;
					if(12.0f >= work->unk64.z) {
						float scale = sind(150.0f*(work->unk64.z/12.0f))+1.0;
						Hu3DModelScaleSet(object->model[2], scale, scale, scale);
					}
				}
				if(Hu3DMotionEndCheck(object->model[0])) {
					work->unk98++;
					Hu3DModelAttrSet(object->model[0], 0x40000001);
					Hu3DMotionSet(object->model[0], object->motion[0]);
					Hu3DMotionSet(object->model[2], object->motion[14]);
					for(i=0; i<4; i++) {
						espScaleSet(work->unkD0[i], 1.0f, 1.0f);
					}
				}
			}
			break;
			
		case 2012:
			if(Hu3DMotionEndCheck(object->model[2])) {
				work->unk98++;
				work->unk64.x = 0;
			}
			break;
			
		case 2013:
			work->unk64.x--;
			if(0.0f > work->unk64.x) {
				s32 choType;
				work->unk64.x = (20.0f*frandf())+20.0f;
				choType = -1;
				for(i=0; i<3; i++) {
					if(choType < 0 && work->unkC4[i] > 0) {
						choType = i;
					}
				}
				if(choType < 0) {
					work->unk98++;
					work->unk64.x = 0;
				} else {
					lbl_1_bss_20++;
					work->unkBC += lbl_1_data_326[choType];
					if(work->unkBC > 99) {
						work->unkBC = 99;
					}
					work->unkC4[choType]--;
					fn_1_892C(work->unkB0, choType, &work->unk4C);
					HuAudFXPlay(1816);
					espBankSet(work->unkD0[2], work->unkBC/10);
					espBankSet(work->unkD0[3], work->unkBC%10);
					work->unk64.z = 0;
				}
			}
			break;
			
		case 2014:
			work->unk64.x++;
			if(30.0f == work->unk64.x) {
				Hu3DModelAttrSet(object->model[2], 1);
				work->unkE0 = Hu3DParManLink(lbl_1_bss_2C, &lbl_1_data_48C);
				Hu3DParManPosSet(work->unkE0, work->unk4C.x, work->unk4C.y+20, work->unk4C.z);
				Hu3DParManAttrReset(work->unkE0, 1);
				Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(work->unkE0), 1);
				Hu3DModelLayerSet(Hu3DParManModelIDGet(work->unkE0), 4);
				HuAudFXPlay(1815);
			}
			if(40.0f == work->unk64.x) {
				Hu3DParManAttrSet(work->unkE0, 1);
			}
			if(60.0f < work->unk64.x && work->unkC0 >= 0) {
				work->unk98++;
				if(work->unkC0 == 1) {
					Hu3DMotionShiftSet(object->model[0], object->motion[9], 0, 20, 0);
				} else {
					Hu3DMotionShiftSet(object->model[0], object->motion[10], 0, 20, 0);
				}
			}
			break;
			
		default:
			OSReport("*** player mode error(%d)!!\n", work->unk98);
			break;

		case 2015:
			break;
	}
	omSetTra(object, work->unk4.x, work->unk4.y, work->unk4.z);
	omSetRot(object, 0, work->unk58, 0);
}

void fn_1_53E8(omObjData *object)
{
	Work53E8 *work = object->data;
	s32 i;
	
	work->unk0 = NULL;
	work->unk88 = 10000;
	work->unk8C = 0;
	work->unk90 = 0;
	work->unk94 = 0;
	work->unk7C.x = 0;
	work->unk7C.y = 0;
	work->unk7C.z = 0;
	work->unkB0 = object->work[0];
	work->unkB4 = GWPlayerCfg[work->unkB0].character;
	work->unkB8 = GWPlayerCfg[work->unkB0].pad_idx;
	work->unk98 = 2000;
	work->unkBC = 0;
	work->unkC0 = -1;
	for(i=0; i<3; i++) {
		work->unkC4[i] = 0;
	}
	work->unk9C = 1;
	work->unk60 = 50;
	work->unk4.x = lbl_1_data_2D4[work->unkB0][0];
	work->unk4.y = lbl_1_data_2D4[work->unkB0][1];
	work->unk4.z = lbl_1_data_2D4[work->unkB0][2];
	work->unk58 = lbl_1_data_2D4[work->unkB0][3];
	work->unk4C.x = 0;
	work->unk4C.y = 0;
	work->unk4C.z = 0;
	object->model[0] = CharModelCreate(lbl_1_data_0[work->unkB4], 2);
	CharModelStepTypeSet(lbl_1_data_0[work->unkB4], 0);
	for(i=0; i<16; i++) {
		object->motion[i] = CharModelMotionCreate(lbl_1_data_0[work->unkB4], lbl_1_data_B0[work->unkB4][i]);
		CharModelMotionSet(lbl_1_data_0[work->unkB4], object->motion[i]);
	}
	CharModelMotionIndexSet(work->unkB4, object->motion[2], 0x5F0002);
	CharModelMotionIndexSet(work->unkB4, object->motion[7], 0x5F0002);
	CharModelMotionIndexSet(work->unkB4, object->motion[3], 0x5F0003);
	Hu3DModelAttrSet(object->model[0], 1);
	Hu3DModelAttrSet(object->model[0], 0x40000001);
	Hu3DModelLayerSet(object->model[0], 2);
	Hu3DMotionSet(object->model[0], object->motion[1]);
	object->model[1] = Hu3DModelCreateFile(0x48003F);
	for(i=11; i<=12; i++) {
		object->motion[i] = Hu3DJointMotionFile(object->model[1], lbl_1_data_2B0[i-11]);
	}
	Hu3DModelAttrSet(object->model[1], 1);
	Hu3DModelAttrReset(object->model[1], 0x40000001);
	Hu3DModelLayerSet(object->model[1], 2);
	Hu3DModelHookSet(object->model[0], CharModelHookNameGet(work->unkB4, 2, 0), object->model[1]);
	object->model[2] = Hu3DModelCreateFile(0x480042);
	for(i=13; i<=15; i++) {
		object->motion[i] = Hu3DJointMotionFile(object->model[2], lbl_1_data_2B8[i-13]);
	}
	Hu3DModelAttrSet(object->model[2], 1);
	Hu3DModelAttrReset(object->model[2], 0x40000001);
	Hu3DModelLayerSet(object->model[2], 2);
	Hu3DModelHookSet(object->model[0], CharModelHookNameGet(work->unkB4, 2, 4), object->model[2]);
	for(i=0; i<4; i++) {
		work->unkD0[i] = espEntry(lbl_1_data_2C4[i], 0, 0);
		espDrawNoSet(work->unkD0[i], 0x40);
		espDispOff(work->unkD0[i]);
		espAttrSet(work->unkD0[i], HUSPR_ATTR_NOANIM);
		espBankSet(work->unkD0[i], 0);
		espPriSet(work->unkD0[i], 128-i);
		espPosSet(work->unkD0[i], 0, 0);
		if(i == 0) {
			espColorSet(work->unkD0[i], 0, 0, 0);
		}
	}
	omSetTra(object, work->unk4.x, work->unk4.y, work->unk4.z);
	omSetRot(object, 0, work->unk58, 0);
	for(i=0; i<3; i++) {
		Hu3DModelShadowSet(object->model[i]);
	}
	for(i=0; i<3; i++) {
		Hu3DModelAttrReset(object->model[i], 1);
	}
	if(GWPlayerCfg[work->unkB0].iscom) {
		switch(GWPlayerCfg[work->unkB0].diff) {
			case 0:
				work->unk0 = lbl_1_data_36C;
				break;
				
			case 1:
				work->unk0 = lbl_1_data_378;
				break;
				
			case 2:
				work->unk0 = lbl_1_data_384;
				break;
			
			case 3:
			default:
				work->unk0 = lbl_1_data_390;
				break;
		}
	}
	CharModelLayerSetAll2(6);
	CharModelMotionDataClose(lbl_1_data_0[work->unkB4]);
	object->func = fn_1_40A8;
}

typedef struct work_713C {
	Vec unk0;
	Vec unkC;
	Vec unk18;
	Vec unk24;
	s16 unk30;
	s32 unk34;
	s32 unk38;
} Work713C;

void fn_1_5B2C(omObjData *object)
{
	Hu3DModelAttrSet(object->model[0], 1);
	fn_1_24(object->work[0]+4096, object->model[0]);
	lbl_1_bss_18[object->work[0]]--;
	Hu3DParManKill(((Work713C *)object->data)->unk30);
	omDelObjEx(lbl_1_bss_1DC, object);
}

void fn_1_74F4(s32 arg0);

void fn_1_5C04(omObjData *object)
{
	Work713C *temp_r31;
	Work53E8 *temp_r29;
	omObjData *temp_r28;
	float *temp_r24;
	
	s32 temp_r23;
	s32 temp_r22;
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f23;
	float sp78;
	temp_r31 = object->data;
	if(lbl_1_bss_4C->work[0] < 1002) {
		return;
	}
	if(temp_r31->unk38) {
		if(lbl_1_bss_4C->work[0] >= 1006) {
			fn_1_5B2C(object);
		} else {
			temp_r31->unk24.z--;
			if(20.0f == temp_r31->unk24.z) {
				Hu3DParManAttrSet(temp_r31->unk30, 1);
			}
			if(0.0f > temp_r31->unk24.z) {
				fn_1_5B2C(object);
				fn_1_74F4(1);
			}
		}
		return;
	} else {
		if(lbl_1_bss_4C->work[0] >= 1006) {
			temp_r31->unk18.y += 0.1f;
			temp_r31->unk18.x = fn_1_1E20(temp_r31->unk18.x, (180.0f > temp_r31->unk18.x) ? 90.0f : 270.0f, 0.05f);
			temp_r31->unk0.x += temp_r31->unk18.y*sind(temp_r31->unk18.x);
			temp_r31->unk0.z += temp_r31->unk18.y*cosd(temp_r31->unk18.x);
			if(1200.0f < ABS(temp_r31->unk0.x)) {
				fn_1_5B2C(object);
				return;
			}
		} else {
			if(temp_r31->unk34) {
				temp_f31 = -temp_r31->unk0.x;
				temp_f30 = -temp_r31->unk0.z;
				temp_r31->unk18.x = fn_1_1E20(temp_r31->unk18.x, atan2d(temp_f31, temp_f30), 0.05f);
				temp_r31->unk0.x += temp_r31->unk18.y*sind(temp_r31->unk18.x);
				temp_r31->unk0.z += temp_r31->unk18.y*cosd(temp_r31->unk18.x);
				temp_f31 = -temp_r31->unk0.x;
				temp_f30 = -temp_r31->unk0.z;
				temp_f23 = sqrtf((temp_f31*temp_f31)+(temp_f30*temp_f30));
				if(600.0f >= temp_f23) {
					temp_r31->unk34 = 0;
				}
			} else {
				temp_r31->unk18.x += ((frandf()*2.0f)-1.0f)*3.0f;
				temp_r31->unk18.y += ((frandf()*2.0f)-1.0f)*0.1f;
				temp_r24 = &lbl_1_data_350[object->work[0]][0];
				if(temp_r24[0] > temp_r31->unk18.y) {
					temp_r31->unk18.y = temp_r24[0];
				}
				if(temp_r24[1] < temp_r31->unk18.y) {
					temp_r31->unk18.y = temp_r24[1];
				}
				temp_r31->unk0.x += temp_r31->unk18.y*sind(temp_r31->unk18.x);
				temp_r31->unk0.z += temp_r31->unk18.y*cosd(temp_r31->unk18.x);
				temp_f31 = -temp_r31->unk0.x;
				temp_f30 = -temp_r31->unk0.z;
				temp_f23 = sqrtf((temp_f31*temp_f31)+(temp_f30*temp_f30));
				if(600.0f < temp_f23) {
					temp_r31->unk18.x = fn_1_1E20(temp_r31->unk18.x, atan2d(temp_f31, temp_f30), 0.05f);
				}
			}
		}
		temp_f23 = ABS(temp_r31->unk24.y-temp_r31->unk0.y);
		if(2.0f > temp_f23) {
			temp_r31->unk24.x--;
			if(0.0f > temp_r31->unk24.x) {
				temp_r31->unk24.x = 60.0f;
				if(frandmod(100) > 50) {
					temp_r31->unk24.y = (frandf()*220.0f)+80.0f;
				}
			}
		} else {
			temp_r31->unk0.y += (temp_r31->unk24.y > temp_r31->unk0.y) ? 1.0f : -1.0f;
		}
		temp_r31->unk18.z += (frandf()*4.0f)+4.0f;
		omSetTra(object, temp_r31->unk0.x, (sind(temp_r31->unk18.z)*10.0)+temp_r31->unk0.y, temp_r31->unk0.z);
		omSetRot(object, 0, temp_r31->unk18.x+180.0f, 0);
		if(temp_r31->unk30 >= 0) {
			temp_f31 = sind(temp_r31->unk18.x+180.0f)*30;
			temp_f30 = cosd(temp_r31->unk18.x+180.0f)*30;
			Hu3DParManPosSet(temp_r31->unk30, temp_r31->unk0.x+temp_f31, temp_r31->unk0.y, temp_r31->unk0.z+temp_f30);
			Hu3DParManVecSet(temp_r31->unk30, temp_r31->unk18.y*sind(temp_r31->unk18.x+180.0f), 0, temp_r31->unk18.y*cosd(temp_r31->unk18.x+180.0f));
		}
		temp_r22 = -1;
		for(temp_r23=0; temp_r23<4; temp_r23++) {
			temp_r29 = lbl_1_bss_48[temp_r23]->data;
			if(600.0f > VECMagXZ(&temp_r31->unk0)) {
				temp_f31 = temp_r29->unk4.x-temp_r31->unk0.x;
				temp_f30 = temp_r29->unk4.z-temp_r31->unk0.z;
				temp_f23 = sqrtf((temp_f31*temp_f31)+(temp_f30*temp_f30))-170;
				if(0.0f < temp_f23 && temp_r29->unk88 > temp_f23) {
					temp_r29->unk88 = temp_f23;
					temp_r29->unk7C = temp_r31->unk0;
				}
			}
			if(temp_r29->unk98 == 2005) {
				temp_f31 = temp_r29->unk28.x-temp_r31->unk0.x;
				temp_f29 = temp_r29->unk28.y-temp_r31->unk0.y;
				temp_f30 = temp_r29->unk28.z-temp_r31->unk0.z;
				temp_f23 = VECMagPoint(temp_f31, temp_f29, temp_f30);
				if(60.0f > temp_f23) {
					if(temp_r22 < 0) {
						temp_r22 = temp_r23;
					} else if(frandmod(100) > 50) {
						temp_r22 = temp_r23;
					}
				}
			}
		}
		if(temp_r22 >= 0) {
			temp_r31->unk38 = 1;
			temp_r31->unk24.z = 30;
			Hu3DParManKill(temp_r31->unk30);
			temp_r31->unk30 = Hu3DParManLink(lbl_1_bss_34, &lbl_1_data_3EC);
			Hu3DParManPosSet(temp_r31->unk30, temp_r31->unk0.x, temp_r31->unk0.y, temp_r31->unk0.z);
			Hu3DParManColorSet(temp_r31->unk30, object->work[0]);
			Hu3DModelAttrSet(object->model[0], 1);
			temp_r28 = lbl_1_bss_48[temp_r22];
			temp_r29 = temp_r28->data;
			temp_r29->unkC4[object->work[0]]++;
			temp_r29->unk90 += lbl_1_data_326[object->work[0]];
			sp78 = Hu3DMotionTimeGet(temp_r28->model[1]);
			Hu3DMotionSet(temp_r28->model[1], temp_r28->motion[12]);
			Hu3DMotionTimeSet(temp_r28->model[1], sp78);
			Hu3DMotionSet(temp_r28->model[2], temp_r28->motion[13]);
			omVibrate(temp_r29->unkB0, 12, 6, 6);
			HuAudFXEmiterPlay(1813, &temp_r31->unk0);
		}
	}
}

void fn_1_713C(omObjData *object)
{
	Work713C *work = object->data;
	s16 mdlId = fn_1_AC(object->work[0]+4096);
	Vec *scale;
	if(mdlId < 0) {
		object->model[0] = Hu3DModelLink(lbl_1_bss_12[object->work[0]]);
	} else {
		object->model[0] = mdlId;
	}
	Hu3DModelAttrSet(object->model[0], 1);
	Hu3DModelAttrSet(object->model[0], 0x40000003);
	Hu3DModelLayerSet(object->model[0], 3);
	Hu3DModelShadowSet(object->model[0]);
	scale = &lbl_1_data_32C[object->work[0]];
	omSetTra(object, work->unk0.x, work->unk0.y, work->unk0.z);
	omSetRot(object, 0, work->unk18.x+180, 0);
	omSetSca(object, scale->x, scale->y, scale->z);
	work->unk30 = Hu3DParManLink(lbl_1_bss_34, &lbl_1_data_39C);
	if(work->unk30 >= 0) {
		float x = sind(work->unk18.x+180)*30.0;
		float y = cosd(work->unk18.x+180)*30.0;
		Hu3DParManPosSet(work->unk30, work->unk0.x+x, work->unk0.y, work->unk0.z+y);
		Hu3DParManVecSet(work->unk30, work->unk18.y*sind(work->unk18.x+180.0f), 0, work->unk18.y*cosd(work->unk18.x+180.0f));
		Hu3DParManAttrSet(work->unk30, 0x804);
		Hu3DParManAttrReset(work->unk30, 1);
		Hu3DParManColorSet(work->unk30, object->work[0]);
		Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(work->unk30), 1);
		Hu3DModelLayerSet(Hu3DParManModelIDGet(work->unk30), 4);
		
	}
	Hu3DModelAttrReset(object->model[0], 0x40000002);
	Hu3DModelAttrReset(object->model[0], 1);
	object->func = fn_1_5C04;
}

void fn_1_74F4(s32 arg0)
{
	s16 no = -1;
	s16 i;
	omObjData *object;
	Work713C *work;
	float radius;
	for(i=0; i<3; i++) {
		if(lbl_1_data_320[i] > lbl_1_bss_18[i]) {
			no = i;
		}
	}
	if(no < 0) {
		return;
	}
	lbl_1_bss_18[no]++;
	object = omAddObjEx(lbl_1_bss_1DC, 101, 1, 0, 1, fn_1_713C);
	object->work[0] = no;
	object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work713C), MEMORY_DEFAULT_NUM);
	work = object->data;
	work->unk34 = arg0;
	work->unk18.z = 0;
	work->unk38 = 0;
	work->unk18.y = 2;
	work->unk24.x = (frandf()*180.0f)+180.0f;
	if(arg0) {
		work->unk18.y = 3;
		work->unk18.x = 180.0f-(frandf()*120.0f);
		if(frandmod(100) > 50) {
			work->unk18.x = 360.0f-work->unk18.x;
		}
		radius = 1200;
		work->unk0.x = radius*sind(work->unk18.x+180.0f);
		work->unk0.y = (frandf()*220.0f)+80.0f;
		work->unk0.z = radius*cosd(work->unk18.x+180.0f);
	} else {
		if(lbl_1_bss_C) {
			lbl_1_bss_C = 0;
			work->unk18.x = 45.0f+(frandf()*90.0f);
			if(frandmod(100) > 50) {
				work->unk18.x += 180.0f;
			}
			work->unk0.x = 0;
			work->unk0.y = 80;
			work->unk0.z = 0;
		} else {
			repeat:
			radius = 300;
			radius += radius*frandf();
			work->unk18.x = 360.0f*frandf();
			work->unk0.x = radius*sind(work->unk18.x);
			work->unk0.y = (frandf()*220.0f)+80.0f;
			work->unk0.z = radius*cosd(work->unk18.x);
			if(0.0f < work->unk0.y) {
				if(150.0f > ABS(work->unk0.x)) {
					goto repeat;
				}
			}
		}
	}
	work->unk24.y = work->unk0.y;
}

void fn_1_7958(omObjData *object)
{
	Hu3DModelAttrSet(object->model[0], 1);
	fn_1_24(object->work[0]+4096, object->model[0]);
	Hu3DParManKill(((Work713C *)object->data)->unk30);
	omDelObjEx(lbl_1_bss_1DC, object);
	lbl_1_bss_1E--;
}

void fn_1_7A2C(omObjData *object)
{
	Work713C *work = object->data;
	float x = work->unkC.x-work->unk0.x;
	float y = work->unkC.y-work->unk0.y;
	float len = sqrtf((x*x)+(y*y));
	if(10.0f > len) {
		work->unk18.y--;
		if(0.0f > work->unk18.y) {
			work->unk18.y = 0;
		}
		work->unk18.x = fn_1_1E20(work->unk18.x, 0.0f, 0.05f);
	} else {
		work->unk18.y += 0.1f;
		if(3.0f < work->unk18.y) {
			work->unk18.y = 3.0f;
		}
		work->unk18.x = fn_1_1E20(work->unk18.x, atan2d(-x, y), 0.05f);
	}
	work->unk0.x -= work->unk18.y*sind(work->unk18.x);
	work->unk0.y += work->unk18.y*cosd(work->unk18.x);
	omSetTra(object, work->unk0.x, work->unk0.y, work->unk0.z);
	omSetRot(object, 90, 0, work->unk18.x);
	if(work->unk30 >= 0) {
		Hu3DParManPosSet(work->unk30, work->unk0.x, work->unk0.y, work->unk0.z);
		Hu3DParManVecSet(work->unk30, -2*sind(work->unk18.x+180.0f), 2*cosd(work->unk18.x+180.0f), 0);
	}
}

void fn_1_803C(omObjData *object)
{
	Work713C *work = object->data;
	float x;
	float y;
	work->unk18.y -= 0.1f;
	if(2.0f > work->unk18.y) {
		work->unk18.y = 2.0f;
		if(work->unkC.y > work->unk0.y) {
			x = work->unkC.x-work->unk0.x;
			y = work->unkC.y-work->unk0.y;
			work->unk18.x = fn_1_1E20(work->unk18.x, atan2d(-x, y), 0.05f);
		}
	}
	
	work->unk0.x -= work->unk18.y*sind(work->unk18.x);
	work->unk0.y += work->unk18.y*cosd(work->unk18.x);
	omSetTra(object, work->unk0.x, work->unk0.y, work->unk0.z);
	omSetRot(object, 90, 0, work->unk18.x);
	if(work->unk30 >= 0) {
		x = sind(work->unk18.x+180)*-20.0;
		y = cosd(work->unk18.x+180)*20.0;
		Hu3DParManPosSet(work->unk30, work->unk0.x+x, work->unk0.y+y, work->unk0.z);
		Hu3DParManVecSet(work->unk30, -work->unk18.y*sind(work->unk18.x+180.0f), work->unk18.y*cosd(work->unk18.x+180.0f), 0);
	}
	if(450.0f < work->unk0.y) {
		fn_1_7958(object);
	}
}

void fn_1_8518(omObjData *object)
{
	Work713C *work;
	s16 mdlId = fn_1_AC(object->work[0]+4096);
	Vec *scale;
	if(mdlId < 0) {
		object->model[0] = Hu3DModelLink(lbl_1_bss_12[object->work[0]]);
	} else {
		object->model[0] = mdlId;
	}
	work = object->data;
	work->unk18.y = 6.0f;
	work->unk18.x = (frandf()*60.0f)-30.0f;
	Hu3DModelAttrSet(object->model[0], 1);
	Hu3DModelAttrSet(object->model[0], 0x40000003);
	Hu3DModelLayerSet(object->model[0], 3);
	Hu3DModelShadowSet(object->model[0]);
	scale = &lbl_1_data_32C[object->work[0]];
	omSetTra(object, work->unk0.x, work->unk0.y, work->unk0.z);
	omSetRot(object, 90, 0, work->unk18.x);
	omSetSca(object, scale->x*0.5f, scale->y*0.5f, scale->z*0.5f);
	work->unk30 = Hu3DParManLink(lbl_1_bss_34, &lbl_1_data_39C);
	if(work->unk30 >= 0) {
		float x = sind(work->unk18.x+180)*-20.0;
		float y = cosd(work->unk18.x+180)*20.0;
		Hu3DParManPosSet(work->unk30, work->unk0.x+x, work->unk0.y+y, work->unk0.z);
		Hu3DParManVecSet(work->unk30, -work->unk18.y*sind(work->unk18.x+180.0f), work->unk18.y*cosd(work->unk18.x+180.0f), 0);
		Hu3DParManAttrSet(work->unk30, 0x804);
		Hu3DParManAttrReset(work->unk30, 1);
		Hu3DParManColorSet(work->unk30, object->work[0]);
		Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(work->unk30), 1);
		Hu3DModelLayerSet(Hu3DParManModelIDGet(work->unk30), 4);
		
	}
	Hu3DModelAttrReset(object->model[0], 0x40000002);
	Hu3DModelAttrReset(object->model[0], 1);
	object->func = fn_1_803C;
}

void fn_1_892C(s16 arg0, s16 arg1, Vec *arg2)
{
	omObjData *object;
	Work713C *work;
	float x;
	float y;
	float z;
	if(lbl_1_bss_1E >= 400) {
		OSReport("over!!\n");
		return;
	}
	lbl_1_bss_1E++;
	object = omAddObjEx(lbl_1_bss_1DC, 102, 1, 0, 2, fn_1_8518);
	object->work[0] = arg1;
	object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work713C), MEMORY_DEFAULT_NUM);
	work = object->data;
	fn_1_40A8InlineFunc(&work->unk0, arg2->x, arg2->y+10, arg2->z+8);
	fn_1_40A8InlineFunc(&work->unkC, arg2->x, 250, arg2->z);
}

s32 fn_1_8AA0(s32 arg0)
{
	float angle = 12.0f*(arg0%30);
	float radius = 730.0f+(60.0f*(arg0/30));
	if(arg0/30 >= 2 && (100.0f > angle || 260.0f < angle)) {
		return 0;
	} else {
		s16 model = Hu3DModelLink(lbl_1_bss_10[0]);
		Hu3DModelAttrSet(model, 0x4001);
		Hu3DModelAttrSet(model, 0x40000003);
		Hu3DModelLayerSet(model, 1);
		Hu3DMotionTimeSet(model, Hu3DMotionMaxTimeGet(model)*frandf());
		Hu3DModelPosSet(model, ((radius*sind(angle))+(frandf()*20.0f))-10, -60.0f, radius*cosd(angle));
		Hu3DModelScaleSet(model, 2, 2, 2);
		Hu3DModelAttrReset(model, 0x40000002);
		Hu3DModelAttrReset(model, 1);
		return 1;
	}
}

void fn_1_AA4C(omObjData *object);

void fn_1_8D58(omObjData *object)
{
	Vec sp38;
	s32 i;
	
	if(omSysExitReq) {
		fn_1_1F58(-1);
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
		object->func = fn_1_AA4C;
	}
	lbl_1_bss_24 += (1.0f/60.0f);
	if(360.0f <= lbl_1_bss_24) {
		lbl_1_bss_24 -= 360.0f;
	}
	Hu3DModelRotSet(object->model[2], 0, lbl_1_bss_24, 0);
	lbl_1_bss_1A8++;
	switch(object->work[0]) {
		case 1000:
			if(!WipeStatGet()) {
				object->work[0]++;
				lbl_1_bss_28 = 0;
			}
			break;
			
		case 1001:
			lbl_1_bss_28++;
			if(60.0f < lbl_1_bss_28) {
				object->work[0]++;
				lbl_1_bss_28 = 0;
				lbl_1_bss_1C4 = lbl_1_data_34;
				lbl_1_bss_1AC = lbl_1_data_4C;
				VECSubtract(&lbl_1_bss_1AC, &lbl_1_bss_1C4, &sp38);
				VECNormalize(&sp38, &sp38);
				HuAudFXListnerSetEX(&lbl_1_bss_1C4, &sp38, 10000.0, 36000.0, 0.0, 300.0, 300.0);
			}
			break;
			
		case 1002:
			lbl_1_bss_28++;
			fn_1_13DC(lbl_1_bss_28/180.0f, &lbl_1_data_40);
			if(180.0f <= lbl_1_bss_28) {
				object->work[0]++;
				fn_1_1350(&lbl_1_data_34, &lbl_1_data_40, &lbl_1_data_4C);
			}
			
			break;
			
		case 1003:
			if(lbl_1_bss_19E < 0) {
				lbl_1_bss_19E = MGSeqStartCreate();
				Hu3DModelAttrSet(lbl_1_bss_4C->model[2], 1);
			} else {
				if(lbl_1_bss_198 < 0 && (MGSeqStatGet(lbl_1_bss_19E) & 0x10)) {
					fn_1_1F24(69);
				}
				if(!MGSeqStatGet(lbl_1_bss_19E)) {
					object->work[0]++;
					lbl_1_bss_1A4 = 3600;
					lbl_1_bss_19C = MGSeqTimerCreate(lbl_1_bss_1A4/60);
					lbl_1_bss_19E = -1;
				}
			}
			break;
			
		case 1004:
			MGSeqParamSet(lbl_1_bss_19C, 1, (lbl_1_bss_1A4+59)/60);
			lbl_1_bss_1A4--;
			if(lbl_1_bss_1A4 < 0) {
				object->work[0] = 1005;
				lbl_1_bss_1A4 = 3600;
				lbl_1_bss_28 = 0;
			}
			break;
			
		case 1005:
			if(lbl_1_bss_19E < 0) {
				MGSeqParamSet(lbl_1_bss_19C, 2, -1);
				lbl_1_bss_19C = -1;
				lbl_1_bss_19E = MGSeqFinishCreate();
				fn_1_1F58(100);
				Hu3DModelAttrReset(lbl_1_bss_4C->model[2], 1);
			} else {
				for(i=0; i<4; i++) {
					if(OM_GET_DATA_PTR(lbl_1_bss_48[i], Work53E8)->unk98 != 2007) {
						break;
					}
				}
				if(i == 4 && !MGSeqStatGet(lbl_1_bss_19E)) {
					object->work[0]++;
					lbl_1_bss_19E = -1;
					lbl_1_bss_20 = 0;
					lbl_1_bss_28 = 0;
					lbl_1_bss_1C4 = lbl_1_data_58;
					lbl_1_bss_1AC = lbl_1_data_70;
				}
			}
			break;
			
		case 1006:
			lbl_1_bss_28++;
			fn_1_13DC(lbl_1_bss_28/120.0f, &lbl_1_data_64);
			if(120.0f <= lbl_1_bss_28) {
				lbl_1_bss_28 = 120.0f;
				for(i=0; i<4; i++) {
					float temp;
					if(OM_GET_DATA_PTR(lbl_1_bss_48[i], Work53E8)->unk98 != 2010) {
						break;
					}
					temp = OM_GET_DATA_PTR(lbl_1_bss_48[i], Work53E8)->unk58;
					if(2.0f < temp && 358.0f > temp) {
						break;
					}
				}
				if(i == 4) {
					object->work[0]++;
					lbl_1_bss_28 = 60;
				}
			}
			break;
			
		case 1007:
			for(i=0; i<4; i++) {
				if(OM_GET_DATA_PTR(lbl_1_bss_48[i], Work53E8)->unk98 != 2014) {
					break;
				}
			}
			if(i == 4) {
				if(0.0f > lbl_1_bss_28--) {
					object->work[0]++;
					lbl_1_bss_28 = 0;
					if(lbl_1_bss_20 == 0) {
						HuAudSStreamPlay(4);
						for(i=0; i<4; i++) {
							OM_GET_DATA_PTR(lbl_1_bss_48[i], Work53E8)->unkC0 = 4;
						}
					} else {
						s32 temp_r27;
						HuAudSStreamPlay(1);
						temp_r27 = -1;
						for(i=0; i<4; i++) {
							s32 temp_r22 = -1;
							s32 temp_r26 = -1;
							Work53E8 *temp_r29;
							s32 j;
							for(j=0; j<4; j++) {
								temp_r29 = lbl_1_bss_48[j]->data;
								if(temp_r29->unkC0 < 0 && temp_r22 < temp_r29->unkBC) {
									temp_r22 = temp_r29->unkBC;
									temp_r26 = j;
								}
							}
							temp_r29 = lbl_1_bss_48[temp_r26]->data;
							temp_r29->unkC0 = i+1;
							if(temp_r27 >= 0 && temp_r29->unkBC == OM_GET_DATA_PTR(lbl_1_bss_48[temp_r27], Work53E8)->unkBC) {
								temp_r29->unkC0 = OM_GET_DATA_PTR(lbl_1_bss_48[temp_r27], Work53E8)->unkC0;
							}
							temp_r27 = temp_r26;
						}
					}
					for(i=0; i<4; i++) {
						GWPlayerCoinWinSet(OM_GET_DATA_PTR(lbl_1_bss_48[i], Work53E8)->unkB0, OM_GET_DATA_PTR(lbl_1_bss_48[i], Work53E8)->unkC0-1);
					}
				}
				
			}
			break;
			
		case 1008:
			lbl_1_bss_28++;
			if(210.0f < lbl_1_bss_28) {
				fn_1_1F58(-1);
				lbl_1_bss_19E = -1;
				WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
				object->func = fn_1_AA4C;
			}
			
			break;
			
		default:
			OSReport("*** main mode error(%d)!!\n", object->work[0]);
			break;
	}
}

void fn_1_9F40(omObjData *object)
{
	s32 singleNo;
	s32 i;
	s32 angleNo;
	lbl_1_bss_24 = 0;
	object->work[0] = 1000;
	object->model[0] = Hu3DModelCreateFile(0x480038);
	Hu3DModelAttrSet(object->model[0], 0x4001);
	Hu3DModelAttrSet(object->model[0], 0x40000002);
	Hu3DModelLayerSet(object->model[0], 0);
	Hu3DModelAttrReset(object->model[0], 1);
	Hu3DModelShadowMapSet(object->model[0]);
	omSetTra(object, 0, -31, 0);
	object->model[1] = Hu3DModelCreateFile(0x480039);
	Hu3DModelAttrSet(object->model[1], 0x4001);
	Hu3DModelAttrSet(object->model[1], 0x40000002);
	Hu3DModelLayerSet(object->model[1], 0);
	Hu3DModelPosSet(object->model[1], 0, -31, 0);
	Hu3DModelAttrReset(object->model[1], 1);
	object->model[2] = Hu3DModelCreateFile(0x48003A);
	Hu3DModelAttrSet(object->model[2], 0x4001);
	Hu3DModelAttrSet(object->model[2], 0x40000002);
	Hu3DModelLayerSet(object->model[2], 0);
	Hu3DModelPosSet(object->model[2], 0, -31, 0);
	Hu3DModelAttrReset(object->model[2], 1);
	for(singleNo=0; singleNo<1; singleNo++) {
		lbl_1_bss_10[singleNo] = Hu3DModelCreateFile(lbl_1_data_368[singleNo]);
		Hu3DModelAttrSet(lbl_1_bss_10[singleNo], 0x4001);
		Hu3DModelAttrSet(lbl_1_bss_10[singleNo], 0x40000003);
	}
	for(i=0, angleNo=0; i<30;) {
		if(fn_1_8AA0(angleNo++) != 0) {
			 i++;
		}
	}
	HuAudFXPlay(1818);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
	object->func = fn_1_8D58;
}

void ObjectSetup(void)
{
	Vec shadowDir;
	s32 i;
	omObjData *object;
	s32 glight;
	OSReport("******* M441 ObjectSetup *********\n");
	lbl_1_bss_1DC = omInitObjMan(600, 8192);
	omGameSysInit(lbl_1_bss_1DC);
	lbl_1_bss_1A8 = 0;
	lbl_1_bss_19E = -1;
	lbl_1_bss_19C = -1;
	lbl_1_bss_1E = 0;
	lbl_1_bss_198 = -1;
	lbl_1_bss_4 = 0;
	lbl_1_bss_8 = 2100;
	lbl_1_bss_0 = 1200;
	Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
	Hu3DCameraPerspectiveSet(1, 30, 20, 20000, 1.2);
	fn_1_1350(&lbl_1_data_10, &lbl_1_data_1C, &lbl_1_data_28);

	glight = Hu3DGLightCreateV(&lbl_1_data_7C, &lbl_1_data_88, &lbl_1_data_94);
	Hu3DGLightStaticSet(glight, 1);
	Hu3DGLightInfinitytSet(glight);
	Hu3DShadowCreate(30, 20, 20000);
	Hu3DShadowTPLvlSet(0.8);
	VECNormalize(&lbl_1_data_98, &shadowDir);
	Hu3DShadowPosSet(&lbl_1_data_98, &shadowDir, &lbl_1_data_A4);
	HuSprExecLayerSet(64, 5);
	omMakeGroupEx(lbl_1_bss_1DC, 0, 4);
	lbl_1_bss_48 = omGetGroupMemberListEx(lbl_1_bss_1DC, 0);
	for(i=0; i<4; i++) {
		object = omAddObjEx(lbl_1_bss_1DC, 100, 3, 16, 0, fn_1_53E8);
		object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work53E8), MEMORY_DEFAULT_NUM);
		object->work[0] = i;
	}
	fn_1_0();
	lbl_1_bss_C = 1;
	omMakeGroupEx(lbl_1_bss_1DC, 1, 20);
	lbl_1_bss_44 = omGetGroupMemberListEx(lbl_1_bss_1DC, 1);
	for(i=0; i<3; i++) {
		lbl_1_bss_18[i] = 0;
		lbl_1_bss_12[i] = Hu3DModelCreateFile(lbl_1_data_314[i]);
		Hu3DModelAttrSet(lbl_1_bss_12[i], 1);
		Hu3DModelAttrSet(lbl_1_bss_12[i], 0x40000003);
	}
	for(i=0; i<20; i++) {
		fn_1_74F4(0);
	}
	omMakeGroupEx(lbl_1_bss_1DC, 2, 400);
	lbl_1_bss_40 = omGetGroupMemberListEx(lbl_1_bss_1DC, 2);
	lbl_1_bss_38 = HuSprAnimReadFile(0x480046);
	HuSprAnimLock(lbl_1_bss_38);
	lbl_1_bss_34 = Hu3DParManCreate(lbl_1_bss_38, 500, &lbl_1_data_39C);
	Hu3DParManAttrSet(lbl_1_bss_34, 1);
	lbl_1_bss_30 = HuSprAnimReadFile(0x480047);
	HuSprAnimLock(lbl_1_bss_30);
	lbl_1_bss_2C = Hu3DParManCreate(lbl_1_bss_30, 20, &lbl_1_data_48C);
	Hu3DParManAttrSet(lbl_1_bss_2C, 1);
	lbl_1_bss_4C = omAddObjEx(lbl_1_bss_1DC, 103, 3, 0, -1, fn_1_9F40);
}

void fn_1_AA4C(omObjData *object)
{
	s32 i;
	if(WipeStatGet()) {
		return;
	}
	if(lbl_1_bss_19E >= 0) {
		MGSeqKill(lbl_1_bss_19E);
	}
	if(lbl_1_bss_19C >= 0) {
		MGSeqKill(lbl_1_bss_19C);
	}
	MGSeqKillAll();
	HuAudAllStop();
	for(i=0; i<4; i++) {
		CharModelKill(lbl_1_data_0[GWPlayerCfg[i].character]);
	}
	omOvlReturnEx(1, 1);
	
}

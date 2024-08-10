#include "REL/m403Dll.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/hsfman.h"
#include "game/hsfdraw.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/object.h"

#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    char unk01[3];
    s32 unk04;
    float unk08;
    s32 unk0C[6];
    s32 unk24[12];
} UnkBss9CData; // Size 0x54

static void fn_1_678C(omObjData *arg0);
static void fn_1_6810(omObjData *arg0);
static void fn_1_6814(omObjData *arg0);
static void fn_1_6980(omObjData *arg0);
static void fn_1_6C98(omObjData *arg0);
static void fn_1_6ED8(omObjData *arg0);
static void fn_1_6FE8(omObjData *arg0);
static void fn_1_73E8(omObjData *arg0);
static void fn_1_799C(void);
static void fn_1_7A98(s16 arg0);
static s32 fn_1_7B20(float arg0, float arg1);
static void fn_1_7BD4(s32 arg0, Vec *arg1);
static s32 fn_1_7C20(UnkBss9CData *arg0, s32 arg1);
static s32 fn_1_7D04(float arg0, float arg1, Vec *arg2);
static s32 fn_1_8254(void);
static s32 fn_1_8274(UnkBss9CData *arg0, s32 *arg1);

static omObjData *lbl_1_bss_B4;
static omObjData *lbl_1_bss_B0;
static omObjData *lbl_1_bss_9C[5];
static s32 lbl_1_bss_98;
static s32 lbl_1_bss_94;
static s32 lbl_1_bss_90;
static s32 lbl_1_bss_8C;
static s32 lbl_1_bss_88;
static s32 lbl_1_bss_84;
static float lbl_1_bss_80;
static s32 lbl_1_bss_7C;
static s32 lbl_1_bss_78;
static s32 lbl_1_bss_74;
static s32 lbl_1_bss_70;
static s32 lbl_1_bss_58[6];

static Vec lbl_1_data_158[] = {
    {  92.39f, 0.0f,  38.27f },
    {  100.0f, 0.0f,    0.0f },
    {  92.39f, 0.0f, -38.27f },
    {  70.71f, 0.0f, -70.71f },
    {  38.27f, 0.0f, -92.39f },
    {    0.0f, 0.0f, -100.0f },
    { -38.27f, 0.0f, -92.39f },
    { -70.71f, 0.0f, -70.71f },
    { -92.39f, 0.0f, -38.27f },
    { -100.0f, 0.0f,    0.0f },
    { -92.39f, 0.0f,  38.27f },
    { -70.71f, 0.0f,  70.71f },
    { -38.27f, 0.0f,  92.39f },
    {    0.0f, 0.0f,  100.0f },
    {  38.27f, 0.0f,  92.39f },
    {  70.71f, 0.0f,  70.71f }
};

static Vec lbl_1_data_218[] = {
    {  55.43f, 0.0f,  22.96f },
    {   60.0f, 0.0f,    0.0f },
    {  55.43f, 0.0f, -22.96f },
    {  42.43f, 0.0f, -42.43f },
    {  22.96f, 0.0f, -55.43f },
    {    0.0f, 0.0f,  -60.0f },
    { -22.96f, 0.0f, -55.43f },
    { -42.43f, 0.0f, -42.43f },
    { -55.43f, 0.0f, -22.96f },
    {  -60.0f, 0.0f,    0.0f },
    { -55.43f, 0.0f,  22.96f },
    { -42.43f, 0.0f,  42.43f },
    { -22.96f, 0.0f,  55.43f },
    {    0.0f, 0.0f,   60.0f },
    {  22.96f, 0.0f,  55.43f },
    {  42.43f, 0.0f,  42.43f }
};

static Vec lbl_1_data_2D8[] = {
    {   38.79f, 0.0f,  -53.4f },
    {     0.0f, 0.0f, -120.0f },
    {  -38.79f, 0.0f,  -53.4f },
    { -114.13f, 0.0f, -37.08f },
    {  -62.77f, 0.0f,   20.4f },
    {  -70.53f, 0.0f,  97.08f },
    {     0.0f, 0.0f,   66.0f },
    {   70.53f, 0.0f,  97.08f },
    {   62.77f, 0.0f,   20.4f },
    {  114.13f, 0.0f, -37.08f }
};

static Vec lbl_1_data_350[] = {
    {  21.34f, 0.0f, -29.37f },
    {    0.0f, 0.0f,  -66.0f },
    { -21.34f, 0.0f, -29.37f },
    { -62.77f, 0.0f,  -20.4f },
    { -34.52f, 0.0f,  11.22f },
    { -38.79f, 0.0f,   53.4f },
    {    0.0f, 0.0f,   36.3f },
    {  38.79f, 0.0f,   53.4f },
    {  34.52f, 0.0f,  11.22f },
    {  62.77f, 0.0f,  -20.4f }
};

static Vec lbl_1_data_3C8[] = {
    {  110.87f, 0.0f,   45.92f },
    {   120.0f, 0.0f,     0.0f },
    {  110.87f, 0.0f,  -45.92f },
    {   84.85f, 0.0f,  -84.85f },
    {   45.92f, 0.0f, -110.87f },
    {     0.0f, 0.0f,  -120.0f },
    {  -45.92f, 0.0f, -110.87f },
    {  -84.85f, 0.0f,  -84.85f },
    { -110.87f, 0.0f,  -45.92f },
    {  -120.0f, 0.0f,     0.0f },
    { -110.87f, 0.0f,   45.92f },
    {  -84.85f, 0.0f,   84.85f },
    {  -45.92f, 0.0f,  110.87f },
    {     0.0f, 0.0f,   120.0f },
    {   45.92f, 0.0f,  110.87f },
    {   84.85f, 0.0f,   84.85f }
};

static Vec lbl_1_data_488[] = {
    {  73.17f, 0.0f,  30.31f },
    {   79.2f, 0.0f,    0.0f },
    {  73.17f, 0.0f, -30.31f },
    {   56.0f, 0.0f,  -56.0f },
    {  30.31f, 0.0f, -73.17f },
    {    0.0f, 0.0f,  -79.2f },
    { -30.31f, 0.0f, -73.17f },
    {  -56.0f, 0.0f,  -56.0f },
    { -73.17f, 0.0f, -30.31f },
    {  -79.2f, 0.0f,    0.0f },
    { -73.17f, 0.0f,  30.31f },
    {  -56.0f, 0.0f,   56.0f },
    { -30.31f, 0.0f,  73.17f },
    {    0.0f, 0.0f,   79.2f },
    {  30.31f, 0.0f,  73.17f },
    {   56.0f, 0.0f,   56.0f }
};

static Vec lbl_1_data_548[] = {
    {   48.49f, 0.0f, -66.74f },
    {     0.0f, 0.0f, -150.0f },
    {  -48.49f, 0.0f, -66.74f },
    { -142.66f, 0.0f, -46.35f },
    {  -78.46f, 0.0f,  25.49f },
    {  -88.17f, 0.0f, 121.35f },
    {     0.0f, 0.0f,   82.5f },
    {   88.17f, 0.0f, 121.35f },
    {   78.46f, 0.0f,  25.49f },
    {  142.66f, 0.0f, -46.35f }
};

static Vec lbl_1_data_5C0[] = {
    {  29.09f, 0.0f, -40.05f },
    {    0.0f, 0.0f,  -90.0f },
    { -29.09f, 0.0f, -40.05f },
    { -85.59f, 0.0f, -27.81f },
    { -47.08f, 0.0f,   15.3f },
    {  -52.9f, 0.0f,  72.81f },
    {    0.0f, 0.0f,   49.5f },
    {   52.9f, 0.0f,  72.81f },
    {  47.08f, 0.0f,   15.3f },
    {  85.59f, 0.0f, -27.81f }
};

static Vec lbl_1_data_638[] = {
    {  129.1f, 0.0f,   54.6f },
    {  140.0f, 0.0f,    0.0f },
    {  129.3f, 0.0f,  -53.6f },
    {   99.0f, 0.0f,  -99.0f },
    {   53.6f, 0.0f, -129.3f },
    {    0.0f, 0.0f, -140.0f },
    {  -53.6f, 0.0f, -129.3f },
    {  -99.0f, 0.0f,  -99.0f },
    { -129.4f, 0.0f,  -53.5f },
    { -140.0f, 0.0f,    0.0f },
    { -136.0f, 0.0f,   20.4f },
    { -102.1f, 0.0f,   -7.6f },
    {  -70.0f, 0.0f,  -14.0f },
    {  -37.8f, 0.0f,   -7.6f },
    {  -10.6f, 0.0f,   10.6f },
    {    7.6f, 0.0f,   37.8f },
    {   14.0f, 0.0f,   70.0f },
    {    7.6f, 0.0f,  102.2f },
    {  -20.4f, 0.0f,  136.0f },
    {    0.1f, 0.0f,  140.1f },
    {   53.9f, 0.0f,  129.5f },
    {   99.5f, 0.0f,   99.0f }
};

static Vec lbl_1_data_740[] = {
    {   95.9f, 0.0f,   42.9f },
    {  106.6f, 0.0f,    0.4f },
    {   98.4f, 0.0f,  -37.2f },
    {   81.7f, 0.0f,  -65.9f },
    {   55.4f, 0.0f,  -89.6f },
    {   11.5f, 0.0f, -101.7f },
    {  -24.5f, 0.0f,  -99.9f },
    {  -60.9f, 0.0f,  -88.6f },
    {  -98.7f, 0.0f,  -64.4f },
    { -110.4f, 0.0f,  -41.5f },
    { -110.4f, 0.0f,  -30.8f },
    {  -90.4f, 0.0f,  -42.3f },
    {  -53.8f, 0.0f,  -48.5f },
    {  -14.6f, 0.0f,  -40.5f },
    {   17.1f, 0.0f,  -16.3f },
    {   35.8f, 0.0f,   28.2f },
    {   35.8f, 0.0f,   65.6f },
    {   24.7f, 0.0f,  101.6f },
    {   19.6f, 0.0f,  114.6f },
    {   34.9f, 0.0f,  114.5f },
    {   62.9f, 0.0f,   99.0f },
    {   83.0f, 0.0f,   73.2f }
};

static Vec lbl_1_data_848[] = {
    {  110.9f, 0.0f,   45.9f },
    {  120.0f, 0.0f,    0.0f },
    {  110.9f, 0.0f,  -45.8f },
    {   84.8f, 0.0f,  -84.9f },
    {   45.9f, 0.0f, -110.9f },
    {    0.0f, 0.0f, -120.0f },
    {  -45.9f, 0.0f, -110.9f },
    {  -84.9f, 0.0f,  -84.8f },
    { -110.9f, 0.0f,  -45.9f },
    { -120.0f, 0.0f,    0.0f },
    { -116.5f, 0.0f,   17.5f },
    {  -87.6f, 0.0f,   -6.6f },
    {  -60.0f, 0.0f,  -12.0f },
    {  -32.4f, 0.0f,   -6.5f },
    {   -9.1f, 0.0f,    9.1f },
    {    6.5f, 0.0f,   32.5f },
    {   12.0f, 0.0f,   60.0f },
    {    6.5f, 0.0f,   87.6f },
    {  -17.5f, 0.0f,  116.5f },
    {    0.0f, 0.0f,  120.0f },
    {   45.9f, 0.0f,  110.9f },
    {   84.8f, 0.0f,   84.9f }
};

static Vec lbl_1_data_950[] = {
    {  80.0f, 0.0f,  31.0f },
    {  83.9f, 0.0f,  -0.1f },
    {  77.2f, 0.0f, -31.7f },
    {  60.4f, 0.0f, -56.8f },
    {  35.6f, 0.0f, -77.4f },
    {  -0.5f, 0.0f, -84.1f },
    { -31.5f, 0.0f, -82.9f },
    { -58.9f, 0.0f, -71.4f },
    { -86.3f, 0.0f, -49.4f },
    { -91.5f, 0.0f, -36.4f },
    { -91.5f, 0.0f, -27.3f },
    { -82.1f, 0.0f, -29.8f },
    { -54.7f, 0.0f, -36.2f },
    { -21.9f, 0.0f, -30.9f },
    {  13.3f, 0.0f, -10.2f },
    {  28.3f, 0.0f,  18.3f },
    {  33.4f, 0.0f,  58.4f },
    {  28.0f, 0.0f,  81.6f },
    {  20.7f, 0.0f,  93.3f },
    {  30.4f, 0.0f,  93.3f },
    {  55.4f, 0.0f,  82.2f },
    {  70.4f, 0.0f,  59.3f }
};

static s32 lbl_1_data_A58[] = {
    DATA_MAKE_NUM(DATADIR_M403, 4),
    DATA_MAKE_NUM(DATADIR_M403, 5),
    DATA_MAKE_NUM(DATADIR_M403, 6),
    DATA_MAKE_NUM(DATADIR_M403, 9),
    DATA_MAKE_NUM(DATADIR_M403, 12),
    DATA_MAKE_NUM(DATADIR_M403, 15),
    DATA_MAKE_NUM(DATADIR_M403, 7),
    DATA_MAKE_NUM(DATADIR_M403, 8),
    DATA_MAKE_NUM(DATADIR_M403, 10),
    DATA_MAKE_NUM(DATADIR_M403, 11),
    DATA_MAKE_NUM(DATADIR_M403, 13),
    DATA_MAKE_NUM(DATADIR_M403, 14)
};

static Vec lbl_1_data_A88[] = {
    { -400.0f, 0.0f, 300.0f },
    {    0.0f, 0.0f, 300.0f },
    {  400.0f, 0.0f, 300.0f },
    { -400.0f, 0.0f, 700.0f },
    {    0.0f, 0.0f, 700.0f },
    {  400.0f, 0.0f, 700.0f }
};

static s32 lbl_1_data_AD0[] = { 6, 8, 10 };
static s32 lbl_1_data_ADC[] = { 7, 9, 11 };
static s32 lbl_1_data_AE8[] = { 1, 2, 3, 4, 5 };

static Vec *lbl_1_data_AFC[] = {
    lbl_1_data_3C8,
    lbl_1_data_158,
    lbl_1_data_548,
    lbl_1_data_2D8,
    lbl_1_data_638,
    lbl_1_data_848
};

static s32 lbl_1_data_B14[] = {
    16, 16, 10, 10, 22, 22
};

static Vec lbl_1_data_B2C[] = {
    {  0.0f, 0.0f,   0.0f },
    {  0.0f, 0.0f,   0.0f },
    {  0.0f, 0.0f, -20.0f },
    {  0.0f, 0.0f, -20.0f },
    { 40.0f, 0.0f, -20.0f },
    { 40.0f, 0.0f, -20.0f }
};

static Vec *lbl_1_data_B74[][2] = {
    { lbl_1_data_3C8, lbl_1_data_488 },
    { lbl_1_data_158, lbl_1_data_218 },
    { lbl_1_data_548, lbl_1_data_5C0 },
    { lbl_1_data_2D8, lbl_1_data_350 },
    { lbl_1_data_638, lbl_1_data_740 },
    { lbl_1_data_848, lbl_1_data_950 }
};

static s32 lbl_1_data_BA4[] = {
    16, 16, 10, 10, 22, 22
};

void fn_1_650C(Process *arg0) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 i;

    sp20.x = 0.0f;
    sp20.y = 3000.0f;
    sp20.z = 50.0f;
    sp14.x = 0.0f;
    sp14.y = 1.0f;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    lbl_1_bss_B4 = omAddObjEx(arg0, 10, 2, 0, -1, fn_1_678C);
    lbl_1_bss_B0 = omAddObjEx(arg0, 12, 4, 0, -1, fn_1_6814);
    for (i = 0; i < 5; i++) {
        lbl_1_bss_9C[i] = omAddObjEx(arg0, 14, 7, 0, -1, fn_1_6C98);
    }
    Hu3DShadowCreate(30.0f, 20.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.65f);
    Hu3DShadowPosSet(&sp20, &sp14, &sp8);
    lbl_1_bss_98 = 0;
    lbl_1_bss_94 = lbl_1_bss_90 = 2;
    lbl_1_bss_84 = 0;
    lbl_1_bss_88 = 0;
    lbl_1_bss_80 = 0.75f;
    lbl_1_bss_74 = 3;
    lbl_1_bss_70 = 0;
    lbl_1_bss_7C = 0;
    lbl_1_bss_78 = 0;
    memset(lbl_1_bss_58, 0, sizeof(lbl_1_bss_58));
}

void fn_1_676C(void) {
    fn_1_799C();
}

static void fn_1_678C(omObjData *arg0) {
    arg0->stat |= 0x100;
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M403, 16));
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M403, 17));
    arg0->func = fn_1_6810;
}

static void fn_1_6810(omObjData *arg0) {
}

static void fn_1_6814(omObjData *arg0) {
    arg0->stat |= 0x100;
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M403, 0));
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M403, 3));
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M403, 1));
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M403, 2));
    Hu3DMotionSpeedSet(arg0->model[2], 0.0f);
    Hu3DModelShadowSet(arg0->model[1]);
    Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, -500.0f);
    Hu3DData[arg0->model[3]].unk_94 = 0.0f;
    Hu3DData[arg0->model[3]].unk_98 = 2.0f;
    arg0->work[3] = 30;
    arg0->func = fn_1_6980;
}

static void fn_1_6980(omObjData *arg0) {
    ModelData *var_r30;
    UnkBss9CData *var_r29;

    if (lbl_1_bss_7C != 0) {
        if (lbl_1_bss_78 == 0) {
            if (arg0->work[0] < 60.0f) {
                arg0->work[0]++;
                var_r30 = &Hu3DData[arg0->model[1]];
                var_r30->rot.x = -120.0f * arg0->work[0] / 60.0f;
            } else {
                lbl_1_bss_78 ^= 1;
                lbl_1_bss_7C = 0;
            }
        } else if (arg0->work[0] != 0) {
            arg0->work[0]--;
            var_r30 = &Hu3DData[arg0->model[1]];
            var_r30->rot.x = -120.0f * arg0->work[0] / 60.0f;
        } else {
            lbl_1_bss_78 ^= 1;
            lbl_1_bss_7C = 0;
        }
    }
    var_r29 = lbl_1_bss_9C[lbl_1_bss_94]->data;
    if (lbl_1_bss_8C != 0) {
        lbl_1_bss_8C = 0;
        lbl_1_bss_88 = 1;
    }
    if (lbl_1_bss_94 != lbl_1_bss_90) {
        lbl_1_bss_88 = 0;
        lbl_1_bss_84 = 0;
    }
    lbl_1_bss_90 = lbl_1_bss_94;
    if (var_r29->unk00_field0 != 0) {
        lbl_1_bss_94 = (lbl_1_bss_94 + 1) % 5;
        lbl_1_bss_84 = 1;
    }
    if (arg0->work[3] != 0) {
        if (--arg0->work[3] == 0) {
            HuAudFXPlay(0x521);
        }
    }
}

static void fn_1_6C98(omObjData *arg0) {
    UnkBss9CData *var_r29;
    s32 i;

    var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*var_r29), MEMORY_DEFAULT_NUM);
    arg0->data = var_r29;
    memset(arg0->data, 0, sizeof(*var_r29));
    for (i = 0; i < 12; i++) {
        var_r29->unk24[i] = -1;
    }
    for (i = 0; i < 12U; i++) {
        var_r29->unk24[i] = Hu3DModelCreateFile(lbl_1_data_A58[i]);
        Hu3DModelAttrSet(var_r29->unk24[i], 1);
    }
    arg0->model[0] = var_r29->unk24[0];
    Hu3DModelAttrReset(arg0->model[0], 1);
    var_r29->unk00_field0 = 0;
    var_r29->unk04 = 4 - lbl_1_bss_98;
    fn_1_6FE8(arg0);
    arg0->trans.y = 5.0f;
    arg0->trans.z = -500.0f;
    switch (var_r29->unk04) {
        case 0:
        case 1:
            break;
        case 2:
            for (i = 0; i < 7; i++) {
                Hu3DModelShadowSet(arg0->model[i]);
            }
            break;
        case 3:
            for (i = 0; i < 7; i++) {
                Hu3DModelShadowMapSet(arg0->model[i]);
            }
            arg0->trans.y = 2.5f;
            break;
        case 4:
            for (i = 0; i < 7; i++) {
                Hu3DModelShadowMapSet(arg0->model[i]);
            }
            arg0->trans.y = 0.0f;
            break;
    }
    fn_1_6ED8(arg0);
    lbl_1_bss_98++;
    arg0->func = fn_1_73E8;
}

static void fn_1_6ED8(omObjData *arg0) {
    Mtx sp38;
    Mtx sp8;
    s32 i;

    PSMTXTrans(sp38, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    mtxRot(sp8, arg0->rot.x, arg0->rot.y, arg0->rot.z);
    PSMTXConcat(sp38, sp8, sp38);
    for (i = 0; i < 6; i++) {
        PSMTXTrans(sp8, lbl_1_data_A88[i].x, lbl_1_data_A88[i].y, lbl_1_data_A88[i].z);
        PSMTXConcat(sp38, sp8, sp8);
        Hu3DModelPosSet(arg0->model[i + 1], sp8[0][3], sp8[1][3], sp8[2][3]);
        Hu3DModelRotSet(arg0->model[i + 1], arg0->rot.x, arg0->rot.y, arg0->rot.z);
    }
}

static void fn_1_6FE8(omObjData *arg0) {
    UnkBss9CData *temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 var_r24;
    s32 var_r25;
    s32 var_r26;
    s32 sp8[6];
    s32 i;

    temp_r30 = arg0->data;
    for (i = 0; i < 100; i++) {
        temp_r29 = (frand8() * 3) >> 8;
        temp_r28 = (frand8() * 3) >> 8;
        var_r26 = lbl_1_data_AD0[temp_r29];
        lbl_1_data_AD0[temp_r29] = lbl_1_data_AD0[temp_r28];
        lbl_1_data_AD0[temp_r28] = var_r26;
        temp_r29 = (frand8() * 3) >> 8;
        temp_r28 = (frand8() * 3) >> 8;
        var_r26 = lbl_1_data_ADC[temp_r29];
        lbl_1_data_ADC[temp_r29] = lbl_1_data_ADC[temp_r28];
        lbl_1_data_ADC[temp_r28] = var_r26;
        temp_r29 = (frand8() * 5) >> 8;
        temp_r28 = (frand8() * 5) >> 8;
        var_r26 = lbl_1_data_AE8[temp_r29];
        lbl_1_data_AE8[temp_r29] = lbl_1_data_AE8[temp_r28];
        lbl_1_data_AE8[temp_r28] = var_r26;
    }
    var_r25 = 0;
    for (i = 0; i < 6; i++) {
        if (lbl_1_bss_58[i] < 6) {
            sp8[var_r25++] = i;
        }
    }
    for (i = 0; i < 100; i++) {
        temp_r29 = (var_r25 * frand8()) >> 8;
        temp_r28 = (var_r25 * frand8()) >> 8;
        var_r26 = sp8[temp_r29];
        sp8[temp_r29] = sp8[temp_r28];
        sp8[temp_r28] = var_r26;
    }
    for (i = 0; i < 6; i++) {
        temp_r30->unk0C[i] = 0;
    }
    for (i = 0; i < lbl_1_bss_70; i++) {
        temp_r30->unk0C[sp8[i]] = lbl_1_data_ADC[i];
    }
    for (; i < lbl_1_bss_74; i++) {
        temp_r30->unk0C[sp8[i]] = lbl_1_data_AD0[i];
    }
    var_r24 = 0;
    for (i = 0; i < 6; i++) {
        if (temp_r30->unk0C[i] == 0) {
            temp_r30->unk0C[i] = lbl_1_data_AE8[var_r24++];
        }
    }
    memcpy(lbl_1_bss_58, &temp_r30->unk0C, sizeof(temp_r30->unk0C));
    for (i = 0; i < 6; i++) {
        if (arg0->model[i + 1] >= 0) {
            Hu3DModelAttrSet(arg0->model[i + 1], 1);
        }
    }
    for (i = 0; i < 6; i++) {
        arg0->model[i + 1] = temp_r30->unk24[temp_r30->unk0C[i]];
        Hu3DModelAttrReset(arg0->model[i + 1], 1);
    }
}

static void fn_1_73E8(omObjData *arg0) {
    UnkBss9CData *temp_r30;
    ModelData *var_r27;
    s32 i;

    temp_r30 = arg0->data;
    if (lbl_1_bss_88 == 0) {
        if (lbl_1_bss_7C != 0 && temp_r30->unk04 < 3) {
            var_r27 = &Hu3DData[lbl_1_bss_B0->model[1]];
            arg0->rot.x = var_r27->rot.x;
            switch (temp_r30->unk04) {
                case 0:
                    arg0->trans.z = -500.0f + 2.5f * lbl_1_bss_B0->work[0] / 60.0f;
                    break;
                case 1:
                    arg0->trans.z = -500.0f + 5.0f * lbl_1_bss_B0->work[0] / 60.0f;
                    break;
                case 2:
                    arg0->trans.z = -500.0f + 7.5f * lbl_1_bss_B0->work[0] / 60.0f;
                    break;
            }
        } else {
            return;
        }
    } else {
        switch (temp_r30->unk04) {
            case 0:
                if (lbl_1_bss_84 != 0) {
                    arg0->trans.z = -495.0f;
                    temp_r30->unk04++;
                }
                break;
            case 1:
                if (lbl_1_bss_84 != 0) {
                    arg0->trans.z = -492.5f;
                    temp_r30->unk00_field0 = 0;
                    temp_r30->unk04++;
                    temp_r30->unk08 = 0.0f;
                    for (i = 0; i < 7; i++) {
                        Hu3DModelShadowSet(arg0->model[i]);
                    }
                }
                break;
            case 2:
                if (lbl_1_bss_84 != 0) {
                    temp_r30->unk04++;
                    arg0->trans.y = 2.5f;
                    for (i = 0; i < 7; i++) {
                        Hu3DModelShadowReset(arg0->model[i]);
                        Hu3DModelShadowMapSet(arg0->model[i]);
                    }
                } else {
                    temp_r30->unk08 += lbl_1_bss_80;
                    if (temp_r30->unk08 > 90.0f) {
                        temp_r30->unk00_field0 = 1;
                        temp_r30->unk08 = 90.0f;
                        HuAudFXPlay(0x522);
                    }
                    arg0->rot.x = -120.0 * cosd(temp_r30->unk08);
                    arg0->trans.z = 7.5 * cosd(temp_r30->unk08) + -500.0;
                }
                break;
            case 3:
                if (lbl_1_bss_84 != 0) {
                    temp_r30->unk04++;
                    arg0->trans.y = 0.0f;
                }
                break;
            case 4:
                if (lbl_1_bss_84 != 0) {
                    temp_r30->unk04 = 0;
                    arg0->trans.y = 5.0f;
                    arg0->trans.z = -497.5f;
                    arg0->rot.x = -120.0f;
                    for (i = 0; i < 7; i++) {
                        fn_1_7A98(arg0->model[i]);
                    }
                    fn_1_6FE8(arg0);
                }
                break;
        }
    }
    fn_1_6ED8(arg0);
}

static void fn_1_799C(void) {
    omObjData* temp_r30;
    UnkBss9CData *temp_r29;
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        temp_r30 = lbl_1_bss_9C[i];
        temp_r29 = temp_r30->data;
        if (temp_r29 != NULL) {
            for (j = 0; j < 12; j++) {
                if (temp_r29->unk24[j] >= 0) {
                    Hu3DModelKill(temp_r29->unk24[j]);
                }
            }
            HuMemDirectFree(temp_r29);
            lbl_1_bss_9C[i]->data = NULL;
        }
        for (i = 0; i < temp_r30->mdlcnt; i++) {
            temp_r30->model[i] = -1;
        }
    }
}

static void fn_1_7A98(s16 arg0) {
    s16 i;
    HsfData *temp_r31;
    HsfObject *var_r28;
    HsfObject *var_r30;
    HsfConstData *temp_r27;

    temp_r31 = Hu3DData[arg0].hsfData;
    var_r28 = temp_r31->object;
    for (i = 0; i < temp_r31->objectCnt; i++, var_r28++) {
        var_r30 = var_r28;
        if (var_r30->constData) {
            temp_r27 = var_r30->constData;
            temp_r27->flags &= ~8;
        }
    }
}

static s32 fn_1_7B20(float arg0, float arg1) {
    s32 var_r31;
    s32 var_r30;

    var_r31 = (arg0 + 600.0f) / 400.0f;
    var_r30 = (arg1 + 400.0f) / 400.0f;
    if (var_r31 < 0) {
        var_r31 = 0;
    } else if (var_r31 > 2) {
        var_r31 = 2;
    }
    if (var_r30 < 0) {
        var_r30 = 0;
    } else if (var_r30 > 1) {
        var_r30 = 1;
    }
    return var_r31 + var_r30 * 3;
}

static void fn_1_7BD4(s32 arg0, Vec *arg1) {
    arg1->x = lbl_1_data_A88[arg0].x;
    arg1->y = lbl_1_data_A88[arg0].y;
    arg1->z = lbl_1_data_A88[arg0].z;
}

static s32 fn_1_7C20(UnkBss9CData *arg0, s32 arg1) {
    return arg0->unk0C[arg1];
}

void fn_1_7C30(float arg0) {
    lbl_1_bss_8C = 1;
    lbl_1_bss_80 = arg0;
}

void fn_1_7C50(s32 arg0) {
    lbl_1_bss_74 = arg0;
}

void fn_1_7C60(void) {
    float var_f30;

    lbl_1_bss_7C = 1;
    var_f30 = (lbl_1_bss_78 == 0) ? 1.6666666f : -1.6666666f;
    Hu3DMotionSpeedSet(lbl_1_bss_B0->model[2], var_f30);
    HuAudFXPlay(0x524);
}

static s32 fn_1_7D04(float arg0, float arg1, Vec *arg2) {
    Mtx sp4C;
    Mtx sp1C;
    Vec sp10;
    Vec *var_r30;
    s32 temp_r28;
    s32 temp_r21;
    s32 temp_r23;
    omObjData *temp_r31;
    UnkBss9CData *var_r22;
    s32 i;

    temp_r31 = lbl_1_bss_9C[lbl_1_bss_94];
    var_r22 = temp_r31->data;
    temp_r21 = fn_1_7B20(arg0, arg1);
    temp_r28 = fn_1_7C20(var_r22, temp_r21);
    if (temp_r28 < 6) {
        return 0;
    }
    temp_r28 -= 6;
    fn_1_7BD4(temp_r21, &sp10);
    sp10 = lbl_1_data_A88[temp_r21];
    PSMTXTrans(sp4C, temp_r31->trans.x, temp_r31->trans.y, temp_r31->trans.z);
    mtxRot(sp1C, temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
    PSMTXConcat(sp4C, sp1C, sp4C);
    PSMTXTrans(sp1C, sp10.x, sp10.y, sp10.z);
    PSMTXConcat(sp4C, sp1C, sp4C);
    var_r30 = lbl_1_data_AFC[temp_r28];
    temp_r23 = lbl_1_data_B14[temp_r28];
    for (i = 0; i < temp_r23; i++) {
        PSMTXTrans(sp1C, var_r30->x, var_r30->y, var_r30->z);
        PSMTXConcat(sp4C, sp1C, sp1C);
        arg2->x = sp1C[0][3];
        arg2->y = sp1C[1][3];
        arg2->z = sp1C[2][3];
        arg2++;
        var_r30++;
    }
    return temp_r23;
}

float fn_1_7F78(float arg0, float arg1) {
    float temp_f30;
    float var_f31;
    omObjData *temp_r31;

    temp_r31 = lbl_1_bss_9C[lbl_1_bss_94];
    temp_f30 = -(arg1 - temp_r31->trans.z);
    if (cosd(temp_r31->rot.x) <= 0.0) {
        var_f31 = 9999.0f;
    } else {
        var_f31 = temp_f30 * sind(temp_r31->rot.x) / cosd(temp_r31->rot.x);
        if (var_f31 > 9999.0f) {
            var_f31 = 9999.0f;
        }
    }
    return var_f31;
}

float fn_1_80D4(Vec *arg0, float arg1) {
    return fn_1_7F78(0.0f, arg0->z - arg1);
}

static s32 fn_1_8254(void) {
    return lbl_1_bss_7C;
}

s32 fn_1_8264(void) {
    return lbl_1_bss_88;
}

static s32 fn_1_8274(UnkBss9CData *arg0, s32 *arg1) {
    s32 var_r30;
    s32 i;

    var_r30 = 0;
    for (i = 0; i < 6; i++) {
        if (arg0->unk0C[i] >= 6) {
            arg1[var_r30++] = i;
        }
    }
    return var_r30;
}

s32 fn_1_82D0(Vec *arg0) {
    omObjData *temp_r31;
    UnkBss9CData *temp_r28;
    s32 sp8[6];
    s32 var_r26;
    s32 temp_r27;
    s32 i;

    temp_r31 = lbl_1_bss_9C[lbl_1_bss_94];
    temp_r28 = temp_r31->data;
    var_r26 = fn_1_8274(temp_r28, sp8);
    for (i = 0; i < var_r26; i++) {
        fn_1_7BD4(sp8[i], arg0);
        temp_r27 = fn_1_7C20(temp_r28, sp8[i]) - 6;
        arg0->x += temp_r31->trans.x + lbl_1_data_B2C[temp_r27].x;
        arg0->y += temp_r31->trans.y + lbl_1_data_B2C[temp_r27].y;
        arg0->z += temp_r31->trans.z + lbl_1_data_B2C[temp_r27].z;
        arg0++;
    }
    return var_r26;
}

s32 fn_1_8470(Vec *arg0) {
    Mtx sp50;
    Mtx sp20;
    omObjData* temp_r30;
    UnkBss9CData *temp_r27;
    s32 sp8[6];
    s32 temp_r26;
    s32 var_r25;
    s32 i;

    temp_r30 = lbl_1_bss_9C[lbl_1_bss_94];
    temp_r27 = temp_r30->data;
    var_r25 = fn_1_8274(temp_r27, sp8);
    PSMTXTrans(sp50, temp_r30->trans.x, temp_r30->trans.y, temp_r30->trans.z);
    mtxRot(sp20, temp_r30->rot.x, temp_r30->rot.y, temp_r30->rot.z);
    PSMTXConcat(sp50, sp20, sp50);
    for (i = 0; i < var_r25; i++) {
        fn_1_7BD4(sp8[i], arg0);
        temp_r26 = fn_1_7C20(temp_r27, sp8[i]) - 6;
        arg0->x += lbl_1_data_B2C[temp_r26].x;
        arg0->y += lbl_1_data_B2C[temp_r26].y;
        arg0->z += lbl_1_data_B2C[temp_r26].z;
        PSMTXTrans(sp20, arg0->x, arg0->y, arg0->z);
        PSMTXConcat(sp50, sp20, sp20);
        arg0->x = sp20[0][3];
        arg0->y = sp20[1][3];
        arg0->z = sp20[2][3];
        arg0++;
    }
    return var_r25;
}

void fn_1_8670(s32 arg0) {
    if (arg0 > lbl_1_bss_74) {
        arg0 = lbl_1_bss_74;
    }
    lbl_1_bss_70 = arg0;
}

s32 fn_1_86A0(Vec *arg0, Vec *arg1) {
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    s32 temp_r17;
    s32 temp_r21;
    s32 temp_r24;
    s32 temp_r27;
    s32 var_r20;
    Vec *temp_r29;
    Vec *temp_r30;
    omObjData *temp_r28;
    UnkBss9CData *temp_r18;
    s32 i;

    temp_r28 = lbl_1_bss_9C[lbl_1_bss_94];
    temp_r18 = temp_r28->data;
    if (temp_r28->rot.x > 0.0f || temp_r28->rot.x <= -90.0f) {
        return 0;
    }
    VECSubtract(arg0, &temp_r28->trans, &sp3C);
    sp3C.z /= cosd(temp_r28->rot.x);
    temp_r17 = fn_1_7B20(arg0->x, arg0->z);
    temp_r24 = fn_1_7C20(temp_r18, temp_r17);
    if (temp_r24 < 6) {
        return 0;
    }
    temp_r24 -= 6;
    sp48 = lbl_1_data_A88[temp_r17];
    VECSubtract(&sp3C, &sp48, &sp3C);
    temp_r30 = lbl_1_data_B74[temp_r24][0];
    temp_r29 = lbl_1_data_B74[temp_r24][1];
    temp_r21 = lbl_1_data_BA4[temp_r24];
    for (i = 0; i < temp_r21; i++) {
        temp_r27 = (i + 1) % temp_r21;
        VECSubtract(&temp_r30[temp_r27], &temp_r30[i], &sp24);
        VECSubtract(&sp3C, &temp_r30[temp_r27], &sp18);
        VECCrossProduct(&sp24, &sp18, &spC);
        if (spC.y < 0.0f) {
            continue;
        }
        VECSubtract(&temp_r29[temp_r27], &temp_r30[temp_r27], &sp24);
        VECSubtract(&sp3C, &temp_r29[temp_r27], &sp18);
        VECCrossProduct(&sp24, &sp18, &spC);
        if (spC.y < 0.0f) {
            continue;
        }
        VECSubtract(&temp_r29[i], &temp_r29[temp_r27], &sp24);
        VECSubtract(&sp3C, &temp_r29[i], &sp18);
        VECCrossProduct(&sp24, &sp18, &spC);
        if (spC.y < 0.0f) {
            continue;
        }
        VECSubtract(&temp_r30[i], &temp_r29[i], &sp24);
        VECSubtract(&sp3C, &temp_r30[i], &sp18);
        VECCrossProduct(&sp24, &sp18, &spC);
        if (spC.y < 0.0f) {
            continue;
        }
        VECSubtract(&temp_r30[temp_r27], &temp_r30[i], &sp24);
        temp_f30 = (sp3C.x * sp24.x - sp24.x * temp_r30[i].x + sp3C.y * sp24.y - sp24.y * temp_r30[i].y + sp3C.z * sp24.z - sp24.z * temp_r30[i].z) / (sp24.x * sp24.x + sp24.y * sp24.y + sp24.z * sp24.z);
        sp30.x = temp_r30[i].x + temp_f30 * sp24.x;
        sp30.y = temp_r30[i].y + temp_f30 * sp24.y;
        sp30.z = temp_r30[i].z + temp_f30 * sp24.z;
        VECSubtract(&sp30, &sp3C, &spC);
        temp_f28 = VECMag(&spC);
        VECSubtract(&temp_r29[temp_r27], &temp_r29[i], &sp18);
        temp_f29 = (sp3C.x * sp18.x - sp18.x * temp_r29[i].x + sp3C.y * sp18.y - sp18.y * temp_r29[i].y + sp3C.z * sp18.z - sp18.z * temp_r29[i].z) / (sp18.x * sp18.x + sp18.y * sp18.y + sp18.z * sp18.z);
        sp30.x = temp_r29[i].x + temp_f29 * sp18.x;
        sp30.y = temp_r29[i].y + temp_f29 * sp18.y;
        sp30.z = temp_r29[i].z + temp_f29 * sp18.z;
        VECSubtract(&sp30, &sp3C, &spC);
        temp_f27 = VECMag(&spC);
        if (temp_f28 == 0.0f) {
            var_f31 = temp_f30;
        } else if (temp_f27 == 0.0f) {
            var_f31 = temp_f29;
        } else {
            temp_f26 = 1.0f - temp_f28 / (temp_f28 + temp_f27);
            var_f31 = temp_f30 * temp_f26 + temp_f29 * (1.0f - temp_f26);
        }
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        } else if (var_f31 > 1.0f) {
            var_f31 = 1.0f;
        }
        sp3C.x = temp_r29[i].x + var_f31 * sp18.x;
        sp3C.y = temp_r29[i].y + var_f31 * sp18.y;
        sp3C.z = temp_r29[i].z + var_f31 * sp18.z;
        arg1->x = temp_r28->trans.x + sp48.x + sp3C.x;
        arg1->y = temp_r28->trans.y + sp48.y + sp3C.y;
        arg1->z = temp_r28->trans.z + (sp48.z + sp3C.z) * cosd(temp_r28->rot.x);
        return 1;
    }
    var_r20 = 0;
    for (i = 0; i < temp_r21; i++) {
        temp_r27 = (i + 1) % temp_r21;
        var_f31 = (sp3C.z - temp_r30[i].z) / (temp_r30[temp_r27].z - temp_r30[i].z);
        spC.x = temp_r30[i].x + var_f31 * (temp_r30[temp_r27].x - temp_r30[i].x);
        if (var_f31 >= 0.0f && var_f31 < 1.0f && spC.x > sp3C.x) {
            var_r20++;
        }
    }
    if (var_r20 & 1) {
        arg1->x = arg0->x;
        arg1->y = arg0->y;
        arg1->z = arg0->z;
        return 1;
    }
    return 0;
}

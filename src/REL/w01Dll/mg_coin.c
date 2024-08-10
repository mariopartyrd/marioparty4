#include "REL/w01Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/frand.h"

#include "game/hsfman.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ float unk0C;
} Data690InnerStruct; // Size 0x10

typedef Data690InnerStruct Data690Block[15];

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ Vec unk04;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ char unk1E[2];
    /* 0x20 */ float unk20;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ char unk2A[2];
} Bss720Data; // Size 0x2C

typedef struct {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ Data690Block *unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ Vec unk20;
    /* 0x2C */ Vec unk2C;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ char unk42[2];
} Bss714Data; // Size 0x44

static void fn_1_A4B8(omObjData *arg0);
static void fn_1_A554(void);
static void fn_1_A5FC(void);
static void fn_1_A6E0(omObjData *arg0);
static float fn_1_B018(Data690Block *arg0);
static void fn_1_B088(omObjData *arg0);
static void fn_1_B1CC(omObjData *arg0, u16 *arg1, u16 *arg2);
static void fn_1_B3B8(omObjData *arg0);
static void fn_1_B478(omObjData *arg0);
static void fn_1_BAF8(omObjData *arg0);
static void fn_1_BCDC(omObjData *arg0);
static void fn_1_BF00(omObjData *arg0);
static void fn_1_BF68(omObjData *arg0);
static void fn_1_C000(void);
static void fn_1_C0FC(omObjData *arg0);
static void fn_1_C25C(void);
static void fn_1_C844(void);
static void fn_1_C894(omObjData *arg0);
static void fn_1_C94C(Vec *arg0, Vec *arg1, Vec *arg2);
static float fn_1_C998(Vec *arg0);
static u32 fn_1_CB44(Vec *arg0, float arg1);
static void fn_1_CEC4(void);
static void fn_1_D034(void);
static void fn_1_D07C(omObjData *arg0);
static void fn_1_D114(ModelData *model, ParticleData *particle, Mtx matrix);

static s32 lbl_1_bss_79C;
static s32 lbl_1_bss_798;
static s16 lbl_1_bss_796;
static s16 lbl_1_bss_790[3];
static s16 lbl_1_bss_78A[3];
static s16 lbl_1_bss_788;
static s16 lbl_1_bss_760[20];
static Process *lbl_1_bss_75C;
static omObjData *lbl_1_bss_758;
static float lbl_1_bss_754;
static s16 lbl_1_bss_750;
static s32 lbl_1_bss_74C;
static s32 lbl_1_bss_748;
static s16 lbl_1_bss_744;
static Vec lbl_1_bss_738;
static s32 lbl_1_bss_734;
static s32 lbl_1_bss_730;
static s32 lbl_1_bss_72C;
static u16 lbl_1_bss_72A;
static u16 lbl_1_bss_728;
static s32 lbl_1_bss_724;
static omObjData *lbl_1_bss_720;
static omObjData *lbl_1_bss_714[3];
static omObjData *lbl_1_bss_710;
static AnimData *lbl_1_bss_70C;
static s16 lbl_1_bss_708;

static Vec lbl_1_data_658[3] = {
    { -50.0f, 238.0f, 0.0f },
    {   0.0f, 275.5f, 0.0f },
    {  50.0f, 238.0f, 0.0f }
};

static u16 lbl_1_data_67C[3][3] = {
    { 10,  5, 20 },
    { 10,  5, 20 },
    {  5, 20, 10 }
};

static Data690Block lbl_1_data_690[3] = {
    {
        { { -50.0f, -12.0f, 0.0f }, 75.0f },
        { { -50.0f,  63.0f, 0.0f }, 50.0f },
        { {   0.0f,  63.0f, 0.0f }, 25.0f },
        { {   0.0f,  88.0f, 0.0f }, 50.0f },
        { {  50.0f,  88.0f, 0.0f }, 87.5f },
        { {  50.0f, 175.5f, 0.0f },  0.0f }
    },
    {
        { {   0.0f, -12.0f, 0.0f }, 75.0f },
        { {   0.0f,  63.0f, 0.0f }, 50.0f },
        { { -50.0f,  63.0f, 0.0f }, 50.0f },
        { { -50.0f, 113.0f, 0.0f }, 50.0f },
        { {   0.0f, 113.0f, 0.0f }, 50.0f },
        { {   0.0f, 163.0f, 0.0f }, 50.0f },
        { { -50.0f, 163.0f, 0.0f }, 12.5f },
        { { -50.0f, 175.5f, 0.0f },  0.0f }
    },
    {
        { {  50.0f, -12.0f, 0.0f }, 100.0f },
        { {  50.0f,  88.0f, 0.0f },  50.0f },
        { {   0.0f,  88.0f, 0.0f },  25.0f },
        { {   0.0f, 113.0f, 0.0f },  50.0f },
        { { -50.0f, 113.0f, 0.0f },  50.0f },
        { { -50.0f, 163.0f, 0.0f },  50.0f },
        { {   0.0f, 163.0f, 0.0f },  50.0f },
        { {   0.0f, 213.0f, 0.0f },   0.0f }
    }
};

static Data690Block lbl_1_data_960[3] = {
    {
        { { -50.0f, -12.0f, 0.0f }, 125.0f },
        { { -50.0f, 113.0f, 0.0f },  50.0f },
        { {   0.0f, 113.0f, 0.0f },  25.0f },
        { {   0.0f, 138.0f, 0.0f },  50.0f },
        { {  50.0f, 138.0f, 0.0f },  37.5f },
        { {  50.0f, 175.5f, 0.0f },   0.0f }
    },
    {
        { {   0.0f, -12.0f, 0.0f }, 75.0f },
        { {   0.0f,  63.0f, 0.0f }, 50.0f },
        { {  50.0f,  63.0f, 0.0f }, 75.0f },
        { {  50.0f, 138.0f, 0.0f }, 50.0f },
        { {   0.0f, 138.0f, 0.0f }, 25.0f },
        { {   0.0f, 163.0f, 0.0f }, 50.0f },
        { { -50.0f, 163.0f, 0.0f }, 12.5f },
        { { -50.0f, 175.5f, 0.0f },  0.0f }
    },
    {
        { {  50.0f, -12.0f, 0.0f }, 75.0f },
        { {  50.0f,  63.0f, 0.0f }, 50.0f },
        { {   0.0f,  63.0f, 0.0f }, 50.0f },
        { {   0.0f, 113.0f, 0.0f }, 50.0f },
        { { -50.0f, 113.0f, 0.0f }, 50.0f },
        { { -50.0f, 163.0f, 0.0f }, 50.0f },
        { {   0.0f, 163.0f, 0.0f }, 50.0f },
        { {   0.0f, 213.0f, 0.0f },  0.0f }
    }
};

static Data690Block lbl_1_data_C30[3] = {
    {
        { { -50.0f, -12.0f, 0.0f }, 100.0f },
        { { -50.0f,  88.0f, 0.0f },  50.0f },
        { {   0.0f,  88.0f, 0.0f },  50.0f },
        { {   0.0f, 138.0f, 0.0f },  50.0f },
        { { -50.0f, 138.0f, 0.0f },  37.5f },
        { { -50.0f, 175.5f, 0.0f },   0.0f }
    },
    {
        { {  0.0f, -12.0f, 0.0f },  75.0f },
        { {  0.0f,  63.0f, 0.0f },  50.0f },
        { { 50.0f,  63.0f, 0.0f }, 100.0f },
        { { 50.0f, 163.0f, 0.0f },  50.0f },
        { {  0.0f, 163.0f, 0.0f },  50.0f },
        { {  0.0f, 213.0f, 0.0f },   0.0f }
    },
    {
        { {  50.0f, -12.0f, 0.0f }, 75.0f },
        { {  50.0f,  63.0f, 0.0f }, 50.0f },
        { {   0.0f,  63.0f, 0.0f }, 25.0f },
        { {   0.0f,  88.0f, 0.0f }, 50.0f },
        { { -50.0f,  88.0f, 0.0f }, 50.0f },
        { { -50.0f, 138.0f, 0.0f }, 50.0f },
        { {   0.0f, 138.0f, 0.0f }, 25.0f },
        { {   0.0f, 163.0f, 0.0f }, 50.0f },
        { {  50.0f, 163.0f, 0.0f }, 12.5f },
        { {  50.0f, 175.5f, 0.0f },  0.0f }
    }
};

void fn_1_9D00(s32 arg0) {
    s32 temp_r31;
    s32 var_r30;

    temp_r31 = GWSystem.star_pos;
    var_r30 = 0;
    if (lbl_1_bss_0->unk00_field0 != 0) {
        if (temp_r31 == 0 || temp_r31 == 1 || temp_r31 == 7) {
            var_r30 = 0;
        } else {
            var_r30 = 1;
        }
    } else if (temp_r31 == 0 || temp_r31 == 1 || temp_r31 == 7) {
        var_r30 = 1;
    } else {
        var_r30 = 0;
    }
    if (BoardPlayerCoinsGet(arg0) < 5) {
        var_r30 = 0;
    }
    if (var_r30 != 0) {
        BoardComKeySetLeft();
    } else {
        BoardComKeySetRight();
    }
}

void fn_1_9DD8(void) {
    Vec sp2C[3];
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Bss720Data *temp_r30;
    Bss714Data *temp_r29;
    s32 i;

    lbl_1_bss_79C = GWPlayer[GWSystem.player_curr].port;
    lbl_1_bss_796 = lbl_1_bss_6C4[6];
    lbl_1_bss_790[0] = lbl_1_bss_6C4[7];
    lbl_1_bss_790[1] = lbl_1_bss_6C4[8];
    lbl_1_bss_790[2] = lbl_1_bss_6C4[9];
    lbl_1_bss_78A[0] = lbl_1_bss_6C4[10];
    lbl_1_bss_78A[1] = lbl_1_bss_6C4[11];
    lbl_1_bss_78A[2] = lbl_1_bss_6C4[12];
    BoardModelVisibilitySet(lbl_1_bss_790[0], 0);
    BoardModelVisibilitySet(lbl_1_bss_790[1], 0);
    BoardModelVisibilitySet(lbl_1_bss_790[2], 0);
    lbl_1_bss_734 = rand8() % 3;
    BoardModelVisibilitySet(lbl_1_bss_790[lbl_1_bss_734], 1);
    BoardModelMotionStart(lbl_1_bss_790[lbl_1_bss_734], 0, 0x40000001);
    BoardModelPosGet(lbl_1_bss_796, &sp20);
    sp8.x = sp8.y = sp8.z = 1.0f;
    for (i = 0; i < 3; i++) {
        sp2C[i] = lbl_1_data_690[i][0].unk00;
        sp2C[i].y -= -12.0f;
        BoardModelPosSet(lbl_1_bss_78A[i], sp20.x + sp2C[i].x, sp20.y + sp2C[i].y, sp20.z + 30.0f);
        BoardModelVisibilitySet(lbl_1_bss_78A[i], 1);
        BoardModelScaleSetV(lbl_1_bss_78A[i], &sp8);
    }
    lbl_1_bss_798 = GWSystem.player_curr;
    BoardModelPosGet(lbl_1_bss_796, &lbl_1_bss_738);
    lbl_1_bss_730 = 1;
    BoardModelPosGet(lbl_1_bss_78A[lbl_1_bss_730], &sp14);
    BoardPlayerPosGet(lbl_1_bss_798, &sp20);
    lbl_1_bss_758 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_A4B8);
    lbl_1_bss_720 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_B3B8);
    lbl_1_bss_720->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Bss720Data), MEMORY_DEFAULT_NUM);
    temp_r30 = lbl_1_bss_720->data;
    temp_r30->unk02 = 0;
    temp_r30->unk04 = sp14;
    temp_r30->unk28 = 0;
    fn_1_CB44(&sp14, 0.0f);
    fn_1_B088(lbl_1_bss_720);
    lbl_1_bss_750 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_W01, 19));
    Hu3DModelAttrSet(lbl_1_bss_750, 1);
    for (i = 0; i < 3; i++) {
        lbl_1_bss_714[i] = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_A6E0);
        lbl_1_bss_714[i]->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Bss714Data), MEMORY_DEFAULT_NUM);
        lbl_1_bss_714[i]->work[0] = lbl_1_bss_78A[i];
        lbl_1_bss_714[i]->work[1] = 0;
        lbl_1_bss_714[i]->work[3] = 0;
        temp_r29 = lbl_1_bss_714[i]->data;
        if (i == lbl_1_bss_730) {
            lbl_1_bss_714[i]->work[2] = 1;
        } else {
            lbl_1_bss_714[i]->work[2] = 0;
        }
        temp_r29->unk18 = 1.0f;
        temp_r29->unk1C = 0.0f;
    }
    lbl_1_bss_72C = 0;
    lbl_1_bss_74C = 5;
    lbl_1_bss_748 = 0x3C;
    lbl_1_bss_72A = 0;
    fn_1_CEC4();
    lbl_1_bss_788 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 17), NULL, 0);
    BoardModelMotionUpdateSet(lbl_1_bss_788, 1);
    BoardModelVisibilitySet(lbl_1_bss_788, 0);
    for (i = 0; i < 20; i++) {
        lbl_1_bss_760[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 1);
        BoardModelVisibilitySet(lbl_1_bss_760[i], 0);
    }
}

static void fn_1_A4B8(omObjData *arg0) {
    if (lbl_1_bss_72A == 0) {
        return;
    }
    if (BoardMGDoneFlagGet() == 1) {
        if (lbl_1_bss_754 <= 0.0f) {
            fn_1_A5FC();
            omDelObjEx(HuPrcCurrentGet(), arg0);
        }
    }
    lbl_1_bss_754 -= 1.0f;
}

static void fn_1_A554(void) {
    float temp_f1;

    lbl_1_bss_72A = 1;
    BoardMGExit();
    temp_f1 = BoardModelMotionTimeGet(lbl_1_bss_796);
    lbl_1_bss_754 = temp_f1;
    BoardModelMotionStart(lbl_1_bss_796, 0, 0);
    BoardModelMotionTimeSet(lbl_1_bss_796, temp_f1);
    BoardModelMotionSpeedSet(lbl_1_bss_796, -1.0f);
}

static void fn_1_A5FC(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        BoardModelVisibilitySet(lbl_1_bss_790[i], 0);
        BoardModelVisibilitySet(lbl_1_bss_78A[i], 0);
        omDelObjEx(HuPrcCurrentGet(), lbl_1_bss_714[i]);
    }
    for (i = 0; i < 20; i++) {
        BoardModelKill(lbl_1_bss_760[i]);
    }
    fn_1_D034();
    BoardModelKill(lbl_1_bss_788);
    BoardMGDoneFlagSet(0);
    Hu3DModelKill(lbl_1_bss_750);
}

static void fn_1_A6E0(omObjData *arg0) {
    Bss714Data *temp_r31;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;

    temp_r31 = arg0->data;
    BoardModelScaleGet(arg0->work[0], &sp2C);
    switch (arg0->work[2]) {
        case 1:
            if ((sp2C.x += 0.08f) >= 1.5f) {
                sp2C.x = 1.5f;
                sp2C.y = 1.5f;
                if (arg0->work[3] == 1) {
                    arg0->work[2] = 0;
                } else {
                    arg0->work[2] = 2;
                }
            } else {
                sp2C.y += 0.08f;
            }
            BoardModelScaleSetV(arg0->work[0], &sp2C);
            break;
        case 2:
            if ((sp2C.x -= 0.08f) <= 1.0f) {
                sp2C.x = 1.0f;
                sp2C.y = 1.0f;
                if (arg0->work[1] == 1) {
                    arg0->work[2] = 0;
                    arg0->work[1] = 0;
                } else {
                    arg0->work[2] = 1;
                }
            } else {
                sp2C.y -= 0.08f;
            }
            BoardModelScaleSetV(arg0->work[0], &sp2C);
            break;
        case 3:
            switch (lbl_1_bss_734) {
                case 0:
                    temp_r31->unk04 = &lbl_1_data_690[lbl_1_bss_730];
                    break;
                case 1:
                    temp_r31->unk04 = &lbl_1_data_960[lbl_1_bss_730];
                    break;
                case 2:
                    temp_r31->unk04 = &lbl_1_data_C30[lbl_1_bss_730];
                    break;
            }
            BoardModelPosGet(arg0->work[0], &sp14);
            sp14.x = lbl_1_bss_738.x + ((*temp_r31->unk04)[0].unk00.x + temp_r31->unk18);
            temp_r31->unk18 = -temp_r31->unk18;
            BoardModelPosSetV(arg0->work[0], &sp14);
            sp14.y += 5.0f;
            BoardPlayerPosSetV(lbl_1_bss_798, &sp14);
            temp_r31->unk1C += 0.022222223f;
            temp_r31->unk38 -= 0.011111111f;
            if (temp_r31->unk38 < 0.0f) {
                temp_r31->unk38 = 0.0f;
            }
            Hu3DModelTPLvlSet(lbl_1_bss_750, temp_r31->unk38);
            if (temp_r31->unk1C > 1.0f) {
                temp_r31->unk1C = 1.0f;
            }
            PSVECAdd(&temp_r31->unk20, &temp_r31->unk2C, &temp_r31->unk20);
            if (temp_r31->unk20.y >= 4.0f) {
                temp_r31->unk20.y = 4.0f;
                temp_r31->unk2C.y = -0.1f;
            }
            if (temp_r31->unk20.y < 1.0f) {
                temp_r31->unk20.y = 1.0f;
            }
            Hu3DModelScaleSet(lbl_1_bss_750, temp_r31->unk20.x, temp_r31->unk20.y, temp_r31->unk20.z);
            break;
        case 4:
            Hu3DModelAttrSet(lbl_1_bss_750, 1);
            arg0->work[2] = 5;
            temp_r31->unk08 = 0;
            temp_r31->unk0C = 12.0f;
            temp_r31->unk14 = (fn_1_B018(temp_r31->unk04) - temp_r31->unk0C) / 90.0f;
            temp_r31->unk10 = temp_r31->unk14 / 20.0f;
            HuAudFXPlay(0x406);
            HuAudFXPlay(0x407);
            HuAudFXStop(lbl_1_bss_724);
            break;
        case 5:
            var_f31 = temp_r31->unk0C + temp_r31->unk10;
            temp_r31->unk0C = var_f31;
            temp_r31->unk10 *= 1.04f;
            if (temp_r31->unk10 > temp_r31->unk14) {
                temp_r31->unk10 = temp_r31->unk14;
            }
            BoardModelPosGet(arg0->work[0], &sp20);
            while (var_f31 >= (*temp_r31->unk04)[temp_r31->unk08].unk0C) {
                var_f31 -= (*temp_r31->unk04)[temp_r31->unk08].unk0C;
                temp_r31->unk08++;
                if ((*temp_r31->unk04)[temp_r31->unk08].unk0C == 0.0f) {
                    omVibrate(lbl_1_bss_798, 12, 6, 6);
                    var_f31 = 0.0f;
                    lbl_1_bss_72C = 1;
                    lbl_1_bss_724 = HuAudFXPlay(0x332);
                    lbl_1_bss_708 = 0;
                    arg0->work[2] = 6;
                    if (sp20.x - lbl_1_bss_738.x < -25.0f) {
                        temp_r31->unk40 = 0;
                        lbl_1_bss_728 = 5;
                    } else if (sp20.x - lbl_1_bss_738.x > 25.0f) {
                        temp_r31->unk40 = 2;
                        lbl_1_bss_728 = 10;
                    } else {
                        temp_r31->unk40 = 1;
                        lbl_1_bss_728 = 20;
                    }
                    break;
                }
            }
            temp_r31->unk0C = var_f31;
            sp14.x = sp14.y = sp14.z = 0.0f;
            if (lbl_1_bss_72C == 0) {
                fn_1_C94C(&(*temp_r31->unk04)[temp_r31->unk08].unk00, &(*temp_r31->unk04)[temp_r31->unk08 + 1].unk00, &sp8);
                sp20.x = lbl_1_bss_738.x + (sp8.x * var_f31 + (*temp_r31->unk04)[temp_r31->unk08].unk00.x);
                sp20.y = lbl_1_bss_738.y + (sp8.y * var_f31 + (*temp_r31->unk04)[temp_r31->unk08].unk00.y);
            } else {
                sp20.x = lbl_1_bss_738.x + (*temp_r31->unk04)[temp_r31->unk08].unk00.x;
                sp20.y = lbl_1_bss_738.y + (*temp_r31->unk04)[temp_r31->unk08].unk00.y;
            }
            BoardModelPosSetV(arg0->work[0], &sp20);
            sp20.y += 5.0f;
            BoardPlayerPosSetV(lbl_1_bss_798, &sp20);
            BoardModelRotSetV(arg0->work[0], &sp14);
            BoardPlayerRotSetV(lbl_1_bss_798, &sp14);
            break;
        case 6:
            if (lbl_1_bss_708 == 0 && (HuAudFXStatusGet(lbl_1_bss_724) == 1 || HuAudFXStatusGet(lbl_1_bss_724) == 0)) {
                BoardAudSeqPause(0, 0, 1000);
                lbl_1_bss_708 = 1;
            }
            BoardModelVisibilitySet(lbl_1_bss_788, 1);
            sp20.x = lbl_1_bss_738.x + lbl_1_data_658[temp_r31->unk40].x;
            sp20.y = lbl_1_bss_738.y + lbl_1_data_658[temp_r31->unk40].y;
            sp20.z = lbl_1_bss_738.z + lbl_1_data_658[temp_r31->unk40].z;
            BoardModelPosSetV(lbl_1_bss_788, &sp20);
            temp_r31->unk1C -= 0.05f;
            if (temp_r31->unk1C <= 0.0f) {
                temp_r31->unk1C = 0.0f;
            }
            break;
    }
}

static float fn_1_B018(Data690Block *arg0) {
    float var_f31;
    s32 i;

    var_f31 = 0.0f;
    i = 0;
    while (TRUE) {
        if ((*arg0)[i].unk0C == 0.0f) {
            break;
        }
        var_f31 += (*arg0)[i].unk0C;
        i++;
    }
    return var_f31;
}

static void fn_1_B088(omObjData *arg0) {
    Bss720Data *temp_r31;
    u16 sp8[] = { 20, 60, 120, 190 };
    s32 i;

    temp_r31 = arg0->data;
    if (rand8() < sp8[GWPlayerCfg[lbl_1_bss_798].diff]) {
        for (i = 0; i < 3; i++) {
            if (lbl_1_data_67C[lbl_1_bss_734][i] == 20) {
                temp_r31->unk26 = i;
            }
        }
    } else {
        temp_r31->unk26 = rand8() % 3;
    }
    temp_r31->unk24 = rand8() % 20 + 20;
}

static void fn_1_B1CC(omObjData *arg0, u16 *arg1, u16 *arg2) {
    Bss720Data *temp_r31;

    temp_r31 = arg0->data;
    *arg1 = *arg2 = 0;
    if (temp_r31->unk24 != 0) {
        temp_r31->unk24--;
        return;
    }
    if (temp_r31->unk28 >= 4 || (rand8() & 1)) {
        if (temp_r31->unk26 == lbl_1_bss_730) {
            *arg2 |= 0x100;
        } else if (temp_r31->unk26 < lbl_1_bss_730) {
            *arg1 |= 1;
        } else {
            *arg1 |= 2;
        }
        temp_r31->unk24 = rand8() % 10 + 10;
    } else {
        temp_r31->unk28++;
        temp_r31->unk24 = rand8() % 10 + 20;
        if (lbl_1_bss_730 == 0) {
            *arg1 |= 2;
        } else if (lbl_1_bss_730 == 2) {
            *arg1 |= 1;
        } else if (rand8() & 1) {
            *arg1 |= 1;
        } else {
            *arg1 |= 2;
        }
    }
}

static void fn_1_B3B8(omObjData *arg0) {
    float temp_f31;

    temp_f31 = BoardModelMotionMaxTimeGet(lbl_1_bss_796);
    if (BoardModelMotionTimeGet(lbl_1_bss_796) >= temp_f31) {
        lbl_1_bss_744 = MGSeqCreate(1, lbl_1_bss_74C, 0x120, 0x40);
        lbl_1_bss_720->func = fn_1_B478;
        BoardMusStart(1, 0xF, 0x7F, 0);
        lbl_1_bss_724 = HuAudFXPlay(0x408);
    }
}

static void fn_1_B478(omObjData *arg0) {
    Bss720Data *temp_r31;
    Vec sp18;
    Vec spC;
    float var_f28;
    u16 var_r27;
    u16 var_r29;

    temp_r31 = arg0->data;
    if ((lbl_1_bss_748 -= 1) == 0) {
        if ((lbl_1_bss_74C -= 1) >= 0) {
            MGSeqParamSet(lbl_1_bss_744, 1, lbl_1_bss_74C);
        }
        lbl_1_bss_748 = 60;
    }
    if (GWPlayerCfg[lbl_1_bss_798].iscom == 1) {
        fn_1_B1CC(arg0, &var_r29, &var_r27);
    } else {
        var_r29 = HuPadDStkRep[lbl_1_bss_79C];
        var_r27 = HuPadBtnDown[lbl_1_bss_79C];
    }
    if ((var_r29 & 1) && lbl_1_bss_730 != 0) {
        lbl_1_bss_714[lbl_1_bss_730]->work[1] = 1;
        lbl_1_bss_714[lbl_1_bss_730]->work[2] = 2;
        lbl_1_bss_730--;
        lbl_1_bss_714[lbl_1_bss_730]->work[2] = 1;
    }
    if ((var_r29 & 2) && lbl_1_bss_730 != 2) {
        lbl_1_bss_714[lbl_1_bss_730]->work[1] = 1;
        lbl_1_bss_714[lbl_1_bss_730]->work[2] = 2;
        lbl_1_bss_730++;
        lbl_1_bss_714[lbl_1_bss_730]->work[2] = 1;
    }
    BoardModelPosGet(lbl_1_bss_78A[lbl_1_bss_730], &sp18);
    BoardPlayerPosGet(lbl_1_bss_798, &spC);
    fn_1_CB44(&sp18, 0.0f);
    temp_r31->unk04 = sp18;
    if (lbl_1_bss_74C < 0 || (var_r27 & 0x100)) {
        MGSeqParamSet(lbl_1_bss_744, 2, -1);
        lbl_1_bss_714[lbl_1_bss_730]->work[1] = 1;
        BoardPlayerPosGet(lbl_1_bss_798, &spC);
        var_f28 = VECDistanceXZ(&temp_r31->unk04, &spC);
        fn_1_C94C(&spC, &temp_r31->unk04, &temp_r31->unk10);
        temp_r31->unk10.y = 0.0f;
        temp_r31->unk10.x *= var_f28 / 30.0f;
        temp_r31->unk10.z *= var_f28 / 30.0f;
        temp_r31->unk00 = 0;
        temp_r31->unk20 = 0.0f;
        arg0->func = fn_1_BAF8;
    }
}

static void fn_1_BAF8(omObjData *arg0) {
    Bss720Data *temp_r31;
    Vec sp14;
    Vec sp8;

    temp_r31 = arg0->data;
    if (lbl_1_bss_714[lbl_1_bss_730]->work[2] != 0) {
        return;
    }
    BoardPlayerMotionStart(lbl_1_bss_798, 4, 0);
    BoardPlayerPosGet(lbl_1_bss_798, &sp14);
    sp14.x += temp_r31->unk10.x;
    sp14.z += temp_r31->unk10.z;
    sp14.y = lbl_1_bss_738.y + 80.0 * sind(6.0f * temp_r31->unk20);
    BoardModelPosGet(lbl_1_bss_714[lbl_1_bss_730]->work[0], &sp8);
    if ((temp_r31->unk20 += 1.0f) == 30.0f) {
        sp14.y = sp8.y + 5.0f;
        BoardPlayerPosSetV(lbl_1_bss_798, &sp14);
        BoardPlayerMotionShiftSet(lbl_1_bss_798, 2, 0.0f, 10.0f, 0);
        arg0->func = fn_1_BCDC;
    }
    BoardPlayerPosSetV(lbl_1_bss_798, &sp14);
}

static void fn_1_BCDC(omObjData *arg0) {
    Bss720Data *temp_r29;
    Bss714Data *temp_r31;
    Vec sp14;
    Vec sp8;

    temp_r29 = arg0->data;
    BoardPlayerPosGet(lbl_1_bss_798, &sp14);
    sp8 = sp14;
    sp8.z += 100.0f;
    if (fn_1_CB44(&sp8, 10.0f) == 1) {
        BoardPlayerMotionShiftSet(lbl_1_bss_798, 1, 0.0f, 10.0f, 0);
        temp_r29->unk1C = 90;
        lbl_1_bss_710->work[0] = 1;
        lbl_1_bss_714[lbl_1_bss_730]->work[2] = 3;
        temp_r31 = lbl_1_bss_714[lbl_1_bss_730]->data;
        Hu3DModelAttrReset(lbl_1_bss_750, 1);
        Hu3DModelPosSet(lbl_1_bss_750, sp14.x, sp14.y, sp14.z);
        temp_r31->unk20.x = 1.4f;
        temp_r31->unk20.y = 1.4f;
        temp_r31->unk20.z = 1.4f;
        temp_r31->unk2C.x = 0.055999998f;
        temp_r31->unk2C.y = 0.08088889f;
        temp_r31->unk2C.z = 0.055999998f;
        temp_r31->unk38 = 1.0f;
        temp_r31->unk3C = 0.0f;
        Hu3DModelScaleSet(lbl_1_bss_750, 1.4f, 1.4f, 1.4f);
        arg0->func = fn_1_BF00;
    }
}

static void fn_1_BF00(omObjData *arg0) {
    Bss720Data *temp_r31;

    temp_r31 = arg0->data;
    if (temp_r31->unk1C == 0) {
        lbl_1_bss_714[lbl_1_bss_730]->work[2] = 4;
        arg0->func = fn_1_BF68;
    } else {
        temp_r31->unk1C--;
    }
}

static void fn_1_BF68(omObjData *arg0) {
    Bss720Data *sp8;

    sp8 = arg0->data;
    if (lbl_1_bss_714[lbl_1_bss_730]->work[2] == 6) {
        lbl_1_bss_75C = HuPrcCreate(fn_1_C000, 0x2004, 0x1000, 0);
        lbl_1_bss_75C->user_data = arg0;
        arg0->func = NULL;
    }
}

static void fn_1_C000(void) {
    char sp8[16]; // array size may range between 1 and 16 (inclusive)
    omObjData *temp_r30;
    Bss720Data *temp_r31;

    BoardAudSeqFadeOut(1, 100);
    sprintf(&sp8, "%d", lbl_1_bss_728);
    BoardWinCreate(2, MAKE_MESSID(11, 6), 0);
    BoardWinInsertMesSet(MAKE_MESSID_PTR(sp8), 0);
    BoardWinWait();
    BoardWinKill();
    temp_r30 = HuPrcCurrentGet()->user_data;
    temp_r31 = temp_r30->data;
    temp_r31->unk10.x = 0.0f;
    temp_r31->unk10.y = 10.0f;
    temp_r31->unk10.z = 3.0f;
    temp_r31->unk20 = 0.0f;
    BoardPlayerMotionShiftSet(lbl_1_bss_798, 4, 0.0f, 10.0f, 0);
    temp_r30->func = fn_1_C0FC;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void fn_1_C0FC(omObjData *arg0) {
    Bss720Data *temp_r31;
    Vec sp8;

    temp_r31 = arg0->data;
    BoardPlayerPosGet(lbl_1_bss_798, &sp8);
    sp8.x += temp_r31->unk10.x;
    sp8.y += temp_r31->unk10.y - 0.029166667f * temp_r31->unk20 * temp_r31->unk20;
    sp8.z += temp_r31->unk10.z;
    temp_r31->unk20 += 1.0f;
    if (sp8.y <= lbl_1_bss_738.y) {
        BoardPlayerMotionShiftSet(lbl_1_bss_798, 1, 0.0f, 10.0f, 0x40000001);
        sp8.y = lbl_1_bss_738.y;
        lbl_1_bss_75C = HuPrcCreate(fn_1_C25C, 0x2004, 0x1000, 0);
        lbl_1_bss_75C->user_data = arg0;
        arg0->func = NULL;
    }
    BoardPlayerPosSetV(lbl_1_bss_798, &sp8);
}

static void fn_1_C25C(void) {
    Vec sp11C[20];
    Vec sp2C[20];
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    s16 var_r30;
    s16 i;

    var_r30 = 0;
    BoardPlayerPosGet(lbl_1_bss_798, &sp20);
    sp14.x = sp14.y = sp14.z = 1.0f;
    for (i = 0; i < lbl_1_bss_728; i++) {
        BoardModelVisibilitySet(lbl_1_bss_760[i], 1);
        sp11C[i] = sp20;
        sp11C[i].y += 600.0f + i * 120;
        sp11C[i].x += -25.0f + 50.0f * frand8() * 0.003921569f;
        sp11C[i].z += -25.0f + 50.0f * frand8() * 0.003921569f;
        sp2C[i].x = sp2C[i].z = 0.0f;
        sp2C[i].y = 360.0f * frand8() * 0.003921569f;
        BoardModelPosSetV(lbl_1_bss_760[i], &sp11C[i]);
        BoardModelScaleSetV(lbl_1_bss_760[i], &sp14);
        BoardModelRotSetV(lbl_1_bss_760[i], &sp2C[i]);
    }
    var_f31 = -1.0f;
    while (TRUE) {
        for (i = 0; i < lbl_1_bss_728; i++) {
            if (i >= var_r30) {
                sp11C[i].y += var_f31;
                BoardModelPosSetV(lbl_1_bss_760[i], &sp11C[i]);
                sp2C[i].y += 45.0f;
                if (sp2C[i].y >= 360.0f) {
                    sp2C[i].y -= 360.0f;
                }
                BoardModelRotSetV(lbl_1_bss_760[i], &sp2C[i]);
                if (sp11C[i].y <= sp20.y + 80.0f) {
                    sp8 = sp11C[i];
                    CharModelCoinEffectCreate(1, &sp8);
                    BoardModelVisibilitySet(lbl_1_bss_760[i], 0);
                    var_r30++;
                    BoardPlayerCoinsAdd(lbl_1_bss_798, 1);
                    HuAudFXPlay(7);
                    omVibrate(lbl_1_bss_798, 0xC, 6, 6);
                }
            }
        }
        var_f31 *= 1.05f;
        if (var_f31 < -20.0f) {
            var_f31 = -20.0f;
        }
        if (var_r30 == lbl_1_bss_728) {
            BoardPlayerMotionShiftSet(lbl_1_bss_798, 7, 0.0f, 10.0f, 0);
            break;
        }
        HuPrcVSleep();
    }
    while (!BoardPlayerMotionEndCheck(lbl_1_bss_798)) {
        HuPrcVSleep();
    }
    lbl_1_bss_75C = HuPrcCreate(fn_1_C844, 0x2004, 0x1000, 0);
    lbl_1_bss_75C->user_data = HuPrcCurrentGet()->user_data;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void fn_1_C844(void) {
    omObjData *var_r31;

    BoardWinCreate(2, MAKE_MESSID(11, 7), 0);
    BoardWinWait();
    BoardWinKill();
    var_r31 = HuPrcCurrentGet()->user_data;
    var_r31->func = fn_1_C894;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void fn_1_C894(omObjData *arg0) {
    float temp_f31;

    lbl_1_bss_72A = 1;
    BoardMGExit();
    temp_f31 = BoardModelMotionTimeGet(lbl_1_bss_796);
    lbl_1_bss_754 = temp_f31;
    BoardModelMotionStart(lbl_1_bss_796, 0, 0);
    BoardModelMotionTimeSet(lbl_1_bss_796, temp_f31);
    BoardModelMotionSpeedSet(lbl_1_bss_796, -1.0f);
    omDelObjEx(HuPrcCurrentGet(), arg0);
}

static void fn_1_C94C(Vec *arg0, Vec *arg1, Vec *arg2) {
    PSVECSubtract(arg1, arg0, arg2);
    PSVECNormalize(arg2, arg2);
}

static float fn_1_C998(Vec *arg0) {
    float temp_f31;

    if (arg0->x || arg0->z) {
        if (arg0->x == 0.0f) {
            if (arg0->z > 0.0f) {
                return 0.0f;
            } else {
                return 180.0f;
            }
        }
        if (arg0->z == 0.0f) {
            if (arg0->x > 0.0f) {
                return 90.0f;
            } else {
                return 270.0f;
            }
        }
        temp_f31 = atan2d(arg0->z, arg0->x);
        if (arg0->z < 0.0f) {
            temp_f31 = 90.0f - temp_f31;
        } else {
            temp_f31 = 90.0f - temp_f31;
            if (temp_f31 < 0.0f) {
                temp_f31 += 360.0f;
            }
        }
        return temp_f31;
    }
    return -1.0f;
}

static u32 fn_1_CB44(Vec *arg0, float arg1) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f28;
    float var_f30;
    float var_f31;

    BoardPlayerPosGet(lbl_1_bss_798, &sp18);
    PSVECSubtract(arg0, &sp18, &sp24);
    PSVECNormalize(&sp24, &sp24);
    var_f28 = fn_1_C998(&sp24);
    BoardPlayerRotGet(lbl_1_bss_798, &spC);
    var_f31 = spC.y;
    var_f30 = var_f28 - var_f31;
    if (arg1 == 0.0f) {
        var_f31 = var_f28;
    } else if (fabs(var_f30) > arg1) {
        if (var_f30 < 0.0f) {
            var_f30 += 360.0f;
        }
        if (var_f30 < 180.0f) {
            if (var_f30 > arg1) {
                var_f31 += arg1;
            } else {
                var_f31 += var_f30;
            }
        } else if (360.0f - var_f30 > arg1) {
            var_f31 -= arg1;
        } else {
            var_f31 -= 360.0f - var_f30;
        }
    } else {
        var_f31 = var_f28;
    }
    if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    BoardPlayerRotYSet(lbl_1_bss_798, var_f31);
    if (var_f31 == var_f28) {
        return 1;
    } else {
        return 0;
    }
}

static void fn_1_CEC4(void) {
    lbl_1_bss_70C = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_W01, 20));
    lbl_1_bss_710 = omAddObjEx(boardObjMan, 0x101, 1, 0, -1, fn_1_D07C);
    lbl_1_bss_710->data = HuMemDirectMallocNum(HEAP_SYSTEM, 12, MEMORY_DEFAULT_NUM);
    lbl_1_bss_710->model[0] = Hu3DParticleCreate(lbl_1_bss_70C, 0x320);
    Hu3DParticleColSet(lbl_1_bss_710->model[0], 0xFF, 0, 0);
    Hu3DParticleScaleSet(lbl_1_bss_710->model[0], 5.0f);
    Hu3DParticleHookSet(lbl_1_bss_710->model[0], fn_1_D114);
    Hu3DParticleBlendModeSet(lbl_1_bss_710->model[0], 1);
    Hu3DModelAttrSet(lbl_1_bss_710->model[0], 1);
    lbl_1_bss_710->work[0] = 0;
}

static void fn_1_D034(void) {
    Hu3DModelKill(lbl_1_bss_710->model[0]);
    omDelObjEx(HuPrcCurrentGet(), lbl_1_bss_710);
}

static void fn_1_D07C(omObjData *arg0) {
    void *sp8;

    sp8 = arg0->data;
    switch (arg0->work[0]) {
        case 0:
            break;
        case 1:
            arg0->work[0] = 2;
            Hu3DModelAttrReset(arg0->model[0], 1);
            Hu3DModelScaleSet(arg0->model[0], 10.0f, 10.0f, 10.0f);
            break;
        case 2:
            break;
    }
}

static void fn_1_D114(ModelData *model, ParticleData *particle, Mtx matrix) {
    Bss714Data *temp_r28;
    HsfanimStruct01 *var_r31;
    Vec sp8;
    float temp_f31;
    s32 i;
    s32 j;
    s32 temp_r26;

    BoardModelPosGet(lbl_1_bss_714[lbl_1_bss_730]->work[0], &sp8);
    temp_r28 = lbl_1_bss_714[lbl_1_bss_730]->data;
    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk2C = 0.0f;
        }
        particle->unk_1C = (void*) 1;
    }
    if (temp_r28->unk1C > 0.0f) {
        for (i = 0; i < 80.0f * temp_r28->unk1C; i++) {
            var_r31 = particle->unk_48;
            for (j = 0; j < particle->unk_30; j++, var_r31++) {
                if (var_r31->unk2C == 0.0f) {
                    break;
                }
            }
            if (j != particle->unk_30) {
                temp_r26 = frand16();
                temp_f31 = (-15.0f + 30.0f * (temp_r26 / 65536.0f)) * temp_r28->unk1C;
                var_r31->unk08.x = sp8.x + temp_f31;
                var_r31->unk08.y = sp8.y;
                var_r31->unk08.z = sp8.z;
                var_r31->unk14.x = 255.0f;
                var_r31->unk14.y = 155.0f;
                var_r31->unk14.z = 55.0f;
                var_r31->unk40.a = 0xFF;
                var_r31->unk20 = 0.0f;
                var_r31->unk24 = temp_r28->unk1C * (-3.0 + (2.0 * (fabs(temp_f31) / 15.0)));
                var_r31->unk28 = 0.0f;
                var_r31->unk2C = 7.3f;
            }
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (var_r31->unk2C == 0.0f) {
            continue;
        }
        var_r31->unk34.x = var_r31->unk08.x;
        var_r31->unk34.y = var_r31->unk08.y;
        var_r31->unk34.z = var_r31->unk08.z;
        var_r31->unk08.x += var_r31->unk20;
        var_r31->unk08.y += var_r31->unk24;
        var_r31->unk08.z += var_r31->unk28;
        if (var_r31->unk08.y <= lbl_1_bss_738.y) {
            var_r31->unk08.y = lbl_1_bss_738.y;
            var_r31->unk24 = -var_r31->unk24 - 0.3f;
            if (var_r31->unk24 < 0.0f) {
                var_r31->unk24 = 0.0f;
            }
            temp_r26 = 80.0f * (2.0f * ((sp8.x - var_r31->unk08.x) / 15.0f) - rand8() / 255.0f);
            var_r31->unk20 = 8.0 * sind(temp_r26);
            var_r31->unk28 = 8.0 * cosd(temp_r26);
        }
        var_r31->unk24 -= 0.35f;
        if ((var_r31->unk14.x -= 25.5f) < 0.0f) {
            var_r31->unk14.x = 0.0f;
        }
        if ((var_r31->unk14.y -= 36.42857f) < 0.0f) {
            var_r31->unk14.y = 0.0f;
        }
        if ((var_r31->unk14.z -= 63.75f) < 0.0f) {
            var_r31->unk14.z = 0.0f;
        }
        var_r31->unk40.r = var_r31->unk14.x;
        var_r31->unk40.g = var_r31->unk14.y;
        var_r31->unk40.b = var_r31->unk14.z;
        if (var_r31->unk40.r == 0 && var_r31->unk40.g == 0 && var_r31->unk40.b == 0) {
            var_r31->unk2C = 0.0f;
        }
    }
}

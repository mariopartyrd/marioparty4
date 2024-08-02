#include "REL/w04Dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/board/audio.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"
#include "game/board/window.h"
#include "game/frand.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    /* 0x00 */ char unk00[0x50];
    /* 0x50 */ u32 unk50; // pointer?
    /* 0x54 */ s32 unk54;
} UnkParticleDataStruct; // Size unknown

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ Vec unk20;
    /* 0x2C */ Process *unk2C;
} BssE4Data; // Size 0x30

static void fn_1_20EC(void);
static void fn_1_28BC(void);
static void fn_1_2B8C(void);
static void fn_1_2C10(void);
static void fn_1_2E60(s16 arg0);
static void fn_1_2EE8(s32 arg0);
static s32 fn_1_2F54(u32 arg0);
static BssE4Data *fn_1_2FBC(s16 arg0);
static void fn_1_2FDC(void);
static void fn_1_30A4(void);
static void fn_1_38D8(void);
static s32 fn_1_3C9C(void);
static void fn_1_45A8(void);
static void fn_1_4630(void);
static s32 fn_1_4680(s16 arg0);
static void fn_1_4848(void);
static void fn_1_5018(void);
static void fn_1_52A0(s16 arg0, Vec *arg1);
static void fn_1_55A0(void);
static void fn_1_5648(void);
static void fn_1_5828(void);
static s16 fn_1_58A4(Vec *arg0);
static void fn_1_5980(s16 arg0);
static void fn_1_59C4(omObjData *arg0);
static void fn_1_5A2C(ModelData *model, ParticleData *particle, Mtx matrix);

static s16 lbl_1_bss_FA;
static s16 lbl_1_bss_F4[3];
static Process *lbl_1_bss_E4[4];
static Process *lbl_1_bss_D4[4];
static omObjData *lbl_1_bss_C4[4];
static s16 lbl_1_bss_C2;
static s16 lbl_1_bss_BA[4];
static s16 lbl_1_bss_B2[4];
static s16 lbl_1_bss_B0;
static Vec lbl_1_bss_80[4];
static s16 lbl_1_bss_7C;
static s32 lbl_1_bss_78;
static s32 lbl_1_bss_74;
static s16 lbl_1_bss_70;
static s32 lbl_1_bss_6C;
static s16 lbl_1_bss_6A;
static s16 lbl_1_bss_52[4][3];
static s16 lbl_1_bss_50;
static AnimData *lbl_1_bss_4C;
static Process *lbl_1_bss_48;

static s32 lbl_1_data_2D0[8] = {
    DATADIR_MARIOMOT,
    DATADIR_LUIGIMOT,
    DATADIR_PEACHMOT,
    DATADIR_YOSHIMOT,
    DATADIR_WARIOMOT,
    DATADIR_DONKEYMOT,
    DATADIR_DAISYMOT,
    DATADIR_WALUIGIMOT
};

static s32 lbl_1_data_2F0 = 28;

static s32 lbl_1_data_2F4[8] = {
    DATA_MAKE_NUM(DATADIR_W04, 35),
    DATA_MAKE_NUM(DATADIR_W04, 36),
    DATA_MAKE_NUM(DATADIR_W04, 37),
    DATA_MAKE_NUM(DATADIR_W04, 38),
    DATA_MAKE_NUM(DATADIR_W04, 39),
    DATA_MAKE_NUM(DATADIR_W04, 40),
    DATA_MAKE_NUM(DATADIR_W04, 41),
    DATA_MAKE_NUM(DATADIR_W04, 42)
};

static s32 lbl_1_data_314[8] = {
    DATA_MAKE_NUM(DATADIR_W04, 43),
    DATA_MAKE_NUM(DATADIR_W04, 44),
    DATA_MAKE_NUM(DATADIR_W04, 45),
    DATA_MAKE_NUM(DATADIR_W04, 46),
    DATA_MAKE_NUM(DATADIR_W04, 47),
    DATA_MAKE_NUM(DATADIR_W04, 48),
    DATA_MAKE_NUM(DATADIR_W04, 49),
    DATA_MAKE_NUM(DATADIR_W04, 50)
};

static char *lbl_1_data_348[] = {
    "kan1", "kan2", "kan3", "kan4"
};

static float lbl_1_data_358[] = {
    -150.00001f, -170.00001f, -30.0f, -220.0f
};

static void fn_1_20EC(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    s32 temp_r30;
    s32 temp_r28;
    BoardSpace *var_r27;
    BoardMapObject *var_r26;
    s32 i;
    s32 j;

    temp_r30 = GWSystem.player_curr;
    lbl_1_bss_70 = 0;
    lbl_1_bss_7C = 0;
    temp_r28 = lbl_1_data_2D0[GWPlayer[temp_r30].character];
    lbl_1_bss_52[temp_r30][0] = BoardPlayerMotionCreate(temp_r30, temp_r28 | lbl_1_data_2F0);
    lbl_1_bss_52[temp_r30][1] = BoardPlayerMotionCreate(temp_r30, lbl_1_data_2F4[GWPlayer[temp_r30].character]);
    for (i = 0; i < 4; i++) {
        if (i != temp_r30) {
            lbl_1_bss_52[i][0] = BoardPlayerMotionCreate(i, temp_r28 | lbl_1_data_2F0);
            lbl_1_bss_52[i][1] = BoardPlayerMotionCreate(i, lbl_1_data_2F4[GWPlayer[i].character]);
            lbl_1_bss_52[i][2] = BoardPlayerMotionCreate(i, lbl_1_data_314[GWPlayer[i].character]);
        }
    }
    for (i = 0; i < 3; i++) {
        lbl_1_bss_F4[i] = BoardModelCreate(0x70000, NULL, 1);
        BoardModelLayerSet(lbl_1_bss_F4[i], 2);
        BoardModelVisibilitySet(lbl_1_bss_F4[i], 0);
    }
    var_r26 = &lbl_1_data_0[8];
    lbl_1_bss_FA = lbl_1_bss_14[8];
    BoardModelPosSetV(lbl_1_bss_FA, &var_r26->pos);
    BoardModelRotSetV(lbl_1_bss_FA, &var_r26->rot);
    BoardModelVisibilitySet(lbl_1_bss_FA, 1);
    BoardModelAlphaSet(lbl_1_bss_FA, 0);
    var_f31 = 0.0f;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_B2[i] = 0;
        lbl_1_bss_D4[i] = NULL;
    }
    fn_1_5648();
    fn_1_2C10();
    BoardRollDispSet(0);
    BoardPlayerMotBlendSet(temp_r30, 180, 15);
    BoardCameraViewSet(2);
    while (!BoardPlayerMotBlendCheck(temp_r30)) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    BoardPlayerMotionShiftSet(temp_r30, lbl_1_bss_52[temp_r30][0], 0.0f, 5.0f, 0);
    HuAudPlayerVoicePlay(temp_r30, 0x128);
    BoardModelPosGet(lbl_1_bss_14[3], &sp20);
    BoardModelPosSetV(lbl_1_bss_FA, &sp20);
    BoardModelVisibilitySet(lbl_1_bss_FA, 1);
    for (i = 0; i < 60; i++) {
        var_f31 += 4.25f;
        BoardModelAlphaSet(lbl_1_bss_FA, var_f31);
        HuPrcVSleep();
    }
    BoardModelAlphaSet(lbl_1_bss_FA, 0xFF);
    HuAudFXPlay(0x4C);
    BoardPlayerIdleSet(temp_r30);
    HuPrcSleep(8);
    BoardWinCreate(2, MAKE_MESSID(32, 1), 3);
    BoardWinWait();
    BoardWinKill();
    var_r27 = BoardSpaceGet(0, GWPlayer[temp_r30].space_curr);
    lbl_1_bss_74 = lbl_1_bss_78 = var_r27->link[0];
    BoardSpacePosGet(0, lbl_1_bss_78, &sp14);
    BoardModelPosGet(lbl_1_bss_FA, &sp20);
    while (fn_1_1130(lbl_1_bss_FA, atan2d(sp14.x - sp20.x, sp14.z - sp20.z), 2.0f) == 0) {
        HuPrcVSleep();
    }
    PSVECSubtract(&sp14, &sp20, &sp8);
    PSVECScale(&sp8, &sp8, 0.022222223f);
    for (i = 0; i < 45; i++) {
        PSVECAdd(&sp20, &sp8, &sp20);
        BoardModelPosSetV(lbl_1_bss_FA, &sp20);
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 1, 1000);
    BoardModelPosSetV(lbl_1_bss_FA, &sp14);
    BoardPlayerPosGet(temp_r30, &sp14);
    while (fn_1_1130(lbl_1_bss_FA, atan2d(sp14.x - sp20.x, sp14.z - sp20.z), 3.0f) == 0) {
        HuPrcVSleep();
    }
    fn_1_2EE8(1);
    while (fn_1_2F54(0) == 0) {
        HuPrcVSleep();
    }
    fn_1_2FBC(0)->unk00 = 2;
    while (fn_1_1130(lbl_1_bss_FA, 90.0f, 3.0f) == 0) {
        HuPrcVSleep();
    }
    while (fn_1_2F54(0) == 0) {
        HuPrcVSleep();
    }
    fn_1_28BC();
    fn_1_2B8C();
    BoardAudSeqPause(0, 0, 1000);
    BoardRollDispSet(1);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    BoardPlayerMotionKill(temp_r30, lbl_1_bss_52[temp_r30][0]);
    BoardPlayerMotionKill(temp_r30, lbl_1_bss_52[temp_r30][1]);
    for (i = 0; i < 4; i++) {
        if (i != temp_r30) {
            for (j = 0; j < 3; j++) {
                BoardPlayerMotionKill(i, lbl_1_bss_52[i][j]);
            }
        }
    }
    for (i = 0; i < 3; i++) {
        BoardModelKill(lbl_1_bss_F4[i]);
    }
    fn_1_5828();
    BoardModelVisibilitySet(lbl_1_bss_FA, 0);
    HuPrcEnd();
}

static void fn_1_28BC(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f30;
    float var_f31;
    BoardSpace *var_r30;
    s16 var_r29;
    s32 var_r31;
    s32 i;
    Process *var_r27;
    float *var_r26;

    var_r27 = HuPrcChildCreate(fn_1_45A8, 0x2001, 0x800, 0, boardMainProc);
    HuPrcDestructorSet2(var_r27, fn_1_4630);
    var_r26 = (float*) &var_r27->user_data;
    lbl_1_bss_C2 = fn_1_4680(lbl_1_bss_78);
    var_r29 = 0;
    while (var_r29 == 0) {
        var_r31 = fn_1_3C9C();
        if (var_r31 != -1) {
            var_r30 = BoardSpaceGet(0, var_r31);
            if (var_r30->flag & 1) {
                lbl_1_bss_50 = var_r31;
            }
            if (var_r30->flag & 8) {
                fn_1_52A0(lbl_1_bss_50, lbl_1_bss_80);
                var_r29 = 1;
                var_f31 = 255.0f;
                HuPrcKill(var_r27);
            }
            BoardSpacePosGet(0, var_r31, &sp20);
            BoardModelPosGet(lbl_1_bss_FA, &sp14);
            temp_f30 = atan2d(sp20.x - sp14.x, sp20.z - sp14.z);
            BoardModelRotYSet(lbl_1_bss_FA, temp_f30);
            PSVECSubtract(&sp20, &sp14, &sp8);
            PSVECScale(&sp8, &sp8, 0.022222223f);
            *var_r26 = temp_f30 - 180.0f;
            fn_1_2EE8(3);
            for (i = 0; i < 45; i++) {
                PSVECAdd(&sp8, &sp14, &sp14);
                BoardModelPosSetV(lbl_1_bss_FA, &sp14);
                fn_1_5018();
                if (var_r29 != 0) {
                    var_f31 -= 5.6666665f;
                    BoardModelAlphaSet(lbl_1_bss_FA, var_f31);
                }
                HuPrcVSleep();
            }
            BoardModelPosSetV(lbl_1_bss_FA, &sp20);
            lbl_1_bss_74 = lbl_1_bss_78;
            lbl_1_bss_78 = var_r31;
            if (var_r29 != 0) {
                BoardModelVisibilitySet(lbl_1_bss_FA, 0);
            }
        }
        HuPrcVSleep();
    }
}

static void fn_1_2B8C(void) {
    s32 i;

    while (fn_1_2F54(4) == 0 || lbl_1_bss_7C != 0) {
        fn_1_2EE8(3);
        HuPrcVSleep();
    }
    HuAudFXStop(lbl_1_bss_6C);
    for (i = 0; i < 4; i++) {
        fn_1_2E60(i);
    }
}

static void fn_1_2C10(void) {
    Vec sp8;
    BssE4Data *temp_r31;
    s32 i;

    for (i = 0; i < 4; i++) {
        temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(BssE4Data), MEMORY_DEFAULT_NUM);
        temp_r31->unk04 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 3), NULL, 0);
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[3]), lbl_1_data_348[i], &sp8);
        BoardModelLayerSet(temp_r31->unk04, 2);
        BoardModelPosSetV(temp_r31->unk04, &sp8);
        temp_r31->unk10 = lbl_1_data_358[i];
        BoardModelRotYSet(temp_r31->unk04, temp_r31->unk10);
        temp_r31->unk18 = 0.0f;
        BoardModelAlphaSet(temp_r31->unk04, temp_r31->unk18);
        BoardModelVisibilitySet(temp_r31->unk04, 0);
        temp_r31->unk14 = 0.003921569f * frand8() * 360.0f;
        temp_r31->unk08 = -1;
        temp_r31->unk00 = 0;
        temp_r31->unk06 = i;
        temp_r31->unk1C = 0.0f;
        temp_r31->unk02 = 1;
        temp_r31->unk0C = 0;
        if (i == 0) {
            temp_r31->unk0A = lbl_1_bss_FA;
        } else {
            temp_r31->unk0A = ((BssE4Data*) lbl_1_bss_E4[i - 1]->user_data)->unk04;
        }
        lbl_1_bss_E4[i] = HuPrcChildCreate(fn_1_30A4, 0x2003, 0x1000, 0, boardMainProc);
        lbl_1_bss_E4[i]->user_data = temp_r31;
        temp_r31->unk2C = HuPrcChildCreate(fn_1_2FDC, 0x2002, 0x1000, 0, boardMainProc);
        temp_r31->unk2C->user_data = temp_r31;
    }
}

static void fn_1_2E60(s16 arg0) {
    BssE4Data *temp_r3;

    temp_r3 = fn_1_2FBC(arg0);
    BoardModelKill(temp_r3->unk04);
    HuPrcKill(temp_r3->unk2C);
    HuPrcKill(lbl_1_bss_E4[arg0]);
    HuMemDirectFree(lbl_1_bss_E4[arg0]->user_data);
}

static void fn_1_2EE8(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (fn_1_2FBC(i)->unk02 != 0) {
            fn_1_2FBC(i)->unk00 = arg0;
        }
    }
}

static s32 fn_1_2F54(u32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0 != fn_1_2FBC(i)->unk00) {
            break;
        }
    }
    if (i != 4) {
        return 0;
    } else {
        return 1;
    }
}

static BssE4Data *fn_1_2FBC(s16 arg0) {
    return lbl_1_bss_E4[arg0]->user_data;
}

static void fn_1_2FDC(void) {
    Vec sp8;
    BssE4Data *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        BoardModelPosGet(temp_r31->unk04, &sp8);
        sp8.y = temp_r31->unk1C + 4.0 * sind(temp_r31->unk14);
        BoardModelPosSetV(temp_r31->unk04, &sp8);
        if (temp_r31->unk08 != -1) {
            sp8.y += 50.0f;
            BoardPlayerPosSetV(temp_r31->unk08, &sp8);
        }
        temp_r31->unk14 += 2.0f;
        HuPrcVSleep();
    }
}

static void fn_1_30A4(void) {
    Vec sp20;
    Vec sp14;
    float temp_f31;
    BssE4Data *temp_r31;
    BoardSpace *var_r28;
    Process *var_r27;
    s16 var_r29;
    s16 temp_r22;
    s32 i;

    var_r29 = 0;
    temp_r31 = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        switch (temp_r31->unk00) {
            case 0:
            case 4:
                break;
            case 1:
                BoardModelPosGet(temp_r31->unk04, &sp20);
                BoardMusStart(1, 0x20, 0x7F, 0);
                lbl_1_bss_6A = 1;
                HuAudFXPlay(0x45F);
                temp_r22 = fn_1_58A4(&sp20);
                HuPrcSleep(45);
                if (temp_r31->unk06 == 0) {
                    BoardPlayerPosGet(GWSystem.player_curr, &temp_r31->unk20);
                    temp_r31->unk20.y += 65.0f;
                } else {
                    temp_r31->unk20 = fn_1_2FBC(temp_r31->unk06 - 1)->unk20;
                    temp_r31->unk20.z -= 300.0f;
                }
                BoardModelPosGet(lbl_1_bss_14[3], &sp20);
                temp_r31->unk1C = sp20.y;
                BoardModelVisibilitySet(temp_r31->unk04, 1);
                if (temp_r31->unk06 == 0) {
                    lbl_1_bss_6C = HuAudFXPlay(0x460);
                }
                for (i = 0; i < 60; i++) {
                    temp_r31->unk18 += 4.25f;
                    BoardModelAlphaSet(temp_r31->unk04, temp_r31->unk18);
                    temp_r31->unk1C += 1.0833334f;
                    HuPrcVSleep();
                }
                fn_1_5980(temp_r22);
                BoardModelPosGet(temp_r31->unk04, &sp20);
                temp_f31 = atan2d(temp_r31->unk20.x - sp20.x, temp_r31->unk20.z - sp20.z);
                while (fn_1_1130(temp_r31->unk04, temp_f31, 5.0f) == 0) {
                    HuPrcVSleep();
                }
                PSVECSubtract(&temp_r31->unk20, &sp20, &sp14);
                PSVECScale(&sp14, &sp14, 0.016666668f);
                for (i = 0; i < 60; i++) {
                    PSVECAdd(&sp14, &sp20, &sp20);
                    BoardModelPosSetV(temp_r31->unk04, &sp20);
                    HuPrcVSleep();
                }
                BoardModelPosSetV(temp_r31->unk04, &temp_r31->unk20);
                while (fn_1_1130(temp_r31->unk04, 0.0f, 5.0f) == 0) {
                    HuPrcVSleep();
                }
                if (temp_r31->unk06 == 0) {
                    i = GWSystem.player_curr;
                    temp_f31 = BoardPlayerRotYGet(i);
                    omVibrate(i, 12, 6, 6);
                    while (TRUE) {
                        if (temp_f31 > 0.0f) {
                            temp_f31 -= 2.0f;
                            if (temp_f31 < 0.0f) {
                                temp_f31 = 0.0f;
                            }
                        }
                        BoardPlayerRotYSet(i, temp_f31);
                        BoardPlayerPosGet(i, &sp14);
                        BoardModelPosGet(temp_r31->unk04, &sp20);
                        sp14.y += 2.2f;
                        if (sp14.y > sp20.y + 50.0f) {
                            sp14.y = sp20.y + 50.0f;
                            break;
                        }
                        BoardPlayerPosSetV(i, &sp14);
                        HuPrcVSleep();
                    }
                    BoardPlayerPosSetV(i, &sp14);
                    BoardPlayerRotYSet(i, 0.0f);
                    BoardPlayerMotionShiftSet(i, lbl_1_bss_52[GWSystem.player_curr][1], 0.0f, 10.0f, 0x40000001);
                    temp_r31->unk08 = i;
                }
                if (temp_r31->unk06 == 0) {
                    BoardModelPosGet(lbl_1_bss_FA, &temp_r31->unk20);
                } else {
                    BoardModelPosGet(fn_1_2FBC(temp_r31->unk06 - 1)->unk04, &temp_r31->unk20);
                }
                temp_r31->unk00 = 0;
                break;
            case 2:
                while (fn_1_1130(temp_r31->unk04, 90.0f, 3.0f) == 0) {
                    BoardPlayerRotYSet(temp_r31->unk08, BoardModelRotYGet(temp_r31->unk04));
                    HuPrcVSleep();
                }
                BoardPlayerRotYSet(temp_r31->unk08, BoardModelRotYGet(temp_r31->unk04));
                temp_r31->unk00 = 0;
                break;
            case 3:
                BoardModelPosGet(temp_r31->unk04, &sp20);
                temp_f31 = atan2d(temp_r31->unk20.x - sp20.x, temp_r31->unk20.z - sp20.z);
                BoardModelRotYSet(temp_r31->unk04, temp_f31);
                if (temp_r31->unk08 != -1) {
                    BoardPlayerRotYSet(temp_r31->unk08, temp_f31);
                }
                PSVECSubtract(&temp_r31->unk20, &sp20, &sp14);
                PSVECScale(&sp14, &sp14, 0.022222223f);
                if (temp_r31->unk0C > 0) {
                    var_r28 = BoardSpaceGet(0, temp_r31->unk0C);
                    if (var_r28->flag & 1) {
                        var_r29 = 1;
                        if (temp_r31->unk08 != -1) {
                            var_r27 = HuPrcChildCreate(fn_1_38D8, 0x2002, 0x1000, 0, boardMainProc);
                            var_r27->user_data = temp_r31;
                            lbl_1_bss_7C++;
                        }
                    }
                }
                for (i = 0; i < 45; i++) {
                    PSVECAdd(&sp20, &sp14, &sp20);
                    BoardModelPosSetV(temp_r31->unk04, &sp20);
                    if (temp_r31->unk08 != -1) {
                        BoardPlayerPosSetV(temp_r31->unk08, &sp20);
                    }
                    if (var_r29 != 0) {
                        if (temp_r31->unk06 == 2 && lbl_1_bss_6A != 0) {
                            BoardAudSeqFadeOut(1, 1000);
                            lbl_1_bss_6A = 0;
                        }
                        temp_r31->unk18 -= 5.6666665f;
                        BoardModelAlphaSet(temp_r31->unk04, temp_r31->unk18);
                    }
                    HuPrcVSleep();
                }
                temp_r31->unk0E = temp_r31->unk0C;
                if (temp_r31->unk06 == 0) {
                    temp_r31->unk0C = lbl_1_bss_74;
                } else {
                    temp_r31->unk0C = fn_1_2FBC(temp_r31->unk06 - 1)->unk0E;
                }
                BoardModelPosSetV(temp_r31->unk04, &temp_r31->unk20);
                if (temp_r31->unk08 != -1) {
                    BoardPlayerPosSetV(temp_r31->unk08, &temp_r31->unk20);
                }
                if (temp_r31->unk06 == 0) {
                    BoardModelPosGet(lbl_1_bss_FA, &temp_r31->unk20);
                } else {
                    BoardModelPosGet(fn_1_2FBC(temp_r31->unk06 - 1)->unk04, &temp_r31->unk20);
                }
                if (var_r29 != 0) {
                    BoardModelVisibilitySet(temp_r31->unk04, 0);
                    temp_r31->unk02 = 0;
                    temp_r31->unk00 = 4;
                } else {
                    temp_r31->unk00 = 0;
                }
                break;
        }
        HuPrcVSleep();
    }
}

static void fn_1_38D8(void) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f28;
    float temp_f26;
    float var_f29;
    BssE4Data *temp_r30;
    s16 temp_r31;

    OSReport("Getoff\n");
    temp_r30 = HuPrcCurrentGet()->user_data;
    temp_r31 = temp_r30->unk08;
    temp_r30->unk08 = -1;
    BoardPlayerMotionShiftSet(temp_r31, 4, 0.0f, 5.0f, 0);
    sp18 = lbl_1_bss_80[temp_r31];
    GWPlayer[temp_r31].space_curr = lbl_1_bss_B0;
    BoardPlayerPosGet(temp_r31, &sp24);
    var_f28 = atan2d(sp18.x - sp24.x, sp18.z - sp24.z);
    BoardPlayerRotYSet(temp_r31, var_f28);
    PSVECSubtract(&sp18, &sp24, &spC);
    PSVECScale(&spC, &spC, 0.025f);
    temp_f26 = 12.0f;
    var_f29 = 0.0f;
    while (TRUE) {
        spC.y = temp_f26 - var_f29 * var_f29 * 0.25f * 0.075f;
        var_f29 += 1.0f;
        PSVECAdd(&spC, &sp24, &sp24);
        if (sp24.y <= sp18.y) {
            sp24.y = sp18.y;
            break;
        }
        var_f28 = VECDistanceXZ(&sp18, &sp24);
        if (var_f28 <= 1.0f) {
            spC.x = spC.z = 0.0f;
        }
        BoardPlayerPosSetV(temp_r31, &sp24);
        HuPrcVSleep();
    }
    BoardPlayerPosSetV(temp_r31, &sp18);
    BoardPlayerIdleSet(temp_r31);
    HuPrcSleep(8);
    BoardPlayerMotBlendSet(temp_r31, 0, 0xF);
    while (!BoardPlayerMotBlendCheck(temp_r31)) {
        HuPrcVSleep();
    }
    lbl_1_bss_7C--;
    HuPrcEnd();
}

static s32 fn_1_3C9C(void) {
    Vec sp50;
    Vec sp44;
    Vec sp38;
    float sp28[4];
    s16 sp20[4];
    s16 sp18[4];
    s16 sp10[4];
    float sp8[2];
    BoardSpace *temp_r30;
    BoardSpace *var_r28;
    float var_f29;
    float var_f30;
    float var_f31;
    s8 var_r26;
    s8 var_r25;
    s32 var_r24;
    s16 var_r23;
    s16 var_r22;
    s16 temp_r20;
    s16 var_r19;
    s16 var_r21;
    s16 var_r27;
    s16 var_r29;
    s16 var_r18;
    s32 temp_r17;
    s32 i;

    temp_r30 = BoardSpaceGet(0, lbl_1_bss_78);
    if (temp_r30->flag & 8) {
        return -1;
    }
    if (temp_r30->flag & 0x400) {
        var_r29 = 0;
        i = BoardSpaceLinkTargetListGet(0, lbl_1_bss_78, sp10);
        for (i--; i >= 0; i--) {
            var_r28 = BoardSpaceGet(0, sp10[i]);
            if (var_r28->flag & 4) {
                sp20[var_r29] = sp10[i];
                sp18[var_r29] = 1;
                var_r29++;
            }
        }
        for (i = 0; i < temp_r30->link_cnt; i++) {
            var_r28 = BoardSpaceGet(0, temp_r30->link[i]);
            if (var_r28->flag & 4) {
                sp20[var_r29] = temp_r30->link[i];
                sp18[var_r29] = 0;
                var_r29++;
            }
        }
        var_r27 = 0;
        BoardModelPosGet(lbl_1_bss_FA, &sp50);
        for (i = 0; i < var_r29; i++) {
            BoardSpacePosGet(0, sp20[i], &sp44);
            sp50.y = sp44.y;
            PSVECSubtract(&sp44, &sp50, &sp38);
            var_f31 = atan2d(sp38.x, sp38.z);
            if (var_f31 < 0.0f) {
                var_f31 += 360.0f;
            }
            sp28[i] = var_f31;
            PSVECNormalize(&sp38, &sp44);
            PSVECScale(&sp44, &sp44, 110.0f);
            sp44.y += 200.0f;
            PSVECAdd(&sp50, &sp44, &sp44);
            BoardModelPosSetV(lbl_1_bss_F4[i], &sp44);
            BoardModelRotYSet(lbl_1_bss_F4[i], var_f31);
            BoardModelVisibilitySet(lbl_1_bss_F4[i], 1);
        }
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(19, 27));
        var_r22 = HuWinCreate(-10000.0f, 368.0f, sp8[0], sp8[1], 0);
        HuWinMesSet(var_r22, MAKE_MESSID(19, 27));
        HuWinBGTPLvlSet(var_r22, 0.0f);
        HuWinMesSpeedSet(var_r22, 0);
        var_f31 = 0.0f;
        temp_r17 = GWSystem.player_curr;
        temp_r20 = GWPlayer[temp_r17].port;
        var_f29 = BoardModelRotYGet(lbl_1_bss_FA) - 180.0f;
        if (var_f29 < 0.0f) {
            var_f29 += 360.0f;
        }
        var_r21 = frandmod(30) + 30;
        var_r18 = 0;
        while (TRUE) {
            var_r23 = var_r27;
            if (GWPlayer[temp_r17].com) {
                var_r26 = var_r25 = 0;
                var_r19 = 0;
                if (var_r21 != 0) {
                    var_r21--;
                } else {
                    var_r21 = frandmod(10) + 15;
                    if (frandBool() || var_r18 == 3) {
                        var_r19 = 0x100;
                    } else {
                        OSReport("com sel chg: %d \n", var_r29);
                        var_r18++;
                        var_r23 = frandmod(var_r29);
                    }
                }
            } else {
                var_r26 = HuPadStkX[temp_r20];
                var_r25 = HuPadStkY[temp_r20];
                var_r19 = HuPadBtnDown[temp_r20];
            }
            if (abs(var_r26) < 10) {
                var_r26 = 0;
            }
            if (abs(var_r25) < 10) {
                var_r25 = 0;
            }
            if (var_r26 != 0 || var_r25 != 0) {
                var_f30 = atan2d(-var_r26, var_r25) - 180.0;
                var_f30 += var_f29;
                if (var_f30 >= 360.0f) {
                    var_f30 -= 360.0f;
                }
                if (var_f30 < 0.0f) {
                    var_f30 += 360.0f;
                }
                for (i = 0; i < var_r29; i++) {
                    if (fabs(sp28[i] - var_f30) < 30.0) {
                        var_r23 = i;
                        break;
                    }
                }
            }
            if (var_r23 != var_r27) {
                HuAudFXPlay(0);
                var_f31 = 0.0f;
                var_r27 = var_r23;
            }
            if (var_r19 & 0x100) {
                break;
            }
            for (i = 0; i < var_r29; i++) {
                if (var_r27 == i) {
                    sp38.x = sp38.y = sp38.z = 1.8f + sind(var_f31);
                    var_f31 += 8.0f;
                    if (var_f31 > 180.0f) {
                        var_f31 -= 180.0f;
                    }
                } else {
                    sp38.x = sp38.y = sp38.z = 1.8f;
                }
                BoardModelScaleSetV(lbl_1_bss_F4[i], &sp38);
            }
            HuPrcVSleep();
        }
        HuAudFXPlay(2);
        for (i = 0; i < var_r29; i++) {
            BoardModelVisibilitySet(lbl_1_bss_F4[i], 0);
        }
        HuWinKill(var_r22);
        var_r24 = sp20[var_r27];
        lbl_1_bss_70 = sp18[var_r27];
        lbl_1_bss_C2 = fn_1_4680(var_r24);
    } else if (lbl_1_bss_70 != 0) {
        i = BoardSpaceLinkTargetListGet(0, lbl_1_bss_78, sp10);
        for (i--; i >= 0; i--) {
            var_r28 = BoardSpaceGet(0, sp10[i]);
            if (var_r28->flag & 0x200) {
                break;
            }
        }
        var_r24 = sp10[i];
    } else {
        for (i = 0; i < temp_r30->link_cnt; i++) {
            var_r28 = BoardSpaceGet(0, temp_r30->link[i]);
            if (var_r28->flag & 0x200) {
                break;
            }
        }
        var_r24 = temp_r30->link[i];
    }
    return var_r24;
}

static void fn_1_45A8(void) {
    float *temp_r30;
    s32 var_r31;

    var_r31 = 15;
    temp_r30 = (float*) &HuPrcCurrentGet()->user_data;
    while (TRUE) {
        if (var_r31 == 0) {
            BoardCameraMoveSet(0);
            BoardCameraTargetPlayerSet(GWSystem.player_curr);
            BoardCameraZoomSet(700.0f);
            BoardStatusShowSetAll(0);
            break;
        }
        var_r31--;
        HuPrcVSleep();
    }
    while (TRUE) {
        BoardCameraRotSet(-15.0f, *temp_r30);
        HuPrcVSleep();
    }
}

static void fn_1_4630(void) {
    BoardCameraMoveSet(0);
    BoardCameraTargetPlayerSet(GWSystem.player_curr);
    BoardCameraViewSet(2);
    BoardStatusShowSetAll(1);
    BoardCameraMoveSet(1);
}

static s32 fn_1_4680(s16 arg0) {
    BoardSpace *var_r30;
    BoardSpace *var_r29;
    s16 sp8[4];
    s16 var_r26;
    s32 var_r27;
    s32 i;

    var_r27 = 0;
    var_r26 = 0;
    var_r30 = BoardSpaceGet(0, arg0);
    lbl_1_bss_C2 = 0;
    while (TRUE) {
        for (i = 0; i < 4; i++) {
            if (i != GWSystem.player_curr && arg0 == GWPlayer[i].space_curr) {
                lbl_1_bss_BA[var_r27++] = i;
            }
        }
        if (var_r27 == 3 || var_r26 == 1) {
            break;
        }
        if (lbl_1_bss_70 != 0) {
            i = BoardSpaceLinkTargetListGet(0, arg0, sp8);
            for (i--; i >= 0; i--) {
                var_r29 = BoardSpaceGet(0, sp8[i]);
                if (var_r29->flag & 0x200) {
                    break;
                }
            }
            arg0 = sp8[i];
        } else {
            for (i = 0; i < var_r30->link_cnt; i++) {
                var_r29 = BoardSpaceGet(0, var_r30->link[i]);
                if (var_r29->flag & 0x200) {
                    break;
                }
            }
            arg0 = var_r30->link[i];
        }
        var_r30 = BoardSpaceGet(0, arg0);
        if (var_r30->flag & 0x401) {
            var_r26 = 1;
        }
    }
    return var_r27;
}

static void fn_1_4848(void) {
    Vec sp20;
    Vec sp14;
    float temp_f28;
    BssE4Data *var_r29;
    s32 temp_r30;
    s32 i;

    temp_r30 = (s32) HuPrcCurrentGet()->user_data;
    BoardPlayerPosGet(temp_r30, &sp20);
    BoardPlayerMotBlendSet(temp_r30, BoardModelRotYGet(lbl_1_bss_FA) - 180.0f, 0xA);
    while (!BoardPlayerMotBlendCheck(temp_r30)) {
        BoardModelPosGet(lbl_1_bss_FA, &sp14);
        temp_f28 = VECDistanceXZ(&sp20, &sp14);
        if (temp_f28 <= 200.0f) {
            HuAudPlayerVoicePlay(temp_r30, 0x128);
            goto block_A;
        }
        HuPrcVSleep();
    }
    BoardPlayerMotionShiftSet(temp_r30, lbl_1_bss_52[temp_r30][0], 0.0f, 5.0f, 0);
    HuAudPlayerVoicePlay(temp_r30, 0x128);
    for (i = 0; i < 65; i++) {
        BoardModelPosGet(lbl_1_bss_FA, &sp14);
        temp_f28 = VECDistanceXZ(&sp20, &sp14);
        if (temp_f28 <= 200.0f) {
            goto block_A;
        }
        HuPrcVSleep();
    }
    BoardPlayerMotionShiftSet(temp_r30, 1, 0.0f, 5.0f, 0);
    BoardModelPosGet(lbl_1_bss_FA, &sp14);
    temp_f28 = VECDistanceXZ(&sp20, &sp14);
    if (temp_f28 > 200.0f) {
        HuPrcVSleep();
    }
block_A:
    lbl_1_bss_B2[temp_r30] = 2;
    BoardPlayerMotionStart(temp_r30, lbl_1_bss_52[temp_r30][2], 0x40000001);
    temp_f28 = 20.0f;
    omVibrate(temp_r30, 12, 4, 2);
    while (TRUE) {
        sp20.y += temp_f28;
        BoardPlayerPosSetV(temp_r30, &sp20);
        if (sp20.y >= 600.0f) {
            break;
        }
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r30, lbl_1_bss_52[temp_r30][1], 0x40000001);
    for (i = 0; i < 4; i++) {
        var_r29 = fn_1_2FBC(i);
        if (var_r29->unk08 == -1) {
            break;
        }
    }
    var_r29->unk08 = temp_r30;
    BoardPlayerRotYSet(temp_r30, BoardModelRotYGet(var_r29->unk04));
    for (i = 0; i < 4; i++) {
        HuPrcSetStat(lbl_1_bss_E4[i], 1);
    }
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_D4[i] && i != temp_r30) {
            HuPrcSetStat(lbl_1_bss_D4[i], 1);
        }
    }
    HuPrcSetStat(lbl_1_bss_48, 1);
    BoardWinCreate(0, MAKE_MESSID(32, 2), -1);
    BoardWinInsertMesSet(GWPlayer[temp_r30].character, 0);
    BoardWinWait();
    BoardWinKill();
    for (i = 0; i < 4; i++) {
        HuPrcResetStat(lbl_1_bss_E4[i], 1);
    }
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_D4[i] && i != temp_r30) {
            HuPrcResetStat(lbl_1_bss_D4[i], 1);
        }
    }
    HuPrcResetStat(lbl_1_bss_48, 1);
    lbl_1_bss_D4[temp_r30] = NULL;
    HuPrcEnd();
}

static void fn_1_5018(void) {
    Vec sp18;
    Vec spC;
    float var_f29;
    Process *temp_r3;
    s32 i;

    BoardModelPosGet(lbl_1_bss_FA, &spC);
    for (i = 0; i < lbl_1_bss_C2; i++) {
        BoardPlayerPosGet(lbl_1_bss_BA[i], &sp18);
        var_f29 = VECDistanceXZ(&sp18, &spC);
        if (var_f29 < 900.0f && lbl_1_bss_B2[lbl_1_bss_BA[i]] == 0) {
            temp_r3 = HuPrcChildCreate(fn_1_4848, 0x2003, 0x2000, 0, boardMainProc);
            lbl_1_bss_D4[lbl_1_bss_BA[i]] = temp_r3;
            temp_r3->user_data = (u8*) lbl_1_bss_BA[i];
            lbl_1_bss_B2[lbl_1_bss_BA[i]] = 1;
        }
    }
}

static void fn_1_52A0(s16 arg0, Vec *arg1) {
    Vec sp40[4];
    Vec sp10[4];
    BssE4Data *var_r30;
    BoardSpace *var_r29;
    BoardSpace *var_r28;
    s16 sp8[4];
    s32 var_r27;
    s32 i;

    OSReport("Landing Pos Get\n");
    lbl_1_bss_B0 = -1;
    var_r29 = BoardSpaceGet(0, arg0);
    for (i = 0; i < var_r29->link_cnt; i++) {
        var_r28 = BoardSpaceGet(0, var_r29->link[i]);
        if (var_r28->flag & 2) {
            lbl_1_bss_B0 = var_r29->link[i];
            break;
        }
    }
    if (lbl_1_bss_B0 == -1) {
        i = BoardSpaceLinkTargetListGet(0, arg0, sp8);
        for (i--; i >= 0; i--) {
            var_r28 = BoardSpaceGet(0, sp8[i]);
            if (var_r28->flag & 2) {
                lbl_1_bss_B0 = sp8[i];
                break;
            }
        }
    }
    if (lbl_1_bss_B0 == -1) {
        OSReport("\x92\x85\x92\x6E\x92\x6E\x93_\x82\xAA\x96\xB3\x82\xA2\n");
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    var_r27 = 0;
    for (i = 0; i < 4; i++) {
        BoardPlayerPosGet(i, &sp40[i]);
        BoardPlayerRotGet(i, &sp10[i]);
        sp8[i] = GWPlayer[i].space_curr;
        if (lbl_1_bss_B0 == sp8[i]) {
            var_r27 += 1;
        }
    }
    for (i = 0; i < 4; i++) {
        var_r30 = fn_1_2FBC(i);
        if (var_r30->unk08 != -1 && var_r30->unk08 != GWSystem.player_curr) {
            BoardSpaceCornerPosGet(lbl_1_bss_B0, var_r27++, &arg1[var_r30->unk08]);
        }
    }
    for (i = 0; i < 4; i++) {
        BoardPlayerPosSetV(i, &sp40[i]);
        BoardPlayerRotSetV(i, &sp10[i]);
        GWPlayer[i].space_curr = sp8[i];
    }
    BoardSpacePosGet(0, lbl_1_bss_B0, &arg1[GWSystem.player_curr]);
}

static void fn_1_55A0(void) {
    lbl_1_bss_48 = NULL;
}

void fn_1_55B4(void) {
    s32 sp8;

    sp8 = GWSystem.player_curr;
    lbl_1_bss_48 = HuPrcChildCreate(fn_1_20EC, 0x2004, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_48, fn_1_55A0);
    while (lbl_1_bss_48) {
        HuPrcVSleep();
    }
}

static void fn_1_5648(void) {
    ParticleData *var_r30;
    s32 i;

    lbl_1_bss_4C = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_W04, 6));
    for (i = 0; i < 4; i++) {
        lbl_1_bss_C4[i] = omAddObjEx(boardObjMan, 0x101, 1, 0, -1, fn_1_59C4);
        lbl_1_bss_C4[i]->model[0] = Hu3DParticleCreate(lbl_1_bss_4C, 100);
        Hu3DParticleColSet(lbl_1_bss_C4[i]->model[0], 0x40, 0xD2, 0xFF);
        Hu3DParticleScaleSet(lbl_1_bss_C4[i]->model[0], 5.0f);
        Hu3DParticleHookSet(lbl_1_bss_C4[i]->model[0], fn_1_5A2C);
        Hu3DParticleBlendModeSet(lbl_1_bss_C4[i]->model[0], 1);
        Hu3DModelAttrSet(lbl_1_bss_C4[i]->model[0], 1);
        var_r30 = Hu3DData[lbl_1_bss_C4[i]->model[0]].unk_120;
        var_r30->unk_1C = lbl_1_bss_C4[i];
    }
}

static void fn_1_5828(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        Hu3DModelKill(lbl_1_bss_C4[i]->model[0]);
        omDelObjEx(boardObjMan, lbl_1_bss_C4[i]);
    }
}

static s16 fn_1_58A4(Vec *arg0) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_C4[i]->work[0] == 0) {
            lbl_1_bss_C4[i]->work[0] = 1;
            lbl_1_bss_C4[i]->trans.x = arg0->x;
            lbl_1_bss_C4[i]->trans.y = arg0->y;
            lbl_1_bss_C4[i]->trans.z = arg0->z;
            return i;
        }
    }
    return -1;
}

static void fn_1_5980(s16 arg0) {
    lbl_1_bss_C4[arg0]->work[1] = 1;
    lbl_1_bss_C4[arg0]->work[2] = 0;
}

static void fn_1_59C4(omObjData *arg0) {
    if (arg0->work[0] != 0) {
        Hu3DModelAttrReset(arg0->model[0], 1);
    }
    if (arg0->work[2] != 0) {
        arg0->work[0] = 0;
        Hu3DModelAttrSet(arg0->model[0], 1);
    }
}

static void fn_1_5A2C(ModelData *model, ParticleData *particle, Mtx matrix) {
    s32 var_r26;
    s32 i;
    s32 j;
    HsfanimStruct01 *var_r31;
    UnkParticleDataStruct *temp_r27;

    temp_r27 = particle->unk_1C;
    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk08.z = 0.0f;
            var_r31->unk2C = 0.0f;
        }
    }
    if (temp_r27->unk50 == 0) {
        for (i = 0; i < 3; i++) {
            var_r31 = particle->unk_48;
            for (j = 0; j < particle->unk_30; j++, var_r31++) {
                if (var_r31->unk08.z == 0.0f) {
                    break;
                }
            }
            if (j != particle->unk_30) {
                var_r31->unk08.x = 0.003921569f * frand8() * 360.0f;
                var_r31->unk08.y = 1.0f + 0.003921569f * frand8() * 1.5f;
                var_r31->unk08.z = 240.0f;
                var_r31->unk40.r = 0x40;
                var_r31->unk40.g = 0xD2;
                var_r31->unk40.b = 0xFF;
                var_r31->unk20 = 2.0f + 0.003921569f * frand8() * 8.0f;
                var_r31->unk24 = 2.0f + 0.003921569f * frand8() * 6.0f;
                var_r31->unk28 = 1.0f + 0.003921569f * frand8() * 3.0f;
                var_r31->unk34.x = -100.0f + 0.003921569f * frand8() * 200.0f;
                var_r31->unk34.y = 0.003921569f * frand8() * 10.0f;
                var_r31->unk34.z = -100.0f + 0.003921569f * frand8() * 200.0f;
                var_r31->unk2C = 7.0f + 0.003921569f * frand8() * 3.0f;
            }
        }
    }
    var_r31 = particle->unk_48;
    var_r26 = 0;
    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (var_r31->unk08.z != 0.0f) {
            var_r31->unk34.x += var_r31->unk28 * sind(var_r31->unk08.x);
            var_r31->unk34.y += var_r31->unk08.y;
            var_r31->unk34.z += var_r31->unk28 * cosd(var_r31->unk08.x);
            var_r31->unk08.x += var_r31->unk24 * sind(var_r31->unk08.x);
            if (var_r31->unk08.x >= 360.0f) {
                var_r31->unk08.x -= 360.0f;
            }
            var_r31->unk40.a = var_r31->unk08.z;
            var_r31->unk08.z -= var_r31->unk20;
            if (var_r31->unk08.z <= 0.0f) {
                var_r31->unk08.z = 0.0f;
            }
        } else {
            var_r26++;
        }
    }
    if (var_r26 == particle->unk_30) {
        temp_r27->unk54 = 1;
    }
}

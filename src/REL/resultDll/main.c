#include "dolphin.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/board/player.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/saveload.h"
#include "game/window.h"
#include "game/wipe.h"
#include "rel_sqrt_consts.h"

#include "math.h"

#include "REL/resultdll.h"

DataListModel lbl_1_data_0[] = { { DATA_MAKE_NUM(DATADIR_RESULT, 0x00), 1, 0, -1, -1, { 148, 132, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x01), 1, 0, -1, -1, { 148, 217, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x02), 1, 0, -1, -1, { 148, 302, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x03), 1, 0, -1, -1, { 148, 387, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 0, -1, -1, { 230, 132, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 4, -1, { 230, 217, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 4, -1, { 230, 302, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 4, -1, { 230, 387, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x05), 0, 0, -1, -1, { 410, 132, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 8, -1, { 410, 217, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 8, -1, { 410, 302, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 8, -1, { 410, 387, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { -1, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } } };

DataListSprite lbl_1_data_2A4[] = {
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x43), 0, 10, 288, 240, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1D), 0, 10, 288, 60, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 270, 132, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 450, 132, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 270, 217, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 450, 217, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 270, 302, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 450, 302, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 270, 387, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 450, 387, { 255, 255, 255, 255 } },
    { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } },
};

s16 lbl_1_data_380 = -1;

omObjData *lbl_1_bss_188;
omObjData *lbl_1_bss_184;
Process *lbl_1_bss_180;
s16 lbl_1_bss_17C;
s32 lbl_1_bss_178;
s32 lbl_1_bss_174;
s16 lbl_1_bss_172;
s16 lbl_1_bss_170;
s16 lbl_1_bss_168[4];
s16 lbl_1_bss_158[8];
AnimData *lbl_1_bss_144[5];
AnimData *lbl_1_bss_E4[8][3];
AnimData *lbl_1_bss_E0;
s16 lbl_1_bss_CE[9];
s16 lbl_1_bss_9E[8][3];
s16 lbl_1_bss_9C;
s16 lbl_1_bss_5C[8][4];
s16 lbl_1_bss_54[4];
s16 lbl_1_bss_52;
s16 lbl_1_bss_4A[4];
s16 lbl_1_bss_42[4];
s16 lbl_1_bss_3A[4];
s16 lbl_1_bss_12[4][5];
s16 lbl_1_bss_A[4];
s16 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

void fn_1_4D8(void);
void fn_1_888(void);

void fn_1_B78(void);
void fn_1_1F4C(void);
void fn_1_2ADC(void);
void fn_1_461C(void);
void fn_1_47FC(void);

void ObjectSetup(void)
{
    s32 i;
    s32 light;
    OSReport("******* RESULT ObjectSetup *********\n");
    lbl_1_bss_180 = omInitObjMan(50, 8192);
    lbl_1_bss_17C = GWSystem.mg_next;

    if (mgInfoTbl[lbl_1_bss_17C].ovl == OVL_M430) {
        for (i = 0; i < 4; i++) {
            GWPlayerCfg[i].group = GWPlayerCfg[i].group / 2;
        }
    }
    HuDataDirClose(mgInfoTbl[lbl_1_bss_17C].data_dir);
    if (mgInfoTbl[lbl_1_bss_17C].type == 3 || mgInfoTbl[lbl_1_bss_17C].type == 5 || mgInfoTbl[lbl_1_bss_17C].type == 6
        || !_CheckFlag(FLAG_ID_MAKE(1, 0))) {
        if (_CheckFlag(0x10000)) {
            HuAR_DVDtoARAM(DATADIR_BOARD);
            while (HuARDMACheck())
                ;
        }
        omOvlReturnEx(1, 1);
        return;
    }
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    CZoom = 500.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    light = Hu3DGLightCreate(0, 100, 1000, 0, -0.5, -1, 255, 255, 255);
    Hu3DGLightInfinitytSet(light);
    lbl_1_bss_174 = 0;
    if (mgInfoTbl[GWSystem.mg_next].type != 4) {
        HuPrcChildCreate(fn_1_4D8, 100, 12288, 0, lbl_1_bss_180);
    }
    else {
        HuPrcChildCreate(fn_1_6490, 100, 12288, 0, lbl_1_bss_180);
    }
    lbl_1_bss_184 = omAddObjEx(lbl_1_bss_180, 32730, 0, 0, -1, omOutView);
    HuWinInit(1);
    lbl_1_bss_172 = frandmod(4);
}

void fn_1_4D8(void)
{
    s16 player;
    s16 i;
    s16 window;
    s16 button;
    Process *process_curr = HuPrcCurrentGet();
    HuAudSeqPlay(57);
    for (i = player = 0; i < 4; i++) {
        if (GWPlayerCfg[i].iscom) {
            player++;
        }
    }
    if (player == 4) {
        lbl_1_bss_4 = 1;
    }
    else {
        lbl_1_bss_4 = 0;
    }
    fn_1_B78();
    HuPrcChildCreate(fn_1_888, 100, 8192, 0, lbl_1_bss_180);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATADIR_RESULT);
    lbl_1_bss_178 = 0;
    HuPrcChildCreate(fn_1_3FD8, 100, 12288, 0, lbl_1_bss_180);
    HuPrcSleep(10);
    if (!lbl_1_bss_174) {
        HuPrcSleep(20);
    }
    fn_1_1F4C();
    fn_1_40DC();
    fn_1_2ADC();
    window = HuWinCreate(-10000.0f, 400.0f, 320, 40, 0);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 0);
    HuWinPriSet(window, 5);
    HuWinAttrSet(window, 0x800);
    HuWinMesSet(window, MAKE_MESSID(0x24, 0x07));
    HuPrcSleep(4);
    i = 0;
    while (1) {
        if (!lbl_1_bss_4 || i <= 120) {
            for (player = button = 0; player < 4; player++) {
                if (!GWPlayerCfg[player].iscom) {
                    button |= HuPadBtnDown[GWPlayerCfg[player].pad_idx];
                }
            }
            if (button & PAD_BUTTON_A) {
                HuAudFXPlay(28);
                break;
            }
            HuPrcVSleep();
            i++;
        }
        else {
            break;
        }
    }
    HuWinKill(window);
    if (GWTeamGet()) {
        fn_1_47FC();
    }
    while (!lbl_1_bss_178) {
        HuPrcVSleep();
    }
    HuAudSeqAllFadeOut(1000);
    WipeColorSet(255, 255, 255);
    if (GWSaveModeGet() != 1 && SLSaveFlagGet()) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        fn_1_461C();
    }
    else {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
    }
    omSysPauseEnable(1);
    omOvlReturnEx(1, 1);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_888(void)
{
    f32 var_f29;
    f32 var_f31;
    f32 var_f30;

    var_f31 = 0.0f;
    var_f30 = 0.0f;
    var_f29 = 0.0f;
    lbl_1_bss_0 = 0;

    while (1) {
        if (((HuPadBtn[0] | HuPadBtn[1] | HuPadBtn[2] | HuPadBtn[3]) & 0x100) != 0 || lbl_1_bss_4 != 0) {
            lbl_1_bss_174 = 1;
        }
        else {
            lbl_1_bss_174 = 0;
        }
        Hu3DModelRotSet(lbl_1_bss_1A9C[4], 0.0f, var_f31, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_1A9C[5], 0.0f, -var_f31, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_1A9C[6], 0.0f, var_f31, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_1A9C[7], 0.0f, -var_f31, 0.0f);
        var_f31 += 0.2;
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        if (lbl_1_bss_0 != 0) {
            Hu3DModelRotSet(lbl_1_bss_1A9C[8], 0.0f, var_f30, 0.0f);
            Hu3DModelRotSet(lbl_1_bss_1A9C[9], 0.0f, -var_f30, 0.0f);
            Hu3DModelRotSet(lbl_1_bss_1A9C[10], 0.0f, var_f30, 0.0f);
            Hu3DModelRotSet(lbl_1_bss_1A9C[11], 0.0f, -var_f30, 0.0f);
            var_f29 += 0.001;
            if (var_f29 > 0.1) {
                var_f29 = 0.1f;
            }
            var_f30 += var_f29;
            if (var_f30 >= 360.0f) {
                var_f30 -= 360.0f;
            }
        }
        HuPrcVSleep();
    }
}

s32 lbl_1_data_3A8[] = {
    DATA_MAKE_NUM(DATADIR_RESULT, 0x10),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x11),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x12),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x13),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x14),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x15),
};

s32 lbl_1_data_3C0[] = {
    DATA_MAKE_NUM(DATADIR_RESULT, 0x1F),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x1E),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x1D),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x21),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x20),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x1F),
};

s16 lbl_1_data_3D8[] = {
    320,
    132,
    500,
    132,
    320,
    217,
    500,
    217,
    320,
    302,
    500,
    302,
    320,
    387,
    500,
    387,
};

s16 lbl_1_data_3F8[] = { 74, 132, 74, 217, 74, 302, 74, 387 };

Vec lbl_1_data_408[4] = { { 148, 132, 500 }, { 148, 217, 500 }, { 148, 302, 500 }, { 148, 387, 500 } };

s16 lbl_1_data_438[] = { 164, 148, 164, 233, 164, 318, 164, 403 };

void fn_1_3B50(s16 group, s16 value);
void fn_1_3CAC(s16 group, s16 value);

void fn_1_3E08(void);

void fn_1_B78(void)
{
    Vec pos;
    s16 sp8[5];
    s16 i;
    s16 j;
    s16 character;
    AnimData *anim;
    s16 sprite;
    s16 group;
    s16 model;
    AnimData *anim2;
    AnimData *anim3;
    AnimData *anim4;

    fn_1_8FF8(lbl_1_data_0);
    lbl_1_data_2A4[0].datanum = lbl_1_data_3A8[mgInfoTbl[lbl_1_bss_17C].type];
    lbl_1_data_2A4[1].datanum = lbl_1_data_3C0[mgInfoTbl[lbl_1_bss_17C].type];
    fn_1_927C(lbl_1_data_2A4);
    espDrawNoSet(lbl_1_bss_1A1A[0], 127);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x1B));
    for (i = 0; i < 8; i++) {
        lbl_1_bss_CE[i] = HuSprGrpCreate(3);
        lbl_1_bss_9E[i][0] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_CE[i], 0, lbl_1_bss_9E[i][0]);
        HuSprPosSet(lbl_1_bss_CE[i], 0, -28.0f, 0.0f);
        lbl_1_bss_9E[i][1] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_CE[i], 1, lbl_1_bss_9E[i][1]);
        HuSprPosSet(lbl_1_bss_CE[i], 1, 0.0f, 0.0f);
        lbl_1_bss_9E[i][2] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_CE[i], 2, lbl_1_bss_9E[i][2]);
        HuSprPosSet(lbl_1_bss_CE[i], 2, 28.0f, 0.0f);
        HuSprGrpPosSet(lbl_1_bss_CE[i], lbl_1_data_3D8[(i * 2)], lbl_1_data_3D8[(i * 2) + 1]);
        fn_1_3B50(lbl_1_bss_CE[i], 999);
    }
    fn_1_3E08();
    fn_1_423C(sp8);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3A));
    anim3 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3B));
    anim2 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3C));
    anim4 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3E));
    for (i = 0; i < 4; i++) {
        lbl_1_bss_3A[i] = HuSprGrpCreate(5);
        if (sp8[lbl_1_bss_4A[i]] < 100) {
            lbl_1_bss_12[i][0] = HuSprCreate(anim, 10, 0);
            HuSprGrpMemberSet(lbl_1_bss_3A[i], 0, lbl_1_bss_12[i][0]);
            HuSprPosSet(lbl_1_bss_3A[i], 0, 30.0f, -25.0f);
        }
        else {
            lbl_1_bss_12[i][0] = HuSprCreate(anim4, 10, 0);
            HuSprGrpMemberSet(lbl_1_bss_3A[i], 0, lbl_1_bss_12[i][0]);
            HuSprPosSet(lbl_1_bss_3A[i], 0, 40.0f, -21.0f);
        }
        lbl_1_bss_12[i][1] = HuSprCreate(anim3, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_3A[i], 1, lbl_1_bss_12[i][1]);
        HuSprPosSet(lbl_1_bss_3A[i], 1, 12.0f, -25.0f);
        lbl_1_bss_12[i][2] = HuSprCreate(anim2, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_3A[i], 2, lbl_1_bss_12[i][2]);
        HuSprPosSet(lbl_1_bss_3A[i], 2, 28.0f, -25.0f);
        lbl_1_bss_12[i][3] = HuSprCreate(anim2, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_3A[i], 3, lbl_1_bss_12[i][3]);
        HuSprPosSet(lbl_1_bss_3A[i], 3, 44.0f, -25.0f);
        lbl_1_bss_12[i][4] = HuSprCreate(anim2, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_3A[i], 4, lbl_1_bss_12[i][4]);
        HuSprPosSet(lbl_1_bss_3A[i], 4, 60.0f, -25.0f);
        HuSprGrpPosSet(lbl_1_bss_3A[i], lbl_1_data_438[(i * 2)], lbl_1_data_438[(i * 2) + 1]);
        fn_1_3CAC(lbl_1_bss_3A[i], 9);
        HuSprGrpScaleSet(lbl_1_bss_3A[i], 0.0f, 0.0f);
    }
    for (i = 0; i < 4; i++) {
        character = GWPlayerCfg[i].character;
        lbl_1_bss_E4[character][0] = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x22) + (character * 3));
        lbl_1_bss_E4[character][1] = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x23) + (character * 3));
        lbl_1_bss_E4[character][2] = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x24) + (character * 3));
        for (j = 0; j < 4; j++) {
            lbl_1_bss_5C[character][j] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x00) + j);
            Hu3DModelScaleSet(lbl_1_bss_5C[character][j], 1.1f, 1.1f, 1.1f);
            Hu3DAnimCreate(lbl_1_bss_E4[character][0], lbl_1_bss_5C[character][j], "ys22");
            Hu3DModelAttrSet(lbl_1_bss_5C[character][j], 1);
        }
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_144[i] = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x16) + i);
    }
    lbl_1_bss_52 = HuSprGrpCreate(4);
    for (i = 0; i < 4; i++) {
        sprite = HuSprCreate(lbl_1_bss_144[lbl_1_bss_42[i]], i, 0);
        HuSprGrpMemberSet(lbl_1_bss_52, i, sprite);
        HuSprPosSet(lbl_1_bss_52, i, lbl_1_data_3F8[(i * 2)], lbl_1_data_3F8[(i * 2) + 1]);
        fn_1_3B50(lbl_1_bss_CE[(i * 2)], GWStarsGet(lbl_1_bss_4A[i]));
        fn_1_3B50(lbl_1_bss_CE[(i * 2) + 1], BoardPlayerCoinsGet(lbl_1_bss_4A[i]));
        character = GWPlayerCfg[lbl_1_bss_4A[i]].character;
        Hu3D2Dto3D(&lbl_1_data_408[i], 1, &pos);
        Hu3DModelPosSetV(lbl_1_bss_5C[character][lbl_1_bss_42[i]], &pos);
        Hu3DModelAttrReset(lbl_1_bss_5C[character][lbl_1_bss_42[i]], 1);
    }
    for (i = 4; i <= 11; i++) {
        Hu3D2Dto3D(&lbl_1_data_0[i].pos, 1, &pos);
        Hu3DModelPosSetV(lbl_1_bss_1A9C[i], &pos);
        Hu3D3Dto2D(&pos, 1, &pos);
    }
    model = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x04));
    for (i = 0; i < 4; i++) {
        j = Hu3DModelLink(model);
        lbl_1_bss_168[i] = j;
        pos = lbl_1_data_408[i];
        pos.x += 5.0f;
        pos.y += 3.0f;
        pos.z += 200.0f;
        Hu3D2Dto3D(&pos, 1, &pos);
        Hu3DModelPosSetV(j, &pos);
        Hu3DModelScaleSet(j, 1.5f, 1.5f, 1.5f);
    }
    Hu3DModelAttrSet(model, 1);
    model = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x07));
    for (i = 0; i < 8; i++) {
        j = Hu3DModelLink(model);
        lbl_1_bss_158[i] = j;
        pos = lbl_1_data_0[i + 4].pos;
        pos.x += 5.0f;
        pos.y += 3.0f;
        pos.z += 200.0f;
        Hu3D2Dto3D(&pos, 1, &pos);
        Hu3DModelPosSetV(j, &pos);
        Hu3DModelScaleSet(j, 1.5f, 1.5f, 1.5f);
    }
    Hu3DModelAttrSet(model, 1);
    lbl_1_bss_E0 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x1C));
    lbl_1_bss_9C = HuSprGrpCreate(4);
    for (i = 0; i < 4; i++) {
        sprite = HuSprCreate(lbl_1_bss_E0, i, 0);
        HuSprGrpMemberSet(lbl_1_bss_9C, i, sprite);
        HuSprScaleSet(lbl_1_bss_9C, i, 0.0f, 0.0f);
        HuSprPosSet(lbl_1_bss_9C, i, lbl_1_data_408[i].x - 4.0f, lbl_1_data_408[i].y - 35.0f);
        HuSprAttrSet(lbl_1_bss_9C, i, 4);
    }
    group = HuSprGrpCreate(4);
    lbl_1_bss_170 = group;
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3F));
    sprite = HuSprCreate(anim, 100, 0);
    HuSprGrpMemberSet(group, 0, sprite);
    HuSprAttrSet(group, 0, 4);
    HuSprDrawNoSet(group, 0, 127);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x40));
    sprite = HuSprCreate(anim, 90, 0);
    HuSprGrpMemberSet(group, 1, sprite);
    HuSprAttrSet(group, 1, 4);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x41));
    sprite = HuSprCreate(anim, 80, 0);
    HuSprGrpMemberSet(group, 2, sprite);
    HuSprAttrSet(group, 2, 4);
    HuSprDrawNoSet(group, 2, 127);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x42));
    sprite = HuSprCreate(anim, 80, 0);
    HuSprGrpMemberSet(group, 3, sprite);
    HuSprAttrSet(group, 3, 4);
    HuSprDrawNoSet(group, 3, 127);
    (void)sprite;
}

void fn_1_1F4C(void)
{
    float temp_f31;
    float temp_f30;

    s16 i;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s32 status;
    s32 temp_r26;
    s32 sp24[4];
    float sp14[4];
    s16 sp8[5];

    fn_1_423C(sp8);
    for (i = 0; i < 4; i++) {
        fn_1_3CAC(lbl_1_bss_3A[i], sp8[lbl_1_bss_4A[i]]);
        sp24[i] = 0;
    }
    temp_r29 = (lbl_1_bss_174) ? 3 : 10;
    for (temp_r30 = 0; temp_r30 <= temp_r29; temp_r30++) {
        temp_f31 = sin(M_PI * ((90.0 / temp_r29) * temp_r30) / 180.0);
        for (i = 0; i < 4; i++) {
            HuSprGrpScaleSet(lbl_1_bss_3A[i], temp_f31, temp_f31);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuSprGrpScaleSet(lbl_1_bss_3A[i], 1.0f, 1.0f);
    }
    for (temp_r28 = 0; temp_r28 <= 14;) {
        for (i = 0; i < 4; i++) {
            if (GWPlayerCoinWinGet(lbl_1_bss_4A[i]) >= 10) {
                HuSprAttrReset(lbl_1_bss_9C, i, 4);
            }
            HuSprScaleSet(lbl_1_bss_9C, i, sin(M_PI * ((120.0f / 14.0f) * temp_r28) / 180.0) * (0.8 * (1.0 / sin((M_PI * 2) / 3))),
                0.8 * (sin(M_PI * ((120.0f / 14.0f) * temp_r28) / 180.0) * (1.0 / sin((M_PI * 2) / 3))));
        }
        temp_r28 += (lbl_1_bss_174) ? 2 : 1;
        HuPrcVSleep();
    }
    if (!lbl_1_bss_174) {
        HuPrcSleep(15);
    }
    for (i = 0; i < 4; i++) {
        sp14[i] = 0.0f;
    }
    for (i = temp_r30 = 0; i < 4; i++) {
        temp_r30 += sp8[i];
    }
    status = -1;
    if (temp_r30) {
        status = HuAudFXPlay(23);
    }
    temp_r30 = 0;
    temp_f30 = temp_r30;
    temp_r30 = 0;
    while (1) {
        temp_r26 = 0;
        temp_f30 += (lbl_1_bss_174) ? 1.0f : 0.2f;
        temp_r30 = temp_f30;
        for (i = temp_r29 = 0; i < 4; i++) {
            if (sp8[lbl_1_bss_4A[i]] - temp_r30 <= 0) {
                if (!sp24[lbl_1_bss_4A[i]] && sp8[lbl_1_bss_4A[i]] != 0) {
                    sp24[lbl_1_bss_4A[i]] = 1;
                    if (!temp_r26) {
                        HuAudFXPlay(9);
                        temp_r26 = 1;
                    }
                }

                temp_r29++;
                fn_1_3CAC(lbl_1_bss_3A[i], 0);
                fn_1_3B50(lbl_1_bss_CE[(i * 2) + 1], sp8[lbl_1_bss_4A[i]] + BoardPlayerCoinsGet(lbl_1_bss_4A[i]));
                if (!sp14[i]) {
                    continue;
                }
                sp14[i] += 20.0f;
                if (sp14[i] >= 360.0f) {
                    sp14[i] -= 360.0f;
                }
                Hu3DModelRotSet(lbl_1_bss_1A9C[i + 8], 0.0f, sp14[i], 0.0f);
            }
            else {
                fn_1_3CAC(lbl_1_bss_3A[i], sp8[lbl_1_bss_4A[i]] - temp_r30);
                fn_1_3B50(lbl_1_bss_CE[(i * 2) + 1], (s32)temp_r30 + BoardPlayerCoinsGet(lbl_1_bss_4A[i]));
                sp14[i] += 20.0f;
                if (sp14[i] >= 360.0f) {
                    sp14[i] -= 360.0f;
                }
                Hu3DModelRotSet(lbl_1_bss_1A9C[i + 8], 0.0f, sp14[i], 0.0f);
            }
        }
        if (temp_r29 == 4) {
            break;
        }
        HuPrcVSleep();
    }
    if (status != -1) {
        HuAudFXStop(status);
    }
    temp_r29 = 0;
    while (1) {
        for (i = temp_r30 = 0; i < 4; i++) {
            if (sp14[i]) {
                sp14[i] += 20.0f;
                if (sp14[i] >= 360.0f) {
                    sp14[i] -= 360.0f;
                }
                Hu3DModelRotSet(lbl_1_bss_1A9C[i + 8], 0.0f, sp14[i], 0.0f);
            }
            else {
                temp_r30++;
            }
        }
        if (temp_r30 >= 4) {
            break;
        }
        HuPrcVSleep();
        temp_r29++;
    }
    if (temp_r29 < 30) {
        HuPrcSleep(30 - temp_r29);
    }
    temp_r29 = (lbl_1_bss_174) ? 3 : 10;
    for (temp_r30 = 0; temp_r30 <= temp_r29; temp_r30++) {
        temp_f31 = cos(M_PI * ((90.0 / temp_r29) * temp_r30) / 180.0);
        for (i = 0; i < 4; i++) {
            HuSprGrpScaleSet(lbl_1_bss_3A[i], temp_f31, temp_f31);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuSprGrpScaleSet(lbl_1_bss_3A[i], 0.0f, 0.0f);
    }
}

void fn_1_2ADC(void)
{
    float temp_f31;
    s16 i;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    float sp54[4];
    Vec sp48;
    s32 sp38[4] = { -1, -1, -1, -1 };
    s16 sp30[4];
    s16 sp28[4];
    s16 sp20[4];
    s16 sp18[4];
    s16 sp10[4];
    s16 sp8[4];
    for (i = 0; i < 4; i++) {
        sp30[i] = sp28[i] = lbl_1_bss_4A[i];
        sp18[i] = sp20[i] = lbl_1_bss_42[i];
        sp10[i] = BoardPlayerCoinsGet(lbl_1_bss_4A[i]);
        sp8[i] = GWStarsGet(lbl_1_bss_4A[i]);
    }
    fn_1_3E08();
    for (i = 0; i < 4; i++) {
        if (sp30[i] != lbl_1_bss_4A[i] || sp18[i] != lbl_1_bss_42[i]) {
            break;
        }
    }
    if (i == 4) {
        lbl_1_bss_0 = 1;
        return;
    }
    lbl_1_data_380 = HuSprGrpCreate(4);
    for (i = 0; i < 4; i++) {
        temp_r24 = HuSprCreate(lbl_1_bss_144[lbl_1_bss_42[i]], i, 0);
        HuSprGrpMemberSet(lbl_1_data_380, i, temp_r24);
        HuSprPosSet(lbl_1_data_380, i, lbl_1_data_3F8[(i * 2)], lbl_1_data_3F8[(i * 2) + 1]);
        HuSprAttrSet(lbl_1_data_380, i, 4);
        temp_r30 = GWPlayerCfg[lbl_1_bss_4A[i]].character;
        lbl_1_bss_54[i] = lbl_1_bss_A[i] = Hu3DModelLink(lbl_1_bss_5C[temp_r30][lbl_1_bss_42[i]]);
        Hu3D2Dto3D(&lbl_1_data_408[i], 1, &sp48);
        Hu3DModelPosSetV(lbl_1_bss_A[i], &sp48);
        if (sp30[i] == lbl_1_bss_4A[i] && sp18[i] == lbl_1_bss_42[i]) {
            Hu3DModelAttrSet(lbl_1_bss_5C[temp_r30][sp18[i]], 1);
            Hu3DModelAttrReset(lbl_1_bss_A[i], 1);
            Hu3DModelScaleSet(lbl_1_bss_A[i], 1.1f, 1.1f, 1.1f);
        }
        else {
            Hu3DModelAttrSet(lbl_1_bss_A[i], 1);
        }
    }
    for (i = 0; i < 4; i++) {
        sp54[i] = 0;
    }
    temp_r25 = 0;
    temp_r28 = 0;
    while (1) {
        for (temp_r26 = i = 0; i < 4; i++) {
            if (sp30[i] == lbl_1_bss_4A[i] && sp18[i] == lbl_1_bss_42[i]) {
                temp_r26++;
                fn_1_3B50(lbl_1_bss_CE[(i * 2)], GWStarsGet(lbl_1_bss_4A[i]));
                fn_1_3B50(lbl_1_bss_CE[(i * 2) + 1], BoardPlayerCoinsGet(lbl_1_bss_4A[i]));
            }
            else {
                if (temp_r28 > (i * 20)) {
                    temp_r27 = temp_r28 - (i * 20);
                    if (temp_r27 <= 20) {
                        if (temp_r27 <= 10) {
                            HuSprScaleSet(lbl_1_bss_52, i, 1.0f, cos(M_PI * (9.0f * temp_r27) / 180.0));
                        }
                        else {
                            HuSprAttrSet(lbl_1_bss_52, i, 4);
                            HuSprAttrReset(lbl_1_data_380, i, 4);
                            HuSprScaleSet(lbl_1_data_380, i, 1.0f, sin(M_PI * (9.0f * (temp_r27 - 10)) / 180.0));
                        }
                        temp_f31 = temp_r27 / 20.0f;
                        temp_r29 = GWStarsGet(sp28[i]) + (temp_f31 * (GWStarsGet(lbl_1_bss_4A[i]) - GWStarsGet(sp28[i])));
                        fn_1_3B50(lbl_1_bss_CE[(i * 2)], temp_r29);
                        temp_r29 = BoardPlayerCoinsGet(sp28[i]) + (temp_f31 * (BoardPlayerCoinsGet(lbl_1_bss_4A[i]) - BoardPlayerCoinsGet(sp28[i])));
                        fn_1_3B50(lbl_1_bss_CE[(i * 2) + 1], temp_r29);
                    }
                    else {
                        temp_r30 = GWPlayerCfg[sp28[i]].character;
                        Hu3DModelAttrSet(lbl_1_bss_5C[temp_r30][sp18[i]], 1);
                        temp_r30 = GWPlayerCfg[lbl_1_bss_4A[i]].character;
                        Hu3DModelAttrReset(lbl_1_bss_A[i], 1);
                        Hu3DModelScaleSet(lbl_1_bss_A[i], 1.1f, 1.1f, 1.1f);
                        fn_1_3B50(lbl_1_bss_CE[(i * 2)], GWStarsGet(lbl_1_bss_4A[i]));
                        fn_1_3B50(lbl_1_bss_CE[(i * 2) + 1], BoardPlayerCoinsGet(lbl_1_bss_4A[i]));
                        for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                            if (sp28[temp_r29] == lbl_1_bss_4A[i]) {
                                break;
                            }
                        }
                        if (lbl_1_bss_42[i] != sp20[temp_r29]) {
                            if (lbl_1_bss_42[i] < sp20[temp_r29]) {
                                Hu3DAnimCreate(lbl_1_bss_E4[temp_r30][1], lbl_1_bss_5C[temp_r30][lbl_1_bss_42[i]], "ys22");
                            }
                            else {
                                Hu3DAnimCreate(lbl_1_bss_E4[temp_r30][2], lbl_1_bss_5C[temp_r30][lbl_1_bss_42[i]], "ys22");
                            }
                            if (lbl_1_bss_42[i] == 0) {
                                sp38[lbl_1_bss_4A[i]] = HuAudPlayerVoicePlay(lbl_1_bss_4A[i], 293);
                            }
                            if (!temp_r25) {
                                temp_r25 = 1;
                                HuAudFXPlay(27);
                            }
                        }
                        sp30[i] = lbl_1_bss_4A[i];
                        sp18[i] = lbl_1_bss_42[i];
                    }
                }
                sp54[i] += 20.0f;
                if (sp54[i] >= 360.0f) {
                    sp54[i] -= 360.0f;
                }
                temp_r30 = GWPlayerCfg[sp28[i]].character;
                Hu3DModelRotSet(lbl_1_bss_5C[temp_r30][sp18[i]], sp54[i] / (4 - i), sp54[i], 0.0f);
            }
        }
        if (temp_r28 <= 10) {
            for (i = 0; i < 4; i++) {
                HuSprScaleSet(lbl_1_bss_9C, i, cos(M_PI * (9.0f * temp_r28) / 180.0), cos(M_PI * (9.0f * temp_r28) / 180.0));
            }
        }
        else {
            for (i = 0; i < 4; i++) {
                HuSprScaleSet(lbl_1_bss_9C, i, 0.0f, 0.0f);
            }
        }
        if (temp_r26 >= 4) {
            break;
        }
        if (lbl_1_bss_174) {
            temp_r28 += 2;
        }
        HuPrcVSleep();
        temp_r28++;
    }
    for (i = 0; i < 4; i++) {
        HuSprScaleSet(lbl_1_bss_9C, i, 0.0f, 0.0f);
    }
    lbl_1_bss_0 = 1;
}

void fn_1_3B50(s16 group, s16 value)
{
    s16 digit;
    s16 digit_value;
    if (value > 999) {
        value = 999;
    }
    digit = 0;
    digit_value = value / 100;
    if (digit_value != 0) {
        HuSprBankSet(group, digit, digit_value);
        HuSprAttrReset(group, digit, 4);
        digit++;
    }
    value -= digit_value * 100;
    digit_value = value / 10;
    if (digit_value != 0 || digit == 1) {
        HuSprBankSet(group, digit, digit_value);
        HuSprAttrReset(group, digit, 4);
        digit++;
    }
    value -= digit_value * 10;
    HuSprBankSet(group, digit, value);
    HuSprAttrReset(group, digit, 4);
    digit++;
    for (digit_value = digit; digit_value < 3; digit_value++) {
        HuSprAttrSet(group, digit_value, 4);
    }
}

void fn_1_3CAC(s16 group, s16 value)
{
    s16 digit;
    s16 digit_value;
    if (value > 999) {
        value = 999;
    }
    digit = 2;
    digit_value = value / 100;
    if (digit_value != 0) {
        HuSprBankSet(group, digit, digit_value);
        HuSprAttrReset(group, digit, 4);
        digit++;
    }
    value -= digit_value * 100;
    digit_value = value / 10;
    if (digit_value != 0 || digit == 3) {
        HuSprBankSet(group, digit, digit_value);
        HuSprAttrReset(group, digit, 4);
        digit++;
    }
    value -= digit_value * 10;
    HuSprBankSet(group, digit, value);
    HuSprAttrReset(group, digit, 4);
    digit++;
    for (digit_value = digit; digit_value < 5; digit_value++) {
        HuSprAttrSet(group, digit_value, 4);
    }
}

void fn_1_3E08(void)
{
    s16 i;
    s16 j;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_42[i] = BoardPlayerRankCalc(i);
        lbl_1_bss_4A[i] = i;
    }
    for (j = 1; j < 4; j++) {
        for (i = 0; i < 4 - j; i++) {
            if (lbl_1_bss_42[i] > lbl_1_bss_42[i + 1]) {
                s16 temp = lbl_1_bss_42[i];
                lbl_1_bss_42[i] = lbl_1_bss_42[i + 1];
                lbl_1_bss_42[i + 1] = temp;
                temp = lbl_1_bss_4A[i];
                lbl_1_bss_4A[i] = lbl_1_bss_4A[i + 1];
                lbl_1_bss_4A[i + 1] = temp;
            }
        }
    }
}

s32 lbl_1_data_450[] = { DATADIR_W01, DATADIR_W02, DATADIR_W03, DATADIR_W04, DATADIR_W05, DATADIR_W06 };

void fn_1_3FD8(void)
{
    s32 status;
    u32 ardma;
    if (!_CheckFlag(0x10000)) {
        lbl_1_bss_178 = 1;
        HuPrcEnd();
        while (1) {
            HuPrcVSleep();
        }
    }
    status = HuDataDirReadAsync(DATADIR_BOARD);
    if (status != -1) {
        while (!HuDataGetAsyncStat(status)) {
            HuPrcVSleep();
        }
    }
    ardma = HuAR_MRAMtoARAM(DATADIR_BOARD);
    if (ardma) {
        while (HuARDMACheck()) {
            HuPrcVSleep();
        }
    }
    HuDataDirClose(DATADIR_BOARD);
    status = HuDataDirReadAsync(lbl_1_data_450[GWSystem.board]);
    if (status != -1) {
        while (!HuDataGetAsyncStat(status)) {
            HuPrcVSleep();
        }
    }
    lbl_1_bss_178 = 1;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_40DC(void)
{
    s16 i;
    s16 sp8[5];
    fn_1_423C(sp8);
    sp8[lbl_1_bss_172] += sp8[4];
    for (i = 0; i < 4; i++) {
        GWCoinsAdd(i, sp8[i]);
        GWPlayerCoinWinSet(i, 0);
        GWPlayerCoinCollectSet(i, 0);
        if (mgInfoTbl[GWSystem.mg_next].type != 4) {
            GWPlayer[i].coins_mg += sp8[i];
            if (GWPlayer[i].coins_mg > 9999) {
                GWPlayer[i].coins_mg = 9999;
            }
        }
    }
}

void fn_1_423C(s16 *data)
{
    s16 i;
    s32 coin;
    u32 mul_coin;
    u32 coin_battle;
    s16 temp_r26;
    s16 mgtype;
    float sp10[4];
    s16 sp8[4];
    mgtype = mgInfoTbl[GWSystem.mg_next].type;
    switch (mgtype) {
        case 4:
            temp_r26 = 0;
            for (i = coin_battle = 0; i < 4; i++) {
                coin_battle += GWPlayerCoinBattleGet(i);
            }
            sp8[0] = sp8[1] = sp8[2] = sp8[3] = 0;
            for (i = 0; i < 4; i++) {
                sp8[GWPlayerCoinWinGet(i)]++;
            }
            sp10[0] = sp10[1] = sp10[2] = sp10[3] = 0;
            if (sp8[0] == 1 && sp8[1] == 1 && sp8[2] == 1) {
                sp10[0] = 0.7f;
                sp10[1] = 0.3f;
            }
            else if (sp8[0] == 2) {
                sp10[0] = 0.5f;
            }
            else if (sp8[0] == 3) {
                sp10[0] = 0.3333333f;
            }
            else if (sp8[0] == 1 && sp8[1] == 2) {
                sp10[0] = 0.6f;
                sp10[1] = 0.2f;
            }
            else if (sp8[0] == 1 && sp8[1] == 3) {
                sp10[0] = 0.7f;
                sp10[1] = 0.1f;
            }
            else if (sp8[0] == 1 && sp8[1] == 1 && sp8[2] == 2) {
                sp10[0] = 0.7f;
                sp10[1] = 0.3f;
            }
            else if (sp8[0] == 4) {
                sp10[0] = 0.25f;
            }
            else {
                temp_r26 = 1;
            }
            for (i = coin = 0; i < 4; i++) {
                if (!temp_r26) {
                    mul_coin = coin_battle * sp10[GWPlayerCoinWinGet(i)];
                }
                else {
                    mul_coin = GWPlayerCoinBattleGet(i);
                }
                data[i] = mul_coin;
                coin += mul_coin;
            }
            if (coin < coin_battle) {
                data[4] = coin_battle - coin;
            }
            else {
                data[4] = 0;
            }
            break;

        default:
            for (i = 0; i < 4; i++) {
                coin = GWPlayerCoinWinGet(i) + GWPlayerCoinCollectGet(i);
                mul_coin = GWLuckyValueGet();
                if (mul_coin == 0) {
                    mul_coin = 1;
                }
                coin *= mul_coin;
                data[i] = coin;
            }
            break;
    }
}

void fn_1_461C(void)
{
    s16 sprite;
    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    espInit();
    HuPrcVSleep();
    sprite = espEntry(0x860020, 5000, 0);
    espPosSet(sprite, 288.0, 240.0);
    espAttrReset(sprite, 4);
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    if (GWSaveModeGet() == 2) {
        GWSaveModeSet(1);
    }
    if (GWPartyGet() == 1) {
        GWGameStat.party_continue = 1;
        SLSaveBoard();
    }
    else {
        GWGameStat.story_continue = 1;
        SLSaveBoardStory();
    }
    SLCommonSet();
    if (SLSave()) {
        saveExecF = 1;
    }
    else {
        GWSaveModeSet(1);
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
}

s32 lbl_1_data_468[] = { DATADIR_MARIOMDL1, DATADIR_LUIGIMDL1, DATADIR_PEACHMDL1, DATADIR_YOSHIMDL1, DATADIR_WARIOMDL1, DATADIR_DONKEYMDL1,
    DATADIR_DAISYMDL1, DATADIR_WALUIGIMDL1 };

Vec lbl_1_data_488[] = {
    { 160, 185, 500 },
    { 240, 185, 500 },
    { 160, 355, 500 },
    { 240, 355, 500 },
};

void fn_1_47FC(void)
{
    s16 temp_r31;
    s16 temp_r24;
    s16 temp_r21;
    s16 temp_r20;
    s16 temp_r19;
    s16 temp_r18;
    s16 temp_r17;
    Vec sp40;
    Vec sp34;
    s16 sp2C[4];
    s16 sp28[2];
    s16 sp24[2];
    s16 sp20[2];
    s16 sp1C[2];
    s16 sp18[2];
    AnimData *sp14;
    s32 sp10;
    s16 spC;
    s16 spA;
    s16 sp8;
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    espAttrSet(lbl_1_bss_1A1A[0], 4);
    espAttrSet(lbl_1_bss_1A1A[1], 4);
    for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
        Hu3DModelAttrSet(lbl_1_bss_1A9C[temp_r31 + 6], 1);
        Hu3DModelAttrSet(lbl_1_bss_1A9C[temp_r31 + 10], 1);
    }
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        espAttrSet(lbl_1_bss_1A1A[temp_r31 + 6], 4);
    }
    for (temp_r31 = 4; temp_r31 < 8; temp_r31++) {
        Hu3DModelAttrSet(lbl_1_bss_158[temp_r31], 1);
    }
    for (temp_r31 = 4; temp_r31 < 8; temp_r31++) {
        HuSprGrpTPLvlSet(lbl_1_bss_CE[temp_r31], 0.0f);
    }
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        for (temp_r19 = 0; temp_r19 < 4; temp_r19++) {
            Hu3DModelAttrSet(lbl_1_bss_5C[GWPlayerCfg[temp_r31].character][temp_r19], 1);
        }
        Hu3DModelAttrSet(lbl_1_bss_54[temp_r31], 1);
    }
    HuSprGrpKill(lbl_1_bss_9C);
    HuSprGrpKill(lbl_1_bss_52);
    if (lbl_1_data_380 != -1) {
        HuSprGrpKill(lbl_1_data_380);
    }
    sp28[0] = sp28[1] = 0;
    sp24[0] = sp24[1] = 0;
    sp1C[0] = 0;
    sp1C[1] = 2;
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r17 = GWPlayer[temp_r31].team;
        sp28[temp_r17] += BoardPlayerCoinsGet(temp_r31);
        sp24[temp_r17] += GWStarsGet(temp_r31);
        sp2C[sp1C[temp_r17]++] = GWPlayerCfg[temp_r31].character;
    }
    sp18[0] = 0;
    sp18[1] = 1;
    if (sp24[0] > sp24[1]) {
        lbl_1_bss_8 = 0;
    }
    else {
        if (sp24[0] == sp24[1]) {
            if (sp28[0] > sp28[1]) {
                lbl_1_bss_8 = 0;
            }
            else if (sp28[0] == sp28[1]) {
                sp18[0] = sp18[1] = 0;
                lbl_1_bss_8 = 0;
            }
            else {
                lbl_1_bss_8 = 1;
            }
        }
        else {
            lbl_1_bss_8 = 1;
        }
    }
    HuSprAttrReset(lbl_1_bss_170, 0, 4);
    HuSprAttrReset(lbl_1_bss_170, 1, 4);
    HuSprPosSet(lbl_1_bss_170, 1, 0, -180);
    HuSprAttrReset(lbl_1_bss_170, 2, 4);
    HuSprAttrReset(lbl_1_bss_170, 3, 4);
    if (lbl_1_bss_8 == 0) {
        sp20[0] = -55;
        sp20[1] = 115;
    }
    else {
        sp20[0] = 115;
        sp20[1] = -55;
        temp_r24 = sp2C[0];
        sp2C[0] = sp2C[2];
        sp2C[2] = temp_r24;
        temp_r24 = sp2C[1];
        sp2C[1] = sp2C[3];
        sp2C[3] = temp_r24;
        temp_r24 = sp28[0];
        sp28[0] = sp28[1];
        sp28[1] = temp_r24;
        temp_r24 = sp24[0];
        sp24[0] = sp24[1];
        sp24[1] = temp_r24;
    }
    HuSprPosSet(lbl_1_bss_170, 2, 0, sp20[0]);
    HuSprPosSet(lbl_1_bss_170, 3, 0, sp20[1]);
    HuSprGrpPosSet(lbl_1_bss_170, 288, 240);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        if (temp_r31 < 2) {
            sp10 = 0;
        }
        else {
            sp10 = 1;
        }
        temp_r18 = lbl_1_bss_5C[sp2C[temp_r31]][sp10];
        Hu3DAnimCreate(lbl_1_bss_E4[sp2C[temp_r31]][0], temp_r18, "ys22");
        Hu3DModelAttrReset(temp_r18, 1);
        Hu3D2Dto3D(&lbl_1_data_488[temp_r31], 1, &sp40);
        Hu3DModelPosSetV(temp_r18, &sp40);
        Hu3DModelRotSet(temp_r18, 0, 0, 0);
        sp34 = lbl_1_data_488[temp_r31];
        sp34.y += 5.0f;
        sp34.x += 3.0f;
        sp34.z += 200.0f;
        Hu3D2Dto3D(&sp34, 1, &sp40);
        Hu3DModelPosSetV(lbl_1_bss_168[temp_r31], &sp40);
    }
    spC = HuSprGrpCreate(2);
    for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
        sp14 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x16) + sp18[temp_r31]);
        spA = HuSprCreate(sp14, temp_r31, 0);
        HuSprGrpMemberSet(spC, temp_r31, spA);
        HuSprPosSet(spC, temp_r31, (lbl_1_data_488[temp_r31 * 2].x) - 80.0f, lbl_1_data_488[temp_r31 * 2].y);
        sp34 = lbl_1_data_488[temp_r31 * 2];
        sp34.x += 180.0f;
        sp34.y -= 35.0f;
        Hu3D2Dto3D(&sp34, 1, &sp40);
        Hu3DModelPosSetV(lbl_1_bss_1A9C[temp_r31 + 4], &sp40);
        sp34.y += 5.0f;
        sp34.x += 3.0f;
        sp34.z += 200.0f;
        Hu3D2Dto3D(&sp34, 1, &sp40);
        Hu3DModelPosSetV(lbl_1_bss_158[temp_r31 * 2], &sp40);
        espPosSet(lbl_1_bss_1A1A[(temp_r31 * 2) + 2], 230.0f + lbl_1_data_488[temp_r31 * 2].x, lbl_1_data_488[temp_r31 * 2].y - 35.0f);
        fn_1_3B50(lbl_1_bss_CE[temp_r31 * 2], sp24[temp_r31]);
        HuSprGrpPosSet(lbl_1_bss_CE[temp_r31 * 2], 320.0f + lbl_1_data_488[temp_r31 * 2].x, lbl_1_data_488[temp_r31 * 2].y - 35.0f);
        sp34 = lbl_1_data_488[temp_r31 * 2];
        sp34.x += 180.0f;
        sp34.y += 35.0f;
        Hu3D2Dto3D(&sp34, 1, &sp40);
        Hu3DModelPosSetV(lbl_1_bss_1A9C[temp_r31 + 8], &sp40);
        sp34.y += 5.0f;
        sp34.x += 3.0f;
        sp34.z += 200.0f;
        Hu3D2Dto3D(&sp34, 1, &sp40);
        Hu3DModelPosSetV(lbl_1_bss_158[(temp_r31 * 2) + 1], &sp40);
        espPosSet(lbl_1_bss_1A1A[(temp_r31 * 2) + 3], 230.0f + lbl_1_data_488[temp_r31 * 2].x, 35.0f + lbl_1_data_488[temp_r31 * 2].y);
        fn_1_3B50(lbl_1_bss_CE[(temp_r31 * 2) + 1], sp28[temp_r31]);
        HuSprGrpPosSet(lbl_1_bss_CE[(temp_r31 * 2) + 1], 320.0f + lbl_1_data_488[temp_r31 * 2].x, 35.0f + lbl_1_data_488[temp_r31 * 2].y);
    }
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    temp_r21 = HuWinCreate(-10000.0f, 400.0f, 320, 40, 0);
    HuWinMesSpeedSet(temp_r21, 0);
    HuWinBGTPLvlSet(temp_r21, 0);
    HuWinPriSet(temp_r21, 5);
    HuWinAttrSet(temp_r21, 0x800);
    HuWinMesSet(temp_r21, MAKE_MESSID(0x24, 0x07));
    HuPrcSleep(4);
    temp_r31 = 0;
    while (1) {
        if (lbl_1_bss_4 && temp_r31 > 120) {
            break;
        }
        for (temp_r20 = sp8 = 0; temp_r20 < 4; temp_r20++) {
            if (!GWPlayerCfg[temp_r20].iscom) {
                sp8 |= HuPadBtnDown[GWPlayerCfg[temp_r20].pad_idx];
            }
        }
        if (sp8 & PAD_BUTTON_A) {
            HuAudFXPlay(28);
            break;
        }
        HuPrcVSleep();
        temp_r31++;
    }
    HuWinKill(temp_r21);
}

void fn_1_5880(omObjData *object)
{
    Vec pos;
    Vec offset;
    Vec dir;
    Vec y_offset;

    f32 z_rot;
    s8 stick_pos;

    if (HuPadBtn[0] & PAD_BUTTON_UP) {
        CRot.x += 2.0f;
    }
    if (HuPadBtn[0] & PAD_BUTTON_DOWN) {
        CRot.x -= 2.0f;
    }
    if (HuPadBtn[0] & PAD_BUTTON_LEFT) {
        CRot.y += 2.0f;
    }
    if (HuPadBtn[0] & PAD_BUTTON_RIGHT) {
        CRot.y -= 2.0f;
    }
    if (HuPadBtnDown[0] & PAD_BUTTON_B) {
        OSReport("CRot   %f,%f,%f\n", CRot.x, CRot.y, CRot.z);
        OSReport("Center %f,%f,%f\n", Center.x, Center.y, Center.z);
        OSReport("CZoom  %f\n", CZoom);
    }

    CZoom += HuPadTrigL[0] / 2;
    CZoom -= HuPadTrigR[0] / 2;

    pos.x = Center.x + (CZoom * (sin((M_PI * CRot.y) / 180.0) * cos((M_PI * CRot.x) / 180.0)));
    pos.y = (Center.y + (CZoom * -sin((M_PI * CRot.x) / 180.0)));
    pos.z = (Center.z + (CZoom * (cos((M_PI * CRot.y) / 180.0) * cos((M_PI * CRot.x) / 180.0))));
    offset.x = Center.x - pos.x;
    offset.y = Center.y - pos.y;
    offset.z = Center.z - pos.z;
    dir.x = (sin((M_PI * CRot.y) / 180.0) * sin((M_PI * CRot.x) / 180.0));
    dir.y = cos((M_PI * CRot.x) / 180.0);
    dir.z = (cos((M_PI * CRot.y) / 180.0) * sin((M_PI * CRot.x) / 180.0));
    z_rot = CRot.z;
    y_offset.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * cos((M_PI * z_rot) / 180.0))
        + dir.y * (offset.x * offset.y * (1.0f - cos((M_PI * z_rot) / 180.0)) - offset.z * sin((M_PI * z_rot) / 180.0))
        + dir.z * (offset.x * offset.z * (1.0f - cos((M_PI * z_rot) / 180.0)) + offset.y * sin((M_PI * z_rot) / 180.0));

    y_offset.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * cos((M_PI * z_rot) / 180.0))
        + dir.x * (offset.x * offset.y * (1.0f - cos((M_PI * z_rot) / 180.0)) + offset.z * sin((M_PI * z_rot) / 180.0))
        + dir.z * (offset.y * offset.z * (1.0f - cos((M_PI * z_rot) / 180.0)) - offset.x * sin((M_PI * z_rot) / 180.0));

    y_offset.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * cos((M_PI * z_rot) / 180.0))
        + (dir.x * (offset.x * offset.z * (1.0 - cos((M_PI * z_rot) / 180.0)) - offset.y * sin((M_PI * z_rot) / 180.0))
        +  dir.y * (offset.y * offset.z * (1.0 - cos((M_PI * z_rot) / 180.0)) + offset.x * sin((M_PI * z_rot) / 180.0)));

	VECCrossProduct(&dir, &offset, &offset);
	VECNormalize(&offset, &offset);
	stick_pos = (HuPadSubStkX[0] & 0xF8);
	if (stick_pos != 0) {
		Center.x += 0.05f * (offset.x * stick_pos);
		Center.y += 0.05f * (offset.y * stick_pos);
		Center.z += 0.05f * (offset.z * stick_pos);
	}
	VECNormalize(&y_offset, &offset);
	stick_pos = -(HuPadSubStkY[0] & 0xF8);
	if (stick_pos != 0) {
		Center.x += 0.05f * (offset.x * stick_pos);
		Center.y += 0.05f * (offset.y * stick_pos);
		Center.z += 0.05f * (offset.z * stick_pos);
	}
}

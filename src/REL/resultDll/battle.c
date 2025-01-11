#include "dolphin.h"
#include "ext_math.h"

#include "game/armem.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "game/gamework_data.h"

#include "REL/resultdll.h"

DataListModel lbl_1_data_4E8[] = { { DATA_MAKE_NUM(DATADIR_RESULT, 0x08), 0, 0, -1, -1, { -300, 0, 0 }, { 0, 0, 0 }, { 0.9f, 0.9f, 0.9f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x09), 0, 0, -1, -1, { -100, 0, 0 }, { 0, 0, 0 }, { 0.9f, 0.9f, 0.9f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0A), 0, 0, -1, -1, { 100, 0, 0 }, { 0, 0, 0 }, { 0.9f, 0.9f, 0.9f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0A), 0, 0, -1, -1, { 300, 0, 0 }, { 0, 0, 0 }, { 0.9f, 0.9f, 0.9f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0B), 0, 0, -1, -1, { -300, 1000, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0B), 0, 0, -1, -1, { -100, 1000, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0B), 0, 0, -1, -1, { 100, 1000, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0B), 0, 0, -1, -1, { 300, 1000, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0D), 0, 0, -1, -1, { 5000, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0E), 0, 1, -1, 8, { 0, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0F), 0x40000002, 0, -1, -1, { 5000, 0, 0 }, { 0, 0, 0 }, { 2.0f, 2.0f, 2.0f } },
    { -1, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } } };

DataListSprite lbl_1_data_758[] = {
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x43), 0, 10, 288, 240, { 255, 255, 255, 255 } },
    { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } },
};

HsfanimStruct00 lbl_1_data_780 = { 80, { 0, 0 }, 3, 30, 90, { 0, -0.2, 0 }, 5.0f, 0.95f, 10.0f, 0.995f, 2,
    {
        { 255, 192, 112, 255 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    {
        { 128, 128, 128, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    } };

s16 lbl_1_data_7D0[] = {
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

Vec lbl_1_data_7F0[] = { { -300, 270, 0 }, { -100, 180, 500 }, { 100, 90, 500 }, { 300, 0, 500 } };

s16 lbl_1_data_820[] = { -284, 148, -84, 233, 116, 318, 316, 403 };

s32 lbl_1_data_830[] = { DATA_MAKE_NUM(DATADIR_RESULT, 0x08), DATA_MAKE_NUM(DATADIR_RESULT, 0x09), DATA_MAKE_NUM(DATADIR_RESULT, 0x0A),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x0A) };

float lbl_1_data_840[] = { 130, 150, 170, 150, 150, 130, 170, 190 };

float lbl_1_data_860[] = { 130, 150, 180, 150, 150, 170, 180, 210 };

float lbl_1_data_880[] = { 140, 160, 180, 150, 150, 120, 180, 210 };

s16 lbl_1_data_8A0[] = { 8, 0, -8 };

typedef struct struct_unk194 {
    s16 unk0;
    s16 unk2;
    Vec unk4;
    Vec unk10;
    float unk1C;
} StructUnk194;

u8 lbl_1_bss_19F8[32];
s16 lbl_1_bss_19F0[4];
s16 lbl_1_bss_19E8[4];
s16 lbl_1_bss_19E0[4];
s16 lbl_1_bss_19B8[4][5];
s16 lbl_1_bss_19B0[4];
s16 lbl_1_bss_1990[4][4];
s16 lbl_1_bss_1828[180];
s16 lbl_1_bss_181C[6];
s16 lbl_1_bss_1814[4];
StructUnk194 lbl_1_bss_194[180];
s32 lbl_1_bss_190;

void fn_1_6760(void);
void fn_1_6824(void);
void fn_1_7544(void);

void fn_1_6490(void)
{
    s16 player;
    s16 i;
    s16 window;
    s16 button;
    Process *process = HuPrcCurrentGet();
    HuAudSeqPlay(10);
    for (i = player = 0; i < 4; i++) {
        if (GWPlayerCfg[i].iscom) {
            player++;
        }
    }
    if (player == 4) {
        lbl_1_bss_190 = 1;
    }
    else {
        lbl_1_bss_190 = 0;
    }
    fn_1_6824();
    HuPrcChildCreate(fn_1_6760, 100, 8192, 0, process);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    lbl_1_bss_178 = 0;
    HuPrcChildCreate(fn_1_3FD8, 100, 12288, 0, process);
    HuPrcSleep(10);
    if (!lbl_1_bss_174) {
        HuPrcSleep(20);
    }
    fn_1_7544();
    fn_1_40DC();
    window = HuWinCreate(-10000.0f, 400.0f, 320, 40, 0);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 0);
    HuWinAttrSet(window, 0x800);
    HuWinMesSet(window, MAKE_MESSID(0x24, 0x07));
    i = 0;
    while (1) {
        if (lbl_1_bss_190 && i > 120) {
            break;
        }
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
    HuWinKill(window);
    while (!lbl_1_bss_178) {
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
    HuAudSeqAllFadeOut(500);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    omSysPauseEnable(1);
    Hu3DParManAllKill();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_6760(void)
{
    Vec temp;
    temp.z = 0.0f;
    temp.y = 0.0f;
    temp.x = 0.0f;
    while (1) {
        if (((HuPadBtn[0] | HuPadBtn[1] | HuPadBtn[2] | HuPadBtn[3]) & 0x100) != 0 || lbl_1_bss_190 != 0) {
            lbl_1_bss_174 = 1;
        }
        else {
            lbl_1_bss_174 = 0;
        }
        HuPrcVSleep();
    }
}

void fn_1_7F98(void);
void fn_1_8338(s16 group, s16 value);
void fn_1_8484(void);
void fn_1_8658(void);
void fn_1_86DC(s16 player);
void fn_1_8CB8(struct model_data *model, Mtx matrix);

void fn_1_6824(void)
{
    s16 i;
    s16 character;
    s16 player;
    s16 x_ofs;
    AnimData *anim;
    AnimData *anim2;
    AnimData *anim3;
    s16 char_mdl;
    Vec pos;
    Vec target;
    Vec up;
    s16 gains[5];
    Process *process = HuPrcCurrentGet();
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    Center.x = 0;
    Center.y = 330;
    Center.z = 0;
    CZoom = 2210;
    Hu3DShadowCreate(20, 100, 5000);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowSizeSet(192);
    target.x = target.y = target.z = 0;
    pos.x = 500;
    pos.z = 1000;
    pos.y = 2000;
    up.x = 0;
    up.y = 1;
    up.z = 0;
    Hu3DShadowPosSet(&pos, &up, &target);
    i = Hu3DHookFuncCreate(fn_1_8CB8);
    Hu3DModelPosSet(i, 0, 0, 0);
    fn_1_8484();
    fn_1_423C(gains);
    gains[lbl_1_bss_172] += gains[4];
    for (i = 0; i < 4; i++) {
        lbl_1_data_4E8[i].datanum = lbl_1_data_830[lbl_1_bss_19E8[i]];
        if (lbl_1_bss_19E8[i] == 3) {
            lbl_1_data_4E8[i].attr = 1;
        }
    }
    fn_1_8FF8(lbl_1_data_4E8);
    fn_1_927C(lbl_1_data_758);
    espDrawNoSet(lbl_1_bss_1A1A[0], 127);
    for (i = 0; i < 4; i++) {
        Hu3DModelShadowSet(lbl_1_bss_1A9C[i]);
    }
    for (i = 0; i < 4; i++) {
        anim = HuSprAnimRead(HuDataReadNum(lbl_1_bss_19E8[i] + DATA_MAKE_NUM(DATADIR_RESULT, 0x44), MEMORY_DEFAULT_NUM));
        ;
        if (lbl_1_bss_19E8[i] <= 2) {
            anim2 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x48), MEMORY_DEFAULT_NUM));
        }
        else {
            anim2 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x48), MEMORY_DEFAULT_NUM));
        }
        Hu3DAnimCreate(anim, lbl_1_bss_1A9C[i + 4], "ys22_a0");
        Hu3DAnimCreate(anim2, lbl_1_bss_1A9C[i + 4], "ys22_a1");
        Hu3DModelAttrSet(lbl_1_bss_1A9C[i + 4], HU3D_MOTATTR_PAUSE);
    }
    anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x3D), MEMORY_DEFAULT_NUM));
    anim2 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x3B), MEMORY_DEFAULT_NUM));
    anim3 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x3C), MEMORY_DEFAULT_NUM));
    for (i = 0; i < 4; i++) {
        if (gains[lbl_1_bss_19F0[i]] >= 100) {
            x_ofs = lbl_1_data_8A0[2];
        }
        else if (gains[lbl_1_bss_19F0[i]] >= 10) {
            x_ofs = lbl_1_data_8A0[1];
        }
        else {
            x_ofs = lbl_1_data_8A0[0];
        }
        lbl_1_bss_19E0[i] = HuSprGrpCreate(5);
        lbl_1_bss_19B8[i][0] = HuSprCreate(anim, 10, 0);
        HuSprGrpMemberSet(lbl_1_bss_19E0[i], 0, lbl_1_bss_19B8[i][0]);
        HuSprPosSet(lbl_1_bss_19E0[i], 0, 17, -32);
        lbl_1_bss_19B8[i][1] = HuSprCreate(anim2, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_19E0[i], 1, lbl_1_bss_19B8[i][1]);
        HuSprPosSet(lbl_1_bss_19E0[i], 1, x_ofs, -36);
        lbl_1_bss_19B8[i][2] = HuSprCreate(anim3, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_19E0[i], 2, lbl_1_bss_19B8[i][2]);
        HuSprPosSet(lbl_1_bss_19E0[i], 2, x_ofs + 16, -36);
        lbl_1_bss_19B8[i][3] = HuSprCreate(anim3, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_19E0[i], 3, lbl_1_bss_19B8[i][3]);
        HuSprPosSet(lbl_1_bss_19E0[i], 3, x_ofs + 32, -36);
        lbl_1_bss_19B8[i][4] = HuSprCreate(anim3, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_19E0[i], 4, lbl_1_bss_19B8[i][4]);
        HuSprPosSet(lbl_1_bss_19E0[i], 4, x_ofs + 48, -36);
        HuSprGrpPosSet(lbl_1_bss_19E0[i], 0, 0);
        fn_1_8338(lbl_1_bss_19E0[i], 9);
        HuSprGrpScaleSet(lbl_1_bss_19E0[i], 0, 0);
    }
    (void)anim3;
    Hu3DMotionSet(lbl_1_bss_1A9C[8], lbl_1_bss_1A5C[9]);
    Hu3DModelAttrSet(lbl_1_bss_1A9C[8], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(lbl_1_bss_1A9C[8]);
    for (i = 0; i < 180; i++) {
        if (i == 0) {
            lbl_1_bss_1828[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x0C));
        }
        else {
            lbl_1_bss_1828[i] = Hu3DModelLink(lbl_1_bss_1828[0]);
        }
        Hu3DModelScaleSet(lbl_1_bss_1828[i], 0.5f, 0.5f, 0.5f);
        Hu3DModelAttrSet(lbl_1_bss_1828[i], HU3D_ATTR_DISPOFF);
    }
    fn_1_8658();
    anim = HuSprAnimRead(HuAR_ARAMtoMRAMFileRead(DATA_MAKE_NUM(DATADIR_EFFECT, 4), MEMORY_DEFAULT_NUM, HEAP_DATA));
    for (i = 0; i < 4; i++) {
        lbl_1_bss_1814[i] = Hu3DParManCreate(anim, 300, &lbl_1_data_780);
        Hu3DParManAttrSet(lbl_1_bss_1814[i], 0x65);
        Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(lbl_1_bss_1814[i]), 1);
        Hu3DParManRotSet(lbl_1_bss_1814[i], 90, 0, 0);
    }
    HuDataDirClose(DATADIR_RESULT);
    for (i = 0; i < 4; i++) {
        player = lbl_1_bss_19F0[i];
        character = GWPlayerCfg[lbl_1_bss_19F0[i]].character;
        char_mdl = CharModelCreate(character, 2);
        lbl_1_bss_19B0[player] = char_mdl;
        lbl_1_bss_1990[player][0] = CharModelMotionCreate(character, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
        lbl_1_bss_1990[player][1] = CharModelMotionCreate(character, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17));
        lbl_1_bss_1990[player][2] = CharModelMotionCreate(character, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x49));
        CharModelVoiceEnableSet(character, lbl_1_bss_1990[player][1], 0);
        CharModelMotionSet(character, lbl_1_bss_1990[player][0]);
        Hu3DModelPosSet(char_mdl, lbl_1_data_7F0[i].x, lbl_1_data_7F0[lbl_1_bss_19E8[i]].y, 0);
        Hu3DModelAttrSet(char_mdl, HU3D_MOTATTR_LOOP);
        Hu3DModelShadowSet(char_mdl);
    }
    CharModelDataClose(-1);
}

Vec lbl_1_data_8B8[] = { { 8, 0, 0 }, { 0, 8, 0 }, { 10, 5, 0 }, { -5, 10, 0 }, { 0, -8, 0 }, { 8, 10, 0 }, { -10, 8, 0 }, { 15, 0, 0 } };

void fn_1_7544(void)
{
    s16 i;
    s16 time;
    s16 done_cnt;
    float pos_y;
    s16 gains[5];
    s16 time_player[4];
    fn_1_423C(gains);
    for (time = 0; time <= 5; time++) {
        pos_y = ((5 - time) * 50) + 580;
        for (i = 0; i < 4; i++) {
            Hu3DModelPosSet(lbl_1_bss_1A9C[i + 4], lbl_1_data_7F0[i].x, pos_y, 0);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        Hu3DModelAttrReset(lbl_1_bss_1A9C[i + 4], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(lbl_1_bss_1A9C[i + 4], 1.5f);
    }
    HuPrcSleep(35);
    for (i = 0; i < 4; i++) {
        if (gains[lbl_1_bss_19F0[i]] > 0) {
            Hu3DParManAttrReset(lbl_1_bss_1814[i], 1);
            time_player[i] = frandmod(10);
        }
        else {
            time_player[i] = 0;
        }
        Hu3DParManPosSet(lbl_1_bss_1814[i], lbl_1_data_7F0[i].x, 610.0f, 0.0f);
    }
    while (1) {
        for (i = done_cnt = 0; i < 4; i++) {
            if (time_player[i]) {
                time_player[i]--;
                continue;
            }
            if (gains[lbl_1_bss_19F0[i]] <= 0) {
                Hu3DParManAttrSet(lbl_1_bss_1814[i], 1);
                done_cnt++;
            }
            else {
                fn_1_86DC(i);
                gains[lbl_1_bss_19F0[i]]--;
                if (gains[lbl_1_bss_19F0[i]] <= 10) {
                    time_player[i] = 4;
                }
                else {
                    if (gains[lbl_1_bss_19F0[i]] <= 20) {
                        time_player[i] = 3;
                    }
                    else {
                        if (gains[lbl_1_bss_19F0[i]] <= 40) {
                            time_player[i] = 2;
                        }
                        else {
                            time_player[i] = 1;
                        }
                    }
                }
            }
        }
        if (done_cnt == 4) {
            break;
        }
        HuPrcVSleep();
    }
    if (gains[4]) {
        HuPrcSleep(20);
        Hu3DModelRotSet(lbl_1_bss_1A9C[8], 0, -90, 0);
        Hu3DModelScaleSet(lbl_1_bss_1A9C[8], 0.8f, 0.8f, 0.8f);
        Hu3DMotionSpeedSet(lbl_1_bss_1A9C[8], 2.0f);
        for (i = 0; i <= 40; i++) {
            Hu3DModelPosSet(lbl_1_bss_1A9C[8], 500.0f * (1.0f - (i / 40.0f)), 0, 100.0f);
            HuPrcVSleep();
        }
        HuAudFXPlay(828);
        Hu3DModelAttrReset(lbl_1_bss_1A9C[10], HU3D_MOTATTR_PAUSE);
        Hu3DModelPosSet(lbl_1_bss_1A9C[10], 0, 0, 200);
        for (i = 0; i < Hu3DMotionMaxTimeGet(lbl_1_bss_1A9C[10]); i++) {
            if (i > 10) {
                Hu3DModelAttrSet(lbl_1_bss_1A9C[8], HU3D_ATTR_DISPOFF);
            }
            Center.x = lbl_1_data_8B8[(i / 2) & 0x7].x;
            Center.y = 330.0f + lbl_1_data_8B8[(i / 2) & 0x7].y;
            Center.z = lbl_1_data_8B8[(i / 2) & 0x7].z;
            espPosSet(lbl_1_bss_1A1A[0], 288.0f + lbl_1_data_8B8[(i / 2) & 0x7].x, 240.0f - lbl_1_data_8B8[(i / 2) & 0x7].y);
            HuPrcVSleep();
        }
        espPosSet(lbl_1_bss_1A1A[0], 288.0, 240.0);
        Center.x = 0;
        Center.y = 330;
        Center.z = 0;
        time_player[0] = 10;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_172 == lbl_1_bss_19F0[i]) {
                break;
            }
        }
        Hu3DParManAttrReset(lbl_1_bss_1814[i], 1);
        while (1) {
            if (time_player[0] != 0) {
                time_player[0]--;
                HuPrcVSleep();
                continue;
            }
            if (gains[4] <= 0) {
                Hu3DParManAttrSet(lbl_1_bss_1814[i], 1);
                break;
            }
            fn_1_86DC(i);
            gains[4]--;
            time_player[0] = 5;
            HuPrcVSleep();
        }
        Hu3DParManAttrSet(lbl_1_bss_1814[i], 1);
    }
    fn_1_423C(gains);
    gains[lbl_1_bss_172] += gains[4];
    for (i = 0; i < 4; i++) {
        if (gains[lbl_1_bss_19F0[i]]) {
            CharModelMotionShiftSet(GWPlayerCfg[lbl_1_bss_19F0[i]].character, lbl_1_bss_1990[lbl_1_bss_19F0[i]][1], 0, 4, HU3D_MOTATTR_NONE);
            HuAudPlayerVoicePlay(lbl_1_bss_19F0[i], 293);
        }
        else {
            CharModelMotionShiftSet(GWPlayerCfg[lbl_1_bss_19F0[i]].character, lbl_1_bss_1990[lbl_1_bss_19F0[i]][2], 0, 4, HU3D_MOTATTR_NONE);
        }
    }
    HuPrcSleep(20);
    fn_1_7F98();
    HuPrcSleep(120);
}

void fn_1_7F98(void)
{
    s16 i;
    s16 time;
    s16 delay;
    s16 gains[5];
    Vec pos_3d;
    Vec pos_2d;
    fn_1_423C(gains);
    gains[lbl_1_bss_172] += gains[4];
    for (i = 0; i < 4; i++) {
        fn_1_8338(lbl_1_bss_19E0[i], gains[lbl_1_bss_19F0[i]]);
        pos_3d.x = lbl_1_data_7F0[i].x;
        if (gains[lbl_1_bss_19F0[i]]) {
            pos_3d.y = lbl_1_data_7F0[lbl_1_bss_19E8[i]].y + lbl_1_data_860[GWPlayerCfg[lbl_1_bss_19F0[i]].character];
        }
        else {
            pos_3d.y = lbl_1_data_7F0[lbl_1_bss_19E8[i]].y + lbl_1_data_880[GWPlayerCfg[lbl_1_bss_19F0[i]].character];
        }
        pos_3d.z = 0;
        Hu3D3Dto2D(&pos_3d, 1, &pos_2d);
        HuSprGrpPosSet(lbl_1_bss_19E0[i], pos_2d.x, pos_2d.y);
    }
    delay = (lbl_1_bss_174) ? 3 : 10;
    for (time = 0; time <= delay; time++) {
        float scale = sind((90.0 / delay) * time);
        for (i = 0; i < 4; i++) {
            HuSprGrpScaleSet(lbl_1_bss_19E0[i], scale, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuSprGrpScaleSet(lbl_1_bss_19E0[i], 1.0f, 1.0f);
    }
}

void fn_1_8338(s16 group, s16 value)
{
    s16 digit;
    s16 digit_value;

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

void fn_1_8484(void)
{
    s16 i;
    s16 j;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_19E8[i] = GWPlayerCoinWinGet(i);
        lbl_1_bss_19F0[i] = i;
    }
    for (j = 1; j < 4; j++) {
        for (i = 0; i < 4 - j; i++) {
            if (lbl_1_bss_19E8[i] > lbl_1_bss_19E8[i + 1]) {
                s16 temp;
                temp = lbl_1_bss_19E8[i];
                lbl_1_bss_19E8[i] = lbl_1_bss_19E8[i + 1];
                lbl_1_bss_19E8[i + 1] = temp;
                temp = lbl_1_bss_19F0[i];
                lbl_1_bss_19F0[i] = lbl_1_bss_19F0[i + 1];
                lbl_1_bss_19F0[i + 1] = temp;
            }
        }
    }
}

void fn_1_8998(void);

void fn_1_8658(void)
{
    s16 i;
    Process *process = HuPrcCurrentGet();
    for (i = 0; i < 180; i++) {
        lbl_1_bss_194[i].unk0 = -1;
    }
    HuPrcChildCreate(fn_1_8998, 100, 8192, 0, process);
}

void fn_1_86DC(s16 player)
{
    s16 i;
    for (i = 0; i < 180; i++) {
        if (lbl_1_bss_194[i].unk0 == -1) {
            break;
        }
    }
    if (i == 180) {
        return;
    }
    lbl_1_bss_194[i].unk0 = player;
    lbl_1_bss_194[i].unk4.x = lbl_1_data_7F0[player].x;
    lbl_1_bss_194[i].unk4.y = 610.0f;
    lbl_1_bss_194[i].unk4.z = 0.0f;
    lbl_1_bss_194[i].unk2 = lbl_1_bss_19E8[player];
    lbl_1_bss_194[i].unk10.x = frandmod(20) - 10.0f;
    lbl_1_bss_194[i].unk10.y = frandmod(20) - 10.0f;
    lbl_1_bss_194[i].unk10.z = 0;
    lbl_1_bss_194[i].unk1C = 10.0f;
    Hu3DModelAttrReset(lbl_1_bss_1828[i], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(lbl_1_bss_1828[i], 0, 100, 0);
    Hu3DModelRotSet(lbl_1_bss_1828[i], 0, 0, 0);
}

void fn_1_8998(void)
{
    s16 i;
    ModelData *model_ptr;
    s16 player;
    while (1) {
        for (i = 0; i < 180; i++) {
            if (lbl_1_bss_194[i].unk0 == -1) {
                continue;
            }
            player = lbl_1_bss_194[i].unk0;
            model_ptr = &Hu3DData[lbl_1_bss_1828[i]];
            model_ptr->pos = lbl_1_bss_194[i].unk4;
            model_ptr->rot.x += lbl_1_bss_194[i].unk10.x;
            model_ptr->rot.y += lbl_1_bss_194[i].unk10.y;
            lbl_1_bss_194[i].unk4.y -= lbl_1_bss_194[i].unk1C;
            lbl_1_bss_194[i].unk1C += 0.2f;
            if (lbl_1_bss_194[i].unk4.y < ((3 - lbl_1_bss_194[i].unk2) * 100) + lbl_1_data_840[GWPlayerCfg[lbl_1_bss_19F0[player]].character]) {
                Vec pos;
                pos.x = lbl_1_data_7F0[player].x;
                pos.y = ((3 - lbl_1_bss_194[i].unk2) * 100) + lbl_1_data_840[GWPlayerCfg[lbl_1_bss_19F0[player]].character];
                pos.z = 0.0f;
                CharModelCoinEffectCreate(1, &pos);
                lbl_1_bss_194[i].unk0 = -1;
                HuAudFXPlay(7);
                Hu3DModelAttrSet(lbl_1_bss_1828[i], HU3D_ATTR_DISPOFF);
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_8CB8(struct model_data *model, Mtx matrix)
{
    s32 sp8 = 0;
    GXTexObj tex;
    Mtx final;
    Mtx inv_camera;
    Mtx shadow;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXInitTexObj(&tex, Hu3DShadowData.unk_04, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex, 0);
    MTXInverse(Hu3DCameraMtx, inv_camera);
    MTXConcat(inv_camera, matrix, final);
    MTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, shadow);
    MTXConcat(shadow, final, final);
    GXLoadTexMtxImm(final, GX_TEXMTX9, GX_MTX3x4);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX9);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXLoadPosMtxImm(matrix, GX_PNMTX0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-500.0f, 0, -500.0f);
    GXPosition3f32(500.0f, 0, -500.0f);
    GXPosition3f32(500.0f, 0, 500.0f);
    GXPosition3f32(-500.0f, 0, 500.0f);
    GXEnd();
}

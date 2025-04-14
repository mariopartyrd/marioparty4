#include "REL/mgmodedll.h"
#include "game/audio.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/wipe.h"

#include "game/chrman.h"

#include "math.h"

s16 lbl_1_bss_2C80[13];
s16 lbl_1_bss_2C66[13];
s16 lbl_1_bss_2C2C[29];
s16 lbl_1_bss_2C24[4];
s16 lbl_1_bss_2C1C[4];
s16 lbl_1_bss_2C14[4];
s16 lbl_1_bss_2BC4[4][10];
s16 lbl_1_bss_264C[10][70];
s16 lbl_1_bss_2638[10];
s16 lbl_1_bss_20C0[10][70];
s16 lbl_1_bss_20AC[10];
s16 lbl_1_bss_20AA;
s16 lbl_1_bss_20A8;

s32 lbl_1_data_9C0[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
};

s32 lbl_1_data_9E0[8] = {
    DATADIR_MARIOMDL1,
    DATADIR_LUIGIMDL1,
    DATADIR_PEACHMDL1,
    DATADIR_YOSHIMDL1,
    DATADIR_WARIOMDL1,
    DATADIR_DONKEYMDL1,
    DATADIR_DAISYMDL1,
    DATADIR_WALUIGIMDL1,
};

s16 lbl_1_data_A00 = -1;

void fn_1_26C54(s16 layer);

void fn_1_26C28(void)
{
    Hu3DLayerHookSet(2, fn_1_26C54);
}

void fn_1_26C54(s16 layer)
{
    Mtx44 proj;
    Mtx modelview;
    Vec pos, target, up;
    GXColor color;
    CameraData *camera = &Hu3DCamera[0];
    MTXPerspective(proj, camera->fov, camera->aspect, camera->nnear, camera->ffar);
    GXSetProjection(proj, GX_PERSPECTIVE);
    GXSetViewport(0, 0, 640, 480, 0, 1);
    GXSetScissor(0, 0, 640, 480);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    color.a = 255;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(0);
    GXSetNumTevStages(01);
    GXSetCullMode(GX_CULL_NONE);
    GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_AND, GX_GEQUAL, 0);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    pos.x = pos.y = pos.z = 0;
    target.x = target.y = 0;
    target.z = -100;
    up.x = up.z = 0;
    up.y = 1;
    MTXLookAt(modelview, &pos, &up, &target);
    GXLoadPosMtxImm(modelview, GX_PNMTX0);
    pos.x = (10000.0f * (-sin(camera->fov / 2.0f))) * 1.2f;
    pos.y = (10000.0f * (-sin(camera->fov / 2.0f))) * (5.0f / 6.0f);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-pos.x, -pos.y, -10000.0f);
    GXPosition3f32(pos.x, -pos.y, -10000.0f);
    GXPosition3f32(pos.x, pos.y, -10000.0f);
    GXPosition3f32(-pos.x, pos.y, -10000.0f);
    GXEnd();
}

void fn_1_27080(void)
{
    s16 i;
    s32 status;
    CharModelDataClose(-1);
    CharKill(-1);
    for (i = 0; i < 4; i++) {
        status = HuDataDirReadAsync(lbl_1_data_9C0[GWPlayerCfg[i].character]);
        if (status != -1) {
            while (!HuDataGetAsyncStat(status)) {
                HuPrcVSleep();
            }
        }
        CharARAMOpen(GWPlayerCfg[i].character);
    }
    for (i = 0; i < 2; i++) {
        status = HuDataDirReadAsync(lbl_1_data_9E0[GWPlayerCfg[i].character]);
        if (status != -1) {
            while (!HuDataGetAsyncStat(status)) {
                HuPrcVSleep();
            }
        }
    }
    lbl_1_bss_20AA = 0;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

s16 fn_1_271B4(s16 mgNo, s16 x, s16 y)
{
    s16 time;
    AnimData *anim;
    s16 sprite;
    s32 mgpic;
    if (mgNo == -1) {
        if (lbl_1_data_A00 == -1) {
            return;
        }
        for (time = 0; time <= 10; time++) {
            HuSprGrpTPLvlSet(lbl_1_data_A00, 1.0 - (time / 10.0));
            HuPrcVSleep();
        }
        HuSprGrpKill(lbl_1_data_A00);
        lbl_1_data_A00 = -1;
        return;
    }

    if (lbl_1_data_A00 != -1) {
        HuSprGrpKill(lbl_1_data_A00);
    }
    lbl_1_data_A00 = HuSprGrpCreate(1);
    mgpic = mgInfoTbl[mgNo].mg_pic[0];
    if (GWMGAvailGet(mgNo + 401)) {
        anim = HuSprAnimReadFile(mgpic);
    }
    else {
        anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x2C));
    }
    sprite = HuSprCreate(anim, 100, 0);
    HuSprGrpMemberSet(lbl_1_data_A00, 0, sprite);
    HuSprGrpPosSet(lbl_1_data_A00, x, y);
    HuSprGrpScaleSet(lbl_1_data_A00, 0.55f, 0.55f);
    HuSprGrpDrawNoSet(lbl_1_data_A00, 64);
    return lbl_1_data_A00;
}

void fn_1_27418(void)
{
    s16 i;
    s16 j;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_2C1C[i] = i;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3 - i; j++) {
            if (GWPlayerCfg[lbl_1_bss_2C1C[j]].group > GWPlayerCfg[lbl_1_bss_2C1C[j + 1]].group) {
                s16 temp = lbl_1_bss_2C1C[j];
                lbl_1_bss_2C1C[j] = lbl_1_bss_2C1C[j + 1];
                lbl_1_bss_2C1C[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        s16 charNo;
        lbl_1_bss_2C24[i] = charNo = GWPlayerCfg[lbl_1_bss_2C1C[i]].character;
        lbl_1_bss_2C14[i] = CharModelCreate(charNo, 2);
        lbl_1_bss_2BC4[i][0] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
        lbl_1_bss_2BC4[i][1] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02));
        lbl_1_bss_2BC4[i][2] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03));
        lbl_1_bss_2BC4[i][3] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x48));
        lbl_1_bss_2BC4[i][4] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x49));
        lbl_1_bss_2BC4[i][5] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17));
        lbl_1_bss_2BC4[i][6] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18));
        CharModelVoiceEnableSet(GWPlayerCfg[lbl_1_bss_2C1C[i]].character, lbl_1_bss_2BC4[i][1], 0);
        CharModelVoiceEnableSet(GWPlayerCfg[lbl_1_bss_2C1C[i]].character, lbl_1_bss_2BC4[i][2], 0);
        Hu3DModelPosSet(lbl_1_bss_2C14[i], 600, 0, 800);
        Hu3DModelLayerSet(lbl_1_bss_2C14[i], 3);
        CharModelDataClose(charNo);
        Hu3DModelShadowSet(lbl_1_bss_2C14[i]);
    }
}

void fn_1_2783C(s16 evtno)
{
    s16 i;
    omOvlHisData *his;
    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].character = lbl_1_bss_8.unk24[i].unk68;
        GWPlayerCfg[i].iscom = lbl_1_bss_8.unk24[i].unk60;
        GWPlayerCfg[i].pad_idx = lbl_1_bss_8.unk24[i].unk6C;
        GWPlayerCfg[i].diff = lbl_1_bss_8.unk24[i].unk64;
    }
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudSeqAllFadeOut(1000);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    CharKill(-1);
    for (i = 0; i < 4; i++) {
        CharARAMOpen(GWPlayerCfg[i].character);
    }
    HuAudVoiceInit(-1);
    his = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MGMODE, evtno, his->stat);
    omOvlCallEx(OVL_INST, 1, 0, 0);
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_279FC(s32 coinSkipF)
{
    s16 i;
    s16 mgNum;
    for (mgNum = 0; mgInfoTbl[mgNum].ovl != 65535; mgNum++)
        ;
    for (i = 0; i < 9; i++) {
        lbl_1_bss_2638[i] = lbl_1_bss_20AC[i] = 0;
    }
    for (i = 0; i < mgNum; i++) {
        s16 type = mgInfoTbl[i].type;
        if (type >= 0 && type < 9) {
            if (coinSkipF) {
                s16 ovl = mgInfoTbl[i].ovl;
                if (ovl == OVL_M408 || ovl == OVL_M422 || ovl == OVL_M430) {
                    continue;
                }
            }
            lbl_1_bss_264C[type][lbl_1_bss_2638[type]] = i;
            lbl_1_bss_2638[type]++;
            if (GWMGAvailGet(i + 401)) {
                lbl_1_bss_20C0[type][lbl_1_bss_20AC[type]] = i;
                lbl_1_bss_20AC[type]++;
            }
        }
    }
}

void fn_1_27C0C(s16 type)
{
    s16 i;
    s16 j;
    for (i = 0; i < 256;) {
        for (j = 0; j < lbl_1_bss_20AC[type]; j++, i++) {
            if (i > 256) {
                break;
            }
            mgIndexList[i] = lbl_1_bss_20C0[type][j];
        }
    }
    for (i = 0; i < 256; i++) {
        mgIndexList[i];
    }
    lbl_801D3E94 = 0;
}

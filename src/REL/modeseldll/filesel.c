#include "game/audio.h"
#include "game/card.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/saveload.h"
#include "game/window.h"
#include "game/wipe.h"

#include "ext_math.h"

#include "REL/modeseldll.h"

s32 msmSysGetOutputMode(void);

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/hsfex.h"
#endif

s16 lbl_1_data_100 = -1;
float lbl_1_data_104[] = { -55, 0, 0, 0, 60, -57, 806, -71, 0, 0, 0, 100, -131, 900, -87, 0, 0, 0, 46, -117, 566, -87, 0, 0, 0, 46, -117, 566, -90, 0,
    0, -22, 39, -153, 432, -40, 0, 0, 0, 130, -186, 6530, -23, 0, 0, -9, 1, -70, 1318, -25, 0, 0, 0, 242, 90, 343, -30, 0, 0, 0, 223, -60, 505, -23,
    0, 0, 0, 65, -97, 1318 };

s32 lbl_1_data_21C[] = {
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x0D),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x0E),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x0F),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x10),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x11),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x12),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x13),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x14),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x15),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x16),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x17),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x18),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x19),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1A),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1B),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1C),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1D),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1E),
};

char *lbl_1_data_26C[] = { "\x0E\x16", "\x0E\x17" };

char *lbl_1_data_278[] = { "A", "B" };

char *lbl_1_data_288[] = { "1", "2", "3" };

s32 lbl_1_bss_14C;
s16 lbl_1_bss_148;
s16 lbl_1_bss_146;
s16 lbl_1_bss_140[3];
s16 lbl_1_bss_13A[3];
s16 lbl_1_bss_134[3];
s32 lbl_1_bss_12C[2];
s32 lbl_1_bss_120[3];
s16 lbl_1_bss_11C;
s16 lbl_1_bss_116[3];
s16 lbl_1_bss_110[3];
float lbl_1_bss_108[2];
float lbl_1_bss_100[2];
AnimData *lbl_1_bss_FC;
AnimData *lbl_1_bss_F8;
AnimData *lbl_1_bss_F4;
s16 lbl_1_bss_EE[3];
s16 lbl_1_bss_E8[3];
OSTime lbl_1_bss_D0[3];
s32 lbl_1_bss_C4[3];
s32 lbl_1_bss_B8[3];
s32 lbl_1_bss_AC[3];
s16 lbl_1_bss_A4[3];
s16 lbl_1_bss_9E[3];
s16 lbl_1_bss_98[3];
s16 lbl_1_bss_92[3];
s16 lbl_1_bss_90;
float lbl_1_bss_8C;
s16 lbl_1_bss_88;

s32 fn_1_3AAC(void);
void fn_1_5D30(void);
s32 fn_1_61B4(void);
void fn_1_AAB8(void);

s32 fn_1_37DC(void)
{
    s16 i;
    s16 result;
    WindowData *window;
    s16 fxstat;
    Process *process = HuPrcCurrentGet();
    Process *child;
    float winSize[2];
    for (i = 0; i < 3; i++) {
        lbl_1_bss_13A[i] = lbl_1_bss_134[i] = -1;
        lbl_1_bss_116[i] = -1;
        lbl_1_bss_110[i] = -1;
    }
    lbl_1_bss_FC = lbl_1_bss_F8 = lbl_1_bss_F4 = NULL;
    curSlotNo = 0;
    fn_1_1EC0(0);
    fn_1_5D30();
    child = HuPrcChildCreate(fn_1_AAB8, 10, 8192, 0, process);
    winSize[0] = 457;
    winSize[1] = 94;
    lbl_1_bss_148 = HuWinExCreateStyled(-10000, 448 - winSize[1], winSize[0], winSize[1], -1, 0);
    window = &winData[lbl_1_bss_148];
    window->active_pad = 1;
    HuWinPushKeySet(lbl_1_bss_148, 0x300);
    HuWinMesSpeedSet(lbl_1_bss_148, 0);
    HuWinDispOn(lbl_1_bss_148);
    fxstat = HuAudFXPlay(2098);
    lbl_1_data_100 = fxstat;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuAudSeqPlay(43);
    while (1) {
        result = fn_1_3AAC();
        if (!result) {
            break;
        }
        if (!SLSaveFlagGet()) {
            GWGameStatReset();
            #if VERSION_PAL
            _ClearFlag(0x1000B);
            #endif
            GWGameStat.sound_mode = msmSysGetOutputMode();
            result = 1;
            break;
        }
        else {
            if (fn_1_61B4()) {
                break;
            }
        }
    }
    if (result == 0) {
        HuAudFXStop(fxstat);
    }
    HuWinExAnimOut(lbl_1_bss_148);
    HuWinExCleanup(lbl_1_bss_148);
    HuPrcKill(child);
    HuCardUnMount(0);
    HuCardUnMount(1);
    return result;
}

#define GET_ZEROSIGN(x) (((x) == 0) ? (-1) : (1))

s32 fn_1_562C(void);
void fn_1_57C8(s16 arg0);
void fn_1_5BAC(s16 arg0, s32 arg1);
s32 fn_1_5C38(void);
void fn_1_B8CC(u32 arg0);
void fn_1_BA20(void);

s32 fn_1_3AAC(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    WindowData *temp_r23;
    float temp_f31;
    CARDFileInfo sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float sp8[2];

    fn_1_1EC0(0);
    temp_r23 = &winData[lbl_1_bss_148];
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x10, 0x0C));
    lbl_1_bss_146 = HuWinExCreateStyled(-10000.0f, 316.0f, sp8[0], sp8[1], -1, 0);
    HuWinBGTPLvlSet(lbl_1_bss_146, 0);
    HuWinMesSpeedSet(lbl_1_bss_146, 0);
repeat:
    sp28.x = 188;
    sp28.y = 250;
    sp28.z = 600;
    Hu3D2Dto3D(&sp28, 1, &sp1C);
    Hu3DModelPosSetV(lbl_1_bss_19A[2], &sp1C);
    Hu3DModelPosSetV(lbl_1_bss_19A[4], &sp1C);
    Hu3DModelPosSetV(lbl_1_bss_19A[0], &sp1C);
    sp28.x = 388;
    Hu3D2Dto3D(&sp28, 1, &sp1C);
    Hu3DModelPosSetV(lbl_1_bss_19A[3], &sp1C);
    Hu3DModelPosSetV(lbl_1_bss_19A[5], &sp1C);
    Hu3DModelPosSetV(lbl_1_bss_19A[1], &sp1C);
    Hu3DModelAttrReset(lbl_1_bss_19A[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_19A[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_19A[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_19A[5], HU3D_ATTR_DISPOFF);
    Hu3DModelRotSet(lbl_1_bss_19A[2], 0, 0, 0);
    Hu3DModelRotSet(lbl_1_bss_19A[3], 0, 0, 0);
    fn_1_57C8(lbl_1_bss_19A[4]);
    fn_1_57C8(lbl_1_bss_19A[5]);
    lbl_1_bss_12C[0] = lbl_1_bss_12C[1] = 1;
    lbl_1_bss_108[0] = lbl_1_bss_108[1] = lbl_1_bss_100[0] = lbl_1_bss_100[1] = 1.0f;
    lbl_1_bss_11C = -1;
    fn_1_5C38();
    for (temp_r30 = 0; temp_r30 <= 20; temp_r30++) {
        temp_f31 = temp_r30 / 20.0;
        temp_f31 = sind(90.0f * temp_f31);
        Hu3DModelScaleSet(lbl_1_bss_19A[0], temp_f31, temp_f31, temp_f31);
        Hu3DModelScaleSet(lbl_1_bss_19A[1], temp_f31, temp_f31, temp_f31);
        Hu3DModelScaleSet(lbl_1_bss_19A[2], temp_f31, temp_f31, temp_f31);
        Hu3DModelScaleSet(lbl_1_bss_19A[3], temp_f31, temp_f31, temp_f31);
        Hu3DModelScaleSet(lbl_1_bss_19A[4], temp_f31, temp_f31, temp_f31);
        Hu3DModelScaleSet(lbl_1_bss_19A[5], temp_f31, temp_f31, temp_f31);
        HuPrcVSleep();
    }
    while (1) {
    repeat_loop:
        HuWinDispOff(lbl_1_bss_146);
        temp_r28 = fn_1_562C();
        if (temp_r28 == 0 && fn_1_5C38() == 0) {
            if (fn_1_5C38() == 0) {
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
                HuWinMesWait(lbl_1_bss_148);
            }
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4F));
            HuWinAttrSet(lbl_1_bss_148, 0x10);
            HuWinMesWait(lbl_1_bss_148);
            temp_r27 = HuWinChoiceGet(lbl_1_bss_148, 1);
            if (temp_r27 == 0) {
                SLSaveFlagSet(0);
                temp_r29 = 1;
                goto cleanup;
            }
            HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x52), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4C));
            HuWinMesWait(lbl_1_bss_148);
            while (!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
                HuPrcVSleep();
            }
        }
        while (!fn_1_5C38()) {
            temp_r28 = fn_1_562C();
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
            HuWinMesWait(lbl_1_bss_148);
            if (temp_r23->key_down & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                return 0;
            }
            if (fn_1_5C38()) {
                break;
            }
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4B));
            HuWinAttrSet(lbl_1_bss_148, 0x10);
            HuWinMesWait(lbl_1_bss_148);
            temp_r27 = HuWinChoiceGet(lbl_1_bss_148, 1);
            if (temp_r27 == 0) {
                SLSaveFlagSet(0);
                temp_r29 = 1;
                goto cleanup;
            }
            HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x52), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4C));
            HuWinMesWait(lbl_1_bss_148);
            while (!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
                HuPrcVSleep();
            }
        }
        SLSaveFlagSet(1);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x01));
        HuWinMesWait(lbl_1_bss_148);
        HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x0C));
        HuWinDispOn(lbl_1_bss_146);
        if (curSlotNo == 0) {
            if (lbl_1_bss_14C & 0x1) {
                temp_r31 = 0;
            }
            else {
                temp_r31 = 1;
            }
        }
        else {
            if (lbl_1_bss_14C & 0x2) {
                temp_r31 = 1;
            }
            else {
                temp_r31 = 0;
            }
        }
        fn_1_5BAC(temp_r31, 1);
        HuPrcSleep(10);
        temp_r24 = temp_r31;
        while (1) {
            if (!fn_1_5C38()) {
                fn_1_5BAC(temp_r31, 0);
                HuPrcSleep(10);
                goto repeat_loop;
            }
            else {
                if ((HuPadDStkRep[0] & 0x1) && (lbl_1_bss_14C & 0x1)) {
                    temp_r31 = 0;
                }
                else if ((HuPadDStkRep[0] & 0x2) && (lbl_1_bss_14C & 0x2)) {
                    temp_r31 = 1;
                }
                else if (!(lbl_1_bss_14C & (1 << temp_r31))) {
                    if (!(lbl_1_bss_14C & (1 << ((temp_r31 + 1) & 0x1)))) {
                        fn_1_5BAC(temp_r31, 0);
                        HuPrcSleep(10);
                        goto repeat_loop;
                    }
                    else {
                        temp_r31 = (temp_r31 + 1) & 0x1;
                    }
                }
                if (temp_r24 != temp_r31) {
                    HuAudFXPlay(0);
                    fn_1_5BAC(temp_r31, 1);
                    fn_1_5BAC((temp_r31 + 1) & 0x1, 0);
                    HuPrcSleep(10);
                    temp_r24 = temp_r31;
                }
                if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                    HuAudFXPlay(2096);
                    goto loop_exit;
                }
                else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                    HuAudFXPlay(3);
                    return 0;
                }
            }
            HuPrcVSleep();
        }
    }
loop_exit:
    HuWinHomeClear(lbl_1_bss_148);
    temp_r26 = (temp_r31 + 1) & 0x1;
    Hu3DMotionSet(lbl_1_bss_19A[temp_r31 + 4], lbl_1_bss_16A[7]);
    Hu3DMotionSpeedSet(lbl_1_bss_19A[temp_r31 + 4], 2.0f);
    lbl_1_bss_12C[0] = lbl_1_bss_12C[1] = 0;
    lbl_1_bss_11C = temp_r31;
    SLCurSlotNoSet(temp_r31);
    temp_r28 = HuCardMount(temp_r31);
    if (temp_r28 == 0) {
        SLSerialNoGet();
        temp_r28 = HuCardOpen(temp_r31, SaveFileNameTbl[0], &sp34);
        if (temp_r28 != 0 && temp_r28 != -4) {
            temp_r29 = 1;
        }
        else {
            temp_r29 = 0;
        }
        HuCardClose(&sp34);
    }
    else {
        if (temp_r28 == -3) {
            goto repeat;
        }
        temp_r29 = 1;
    }
    temp_r27 = HuCardSectorSizeGet(curSlotNo);
    if (temp_r27 > 0 && temp_r27 != 8192) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x39));
        HuWinMesWait(lbl_1_bss_148);
        temp_r29 = 1;
        goto skip_check;
    }
    else {
        if (temp_r27 == -128) {
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
            HuWinMesWait(lbl_1_bss_148);
            temp_r29 = 1;
            goto skip_check;
        }
        else {
            lbl_1_bss_8C += 720.0f;
            for (temp_r30 = 0; temp_r30 <= 40; temp_r30++) {
                if (temp_r30 <= 30) {
                    temp_f31 = temp_r30 / 30.0f;
                    sp28.x = 288.0 + (GET_ZEROSIGN(temp_r26) * (100.0 + (250.0 * sind(90.0f * temp_f31))));
                    sp28.y = 250.0 - (100.0 * sind(180.0f * temp_f31));
                    sp28.z = (temp_r30 * 100) + 600;
                    Hu3D2Dto3D(&sp28, 1, &sp1C);
                    Hu3DModelPosSetV(lbl_1_bss_19A[temp_r26 + 2], &sp1C);
                    Hu3DModelPosSetV(lbl_1_bss_19A[temp_r26], &sp1C);
                    Hu3DModelRotSet(lbl_1_bss_19A[temp_r26 + 2], temp_r30 * 20, temp_r30 * 10, 0);
                }

                if (temp_r30 > 20) {
                    temp_f31 = (temp_r30 - 20) / 20.0f;
                    if (temp_r29) {
                        sp28.x = 288.0f + ((1.0 - temp_f31) * (100 * GET_ZEROSIGN(temp_r31)));
                        sp28.y = 250.0 - (100.0 * sind(180.0f * temp_f31));
                        sp28.z = 600.0f;
                        Hu3D2Dto3D(&sp28, 1, &sp1C);
                        Hu3DModelPosSetV(lbl_1_bss_19A[temp_r31], &sp1C);
                        temp_f31 = (0.5 * sind(90.0f * temp_f31)) + 1.0;
                        Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31], temp_f31, temp_f31, temp_f31);
                    }
                    else {
                        sp28.x = 288.0f + (100 * GET_ZEROSIGN(temp_r31));
                        sp28.y = 250;
                        sp28.z = 600;
                        Hu3D2Dto3D(&sp28, 1, &sp1C);
                        sp28.x = 60;
                        sp28.y = 90;
                        sp28.z = 600;
                        Hu3D2Dto3D(&sp28, 1, &sp10);
                        VECSubtract(&sp10, &sp1C, &sp28);
                        sp28.x *= sind(90.0f * temp_f31);
                        sp28.y *= 1.0 - cosd(90.0f * temp_f31);
                        sp28.z = 0;
                        VECAdd(&sp28, &sp1C, &sp1C);
                        Hu3DModelPosSetV(lbl_1_bss_19A[temp_r31], &sp1C);
                        lbl_1_bss_108[temp_r31] *= cosd(90.0f * temp_f31);
                        lbl_1_bss_100[temp_r31] = 1.0 - temp_f31;
                        temp_f31 = 1.0 + (0.3 * cosd(90.0f * temp_f31));
                        Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31], temp_f31, temp_f31, temp_f31);
                    }
                }
                HuPrcVSleep();
            }
            if (temp_r29 == 0) {
                HuWinKill(lbl_1_bss_146);
                return 1;
            }
            HuWinDispOff(lbl_1_bss_146);
            temp_r29 = 0;
            if (temp_r28 == -2) {
                HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[temp_r31]), 0);
                #if VERSION_PAL
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x39));
                #else
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x37));
                #endif
                HuWinMesWait(lbl_1_bss_148);
                temp_r29 = 1;
            }
            else if (temp_r28 == -128) {
                HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[temp_r31]), 0);
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
                HuWinMesWait(lbl_1_bss_148);
                temp_r29 = 1;
            }
            else if (temp_r28 == -3) {
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
                HuWinMesWait(lbl_1_bss_148);
                temp_r29 = 1;
            }
            else if (temp_r28 == -6) {
                UnMountCnt = 0;
                HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[temp_r31]), 0);
                HuWinAttrSet(lbl_1_bss_148, 0x10);
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x04));
                HuWinMesWait(lbl_1_bss_148);
                temp_r25 = HuWinChoiceGet(lbl_1_bss_148, 1);
                if (temp_r25 == 0) {
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4E));
                    HuWinMesWait(lbl_1_bss_148);
                    temp_r25 = HuWinChoiceGet(lbl_1_bss_148, 1);
                    if (temp_r25 == 0) {
                        fn_1_B8CC(MAKE_MESSID(16, 0x38));
                        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x0B));
                        HuWinMesWait(lbl_1_bss_148);
                        HuPrcSleep(60);
                        if (UnMountCnt & (1 << temp_r31)) {
                            fn_1_BA20();
                            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x50));
                            HuWinMesWait(lbl_1_bss_148);
                            temp_r29 = 1;
                            goto cleanup;
                        }
                        else {
                            _SetFlag(0x30000);
                            temp_r28 = HuCardFormat(temp_r31);
                            _ClearFlag(FLAG_ID_MAKE(3, 0));
                            if (temp_r28 == 0) {
                                SLSerialNoGet();
                            }
                            fn_1_BA20();
                            if (temp_r28 == -128) {
                                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x36));
                                HuWinMesWait(lbl_1_bss_148);
                                HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
                                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
                                HuWinMesWait(lbl_1_bss_148);
                                temp_r29 = 1;
                            }
                            else if (temp_r28 == -3) {
                                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
                                HuWinMesWait(lbl_1_bss_148);
                                temp_r29 = 1;
                            }
                        }
                    }
                    else {
                        temp_r29 = 1;
                    }
                }
                else {
                    temp_r29 = 1;
                }
            }
        }
    }
    if (temp_r29 == 0) {
        goto cleanup;
    }
skip_check:
    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4F));
    HuWinAttrSet(lbl_1_bss_148, 0x10);
    HuWinMesWait(lbl_1_bss_148);
    temp_r27 = HuWinChoiceGet(lbl_1_bss_148, 1);
    if (temp_r27 == 0) {
        SLSaveFlagSet(0);
        goto cleanup;
    }
    else {
        HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x52), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4C));
        HuWinMesWait(lbl_1_bss_148);
        while (!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
            HuPrcVSleep();
        }
    }
cleanup:
    HuWinDispOff(lbl_1_bss_146);
    lbl_1_bss_8C += 720.0f;
    for (temp_r30 = 0; temp_r30 <= 20; temp_r30++) {
        temp_f31 = temp_r30 / 20.0f;
        if (temp_r29) {
            temp_f31 = 1.5 * cosd(90.0f * temp_f31);
            Hu3DModelScaleSet(lbl_1_bss_19A[0], temp_f31, temp_f31, temp_f31);
            Hu3DModelScaleSet(lbl_1_bss_19A[1], temp_f31, temp_f31, temp_f31);
            Hu3DModelScaleSet(lbl_1_bss_19A[2], 0.7 * temp_f31, 0.7 * temp_f31, 0.7 * temp_f31);
            Hu3DModelScaleSet(lbl_1_bss_19A[3], 0.7 * temp_f31, 0.7 * temp_f31, 0.7 * temp_f31);
            if (!SLSaveFlagGet()) {
                espScaleSet(lbl_1_bss_152[1], temp_f31, temp_f31);
            }
        }
        else {
            sp28.x = 288;
            sp28.y = 250;
            sp28.z = 600;
            Hu3D2Dto3D(&sp28, 1, &sp1C);
            sp28.x = 60;
            sp28.y = 90;
            sp28.z = 600;
            Hu3D2Dto3D(&sp28, 1, &sp10);
            VECSubtract(&sp10, &sp1C, &sp28);
            sp28.x *= sind(90.0f * temp_f31);
            sp28.y *= 1.0 - cosd(90.0f * temp_f31);
            sp28.z = 0.0f;
            VECAdd(&sp28, &sp1C, &sp1C);
            Hu3DModelPosSetV(lbl_1_bss_19A[temp_r31], &sp1C);
            lbl_1_bss_108[temp_r31] *= cosd(90.0f * temp_f31);
            lbl_1_bss_100[temp_r31] = 1.0 - temp_f31;
            temp_f31 = 1.0 + (0.5 * cosd(90.0f * temp_f31));
            Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31], temp_f31, temp_f31, temp_f31);
        }
        HuPrcVSleep();
    }
    if (temp_r29 && SLSaveFlagGet()) {
        goto repeat;
    }
    HuWinKill(lbl_1_bss_146);
    return 1;
}

s32 fn_1_562C(void)
{
    s16 i;
    s16 result;
    s16 ret;
    ret = 1;
    for (i = 0; i < 2; i++) {
        result = HuCardSlotCheck((s32)i);
        if (result == -2) {
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[i]), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x37));
            HuWinMesWait(lbl_1_bss_148);
            ret = 0;
        }
        else if (result > 0 && result != 8192) {
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[i]), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x39));
            HuWinMesWait(lbl_1_bss_148);
            ret = 0;
        }
        else if (result == -128) {
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[i]), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
            HuWinMesWait(lbl_1_bss_148);
            ret = 0;
        }
    }
    return ret;
}

void fn_1_57C8(s16 arg0)
{
    ModelData *model = &Hu3DData[arg0];
    HsfData *hsf = model->hsfData;
    HsfMaterial *mat = hsf->material;
    s16 i;
    for (i = 0; i < hsf->materialCnt; i++, mat++) {
        mat->invAlpha = 0.0f;
        mat->pass &= 0xF0;
    }
}

typedef struct work_filesel {
    s16 index;
    s32 param;
} WorkFilesel;

void fn_1_5850(void)
{
    s16 index;
    WorkFilesel *work;
    s16 i;
    s32 param;
    Process *curr;
    curr = HuPrcCurrentGet();
    work = curr->user_data;
    index = work->index;
    param = work->param;
    Hu3DModelAttrSet(lbl_1_bss_19A[index + 2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_19A[index + 4], HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(lbl_1_bss_19A[index + 4], lbl_1_bss_16A[6]);
    Hu3DMotionSpeedSet(lbl_1_bss_19A[index + 4], 2.0f);
    if (param) {
        Hu3DModelAttrReset(lbl_1_bss_19A[index + 4], HU3D_MOTATTR_REV);
    }
    else {
        Hu3DModelAttrSet(lbl_1_bss_19A[index + 4], HU3D_MOTATTR_REV);
        Hu3DMotionTimeSet(lbl_1_bss_19A[index + 4], Hu3DMotionMaxTimeGet(lbl_1_bss_19A[6]));
    }
    for (i = 0; i < 10; i++) {
        float scale;
        float time = i / 10.0;
        if (param) {
            scale = 1.0 + (0.3 * sind(90.0f * time));
        }
        else {
            scale = 1.0 + (0.3 * cosd(90.0f * time));
        }
        Hu3DModelScaleSet(lbl_1_bss_19A[index + 2], scale, scale, scale);
        Hu3DModelScaleSet(lbl_1_bss_19A[index + 4], scale, scale, scale);
        Hu3DModelScaleSet(lbl_1_bss_19A[index], scale, scale, scale);
        HuPrcVSleep();
    }
    if (!param) {
        Hu3DModelAttrReset(lbl_1_bss_19A[index + 2], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_19A[index + 4], HU3D_ATTR_DISPOFF);
    }
    HuMemDirectFree(work);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_5BAC(s16 arg0, s32 arg1)
{
    WorkFilesel *work;
    Process *child;
    Process *parent;
    parent = HuPrcCurrentGet();
    child = HuPrcChildCreate(fn_1_5850, 50, 8192, 0, parent);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkFilesel), MEMORY_DEFAULT_NUM);
    child->user_data = work;
    work->index = arg0;
    work->param = arg1;
}

s32 fn_1_5C38(void)
{
    s32 result;
    lbl_1_bss_14C = 0;
    result = HuCardSlotCheck(0);
    if (result == 8192) {
        Hu3DModelAttrReset(lbl_1_bss_19A[0], HU3D_ATTR_DISPOFF);
        lbl_1_bss_14C |= 1;
    }
    else {
        Hu3DModelAttrSet(lbl_1_bss_19A[0], HU3D_ATTR_DISPOFF);
    }
    result = HuCardSlotCheck(1);
    if (result == 8192) {
        Hu3DModelAttrReset(lbl_1_bss_19A[1], HU3D_ATTR_DISPOFF);
        lbl_1_bss_14C |= 2;
    }
    else {
        Hu3DModelAttrSet(lbl_1_bss_19A[1], HU3D_ATTR_DISPOFF);
    }
    return lbl_1_bss_14C;
}

void fn_1_5D30(void)
{
    ModelData *model;
    Vec pos_2d;
    Vec pos_3d;
    Mtx scale;
    espAttrReset(lbl_1_bss_152[0], HUSPR_ATTR_DISPOFF);
    espDrawNoSet(lbl_1_bss_152[0], 127);
    espAttrReset(lbl_1_bss_152[1], HUSPR_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_19A[2], HU3D_ATTR_DISPOFF);
    pos_2d.x = 188;
    pos_2d.y = 250;
    pos_2d.z = 600;
    Hu3D2Dto3D(&pos_2d, 1, &pos_3d);
    Hu3DModelPosSetV(lbl_1_bss_19A[2], &pos_3d);
    Hu3DModelPosSetV(lbl_1_bss_19A[4], &pos_3d);
    Hu3DModelPosSetV(lbl_1_bss_19A[0], &pos_3d);
    MTXScale(scale, 0.5f, 0.5f, 0.5f);
    model = &Hu3DData[lbl_1_bss_19A[2]];
    MTXCopy(scale, model->unk_F0);
    model = &Hu3DData[lbl_1_bss_19A[4]];
    MTXCopy(scale, model->unk_F0);
    model = &Hu3DData[lbl_1_bss_19A[0]];
    MTXCopy(scale, model->unk_F0);
    Hu3DModelAttrReset(lbl_1_bss_19A[3], HU3D_ATTR_DISPOFF);
    pos_2d.x = 388;
    Hu3D2Dto3D(&pos_2d, 1, &pos_3d);
    Hu3DModelPosSetV(lbl_1_bss_19A[3], &pos_3d);
    Hu3DModelPosSetV(lbl_1_bss_19A[5], &pos_3d);
    Hu3DModelPosSetV(lbl_1_bss_19A[1], &pos_3d);
    model = &Hu3DData[lbl_1_bss_19A[3]];
    MTXCopy(scale, model->unk_F0);
    model = &Hu3DData[lbl_1_bss_19A[5]];
    MTXCopy(scale, model->unk_F0);
    model = &Hu3DData[lbl_1_bss_19A[1]];
    MTXCopy(scale, model->unk_F0);
    Hu3DModelScaleSet(lbl_1_bss_19A[0], 0, 0, 0);
    Hu3DModelScaleSet(lbl_1_bss_19A[1], 0, 0, 0);
    Hu3DModelScaleSet(lbl_1_bss_19A[2], 0, 0, 0);
    Hu3DModelScaleSet(lbl_1_bss_19A[3], 0, 0, 0);
    Hu3DModelScaleSet(lbl_1_bss_19A[4], 0, 0, 0);
    Hu3DModelScaleSet(lbl_1_bss_19A[5], 0, 0, 0);
    fn_1_5C38();
}

void fn_1_7628(s16 boxno, s32 flag);

s32 fn_1_76B4(char *name, s16 slotno);
s32 fn_1_7B74(s16 boxno);
s32 fn_1_812C(void);
s32 fn_1_83B4(void);
s32 fn_1_8540(s16 boxno);
s32 fn_1_8C30(s16 boxno);
s32 fn_1_9E14(void);
s32 fn_1_9E4C(void);

void fn_1_A8C0(s16 boxno);
void fn_1_BA80(s16 boxno);

s32 fn_1_61B4(void)
{
    float temp_f31;
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s32 temp_r27;
    s16 temp_r26;
    float sp10[2];
    OSTime sp8;
    HuWinMesMaxSizeGet(1, sp10, MAKE_MESSID(0x10, 0x3D));
    lbl_1_bss_146 = HuWinExCreateStyled(-10000, 316, sp10[0], sp10[1], -1, 0);
    HuWinAttrSet(lbl_1_bss_146, 0x800);
    HuWinBGTPLvlSet(lbl_1_bss_146, 0);
    HuWinMesSpeedSet(lbl_1_bss_146, 0);
    temp_r30 = -1;
    for (temp_r29 = lbl_1_bss_88 = 0; temp_r29 < 3; temp_r29++) {
        lbl_1_bss_EE[temp_r29] = -1;
        lbl_1_bss_E8[temp_r29] = -1;
        lbl_1_bss_140[temp_r29] = 0;
        temp_r27 = fn_1_76B4(SaveFileNameTbl[temp_r29], curSlotNo);
        if (temp_r27 == 0) {
            temp_r27 = fn_1_83B4();
            if (temp_r27 == 0) {
                lbl_1_bss_140[temp_r29] = 1;
                if (lbl_1_bss_88 == 0) {
                    temp_r30 = temp_r29;
                }
                lbl_1_bss_88++;
                if (SLCheckSumCheck()) {
                    fn_1_A8C0(temp_r29);
                }
            }
            fn_1_9E14();
        }
        if (temp_r27 != 0 && temp_r27 != -4) {
            HuWinKill(lbl_1_bss_146);
            return 0;
        }
    }
    fn_1_9E4C();
    if (temp_r30 == -1) {
        temp_r30 = 0;
    }
    lbl_1_bss_120[0] = lbl_1_bss_120[1] = lbl_1_bss_120[2] = 1;
    UnMountCnt = 0;
    for (temp_r29 = 0; temp_r29 <= 20; temp_r29++) {
        temp_f31 = sind(90.0f * (temp_r29 / 20.0f));
        for (temp_r28 = 0; temp_r28 < 3; temp_r28++) {
            Hu3DModelScaleSet(lbl_1_bss_19A[temp_r28 + 8], temp_f31, temp_f31, temp_f31);
            Hu3DModelScaleSet(lbl_1_bss_19A[temp_r28 + 11], temp_f31, temp_f31, temp_f31);
        }
        HuPrcVSleep();
    }
    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x07));
    HuWinMesWait(lbl_1_bss_148);
    fn_1_7628(temp_r30, 1);
    if (lbl_1_bss_88 == 0) {
        HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x40));
    }
    else {
        if (lbl_1_bss_88 == 3) {
            HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x3F));
        }
        else {
            HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x3D));
        }
    }
    HuWinDispOn(lbl_1_bss_146);
    fn_1_BA80(temp_r30);
    if (UnMountCnt & (1 << curSlotNo)) {
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x50));
        HuWinMesWait(lbl_1_bss_148);
        temp_r31 = 0;
    }
    else {
        UnMountCnt = 0;
        while (1) {
            HuPrcVSleep();
            if (UnMountCnt & (1 << curSlotNo)) {
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x50));
                HuWinMesWait(lbl_1_bss_148);
                temp_r31 = 0;
                break;
            }
            temp_r26 = 0;
            if (HuPadDStkRep[0] & 0x1) {
                temp_r26 = -1;
            }
            else if (HuPadDStkRep[0] & 0x2) {
                temp_r26 = 1;
            }
            if (temp_r26) {
                fn_1_7628(temp_r30, 0);
                temp_r30 += temp_r26;
                if (temp_r30 < 0) {
                    temp_r30 = 2;
                }
                else if (temp_r30 >= 3) {
                    temp_r30 = 0;
                }
                HuAudFXPlay(0);
                fn_1_7628(temp_r30, 1);
                fn_1_BA80(temp_r30);
                HuPrcSleep(10);
            }
            if ((HuPadBtnDown[0] & PAD_BUTTON_X) && lbl_1_bss_140[temp_r30]) {
                UnMountCnt = 0;
                temp_r31 = fn_1_76B4(SaveFileNameTbl[temp_r30], curSlotNo);
                if (temp_r31 < 0) {
                    temp_r31 = 0;
                    break;
                }
                if (!lbl_1_bss_140[temp_r30]) {
                    continue;
                }
                HuWinDispOff(lbl_1_bss_146);
                HuAudFXPlay(2);
                HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_288[temp_r30]), 1);
                HuWinAttrSet(lbl_1_bss_148, 0x10);
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x08));
                HuWinMesWait(lbl_1_bss_148);
                temp_r31 = HuWinChoiceGet(lbl_1_bss_148, 1);
                if (temp_r31 == 0) {
                    temp_r31 = fn_1_8540(temp_r30);
                    if (temp_r31 == 0) {
                        break;
                    }
                }
                if (UnMountCnt & (1 << curSlotNo)) {
                    continue;
                }
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x07));
                HuWinMesWait(lbl_1_bss_148);
                if (lbl_1_bss_88 == 0) {
                    HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x40));
                }
                else if (lbl_1_bss_88 == 3) {
                    HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x3F));
                }
                else {
                    HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x3D));
                }
                HuWinDispOn(lbl_1_bss_146);
                fn_1_BA80(temp_r30);
                continue;
            }
            else if (HuPadBtnDown[0] & PAD_BUTTON_Y) {
                UnMountCnt = 0;
                if (HuCardSlotCheck(curSlotNo) < 0) {
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
                    HuWinMesWait(lbl_1_bss_148);
                    temp_r31 = 0;
                    break;
                }
                if (!lbl_1_bss_140[temp_r30]) {
                    continue;
                }
                for (temp_r29 = 0; temp_r29 < 3; temp_r29++) {
                    if (!lbl_1_bss_140[temp_r29]) {
                        break;
                    }
                }
                if (temp_r29 == 3) {
                    continue;
                }
                HuWinDispOff(lbl_1_bss_146);
                HuAudFXPlay(2);
                if (fn_1_8C30(temp_r30) == 0) {
                    temp_r31 = 0;
                    break;
                }
                if (UnMountCnt & (1 << curSlotNo)) {
                    continue;
                }
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x07));
                HuWinMesWait(lbl_1_bss_148);
                if (lbl_1_bss_88 == 0) {
                    HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x40));
                }
                else if (lbl_1_bss_88 == 3) {
                    HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x3F));
                }
                else {
                    HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x3D));
                }
                HuWinDispOn(lbl_1_bss_146);
                fn_1_BA80(temp_r30);
                continue;
            }
            else if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                UnMountCnt = 0;
                HuWinDispOff(lbl_1_bss_146);
                HuCardMount(curSlotNo);
                if (HuCardSlotCheck(curSlotNo) < 0) {
                    HuAudFXPlay(4);
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
                    HuWinMesWait(lbl_1_bss_148);
                    temp_r31 = 0;
                    break;
                }
                if (SLSerialNoCheck() == 0) {
                    HuAudFXPlay(4);
                    HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x45));
                    HuWinMesWait(lbl_1_bss_148);
                    temp_r31 = 0;
                    break;
                }
                HuAudFXPlay(2097);
                SLCurBoxNoSet(temp_r30);
                if (!lbl_1_bss_140[temp_r30]) {
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x0B));
                    HuWinMesWait(lbl_1_bss_148);
                    sp8 = OSGetTime();
                    SLSaveDataMake(1, &sp8);
                    GWGameStatReset();
                    #if VERSION_PAL
                    _ClearFlag(0x1000B);
                    #endif
                    GWGameStat.sound_mode = msmSysGetOutputMode();
                    SLCommonSet();
                    fn_1_B8CC(MAKE_MESSID(16, 0x3C));
                    HuPrcSleep(20);
                    if (UnMountCnt & (1 << curSlotNo)) {
                        fn_1_BA20();
                        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x50));
                        HuWinMesWait(lbl_1_bss_148);
                        temp_r31 = 0;
                        break;
                    }
                    temp_r27 = fn_1_7B74(temp_r30);
                    fn_1_BA20();
                    if (temp_r27 != 0) {
                        temp_r31 = 1;
                        break;
                    }
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4F));
                    HuWinAttrSet(lbl_1_bss_148, 0x10);
                    HuWinMesWait(lbl_1_bss_148);
                    temp_r31 = HuWinChoiceGet(lbl_1_bss_148, 1);
                    if (temp_r31 == 0) {
                        SLSaveFlagSet(0);
                        temp_r31 = 1;
                        break;
                    }
                    HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x52), 0);
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4C));
                    HuWinMesWait(lbl_1_bss_148);
                    while (!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
                        HuPrcVSleep();
                    }
                    temp_r31 = 0;
                    break;
                }
                else {
                    if (!fn_1_76B4(SaveFileNameTbl[temp_r30], curSlotNo)) {
                        if (!fn_1_83B4()) {
                            if (SLCheckSumCheck()) {
                                fn_1_9E14();
                                SLLoadGameStat();
                                #if VERSION_PAL
                                if(GwLanguageSave != -1) {
                                    GWGameStat.language = GwLanguageSave;
                                }
                                GwLanguage = GWGameStat.language;
                                _ClearFlag(0x1000B);
                                #endif
                                temp_r31 = 1;
                                break;
                            }
                            HuWinHomeClear(lbl_1_bss_148);
                            HuPrcSleep(60);
                            if (UnMountCnt & (1 << curSlotNo)) {
                                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x50));
                                HuWinMesWait(lbl_1_bss_148);
                                temp_r31 = 0;
                                break;
                            }
                            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_288[temp_r30]), 0);
                            HuWinAttrSet(lbl_1_bss_148, 0x10);
                            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x3A));
                            HuWinMesWait(lbl_1_bss_148);
                            temp_r31 = HuWinChoiceGet(lbl_1_bss_148, 1);
                            if (!temp_r31) {
                                temp_r31 = fn_1_8540(temp_r30);
                                if (temp_r31 == 0) {
                                    break;
                                }
                                if (HuCardMount(curSlotNo) < 0) {
                                    temp_r31 = 0;
                                    break;
                                }
                            }
                        }
                        else {
                            temp_r31 = 0;
                        }
                    }
                    else {
                        temp_r31 = 0;
                    }
                    if (temp_r31 == 0) {
                        break;
                    }
                    if (UnMountCnt & (1 << curSlotNo)) {
                        continue;
                    }
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x07));
                    HuWinMesWait(lbl_1_bss_148);
                    if (lbl_1_bss_88 == 0) {
                        HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x40));
                    }
                    else if (lbl_1_bss_88 == 3) {
                        HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x3F));
                    }
                    else {
                        HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x3D));
                    }
                    HuWinDispOn(lbl_1_bss_146);
                    fn_1_BA80(temp_r30);
                    continue;
                }
            }
            else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                temp_r31 = 0;
                break;
            }
        }
    }
    HuWinDispOff(lbl_1_bss_146);
    for (temp_r29 = 0; temp_r29 <= 20; temp_r29++) {
        temp_f31 = cosd(90.0 * (temp_r29 / 20.0));
        Hu3DModelScaleSet(lbl_1_bss_19A[curSlotNo], temp_f31, temp_f31, temp_f31);
        for (temp_r28 = 0; temp_r28 < 3; temp_r28++) {
            Hu3DModelScaleSet(lbl_1_bss_19A[temp_r28 + 8], temp_f31, temp_f31, temp_f31);
            Hu3DModelScaleSet(lbl_1_bss_19A[temp_r28 + 11], temp_f31, temp_f31, temp_f31);
        }
        if (temp_r31) {
            espScaleSet(lbl_1_bss_152[1], temp_f31, temp_f31);
        }
        HuPrcVSleep();
    }
    HuWinKill(lbl_1_bss_146);
    return temp_r31;
}

void fn_1_72DC(void)
{
    s16 index;
    WorkFilesel *work;
    s16 i;
    s32 param;
    Process *curr;
    curr = HuPrcCurrentGet();
    work = curr->user_data;
    index = work->index;
    param = work->param;
    if (param) {
        Hu3DModelAttrReset(lbl_1_bss_19A[index + 8], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_19A[index + 11], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(lbl_1_bss_19A[index + 8], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_19A[index + 11], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i <= 10; i++) {
        float scale;
        Vec pos_2d;
        Vec pos_3d;
        if (param) {
            scale = sind(90.0f * (i / 10.0f));
        }
        else {
            scale = cosd(90.0f * (i / 10.0f));
        }
        pos_2d.x = 158.0f + (index * 130);
        pos_2d.y = 230;
        pos_2d.z = 800;
        Hu3D2Dto3D(&pos_2d, 1, &pos_3d);
        pos_3d.z = 800 + (100.0f * scale);
        Hu3DModelPosSetV(lbl_1_bss_19A[index + 8], &pos_3d);
        Hu3DModelPosSetV(lbl_1_bss_19A[index + 11], &pos_3d);
        Hu3DModelScaleSet(lbl_1_bss_19A[index + 8], 1, 1, 1);
        Hu3DModelScaleSet(lbl_1_bss_19A[index + 11], 1, 1, 1);
        HuPrcVSleep();
    }
    (void)curr;
    HuMemDirectFree(work);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_7628(s16 boxno, s32 flag)
{
    WorkFilesel *work;
    Process *parent;
    Process *child;

    parent = HuPrcCurrentGet();
    child = HuPrcChildCreate(fn_1_72DC, 50, 8192, 0, parent);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkFilesel), MEMORY_DEFAULT_NUM);
    child->user_data = work;
    work->index = boxno;
    work->param = flag;
}

s32 fn_1_76B4(char *name, s16 slotno)
{
    s32 result;
    s16 choice;
    s16 filecnt;
    filecnt = 0;
    while (1) {
        filecnt++;
        result = HuCardMount(slotno);
        if (result == 0) {
            result = HuCardOpen(slotno, name, &curFileInfo);
            if (result == 0 || result == -4) {
                if (SLSerialNoCheck()) {
                    return result;
                }
            }
        }
        if (result == -2) {
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[slotno]), 0);
            #if VERSION_PAL
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x39));
            #else
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x37));
            #endif
            HuWinMesWait(lbl_1_bss_148);
            return result;
        }
        if (result == -128 || filecnt > 3) {
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[slotno]), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
            HuWinMesWait(lbl_1_bss_148);
            return result;
        }
        else if (result == -3) {
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
            HuWinMesWait(lbl_1_bss_148);
            return result;
        }
        else if (result == -4 || !SLSerialNoCheck()) {
            OSReport("Card Open Error:No File\n");
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x45));
            HuWinMesWait(lbl_1_bss_148);
            break;
        }
        else if (result == -6) {
            UnMountCnt = 0;
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[slotno]), 0);
            HuWinAttrSet(lbl_1_bss_148, 0x10);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x04));
            HuWinMesWait(lbl_1_bss_148);
            choice = HuWinChoiceGet(lbl_1_bss_148, 1);
            if (choice == 0) {
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4E));
                HuWinMesWait(lbl_1_bss_148);
                choice = HuWinChoiceGet(lbl_1_bss_148, 1);
                if (choice == 0) {
                    fn_1_B8CC(MAKE_MESSID(16, 0x38));
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x0B));
                    HuWinMesWait(lbl_1_bss_148);
                    HuPrcSleep(60);
                    if (UnMountCnt & (1 << curSlotNo)) {
                        fn_1_BA20();
                        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x50));
                        HuWinMesWait(lbl_1_bss_148);
                    }
                    else {
                        _SetFlag(0x30000);
                        result = HuCardFormat(slotno);
                        _ClearFlag(0x30000);
                        if (result == 0) {
                            SLSerialNoGet();
                        }
                        fn_1_BA20();
                        if (result == -128) {
                            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x36));
                            HuWinMesWait(lbl_1_bss_148);
                            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
                            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
                            HuWinMesWait(lbl_1_bss_148);
                            return result;
                        }
                        else if (result == -3) {
                            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
                            HuWinMesWait(lbl_1_bss_148);
                            return result;
                        }
                    }
                }
                else {
                    return result;
                }
                continue;
            }
            return result;
        }
        break;
    }
    return result;
}

s32 fn_1_7B74(s16 boxno)
{
    s32 result;
    s32 i;
    result = HuCardMount(curSlotNo);
    if (result == 0 && !SLSerialNoCheck()) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x45));
        HuWinMesWait(lbl_1_bss_148);
    }
    else {
        result = HuCardSectorSizeGet(curSlotNo);
        if (result == -3) {
            fn_1_BA20();
            OSReport("SectorSize Check Error:No Card %d\n", curSlotNo);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
            HuWinMesWait(lbl_1_bss_148);
        }
        else {
            if (result != 8192) {
                fn_1_BA20();
                HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x39));
                HuWinMesWait(lbl_1_bss_148);
            }
            else {
                u32 byteNotUsed;
                u32 filesNotUsed;
                result = HuCardFreeSpaceGet(curSlotNo, &byteNotUsed, &filesNotUsed);
                if (filesNotUsed == 0 && byteNotUsed < SAVE_BUF_SIZE) {
                    fn_1_BA20();
                    HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4A));
                    HuWinMesWait(lbl_1_bss_148);
                }
                else if (filesNotUsed == 0) {
                    fn_1_BA20();
                    HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4A));
                    HuWinMesWait(lbl_1_bss_148);
                }
                else if (byteNotUsed < SAVE_BUF_SIZE) {
                    fn_1_BA20();
                    HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4A));
                    HuWinMesWait(lbl_1_bss_148);
                }
                else {
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x0B));
                    HuWinMesWait(lbl_1_bss_148);
                    for (i = 0; i <= 40; i++) {
                        float time = i / 40.0;
                        Hu3DModelTPLvlSet(lbl_1_bss_19A[boxno + 8], 0.6 + (0.4 * time));
                        Hu3DModelTPLvlSet(lbl_1_bss_19A[boxno + 11], 0.3 + (0.7 * time));
                        HuPrcVSleep();
                    }
                    _SetFlag(0x30000);
                    result = HuCardCreate(curSlotNo, SaveFileNameTbl[boxno], SAVE_BUF_SIZE, &curFileInfo);
                    if (result == -3) {
                        _ClearFlag(0x30000);
                        fn_1_BA20();
                        OSReport("File Create Error:No Card\n");
                        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
                        HuWinMesWait(lbl_1_bss_148);
                    }
                    else if (result == -2) {
                        _ClearFlag(0x30000);
                        fn_1_BA20();
                        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
                        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x37));
                        HuWinMesWait(lbl_1_bss_148);
                    }
                    else if (result < 0) {
                        _ClearFlag(0x30000);
                        fn_1_BA20();
                        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
                        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
                        HuWinMesWait(lbl_1_bss_148);
                    }
                    else {
                        result = fn_1_812C();
                        _ClearFlag(0x30000);
                        if (result != 0) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

s32 fn_1_812C(void)
{
    s32 result;
    SLCheckSumSet();
    _SetFlag(0x30000);
    result = HuCardWrite(&curFileInfo, &saveBuf.buf[0], SAVE_BUF_SIZE, 0);
    _ClearFlag(0x30000);
    if (result == -3) {
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    if (result == -2) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x37));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    if (result < 0) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    result = SLStatSet(0);
    if (result == -3) {
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    if (result == -2) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x37));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    if (result < 0) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    return 1;
}

s32 fn_1_83B4(void)
{
    s32 result;
    result = HuCardRead(&curFileInfo, &saveBuf.buf[0], SAVE_BUF_SIZE, 0);
    if (result == -3) {
        OSReport("Card Read Error:No Card\n");
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
        HuWinMesWait(lbl_1_bss_148);
    }
    else if (result == -4 || !SLSerialNoCheck()) {
        OSReport("Card Read Error:No File\n", result);
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x45));
        HuWinMesWait(lbl_1_bss_148);
    }
    else if (result < 0) {
        OSReport("Card Read Error:Fatal Error %d\n", result);
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
        HuWinMesWait(lbl_1_bss_148);
    }
    return result;
}

s32 fn_1_8540(s16 boxno)
{
    float scale;
    s32 result;
    s32 time;
    AnimData *sprite;
    result = HuCardMount(curSlotNo);
    if (result == -3) {
        OSReport("Card Delete Error:No Card\n");
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    if (result == -4 || !SLSerialNoCheck()) {
        OSReport("Card Delete Error:No File\n", result);
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x45));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    if (result < 0) {
        OSReport("Card Delete Error:Fatal Error %d\n", result);
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }

    fn_1_B8CC(MAKE_MESSID(16, 0x3B));
    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x0B));
    HuWinMesWait(lbl_1_bss_148);
    HuPrcSleep(60);
    if (UnMountCnt & (1 << curSlotNo)) {
        fn_1_BA20();
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x50));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    else {
        _SetFlag(0x30000);
        result = HuCardDelete(curSlotNo, SaveFileNameTbl[boxno]);
        _ClearFlag(0x30000);
        fn_1_BA20();
        if (result == -3) {
            OSReport("Card Delete Error:No Card\n");
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x02));
            HuWinMesWait(lbl_1_bss_148);
            return 0;
        }
        if (result == -4 || !SLSerialNoCheck()) {
            OSReport("Card Delete Error:No File\n", result);
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x45));
            HuWinMesWait(lbl_1_bss_148);
            return 0;
        }
        if (result < 0) {
            OSReport("Card Delete Error:Fatal Error %d\n", result);
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x53));
            HuWinMesWait(lbl_1_bss_148);
            return 0;
        }
        for (time = 0; time <= 10; time++) {
            scale = cosd(90.0 * (time / 10.0));
            Hu3DModelScaleSet(lbl_1_bss_19A[boxno + 8], scale, scale, scale);
            HuPrcVSleep();
        }
        Hu3DAnimKill(lbl_1_bss_13A[boxno]);
        Hu3DAnimKill(lbl_1_bss_134[boxno]);
        sprite = HuSprAnimRead(HuDataReadNum(lbl_1_data_21C[8], MEMORY_DEFAULT_NUM));
        lbl_1_bss_13A[boxno] = Hu3DAnimCreate(sprite, lbl_1_bss_19A[boxno + 8], "star");
        sprite = HuSprAnimRead(HuDataReadNum(lbl_1_data_21C[17], MEMORY_DEFAULT_NUM));
        lbl_1_bss_134[boxno] = Hu3DAnimCreate(sprite, lbl_1_bss_19A[boxno + 11], "star");
        lbl_1_bss_EE[boxno] = -1;
        Hu3DModelTPLvlSet(lbl_1_bss_19A[boxno + 8], 0.6f);
        Hu3DModelTPLvlSet(lbl_1_bss_19A[boxno + 11], 0.3f);
        for (time = 0; time <= 20; time++) {
            scale = sind(90.0 * (time / 20.0));
            Hu3DModelScaleSet(lbl_1_bss_19A[boxno + 8], scale, scale, scale);
            HuPrcVSleep();
        }
        lbl_1_bss_140[boxno] = 0;
        lbl_1_bss_88--;
        return 1;
    }
}

s32 fn_1_8C30(s16 boxno)
{
    float temp_f31;
    s16 temp_r31;
    s16 temp_r30;
    s32 temp_r29;
    s16 temp_r26;
    s16 temp_r25;
    AnimData *temp_r19;
    Vec sp60;
    Vec sp54;
    Vec sp48;
    Vec sp3C;
    s32 sp38;
    s32 sp34;
    Process *sp30;
    ModelData *sp2C;
    sp30 = HuPrcCurrentGet();
    OSReport("Card Copy Seq.:Open\n");
    temp_r29 = fn_1_76B4(SaveFileNameTbl[boxno], curSlotNo);
    if (temp_r29 < 0 || !SLSerialNoCheck()) {
        return 0;
    }
    OSReport("Card Copy Seq.:Read\n");
    temp_r29 = fn_1_83B4();
    if (temp_r29 != 0) {
        return 0;
    }
    OSReport("Card Copy Seq.:CheckSum Check\n");
    if (!SLCheckSumCheck()) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_288[boxno]), 0);
        HuWinAttrSet(lbl_1_bss_148, 0x10);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x3A));
        HuWinMesWait(lbl_1_bss_148);
        temp_r29 = HuWinChoiceGet(lbl_1_bss_148, 1);
        if (temp_r29 != 0) {
            return 1;
        }
        else {
            temp_r29 = fn_1_8540(boxno);
            return temp_r29;
        }
    }
    if (!SLSerialNoCheck()) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x45));
        HuWinMesWait(lbl_1_bss_148);
        return 0;
    }
    temp_r29 = HuCardFreeSpaceGet(curSlotNo, (u32 *)&sp34, (u32 *)&sp38);
    if (sp38 == 0 && sp34 < SAVE_BUF_SIZE) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4A));
        HuWinMesWait(lbl_1_bss_148);
        return 1;
    }
    else if (sp38 == 0) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4A));
        HuWinMesWait(lbl_1_bss_148);
        return 1;
    }
    else if (sp34 < SAVE_BUF_SIZE) {
        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x4A));
        HuWinMesWait(lbl_1_bss_148);
        return 1;
    }
    for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
        if (!lbl_1_bss_140[temp_r30]) {
            break;
        }
    }
    if (temp_r30 == 3) {
        return 1;
    }
    temp_r31 = temp_r30;
    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x09));
    HuWinMesWait(lbl_1_bss_148);
    HuWinMesSet(lbl_1_bss_146, MAKE_MESSID(16, 0x35));
    HuWinDispOn(lbl_1_bss_146);
    lbl_1_bss_90 = boxno;
    Hu3DModelAttrReset(lbl_1_bss_19A[23], HU3D_ATTR_DISPOFF);
    sp2C = &Hu3DData[lbl_1_bss_19A[boxno + 8]];
    Hu3DModelPosSetV(lbl_1_bss_19A[23], &sp2C->pos);
    for (temp_r30 = 1; temp_r30 <= 10; temp_r30++) {
        temp_f31 = 0.7 + (0.3 * (temp_r30 / 10.0));
        Hu3DModelScaleSet(lbl_1_bss_19A[23], temp_f31, temp_f31, temp_f31);
        HuPrcVSleep();
    }
    fn_1_7628(temp_r31, 1);
    while (1) {
        HuPrcVSleep();
        if (UnMountCnt & (1 << curSlotNo)) {
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x50));
            HuWinMesWait(lbl_1_bss_148);
            break;
        }
        else {
            temp_r26 = 0;
            if (HuPadDStkRep[0] & 0x1) {
                temp_r26 = -1;
            }
            else if (HuPadDStkRep[0] & 0x2) {
                temp_r26 = 1;
            }
            (void)temp_r26;
            if (temp_r26) {
                HuAudFXPlay(0);
                fn_1_7628(temp_r31, 0);
                while (1) {
                    temp_r31 += temp_r26;
                    if (temp_r31 < 0) {
                        temp_r31 = 2;
                    }
                    else if (temp_r31 >= 3) {
                        temp_r31 = 0;
                    }
                    if (lbl_1_bss_140[temp_r31] == 0) {
                        break;
                    }
                }
                fn_1_7628(temp_r31, 1);
                HuPrcSleep(10);
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                HuAudFXPlay(2096);
            }
            else if (!(HuPadBtnDown[0] & PAD_BUTTON_B)) {
                continue;
            }
            else {
                HuAudFXPlay(3);
                Hu3DModelAttrSet(lbl_1_bss_19A[23], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_19A[boxno + 8], HU3D_ATTR_DISPOFF);
                fn_1_7628(temp_r31, 0);
                HuWinDispOff(lbl_1_bss_146);
                return 1;
            }
            HuWinDispOff(lbl_1_bss_146);
            temp_r29 = fn_1_76B4(SaveFileNameTbl[boxno], curSlotNo);
            if (temp_r29 >= 0 && SLSerialNoCheck()) {
                fn_1_B8CC(MAKE_MESSID(16, 0x0A));
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x0B));
                HuWinMesWait(lbl_1_bss_148);
                Hu3DModelAttrReset(lbl_1_bss_19A[boxno + 8], HU3D_ATTR_DISPOFF);
                OSReport("CheckSum Check\n");
                if (!SLCheckSumCheck()) {
                    HuPrcSleep(60);
                    HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(lbl_1_data_288[boxno]), 0);
                    HuWinAttrSet(lbl_1_bss_148, 0x10);
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x3A));
                    HuWinMesWait(lbl_1_bss_148);
                    temp_r29 = HuWinChoiceGet(lbl_1_bss_148, 1);
                    if (temp_r29 == 0) {
                        temp_r29 = fn_1_8540(boxno);
                    }
                }
                else {
                    fn_1_9E14();
                    for (temp_r30 = 0; temp_r30 <= 10; temp_r30++) {
                        temp_f31 = cosd(90.0 * (temp_r30 / 10.0));
                        Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31 + 8], temp_f31, temp_f31, temp_f31);
                        HuPrcVSleep();
                    }
                    Hu3DModelAttrSet(lbl_1_bss_19A[23], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_19A[boxno + 8], HU3D_ATTR_DISPOFF);
                    if (UnMountCnt & (1 << curSlotNo)) {
                        fn_1_BA20();
                        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x50));
                        HuWinMesWait(lbl_1_bss_148);
                    }
                    else {
                        OSReport("File Create\n");
                        SLCurBoxNoSet(temp_r31);
                        SLLoadGameStat();
                        SLSaveDataMake(0, &GWGameStat.create_time);
                        if (fn_1_7B74(temp_r31)) {
                            fn_1_9E14();
                            fn_1_A8C0(temp_r31);
                            Hu3DAnimKill(lbl_1_bss_13A[temp_r31]);
                            Hu3DAnimKill(lbl_1_bss_134[temp_r31]);
                            temp_r25 = lbl_1_bss_E8[temp_r31];
                            if (temp_r25 < 0) {
                                temp_r25 = 8;
                            }
                            (void)temp_r25;
                            temp_r19 = HuSprAnimRead(HuDataReadNum(lbl_1_data_21C[temp_r25], MEMORY_DEFAULT_NUM));
                            lbl_1_bss_13A[temp_r31] = Hu3DAnimCreate(temp_r19, lbl_1_bss_19A[temp_r31 + 8], "star");
                            temp_r19 = HuSprAnimRead(HuDataReadNum(lbl_1_data_21C[temp_r25], MEMORY_DEFAULT_NUM));
                            lbl_1_bss_134[temp_r31] = Hu3DAnimCreate(temp_r19, lbl_1_bss_19A[temp_r31 + 11], "star");
                            Hu3DModelAttrReset(lbl_1_bss_19A[temp_r31 + 11], HU3D_ATTR_DISPOFF);
                            Hu3DModelAttrSet(lbl_1_bss_19A[temp_r31 + 8], HU3D_ATTR_DISPOFF);
                            sp60.x = 158.0f + (boxno * 130);
                            sp60.y = 230;
                            sp60.z = 800;
                            Hu3D2Dto3D(&sp60, 1, &sp54);
                            sp54.z = 900;
                            sp60.x = 158.0f + (temp_r31 * 130);
                            Hu3D2Dto3D(&sp60, 1, &sp48);
                            sp48.z = 800;
                            VECSubtract(&sp48, &sp54, &sp3C);
                            Hu3DModelTPLvlSet(lbl_1_bss_19A[temp_r31 + 8], 1.0f);
                            Hu3DModelTPLvlSet(lbl_1_bss_19A[temp_r31 + 11], 1.0f);
                            lbl_1_bss_120[temp_r31] = 0;
                            for (temp_r30 = 1; temp_r30 <= 30; temp_r30++) {
                                temp_f31 = temp_r30 / 30.0;
                                sp60.x = sp3C.x * temp_f31;
                                sp60.y = sp3C.y * temp_f31;
                                sp60.z = (sp3C.z * temp_f31) + (-300 * sind(180.0f * temp_f31));
                                VECAdd(&sp60, &sp54, &sp60);
                                Hu3DModelPosSetV(lbl_1_bss_19A[temp_r31 + 11], &sp60);
                                HuPrcVSleep();
                            }
                            lbl_1_bss_120[temp_r31] = 1;
                            fn_1_BA20();
                            lbl_1_bss_140[temp_r31] = 1;
                            lbl_1_bss_88++;
                            return 1;
                        }
                    }
                }
            }
            break;
        }
    }
    fn_1_BA20();
    Hu3DModelAttrSet(lbl_1_bss_19A[23], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_19A[boxno + 8], HU3D_ATTR_DISPOFF);
    for (temp_r30 = 0; temp_r30 <= 10; temp_r30++) {
        temp_f31 = sind(90.0 * (temp_r30 / 10.0));
        Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31 + 8], temp_f31, temp_f31, temp_f31);
        HuPrcVSleep();
    }
    fn_1_7628(temp_r31, 0);
    return 0;
}

s32 fn_1_9E14(void)
{
    s32 result = HuCardClose(&curFileInfo);
    return result;
}

s16 lbl_1_data_400[] = { 15, 15, 13, 15, 15, 8, 15, 15, 8, 15, 15 };

s32 fn_1_9E4C(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    ModelData *temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    AnimData *temp_r24;
    s16 temp_r23;
    AnimData *temp_r22;
    Mtx sp24;
    Vec sp18;
    Vec spC;
    WindowData *sp8;
    temp_r23 = -1;
    sp8 = &winData[lbl_1_bss_148];
    OSReport("Init\n");
    MTXScale(sp24, 0.5f, 0.5f, 0.5f);
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        if (lbl_1_bss_116[temp_r31] != -1) {
            HuSprGrpKill(lbl_1_bss_116[temp_r31]);
        }
    }
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        if (lbl_1_bss_110[temp_r31] != -1) {
            HuSprGrpKill(lbl_1_bss_110[temp_r31]);
        }
    }
    lbl_1_bss_FC = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x22), MEMORY_DEFAULT_NUM));
    lbl_1_bss_F8 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x23), MEMORY_DEFAULT_NUM));
    lbl_1_bss_F4 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x25), MEMORY_DEFAULT_NUM));
    temp_r22 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x24), MEMORY_DEFAULT_NUM));
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        Hu3DModelAttrSet(lbl_1_bss_19A[temp_r31 + 8], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_19A[temp_r31 + 11], HU3D_ATTR_DISPOFF);
        temp_r27 = lbl_1_bss_E8[temp_r31];
        if (temp_r27 < 0 || temp_r27 >= 8) {
            temp_r27 = 8;
        }
        if (lbl_1_bss_13A[temp_r31] != -1) {
            Hu3DAnimKill(lbl_1_bss_13A[temp_r31]);
        }
        if (lbl_1_bss_134[temp_r31] != -1) {
            Hu3DAnimKill(lbl_1_bss_134[temp_r31]);
        }
        temp_r24 = HuSprAnimRead(HuDataReadNum(lbl_1_data_21C[temp_r27], MEMORY_DEFAULT_NUM));
        lbl_1_bss_13A[temp_r31] = Hu3DAnimCreate(temp_r24, lbl_1_bss_19A[temp_r31 + 8], "star");
        temp_r24 = HuSprAnimRead(HuDataReadNum(lbl_1_data_21C[temp_r27 + 9], MEMORY_DEFAULT_NUM));
        lbl_1_bss_134[temp_r31] = Hu3DAnimCreate(temp_r24, lbl_1_bss_19A[temp_r31 + 11], "star");
        if (!lbl_1_bss_140[temp_r31]) {
            Hu3DModelTPLvlSet(lbl_1_bss_19A[temp_r31 + 8], 0.6f);
            Hu3DModelTPLvlSet(lbl_1_bss_19A[temp_r31 + 11], 0.3f);
        }
        else {
            Hu3DModelTPLvlSet(lbl_1_bss_19A[temp_r31 + 8], 1.0f);
            Hu3DModelTPLvlSet(lbl_1_bss_19A[temp_r31 + 11], 1.0f);
        }
        sp18.x = 158.0f + (temp_r31 * 130);
        sp18.y = 230;
        sp18.z = 800;
        Hu3D2Dto3D(&sp18, 1, &spC);
        spC.z = 800;
        Hu3DModelPosSetV(lbl_1_bss_19A[temp_r31 + 8], &spC);
        Hu3DModelPosSetV(lbl_1_bss_19A[temp_r31 + 11], &spC);
        Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31 + 8], 0, 0, 0);
        Hu3DModelScaleSet(lbl_1_bss_19A[temp_r31 + 11], 0, 0, 0);
        temp_r28 = &Hu3DData[lbl_1_bss_19A[temp_r31 + 8]];
        MTXCopy(sp24, temp_r28->unk_F0);
        temp_r28 = &Hu3DData[lbl_1_bss_19A[temp_r31 + 11]];
        MTXCopy(sp24, temp_r28->unk_F0);
        lbl_1_bss_116[temp_r31] = HuSprGrpCreate(9);
        temp_r29 = HuSprCreate(lbl_1_bss_FC, 3000, 0);
        HuSprGrpMemberSet(lbl_1_bss_116[temp_r31], 0, temp_r29);
        HuSprPosSet(lbl_1_bss_116[temp_r31], 0, -48, 0);
        for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
            temp_r29 = HuSprCreate(lbl_1_bss_F8, 3000, 0);
            HuSprGrpMemberSet(lbl_1_bss_116[temp_r31], temp_r30 + 1, temp_r29);
            HuSprPosSet(lbl_1_bss_116[temp_r31], temp_r30 + 1, (temp_r30 * 24) - 24, 0);
        }
        temp_r29 = HuSprCreate(lbl_1_bss_F4, 3000, 0);
        HuSprGrpMemberSet(lbl_1_bss_116[temp_r31], 5, temp_r29);
        HuSprPosSet(lbl_1_bss_116[temp_r31], 5, 16, 0);
        HuSprGrpScissorSet(lbl_1_bss_116[temp_r31], 0, 16, 640, 448);
        lbl_1_bss_110[temp_r31] = HuSprGrpCreate(11);
        for (temp_r30 = temp_r25 = 0; temp_r30 < 11; temp_r30++) {
            temp_r25 += lbl_1_data_400[temp_r30];
        }
        for (temp_r30 = temp_r26 = 0; temp_r30 < 11; temp_r30++) {
            temp_r29 = HuSprCreate(temp_r22, 3000, 0);
            HuSprGrpMemberSet(lbl_1_bss_110[temp_r31], temp_r30, temp_r29);
            HuSprPosSet(lbl_1_bss_110[temp_r31], temp_r30, -(temp_r25 / 2) + 8 + temp_r26, 0);
            temp_r26 += lbl_1_data_400[temp_r30];
        }
        HuSprAttrSet(lbl_1_bss_110[temp_r31], 5, 4);
        HuSprBankSet(lbl_1_bss_110[temp_r31], 2, 10);
        HuSprBankSet(lbl_1_bss_110[temp_r31], 8, 11);
        HuSprGrpScissorSet(lbl_1_bss_110[temp_r31], 0, 16, 640, 448);
    }
    MTXScale(sp24, 0.45f, 0.45f, 0.45f);
    temp_r28 = &Hu3DData[lbl_1_bss_19A[23]];
    Hu3DModelAttrSet(lbl_1_bss_19A[23], HU3D_MOTATTR_LOOP);
    MTXCopy(sp24, temp_r28->unk_F0);
    return temp_r23;
}

void fn_1_A8C0(s16 boxno)
{
    SLLoadGameStat();
    SLLoadBoardStory();
    lbl_1_bss_EE[boxno] = GWGameStat.total_stars;
    lbl_1_bss_D0[boxno] = GWGameStat.create_time;
    lbl_1_bss_E8[boxno] = GWSystem.storyChar;
    lbl_1_bss_C4[boxno] = GWGameStat.story_continue;
    lbl_1_bss_B8[boxno] = GWGameStat.party_continue;
    if (GWGameStat.story_continue) {
        SLLoadBoardStory();
        lbl_1_bss_A4[boxno] = GWSystem.board;
        lbl_1_bss_AC[boxno] = 0;
    }
    if (GWGameStat.party_continue) {
        SLLoadBoard();
        lbl_1_bss_9E[boxno] = GWSystem.board;
        lbl_1_bss_98[boxno] = GWSystem.turn;
        lbl_1_bss_92[boxno] = GWSystem.max_turn;
    }
}

void fn_1_AAB8(void)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    ModelData *temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    Mtx sp48;
    OSCalendarTime sp20;
    Vec sp14;
    Vec sp8;
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        lbl_1_bss_12C[temp_r30] = 1;
    }
    while (1) {
        for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
            MTXScale(sp48, 0.5f, 0.5f, 0.5f);
            mtxRotCat(sp48, 0.0f, 0.0f, 15.0f * lbl_1_bss_100[temp_r30]);
            temp_r31 = &Hu3DData[lbl_1_bss_19A[temp_r30]];
            MTXCopy(sp48, temp_r31->unk_F0);
            Hu3DModelRotSet(lbl_1_bss_19A[temp_r30], 0, lbl_1_bss_8C * lbl_1_bss_108[temp_r30] * GET_ZEROSIGN(temp_r30 == 0), 0);
            if (!lbl_1_bss_12C[temp_r30]) {
                espAttrSet(lbl_1_bss_152[temp_r30 + 2], HUSPR_ATTR_DISPOFF);
            }
            else {
                temp_r31 = &Hu3DData[lbl_1_bss_19A[temp_r30 + 2]];
                if (temp_r31->attr & 0x1) {
                    temp_r31 = &Hu3DData[lbl_1_bss_19A[temp_r30 + 4]];
                }
                if (temp_r31->attr & 0x1) {
                    espAttrSet(lbl_1_bss_152[temp_r30 + 2], HUSPR_ATTR_DISPOFF);
                }
                else {
                    espAttrReset(lbl_1_bss_152[temp_r30 + 2], HUSPR_ATTR_DISPOFF);
                }
                sp8 = temp_r31->pos;
                sp8.y -= 30.0f * temp_r31->scale.x;
                Hu3D3Dto2D(&sp8, 1, &sp14);
                espPosSet(lbl_1_bss_152[temp_r30 + 2], sp14.x, sp14.y);
                espScaleSet(lbl_1_bss_152[temp_r30 + 2], temp_r31->scale.x, temp_r31->scale.x);
            }
        }
        lbl_1_bss_8C += 3.0f;
        if (lbl_1_bss_8C > 1080.0f) {
            lbl_1_bss_8C -= 360;
        }
        if (lbl_1_bss_11C == -1) {
            espAttrSet(lbl_1_bss_152[4], HUSPR_ATTR_DISPOFF);
        }
        else {
            temp_r31 = &Hu3DData[lbl_1_bss_19A[lbl_1_bss_11C]];
            if (temp_r31->attr & 0x1) {
                espAttrSet(lbl_1_bss_152[4], HUSPR_ATTR_DISPOFF);
            }
            else {
                espBankSet(lbl_1_bss_152[4], lbl_1_bss_11C);
                espAttrReset(lbl_1_bss_152[4], HUSPR_ATTR_DISPOFF);
                sp8 = temp_r31->pos;
                sp8.y += 5.0f * temp_r31->scale.x;
                Hu3D3Dto2D(&sp8, 1, &sp14);
                espPosSet(lbl_1_bss_152[4], sp14.x, sp14.y);
                espScaleSet(lbl_1_bss_152[4], temp_r31->scale.x, temp_r31->scale.x);
            }
        }
        for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
            if (!lbl_1_bss_120[temp_r30]) {
                espAttrSet(lbl_1_bss_152[temp_r30 + 5], HUSPR_ATTR_DISPOFF);
                continue;
            }
            temp_r31 = &Hu3DData[lbl_1_bss_19A[temp_r30 + 8]];
            if (temp_r31->attr & 0x1) {
                temp_r31 = &Hu3DData[lbl_1_bss_19A[temp_r30 + 11]];
            }
            temp_f30 = (900.0 + (50.0 * temp_r31->scale.x)) * sin(M_PI / 12);
            temp_f29 = (temp_r31->pos.z + (50.0 * temp_r31->scale.x)) * sin(M_PI / 12);
            temp_f31 = temp_r31->scale.x * (temp_f29 / temp_f30);
            if (temp_r31->attr & 0x1) {
                espAttrSet(lbl_1_bss_152[temp_r30 + 5], HUSPR_ATTR_DISPOFF);
            }
            else {
                espAttrReset(lbl_1_bss_152[temp_r30 + 5], HUSPR_ATTR_DISPOFF);
            }
            sp8 = temp_r31->pos;
            sp8.y += 40.0 * temp_r31->scale.x;
            sp8.z += 50.0 * temp_r31->scale.x;
            Hu3D3Dto2D(&sp8, 1, &sp14);
            espPosSet(lbl_1_bss_152[temp_r30 + 5], sp14.x, sp14.y);
            espScaleSet(lbl_1_bss_152[temp_r30 + 5], temp_f31, temp_f31);
            if (lbl_1_bss_EE[temp_r30] == -1) {
                HuSprGrpPosSet(lbl_1_bss_116[temp_r30], 0, -500);
            }
            else {
                sp8 = temp_r31->pos;
                sp8.y -= 30.0 * temp_r31->scale.x;
                sp8.z += 50.0 * temp_r31->scale.x;
                Hu3D3Dto2D(&sp8, 1, &sp14);
                HuSprGrpPosSet(lbl_1_bss_116[temp_r30], sp14.x, sp14.y);
                HuSprGrpScaleSet(lbl_1_bss_116[temp_r30], temp_f31, temp_f31);
                if (lbl_1_bss_EE[temp_r30] > 9999) {
                    for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
                        HuSprAttrSet(lbl_1_bss_116[temp_r30], temp_r28 + 1, HUSPR_ATTR_DISPOFF);
                    }
                    HuSprAttrReset(lbl_1_bss_116[temp_r30], 5, HUSPR_ATTR_DISPOFF);
                }
                else {
                    for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
                        HuSprAttrReset(lbl_1_bss_116[temp_r30], temp_r28 + 1, HUSPR_ATTR_DISPOFF);
                    }
                    HuSprAttrSet(lbl_1_bss_116[temp_r30], 5, HUSPR_ATTR_DISPOFF);
                    temp_r29 = lbl_1_bss_EE[temp_r30];
                    HuSprBankSet(lbl_1_bss_116[temp_r30], 1, temp_r29 / 1000);
                    temp_r29 -= (temp_r29 / 1000) * 1000;
                    HuSprBankSet(lbl_1_bss_116[temp_r30], 2, temp_r29 / 100);
                    temp_r29 -= (temp_r29 / 100) * 100;
                    HuSprBankSet(lbl_1_bss_116[temp_r30], 3, temp_r29 / 10);
                    temp_r29 -= (temp_r29 / 10) * 10;
                    HuSprBankSet(lbl_1_bss_116[temp_r30], 4, temp_r29);
                }
                sp8 = temp_r31->pos;
                sp8.y -= 40.0 * temp_r31->scale.x;
                sp8.z += 50.0 * temp_r31->scale.x;
                Hu3D3Dto2D(&sp8, 1, &sp14);
                HuSprGrpPosSet(lbl_1_bss_110[temp_r30], sp14.x, sp14.y);
                HuSprGrpScaleSet(lbl_1_bss_110[temp_r30], temp_f31, temp_f31);
                OSTicksToCalendarTime(lbl_1_bss_D0[temp_r30], &sp20);
                #if VERSION_PAL
                temp_r29 = sp20.mday;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 0, temp_r29 / 10);
                temp_r29 -= (temp_r29 / 10) * 10;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 1, temp_r29);
                temp_r29 = sp20.mon+1;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 3, temp_r29 / 10);
                temp_r29 -= (temp_r29 / 10) * 10;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 4, temp_r29);
                #else
                temp_r29 = sp20.mon + 1;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 0, temp_r29 / 10);
                temp_r29 -= (temp_r29 / 10) * 10;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 1, temp_r29);
                temp_r29 = sp20.mday;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 3, temp_r29 / 10);
                temp_r29 -= (temp_r29 / 10) * 10;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 4, temp_r29);
                #endif
                temp_r29 = sp20.hour;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 6, temp_r29 / 10);
                temp_r29 -= (temp_r29 / 10) * 10;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 7, temp_r29);
                temp_r29 = sp20.min;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 9, temp_r29 / 10);
                temp_r29 -= (temp_r29 / 10) * 10;
                HuSprBankSet(lbl_1_bss_110[temp_r30], 10, temp_r29);
            }
        }
        HuPrcVSleep();
    }
}

s16 lbl_1_data_41C = -1;

void fn_1_B8CC(u32 arg0)
{
    float size[2];
    if (lbl_1_data_41C != -1) {
        HuWinExCleanup(lbl_1_data_41C);
    }
    HU_WIN_INSERT_MES_SIZE_GET_PTR(MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
    HuWinMesMaxSizeGet(1, size, arg0);
    lbl_1_data_41C = HuWinExCreateStyled(-10000, 308, size[0], size[1], -1, 2);
    HuWinMesSpeedSet(lbl_1_data_41C, 0);
    HuWinExAnimIn(lbl_1_data_41C);
    HU_WIN_INSERT_MES_SET_PTR(lbl_1_data_41C, MAKE_MESSID_PTR(lbl_1_data_278[curSlotNo]), 0);
    HuWinMesSet(lbl_1_data_41C, arg0);
    HuWinMesWait(lbl_1_data_41C);
}

void fn_1_BA20(void)
{
    if (lbl_1_data_41C != -1) {
        HuWinExAnimOut(lbl_1_data_41C);
        HuWinExCleanup(lbl_1_data_41C);
        lbl_1_data_41C = -1;
    }
}

void fn_1_BA80(s16 boxno)
{
    char mesMaxTurn[4];
    char mesTurn[4];
    char mesDummy[1] = { 0 };
    if (lbl_1_bss_EE[boxno] < 0) {
        HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x11));
    }
    else {
        if (!lbl_1_bss_C4[boxno] && !lbl_1_bss_B8[boxno]) {
            HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x11), 0);
            HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(mesDummy), 1);
            HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x43));
        }
        else {
            if (!lbl_1_bss_C4[boxno]) {
                HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x11), 0);
                HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(mesDummy), 1);
                HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x12) + lbl_1_bss_9E[boxno], 2);
                sprintf(mesMaxTurn, "%2d", lbl_1_bss_98[boxno]);
                HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(mesMaxTurn), 3);
                sprintf(mesTurn, "%2d", lbl_1_bss_92[boxno]);
                HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(mesTurn), 4);
                HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x42));
            }
            else {
                if (!lbl_1_bss_B8[boxno]) {
                    HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x12) + lbl_1_bss_A4[boxno], 0);
                    if (lbl_1_bss_AC[boxno]) {
                        HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x18), 1);
                    }
                    else {
                        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(mesDummy), 1);
                    }
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x43));
                }
                else {
                    HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x12) + lbl_1_bss_A4[boxno], 0);
                    if (lbl_1_bss_AC[boxno]) {
                        HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x18), 1);
                    }
                    else {
                        HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(mesDummy), 1);
                    }
                    HuWinInsertMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x12) + lbl_1_bss_9E[boxno], 2);
                    sprintf(mesMaxTurn, "%2d", lbl_1_bss_98[boxno]);
                    HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(mesMaxTurn), 3);
                    sprintf(mesTurn, "%2d", lbl_1_bss_92[boxno]);
                    HU_WIN_INSERT_MES_SET_PTR(lbl_1_bss_148, MAKE_MESSID_PTR(mesTurn), 4);
                    HuWinMesSet(lbl_1_bss_148, MAKE_MESSID(16, 0x42));
                }
            }
        }
    }
    HuWinMesWait(lbl_1_bss_148);
}

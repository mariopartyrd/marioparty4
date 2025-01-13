#include "msm/msmsys.h"
#include "msm/msmfio.h"
#include "msm/msmmem.h"
#include "msm/msmmus.h"
#include "msm/msmse.h"
#include "msm/msmstream.h"
#include "musyx/musyx.h"

#include "game/msm.h" // TODO remove, only for decomp

typedef struct _unkStruct2 {
    char *unk0;
    s32 unk4;
    void *unk8;
    void *unkC;
    void *unk10;
    u32 unk14;
    void *unk18;
} unkStruct2;

typedef struct _unkStruct4 {
    SND_GROUPID unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} unkStruct4;

static sysData sys;

void msmSysServer(void)
{
    if (sndIsInstalled() == 1) {
        if (--sys.unk4F8 == 0) {
            sys.unk4F8 = 3;
            msmMusPeriodicProc();
            msmSePeriodicProc();
            msmStreamPeriodicProc();
        }
    }
    sys.unk4F4();
}

s32 msmSysSetAuxParam(s32 arg0, s32 arg1)
{
    SND_AUX_CALLBACK sp24;
    SND_AUX_CALLBACK sp20;
    void **var_r26;
    s32 var_r23;
    unkSubStruct2 *temp_r3;
    sysData *var_r25;
    sysData *var_r27;
    unkSubStruct *temp_r5;
    u32 var_r0;
    u8 temp_r5_2;
    unkSubStruct *temp_r4_2;

    if ((sys.unk18 != -2) && (arg0 >= 0)) {
        sys.unk18 = arg0;
    }
    if ((sys.unk19 != -2) && (arg1 >= 0)) {
        temp_r5->unk0 = arg1;
    }
    if ((sys.unk18 < 0) && (temp_r5->unk0 < 0)) {
        return 0;
    }
    var_r27 = &sys;
    var_r25 = &sys;
    var_r26 = &sp20;

    // the for loop first sets sp20 and then sp24
    for (var_r23 = 0; var_r23 < 2; var_r23++, var_r27++, var_r26++, var_r25++) {
        if (var_r27->unk18 < 0) {
            *var_r26 = NULL;
            continue;
        }
        temp_r4_2 = &sys.unk14[var_r27->unk18];
        temp_r3 = &var_r25->unk1C;
        switch (temp_r4_2->unk0) {
            case 0:
                *var_r26 = &sndAuxCallbackReverbHI;
                temp_r3->unk1C4 = temp_r4_2->unk4s[0];
                temp_r3->unk1C8 = temp_r4_2->unk4f[1];
                temp_r3->unk1CC = temp_r4_2->unk4f[2];
                temp_r3->unk1D0 = temp_r4_2->unk4f[3];
                temp_r3->unk1D4 = temp_r4_2->unk4f[4];
                temp_r3->unk1D8 = temp_r4_2->unk4f[5];
                temp_r3->unk1DC = temp_r4_2->unk4f[6];
                // var_r0 = sndAuxCallbackPrepareReverbHI();
                break;
            case 1:
                *var_r26 = &sndAuxCallbackReverbSTD;
                temp_r3->unk13C = temp_r4_2->unk4s[0];
                temp_r3->unk140 = temp_r4_2->unk4f[1];
                temp_r3->unk144 = temp_r4_2->unk4f[2];
                temp_r3->unk148 = temp_r4_2->unk4f[3];
                temp_r3->unk14C = temp_r4_2->unk4f[4];
                temp_r3->unk150 = temp_r4_2->unk4f[5];
                // var_r0 = sndAuxCallbackPrepareReverbSTD();
                break;
            case 2:
                *var_r26 = &sndAuxCallbackChorus;
                temp_r3->unk90 = temp_r4_2->unk4s[0];
                temp_r3->unk94 = temp_r4_2->unk4s[1];
                temp_r3->unk98 = temp_r4_2->unk4s[2];
                // var_r0 = sndAuxCallbackPrepareChorus();
                break;
            case 3:
                *var_r26 = &sndAuxCallbackDelay;
                temp_r3->unk3C = temp_r4_2->unk4s[0];
                temp_r3->unk48 = temp_r4_2->unk4s[3];
                temp_r3->unk54 = temp_r4_2->unk4s[6];
                temp_r3->unk40 = temp_r4_2->unk4s[1];
                temp_r3->unk4C = temp_r4_2->unk4s[4];
                temp_r3->unk58 = temp_r4_2->unk4s[7];
                temp_r3->unk44 = temp_r4_2->unk4s[2];
                temp_r3->unk50 = temp_r4_2->unk4s[5];
                temp_r3->unk5C = temp_r4_2->unk4s[8];
                // var_r0 = sndAuxCallbackPrepareDelay();
                break;
        }
        if (var_r0 == 0) {
            return 1;
        }
    }
    sndSetAuxProcessingCallbacks(0, sp20, &sys.unk1C, 0xFF, 0, sp24, &sys.unk1FC, 0xFF, 0);
    return 0;
}

s8 msmSysLoadBaseGroup(void *arg0)
{
    DVDFileInfo spC;
    sysData *var_r30;
    s32 var_r28;
    unkStruct3 *temp_r27;
    unkStruct4 *temp_r25;

    if (msmFioOpen(sys.unk0, &spC) != 1) {
        return -1;
    }
    var_r30 = &sys;
    for (var_r28 = 0; var_r28 < sys.unk3F4; var_r30 = (sysData *)((s32)var_r30 + 4), var_r28++, sys.unk8 += temp_r25->unk10) {
        temp_r27 = var_r30->unk3F8;
        temp_r25 = (unkStruct4 *)(sys.unk3EC + (sys.unk10->unk29[var_r28] << 5));
        if (msmFioRead(&spC, temp_r27, temp_r25->unk8, temp_r25->unk4 + sys.unkC->unk38) < 0) {
            msmFioClose(&spC);
            return -2;
        }
        if (msmFioRead(&spC, arg0, temp_r25->unk10, temp_r25->unkC + sys.unkC->unk40) < 0) {
            msmFioClose(&spC);
            return -2;
        }
        if (sndPushGroup((void *)(temp_r27->unk4 + (s32)temp_r27), temp_r25->unk0, arg0, (void *)(temp_r27->unk8 + (s32)temp_r27),
                (void *)(temp_r27->unk0 + (s32)temp_r27))
            == 0U) {
            msmFioClose(&spC);
            return -0x20;
        }
    }
    msmFioClose(&spC);
    return 0;
}

s32 msmSysGroupInit(DVDFileInfo *arg0);

void msmSysIrqDisable(void)
{
    if (sys.unk4EC++ == 0) {
        sys.unk4F0 = OSDisableInterrupts();
    }
}

void msmSysIrqEnable(void)
{
    if (sys.unk4EC != 0) {
        if (--sys.unk4EC == 0) {
            OSRestoreInterrupts(sys.unk4F0);
        }
    }
}

void msmSysRegularProc(void);

s32 msmSysGetOutputMode(void)
{
    return sys.unk4;
}

s32 msmSysGetSampSize(BOOL baseGrp)
{
    if (baseGrp != 0) {
        return sys.unk3E8;
    }
    return sys.unk3E4;
}

void msmSysCheckInit(void)
{
    sndIsInstalled();
}

s32 msmSysInit(MSM_INIT *init, MSM_ARAM *aram)
{
    s32 var_r26;
    s32 temp_r3;
    void *temp_r3_8;

    SND_HOOKS sp4C = { msmMemAlloc, msmMemFree };
    DVDFileInfo sp10;
    if (sndIsInstalled() == 1) {
        return -0x24;
    }
    var_r26 = 0; // retErr
    sys.unk4EC = 0;
    msmMemInit(init->heap, init->heapSize);
    msmFioInit(init->open, init->read, init->close);
    sys.unk0 = DVDConvertPathToEntrynum(init->msmPath);
    if (sys.unk0 < 0) {
        return -1;
    }
    if (msmFioOpen(sys.unk0, &sp10) != 1) {
        return -1;
    }
    if ((sys.unkC = msmMemAlloc(0x60)) == NULL) {
        msmFioClose(&sp10);
        return -0xA;
    }
    if (msmFioRead(&sp10, sys.unkC, 0x60, 0) < 0) {
        msmFioClose(&sp10);
        return -2;
    }
    if (sys.unkC->unk4 != 2) {
        msmFioClose(&sp10);
        return -0x79;
    }
    if ((sys.unk10 = msmMemAlloc(sys.unkC->unk14)) == NULL) {
        msmFioClose(&sp10);
        return -0xA;
    }
    if (msmFioRead(&sp10, sys.unk10, sys.unkC->unk14, sys.unkC->unk10) < 0) {
        msmFioClose(&sp10);
        return -2;
    }
    if (aram != NULL) {
        if (aram->skipARInit == 0) {
            ARInit(aram->stackIndex, aram->aramEnd);
            ARQInit();
            aram = (MSM_ARAM *)ARAlloc(sys.unk10->unk14);
            if ((u32)aram != ARGetBaseAddress()) {
                msmFioClose(&sp10);
                return -0x14;
            }
            sys.unk7 = 0;
        }
        else {
            if ((sys.unk10->unk14 + ARGetBaseAddress()) > aram->aramEnd) {
                msmFioClose(&sp10);
                return -0x14;
            }
            ARInit(NULL, 0);
            ARQInit();
            sys.unk7 = 1;
        }
    }
    var_r26 = msmSysGroupInit(&sp10);
    if (var_r26 != 0) {
        msmFioClose(&sp10);
        return var_r26;
    }
    var_r26 = msmMusInit(&sys.unk0, &sp10);
    if (var_r26 != 0) {
        msmFioClose(&sp10);
        return var_r26;
    }
    var_r26 = msmSeInit(&sys, &sp10);
    if (var_r26 != 0) {
        msmFioClose(&sp10);
        return var_r26;
    }
    sys.unk18 = sys.unk10->unkE == -2 ? -2 : -1;
    sys.unk19 = sys.unk10->unkF == -2 ? -2 : -1;
    if ((s32)sys.unkC->unk1C == 0) {
        var_r26 = 0;
    }
    else {
        if ((sys.unk14 = msmMemAlloc(sys.unkC->unk1C)) == NULL) {
            var_r26 = -0xA;
        }
        else {
            if (msmFioRead(&sp10, sys.unk14, sys.unkC->unk1C, sys.unkC->unk18) < 0) {
                var_r26 = -2;
            }
            else {
                var_r26 = 0;
            }
        }
    }
    if (var_r26 != 0) {
        msmFioClose(&sp10);
        return var_r26;
    }
    msmFioClose(&sp10);
    temp_r3 = msmStreamInit(init->pdtPath);
    if (temp_r3 < 0) {
        return temp_r3;
    }
    AIInit(NULL);
    sndSetHooks(&sp4C);
    if (sndInit(sys.unk10->unk0, sys.unk10->unk1, sys.unk10->unk2, 1, 0, sys.unk10->unk14) != 0) {
        return -0x1E;
    }
    sys.unk4F4 = AIRegisterDMACallback(msmSysServer);
    sys.unk4F8 = 1;
    var_r26 = msmStreamAmemAlloc();
    if (var_r26 < 0) {
        sndQuit();
        return var_r26;
    }
    sys.unk8 = var_r26 + 0x500;
    if ((s32)sys.unk10->unk10 != 0) {
        temp_r3_8 = msmMemAlloc(sys.unk10->unk10 + 0x100);
        if (temp_r3_8 == NULL) {
            msmStreamAmemFree();
            sndQuit();
            return -0xA;
        }
        msmMemFree(temp_r3_8);
    }
    if (msmSysSetAuxParam(sys.unk10->unkE, sys.unk10->unkF) != 0) {
        msmStreamAmemFree();
        sndQuit();
        return -0x1F;
    }
    msmSysSetOutputMode(OSGetSoundMode() == 0 ? SND_OUTPUTMODE_MONO : SND_OUTPUTMODE_STEREO);
    sndVolume(0x7F, 0, 0xFF);
    return 0;
}

#include "REL/w10Dll.h"
#include "game/data.h"
#include "game/board/model.h"
#include "game/board/tutorial.h"
#include "game/board/window.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/board/main.h"
#endif

static s16 hostMdl;
static s16 hostPos;
static Process *hostProc;

static s32 hostMot[2] = {
    DATA_MAKE_NUM(DATADIR_W10, 16),
    -1
};

static Vec hostPosTbl[2] = {
    {70.0f, 355.0f, 200.f},
    {70.0f, 175.0f, 200.f},
};

static void UpdateHost(void);


void HostCreate(void) {
    hostPos = 0;
    hostMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W10, 15), hostMot, 0);
    BoardModelMotionStart(hostMdl, 1, 0x40000001);
    BoardTutorialHostSet(hostMdl);
    BoardModelLayerSet(hostMdl, 6);
    hostProc = HuPrcCreate(UpdateHost, 0x1FFF, 0x1800, 0);
}

void HostWinExec(s32 arg0) {
    s16 pos;

    switch (hostPos) {
    case 0:
        pos = 5;
        break;
    case 1:
        pos = 6;
        break;
    }
    BoardWinCreate(pos, arg0, -1);
    BoardWinWait();
    BoardWinKill();
}

void HostPosSet(s16 arg0) {
    hostPos = arg0;
}

static void UpdateHost(void) {
    Mtx rot;
    Vec sp14;
    Vec sp8;
    
    while (1) {
        if (BoardIsKill() != 0) {
            BoardModelKill(hostMdl);
            BoardTutorialHostSet(-1);
            HuPrcEnd();
        }
        Hu3D2Dto3D(&hostPosTbl[hostPos], 1, &sp14);
        BoardModelPosSetV(hostMdl, &sp14);
        BoardCameraRotGet(&sp8);
        MTXRotDeg(rot, 'y', 15);
        BoardModelMtxSet(hostMdl, &rot);
        BoardModelRotSet(hostMdl, sp8.x, 0.0f, 0.0f);
        BoardModelScaleSet(hostMdl, 0.2f, 0.2f, 0.2f);
        HuPrcVSleep();        
    }
}
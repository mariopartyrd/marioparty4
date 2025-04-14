#include "REL/w10Dll.h"
#include "game/board/char_wheel.h"
#include "game/board/lottery.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/shop.h"
#include "game/board/space.h"
#include "game/board/star.h"
#include "game/board/tutorial.h"
#include "game/board/ui.h"
#include "game/board/boo_house.h"
#include "game/board/mg_setup.h"

void TutorialStartExec(void) {
    HostWinExec(0x2E0001);
}

void TutorialPreRollExec(void) {
    HostWinExec(0x2E0002);
}

void TutorialOrderExec(void) {
    HostWinExec(0x2E0003);
}

void TutorialP1StartExec(void) {
    HostWinExec(0x2E0004);
}

void TutorialP2StartExec(void) {
    HostWinExec(0x2E0005);
}

void TutorialP3StartExec(void) {
    HostWinExec(0x2E0006);
}

void TutorialP4StartExec(void) {
    HostWinExec(0x2E0007);
}

void TutorialGameStartExec(void) {
    HostWinExec(0x2E0008);
    HostWinExec(0x2E0009);
    BoardSpaceStarSetIndex(0);
    BoardModelVisibilitySet(boardStarHostMdl, 1);
}

void TutorialRollExec(void) {
    HostWinExec(0x2E000A);
}

void TutorialMoveExec(void) {
    HostWinExec(0x2E000B);
}

void TutorialLandExec(void) {

}

void TutorialLandBlueExec(void) {
    TutorialSpaceShow(0, 0x122, 0x8C);
    HostWinExec(0x2E000C);
    HostWinExec(0x2E000D);
    TutorialSpaceHide();
}

void TutorialLandRedExec(void) {
    TutorialSpaceShow(1, 0x122, 0x8C);
    HostWinExec(0x2E000E);
    TutorialSpaceHide();
}

void TutorialLandHappenExec(void) {
    TutorialSpaceShow(2, 0x122, 0x8C);
    HostWinExec(0x2E000F);
    TutorialSpaceHide();
    BoardTutorialDirInputSet(0, 0x50, 1);
}

void TutorialLandFortuneExec(void) {
    TutorialSpaceShow(3, 0x122, 0x8C);
    HostWinExec(0x2E0010);
    TutorialSpaceHide();
    HostWinExec(0x2E0011);
    BoardTutorialDirInputSet(-0x50, 0, 1);
}

void TutorialLandBowserExec(void) {
    TutorialSpaceShow(4, 0x122, 0x8C);
    HostWinExec(0x2E0012);
    TutorialSpaceHide();
    BoardTutorialDirInputSet(0, 0x50, 1);
}

void TutorialLandMushroomExec(void) {
    TutorialSpaceShow(5, 0x122, 0x8C);
    HostWinExec(0x2E0013);
    TutorialSpaceHide();
}

void TutorialMushroomMegaExec(void) {
    HostWinExec(0x2E0014);
}

void TutorialMushroomMiniExec(void) {
    HostWinExec(0x2E0015);
    BoardTutorialDirInputSet(-0x50, 0, 1);
}

void TutorialLandBattleExec(void) {
    TutorialSpaceShow(6, 0x122, 0x8C);
    HostWinExec(0x2E0016);
    TutorialSpaceHide();
}

void TutorialLandWarpExec(void) {
    TutorialSpaceShow(7, 0x122, 0x8C);
    HostWinExec(0x2E0017);
    TutorialSpaceHide();
    BoardCharWheelTargetSet(1);
}

void TutorialWarpDecideExec(void) {
    HostWinExec(0x2E0018);
}

void TutorialBlockStarExec(void) {
    s32 space;
    
    HostWinExec(0x2E0019);
    space = BoardSpaceFlagSearch(0, 1);
    BoardTutorialBlockSetPos(space, 0);
}

void TutorialBlockCoinExec(void) {
    s32 space;
    
    HostWinExec(0x2E001A);
    space = BoardSpaceFlagSearch(0, 1);
    BoardTutorialBlockSetPos(space, 0);
    BoardTutorialItemSet(0);
}

void TutorialMiniMegaExec(void) {
    HostWinExec(0x2E001B);
    BoardTutorialDirInputSet(0x50, 0, 1);
}

void TutorialMiniUseExec(void) {
    HostWinExec(0x2E001C);
}

void TutorialMiniStopExec(void) {
    HostWinExec(0x2E001D);
    BoardPlayerItemAdd(2, 1);
    BoardTutorialItemSet(1);
}

void TutorialMegaUseExec(void) {
    HostWinExec(0x2E001E);
}

void TutorialMegaDiceExec(void) {
    HostWinExec(0x2E001F);
}

void TutorialMegaStompExec(void) {
    HostWinExec(0x2E0020);
}

void TutorialMegaEventExec(void) {
    HostWinExec(0x2E0021);
}

void TutorialMegaStopExec(void) {
    HostWinExec(0x2E0022);
}

void TutorialEndExec(void) {
    s32 i;
    Vec pos;
    Vec offset;
    s32 space;
    
    HostWinExec(0x2E0023);
    for (i = 0; i < 4; i++) {
        GWPlayer[i].color = 1;
    }
    BoardMGSetupTutorialExec();
    BoardStatusShowSetAll(0);
    HostPosSet(0);
    HostWinExec(0x2E002B);
    offset.x = -33.0f;
    offset.y = offset.z = 0.0f;
    space = BoardSpaceFlagSearch(0, 0x80000);
    BoardSpacePosGet(0, space, &pos);
    BoardModelPosSetV(boardWork->focus_mdl, &pos);
    BoardCameraMotionStartEx(boardWork->focus_mdl, &offset, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    HostWinExec(0x2E002C);
    BoardShopTutorialExec(space);
    BoardCameraMotionStartEx(boardWork->focus_mdl, &offset, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    space = BoardSpaceFlagSearch(0, 0x10000000);
    BoardSpacePosGet(0, space, &pos);
    BoardModelPosSetV(boardWork->focus_mdl, &pos);
    BoardCameraMotionStartEx(boardWork->focus_mdl, &offset, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    HostWinExec(0x2E002E);
    BoardLotteryTutorialExec();
    BoardCameraMotionStartEx(boardWork->focus_mdl, &offset, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    space = BoardSpaceFlagSearch(0, 0x08000000);
    BoardSpacePosGet(0, space, &pos);
    BoardModelPosSetV(boardWork->focus_mdl, &pos);
    BoardCameraMotionStartEx(boardWork->focus_mdl, &offset, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    HostWinExec(0x2E0030);
    BoardBooHouseTutorialExec();
    BoardCameraMotionStartEx(boardWork->focus_mdl, &offset, NULL, 3200.0f, -1.0f, 30);
    BoardCameraMotionWait();
    HostWinExec(0x2E0032);
    BoardCameraTargetModelSet(BoardStarHostMdlGet());
    BoardCameraMotionWait();
    HostWinExec(0x2E0033);
    HostWinExec(0x2E0034);
    TutorialSpaceShow(8, 0x122, 0x8C);
    HostWinExec(0x2E0035);
    TutorialSpaceHide();
    TutorialSpaceShow(9, 0x122, 0x8C);
    HostWinExec(0x2E0036);
    TutorialSpaceHide();
    TutorialSpaceShow(0xA, 0x122, 0x8C);
    HostWinExec(0x2E0037);
    TutorialSpaceHide();
    HostWinExec(0x2E0038);
    HostWinExec(0x2E0039);
    if (tutorialDoneF == 0) {
        tutorialDoneF = 1;
        BoardAudSeqFadeOut(0, 0x1F3);
        BoardKill();
    }
    BoardTutorialHookSet(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

void TutorialMGStatusExec(void) {
    HostPosSet(1);
    HostWinExec(0x2E0024);
}

void TutorialMG4PExec(void) {
    HostWinExec(0x2E0025);
    GWPlayer[1].color = 2;
    GWPlayer[3].color = 2;
}

void TutorialMG2Vs2Exec(void) {
    HostWinExec(0x2E0026);
    GWPlayer[0].color = 2;
}

void TutorialMG1Vs3Exec(void) {
    HostWinExec(0x2E0027);
    GWPlayer[0].color = 1;
    GWPlayer[1].color = 1;
    GWPlayer[2].color = 1;
    GWPlayer[3].color = 2;
}

void TutorialMG1Vs3AltExec(void) {
    HostWinExec(0x2E0028);
    HostWinExec(0x2E0029);
    boardTutorialData[0] = 0;
    BoardStatusItemSet(0);
}

void TutorialShopExec(void) {
    HostWinExec(0x2E002D);
}

void TutorialLotteryExec(void) {
    HostWinExec(0x2E002F);
}

void TutorialBooHouseExec(void) {
    HostWinExec(0x2E0031);
}

void TutorialNullExec(void) {

}
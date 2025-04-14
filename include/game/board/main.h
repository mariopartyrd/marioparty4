#ifndef _BOARD_MAIN_H
#define _BOARD_MAIN_H

#include "dolphin.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/object.h"


#define BOARD_ID_MAIN1 0 // TOADS_MIDWAY_MADNESS
#define BOARD_ID_MAIN2 1 // GOOMBAS_GREEDY_GALA
#define BOARD_ID_MAIN3 2 // SHY_GUYS_JUNGLE_JAM
#define BOARD_ID_MAIN4 3 // BOOS_HAUNTED_BASH
#define BOARD_ID_MAIN5 4 // KOOPAS_SEASIDE_SOIREE
#define BOARD_ID_MAIN6 5 // BOWSERS_GNARLY_PARTY
#define BOARD_ID_TUTORIAL 6 // TUTORIAL_BOARD
#define BOARD_ID_EXTRA1 7 // MEGA_BOARD_MAYHEM
#define BOARD_ID_EXTRA2 8 // MINI_BOARD_MAD_DASH

#define BOARD_FABS(value) ((value < 0) ? -(value) : (value))

typedef struct board_focus_data {
    u16 view_type;
    s16 time;
    s16 max_time;
    float fov_start;
    float fov_end;
    float zoom_start;
    float zoom_end;
    Vec rot_start;
    Vec rot_end;
    Vec target_start;
    Vec target_end;
} BoardFocusData;

typedef struct board_camera_data {
    struct {
        u8 hide_all : 1;
        u8 moving : 1;
        u8 quaking : 1;
    };
    u16 mask;
    s16 target_mdl;
    s16 target_space;
    s32 quake_timer;
    float quake_strength;
    float fov;
    float nnear;
    float ffar;
    float aspect;
    float viewport_x;
    float viewport_y;
    float viewport_w;
    float viewport_h;
    float viewport_near;
    float viewport_far;
    Vec pos;
    Vec up;
    Vec target;
    Vec offset;
    Vec rot;
    float zoom;
    void (*pos_calc)(struct board_camera_data *);
    BoardFocusData focus;
} BoardCameraData;

extern BoardCameraData boardCamera;
SHARED_SYM extern Process *boardObjMan;
SHARED_SYM extern Process *boardMainProc;
SHARED_SYM extern u32 boardRandSeed;
extern omObjData *boardMainObj;

typedef void (*BoardFunc)(void);

typedef void (*BoardLightHook)(void);
typedef void (*BoardBowserHook)(s32 beforeF);

typedef void (*BoardCameraPosCalcFunc)(BoardCameraData *camera);

typedef void (*BoardTurnStartHook)(s32 player, s32 space);

SHARED_SYM extern BoardTurnStartHook boardTurnStartFunc;
SHARED_SYM extern void (*boardStarShowNextHook)(void);
SHARED_SYM extern void (*boardStarGiveHook)(void);
SHARED_SYM extern BoardBowserHook boardBowserHook;
SHARED_SYM extern BoardFunc boardTurnFunc;
extern BoardLightHook boardLightResetHook;
extern BoardLightHook boardLightSetHook;

void BoardCommonInit(BoardFunc create, BoardFunc destroy);
void BoardKill(void);
s32 BoardIsKill(void);
void BoardPauseDisableSet(s32 value);
s32 BoardPauseDisableGet();
void BoardSaveInit(s32 board);
void BoardStoryConfigSet(s32 mg_list, s32 diff_story);
void BoardPartyConfigSet(s32 team, s32 bonus_star, s32 mg_list, s32 max_turn, s32 p1_handicap, s32 p2_handicap, s32 p3_handicap, s32 p4_handicap);
s32 BoardTurnNext(void);
void BoardNextOvlSet(OverlayID overlay);
s32 BoardStartCheck(void);
void BoardLightHookSet(BoardLightHook set, BoardLightHook reset);
void BoardLightSetExec(void);
void BoardLightResetExec(void);
void BoardCameraBackup(void);
void BoardCameraRestore(void);
void BoardCameraScissorSet(s32 x, s32 y, s32 w, s32 h);
void BoardCameraViewSet(s32 type);
s32 BoardCameraPosGet(Vec *dst);
s32 BoardCameraTargetGet(Vec *dst);
s32 BoardCameraRotGet(Vec *dst);
float BoardCameraZoomGet();
s32 BoardCameraDirGet(Vec *dst);
s32 BoardCameraPointDirGet(Vec *point, Vec *dst);
void BoardCameraMaskSet(u16 mask);
void BoardCameraMoveSet(s32 move);
void BoardCameraOffsetSet(float x, float y, float z);
void BoardCameraTargetPlayerSet(s32 player);
void BoardCameraTargetModelSet(s16 model);
void BoardCameraTargetSpaceSet(s32 space);
void BoardCameraQuakeSet(s32 duration, float strength);
void BoardCameraQuakeReset();
void BoardCameraTargetSet(float x, float y, float z);
#ifndef __MWERKS__
void BoardCameraPosCalcFuncSet(BoardCameraPosCalcFunc func);
#endif
void BoardCameraPosSet(float x, float y, float z);
void BoardCameraXRotZoomSet(float zoom, float x_rot);
void BoardCameraZoomSet(float zoom);
void BoardCameraRotSet(float x, float y);
void BoardCameraNearFarSet(float nnear, float ffar);
void BoardCameraNearFarGet(float *nnear, float *ffar);
void BoardCameraMotionStart(s16 model_target, Vec *rot_target, float zoom_target, float fov_target);
void BoardCameraMotionStartEx(s16 model_target, Vec *rot_target, Vec *offset_end, float zoom_target, float fov_target, s16 max_time);
void BoardCameraFovSet(float fov);
s32 BoardCameraCullCheck(Vec *point, float radius);
s32 BoardCameraMotionIsDone(void);
void BoardCameraMotionWait(void);
void BoardCameraInit(void);
void BoardMGDoneFlagSet(s32 flag);
s32 BoardMGDoneFlagGet();
void BoardMGExit(void);
void BoardMGCreate(s32 arg0);
void BoardEventFlagSet(void);
void BoardEventFlagReset(void);
s32 BoardEventFlagGet(void);
void BoardMTXCalcLookAt(Mtx dest, Vec *eye, Vec *up, Vec *target);
float BoardArcSin(float value);
float BoardArcCos(float value);
void BoardRandInit(void);
u32 BoardRand(void);
u32 BoardRandMod(u32 value);
float BoardRandFloat(void);
float BoardVecDistXZCalc(Vec *vec1, Vec *vec2);
s32 BoardVecMaxDistXZCheck(Vec *vec1, Vec *vec2, float max_dist);
void BoardDAngleCalcVec(Vec *vec1);
float BoardDAngleCalc(float value);
s32 BoardDAngleCalcRange(float *value, float min, float range);
s32 BoardVecMinDistCheck(Vec *vec1, Vec *vec2, float min_dist);
void BoardFilterFadeOut(s16 len);
void BoardFilterFadeInit(s16 len, u8 max_alpha);
s32 BoardFilterFadePauseCheck(void);
s32 BoardFilterFadeCheck(void);
void BoardConfettiCreate(Vec *pos, s16 count, float range);
void BoardConfettiKill(void);
void BoardConfettiStop(void);
void BoardLast5GfxInit(void);
void BoardLast5GfxShowSet(s32 show);
void BoardTauntInit(void);
void BoardTauntKill(void);
s32 BoardDataDirReadAsync(s32 data_num);
void BoardDataAsyncWait(s32 status);

#endif

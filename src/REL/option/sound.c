#include "REL/option.h"
#include "ext_math.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/msm.h"
#include "game/process.h"
#include "game/window.h"

#include "dolphin.h"
#include "math.h"

#ifndef __MWERKS__
#include <game/audio.h>
#endif

typedef struct {
    /* 0x000 */ omObjData *object[26];
    /* 0x068 */ OptionWindow *window[13];
    /* 0x09C */ s32 execMode;
    /* 0x0A0 */ s16 sprite[19];
    /* 0x0C8 */ s32 changeTimer;
    /* 0x0CC */ s32 selectedOption;
    /* 0x0D0 */ s32 soundMode;
    /* 0x0D4 */ s32 page;
    /* 0x0D8 */ s32 cursorPos;
    /* 0x0DC */ s32 prevCursorPos;
    /* 0x0E0 */ s16 sndGrpSet;
    /* 0x0E4 */ BOOL optionSelected;
    /* 0x0E8 */ BOOL doneF;
    /* 0x0EC */ BOOL cameraDoneF;
    /* 0x0F0 */ s16 bgMusicStat;
    /* 0x0F2 */ s16 seqStat;
    /* 0x0F4 */ s16 streamStat;
    /* 0x0F6 */ s16 fxStat;
    /* 0x0F8 */ s32 cursorDelay;
    /* 0x0FC */ s32 pageDelta;
    /* 0x100 */ s32 cursorDelta;
    /* 0x104 */ float cursorTime;
    /* 0x108 */ float cursorSpeed;
    /* 0x10C */ Process *noteSpawner;
} SoundWork; // Size 0x110

typedef struct {
    /* 0x00 */ BOOL enabled;
    /* 0x04 */ s32 type;
    /* 0x08 */ s32 side;
    /* 0x0C */ float pos;
    /* 0x10 */ float speed;
} NoteWork; // Size 0x14

typedef struct {
    /* 0x00 */ BOOL enabled;
    /* 0x04 */ s32 nameMess;
    /* 0x08 */ s16 type;
    /* 0x0A */ s16 sndGrpSet;
    /* 0x0C */ s32 id;
} SndSelData; // Size 0x10

#define NUM_NOTES 16

#define MODE_DISABLED 0
#define MODE_HANDLE_INITIAL_SCREEN 1
#define MODE_HANDLE_OPTION_SEL 2
#define MODE_HANDLE_SOUND 3
#define MODE_HANDLE_MUSIC 4
#define MODE_HANDLE_VOICE 5

#define SOUND_MODE_STEREO 0
#define SOUND_MODE_MONO 1

#define NUM_BOARDS 6

#define NOTE_TYPE_QUAVER 0
#define NOTE_TYPE_QUARTER 1

#define NOTE_SIDE_LEFT 0
#define NOTE_SIDE_RIGHT 1

static void ExecZoom(omObjData *object);
static void ExecOptionSel(omObjData *object);
static void ExecOutputMode(omObjData *object);
static void ExecMusic(omObjData *object);
static void ExecVoice(omObjData *object);
static void LightSetCurr(omObjData *object, s32 id);
static void LightSetNone(omObjData *object);
static omObjData *CreateHand(void);
static void KillHand(omObjData *object);
static omObjData *CreateOutputModeHand(void);
static void KillOutputModeHand(omObjData *object);
static omObjData *CreateSystem(void);
static void KillSystem(omObjData *system);
static omObjData *CreateLightObj(s32 id, BOOL off);
static void KillLightObj(omObjData *indicator);
static void LightDispOff(omObjData *object);
static void LightDispOn(omObjData *object);
static void CreateSpr(omObjData *object);
static void KillSpr(omObjData *object);
static void OptionSelDisp(omObjData *object);
static void OptionSelHide(omObjData *object);
static void OutputModeDisp(omObjData *object);
static void OutputModeHide(omObjData *object);
static void MusicPageDisp(omObjData *object, s32 page);
static void MusicPageHide(omObjData *object);
static void VoicePageDisp(omObjData *object, s32 character);
static void VoicePageHide(omObjData *object);
static omObjData *CreateNoteObj(s32 type);
static void KillNote(omObjData *note);
static void HandleNote(omObjData *note);
static void CreateNote(omObjData *object, s32 type, s32 side, s32 color);
static void CreateNoteSpawner(omObjData *object);
static void KillNoteSpawner(omObjData *object);
static void ExecNoteSpawner(void);
static void OptionPlaySound(omObjData *object);
static void FadeSound(omObjData *object);

omObjData *optionSound;

static const s32 musicPageNameTbl[] = {
    MAKE_MESSID(47, 70),
    MAKE_MESSID(47, 81),
    MAKE_MESSID(47, 172),
    MAKE_MESSID(47, 92),
    MAKE_MESSID(47, 101),
    MAKE_MESSID(47, 109),
    MAKE_MESSID(47, 119),
    MAKE_MESSID(47, 173),
    MAKE_MESSID(47, 174),
    MAKE_MESSID(47, 129),
    MAKE_MESSID(47, 140),
    MAKE_MESSID(47, 149),
    MAKE_MESSID(47, 156),
    MAKE_MESSID(47, 176),
};

static const SndSelData musicTbl[14][10] = {
    {
        { TRUE, MAKE_MESSID(47, 71), 1, 0, 20 },
        { TRUE, MAKE_MESSID(47, 72), 2, 79, 43 },
        { TRUE, MAKE_MESSID(47, 73), 3, 81, 44 },
        { TRUE, MAKE_MESSID(47, 74), 29, 80, 45 },
        { TRUE, MAKE_MESSID(47, 76), 30, 82, 47 },
        { TRUE, MAKE_MESSID(47, 78), 1, 0, 12 },
        { TRUE, MAKE_MESSID(47, 77), 4, 83, 48 },
        { TRUE, MAKE_MESSID(47, 80), 11, 90, 40 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 79), 1, 0, 5 },
        { TRUE, MAKE_MESSID(47, 170), 33, 0, 12 },
        { TRUE, MAKE_MESSID(47, 82), 33, 0, 7 },
        { TRUE, MAKE_MESSID(47, 83), 33, 0, 4 },
        { TRUE, MAKE_MESSID(47, 171), 33, 0, 10 },
        { TRUE, MAKE_MESSID(47, 84), 33, 0, 9 },
        { TRUE, MAKE_MESSID(47, 85), 33, 0, 1 },
        { TRUE, MAKE_MESSID(47, 86), 33, 0, 3 },
        { TRUE, MAKE_MESSID(47, 87), 33, 0, 2 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 88), 33, 0, 5 },
        { TRUE, MAKE_MESSID(47, 89), 33, 0, 6 },
        { TRUE, MAKE_MESSID(47, 90), 33, 0, 11 },
        { TRUE, MAKE_MESSID(47, 91), 33, 0, 8 },
        { TRUE, MAKE_MESSID(47, 125), 1, 0, 2 },
        { TRUE, MAKE_MESSID(47, 126), 1, 0, 6 },
        { TRUE, MAKE_MESSID(47, 127), 1, 0, 9 },
        { TRUE, MAKE_MESSID(47, 128), 1, 0, 10 },
        { TRUE, MAKE_MESSID(47, 124), 12, 93, 49 },
        { TRUE, MAKE_MESSID(47, 123), 12, 93, 50 },
    },
    {
        { TRUE, MAKE_MESSID(47, 93), 5, 84, 13 },
        { TRUE, MAKE_MESSID(47, 94), 5, 84, 14 },
        { TRUE, MAKE_MESSID(47, 95), 5, 84, 15 },
        { TRUE, MAKE_MESSID(47, 96), 5, 84, 16 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 97), 6, 85, 17 },
        { TRUE, MAKE_MESSID(47, 98), 6, 85, 18 },
        { TRUE, MAKE_MESSID(47, 99), 6, 85, 19 },
        { TRUE, MAKE_MESSID(47, 100), 6, 85, 20 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 102), 7, 86, 21 },
        { TRUE, MAKE_MESSID(47, 103), 7, 86, 22 },
        { TRUE, MAKE_MESSID(47, 104), 7, 86, 23 },
        { TRUE, MAKE_MESSID(47, 105), 7, 86, 24 },
        { TRUE, MAKE_MESSID(47, 106), 7, 86, 25 },
        { TRUE, MAKE_MESSID(47, 107), 7, 86, 26 },
        { TRUE, MAKE_MESSID(47, 108), 7, 86, 27 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 110), 8, 87, 28 },
        { TRUE, MAKE_MESSID(47, 111), 8, 87, 30 },
        { TRUE, MAKE_MESSID(47, 112), 8, 87, 29 },
        { TRUE, MAKE_MESSID(47, 113), 8, 87, 31 },
        { TRUE, MAKE_MESSID(47, 114), 8, 87, 32 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 115), 9, 88, 33 },
        { TRUE, MAKE_MESSID(47, 116), 9, 88, 34 },
        { TRUE, MAKE_MESSID(47, 117), 9, 88, 35 },
        { TRUE, MAKE_MESSID(47, 118), 9, 88, 36 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 120), 10, 89, 37 },
        { TRUE, MAKE_MESSID(47, 121), 10, 89, 38 },
        { TRUE, MAKE_MESSID(47, 122), 10, 89, 39 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 130), 13, 94, 59 },
        { TRUE, MAKE_MESSID(47, 131), 13, 94, 57 },
        { TRUE, MAKE_MESSID(47, 132), 14, 95, 67 },
        { TRUE, MAKE_MESSID(47, 133), 15, 96, 68 },
        { TRUE, MAKE_MESSID(47, 134), 16, 97, 69 },
        { TRUE, MAKE_MESSID(47, 135), 17, 98, 70 },
        { TRUE, MAKE_MESSID(47, 136), 18, 99, 71 },
        { TRUE, MAKE_MESSID(47, 137), 19, 100, 72 },
        { TRUE, MAKE_MESSID(47, 138), 20, 101, 73 },
        { TRUE, MAKE_MESSID(47, 139), 21, 102, 74 },
    },
    {
        { TRUE, MAKE_MESSID(47, 141), 22, 103, 75 },
        { TRUE, MAKE_MESSID(47, 142), 23, 104, 76 },
        { TRUE, MAKE_MESSID(47, 143), 24, 105, 77 },
        { TRUE, MAKE_MESSID(47, 144), 13, 94, 58 },
        { TRUE, MAKE_MESSID(47, 175), 13, 94, 60 },
        { TRUE, MAKE_MESSID(47, 145), 1, 0, 1 },
        { TRUE, MAKE_MESSID(47, 146), 1, 0, 3 },
        { TRUE, MAKE_MESSID(47, 147), 1, 0, 4 },
        { TRUE, MAKE_MESSID(47, 148), 1, 0, 11 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 152), 25, 106, 61 },
        { TRUE, MAKE_MESSID(47, 150), 25, 106, 62 },
        { TRUE, MAKE_MESSID(47, 151), 25, 106, 63 },
        { TRUE, MAKE_MESSID(47, 155), 26, 107, 65 },
        { TRUE, MAKE_MESSID(47, 153), 26, 107, 64 },
        { TRUE, MAKE_MESSID(47, 154), 26, 107, 66 },
        { TRUE, MAKE_MESSID(47, 164), 1, 0, 13 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 157), 27, 108, 51 },
        { TRUE, MAKE_MESSID(47, 158), 27, 108, 53 },
        { TRUE, MAKE_MESSID(47, 159), 27, 108, 54 },
        { TRUE, MAKE_MESSID(47, 160), 27, 108, 52 },
        { TRUE, MAKE_MESSID(47, 161), 27, 108, 55 },
        { TRUE, MAKE_MESSID(47, 162), 27, 108, 56 },
        { TRUE, MAKE_MESSID(47, 163), 1, 0, 7 },
        { TRUE, MAKE_MESSID(47, 165), 1, 0, 22 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 177), 32, 92, 46 },
        { TRUE, MAKE_MESSID(47, 178), 31, 91, 41 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
};

static const s32 voiceCharNameTbl[12] = {
    MAKE_MESSID(0, 0),
    MAKE_MESSID(0, 1),
    MAKE_MESSID(0, 2),
    MAKE_MESSID(0, 3),
    MAKE_MESSID(0, 4),
    MAKE_MESSID(0, 5),
    MAKE_MESSID(0, 6),
    MAKE_MESSID(0, 7),
    MAKE_MESSID(47, 34),
    MAKE_MESSID(47, 44),
    MAKE_MESSID(47, 55),
    MAKE_MESSID(47, 62),
};

static const SndSelData voiceTbl[12][10] = {
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2217 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2219 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2216 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2223 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2220 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2221 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2222 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2218 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2208 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2210 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2207 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2214 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2211 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2212 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2213 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2209 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2226 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2228 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2225 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2232 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2229 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2230 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2231 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2227 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2253 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2255 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2252 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2259 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2256 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2257 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2258 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2254 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2244 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2246 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2243 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2250 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2247 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2248 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2249 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2245 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2199 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2201 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2198 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2205 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2202 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2203 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2204 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2200 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2190 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2192 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2189 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2196 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2193 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2194 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2195 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2191 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2235 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2237 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2234 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2241 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2238 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2239 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2240 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2236 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 35), 28, 109, 54 },
        { TRUE, MAKE_MESSID(47, 36), 28, 109, 55 },
        { TRUE, MAKE_MESSID(47, 37), 28, 109, 56 },
        { TRUE, MAKE_MESSID(47, 38), 28, 109, 67 },
        { TRUE, MAKE_MESSID(47, 39), 28, 109, 68 },
        { TRUE, MAKE_MESSID(47, 40), 28, 109, 69 },
        { TRUE, MAKE_MESSID(47, 41), 28, 109, 64 },
        { TRUE, MAKE_MESSID(47, 42), 28, 109, 65 },
        { TRUE, MAKE_MESSID(47, 43), 28, 109, 66 },
        { FALSE, MAKE_MESSID(47, 24), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 45), 28, 109, 75 },
        { TRUE, MAKE_MESSID(47, 46), 28, 109, 76 },
        { TRUE, MAKE_MESSID(47, 47), 28, 109, 77 },
        { TRUE, MAKE_MESSID(47, 48), 28, 109, 70 },
        { TRUE, MAKE_MESSID(47, 49), 28, 109, 71 },
        { TRUE, MAKE_MESSID(47, 50), 28, 109, 72 },
        { TRUE, MAKE_MESSID(47, 51), 28, 109, 58 },
        { TRUE, MAKE_MESSID(47, 52), 28, 109, 59 },
        { TRUE, MAKE_MESSID(47, 53), 28, 109, 60 },
        { TRUE, MAKE_MESSID(47, 54), 28, 109, 61 },
    },
    {
        { TRUE, MAKE_MESSID(47, 56), 28, 109, 62 },
        { TRUE, MAKE_MESSID(47, 57), 28, 109, 63 },
        { TRUE, MAKE_MESSID(47, 58), 28, 109, 79 },
        { TRUE, MAKE_MESSID(47, 59), 28, 109, 80 },
        { TRUE, MAKE_MESSID(47, 60), 28, 109, 73 },
        { TRUE, MAKE_MESSID(47, 61), 28, 109, 74 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 63), 28, 109, 36 },
        { TRUE, MAKE_MESSID(47, 64), 28, 109, 37 },
        { TRUE, MAKE_MESSID(47, 65), 28, 109, 38 },
        { TRUE, MAKE_MESSID(47, 67), 28, 109, 40 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
};

static BOOL musicPageOn[14] = { TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE };

static omObjFunc execModeTbl[] = { NULL, ExecZoom, ExecOptionSel, ExecOutputMode, ExecMusic, ExecVoice };

static s32 choiceMess[] = { MAKE_MESSID(47, 8), MAKE_MESSID(47, 10), MAKE_MESSID(47, 9) };

omObjData *OptionSoundCreate(void)
{
    omObjData *object;
    SoundWork *work;
    s32 i;

    object = omAddObjEx(optionObjMan, 1003, 0, 0, 1, NULL);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(SoundWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    work->selectedOption = 0;
    work->doneF = FALSE;
    work->optionSelected = FALSE;
    work->bgMusicStat = -2;
    work->seqStat = -1;
    work->streamStat = -1;
    work->fxStat = -1;
    work->noteSpawner = NULL;
    switch (GWGameStat.sound_mode) {
        case 0:
            work->soundMode = SOUND_MODE_MONO;
            break;
        case 2:
        default:
            work->soundMode = SOUND_MODE_STEREO;
            break;
    }

    work->object[0] = CreateSystem();
    for (i = 0; i < 6; i++) {
        work->object[i + 1] = CreateLightObj(i % 3, (i / 3) > 0);
    }
    LightSetNone(object);
    work->object[7] = CreateHand();
    work->object[8] = CreateOutputModeHand();
    for (i = 0; i < NUM_NOTES; i++) {
        work->object[i + 10] = CreateNoteObj((i / 8) == 0 ? NOTE_TYPE_QUAVER : NOTE_TYPE_QUARTER);
    }
    CreateSpr(object);
    OptionSoundExecModeSet(object, MODE_DISABLED);
    for (i = 0; i < NUM_BOARDS; i++) {
        musicPageOn[i + 3] = (GWGameStat.board_play_count[i] != 0) ? TRUE : FALSE;
    }
    musicPageOn[11] = (GWGameStat.musicAllF != 0) ? TRUE : FALSE;
    musicPageOn[12] = (GWGameStat.musicAllF != 0) ? TRUE : FALSE;
    musicPageOn[13] = (GWGameStat.musicAllF != 0) ? TRUE : FALSE;
    return object;
}

void OptionSoundKill(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    KillHand(work->object[7]);
    KillOutputModeHand(work->object[8]);
    KillSystem(work->object[0]);
    for (i = 0; i < 6; i++) {
        KillLightObj(work->object[i + 1]);
    }
    for (i = 0; i < 16; i++) {
        KillNote(work->object[i + 10]);
    }
    KillSpr(object);
    HuMemDirectFree(work);
}

void OptionSoundExecModeSet(omObjData *object, s32 execMode)
{
    SoundWork *work = object->data;

    work->execMode = execMode;
    object->func = execModeTbl[execMode];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 OptionSoundExecModeGet(omObjData *object)
{
    SoundWork *work = object->data;

    return work->execMode;
}

static void ExecZoom(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    switch (object->unk10) {
        case 0:
            if (!work->doneF) {
                work->window[0] = OptionWinCreate(0);
                work->window[1] = OptionWinCreate(1);
                work->window[2] = OptionWinCreate(2);
                for (i = 0; i < 10; i++) {
                    work->window[i + 3] = OptionWinCreate(3);
                }
                OptionCameraFocusSet(optionCamera, 0.0f, 120.0f, -600.0f, 0x28);
                OptionCameraTargetSet(optionCamera, 0.0f, 120.0f, -350.0f, 0x28);
                work->doneF = TRUE;
                work->selectedOption = 0;
                work->optionSelected = FALSE;
                object->unk10 = 1;
            }
            else {
                object->unk10 = 2;
            }
            break;
        case 1:
            if (OptionCameraDoneCheck(optionCamera) == 0) {
                OptionSoundExecModeSet(object, MODE_HANDLE_OPTION_SEL);
            }
            break;
        case 2:
            for (i = 0; i < 13; i++) {
                OptionWinKill(work->window[i]);
            }
            OptionCameraFocusSet(optionCamera, 0.0f, 120.0f, -600.0f, 0x28);
            OptionCameraTargetSet(optionCamera, 0.0f, 120.0f, 0.0f, 0x28);
            work->doneF = FALSE;
            work->optionSelected = FALSE;
            OptionSoundExecModeSet(object, MODE_DISABLED);
            break;
    }
}

static void ExecOptionSel(omObjData *object)
{
    SoundWork *work = object->data;

    switch (object->unk10) {
        case 0:
            LightSetNone(object);
            work->cursorPos = work->selectedOption;
            if (!work->optionSelected) {
                OptionRumbleMotionShowStart(optionRumble);
            }
            else {
                OutputModeHide(object);
                MusicPageHide(object);
                VoicePageHide(object);
            }
            work->optionSelected = FALSE;
            work->cameraDoneF = FALSE;
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            OptionSelDisp(object);
            OptionWinAnimIn(work->window[1]);
            OptionWinMesSet(work->window[1], MAKE_MESSID(47, 168));
            OptionWinAnimIn(work->window[0]);
            OptionWinMesSet(work->window[0], choiceMess[work->cursorPos]);
            if (!work->cameraDoneF) {
                Hu3DModelAttrReset(work->object[7]->model[0], HU3D_ATTR_DISPOFF);
                work->cameraDoneF = TRUE;
            }
            omSetTra(work->object[7], -34.0f + 40.0f * work->cursorPos, 120.0f, -500.0f);
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (OptionPadCheck(PAD_BUTTON_A)) {
                    work->selectedOption = work->cursorPos;
                    work->optionSelected = TRUE;
                    LightSetCurr(object, work->selectedOption);
                    HuAudFXPlay(2);
                    object->unk10 = 3;
                }
                else if (OptionPadCheck(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    object->unk10 = 3;
                }
                else if (OptionPadDStkRepCheck(1) && work->cursorPos > 0) {
                    work->cursorPos--;
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
                else if (OptionPadDStkRepCheck(2) && work->cursorPos < 2) {
                    work->cursorPos++;
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
            }
            break;
        case 3:
            OptionWinAnimOut(work->window[1]);
            OptionWinAnimOut(work->window[0]);
            if (!work->optionSelected) {
                OptionRumbleMotionHideStart(optionRumble);
            }
            Hu3DModelAttrSet(work->object[7]->model[0], HU3D_ATTR_DISPOFF);
            object->unk10 = 4;
            /* fallthrough */
        case 4:
            if ((work->optionSelected || !OptionRumbleMotionCheck(optionRumble)) && work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (work->optionSelected) {
                    switch (work->selectedOption) {
                        case 0:
                            OptionSoundExecModeSet(object, MODE_HANDLE_SOUND);
                            break;
                        case 1:
                            OptionSoundExecModeSet(object, MODE_HANDLE_MUSIC);
                            break;
                        case 2:
                            OptionSoundExecModeSet(object, MODE_HANDLE_VOICE);
                            break;
                    }
                }
                else {
                    OptionSelHide(object);
                    OptionSoundExecModeSet(object, MODE_HANDLE_INITIAL_SCREEN);
                }
            }
            break;
    }
}

static const s32 outputModeTbl[] = { 2, 0 };
static const s32 soundModeTbl[] = { 1, 0 };

static const s32 soundModeNameTbl[] = { MAKE_MESSID(47, 11), MAKE_MESSID(47, 12) };

static void ExecOutputMode(omObjData *object)
{
    SoundWork *work = object->data;
    Vec pos;

    switch (object->unk10) {
        case 0:
            OptionSelHide(object);
            work->optionSelected = FALSE;
            work->cursorPos = work->soundMode;
            work->cameraDoneF = FALSE;
            work->optionSelected = FALSE;
            CreateNoteSpawner(object);
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            OutputModeDisp(object);
            OptionWinAnimIn(work->window[1]);
            OptionWinMesSet(work->window[1], MAKE_MESSID(47, 168));
            OptionWinAnimIn(work->window[0]);
            OptionWinMesSet(work->window[0], soundModeNameTbl[work->soundMode]);
            if (!work->cameraDoneF) {
                Hu3DModelAttrReset(work->object[8]->model[0], HU3D_ATTR_DISPOFF);
                work->cameraDoneF = TRUE;
            }
            pos.x = -38.0f;
            pos.y = 140.0f - 15.0f * work->cursorPos;
            pos.z = -500.0f;
            omSetTra(work->object[8], pos.x, pos.y, pos.z);
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (OptionPadCheck(PAD_BUTTON_A)) {
                    work->soundMode = work->cursorPos;
                    if (work->soundMode == SOUND_MODE_STEREO) {
                        HuAudFXPlay(0x841);
                    }
                    else {
                        HuAudFXPlay(0x842);
                    }
                    GWGameStat.sound_mode = outputModeTbl[work->cursorPos];
                    msmSysSetOutputMode(outputModeTbl[work->cursorPos]);
                    OSSetSoundMode(soundModeTbl[work->cursorPos]);
                    work->optionSelected = TRUE;
                    OutputModeDisp(object);
                    work->changeTimer = 0;
                    object->unk10 = 3;
                }
                else if (OptionPadCheck(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    object->unk10 = 4;
                }
                else if (OptionPadDStkRepCheck(8) != 0 && work->cursorPos > 0) {
                    work->cursorPos--;
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
                else if (OptionPadDStkRepCheck(4) != 0 && work->cursorPos < 1) {
                    work->cursorPos++;
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
            }
            break;
        case 3:
            if (work->changeTimer++ >= 60) {
                object->unk10 = 4;
                return;
            }
            break;
        case 4:
            KillNoteSpawner(object);
            OptionWinAnimOut(work->window[1]);
            OptionWinAnimOut(work->window[0]);
            Hu3DModelAttrSet(work->object[8]->model[0], HU3D_ATTR_DISPOFF);
            object->unk10 = 5;
            /* fallthrough */
        case 5:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                work->optionSelected = FALSE;
                OutputModeDisp(object);
                work->optionSelected = TRUE;
                OptionSoundExecModeSet(object, MODE_HANDLE_OPTION_SEL);
            }
            break;
    }
}

static void ExecMusic(omObjData *object)
{
    SoundWork *work = object->data;
    float oldX;
    float oldY;
    float x;
    float y;
    float newX;
    float newY;
    s32 i;
    s32 cursorPosNew;
    s32 cursorPosOld;

    cursorPosOld = work->cursorPos;
    switch (object->unk10) {
        case 0:
            OptionSelHide(object);
            work->page = 0;
            work->cursorDelta = 0;
            work->pageDelta = 0;
            espBankSet(work->sprite[14], 0);
            espBankSet(work->sprite[15], 2);
            espPosSet(work->sprite[14], 36.0f, 222.0f);
            espPosSet(work->sprite[15], 544.0f, 222.0f);
            OptionFadeSprite(work->sprite[14], 1, 5);
            OptionFadeSprite(work->sprite[15], 1, 5);
            work->cursorDelay = 0;
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            work->cursorPos = 0;
            work->prevCursorPos = 0;
            if (work->pageDelta != 0) {
                do {
                    work->page += work->pageDelta;
                    if (work->page >= 14) {
                        work->page = 0;
                    }
                    else if (work->page < 0) {
                        work->page = 13;
                    }
                } while (!musicPageOn[work->page]);
                HuAudFXPlay(0x840);
                if (work->pageDelta > 0) {
                    espBankSet(work->sprite[15], 3);
                }
                else {
                    espBankSet(work->sprite[14], 1);
                }
                work->cursorDelay = 5;
                work->pageDelta = 0;
            }
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->cursorDelta != 0) {
                cursorPosNew = work->cursorPos + work->cursorDelta;
                if (cursorPosNew > 9) {
                    cursorPosNew = 9;
                }
                else if (cursorPosNew < 0) {
                    cursorPosNew = 0;
                }
                if (!musicTbl[work->page][cursorPosNew].enabled) {
                    if (work->cursorPos < 5) {
                        for (i = cursorPosNew; i >= 5; i--) {
                            if (musicTbl[work->page][i].enabled) {
                                cursorPosNew = i;
                                break;
                            }
                        }
                        if (i < 5) {
                            cursorPosNew = work->cursorPos;
                        }
                    }
                    else {
                        cursorPosNew = work->cursorPos;
                    }
                }
                work->prevCursorPos = work->cursorPos;
                if (work->cursorPos != cursorPosNew) {
                    work->cursorPos = cursorPosNew;
                    HuAudFXPlay(0x840);
                }
                work->cursorDelta = 0;
            }
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            MusicPageDisp(object, work->page);
            OptionWinAnimIn(work->window[0]);
            OptionWinMesSet(work->window[0], MAKE_MESSID(47, 10));
            OptionWinAnimIn(work->window[1]);
            OptionWinMesSet(work->window[1], MAKE_MESSID(47, 18));
            espDispOn(work->sprite[18]);
            work->cursorTime = 0.0f;
            work->cursorSpeed = 0.0625f;
            if (work->cursorDelay > 0) {
                object->unk10 = 5;
            }
            else {
                object->unk10 = 4;
            }
            /* fallthrough */
        case 4:
            oldX = 166.0f + 244.0f * (work->prevCursorPos / 5);
            oldY = 144.0f + 29.0f * (work->prevCursorPos % 5);
            newX = 166.0f + 244.0f * (work->cursorPos / 5);
            newY = 144.0f + 29.0f * (work->cursorPos % 5);
            x = oldX + work->cursorTime * (newX - oldX);
            y = oldY + work->cursorTime * (newY - oldY);
            espPosSet(work->sprite[18], x, y);
            if ((work->cursorTime += work->cursorSpeed) < 1.0f) {
                break;
            }
            espPosSet(work->sprite[18], 166.0f + 244.0f * (work->cursorPos / 5), 144.0f + 29.0f * (work->cursorPos % 5));
            object->unk10 = 6;
            break;
        case 5:
            if (work->cursorDelay > 0) {
                work->cursorDelay--;
                break;
            }
            espBankSet(work->sprite[14], 0);
            espBankSet(work->sprite[15], 2);
            object->unk10 = 6;
            /* fallthrough */
        case 6:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (OptionPadCheck(PAD_BUTTON_A)) {
                    if (work->bgMusicStat == -2) {
                        HuAudFadeOut(0x64);
                        work->bgMusicStat = -1;
                    }
                    else if (work->bgMusicStat != -1) {
                        HuAudSeqFadeOut(work->bgMusicStat, 0x64);
                        work->bgMusicStat = -1;
                    }
                    OptionPlaySound(object);
                }
                else if (OptionPadCheck(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    work->changeTimer = 0;
                    object->unk10 = 7;
                }
                else {
                    if (OptionPadDStkCheck(1) != 0 && work->cursorPos >= 5) {
                        work->cursorDelta -= 5;
                    }
                    else if (OptionPadDStkCheck(2) != 0 && work->cursorPos < 5) {
                        work->cursorDelta += 5;
                    }
                    if (OptionPadDStkCheck(8) != 0 && work->cursorPos % 5 > 0) {
                        work->cursorDelta--;
                    }
                    else if (OptionPadDStkCheck(4) != 0 && work->cursorPos % 5 < 4) {
                        work->cursorDelta++;
                    }
                    if (work->cursorDelta != 0) {
                        object->unk10 = 2;
                    }
                    else if (OptionPadCheck(PAD_TRIGGER_L)) {
                        work->pageDelta = -1;
                    }
                    else if (OptionPadCheck(PAD_TRIGGER_R)) {
                        work->pageDelta = 1;
                    }
                    if (work->pageDelta != 0) {
                        object->unk10 = 1;
                    }
                }
            }
            break;
        case 7:
            OptionWinAnimOut(work->window[1]);
            OptionWinAnimOut(work->window[0]);
            FadeSound(object);
            OptionFadeSprite(work->sprite[14], 0, 5);
            OptionFadeSprite(work->sprite[15], 0, 5);
            object->unk10 = 8;
            /* fallthrough */
        case 8:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                espDispOff(work->sprite[18]);
                if (work->bgMusicStat == -1) {
                    work->bgMusicStat = HuAudSeqPlay(0x2D);
                }
                OptionSoundExecModeSet(object, MODE_HANDLE_OPTION_SEL);
            }
            break;
    }
}

static void ExecVoice(omObjData *object)
{
    SoundWork *work = object->data;
    float oldX;
    float oldY;
    float x;
    float y;
    float newX;
    float newY;
    s32 i;
    s32 cursorPosNew;

    switch (object->unk10) {
        case 0:
            OptionSelHide(object);
            work->page = 0;
            work->cursorDelta = 0;
            work->pageDelta = 0;
            espBankSet(work->sprite[14], 0);
            espBankSet(work->sprite[15], 2);
            espPosSet(work->sprite[14], 36.0f, 222.0f);
            espPosSet(work->sprite[15], 544.0f, 222.0f);
            OptionFadeSprite(work->sprite[14], 1, 5);
            OptionFadeSprite(work->sprite[15], 1, 5);
            work->cursorDelay = 0;
            object->unk10 = 3;
            /* fallthrough */
        case 1:
            work->cursorPos = 0;
            work->prevCursorPos = 0;
            if (work->pageDelta != 0) {
                work->page += work->pageDelta;
                if (work->page > 11) {
                    work->page = 0;
                }
                else if (work->page < 0) {
                    work->page = 11;
                }
                HuAudFXPlay(0x840);
                if (work->pageDelta > 0) {
                    espBankSet(work->sprite[15], 3);
                }
                else {
                    espBankSet(work->sprite[14], 1);
                }
                work->cursorDelay = 5;
                work->pageDelta = 0;
            }
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->cursorDelta != 0) {
                cursorPosNew = work->cursorPos + work->cursorDelta;
                if (cursorPosNew > 9) {
                    cursorPosNew = 9;
                }
                else if (cursorPosNew < 0) {
                    cursorPosNew = 0;
                }
                if (!voiceTbl[work->page][cursorPosNew].enabled) {
                    if (work->cursorPos < 5) {
                        for (i = cursorPosNew; i >= 5; i--) {
                            if (voiceTbl[work->page][i].enabled) {
                                cursorPosNew = i;
                                break;
                            }
                        }
                        if (i < 5) {
                            cursorPosNew = work->cursorPos;
                        }
                    }
                    else {
                        cursorPosNew = work->cursorPos;
                    }
                }
                work->prevCursorPos = work->cursorPos;
                if (work->cursorPos != cursorPosNew) {
                    work->cursorPos = cursorPosNew;
                    HuAudFXPlay(0x840);
                }
                work->cursorDelta = 0;
            }
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            VoicePageDisp(object, work->page);
            OptionWinAnimIn(work->window[0]);
            OptionWinMesSet(work->window[0], MAKE_MESSID(47, 9));
            OptionWinAnimIn(work->window[1]);
            OptionWinMesSet(work->window[1], MAKE_MESSID(47, 18));
            espDispOn(work->sprite[18]);
            work->cursorTime = 0.0f;
            work->cursorSpeed = 0.0625f;
            if (work->cursorDelay > 0) {
                object->unk10 = 5;
            }
            else {
                object->unk10 = 4;
            }
            /* fallthrough */
        case 4:
            oldX = 166.0f + 244.0f * (work->prevCursorPos / 5);
            oldY = 144.0f + 29.0f * (work->prevCursorPos % 5);
            newX = 166.0f + 244.0f * (work->cursorPos / 5);
            newY = 144.0f + 29.0f * (work->cursorPos % 5);
            x = oldX + work->cursorTime * (newX - oldX);
            y = oldY + work->cursorTime * (newY - oldY);
            espPosSet(work->sprite[18], x, y);
            if ((work->cursorTime += work->cursorSpeed) < 1.0f) {
                break;
            }
            espPosSet(work->sprite[18], 166.0f + 244.0f * (work->cursorPos / 5), 144.0f + 29.0f * (work->cursorPos % 5));
            object->unk10 = 6;
            break;
        case 5:
            if (work->cursorDelay > 0) {
                work->cursorDelay--;
                break;
            }
            espBankSet(work->sprite[14], 0);
            espBankSet(work->sprite[15], 2);
            object->unk10 = 6;
            /* fallthrough */
        case 6:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (OptionPadCheck(PAD_BUTTON_A)) {
                    OptionPlaySound(object);
                }
                else if (OptionPadCheck(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    work->changeTimer = 0;
                    object->unk10 = 7;
                }
                else {
                    if (OptionPadDStkCheck(1) != 0 && work->cursorPos >= 5) {
                        work->cursorDelta -= 5;
                    }
                    else if (OptionPadDStkCheck(2) != 0 && work->cursorPos < 5) {
                        work->cursorDelta += 5;
                    }
                    if (OptionPadDStkCheck(8) != 0 && work->cursorPos % 5 > 0) {
                        work->cursorDelta--;
                    }
                    else if (OptionPadDStkCheck(4) != 0 && work->cursorPos % 5 < 4) {
                        work->cursorDelta++;
                    }
                    if (work->cursorDelta != 0) {
                        object->unk10 = 2;
                    }
                    else if (OptionPadCheck(PAD_TRIGGER_L)) {
                        work->pageDelta = -1;
                    }
                    else if (OptionPadCheck(PAD_TRIGGER_R)) {
                        work->pageDelta = 1;
                    }
                    if (work->pageDelta != 0) {
                        object->unk10 = 1;
                    }
                }
            }
            break;
        case 7:
            OptionWinAnimOut(work->window[1]);
            OptionWinAnimOut(work->window[0]);
            FadeSound(object);
            OptionFadeSprite(work->sprite[14], 0, 5);
            OptionFadeSprite(work->sprite[15], 0, 5);
            object->unk10 = 8;
            /* fallthrough */
        case 8:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                espDispOff(work->sprite[18]);
                OptionSoundExecModeSet(object, MODE_HANDLE_OPTION_SEL);
            }
            break;
    }
}

static void LightSetCurr(omObjData *object, s32 id)
{
    SoundWork *work = object->data;

    switch (id) {
        case 0:
            LightDispOff(work->object[1]);
            LightDispOff(work->object[5]);
            LightDispOff(work->object[6]);
            LightDispOn(work->object[4]);
            LightDispOn(work->object[2]);
            LightDispOn(work->object[3]);
            break;
        case 1:
            LightDispOff(work->object[4]);
            LightDispOff(work->object[2]);
            LightDispOff(work->object[6]);
            LightDispOn(work->object[1]);
            LightDispOn(work->object[5]);
            LightDispOn(work->object[3]);
            break;
        case 2:
            LightDispOff(work->object[4]);
            LightDispOff(work->object[5]);
            LightDispOff(work->object[3]);
            LightDispOn(work->object[1]);
            LightDispOn(work->object[2]);
            LightDispOn(work->object[6]);
            break;
    }
}

static void LightSetNone(omObjData *object)
{
    SoundWork *work = object->data;

    LightDispOff(work->object[4]);
    LightDispOff(work->object[5]);
    LightDispOff(work->object[6]);
    LightDispOn(work->object[1]);
    LightDispOn(work->object[2]);
    LightDispOn(work->object[3]);
}

static omObjData *CreateHand(void)
{
    omObjData *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 13));
    Hu3DModelLayerSet(object->model[0], 2);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    omSetRot(object, -80.0f, 45.0f, 0.0f);
    omSetSca(object, 0.6f, 0.6f, 0.6f);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    return object;
}

static void KillHand(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}

static omObjData *CreateOutputModeHand(void)
{
    omObjData *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 14));
    Hu3DModelLayerSet(object->model[0], 2);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    omSetRot(object, 0.0f, -90.0f, 0.0f);
    omSetSca(object, 0.6f, 0.6f, 0.6f);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    return object;
}

static void KillOutputModeHand(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}

static omObjData *CreateSystem(void)
{
    omObjData *system;

    system = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    system->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 3));
    Hu3DModelAttrSet(system->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(system->model[0], 0);
    return system;
}

static void KillSystem(omObjData *system)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(system->model[i]);
    }
}

static const Vec lightPosTbl[3] = { { -40.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 40.0f, 0.0f, 0.0f } };

static omObjData *CreateLightObj(s32 id, BOOL off)
{
    omObjData *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    if (off) {
        object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 5));
    }
    else {
        object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 4));
    }
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->model[0], 0);
    omSetTra(object, lightPosTbl[id].x, lightPosTbl[id].y, lightPosTbl[id].z);
    return object;
}

static void KillLightObj(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}

static void LightDispOff(omObjData *indicator)
{
    Hu3DModelAttrReset(indicator->model[0], HU3D_ATTR_DISPOFF);
}

static void LightDispOn(omObjData *indicator)
{
    Hu3DModelAttrSet(indicator->model[0], HU3D_ATTR_DISPOFF);
}

static s32 spriteDataTbl[] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 38),
    DATA_MAKE_NUM(DATADIR_OPTION, 39),
    DATA_MAKE_NUM(DATADIR_OPTION, 40),
    DATA_MAKE_NUM(DATADIR_OPTION, 35),
    DATA_MAKE_NUM(DATADIR_OPTION, 36),
    DATA_MAKE_NUM(DATADIR_OPTION, 37),
    DATA_MAKE_NUM(DATADIR_OPTION, 41),
    DATA_MAKE_NUM(DATADIR_OPTION, 43),
    DATA_MAKE_NUM(DATADIR_OPTION, 42),
    DATA_MAKE_NUM(DATADIR_OPTION, 44),
    DATA_MAKE_NUM(DATADIR_OPTION, 45),
    DATA_MAKE_NUM(DATADIR_OPTION, 46),
    DATA_MAKE_NUM(DATADIR_OPTION, 47),
    DATA_MAKE_NUM(DATADIR_OPTION, 48),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 63),
    DATA_MAKE_NUM(DATADIR_OPTION, 64),
    DATA_MAKE_NUM(DATADIR_OPTION, 65),
};

static void CreateSpr(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 19; i++) {
        work->sprite[i] = espEntry(spriteDataTbl[i], 0, 0);
        espDrawNoSet(work->sprite[i], 0x40);
        espDispOff(work->sprite[i]);
    }
    espBankSet(work->sprite[14], 0);
    espBankSet(work->sprite[15], 2);
    HuSprExecLayerSet(0x40, 1);
}

static void KillSpr(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 19; i++) {
        espKill(work->sprite[i]);
    }
}

static void OptionSelDisp(omObjData *object)
{
    SoundWork *work = object->data;
    float x = 288.0f;
    float y = 188.0f;

    espPosSet(work->sprite[12], 288.0f, 72.0f);
    espPosSet(work->sprite[0], x + -112.0f, y);
    espPosSet(work->sprite[3], x + -112.0f, y);
    espPosSet(work->sprite[1], x, y);
    espPosSet(work->sprite[4], x, y);
    espPosSet(work->sprite[2], x + 112.0f, y);
    espPosSet(work->sprite[5], x + 112.0f, y);
    espDispOn(work->sprite[12]);
    switch (work->cursorPos) {
        case 0:
            espDispOn(work->sprite[3]);
            espDispOn(work->sprite[1]);
            espDispOn(work->sprite[2]);
            espDispOff(work->sprite[0]);
            espDispOff(work->sprite[4]);
            espDispOff(work->sprite[5]);
            break;
        case 1:
            espDispOn(work->sprite[0]);
            espDispOn(work->sprite[4]);
            espDispOn(work->sprite[2]);
            espDispOff(work->sprite[3]);
            espDispOff(work->sprite[1]);
            espDispOff(work->sprite[5]);
            break;
        case 2:
            espDispOn(work->sprite[0]);
            espDispOn(work->sprite[1]);
            espDispOn(work->sprite[5]);
            espDispOff(work->sprite[3]);
            espDispOff(work->sprite[4]);
            espDispOff(work->sprite[2]);
            break;
    }
}

static void OptionSelHide(omObjData *object)
{
    static const s32 sprHideTbl[] = { 12, 0, 1, 2, 3, 4, 5 };
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 7; i++) {
        espDispOff(work->sprite[sprHideTbl[i]]);
    }
}

static void OutputModeDisp(omObjData *object)
{
    SoundWork *work = object->data;
    float x = 290.0f;
    float y = 192.0f;

    espPosSet(work->sprite[13], 288.0f, 72.0f);
    espPosSet(work->sprite[6], x, y - 32.0f);
    espPosSet(work->sprite[7], x, y - 32.0f);
    espPosSet(work->sprite[8], x, y + 32.0f);
    espPosSet(work->sprite[9], x, y + 32.0f);
    switch (work->cursorPos) {
        case 0:
            espPosSet(work->sprite[17], x, y - 32.0f);
            break;
        case 1:
            espPosSet(work->sprite[17], x, y + 32.0f);
            break;
    }
    espDispOn(work->sprite[13]);
    switch (work->cursorPos) {
        case 0:
            espDispOn(work->sprite[6]);
            espDispOn(work->sprite[9]);
            espDispOff(work->sprite[7]);
            espDispOff(work->sprite[8]);
            break;
        case 1:
            espDispOn(work->sprite[7]);
            espDispOn(work->sprite[8]);
            espDispOff(work->sprite[6]);
            espDispOff(work->sprite[9]);
            break;
    }
    if (work->optionSelected) {
        espDispOn(work->sprite[17]);
    }
    else {
        espDispOff(work->sprite[17]);
    }
}

static void OutputModeHide(omObjData *object)
{
    static const s32 sprHideTbl[] = { 13, 6, 7, 8, 9 };
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        espDispOff(work->sprite[sprHideTbl[i]]);
    }
}

static void MusicPageDisp(omObjData *object, s32 page)
{
    SoundWork *work = object->data;
    s32 i;

    espPosSet(work->sprite[10], 288.0f, 72.0f);
    espDispOn(work->sprite[10]);
    OptionWinDispOn(work->window[2]);
    for (i = 0; i < 10; i++) {
        OptionWinDispOn(work->window[i + 3]);
        OptionWinPosSet(work->window[i + 3], 52.0f + 244.0f * (i / 5), 124.0f + 29.0f * (i % 5));
    }
    OptionWinMesSet(work->window[2], musicPageNameTbl[page]);
    for (i = 0; i < 10; i++) {
        OptionWinMesSet(work->window[i + 3], musicTbl[page][i].nameMess);
    }
}

static void MusicPageHide(omObjData *object)
{
    static const s32 sprHideTbl[] = { 10 };
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        espDispOff(work->sprite[sprHideTbl[i]]);
    }
    OptionWinDispOff(work->window[2]);
    for (i = 0; i < 10; i++) {
        OptionWinDispOff(work->window[i + 3]);
    }
}

static void VoicePageDisp(omObjData *object, s32 character)
{
    SoundWork *work = object->data;
    s32 i;

    espPosSet(work->sprite[11], 288.0f, 72.0f);
    espDispOn(work->sprite[11]);
    OptionWinDispOn(work->window[2]);
    for (i = 0; i < 10; i++) {
        OptionWinDispOn(work->window[i + 3]);
        OptionWinPosSet(work->window[i + 3], 52.0f + 244.0f * (i / 5), 124.0f + 29.0f * (i % 5));
    }
    OptionWinMesSet(work->window[2], voiceCharNameTbl[character]);
    for (i = 0; i < 10; i++) {
        OptionWinMesSet(work->window[i + 3], voiceTbl[character][i].nameMess);
    }
}

static void VoicePageHide(omObjData *object)
{
    static const s32 sprHideTbl[] = { 11, 0 };
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        espDispOff(work->sprite[sprHideTbl[i]]);
    }
    OptionWinDispOff(work->window[2]);
    for (i = 0; i < 10; i++) {
        OptionWinDispOff(work->window[i + 3]);
    }
}

static s32 noteMdlTbl[] = { DATA_MAKE_NUM(DATADIR_OPTION, 7), DATA_MAKE_NUM(DATADIR_OPTION, 8) };

static omObjData *CreateNoteObj(s32 type)
{
    omObjData *note;
    NoteWork *noteWork;

    note = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    noteWork = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(NoteWork), MEMORY_DEFAULT_NUM);
    note->data = noteWork;
    noteWork->enabled = FALSE;
    noteWork->type = type;
    note->model[0] = Hu3DModelCreateFile(noteMdlTbl[type]);
    Hu3DModelAttrSet(note->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(note->model[0], 2);
    Hu3DModelAttrReset(note->model[0], HU3D_ATTR_ZWRITE_OFF);
    return note;
}

static void KillNote(omObjData *note)
{
    NoteWork *noteWork = note->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(note->model[i]);
    }
    HuMemDirectFree(noteWork);
}

static void HandleNote(omObjData *note)
{
    NoteWork *noteWork = note->data;
    float time;
    float scale;
    float angle;
    float zRot;
    float radius;
    float x;
    float z;
    float y;
    float tplvl;

    Hu3DModelAttrReset(note->model[0], HU3D_ATTR_DISPOFF);
    time = sind(45.0f * noteWork->pos);
    time = time * time;
    switch (noteWork->side) {
        case NOTE_SIDE_LEFT:
            angle = 174.5f + 7.0f * time;
            zRot = -15.0 + 30.0 * sind(1440.0f * time);
            break;
        case NOTE_SIDE_RIGHT:
            angle = 185.5f - (7.0f * time);
            zRot = 15.0 - 30.0 * sind(1440.0f * time);
            break;
    }
    tplvl = sind(180.0f * noteWork->pos);
    radius = 500.0f - 25.0f * time;
    x = radius * -sind(angle);
    z = radius * cosd(angle);
    y = 160.0f - 15.0f * noteWork->pos;
    scale = 0.5 + 2.0 * sind(90.0f * time);
    omSetTra(note, x, y, z);
    Hu3DModelTPLvlSet(note->model[0], tplvl);
    omSetSca(note, scale, scale, scale);
    omSetRot(note, 0.0f, 0.0f, zRot);
    if ((noteWork->pos += noteWork->speed) < 1.0f) {
        return;
    }
    noteWork->enabled = FALSE;
    Hu3DModelAttrSet(note->model[0], HU3D_ATTR_DISPOFF);
    note->func = NULL;
    note->unk10 = 0;
}

static void CreateNote(omObjData *object, s32 type, s32 side, s32 color)
{
    omObjData *noteObj;
    NoteWork *note;
    s32 i;

    for (i = 0; i < NUM_NOTES; i++) {
        noteObj = ((SoundWork *)object->data)->object[i + 10];
        note = noteObj->data;
        if (!note->enabled && note->type == type) {
            break;
        }
    }
    if (i != NUM_NOTES) {
        Hu3DMotionTimeSet(noteObj->model[0], 2.0f * color);
        Hu3DMotionStartEndSet(noteObj->model[0], 2.0f * color, 2.0f * color + 1.0f);
        note->enabled = TRUE;
        note->side = side;
        note->pos = 0.0f;
        note->speed = 0.011111111f;
        noteObj->func = HandleNote;
        noteObj->unk10 = 0;
    }
}

static void CreateNoteSpawner(omObjData *object)
{
    SoundWork *work = object->data;

    work->noteSpawner = HuPrcChildCreate(ExecNoteSpawner, 0x64, 0x2000, 0, HuPrcCurrentGet());
    work->noteSpawner->user_data = object;
}

static void KillNoteSpawner(omObjData *object)
{
    SoundWork *work = object->data;

    HuPrcKill(work->noteSpawner);
}

static void ExecNoteSpawner(void)
{
    omObjData *object;
    SoundWork *work;
    s32 type;
    s32 color;

    object = HuPrcCurrentGet()->user_data;
    work = object->data;
    while (TRUE) {
        switch (work->cursorPos) {
            case 0:
                type = NOTE_TYPE_QUARTER;
                color = frandmod(7);
                CreateNote(object, type, NOTE_SIDE_LEFT, color);
                type = NOTE_TYPE_QUAVER;
                color = frandmod(7);
                CreateNote(object, type, NOTE_SIDE_RIGHT, color);
                break;
            case 1:
                type = NOTE_TYPE_QUAVER;
                color = frandmod(7);
                CreateNote(object, type, NOTE_SIDE_LEFT, color);
                CreateNote(object, type, NOTE_SIDE_RIGHT, color);
                break;
        }
        HuPrcSleep(24);
    }
}

static void OptionPlaySound(omObjData *object)
{
    SoundWork *work = object->data;
    SndSelData *sndSelData;

    if (work->selectedOption == 1) {
        sndSelData = (SndSelData *)&musicTbl[work->page][work->cursorPos];
    }
    else {
        sndSelData = (SndSelData *)&voiceTbl[work->page][work->cursorPos];
    }
    if (sndSelData->enabled) {
        FadeSound(object);
        switch (sndSelData->type) {
            case 1:
                work->streamStat = HuAudSStreamPlay(sndSelData->id);
                break;
            case 28:
                if (sndSelData->sndGrpSet != work->sndGrpSet) {
                    HuAudSndGrpSetSet(sndSelData->sndGrpSet);
                }
                work->fxStat = HuAudFXPlay(sndSelData->id);
                break;
            default:
                if (sndSelData->sndGrpSet != work->sndGrpSet && sndSelData->sndGrpSet != 2) {
                    HuAudSndGrpSetSet(sndSelData->sndGrpSet);
                }
                work->seqStat = HuAudSeqPlay(sndSelData->id);
                break;
        }
        work->sndGrpSet = sndSelData->sndGrpSet;
        HuPrcSleep(40);
    }
}

static void FadeSound(omObjData *object)
{
    SoundWork *work = object->data;

    if (work->seqStat != -1) {
        HuAudSeqFadeOut(work->seqStat, 0x64);
        work->seqStat = -1;
    }
    if (work->streamStat != -1) {
        HuAudSStreamFadeOut(work->streamStat, 0x64);
        work->streamStat = -1;
    }
    if (work->fxStat != -1) {
        HuAudFXFadeOut(work->fxStat, 0x64);
        work->fxStat = -1;
    }
    HuPrcSleep(20);
}

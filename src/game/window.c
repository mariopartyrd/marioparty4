#include "game/gamework_data.h"

#include "game/armem.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/disp.h"
#include "game/dvd.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"

#include "ext_math.h"
#include "stdarg.h"
#include "string.h"

#include "data_num/win.h"

typedef struct {
    /* 0x00 */ AnimData **anim;
    /* 0x04 */ s16 bank;
    /* 0x06 */ s16 w;
    /* 0x08 */ s16 h;
    /* 0x0A */ s16 center_x;
    /* 0x0C */ s16 center_y;
} spcFontTblData;

typedef struct {
    /* 0x00 */ s16 time;
    /* 0x04 */ u32 player[4];
} keyBufData; // Size 0x14

static void MesDispFunc(HuSprite *sprite);
static u8 winBGMake(AnimData *bg, AnimData *frame);
static void HuWinProc(void);
static void HuWinDrawMes(s16 window);
static s32 HuWinCR(WindowData *window);
static void _HuWinHomeClear(WindowData *window);
static void HuWinKeyWait(s16 window);
static s16 HuWinSpcFontEntry(WindowData *window, s16 entry, s16 x, s16 y);
static void HuWinSpcFontClear(WindowData *window);
static void HuWinChoice(WindowData *window);
static void GetMesMaxSizeSub(u32 mess);
static s32 GetMesMaxSizeSub2(WindowData *window, u8 *mess_data);

void mtxTransCat(Mtx, float, float, float);
SHARED_SYM WindowData ATTRIBUTE_ALIGN(32) winData[32];
static u32 winKey[4];
keyBufData winComKeyBuf[256];

static AnimData *iconAnim;
static AnimData *cursorAnim;
static AnimData *cardAnimA;
static AnimData *cardAnimB;
static Process *winProc;
SHARED_SYM void *messDataPtr;
static s32 messDataNo;
static s16 winMaxWidth;
static s16 winMaxHeight;
#if VERSION_NTSC
static u8 mesWInsert[8];
#else
static u16 mesWInsert[8];
#endif

static u8 winTabSize;
static u8 winInsertF;
static u32 winAMemP;
static u8 *fontWidthP;
static s32 cancelCRF;
static s16 mesCharCnt;
static s16 comKeyIdxNow;
static s16 comKeyIdx;
static u8 LanguageNo;
AnimData *fontAnim;

static spcFontTblData spcFontTbl[] = { { &iconAnim, 0, 20, 24, 10, 12 }, { &iconAnim, 1, 20, 24, 10, 12 }, { &iconAnim, 2, 20, 24, 10, 12 },
    { &iconAnim, 3, 20, 24, 10, 12 }, { &iconAnim, 4, 20, 24, 10, 12 }, { &iconAnim, 5, 20, 24, 10, 12 }, { &iconAnim, 6, 20, 24, 10, 12 },
    { &iconAnim, 7, 20, 24, 10, 12 }, { &iconAnim, 8, 20, 24, 10, 12 }, { &iconAnim, 9, 20, 24, 10, 12 }, { &iconAnim, 10, 20, 24, 10, 12 },
    { &iconAnim, 11, 30, 24, 15, 12 }, { &iconAnim, 12, 20, 24, 10, 12 }, { &iconAnim, 13, 20, 24, 10, 12 }, { &iconAnim, 14, 20, 24, 10, 12 },
    { &iconAnim, 15, 20, 24, 10, 12 }, { &iconAnim, 16, 20, 24, 10, 12 }, { &iconAnim, 17, 20, 24, 10, 12 }, { &iconAnim, 18, 20, 24, 10, 12 },
    { &iconAnim, 19, 24, 24, 12, 12 }, { &cursorAnim, 0, 40, 32, -15, 18 }, { &cardAnimA, 0, 32, 32, 16, 16 }, { &cardAnimB, 0, 32, 32, 16, 16 } };

#if VERSION_ENG
u8 charWETbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 18, 20, 12, 12, 11, 14, 8, 13, 12, 12, 12, 12, 12, 12, 12, 9, 11, 12, 11, 15, 12, 13, 12,
    13, 12, 12, 11, 12, 11, 15, 12, 13, 11, 12, 6, 8, 8, 12, 20, 12, 11, 12, 11, 11, 9, 12, 11, 4, 8, 11, 4, 14, 11, 12, 11, 12, 9, 11, 9, 11, 11, 15,
    11, 11, 11, 4, 13, 8, 14, 12, 9, 8, 8, 8, 20, 4, 12, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 12, 12, 12, 12, 12, 12, 12, 12, 8, 8, 12, 12, 12, 12,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 12, 12, 7, 14,
    17, 13, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 16, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 };
#elif VERSION_JP
u8 charWETbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 13, 8, 11, 12, 13, 12, 11, 11, 12, 11, 18, 20, 12, 12, 11, 14, 8, 13, 12, 12, 12, 12, 12, 12, 12, 9, 11, 12, 11, 15, 12, 13, 12,
    13, 12, 12, 11, 12, 11, 15, 12, 13, 11, 12, 6, 8, 8, 12, 20, 12, 11, 12, 11, 11, 9, 12, 11, 4, 8, 11, 4, 14, 11, 12, 11, 12, 9, 11, 9, 11, 11, 15,
    11, 11, 11, 4, 13, 8, 14, 12, 9, 8, 8, 8, 20, 4, 12, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 12, 12, 12, 12, 12, 12, 12, 12, 8, 8, 12, 12, 12, 12,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 12, 12, 7, 14,
    17, 13, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 16, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 };

#else
u8 charWETbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 18, 20, 12, 12, 11, 14, 8, 13, 12, 12, 12, 12, 12, 12, 12, 9, 11, 12, 11, 15, 12, 13, 12,
    13, 12, 12, 11, 12, 11, 15, 12, 13, 11, 12, 6, 8, 8, 12, 20, 12, 11, 12, 11, 11, 9, 12, 11, 4, 8, 11, 4, 14, 11, 12, 11, 12, 9, 11, 9, 11, 11, 15,
    11, 11, 11, 4, 13, 8, 14, 12, 9, 8, 8, 8, 20, 4, 12, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 12, 12, 12, 12, 12, 12, 12, 12, 8, 8, 12, 12, 12, 12,
    12, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 13, 13, 6, 12,
    18, 14, 14, 8, 20, 20, 20, 20, 20, 20, 20, 20, 20, 10, 10, 10, 12, 12, 12, 12, 12, 10, 10, 12, 12, 10, 10, 10, 10, 7, 7, 12, 12, 10, 12, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 16, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 };

#endif

u8 charWJTbl[] = { 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 };

static u8 ATTRIBUTE_ALIGN(32) charColPal[2 * 3 * 10] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0xFF, 0xFF, 0xA0, 0x00, 0xFF, 0xFF, 0xFF, 0x60, 0x60, 0x60, 0x90, 0x90, 0x90, 0x00, 0x00, 0x00, 0x60, 0xB0, 0xFF, 0xFF, 0x40, 0x80,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x60, 0x60, 0x60, 0x90, 0x90, 0x90 };

static s32 frameFileTbl[] = { WIN_FRAME1_ANM, WIN_FRAME2_ANM, WIN_FRAME3_ANM, WIN_FRAME1_ANM };

#if VERSION_NTSC
static char *mesDataTbl[] = { "mess/mini.dat", "mess/board.dat", "mess/mini_e.dat", "mess/board_e.dat" };
#else
static char *mesDataTbl[] = { "mess/mini.dat", "mess/board.dat", "mess/mini_e.dat", "mess/board_e.dat", "mess/mini_g.dat", "mess/board_g.dat",
    "mess/mini_f.dat", "mess/board_f.dat", "mess/mini_i.dat", "mess/board_i.dat", "mess/mini_s.dat", "mess/board_s.dat" };
#endif

static s32 winVoiceTbl[]
    = { 0x37, 0x36, 0x38, 0x44, 0x43, 0x45, 0x41, 0x40, 0x42, 0x4C, 0x4B, 0x4D, 0x47, 0x46, 0x48, 0x3E, 0x3E, 0x3F, 0x49, 0x49, 0x49 };

static s16 winPrio = 1000;

void HuWindowInit(void)
{
    s16 i;

    winAMemP = HuAR_DVDtoARAM(DATADIR_WIN);
    for (i = 0; i < 32; i++) {
        winData[i].group = -1;
    }
    winProc = 0;
    winPrio = 1000;
}

void HuWinInit(s32 mess_data_no)
{
    s16 i;
    void *anim_data;

    if (!winProc) {
        HuAR_ARAMtoMRAM(winAMemP);
        winProc = HuPrcCreate(HuWinProc, 0x64, 0x1000, 0);
        HuPrcSetStat(winProc, 0xC);
        LanguageNo = GWLanguageGet();
        messDataNo = mess_data_no;
        fontWidthP = (LanguageNo == 0) ? charWJTbl : charWETbl;
        HuWinMesRead(mess_data_no);
        for (i = 0; i < 32; i++) {
            winData[i].group = -1;
        }
        if (!fontAnim) {
            if (LanguageNo == 0) {
                anim_data = HuDataReadNum(WIN_FONTJ_ANM, MEMORY_DEFAULT_NUM);
            }
            else {
                anim_data = HuDataReadNum(WIN_FONTE_ANM, MEMORY_DEFAULT_NUM);
            }
            fontAnim = HuSprAnimRead(anim_data);
        }
        if (!iconAnim) {
            anim_data = HuDataReadNum(WIN_ICON_ANM, MEMORY_DEFAULT_NUM);
            iconAnim = HuSprAnimRead(anim_data);
            HuSprAnimLock(iconAnim);
        }
        if (!cursorAnim) {
            anim_data = HuDataReadNum(WIN_CURSOR_ANM, MEMORY_DEFAULT_NUM);
            cursorAnim = HuSprAnimRead(anim_data);
            HuSprAnimLock(cursorAnim);
        }
        if (!cardAnimA) {
            anim_data = HuDataReadNum(WIN_CARDA_ANM, MEMORY_DEFAULT_NUM);
            cardAnimA = HuSprAnimRead(anim_data);
            HuSprAnimLock(cardAnimA);
        }
        if (!cardAnimB) {
            anim_data = HuDataReadNum(WIN_CARDB_ANM, MEMORY_DEFAULT_NUM);
            cardAnimB = HuSprAnimRead(anim_data);
            HuSprAnimLock(cardAnimB);
        }
        HuDataDirClose(DATADIR_WIN);
        HuWinComKeyReset();
        winPrio = 1000;
    }
}

s16 HuWinCreate(float x, float y, s16 w, s16 h, s16 frame)
{
    AnimData *bg_anim;
    WindowData *window;
    HuSprite *sprite_ptr;
    s16 group;
    s16 sprite;
    s16 window_id;
    s16 i;
    void *frame_data;

    for (window_id = 0; window_id < 32; window_id++) {
        if (winData[window_id].group == -1) {
            break;
        }
    }
    if (window_id == 32) {
        return -1;
    }
    window = &winData[window_id];
    window->group = group = HuSprGrpCreate(30);
    if (frame < 0 || frame >= 4) {
        frame = 0;
    }
    w = (w + 15) & 0xFFF0;
    h = (h + 15) & 0xFFF0;
    if (x == -10000.0f) {
        window->pos_x = (HU_DISP_WIDTHF - w) / 2;
    }
    else {
        window->pos_x = x;
    }
    if (y == -10000.0f) {
        window->pos_y = (HU_DISP_HEIGHTF - h) / 2;
    }
    else {
        window->pos_y = y;
    }
    HuSprGrpCenterSet(group, w / 2, h / 2);
    HuSprGrpPosSet(group, window->pos_x, window->pos_y);
    frame_data = HuAR_ARAMtoMRAMFileRead(frameFileTbl[frame], MEMORY_DEFAULT_NUM, HEAP_DATA);
    window->frame = HuSprAnimRead(frame_data);
    sprite = window->sprite_id[0] = HuSprCreate(window->frame, winPrio, 0);
    HuSprGrpMemberSet(group, 0, sprite);
    HuSprTPLvlSet(group, 0, 0.9f);
    bg_anim = HuSprAnimMake(w / 16, h / 16, 6);
    HuSprBGSet(group, 0, bg_anim, 0);
    window->color_key = winBGMake(bg_anim, window->frame);
    sprite = window->sprite_id[1] = HuSprFuncCreate(MesDispFunc, winPrio);
    sprite_ptr = &HuSprData[sprite];
    sprite_ptr->work[0] = window_id;
    HuSprGrpMemberSet(group, 1, sprite);
    window->num_chars = 0;
#if VERSION_JP
    window->max_chars = (w / 20) * (h / 24) * 3;
#else
    window->max_chars = (w / 8) * (h / 24) * 4;
#endif
    window->char_data = HuMemDirectMalloc(HEAP_SYSTEM, window->max_chars * sizeof(WinChar));
    window->attr = 0;
    window->stat = 0;
    window->unk8C = 0;
    window->mess_time = 0;
    window->mess_x = window->mess_y = 0;
    window->mess_rect_x = 8;
    window->mess_rect_y = 8;
    window->mess_rect_w = w - 8;
    window->mess_rect_h = h - 8;
    window->speed = 1;
    window->mess_color = 7;
    window->mess_shadow_color = 0;
    window->active_pad = 0xF;
    window->player_disable = 0;
    window->mess_stackptr = 0;
    window->mess = 0;
    window->num_choices = 0;
    window->prio = winPrio;
    window->spacing_x = 1;
    window->spacing_y = 2;
    window->w = w;
    window->h = h;
    window->scissor_x = window->scissor_y = 0;
    window->scissor_w = 0x280;
    window->scissor_h = 0x1E0;
    window->tab_w = 24;
    window->push_key = 0x300;
#if !VERSION_JP
    window->key_auto = 0;
#endif
    if (frame == 0 || frame == 2) {
        memcpy(&window->mess_pal, &charColPal[30], 30);
    }
    else {
        memcpy(&window->mess_pal, charColPal, 30);
        window->mess_shadow_color = 9;
    }
    for (i = 0; i < 8; i++) {
        window->insert_mess[i] = 0;
    }
    for (i = 2; i < 30; i++) {
        window->sprite_id[i] = -1;
    }
    winPrio -= 3;
    if (winPrio < 500) {
        winPrio = 1000;
    }
    for (i = 0; i < 16; i++) {
        window->choice_disable[i] = 0;
        window->choice_data[i].stat = 0;
    }
    return window_id;
}

void HuWinKill(s16 window)
{
    WindowData *window_ptr = &winData[window];
    s16 i;

    if (window_ptr->group != -1) {
        HuMemDirectFree(window_ptr->char_data);
        for (i = 2; i < 30; i++) {
            if (window_ptr->sprite_id[i] != -1) {
                HuSprGrpMemberKill(window_ptr->group, i);
            }
        }
        HuSprGrpKill(window_ptr->group);
        window_ptr->group = -1;
    }
}

void HuWinAllKill(void)
{
    s16 i;

    for (i = 0; i < 32; i++) {
        if (winData[i].group != -1) {
            HuWinKill(i);
        }
    }
    if (fontAnim != 0) {
        HuSprAnimKill(fontAnim);
        fontAnim = 0;
    }
    if (iconAnim != 0) {
        HuSprAnimKill(iconAnim);
        iconAnim = 0;
    }
    if (cursorAnim != 0) {
        HuSprAnimKill(cursorAnim);
        cursorAnim = 0;
    }
    if (cardAnimA != 0) {
        HuSprAnimKill(cardAnimA);
        cardAnimA = 0;
    }
    if (cardAnimB != 0) {
        HuSprAnimKill(cardAnimB);
        cardAnimB = 0;
    }
    if (winProc != 0) {
        HuPrcKill(winProc);
        winProc = 0;
    }
    if (messDataPtr != 0) {
        HuMemDirectFree(messDataPtr);
        messDataPtr = 0;
    }
    HuDataDirClose(DATADIR_WIN);
}

static void MesDispFunc(HuSprite *sprite)
{
    WindowData *window = &winData[sprite->work[0]];
    HuSprGrp *group;
    float uv_maxx;
    float uv_maxy;
    float uv_minx;
    float uv_miny;
    float char_w;
    float char_x;
    float char_y;
    float char_uv_h;
    s16 i;
    u16 alpha;
    s16 color;
    Mtx scale;
    Mtx modelview;
    Mtx44 proj;

    if (window->num_chars != 0) {
        group = &HuSprGrpData[window->group];
        GXInvalidateTexAll();
        C_MTXOrtho(proj, 0.0f, HU_DISP_HEIGHTF, 0.0f, HU_DISP_WIDTHF, 0.0f, 10.0f);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_RGBA8, 0);
        GXSetCullMode(GX_CULL_NONE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        GXSetNumTevStages(1);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 1, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(0);
        MTXRotRad(modelview, 'z', MTXDegToRad(sprite->z_rot));
        MTXScale(scale, sprite->scale_x, sprite->scale_y, 1.0f);
        MTXConcat(modelview, scale, modelview);
        mtxTransCat(modelview, sprite->x, sprite->y, 0.0f);
        MTXConcat(*sprite->group_mtx, modelview, modelview);
        GXLoadPosMtxImm(modelview, 0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        HuSprTexLoad(fontAnim, 0, 0, GX_CLAMP, GX_CLAMP, VERSION_JP ? GX_NEAR : GX_LINEAR);
        GXBegin(GX_QUADS, GX_VTXFMT0, window->num_chars * 4);
        char_uv_h = (LanguageNo == 0) ? (24.0f / 408.0f) : (24.0f / 312.0f);
        for (i = 0; i < window->num_chars; i++) {
            char_w = fontWidthP[window->char_data[i].character + 48];
#if VERSION_JP
            uv_minx = 0.003125 + (20.0f / 320.0f) * (window->char_data[i].character % 16);
#else
            uv_minx = (20.0f / 320.0f) * (window->char_data[i].character % 16);
#endif
            uv_miny = char_uv_h * (window->char_data[i].character / 16);
            uv_maxx = uv_minx + (char_w / 320.0);
            uv_maxy = uv_miny + char_uv_h;
            char_x = window->char_data[i].x;
            char_y = window->char_data[i].y;
            color = window->char_data[i].color;
            if (window->speed != 0) {
                alpha = window->char_data[i].fade * 8;
            }
            else {
                alpha = 255;
            }
            alpha = 255;
            if (window->char_data[i].fade < 31) {
                window->char_data[i].fade++;
            }
            GXPosition3f32(char_x + 1.0f, char_y, 0.0f);
            GXColor4u8(window->mess_pal[color][0], window->mess_pal[color][1], window->mess_pal[color][2], alpha);
            GXPosition2f32(uv_minx, uv_miny);
            GXPosition3f32(char_x + char_w, char_y, 0.0f);
            GXColor4u8(window->mess_pal[color][0], window->mess_pal[color][1], window->mess_pal[color][2], alpha);
            GXPosition2f32(uv_maxx, uv_miny);
            GXPosition3f32(char_x + char_w, char_y + 24.0f, 0.0f);
            GXColor4u8(window->mess_pal[color][0], window->mess_pal[color][1], window->mess_pal[color][2], alpha);
            GXPosition2f32(uv_maxx, uv_maxy);
            GXPosition3f32(char_x + 1.0f, char_y + 24.0f, 0.0f);
            GXColor4u8(window->mess_pal[color][0], window->mess_pal[color][1], window->mess_pal[color][2], alpha);
            GXPosition2f32(uv_minx, uv_maxy);
        }
        GXEnd();
        mesCharCnt++;
    }
}

static u8 winBGMake(AnimData *bg, AnimData *frame)
{
    AnimBmpData *bmp;
    s16 block_h;
    s16 h;
    s16 block_w;
    s16 w;
    s16 i;
    s16 j;
    u8 *bmp_data;
    u16 *palette;

    w = bg->bmp->sizeX;
    h = bg->bmp->sizeY;
    block_w = (w + 7) & 0xF8;
    block_h = (h + 3) & 0xFC;
    bmp_data = bg->bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, block_w * block_h, MEMORY_DEFAULT_NUM);
    for (i = 0; i < h; i++) {
        if (i == 0) {
            for (j = 0; j < w; j++) {
                if (j == 0) {
                    bmp_data[(j & 7) + ((j >> 3) << 5) + (i >> 2) * (block_w * 4) + (i & 3) * 8] = 0;
                }
                else if (j == w - 1) {
                    bmp_data[(j & 7) + ((j >> 3) << 5) + (i >> 2) * (block_w * 4) + (i & 3) * 8] = 0x10;
                }
                else {
                    bmp_data[(j & 7) + ((j >> 3) << 5) + (i >> 2) * (block_w * 4) + (i & 3) * 8] = 0x70;
                }
            }
        }
        else if (i == h - 1) {
            for (j = 0; j < w; j++) {
                if (j == 0) {
                    bmp_data[(j & 7) + ((j >> 3) << 5) + (i >> 2) * (block_w * 4) + (i & 3) * 8] = 0x20;
                }
                else if (j == w - 1) {
                    bmp_data[(j & 7) + ((j >> 3) << 5) + (i >> 2) * (block_w * 4) + (i & 3) * 8] = 0x30;
                }
                else {
                    bmp_data[(j & 7) + ((j >> 3) << 5) + (i >> 2) * (block_w * 4) + (i & 3) * 8] = 0x60;
                }
            }
        }
        else {
            for (j = 0; j < w; j++) {
                if (j == 0) {
                    bmp_data[(j & 7) + ((j >> 3) << 5) + (i >> 2) * (block_w * 4) + (i & 3) * 8] = 0x40;
                }
                else if (j == w - 1) {
                    bmp_data[(j & 7) + ((j >> 3) << 5) + (i >> 2) * (block_w * 4) + (i & 3) * 8] = 0x50;
                }
                else {
                    bmp_data[(j & 7) + ((j >> 3) << 5) + (i >> 2) * (block_w * 4) + (i & 3) * 8] = 0x80;
                }
            }
        }
    }
    DCStoreRangeNoSync(bg->bmp->data, block_w * block_h);
    bmp = frame->bmp;
    palette = bmp->palData;
    for (w = 0; w < bmp->palNum; w++, palette++) {
        if (*palette == 0xFC00) {
            *palette = 0x6114;
            break;
        }
    }
    DCStoreRangeNoSync(bmp->palData, 0x200);
    return w;
}

static void HuWinProc(void)
{
    WindowData *window;
    s16 i;

    while (1) {
        HuPrcVSleep();
        window = winData;
        for (i = 0; i < 32; i++, window++) {
            if (window->group != -1 && !(window->attr & 8)) {
                switch (window->stat) {
                    case 0:
                        break;
                    case 1:
                        HuWinDrawMes(i);
                        break;
                    case 2:
                        HuWinComKeyGet(i, winKey);
                        HuWinKeyWait(i);
                        break;
                    case 3:
                        if (!(window->attr & 0x40) || HuWinActiveKeyGetX(window) == 0) {
                            window->attr &= ~0x40;
                            HuWinComKeyGet(i, winKey);
                            HuWinChoice(window);
                        }
                        break;
                }
            }
        }
    }
}

static inline void charEntry(s16 window, s16 x, s16 y, s16 char_idx, s16 color)
{
    WindowData *window_ptr = &winData[window];
    WinChar *win_char = window_ptr->char_data;

    win_char = &window_ptr->char_data[window_ptr->num_chars];
    win_char->x = x - window_ptr->w / 2;
    win_char->y = y - window_ptr->h / 2;
    win_char->character = char_idx - 48;
    win_char->color = color;
    win_char->fade = 0;
    window_ptr->num_chars++;
    if (window_ptr->num_chars >= window_ptr->max_chars) {
        window_ptr->num_chars = window_ptr->max_chars - 1;
    }
}

static void HuWinDrawMes(s16 window)
{
    WindowData *window_ptr = &winData[window];
    HuSprGrp *group = &HuSprGrpData[window_ptr->group];
    s16 i;
    s16 char_w;
    s16 tab_w;
    s16 insert_mess;
    s16 mess_end;
    s16 c;

    s16 shadow_color;
    s16 color;
    s16 mess_w;

    window_ptr->mess_time += VERSION_JP ? 1 : 3;
    while (window_ptr->mess_time >= window_ptr->speed || (window_ptr->attr & 0x2000)) {
#if VERSION_JP
        window_ptr->mess_time = 0;
#else
        window_ptr->mess_time -= window_ptr->speed;
        if (window_ptr->mess_time < 0) {
            window_ptr->mess_time = 0;
        }
#endif
        char_w = window_ptr->spacing_x + fontWidthP[window_ptr->mess[0]];
        mess_end = 0;
        if (window_ptr->mess[0] != 0 && (window_ptr->attr & 4)) {
            window_ptr->attr &= ~4;
            _HuWinHomeClear(window_ptr);
        }
        while (window_ptr->mess[0] < 48 || window_ptr->mess[0] == 255) {
            switch (window_ptr->mess[0]) {
                case 0:
                    if (window_ptr->mess_stackptr == 0) {
                        for (i = 0; i < 16; i++) {
                            window_ptr->choice_disable[i] = 0;
                        }
                        window_ptr->stat = 0;
                        window_ptr->attr &= ~0x80;
                        return;
                    }
                    window_ptr->mess_stackptr--;
                    window_ptr->mess = window_ptr->mess_stack[window_ptr->mess_stackptr];
#if !VERSION_JP
                    window_ptr->mess_time = 0;
#endif
                    break;

                case 31:
                    window_ptr->mess++;
                    insert_mess = window_ptr->mess[0] - 1;
                    if (window_ptr->insert_mess[insert_mess] != 0) {
                        window_ptr->mess_stack[window_ptr->mess_stackptr] = window_ptr->mess;
                        window_ptr->mess = window_ptr->insert_mess[insert_mess];
                        window_ptr->mess_stackptr++;
                        if (window_ptr->mess[0] != 0xB) {
                            window_ptr->mess--;
                        }
                    }
                    break;

                case 11:
                    window_ptr->attr &= ~0x2200;
                    _HuWinHomeClear(window_ptr);
                    if (window_ptr->attr & 0x800) {
                        mess_w = GetMesMaxSizeSub2(window_ptr, window_ptr->mess + 1);
                        window_ptr->mess_x = (window_ptr->mess_rect_w - mess_w) / 2;
                    }
                    else if (window_ptr->attr & 0x1000) {
                        mess_w = GetMesMaxSizeSub2(window_ptr, window_ptr->mess + 1);
                        window_ptr->mess_x = window_ptr->mess_rect_w - mess_w;
                    }
                    break;

                case 30:
                    window_ptr->mess++;
                    if (!(window_ptr->attr & 0x80)) {
                        window_ptr->mess_color = window_ptr->mess[0] - 1;
                    }
                    break;

                case 29:
                    window_ptr->attr ^= 1;
                    break;

                case 10:
                    window_ptr->attr &= ~0x2020;
                    if (window_ptr->attr & 0x200) {
                        if (!(window_ptr->attr & 0x100)) {
                            if (HuWinCR(window_ptr) != 0) {
                                window_ptr->mess++;
                                HuWinKeyWaitEntry(window);
                                window_ptr->attr |= 2;
                                return;
                            }
                            if (window_ptr->attr & 0x800) {
                                mess_w = GetMesMaxSizeSub2(window_ptr, window_ptr->mess + 1);
                                window_ptr->mess_x = (window_ptr->mess_rect_w - mess_w) / 2;
                            }
                            else if (window_ptr->attr & 0x1000) {
                                mess_w = GetMesMaxSizeSub2(window_ptr, window_ptr->mess + 1);
                                window_ptr->mess_x = window_ptr->mess_rect_w - mess_w;
                            }
                            break;
                        }
                        char_w = fontWidthP[16] + window_ptr->spacing_x;
                            /* fallthrough */
                        case 16:
                        case 32:
                            window_ptr->attr |= 0x200;
                            if (window_ptr->mess_x + char_w > window_ptr->mess_rect_w) {
                                if (HuWinCR(window_ptr) != 0) {
                                    window_ptr->mess++;
                                    HuWinKeyWaitEntry(window);
                                    window_ptr->attr |= 2;
                                    return;
                                }
                                break;
                            }
                            window_ptr->mess_x += char_w;
                    }
                    break;

                case 14:
                    window_ptr->attr |= 0x200;
                    window_ptr->mess++;
                    tab_w = window_ptr->spacing_x + spcFontTbl[window_ptr->mess[0] - 1].w;
                    if (window_ptr->mess_x + tab_w > window_ptr->mess_rect_w && HuWinCR(window_ptr) != 0) {
                        window_ptr->mess--;
                        HuWinKeyWaitEntry(window);
                        window_ptr->attr |= 2;
                        return;
                    }
                    HuWinSpcFontEntry(window_ptr, window_ptr->mess[0] - 1, window_ptr->mess_rect_x + window_ptr->mess_x,
                        window_ptr->mess_rect_y + window_ptr->mess_y);
                    window_ptr->mess_x += tab_w;
                    mess_end = 1;
                    break;

                case 28:
                    window_ptr->mess++;
                    HuAudFXPlay(winVoiceTbl[window_ptr->mess[0] - 1]);
                    break;

                case 255:
                    window_ptr->mess++;
                    HuWinKeyWaitEntry(window);
                    window_ptr->attr |= 4;
                    window_ptr->attr &= ~0x200;
                    return;

                case 15:
                    window_ptr->attr |= 0x2000;
                    if (window_ptr->choice_disable[window_ptr->num_choices] != 0) {
                        window_ptr->attr |= 0x20;
                        window_ptr->choice_data[window_ptr->num_choices].stat |= 1;
                    }
                    else {
                        window_ptr->choice_data[window_ptr->num_choices].stat &= ~1;
                    }

                    window_ptr->choice_data[window_ptr->num_choices].x = window_ptr->mess_x + window_ptr->mess_rect_y;
                    window_ptr->choice_data[window_ptr->num_choices].y = window_ptr->mess_y + window_ptr->mess_rect_x;
                    window_ptr->num_choices++;
                    break;

                case 12:
                    window_ptr->attr |= 0x200;
                    tab_w = window_ptr->tab_w * ((window_ptr->mess_x + window_ptr->tab_w) / window_ptr->tab_w) - window_ptr->mess_x;
                    if (window_ptr->mess_x + tab_w > window_ptr->mess_rect_w) {
                        if (HuWinCR(window_ptr) != 0) {
                            window_ptr->mess++;
                            HuWinKeyWaitEntry(window);
                            window_ptr->attr |= 2;
                            return;
                        }
                    }
                    else {
                        window_ptr->mess_x += tab_w;
                    }
                    break;
            }
            window_ptr->mess++;
            char_w = window_ptr->spacing_x + fontWidthP[window_ptr->mess[0]];
            if (mess_end != 0) {
                break;
            }
        }
        if (mess_end == 0) {
            if (window_ptr->mess_x + char_w > window_ptr->mess_rect_w && HuWinCR(window_ptr) != 0) {
                HuWinKeyWaitEntry(window);
                window_ptr->attr |= 2;
                return;
            }
            c = window_ptr->mess[0];
            window_ptr->attr |= 0x200;
#if VERSION_NTSC
            if (window_ptr->mess[1] == 128) {
                if (c >= 150 && c <= 164) {
                    c = c + 106;
                }
                else if (c >= 170 && c <= 174) {
                    c = c + 101;
                }
                else if (c >= 214 && c <= 228) {
                    c = c + 67;
                }
                else if (c >= 234 && c <= 238) {
                    c = c + 62;
                }
                window_ptr->mess++;
            }
            else if (window_ptr->mess[1] == 129) {
                if (c >= 170 && c <= 174) {
                    c = c + 106;
                }
                else if (c >= 234 && c <= 238) {
                    c = c + 67;
                }
                window_ptr->mess++;
            }
#endif
            color = (window_ptr->attr & 0x20) ? 8 : window_ptr->mess_color;
            if (window_ptr->attr & 1) {
                shadow_color = 0;
                if (window_ptr->mess_color == 0 || window_ptr->mess_color == 1) {
                    shadow_color = 8;
                }
                charEntry(window, window_ptr->mess_rect_x + window_ptr->mess_x + 2, window_ptr->mess_rect_y + window_ptr->mess_y, c, shadow_color);
                charEntry(window, window_ptr->mess_rect_x + window_ptr->mess_x - 2, window_ptr->mess_rect_y + window_ptr->mess_y, c, shadow_color);
                charEntry(window, window_ptr->mess_rect_x + window_ptr->mess_x, window_ptr->mess_rect_y + window_ptr->mess_y + 2, c, shadow_color);
                charEntry(window, window_ptr->mess_rect_x + window_ptr->mess_x, window_ptr->mess_rect_y + window_ptr->mess_y - 2, c, shadow_color);
                charEntry(window, window_ptr->mess_rect_x + window_ptr->mess_x, window_ptr->mess_rect_y + window_ptr->mess_y, c, color);
            }
            else {
                charEntry(window, window_ptr->mess_rect_x + window_ptr->mess_x + 2, window_ptr->mess_rect_y + window_ptr->mess_y + 2, c,
                    window_ptr->mess_shadow_color);
                charEntry(window, window_ptr->mess_rect_x + window_ptr->mess_x, window_ptr->mess_rect_y + window_ptr->mess_y, c, color);
            }
            window_ptr->mess_x += char_w;
            window_ptr->mess++;
        }
    }
}

static s32 HuWinCR(WindowData *window)
{
    if (window->mess_y + 48 > window->mess_rect_h) {
        window->mess_y = 0;
        window->mess_x = 0;
        return 1;
    }
    else {
        window->mess_y += window->spacing_y + 24;
        window->mess_x = 0;
        return 0;
    }
}

static void _HuWinHomeClear(WindowData *window)
{
    s16 i;

    window->num_chars = 0;
    window->mess_y = window->mess_x = 0;
    window->num_choices = 0;
    HuWinSpcFontClear(window);
    window->attr &= ~0x2020;
    for (i = 0; i < 16; i++) {
        window->choice_data[i].stat = 0;
    }
}

void HuWinHomeClear(s16 window)
{
    WindowData *window_ptr = &winData[window];

    _HuWinHomeClear(window_ptr);
}

void HuWinKeyWaitEntry(s16 window)
{
    WindowData *window_ptr = &winData[window];

    if (window_ptr->attr & 0x400) {
        window_ptr->stat = 0;
    }
    else {
        window_ptr->stat = 2;
        window_ptr->advance_sprite = HuWinSpcFontEntry(window_ptr, 19, window_ptr->mess_rect_w - 20, window_ptr->mess_rect_h - 24);
    }
}

static void HuWinKeyWait(s16 window)
{
    WindowData *window_ptr = &winData[window];

    if (window_ptr->push_key & HuWinActivePadGet(window_ptr)) {
        window_ptr->key_down = HuWinActivePadGet(window_ptr);
        window_ptr->stat = 1;
        HuAudFXPlay(28);
        HuWinSprKill(window, window_ptr->advance_sprite);
        if (window_ptr->attr & 2) {
            _HuWinHomeClear(window_ptr);
        }
        window_ptr->attr &= ~2;
    }
}

static s16 HuWinSpcFontEntry(WindowData *window, s16 entry, s16 x, s16 y)
{
    HuSprGrp *group = &HuSprGrpData[window->group];
    s16 sprite;
    s16 i;
    AnimData *anim;

    for (i = 10; i < 30; i++) {
        if (window->sprite_id[i] == -1) {
            anim = *spcFontTbl[entry].anim;
            window->sprite_id[i] = sprite = HuSprCreate(anim, window->prio - 1, spcFontTbl[entry].bank);
            HuSprGrpMemberSet(window->group, i, sprite);
            HuSprPosSet(window->group, i, x + spcFontTbl[entry].center_x - window->w / 2, y + spcFontTbl[entry].center_y - window->h / 2);
            break;
        }
    }
    return i;
}

static void HuWinSpcFontPosSet(WindowData *window, s16 index, s16 x, s16 y)
{
    HuSprGrp *group = &HuSprGrpData[window->group];

    HuSprPosSet(window->group, index, x - window->w / 2, y - window->h / 2);
}

static void HuWinSpcFontClear(WindowData *window)
{
    s16 i;

    for (i = 10; i < 30; i++) {
        if (window->sprite_id[i] != -1) {
            HuSprGrpMemberKill(window->group, i);
            window->sprite_id[i] = -1;
        }
    }
}

static void HuWinChoice(WindowData *window)
{
    WinChoice *choice;
    float choice_dist;
    float min_choice_dist_x;
    s16 choice_dist_y;
    s16 key;
    s16 choice_curr_x;
    s16 choice_curr_y;
    s16 choice_curr;
    s16 choice_max;
    s16 choice_dist_x;
    s16 dir;
    s16 choice_y;
    s16 choice_next;
    s16 i;

    choice_curr = window->choice;
    choice_next = choice_curr;
    dir = -1;
    key = HuWinActivePadGet(window);
    if (key & 1) {
        dir = 0;
    }
    if (key & 2) {
        dir = 2;
    }
    if (key & 8) {
        dir = 1;
    }
    if (key & 4) {
        dir = 3;
    }
    choice_curr_x = window->choice_data[choice_curr].x;
    choice_curr_y = window->choice_data[choice_curr].y;
    min_choice_dist_x = 100000.0f;
    choice_dist = min_choice_dist_x;
    choice_max = window->num_choices;
    switch (dir) {
        case 0:
            for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                if (i != choice_curr && !(choice->stat & 1) && choice->y == choice_curr_y && choice->x < choice_curr_x) {
                    break;
                }
            }
            if (i != choice_max) {
                for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                    if (i != choice_curr && !(choice->stat & 1) && choice->y == choice_curr_y && choice->x < choice_curr_x
                        && choice_dist > choice_curr_x - choice->x) {
                        choice_dist = choice_curr_x - choice->x;
                        choice_next = i;
                    }
                }
            }
            break;
        case 1:
            for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                if (i != choice_curr && !(choice->stat & 1) && choice->y < choice_curr_y) {
                    break;
                }
            }
            if (i != choice_max) {
                for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                    if (i != choice_curr && !(choice->stat & 1) && choice->y < choice_curr_y) {
                        choice_dist_y = choice_curr_y - choice->y;
                        if (choice_dist_y <= choice_dist) {
                            if (choice_dist_y < choice_dist) {
                                min_choice_dist_x = 100000.0f;
                            }
                            choice_dist_x = choice_curr_x - choice->x;
                            choice_dist_x = choice_dist_x * choice_dist_x;
                            if (choice_dist_x < min_choice_dist_x) {
                                choice_dist = choice_dist_y;
                                min_choice_dist_x = choice_dist_x;
                                choice_next = i;
                            }
                        }
                    }
                }
            }
            else {
                choice_y = -1000;
                for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                    if (i != choice_curr && !(choice->stat & 1) && choice->y > choice_y) {
                        choice_y = choice->y;
                    }
                }
                if (choice_y != choice_curr_y) {
                    min_choice_dist_x = 100000.0f;
                    for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                        if (i != choice_curr && !(choice->stat & 1) && choice->y == choice_y) {
                            choice_dist_x = choice_curr_x - choice->x;
                            choice_dist_x = choice_dist_x * choice_dist_x;
                            if (choice_dist_x < min_choice_dist_x) {
                                min_choice_dist_x = choice_dist_x;
                                choice_next = i;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                if (i != choice_curr && !(choice->stat & 1) && choice->y == choice_curr_y && choice->x > choice_curr_x) {
                    break;
                }
            }
            if (i != choice_max) {
                for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                    if (i != choice_curr && !(choice->stat & 1) && choice->y == choice_curr_y && choice->x > choice_curr_x
                        && choice_dist > choice->x - choice_curr_x) {
                        choice_dist = choice->x - choice_curr_x;
                        choice_next = i;
                    }
                }
            }
            break;
        case 3:
            for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                if (i != choice_curr && !(choice->stat & 1) && choice->y > choice_curr_y) {
                    break;
                }
            }
            if (i != choice_max) {
                for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                    if (i != choice_curr && !(choice->stat & 1) && choice->y > choice_curr_y) {
                        choice_dist_y = choice->y - choice_curr_y;
                        if (choice_dist_y <= choice_dist) {
                            if (choice_dist_y < choice_dist) {
                                min_choice_dist_x = 100000.0f;
                            }
                            choice_dist_x = choice_curr_x - choice->x;
                            choice_dist_x = choice_dist_x * choice_dist_x;
                            if (choice_dist_x < min_choice_dist_x) {
                                choice_dist = choice_dist_y;
                                min_choice_dist_x = choice_dist_x;
                                choice_next = i;
                            }
                        }
                    }
                }
            }
            else {
                choice_y = 1000;
                for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                    if (i != choice_curr && !(choice->stat & 1) && choice->y < choice_y) {
                        choice_y = choice->y;
                    }
                }
                if (choice_y != choice_curr_y) {
                    min_choice_dist_x = 100000.0f;
                    for (i = 0, choice = window->choice_data; i < choice_max; i++, choice++) {
                        if (i != choice_curr && !(choice->stat & 1) && choice->y == choice_y) {
                            choice_dist_x = choice_curr_x - choice->x;
                            choice_dist_x = choice_dist_x * choice_dist_x;
                            if (choice_dist_x < min_choice_dist_x) {
                                min_choice_dist_x = choice_dist_x;
                                choice_next = i;
                            }
                        }
                    }
                }
            }
            break;
    }
    if (window->choice != choice_next) {
        window->choice = choice_next;
        HuAudFXPlay(0);
    }
    else if (key & (VERSION_JP ? PAD_BUTTON_A : (window->key_auto | PAD_BUTTON_A))) {
        HuAudFXPlay(2);
        window->key_down = key;
        window->stat = 0;
    }
    else if ((key & PAD_BUTTON_B) && !(window->attr & 0x10)) {
        HuAudFXPlay(3);
#if !VERSION_JP
        window->key_down = key;
#else
        (void)key; // hack to match Japanese version
#endif
        window->choice = -1;
        window->stat = 0;
    }
    HuWinSpcFontPosSet(window, window->cursor_sprite, window->choice_data[choice_next].x + spcFontTbl[20].center_x,
        window->choice_data[choice_next].y + spcFontTbl[20].center_y);
}

u32 HuWinActivePadGet(WindowData *window)
{
    s32 win_key;
    u32 i;

    win_key = 0;
    for (i = 0; i < 4; i++) {
        if (window->active_pad & (1 << i)) {
            win_key |= winKey[i];
        }
    }
    return win_key;
}

u32 HuWinActiveKeyGetX(WindowData *window)
{
    u32 button;
    u32 i;
    u32 j;
    u8 active_pad;

    button = 0;
    active_pad = (window->active_pad & ~window->player_disable);
    for (i = 0; i < 4; i++) {
        if (active_pad & (1 << i)) {
            for (j = 0; j < 4; j++) {
                if (i == GWPlayerCfg[j].pad_idx) {
                    break;
                }
            }
            if (j != 4 && GWPlayerCfg[j].iscom == 0) {
                button |= HuPadBtn[GWPlayerCfg[j].pad_idx];
            }
        }
    }
    return button;
}

void HuWinPosSet(s16 window, float x, float y)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->pos_x = x;
    window_ptr->pos_y = y;
    HuSprGrpPosSet(window_ptr->group, x, y);
}

void HuWinScaleSet(s16 window, float x, float y)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->scale_x = x;
    window_ptr->scale_y = y;
    HuSprGrpScaleSet(window_ptr->group, x, y);
}

void HuWinZRotSet(s16 window, float z_rot)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->z_rot = z_rot;
    HuSprGrpZRotSet(window_ptr->group, z_rot);
}

void HuWinCenterPosSet(s16 window, float x, float y)
{
    WindowData *window_ptr = &winData[window];

    HuSprGrpCenterSet(window_ptr->group, window_ptr->w / 2.0f - x, window_ptr->h / 2.0f - y);
}

void HuWinDrawNoSet(s16 window, s16 draw_no)
{
    WindowData *window_ptr = &winData[window];

    HuSprGrpDrawNoSet(window_ptr->group, draw_no);
}

void HuWinScissorSet(s16 window, s16 x, s16 y, s16 w, s16 h)
{
    WindowData *window_ptr = &winData[window];

    HuSprGrpScissorSet(window_ptr->group, x, y, w, h);
}

void HuWinPriSet(s16 window, s16 prio)
{
    WindowData *window_ptr = &winData[window];
    s16 i;

    HuSprPriSet(window_ptr->group, 0, prio);
    HuSprPriSet(window_ptr->group, 1, prio);
    for (i = 2; i < 30; i++) {
        if (window_ptr->sprite_id[i] != -1) {
            HuSprPriSet(window_ptr->group, i, prio - 1);
        }
    }
    window_ptr->prio = prio;
}

void HuWinAttrSet(s16 window, u32 attr)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->attr |= attr;
}

void HuWinAttrReset(s16 window, u32 attr)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->attr &= ~attr;
}

s16 HuWinStatGet(s16 window)
{
    WindowData *window_ptr = &winData[window];

    return window_ptr->stat;
}

void HuWinMesColSet(s16 window, u8 color)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->mess_color = color;
    window_ptr->attr |= 0x80;
}

void HuWinMesPalSet(s16 window, u8 index, u8 r, u8 g, u8 b)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->mess_pal[index][0] = r;
    window_ptr->mess_pal[index][1] = g;
    window_ptr->mess_pal[index][2] = b;
}

void HuWinBGTPLvlSet(s16 window, float tp_level)
{
    WindowData *window_ptr = &winData[window];

    HuSprTPLvlSet(window_ptr->group, 0, tp_level);
}

void HuWinBGColSet(s16 window, GXColor *bg_color)
{
    WindowData *window_ptr = &winData[window];

    HuSprColorSet(window_ptr->group, 0, bg_color->r, bg_color->g, bg_color->b);
}

void HuWinMesSpeedSet(s16 window, s16 speed)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->speed = speed;
}

void HuWinMesRead(s32 mess_data_no)
{
    void *dvd_mess;
    char *mess_path;

    if (messDataPtr) {
        HuMemDirectFree(messDataPtr);
    }
    messDataNo = mess_data_no;
#if VERSION_NTSC
    if (LanguageNo == 0) {
        mess_path = mesDataTbl[messDataNo];
    }
    else {
        mess_path = mesDataTbl[messDataNo + 2];
    }
#else
    mess_path = mesDataTbl[messDataNo + (LanguageNo * 2)];
#endif
    dvd_mess = HuDvdDataRead(mess_path);
    messDataPtr = HuMemDirectMalloc(HEAP_SYSTEM, DirDataSize);
    memcpy(messDataPtr, dvd_mess, DirDataSize);
    HuMemDirectFree(dvd_mess);
}

void HuWinMesSet(s16 window, u32 mess)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->stat = 1;
    if ((mess & 0x80000000) == 0) {
        if (messDataPtr == 0) {
            OSReport("Error: No Message\n");
            return;
        }
        window_ptr->mess = MessData_MesPtrGet(messDataPtr, mess);
        if (window_ptr->mess == 0) {
            OSReport("Error: No Message data\n");
#if !VERSION_JP
            HuWinMesSet(window, 0);
            return;
#endif
        }
    }
    else {
        window_ptr->mess = (u8 *)mess;
    }
    if (!(window_ptr->attr & 0x80)) {
        window_ptr->mess_color = 7;
#if !VERSION_JP
        window_ptr->mess_time = 0;
#endif
    }
}

void HuWinInsertMesSet(s16 window, u32 mess, s16 index)
{
    WindowData *window_ptr = &winData[window];

    if (!(mess & 0x80000000)) {
        if (messDataPtr == 0) {
            OSReport("Error: No Message\n");
            return;
        }
        window_ptr->insert_mess[index] = MessData_MesPtrGet(messDataPtr, mess);
        if (window_ptr->insert_mess[index] == 0) {
            OSReport("Error: No Message data\n");
        }
    }
    else {
        window_ptr->insert_mess[index] = (u8 *)mess;
    }
}

s16 HuWinChoiceGet(s16 window, s16 start_choice)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->attr |= 0x40;
    while (window_ptr->stat != 0) {
        HuPrcVSleep();
    }
    for (; start_choice < window_ptr->num_choices; start_choice++) {
        if (!(window_ptr->choice_data[start_choice].stat & 1)) {
            break;
        }
    }
    if (start_choice == window_ptr->num_choices) {
        for (start_choice = 0; start_choice < window_ptr->num_choices; start_choice++) {
            if (!(window_ptr->choice_data[start_choice].stat & 1)) {
                break;
            }
        }
        if (start_choice == window_ptr->num_choices) {
            return -1;
        }
    }
    window_ptr->cursor_sprite = HuWinSpcFontEntry(window_ptr, 0x14, window_ptr->choice_data[start_choice].x, window_ptr->choice_data[start_choice].y);
    window_ptr->stat = 3;
    window_ptr->choice = start_choice;
    while (window_ptr->stat != 0) {
        HuPrcVSleep();
    }
    return window_ptr->choice;
}

s16 HuWinChoiceNumGet(s16 window)
{
    WindowData *window_ptr = &winData[window];

    return window_ptr->num_choices;
}

void HuWinChoiceDisable(s16 window, s16 choice)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->choice_disable[choice] = 1;
}

s16 HuWinChoiceNowGet(s16 window)
{
    WindowData *window_ptr = &winData[window];

    if (window_ptr->stat == 3) {
        return window_ptr->choice;
    }
    else {
        return -1;
    }
}

void HuWinMesWait(s16 window)
{
    WindowData *window_ptr = &winData[window];

    while (window_ptr->stat != 0) {
        HuPrcVSleep();
    }
}

s16 HuWinAnimSet(s16 window, AnimData *anim, s16 bank, float x, float y)
{
    WindowData *window_ptr = &winData[window];
    s16 sprite;

    sprite = HuSprCreate(anim, window_ptr->prio - 1, bank);
    return HuWinSprSet(window, sprite, x, y);
}

s16 HuWinSprSet(s16 window, s16 sprite, float x, float y)
{
    WindowData *window_ptr = &winData[window];
    HuSprGrp *group = &HuSprGrpData[window_ptr->group];
    s16 i;

    for (i = 2; i <= 9; i++) {
        if (window_ptr->sprite_id[i] == -1) {
            window_ptr->sprite_id[i] = sprite;
            HuSprGrpMemberSet(window_ptr->group, i, sprite);
            HuSprPosSet(window_ptr->group, i, x - group->center_x, y - group->center_y);
            break;
        }
    }
    return i;
}

void HuWinSprPosSet(s16 window, s16 index, float x, float y)
{
    WindowData *window_ptr = &winData[window];
    HuSprGrp *group = &HuSprGrpData[window_ptr->group];

    HuSprPosSet(window_ptr->group, index, x - group->center_x, y - group->center_y);
}

void HuWinSprPriSet(s16 window, s16 index, s16 prio)
{
    WindowData *window_ptr = &winData[window];
    HuSprGrp *group = &HuSprGrpData[window_ptr->group];

    HuSprPriSet(window_ptr->group, index, prio);
}

s16 HuWinSprIDGet(s16 window, s16 index)
{
    WindowData *window_ptr = &winData[window];

    return window_ptr->sprite_id[index];
}

void HuWinSprKill(s16 window, s16 index)
{
    WindowData *window_ptr = &winData[window];

    HuSprGrpMemberKill(window_ptr->group, index);
    window_ptr->sprite_id[index] = -1;
}

void HuWinDispOff(s16 window)
{
    WindowData *window_ptr = &winData[window];
    s16 i;

    for (i = 0; i < 30; i++) {
        if (window_ptr->sprite_id[i] != -1) {
            HuSprAttrSet(window_ptr->group, i, HUSPR_ATTR_DISPOFF);
        }
    }
    window_ptr->attr |= 8;
}

void HuWinDispOn(s16 window)
{
    WindowData *window_ptr = &winData[window];
    s16 i;

    for (i = 0; i < 30; i++) {
        if (window_ptr->sprite_id[i] != -1) {
            HuSprAttrReset(window_ptr->group, i, HUSPR_ATTR_DISPOFF);
        }
    }
    window_ptr->attr = window_ptr->attr & ~8;
}

void HuWinComKeyWait(s32 player_1, s32 player_2, s32 player_3, s32 player_4, s16 delay)
{
    s32 wait_input_p4;
    s32 wait_input_p3;
    s32 wait_input_p2;
    s32 wait_input_p1;

    if (player_4 == -1) {
        wait_input_p4 = -1;
    }
    else {
        wait_input_p4 = 0;
    }
    if (player_3 == -1) {
        wait_input_p3 = -1;
    }
    else {
        wait_input_p3 = 0;
    }
    if (player_2 == -1) {
        wait_input_p2 = -1;
    }
    else {
        wait_input_p2 = 0;
    }
    if (player_1 == -1) {
        wait_input_p1 = -1;
    }
    else {
        wait_input_p1 = 0;
    }
    _HuWinComKeySet(wait_input_p1, wait_input_p2, wait_input_p3, wait_input_p4, delay);
    _HuWinComKeySet(player_1, player_2, player_3, player_4, 1);
}

void HuWinComKeySet(s32 player_1, s32 player_2, s32 player_3, s32 player_4)
{
    _HuWinComKeySet(player_1, player_2, player_3, player_4, 1);
}

void _HuWinComKeySet(s32 player_1, s32 player_2, s32 player_3, s32 player_4, s16 delay)
{
    winComKeyBuf[comKeyIdx].player[0] = player_1;
    winComKeyBuf[comKeyIdx].player[1] = player_2;
    winComKeyBuf[comKeyIdx].player[2] = player_3;
    winComKeyBuf[comKeyIdx].player[3] = player_4;
    winComKeyBuf[comKeyIdx].time = delay;
    comKeyIdx++;
    comKeyIdx &= 0xFF;
}

void HuWinComKeyGet(s16 window, u32 *data)
{
    WindowData *window_ptr = &winData[window];
    s16 i;

    if (comKeyIdx == comKeyIdxNow) {
        for (i = 0; i < 4; i++) {
            if (!(window_ptr->player_disable & (1 << i))) {
                data[i] = HuPadDStkRep[i] | HuPadBtnDown[i];
            }
            else {
                data[i] = 0;
            }
        }
    }
    else {
        for (i = 0; i < 4; i++) {
            data[i] = winComKeyBuf[comKeyIdxNow].player[i];
            if (data[i] == 0xFFFFFFFF) {
                if (!(window_ptr->player_disable & (1 << i))) {
                    data[i] = HuPadDStkRep[i] | HuPadBtnDown[i];
                }
                else {
                    data[i] = 0;
                }
            }
        }
        winComKeyBuf[comKeyIdxNow].time--;
        if (winComKeyBuf[comKeyIdxNow].time <= 0) {
            comKeyIdxNow++;
            comKeyIdxNow &= 0xFF;
        }
    }
}

void HuWinComKeyReset(void)
{
    comKeyIdx = comKeyIdxNow = 0;
}

void HuWinMesMaxSizeGet(s16 mess_num, float *size, ...)
{
    s16 i;
    u32 mess;
    va_list list;

    winInsertF = 0;
    va_start(list, size);
    winMaxWidth = winMaxHeight = 0;
    for (i = 0; i < mess_num; i++) {
        mess = va_arg(list, u32);
        GetMesMaxSizeSub(mess);
    }
    for (i = 0; i < 8; i++) {
        mesWInsert[i] = 0;
    }
    winTabSize = 24;
    cancelCRF = 0;
    size[0] = (winMaxWidth + 0x1F) & 0xFFF0;
    size[1] = winMaxHeight + 0x10;
    va_end(list);
}

void HuWinInsertMesSizeGet(u32 mess, s16 index)
{
    winInsertF = 1;
    winMaxWidth = winMaxHeight = 0;
    GetMesMaxSizeSub(mess);
    mesWInsert[index] = winMaxWidth;
}

void HuWinMesSizeCancelCRSet(s32 cancel_cr)
{
    cancelCRF = cancel_cr;
}

void HuWinMesMaxSizeBetGet(float *size, u32 start, u32 end)
{
    u32 i;

    if (end < start) {
        size[0] = size[1] = 100.0f;
    }
    else {
        winInsertF = 0;
        winMaxWidth = winMaxHeight = 0;
        for (i = start; i <= end; i++) {
            GetMesMaxSizeSub(i);
        }
        for (i = 0; i < 8; i++) {
            mesWInsert[i] = 0;
        }
        winTabSize = 24;
        cancelCRF = 0;
        size[0] = (winMaxWidth + 0x1F) & 0xFFF0;
        size[1] = winMaxHeight + 0x10;
    }
}

static void GetMesMaxSizeSub(u32 mess)
{
    s16 line_h;
    s16 char_w;
    s16 line_w;
    u8 *mess_start;
    s16 from_messdata;
    s16 char_h;
    s32 cr_flag;
    u8 *mess_data;

    mess_start = NULL;
    cr_flag = 0;
    if (mess > 0x80000000) {
        from_messdata = 0;
        mess_data = (u8 *)mess;
    }
    else {
        from_messdata = 1;
        mess_data = mess_start = MessData_MesPtrGet(messDataPtr, mess);
    }
    line_h = 26;
    line_w = 0;
    while (*mess_data != 0) {
        char_h = 0;
        char_w = fontWidthP[*mess_data] + 1;
        switch (*mess_data) {
            case 16:
            case 32:
                break;
            case 30:
                mess_data++;
                char_w = 0;
                break;
            case 10:
                if (cr_flag != 0) {
                    if (cancelCRF == 0) {
                        if (winMaxWidth < line_w) {
                            winMaxWidth = line_w;
                        }
                        line_w = char_w = 0;
                        if (mess_data[1] != 0) {
                            char_h = 26;
                        }
                    }
                    else {
                        char_w = fontWidthP[16] + 1;
                    }
                }
                break;
            case 255:
                line_w += char_w;
                /* fallthrough */
            case 11:
                cr_flag = 0;
                if (winInsertF == 0) {
                    if (winMaxWidth < line_w) {
                        winMaxWidth = line_w;
                    }
                    if (winMaxHeight < line_h) {
                        winMaxHeight = line_h;
                    }
                    line_h = 26;
                    char_h = 0;
                    line_w = char_w = 0;
                }
                break;
            case 28:
                mess_data++;
                /* fallthrough */
            case 15:
            case 29:
                char_w = 0;
                break;
            case 12:
                char_w = winTabSize * ((line_w + winTabSize) / winTabSize) - line_w;
                break;
            case 14:
                mess_data++;
                char_w = spcFontTbl[*mess_data - 1].w + 1;
                break;
            case 31:
                mess_data++;
                char_w = mesWInsert[*mess_data - 1];
                break;
        }
#if VERSION_NTSC
        if ((*mess_data != 255 && *mess_data >= 32) || *mess_data == 16) {
            cr_flag = 1;
        }
#else
        if ((*mess_data != 255 && *mess_data >= 32) || *mess_data == 16 || mess_data[-1] == 31) {
            cr_flag = 1;
        }
#endif
        line_w += char_w;
        line_h += char_h;
        mess_data++;
    }
    if (winMaxWidth < line_w) {
        winMaxWidth = line_w;
    }
    if (winMaxHeight < line_h) {
        winMaxHeight = line_h;
    }
}

static s32 GetMesMaxSizeSub2(WindowData *window, u8 *mess_data)
{
    s32 sp8;
    u8 mess_finish;
    s16 mess_h;
    s16 char_w;
    s16 mess_w;
    s32 mess_end;
    s16 char_h;
    u8 *mess;

    sp8 = 0;
    mess_end = 0;
    mess = mess_data;
    mess_h = 0x1A;
    mess_w = 0;
    mess_finish = 0;
    while (*mess != 0 && mess_finish == 0) {
        char_h = 0;
        char_w = fontWidthP[*mess] + 1;
        switch (*mess) {
            case 16:
            case 32:
                break;

            case 10:
                if (mess_end != 0 && !(window->attr & 0x100)) {
                    char_w = 0;
                    mess_finish = 1;
                }
                break;

            case 255:
                mess_w += char_w;
                /* fallthrough */
            case 11:
                mess_end = 0;
                mess_h = 0x1A;
                char_h = 0;
                mess_w = char_w = 0;
                break;

            case 28:
            case 30:
                mess++;
                /* fallthrough */
            case 15:
            case 29:
                char_w = 0;
                break;

            case 12:
                char_w = winTabSize * ((mess_w + winTabSize) / winTabSize) - mess_w;
                break;

            case 14:
                mess++;
                char_w = spcFontTbl[*mess - 1].w + 1;
                break;

            case 31:
                mess++;
                break;
        }
        if ((*mess != 0xFF && *mess >= 0x20) || *mess == 0x10) {
            mess_end = 1;
        }
        mess_w += char_w;
        mess_h += char_h;
        mess++;
    }
    return mess_w;
}

s16 HuWinKeyWaitNumGet(u32 mess)
{
    s16 wait_num;
    u8 *mess_data;
#ifdef __MWERKS__
    // TODO PC

    if (mess > 0x80000000) {
        mess_data = (u8 *)mess;
    }
    else {
        mess_data = MessData_MesPtrGet(messDataPtr, mess);
    }
    for (wait_num = 0; *mess_data != 0; mess_data++) {
        if (*mess_data == 0xFF) {
            wait_num++;
        }
    }
#endif
    return wait_num;
}

void HuWinPushKeySet(s16 window, s16 push_key)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->push_key = push_key;
}

void HuWinDisablePlayerSet(s16 window, u8 player)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->player_disable |= player;
}

void HuWinDisablePlayerReset(s16 window, u8 player)
{
    WindowData *window_ptr = &winData[window];

    window_ptr->player_disable &= ~(int)player;
}

static s32 winPortraitTbl[]
    = { WIN_TOAD_TALK_ANM, WIN_BOBOMB_TALK_ANM, WIN_SHYGUY_TALK_ANM, WIN_BOO_TALK_ANM, WIN_GOOMBA_TALK_ANM, WIN_BOWSER_TALK_ANM, WIN_KKID_TALK_ANM,
          WIN_KOOPA_TALK_ANM, WIN_CONDOR_TALK_ANM, WIN_BOO_BLUE_TALK_ANM, WIN_DOLPHIN_TALK_ANM, WIN_BOO_RED_TALK_ANM, WIN_THWOMP_TALK_ANM,
          WIN_W01_HOST_TALK_ANM, WIN_W02_HOST_TALK_ANM, WIN_W03_HOST_TALK_ANM, WIN_W04_HOST_TALK_ANM, WIN_W05_HOST_TALK_ANM, WIN_W06_HOST_TALK_ANM };

s16 HuWinExCreate(float x, float y, s16 w, s16 h, s16 portrait)
{
    return HuWinExCreateStyled(x, y, w, h, portrait, 0);
}

static void HuWinExCreatePortrait(s16 window, s16 portrait, float x, float y)
{
    s16 sprite;
    AnimData *anim;
    WindowData *window_ptr;
    void *data;

    data = HuAR_ARAMtoMRAMFileRead(winPortraitTbl[portrait], MEMORY_DEFAULT_NUM, HEAP_DATA);
    anim = HuSprAnimRead(data);
    window_ptr = &winData[window];
    sprite = HuSprCreate(anim, window_ptr->prio - 1, 0);
    HuWinSprSet(window, sprite, x, y);
}

s16 HuWinExCreateStyled(float x, float y, s16 w, s16 h, s16 portrait, s16 frame)
{
    WindowData *window_ptr;
    s16 window;

    if (portrait >= 0) {
        h = (h < 84) ? 84 : h;
    }
    window = HuWinCreate(x, y, w, h, frame);
    window_ptr = &winData[window];
    if (frame == 1) {
        window_ptr->mess_shadow_color = 9;
    }
    if (portrait >= 0) {
        HuWinExCreatePortrait(window, portrait, 48.0f, 48.0f);
    }
    HuWinDispOff(window);
    return window;
}

void HuWinExAnimIn(s16 window)
{
    WindowData *window_ptr = &winData[window];
    s16 i;

    _HuWinHomeClear(window_ptr);
    if (window_ptr->sprite_id[2] == -1) {
        HuSprScaleSet(window_ptr->group, 0, 1.0f, 0.0f);
        HuWinDispOn(window);
        for (i = 0; i <= 10; i++) {
            HuSprScaleSet(window_ptr->group, 0, 1.0f, 1.0 - 1.1 * cosd(9.0f * i));
            HuPrcVSleep();
        }
        HuSprScaleSet(window_ptr->group, 0, 1.0f, 1.0f);
    }
    else {
        HuSprScaleSet(window_ptr->group, 0, 1.0f, 0.0f);
        HuSprScaleSet(window_ptr->group, 2, 1.0f, 0.0f);
        HuWinDispOn(window);
        for (i = 0; i <= 20; i++) {
            if (i <= 10) {
                HuSprScaleSet(window_ptr->group, 0, 1.0f, 1.1 * (1.0 - cosd(9.0f * i)));
            }
            else {
                HuSprScaleSet(window_ptr->group, 0, 1.0f, 1.0f);
            }
            if (i > 10) {
                s16 time = i - 10;
                HuSprScaleSet(window_ptr->group, 2, 1.0f, 1.0 - 1.1 * cosd(9.0f * time));
            }
            HuPrcVSleep();
        }
        HuSprScaleSet(window_ptr->group, 2, 1.0f, 1.0f);
    }
}

void HuWinExAnimOut(s16 window)
{
    WindowData *window_ptr = &winData[window];
    s16 i;

    _HuWinHomeClear(window_ptr);
    if (window_ptr->sprite_id[2] == -1) {
        for (i = 0; i <= 10; i++) {
            HuSprScaleSet(window_ptr->group, 0, 1.0f, cosd(9.0f * i));
            HuPrcVSleep();
        }
        HuWinDispOff(window);
    }
    else {
        for (i = 0; i <= 15; i++) {
            if (i <= 10) {
                HuSprScaleSet(window_ptr->group, 2, 1.0f, cosd(9.0f * i));
            }
            if (i > 5) {
                s16 time = i - 5;
                HuSprScaleSet(window_ptr->group, 0, 1.0f, cosd(9.0f * time));
            }
            HuPrcVSleep();
        }
        HuWinDispOff(window);
    }
}

void HuWinExCleanup(s16 window)
{
    HuWinKill(window);
}

void HuWinExAnimPopIn(s16 window, s16 portrait)
{
    WindowData *window_ptr = &winData[window];
    s16 i;

    for (i = 0; i <= 10; i++) {
        HuSprScaleSet(window_ptr->group, 2, 1.0f, cosd(9.0f * i));
        HuPrcVSleep();
    }
    HuWinSprKill(window, 2);
    HuWinExCreatePortrait(window, portrait, 48.0f, 48.0f);
    for (i = 0; i <= 10; i++) {
        HuSprScaleSet(window_ptr->group, 2, 1.0f, sind(9.0f * i));
        HuPrcVSleep();
    }
    HuSprScaleSet(window_ptr->group, 2, 1.0f, 1.0f);
}

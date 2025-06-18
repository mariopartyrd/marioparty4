#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "dolphin.h"
#include "game/process.h"
#include "game/dvd.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define OM_DLL_MAX 20

#define OVL_DEFINE(name, path) name,

typedef enum {
    OVL_INVALID = -1,
    #include "ovl_table.h"
    OVL_COUNT
} OverlayID;

#undef OVL_DEFINE

#define OM_STAT_DELETED 0x1
#define OM_STAT_DISABLED 0x2
#define OM_STAT_ACTIVE 0x4
#define OM_STAT_PAUSED 0x10
#define OM_STAT_NOPAUSE 0x20
#define OM_STAT_MODEL_PAUSED 0x100


#define OM_GET_WORK_PTR(object, type) ((type *)(&((object)->work[0])))
#define OM_GET_DATA_PTR(object, type) ((type *)(((object)->data)))

struct om_obj_data;

typedef void (*omObjFunc)(struct om_obj_data *);

typedef struct om_ovl_his_data {
    OverlayID overlay;
    s32 event;
    s32 stat;
} omOvlHisData;

typedef struct om_obj_data {
/* 0x00 */ u16 stat;
/* 0x02 */ s16 next_idx_alloc;
/* 0x04 */ s16 prio;
/* 0x06 */ s16 prev;
/* 0x08 */ s16 next;
/* 0x0A */ s16 next_idx;
/* 0x0C */ s16 group;
/* 0x0E */ u16 group_idx;
/* 0x10 */ u32 unk10;
/* 0x14 */ omObjFunc func;
/* 0x18 */ Vec trans;
/* 0x24 */ Vec rot;
/* 0x30 */ Vec scale;
/* 0x3C */ u16 mdlcnt;
/* 0x40 */ s16 *model;
/* 0x44 */ u16 mtncnt;
/* 0x48 */ s16 *motion;
/* 0x4C */ u32 work[4];
/* 0x5C */ void *data;
} omObjData;

typedef struct om_dll_data {
	char *name;
#ifdef _WIN32
    HMODULE hModule;
#elif defined (__linux__) || defined(__APPLE__)
    void *handle;
#else
	OSModuleHeader *module;
	void *bss;
	s32 ret;
#endif

} omDllData;

void omMasterInit(s32 prio, FileListEntry *ovl_list, s32 ovl_count, OverlayID start_ovl);
void omOvlCallEx(OverlayID overlay, s16 arg2, s32 event, s32 stat);
void omOvlGotoEx(OverlayID overlay, s16 arg2, s32 event, s32 stat);
void omOvlReturnEx(s16 level, s16 arg2);
void omOvlKill(s16 arg);
void omOvlHisChg(s32 level, OverlayID overlay, s32 event, s32 stat);
omOvlHisData *omOvlHisGet(s32 level);
Process *omInitObjMan(s16 max_objs, s32 prio);
void omDestroyObjMan(void);
omObjData *omAddObjEx(Process *objman_process, s16 prio, u16 mdlcnt, u16 mtncnt, s16 group, omObjFunc func);
void omAddMember(Process *objman_process, u16 group, omObjData *object);
void omDelObjEx(Process *objman_process, omObjData *object);
void omDelMember(Process *objman_process, omObjData *object);
void omMakeGroupEx(Process *objman_process, u16 group, u16 max_objs);
omObjData **omGetGroupMemberListEx(Process *objman_process, s16 group);
void omSetStatBit(omObjData *obj, u16 stat);
void omResetStatBit(omObjData *obj, u16 stat);
void omSetTra(omObjData *obj, float x, float y, float z);
void omSetRot(omObjData *obj, float x, float y, float z);
void omSetSca(omObjData *obj, float x, float y, float z);
void omMain(void);
void omAllPause(BOOL pause);
char omPauseChk(void);
OverlayID omCurrentOvlGet(void);


void omDLLDBGOut(void);
void omDLLInit(FileListEntry *ovl_list);
s32 omDLLStart(s16 overlay, s16 flag);
void omDLLNumEnd(s16 overlay, s16 flag);
void omDLLEnd(s16 dllno, s16 flag);
omDllData *omDLLLink(omDllData **dll_ptr, s16 overlay, s16 flag);
void omDLLUnlink(omDllData *dll_ptr, s16 flag);
s32 omDLLSearch(s16 overlay);
void omDLLInfoDump(OSModuleInfo *module);
void omDLLHeaderDump(OSModuleHeader *module);

void omOutView(omObjData *object);
void omOutViewMulti(omObjData *object);
void omSystemKeyCheckSetup(Process *objman);
void omSystemKeyCheck(omObjData *object);
void omSysPauseEnable(u8 flag);
void omSysPauseCtrl(s16 flag);

extern omObjData *omDBGSysKeyObj;
extern Process *omwatchproc;
extern OverlayID omnextovl;
SHARED_SYM extern OverlayID omcurovl;
extern s32 omcurdll;
SHARED_SYM extern s32 omovlhisidx;
SHARED_SYM extern s32 omovlevtno;
extern s32 omnextovlevtno;
SHARED_SYM extern u32 omovlstat;
extern char omUPauseFlag;
SHARED_SYM extern s16 omSysExitReq;
extern s16 omdispinfo;
extern u8 omSysPauseEnableFlag;
extern OverlayID omprevovl;

extern omDllData *omDLLinfoTbl[OM_DLL_MAX];

SHARED_SYM extern Vec CRot;
SHARED_SYM extern Vec Center;
SHARED_SYM extern float CZoom;
SHARED_SYM extern Vec CRotM[16];
SHARED_SYM extern Vec CenterM[16];
SHARED_SYM extern float CZoomM[16];
SHARED_SYM extern s16 omDBGMenuButton;

#endif

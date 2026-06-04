#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "types.h"
#include "dolphin.h"
#include "game/process.h"
#include "game/dvd.h"

#define OM_DLL_MAX 20

#define DLL(name) DLL_##name,

typedef enum omOvl_e {
    DLL_NONE = -1,
    #include "ovl_table.h"
    DLL_MAX
} OMOVL;

#undef DLL

#define OM_STAT_DELETED (1 << 0)
#define OM_STAT_DISABLED (1 << 1)
#define OM_STAT_ACTIVE (1 << 2)
#define OM_STAT_PAUSED (1 << 4)
#define OM_STAT_NOPAUSE (1 << 5)
#define OM_STAT_MODELPAUSE (1 << 8)

#define OM_GRP_NONE -1

#define OM_GET_WORK_PTR(object, type) ((type *)(&((object)->work[0])))
#define OM_GET_DATA_PTR(object, type) ((type *)(((object)->data)))

// typedef HUPROCESS OMOBJMAN;
typedef struct omObj_s OMOBJ;
typedef void (*OMOBJFUNC)(OMOBJ *obj);

typedef struct omOvlHis_s {
    OMOVL ovl;
    s32 evtno;
    s32 stat;
} OMOVLHIS;

struct omObj_s {
/* 0x00 */ u16 stat;
/* 0x02 */ s16 objNext;
/* 0x04 */ s16 prio;
/* 0x06 */ s16 prev;
/* 0x08 */ s16 next;
/* 0x0A */ s16 nextNo;
/* 0x0C */ s16 grpNo;
/* 0x0E */ u16 memberNo;
/* 0x10 */ u32 mode;
/* 0x14 */ OMOBJFUNC objFunc;
/* 0x18 */ Vec trans;
/* 0x24 */ Vec rot;
/* 0x30 */ Vec scale;
/* 0x3C */ u16 mdlcnt;
/* 0x40 */ s16 *mdlId;
/* 0x44 */ u16 mtncnt;
/* 0x48 */ s16 *mtnId;
/* 0x4C */ u32 work[4];
/* 0x5C */ void *data;
};

typedef struct om_dll_data {
	char *name;
	OSModuleHeader *module;
	void *bss;
	s32 ret;
} omDllData;

void omMasterInit(s32 prio, FileListEntry *ovl_list, s32 ovl_count, OMOVL start_ovl);
void omOvlCallEx(OMOVL overlay, s16 arg2, s32 event, s32 stat);
void omOvlGotoEx(OMOVL overlay, s16 arg2, s32 event, s32 stat);
void omOvlReturnEx(s16 level, s16 arg2);
void omOvlKill(s16 arg);
void omOvlHisChg(s32 level, OMOVL overlay, s32 event, s32 stat);
OMOVLHIS *omOvlHisGet(s32 level);
HUPROCESS *omInitObjMan(s16 max_objs, s32 prio);
void omDestroyObjMan(void);
OMOBJ *omAddObjEx(HUPROCESS *objman_process, s16 prio, u16 mdlcnt, u16 mtncnt, s16 group, OMOBJFUNC func);
void omAddMember(HUPROCESS *objman_process, u16 group, OMOBJ *object);
void omDelObjEx(HUPROCESS *objman_process, OMOBJ *object);
void omDelMember(HUPROCESS *objman_process, OMOBJ *object);
void omMakeGroupEx(HUPROCESS *objman_process, u16 group, u16 max_objs);
OMOBJ **omGetGroupMemberListEx(HUPROCESS *objman_process, s16 group);
void omSetStatBit(OMOBJ *obj, u16 stat);
void omResetStatBit(OMOBJ *obj, u16 stat);
void omSetTra(OMOBJ *obj, float x, float y, float z);
void omSetRot(OMOBJ *obj, float x, float y, float z);
void omSetSca(OMOBJ *obj, float x, float y, float z);
void omMain(void);
void omAllPause(BOOL pause);
char omPauseChk(void);
OMOVL omCurrentOvlGet(void);


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

void omOutView(OMOBJ *object);
void omOutViewMulti(OMOBJ *object);
void omSystemKeyCheckSetup(HUPROCESS *objman);
void omSystemKeyCheck(OMOBJ *object);
void omSysPauseEnable(u8 flag);
void omSysPauseCtrl(s16 flag);

extern OMOBJ *omDBGSysKeyObj;
extern HUPROCESS *omwatchproc;
extern OMOVL omnextovl;
extern OMOVL omcurovl;
extern s32 omcurdll;
extern s32 omovlhisidx;
extern s32 omovlevtno;
extern s32 omnextovlevtno;
extern u32 omovlstat;
extern char omUPauseFlag;
extern s16 omSysExitReq;
extern s16 omdispinfo;
extern u8 omSysPauseEnableFlag;
extern OMOVL omprevovl;

extern omDllData *omDLLinfoTbl[OM_DLL_MAX];

extern Vec CRot;
extern Vec Center;
extern float CZoom;
extern Vec CRotM[16];
extern Vec CenterM[16];
extern float CZoomM[16];
extern s16 omDBGMenuButton;

#endif

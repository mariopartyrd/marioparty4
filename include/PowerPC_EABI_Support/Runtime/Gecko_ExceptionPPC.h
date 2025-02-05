#ifndef _RUNTIME_GECKO_EXCEPTIONPPC_H
#define _RUNTIME_GECKO_EXCEPTIONPPC_H

#include <dolphin/types.h>

typedef u8 exaction_type;

#define EXACTION_ENDBIT 0x80
#define EXACTION_MASK   0x7F

// EXAction structs

#define EXACTION_ENDOFLIST 0
#define EXACTION_BRANCH    1

typedef struct ex_branch {
	exaction_type action;
	u8 unused;
	u16 target;
} ex_branch;

#define EXACTION_DESTROYLOCAL 2

typedef struct ex_destroylocal {
	exaction_type action;
	u8 unused;
	s16 local;
	void* dtor;
} ex_destroylocal;

#define EXACTION_DESTROYLOCALCOND 3

typedef struct ex_destroylocalcond {
	exaction_type action;
	u8 dlc_field;
	s16 cond;
	s16 local;
	void* dtor;
} ex_destroylocalcond;

#define ex_destroylocalcond_MakeField(regcond) (((regcond) << 7))
#define ex_destroylocalcond_GetRegCond(field)  ((field) >> 7)

#define EXACTION_DESTROYLOCALPOINTER 4

typedef struct ex_destroylocalpointer {
	exaction_type action;
	u8 dlp_field;
	s16 pointer;
	void* dtor;
} ex_destroylocalpointer;

#define ex_destroylocalpointer_MakeField(regpointer) (((regpointer) << 7))
#define ex_destroylocalpointer_GetRegPointer(field)  ((field) >> 7)

#define EXACTION_DESTROYLOCALARRAY 5

typedef struct ex_destroylocalarray {
	exaction_type action;
	u8 unused;
	s16 localarray;
	u16 elements;
	u16 element_size;
	void* dtor;
} ex_destroylocalarray;

#define EXACTION_DESTROYBASE   6
#define EXACTION_DESTROYMEMBER 7

typedef struct ex_destroymember {
	exaction_type action;
	u8 dm_field;
	s16 objectptr;
	s32 offset;
	void* dtor;
} ex_destroymember;

#define ex_destroymember_MakeField(regpointer) (((regpointer) << 7))
#define ex_destroymember_GetRegPointer(field)  ((field) >> 7)

#define EXACTION_DESTROYMEMBERCOND 8

typedef struct ex_destroymembercond {
	exaction_type action;
	u8 dmc_field;
	s16 cond;
	s16 objectptr;
	s32 offset;
	void* dtor;
} ex_destroymembercond;

#define ex_destroymembercond_MakeField(regcond, regpointer) (((regcond) << 7) | (((regpointer)&0x1) << 6))
#define ex_destroymembercond_GetRegCond(field)              ((field) >> 7)
#define ex_destroymembercond_GetRegPointer(field)           (((field) >> 6) & 0x1)

#define EXACTION_DESTROYMEMBERARRAY 9

typedef struct ex_destroymemberarray {
	exaction_type action;
	u8 dma_field;
	s16 objectptr;
	s32 offset;
	s32 elements;
	s32 element_size;
	void* dtor;
} ex_destroymemberarray;

#define ex_destroymemberarray_MakeField(regpointer) (((regpointer) << 7))
#define ex_destroymemberarray_GetRegPointer(field)  ((field) >> 7)

#define EXACTION_DELETEPOINTER 10

typedef struct ex_deletepointer {
	exaction_type action;
	u8 dp_field;
	s16 objectptr;
	void* deletefunc;
} ex_deletepointer;

#define ex_deletepointer_MakeField(regpointer) (((regpointer) << 7))
#define ex_deletepointer_GetRegPointer(field)  ((field) >> 7)

#define EXACTION_DELETEPOINTERCOND 11

typedef struct ex_deletepointercond {
	exaction_type action;
	u8 dpc_field;
	s16 cond;
	s16 objectptr;
	void* deletefunc;
} ex_deletepointercond;

#define ex_deletepointercond_MakeField(regcond, regpointer) (((regcond) << 7) | (((regpointer)&0x1) << 6))
#define ex_deletepointercond_GetRegCond(field)              ((field) >> 7)
#define ex_deletepointercond_GetRegPointer(field)           (((field) >> 6) & 0x1)

#define EXACTION_CATCHBLOCK 12

typedef struct ex_catchblock {
	exaction_type action;
	u8 unused;
	char* catch_type;
	u16 catch_pcoffset;
	s16 cinfo_ref;
} ex_catchblock;

#define EXACTION_ACTIVECATCHBLOCK 13

typedef struct ex_activecatchblock {
	exaction_type action;
	u8 unused;
	s16 cinfo_ref;
} ex_activecatchblock;

#define EXACTION_TERMINATE 14

typedef struct ex_terminate {
	exaction_type action;
	u8 unused;
} ex_terminate;

#define EXACTION_SPECIFICATION 15

typedef struct ex_specification {
	exaction_type action;
	u8 unused;
	u16 specs;
	s32 pcoffset;
	s32 cinfo_ref;
	char* spec[];
} ex_specification;

#define EXACTION_CATCHBLOCK_32 16

typedef struct ex_catchblock_32 {
	exaction_type action;
	u8 unused;
	char* catch_type;
	s32 catch_pcoffset;
	s32 cinfo_ref;
} ex_catchblock_32;

// Other structs

typedef struct ExceptionRangeSmall {
	u16 start;
	u16 end;
	u16 action;
} ExceptionRangeSmall;

typedef struct ExceptionTableSmall {
	u16 et_field;
	ExceptionRangeSmall ranges[0];
} ExceptionTableSmall;

typedef struct ExceptionRangeLarge {
	u32 start;
	u16 size;
	u16 action;
} ExceptionRangeLarge;

typedef struct ExceptionTableLarge {
	u16 et_field;
	u16 et_field2;
	ExceptionRangeLarge ranges[];
} ExceptionTableLarge;

#define ET_MakeField(savedGPRs, savedFPRs, savedCR, hasframeptr, isLarge) \
	(((savedGPRs) << 11) | ((savedFPRs & 0x1f) << 6) | ((savedCR & 0x1) << 5) | ((hasframeptr & 0x1) << 4) | ((isLarge & 1) << 3))

#define ET_GetSavedGPRs(field)   ((field) >> 11)
#define ET_GetSavedFPRs(field)   (((field) >> 6) & 0x1f)
#define ET_GetSavedCR(field)     (((field) >> 5) & 0x1)
#define ET_GetHasFramePtr(field) (((field) >> 4) & 0x1)
#define ET_IsLargeTable(field)   (((field) >> 3) & 0x1)
#define ET_ClearLargeBit(field)  ((field) & ~(1 << 3))
#define ET_SetLargeBit(field)    ((field) | (1 << 3))

#define ET_HasElfVector(field) (((field) >> 1) & 0x1)

typedef struct ExceptionTableIndex {
	u32 functionoffset;
	u32 eti_field;
	u32 exceptionoffset;
} ExceptionTableIndex;

#define ETI_MakeField(direct, fsize) ((((s32)(direct)) << 31) | ((fsize)&0x7fffffff))
#define ETI_GetDirectStore(field)    ((field) >> 31)
#define ETI_GetFunctionSize(field)   ((field)&0x7fffffff)

#endif

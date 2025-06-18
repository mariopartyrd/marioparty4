#ifndef REL_W05_H
#define REL_W05_H

#include "dolphin/types.h"

#include "game/board/main.h"
#include "game/board/map_object.h"
#include "game/board/player.h"

// structs
typedef struct bitcopy {
    u32 unk_00;
    s8 unk_04;
} bitcopy;

typedef struct _dataCopy {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A[3];
    s16 unk_10;
    s16 unk_12;
} dataCopy;

typedef struct _dataCopy2 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    Vec unk_0C[3];
    s16 unk_30;
    s16 unk_32;
} dataCopy2;

// functions
void BoardCreate(void);
void BoardDestroy(void);
void fn_1_744(void);
void fn_1_788(void);
s32 fn_1_78C(void);
s32 fn_1_82C(void);
void fn_1_92C(void);
void fn_1_950(void);
void fn_1_954(void);
void fn_1_D4C(void);
void fn_1_D84(void);
void fn_1_E04(void);
void fn_1_E40(void);
s32 fn_1_1114(void);
s32 fn_1_1208(s16, float, float);

void fn_1_13D4(void);
void fn_1_14D0(void);
s16 fn_1_14FC(void);
void fn_1_155C(void);
void fn_1_1E44(void);

void fn_1_2B40(void);
void fn_1_2C7C(s32);
void fn_1_3044(void);
void fn_1_3430(void);
void fn_1_3514(void);
void fn_1_3D88(void);
void fn_1_3E8C(void);

void fn_1_3F74(void);
void fn_1_3FD8(void);
void fn_1_4034(s32);
void fn_1_4EB4(s32, s32, Vec *);
void fn_1_5648(void);
void fn_1_5794(s32, s32, Vec *);
void fn_1_6670(void);
omObjData *fn_1_66C0(u32, Vec *);
void fn_1_6914(omObjData *);
void fn_1_62AC(s32, Vec *);
void fn_1_64BC(void);
void fn_1_65E8(void);
void fn_1_6670(void);
omObjData *fn_1_66C0(u32, Vec *);
void fn_1_6914(omObjData *);

void fn_1_6B28(void);
void fn_1_6B7C(void);
void fn_1_7284(omObjData *);
void fn_1_72E4(void);
void fn_1_7314(void);
void fn_1_73C0(void);
void fn_1_74D0(s16[3]);
void fn_1_77B0(void);
void fn_1_78A0(omObjData *);
void fn_1_7928(omObjData *);
void fn_1_799C(void);
void fn_1_7E4C(omObjData *);
void fn_1_7E94(dataCopy *);
void fn_1_7F04(omObjData *);
void fn_1_80D8(omObjData *);
void fn_1_8410(omObjData *);
void fn_1_850C(omObjData *);
void fn_1_8668(omObjData *);
void fn_1_8798(dataCopy *, s32 *, s32 *, s32 *);
u32 fn_1_8884(void);
void fn_1_88B8(void);
void fn_1_896C(void);
void fn_1_91DC(void);
void fn_1_9268(ModelData *, ParticleData *, float[3][4]);

void fn_1_9680(void);
void fn_1_96B4(void);
void fn_1_9760(void);
void fn_1_97AC(void);
void fn_1_9A68(omObjData *);
void fn_1_9AC0(void);
void fn_1_9AF0(void);
void fn_1_9B74(void);
void fn_1_9C24(omObjData *);
void fn_1_9C98(dataCopy2 *);
void fn_1_9D0C(omObjData *);
void fn_1_9F24(omObjData *);
void fn_1_A224(omObjData *);
void fn_1_A4F8(omObjData *);
void fn_1_A5B0(omObjData *);
void fn_1_A990(omObjData *);
void fn_1_AB24(void);
void fn_1_B214(omObjData *);
void fn_1_B2B0(omObjData *, u16 *, s16 *);
void fn_1_B3C4(omObjData *);

// data
extern BoardMapObject lbl_1_data_0[7];
extern s16 lbl_1_data_118;
extern s16 lbl_1_data_11A;
extern s16 lbl_1_data_11C;
extern s16 lbl_1_data_11E;
extern s16 lbl_1_data_120;
extern s32 lbl_1_data_124[8];
extern s32 lbl_1_data_144[2];
extern s32 lbl_1_data_14C;

extern s32 lbl_1_data_150[5];
extern s16 lbl_1_data_164;
extern u32 lbl_1_data_170[4];
extern s32 lbl_1_data_180;
extern s16 lbl_1_data_184;
extern s32 lbl_1_data_188[4];
extern s32 lbl_1_data_198[2];

extern s32 lbl_1_data_1A8[3];
extern char *lbl_1_data_1C4[2];
extern s32 lbl_1_data_1CC[3];

extern char *lbl_1_data_22C[6];
extern s32 lbl_1_data_244[6];
extern Vec lbl_1_data_25C[6];
extern Vec lbl_1_data_2A4[6];
extern s32 lbl_1_data_2EC[2];
extern s32 lbl_1_data_2F4[6];

extern s32 lbl_1_data_310[2];
extern char *lbl_1_data_330[3];
extern s32 lbl_1_data_350[14];
extern s32 lbl_1_data_350[14];
extern s16 lbl_1_data_388[92];
extern float lbl_1_data_440[3];

extern char *lbl_1_data_464[3];
extern s32 lbl_1_data_470[3];
extern s32 lbl_1_data_47C[3];
extern char *lbl_1_data_494[3];
extern s16 lbl_1_data_4B2[3];
extern s32 lbl_1_data_4B8[3];

// bss
extern s16 lbl_1_bss_102[3];
extern s16 lbl_1_bss_100;
extern s16 lbl_1_bss_FE;
extern s16 lbl_1_bss_D6[20];
extern s16 lbl_1_bss_D4;
extern omObjData *lbl_1_bss_D0;
extern omObjData *lbl_1_bss_CC;
extern omObjData *lbl_1_bss_C8;
extern s16 lbl_1_bss_C6;
extern s16 lbl_1_bss_C4;
extern s16 lbl_1_bss_C2;
extern s16 lbl_1_bss_C0;
extern u32 lbl_1_bss_BC;
extern s32 lbl_1_bss_B8;

extern s16 lbl_1_bss_B6;
extern s16 lbl_1_bss_B0[3];
extern s16 lbl_1_bss_AA[3];
extern s16 lbl_1_bss_A4[3];
extern s16 lbl_1_bss_A2;
extern s16 lbl_1_bss_9E[2];
extern s16 lbl_1_bss_9C;
extern Process *lbl_1_bss_98;
extern omObjData *lbl_1_bss_94;
extern omObjData *lbl_1_bss_90;
extern omObjData *lbl_1_bss_8C;
extern s32 lbl_1_bss_88;
extern s32 lbl_1_bss_7C[3];
extern AnimData *lbl_1_bss_78;

extern s16 lbl_1_bss_72[2];
extern s16 lbl_1_bss_6C[3];
extern s32 lbl_1_bss_68;
extern s16 lbl_1_bss_64;
extern s16 lbl_1_bss_58[6];

extern s16 lbl_1_bss_4E[2];
extern s16 lbl_1_bss_4C;
extern s16 lbl_1_bss_4A;
extern s16 lbl_1_bss_48;
extern s16 lbl_1_bss_44[2];
extern Vec lbl_1_bss_38;
extern s16 lbl_1_bss_30[4];

extern s16 lbl_1_bss_28;

extern s16 lbl_1_bss_14[7];
extern s32 *lbl_1_bss_10;
extern s16 lbl_1_bss_8[4];
extern Process *lbl_1_bss_4;
extern bitcopy *lbl_1_bss_0;

#endif

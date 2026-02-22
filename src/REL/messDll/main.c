#include "REL/executor.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"

#include "dolphin.h"
#include "ext_math.h"

extern s32 sprintf(char *, const char *, s32);

static void fn_1_2BC(omObjData *arg0);
static void fn_1_300(omObjData *arg0);
static void fn_1_E88(void);
#if VERSION_PAL
static void fn_1_1174();
#endif
static s32 fn_1_11B0(s16 arg0, s16 arg1);

static Process *lbl_1_bss_34;
static omObjData *lbl_1_bss_30;
static omObjData *lbl_1_bss_2C;
static u8 lbl_1_bss_pad[0x20];
#if VERSION_PAL
static Process *lbl_1_bss_C;
#endif
static Process *lbl_1_bss_8;
#if VERSION_PAL
static s16 lbl_1_bss_4;
#else
static u8 lbl_1_bss_4_pad[4];
#endif
static s16 lbl_1_bss_2;
static s16 lbl_1_bss_0;

void ObjectSetup(void)
{
    OSReport("******* SAFObjectSetup *********\n");
    lbl_1_bss_34 = omInitObjMan(0x32, 0x2000);
    CRot.x = -20.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 120.0f;
    Center.z = 0.0f;
    CZoom = 500.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lbl_1_bss_30 = omAddObjEx(lbl_1_bss_34, 0, 0x40, 0, -1, fn_1_2BC);
    lbl_1_bss_2C = omAddObjEx(lbl_1_bss_34, 0x7FDA, 0, 0, -1, omOutView);
#if VERSION_PAL
    GWGameStat.language = 1;
#endif
    HuWinInit(1);
#if VERSION_PAL
    lbl_1_bss_C
#else
    lbl_1_bss_8
#endif
        = HuPrcChildCreate(fn_1_E88, 100, 0x3000, 0, lbl_1_bss_34);
}

static void fn_1_2BC(omObjData *arg0)
{
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    arg0->func = fn_1_300;
}

static void fn_1_300(omObjData *arg0)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    s8 temp_r31;

    if (HuPadBtnDown[0] & 0x1000) {
        GWSystem.mg_next = 1;
        omOvlReturnEx(1, 1);
        return;
    }
    CRot.x += -HuPadSubStkY[0] / 20;
    CRot.y += HuPadSubStkX[0] / 20;
    CZoom += HuPadTrigL[0] / 2;
    CZoom -= HuPadTrigR[0] / 2;
    sp2C.x = Center.x + CZoom * (sind(CRot.y) * cosd(CRot.x));
    sp2C.y = Center.y + CZoom * -sind(CRot.x);
    sp2C.z = Center.z + CZoom * (cosd(CRot.y) * cosd(CRot.x));
    sp20.x = Center.x - sp2C.x;
    sp20.y = Center.y - sp2C.y;
    sp20.z = Center.z - sp2C.z;
    sp14.x = sind(CRot.y) * sind(CRot.x);
    sp14.y = cosd(CRot.x);
    sp14.z = cosd(CRot.y) * sind(CRot.x);
    temp_f31 = CRot.z;
    sp8.x = sp14.x * (sp20.x * sp20.x + (1.0f - sp20.x * sp20.x) * cosd(temp_f31))
        + sp14.y * (sp20.x * sp20.y * (1.0 - cosd(temp_f31)) - sp20.z * sind(temp_f31))
        + sp14.z * (sp20.x * sp20.z * (1.0 - cosd(temp_f31)) + sp20.y * sind(temp_f31));
    sp8.y = sp14.x * (sp20.x * sp20.y * (1.0 - cosd(temp_f31)) + sp20.z * sind(temp_f31))
        + sp14.y * (sp20.y * sp20.y + (1.0f - sp20.y * sp20.y) * cosd(temp_f31))
        + sp14.z * (sp20.y * sp20.z * (1.0 - cosd(temp_f31)) - sp20.x * sind(temp_f31));
    sp8.z = sp14.x * (sp20.x * sp20.z * (1.0 - cosd(temp_f31)) - sp20.y * sind(temp_f31))
        + sp14.y * (sp20.y * sp20.z * (1.0 - cosd(temp_f31)) + sp20.x * sind(temp_f31))
        + sp14.z * (sp20.z * sp20.z + (1.0f - sp20.z * sp20.z) * cosd(temp_f31));
    VECCrossProduct(&sp14, &sp20, &sp20);
    VECNormalize(&sp20, &sp20);
    temp_r31 = HuPadSubStkX[0] & 0xF8;
    if (temp_r31 != 0) {
        Center.x += sp20.x * temp_r31 * 0.05f;
        Center.y += sp20.y * temp_r31 * 0.05f;
        Center.z += sp20.z * temp_r31 * 0.05f;
    }
    VECNormalize(&sp8, &sp20);
    temp_r31 = -(HuPadSubStkY[0] & 0xF8);
    if (temp_r31 != 0) {
        Center.x += sp20.x * temp_r31 * 0.05f;
        Center.y += sp20.y * temp_r31 * 0.05f;
        Center.z += sp20.z * temp_r31 * 0.05f;
    }
}

static char *lbl_1_data_32C[]
    = { "001_Character_Name_ss", "002_Hidden_Block", "003_Battle_M", "004_Bowser_M", "005_Warp_M", "006_Mushroom_M", "007_Lot_house", "008_Boo_house",
          "009_ItemName", "010_Bord", "011_RoundItem", "012_Spaceamida", "013_Star_M", "014_RollerCoaster", "015_Last5", "016_ItemShop", "017_System",
          "018_ModeSelect", "019_Item", "020_Map2_event", "021_Lucky_Minigame", "022_Bord_Start", "023_Map3_event", "024_Minigame_Name", "025_mg_446",
          "026_debugmes", "027_Party_Mode", "028_SETUP", "029_Miracle", "030_mg_kuppa", "031_Story_Mode", "032_Bowser_Story", "033_Map4_event",
          "034_mg_inst", "035_E3_only", "036_saf", "037_Mg_inst_sys_", "038_Bord_Results", "039_Bord_Results2", "040_Map5_event", "041_Mg_Mode",
          "042_mg_445", "043_mg_447", "044_mg_448", "045_mg_449", "046_mg_450", "047_tutorial", "048_Option_Rooml", "049_Map6_event", "050_charley",
          "051_Present_Room", "052_Extra_Room", "053_Staff_Post", "054_Staff_Name", "055_Opening_Demo", "056_mgex_inst", NULL };

#if VERSION_PAL
char *lbl_1_data_438[] = {
    "ENGLISH", "GERMANY", "FRENCH", "ITALY", "SPANISH"
};
#endif

static s16 lbl_1_data_410 = -1;

static void fn_1_E88(void)
{
    s16 sp10[256]; // unknown size
    char spC[4];
    char sp8[4];
    s16 temp_r3;
    s16 var_r25;
    s16 var_r27;
#if VERSION_PAL
    s16 var_r26 = 0;
#endif
    s16 var_r28;
    s32 var_r30;
    s32 var_r31;
    s32 temp_r3_2;
    char *var_r29;

    var_r28 = var_r27 = 0;
    while (lbl_1_data_32C[var_r28] != 0) {
        var_r29 = lbl_1_data_32C[var_r28];
        while (*var_r29 != 0) {
            if (*var_r29 == '_') {
                *var_r29 = 0x86;
            }
            var_r29++;
        }
        sp10[var_r28] = 0;
        var_r30 = (var_r28 << 16);
        var_r25 = 0;
        while (1) {
            if ((s32)MessData_MesPtrGet(messDataPtr, var_r30 + var_r25) == 0) {
                break;
            }
            sp10[var_r28]++;
            var_r25++;
        }
        var_r27++;
        var_r28++;
    }
#if VERSION_NTSC
    temp_r3 = HuWinExCreateStyled(-10000.0f, 32.0f, 316, 40, -1, 0);
    HuWinExAnimIn(temp_r3);
    HuWinAttrSet(temp_r3, 0x800);
    HuWinMesSpeedSet(temp_r3, 0);
    HuWinMesSet(temp_r3, MAKE_MESSID_PTR(lbl_1_data_32C[0]));
    lbl_1_bss_0 = HuWinCreate(460.0f, 32.0f, 100, 40, 0);
    HuWinAttrSet(lbl_1_bss_0, 0x800);
    HuWinMesSpeedSet(lbl_1_bss_0, 0);
    HuWinMesSet(lbl_1_bss_0, MAKE_MESSID_PTR("\x1F\x01_\x1F\x02"));
#else
    MAKE_MESSID_PTR("\x1F\x01_\x1F\x02");
    fn_1_1174();
    HuWinMesSet(lbl_1_bss_0, (u32)lbl_1_data_438[0]);
#endif
    var_r31 = 0;
    var_r30 = 0;
    while (1) {
#if VERSION_PAL
#define _WINDOW lbl_1_bss_2
#else
#define _WINDOW lbl_1_bss_0
#endif
        HuWinHomeClear(_WINDOW);
        sprintf(spC, "%03d", var_r30 + 1);
        HuWinInsertMesSet(_WINDOW, MAKE_MESSID_PTR(spC), 0);
        sprintf(sp8, "%03d", sp10[var_r31]);
        HuWinInsertMesSet(_WINDOW, MAKE_MESSID_PTR(sp8), 1);
        HuWinMesSet(_WINDOW, MAKE_MESSID_PTR("\x1F\x01_\x1F\x02"));
        temp_r3_2 = fn_1_11B0(var_r31, var_r30);
#undef _WINDOW
#if VERSION_PAL
        if (temp_r3_2 & 0x400) {
            HuWinAllKill();
            HuPrcVSleep();
            var_r26++;
            if (var_r26 >= 5) {
                var_r26 = 0;
            }
            GWGameStat.language = var_r26 + 1;
            HuWinInit(1);
            HuPrcVSleep();
            fn_1_1174();
            HuWinMesSet(lbl_1_bss_0, (u32)lbl_1_data_438[var_r26]);
        }
        else
#endif
        if (temp_r3_2 & 0x20) {
            var_r31++;
            if (var_r31 >= var_r27) {
                var_r31 = 0;
            }
            var_r30 = 0;
        }
        else if (temp_r3_2 & 0x40) {
            var_r31--;
            if (var_r31 < 0) {
                var_r31 = var_r27 - 1;
            }
            var_r30 = 0;
        }
        else if (temp_r3_2 & 0x200) {
            var_r30--;
            if (var_r30 < 0) {
                var_r31--;
                if (var_r31 < 0) {
                    var_r31 = var_r27 - 1;
                }
                var_r30 = sp10[var_r31] - 1;
            }
        }
        else {
            var_r30++;
            if (var_r30 >= sp10[var_r31]) {
                var_r31++;
                if (var_r31 >= var_r27) {
                    var_r31 = 0;
                }
                var_r30 = 0;
            }
        }
        HuPrcVSleep();
    }
}

static char *lbl_1_data_440[] = { "]1^", "]2^", "]3^", "]4^", "]5^", "]6^", "]7^", "]8^" };

#if VERSION_PAL
static void fn_1_1174()
{
    lbl_1_bss_4 = HuWinExCreateStyled(-10000.0f, 32.0f, 316, 40, -1, 0);
    HuWinExAnimIn(lbl_1_bss_4);
    HuWinAttrSet(lbl_1_bss_4, 0x800);
    HuWinMesSpeedSet(lbl_1_bss_4, 0x0);
    
    lbl_1_bss_2 = HuWinCreate(460.0f, 32.0f, 100, 40, 0);
    HuWinAttrSet(lbl_1_bss_2, 0x800);
    HuWinMesSpeedSet(lbl_1_bss_2, 0x0);

    lbl_1_bss_0 = HuWinExCreateStyled(16.0f, 32.0f, 100, 40, -1, 0);
    HuWinExAnimIn(lbl_1_bss_0);
    HuWinAttrSet(lbl_1_bss_0, 0x800);
    HuWinMesSpeedSet(lbl_1_bss_0, 0x0);
}
#endif

static s32 fn_1_11B0(s16 arg0, s16 arg1)
{
    WindowData *temp_r30;
    float spC[2];
    s32 temp_r28;
    s32 var_r27;
    s32 var_r26;
    u8 *var_r29;
    s16 i;

    var_r27 = 0;
    var_r26 = 0;
#if VERSION_PAL
    HuWinHomeClear(lbl_1_bss_4);
    HuWinMesSet(lbl_1_bss_4, MAKE_MESSID_PTR(lbl_1_data_32C[arg0]));
#else
    HuWinHomeClear(lbl_1_bss_2);
    HuWinMesSet(lbl_1_bss_2, MAKE_MESSID_PTR(lbl_1_data_32C[arg0]));
#endif
    HuPrcVSleep();
    if (lbl_1_data_410 != -1) {
        HuWinKill(lbl_1_data_410);
    }
    temp_r28 = MAKE_MESSID(arg0, arg1);
    for (i = 0; i < 8; i++) {
        HuWinInsertMesSizeGet(MAKE_MESSID_PTR(lbl_1_data_440[i]), (s16)i);
    }
    HuWinMesMaxSizeGet(1, &spC[0], temp_r28);
    if (spC[0] <= 16.0f) {
        spC[0] = 32.0f;
    }
    lbl_1_data_410 = HuWinCreate(-10000.0f, -10000.0f, spC[0], spC[1], (VERSION_PAL) ? 1 : 0);
#if VERSION_PAL
    HuWinMesPalSet(lbl_1_data_410, 7, 0, 0, 0);
#endif
    for (i = 0; i < 8; i++) {
        HuWinInsertMesSet(lbl_1_data_410, MAKE_MESSID_PTR(lbl_1_data_440[i]), (s16)i);
    }
    temp_r30 = &winData[lbl_1_data_410];
    temp_r30->push_key |= (VERSION_PAL) ? 0x760 : 0x360;
    temp_r30->key_auto = (VERSION_PAL) ? 0x460 : 0x60;
    HuWinMesSet(lbl_1_data_410, temp_r28);
    var_r29 = MessData_MesPtrGet(messDataPtr, temp_r28);
    while (*var_r29 != 0) {
        if (*var_r29 == 0xF) {
            var_r27 = 1;
        }

#if VERSION_PAL
        if (*var_r29 == 0xFF) {
#else
        if (*var_r29 == 0) {
#endif
            var_r26 = 1;
        }
        var_r29++;
    }
    if (var_r27 != 0) {
        HuWinMesWait(lbl_1_data_410);
        HuWinChoiceGet(lbl_1_data_410, 0);
        return temp_r30->key_down;
    }
    if (var_r26 == 0) {
        while (!(HuPadBtnRep[0] & ((VERSION_PAL) ? 0x760 : 0x360))) {
            HuPrcVSleep();
        }
        return HuPadBtnRep[0];
    }
    while (temp_r30->stat != 0) {
        if (HuPadBtnRep[0] & ((VERSION_PAL) ? 0x460 : 0x60)) {
            return HuPadBtnDown[0];
        }
        HuPrcVSleep();
    }
    return temp_r30->key_down;
}

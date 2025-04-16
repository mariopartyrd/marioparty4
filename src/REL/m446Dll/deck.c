#include "REL/m446Dll.h"

#include "game/audio.h"
#include "ext_math.h"

// bss
u32 lbl_1_bss_20;

// data
static const s32 lbl_1_rodata_D0[5][2] = {
    {1, 5}, {0, 5}, {2, 5}, {3, 5}, {4, 3}
};

unkStruct5* fn_1_3064(void) {
    unkStruct4* var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    unkStruct5* temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkStruct5), MEMORY_DEFAULT_NUM);
    if (!temp_r3) {
        return NULL;
    }
    temp_r3->unk0 = fn_1_1C64(0x17);
    if (!temp_r3->unk0) {
        HuMemDirectFree(temp_r3);
        return NULL;
    }
    temp_r3->unk4.x = 0.0f;
    temp_r3->unk4.y = 85.0f;
    temp_r3->unk4.z = 0.0f;
    
    for (var_r28 = 0, var_r30 = 0; var_r30 < 5; var_r30++) {
        for (var_r29 = 0; var_r29 < lbl_1_rodata_D0[var_r30][1]; var_r29++, var_r28++) {
            var_r27 = m446CardCreate(lbl_1_rodata_D0[var_r30][0]);
            m446DeckPushCard(temp_r3, var_r27, 0);
        }
    }
    return temp_r3;
}

void fn_1_3180(unkStruct2** arg0) {
    unkStruct4* sp8;

    while (fn_1_1D6C(*arg0, &sp8) != 0) {
        fn_1_2688(sp8);
    }
    fn_1_1CF8(*arg0);
    HuMemDirectFree(arg0);
}

void fn_1_31D8(unkStruct2** arg0, unkStruct4** arg1, s32* arg2, s32 arg3) {
    Vec sp10;
    unkStruct4 *spC;
    f32 var_f30;
    f32 var_f31;
    s32 var_r29;
    s32 var_r31;
    
    HuAudFXPlay(0x765);
    var_f30 = 360.0f / fn_1_1DEC(*arg0);
    if (fn_1_38F0() % 2 != 0) {
        var_f30 = -var_f30;
    }
    
    var_f31 = fn_1_38F0() % 360;
    var_r29 = 0;
    var_r31 = 0;
    while (fn_1_1D6C(*arg0, &spC) != 0) {
        if (arg3 != 0) {
            sp10 = spC->unk10;
            sp10.x = ((25.0 * cosd(var_f31)) - (25.0 * sind(var_f31)));
            sp10.z = ((25.0 * cosd(var_f31)) + (25.0 * sind(var_f31)));
            sp10.y = 81.0f + (0.1f * var_r31);
            fn_1_2890(spC, &sp10, 0x12, var_r29 += 3);
            var_f31 += var_f30;
        }
        arg1[var_r31++] = spC;
    }
    *arg2 = var_r31;
}

void fn_1_34A0(unkStruct5* arg0, unkStruct4** arg1, s32 arg2, s32 arg3) {
    Vec sp10;
    unkStruct4* spC;
    s32 temp_r30;
    s32 var_r22;
    s32 var_r25;
    s32 var_r24;
    s32 temp_r23;
    unkStruct2* temp_r28;
    s32 var_r27;

    temp_r23 = arg2;
    HuAudFXPlay(0x766);
    temp_r28 = fn_1_1C64(6);
    var_r27 = 0;
    do {
        
        do {
        temp_r30 = fn_1_38F0() % temp_r23;
        spC = arg1[temp_r30];
        } while (!spC);
        
        if (spC->unk0 != 4) {
            if ((var_r27 % 3) == 0) {
                var_r25 = spC->unk0;
            } else if ((var_r27 % 3) == 1) {
                var_r22 = spC->unk0;
                if (spC->unk0 == var_r25) {
                    continue;
                }
            } else if ((spC->unk0 == var_r25) || (spC->unk0 == var_r22)) continue;
            arg1[temp_r30] = NULL;
            fn_1_1D30(temp_r28, spC);
            var_r27++;
        }
    } while (fn_1_1DEC(temp_r28) < 6);
    var_r24 = 0;
    do {
        if (arg2 > 6) {
            do {
                temp_r30 = fn_1_38F0() % temp_r23;
                spC = arg1[temp_r30];
            } while (!spC);
            arg1[temp_r30] = NULL;
        } else {
            fn_1_1D6C(temp_r28, &spC);
        }
        fn_1_1D30(arg0->unk0, spC);
        sp10 = arg0->unk4;
        sp10.y += 0.5f * fn_1_1DEC(arg0->unk0);
        if (arg3 != 0) {
            fn_1_2890(spC, &sp10, 0x12, var_r24 += 3);
        } else {
            spC->unk10 = sp10;
        }
        arg2--;
    } while (arg2 != 0);
    fn_1_1CF8(temp_r28);
}

s32 m446DeckPushCard(unkStruct5* arg0, unkStruct4* arg1, s32 arg2) {
    Vec sp18;
    Vec spC;
    
    if (fn_1_1D30(arg0->unk0, arg1) == 0) {
        OSReport("[!] m446DeckPushCard ERROR...\n");
        return 0;
    }
    sp18 = arg0->unk4;
    sp18.y += 0.5f * fn_1_1DEC(arg0->unk0);
    spC = arg1->unk34;
    spC.y = 0.0f;
    switch (arg2) {
        case 2:
            fn_1_27FC(arg1, &sp18, 0x3C);
            fn_1_2928(arg1, &spC, 0x3C);
            break;
        default:
            arg1->unk10 = sp18;
            arg1->unk34 = spC;
    }
    return 1;
}

s32 m446DeckPopCard(unkStruct2** arg0, unkStruct4** arg1) {
    if (fn_1_1D6C(*arg0, arg1) == 0) {
        OSReport("[!] m446DeckPopCard ERROR...\n");
        return 0;
    } else {
        return 1;
    }
}

void fn_1_38B0(unkStruct2** arg0) {
    fn_1_1DEC(*arg0);
}

void fn_1_38E0(u32 arg0) {
    lbl_1_bss_20 = arg0;
}

s32 fn_1_38F0(void) {
    return ((lbl_1_bss_20 = (lbl_1_bss_20 * 0x41C64E6D) + 0x3039) >> 16) % 32768;
}

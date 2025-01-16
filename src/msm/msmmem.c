#include "msm/msmmem.h"

typedef struct _unkStruct {
    struct _unkStruct* prev;
    struct _unkStruct* next;
    u32 unk8;
    u32 unkC;
    void* unk10;
    void* unk14;
    char unk18[0x8];
} unkStruct;

typedef struct _unkMemStruct {
    unkStruct* unk0;
    u32 unk4;
    unkStruct* unk8;
    unkStruct unkC;
} unkMemStruct;

static unkMemStruct mem;

void msmMemFree(void* arg0) {
    unkStruct* temp_r6;
    unkStruct* temp_r7;
    unkStruct* temp_r8;
    unkStruct* temp_r5;
    unkStruct* temp;
    
    temp = arg0;

    temp_r6 = &temp[-1];
    temp_r7 = temp_r6->prev;
    temp_r8 = temp_r6->next;
    if (mem.unk0 > temp_r6 || ((u32)mem.unk0 + (u32)mem.unk4) <= (u32)temp_r6) {
        return;
    }

    if ((temp_r7->next != temp_r6) || (temp_r6->unk10 != arg0) || (temp_r8 && (temp_r8->prev != temp_r6))) {
        return;
    }
    
    temp_r7->unkC += temp_r6->unk8 + temp_r6->unkC;
    temp_r7->next = temp_r8;
    temp_r5 = mem.unk8;
    if ((temp_r5 == temp_r6) || (temp_r5->unkC < temp_r7->unkC)) {
        mem.unk8 = temp_r7;
    }
    if (temp_r8) {
        temp_r8->prev = temp_r7;
        if (mem.unk8->unkC < temp_r8->unkC) {
            mem.unk8 = temp_r8;
        }
    }
}

void* msmMemAlloc(u32 arg0) {
    s32 temp_r0;
    u32 var_r5;
    u32 var_r7;
    unkStruct* temp_r5;
    unkStruct* var_r8;
    unkStruct* temp_r9;

    var_r7 = arg0 + 0x20;
    temp_r0 = var_r7 & 0x1F;
    if (temp_r0 != 0) {
        var_r7 += 0x20 - temp_r0;
    }
    if (mem.unk8->unkC >= var_r7) {
        var_r8 = mem.unk8;
    } else {
        var_r8 = &mem.unkC;
        
       do {
            if (var_r8->unkC >= var_r7) break;
            var_r8 = var_r8->next;
        } while (var_r8);
        if (!var_r8) {
            return NULL;
        }
    }
    
    var_r5 = var_r8->unk8;
    if (var_r5 != 0) {
        var_r5 -= 0x20;
    }
    temp_r5 = (void*)((u32)var_r8->unk10 + (var_r5));
    temp_r9 = var_r8->next;
    if ((mem.unk0 > temp_r5) || ((void*)((u32)mem.unk0 + (u32)mem.unk4) <= temp_r5)) {
        return NULL;
    }
    temp_r5->unk8 = var_r7;
    temp_r5->unkC = var_r8->unkC - var_r7;
    temp_r5->unk10 = (temp_r5 + 1);
    temp_r5->prev = var_r8;
    temp_r5->next = temp_r9;
    mem.unk8 = temp_r5;
    var_r8->unkC = 0;
    var_r8->next = temp_r5;
    if (temp_r9) {
        temp_r9->prev = temp_r5;
        if (mem.unk8->unkC < temp_r9->unkC) {
            mem.unk8 = temp_r9;
        }
    }
    return temp_r5->unk10;
}

void msmMemInit(void* arg0, u32 arg1) {
    unkStruct* temp_r7;
    s32 temp;

    temp = (s32)arg0 & 0x1F;
    switch (temp) {
        default:
            temp = 0x20 - temp;
            break;
        case 0:
            temp = 0;
            break;
    }
    
    mem.unk0 = (void*)((s32)arg0 + temp);
    temp = (s32)arg0 + arg1;
    mem.unk4 = ((temp - (s32)mem.unk0) & ~0x1F);
    temp_r7 = &mem.unkC;
    temp_r7->unk8 = 0;
    temp_r7->unkC = mem.unk4;
    temp_r7->unk10 = mem.unk0;
    temp_r7->prev = NULL;
    temp_r7->next = NULL;
    mem.unk8 = &mem.unkC;
}

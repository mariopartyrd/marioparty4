#include "game/esprite.h"
#include "game/data.h"
#include "game/sprite.h"

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ ANIMDATA *unk08;
} UnkEspriteStruct01; // Size 0xC

s16 esprite[0x180][2];
UnkEspriteStruct01 espanim[0x180];

static s16 gid;

void espInit(void) {
    s32 i;

    gid = HuSprGrpCreate(0x180);
    for (i = 0; i < 0x180; i++) {
        esprite[i][0] = i;
        esprite[i][1] = -1;
    }
    for (i = 0; i < 0x180; i++) {
        espanim[i].unk04 = 0;
    }
}

s16 espEntry(s32 arg0, s16 arg1, s16 arg2) {
    UnkEspriteStruct01 *var_r30;
    UnkEspriteStruct01 *var_r31;
    s16 (*var_r29)[2];
    void *temp_r26;
    s16 temp_r25;
    s16 var_r28;
    s32 var_r27;

    var_r29 = esprite;
    for (var_r28 = 0; var_r28 < 0x180; var_r29++, var_r28++) {
        if (var_r29[0][1] == -1) {
            break;
        }
    }
    if (var_r28 == 0x180) {
        return -1;
    }
    var_r31 = espanim;
    var_r30 = NULL;
    for (var_r27 = 0; var_r27 < 0x180; var_r31++, var_r27++) {
        if (var_r31->unk04 != 0) {
            if (var_r31->unk00 == arg0) {
                var_r30 = NULL;
                break;
            }
        } else if (var_r30 == NULL) {
            var_r30 = var_r31;
        }
    }
    if (var_r27 == 0x180) {
        if (var_r30 == NULL) {
            return -1;
        }
        temp_r26 = HuDataSelHeapReadNum(arg0, MEMORY_DEFAULT_NUM, HEAP_DATA);
        if (temp_r26 == NULL) {
            return -1;
        }
        var_r30->unk00 = arg0;
        var_r30->unk08 = HuSprAnimRead(temp_r26);
        var_r31 = var_r30;
    }
    temp_r25 = HuSprCreate(var_r31->unk08, arg1, arg2);
    if (temp_r25 == -1) {
        if (var_r30 != NULL) {
            HuSprAnimKill(var_r31->unk08);
        }
        return -1;
    }
    var_r31->unk04++;
    var_r29[0][1] = var_r31 - espanim;
    HuSprGrpMemberSet(gid, var_r29[0][0], temp_r25);
    return var_r28;
}

void espKill(s16 arg0) {
    HuSprGrpMemberKill(gid, esprite[arg0][0]);
    espanim[esprite[arg0][1]].unk04--;
    esprite[arg0][1] = -1;
}

s16 espGrpIDGet(void) {
    return gid;
}

void espDispOn(s16 arg0) {
    HuSprAttrReset(gid, esprite[arg0][0], 4);
}

void espDispOff(s16 arg0) {
    HuSprAttrSet(gid, esprite[arg0][0], 4);
}

void espAttrSet(s16 arg0, u16 arg1) {
    HuSprAttrSet(gid, esprite[arg0][0], arg1);
}

void espAttrReset(s16 arg0, u16 arg1) {
    HuSprAttrReset(gid, esprite[arg0][0], arg1);
}

void espPosSet(s16 arg0, float arg1, float arg2) {
    HuSprPosSet(gid, esprite[arg0][0], arg1, arg2);
}

void espScaleSet(s16 arg0, float arg1, float arg2) {
    HuSprScaleSet(gid, esprite[arg0][0], arg1, arg2);
}

void espZRotSet(s16 arg0, float arg1) {
    HuSprZRotSet(gid, esprite[arg0][0], arg1);
}

void espTPLvlSet(s16 arg0, float arg1) {
    HuSprTPLvlSet(gid, esprite[arg0][0], arg1);
}

void espColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    HuSprColorSet(gid, esprite[arg0][0], arg1, arg2, arg3);
}

void espSpeedSet(s16 arg0, float arg1) {
    HuSprSpeedSet(gid, esprite[arg0][0], arg1);
}

void espBankSet(s16 arg0, s16 arg1) {
    HuSprBankSet(gid, esprite[arg0][0], arg1);
}

void espDrawNoSet(s16 arg0, s16 arg1) {
    HuSprDrawNoSet(gid, esprite[arg0][0], arg1);
}

void espPriSet(s16 arg0, s16 arg1) {
    HuSprPriSet(gid, esprite[arg0][0], arg1);
}

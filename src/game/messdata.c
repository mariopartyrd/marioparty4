#include "dolphin.h"

#include <port/byteswap.h>

static void *MessData_MesDataGet(void *messdata, u32 id)
{
    s32 i;
    s32 max_bank;
    u16 *banks;
    u16 bank;
    s32 *data;
#ifdef TARGET_PC
    s32 ofs;
    u16 bank_pc;
#endif
    bank = id >> 16;
    data = messdata;
    max_bank = *data;
#ifdef TARGET_PC
    byteswap_s32(&max_bank);
#endif
    data++;
#ifdef TARGET_PC
    ofs = *data;
    byteswap_s32(&ofs);
    banks = (u16 *)(((u8 *)messdata) + ofs);
#else
    banks = (u16 *)(((u8 *)messdata)+(*data));
#endif
    for(i = max_bank; i != 0; i--, banks += 2) {
#ifdef TARGET_PC
        bank_pc = *banks;
        byteswap_u16(&bank_pc);
        if(bank_pc == bank) {
            break;
        }
#else
        if(*banks == bank) {
            break;
        }
#endif
    }
    if (i == 0) {
        return NULL;
    }
#ifdef TARGET_PC
    bank_pc = banks[1];
    byteswap_u16(&bank_pc);
    ofs = data[bank_pc];
    byteswap_s32(&ofs);
    return (((u8 *)messdata) + ofs);
#else
    data += banks[1];
    return (((u8 *)messdata) + (*data));
#endif
}

static void *_MessData_MesPtrGet(void *messbank, u32 id)
{
    u16 index;
    s32 max_index;
    s32 *data;
#ifdef TARGET_PC
    s32 ofs;
#endif

    index = id & 0xFFFF;
    data = messbank;
    max_index = *data;
#if TARGET_PC
    byteswap_s32(&max_index);
#endif
    data++;
    if(max_index <= index) {
        return NULL;
    } else {
        data =  data+index;
#ifdef TARGET_PC
        ofs = *data;
        byteswap_s32(&ofs);
        return (((u8 *)messbank)+(ofs));
#else
        return (((u8 *)messbank)+(*data));
#endif
    }
}

void *MessData_MesPtrGet(void *messdata, u32 id)
{
    void *bank = MessData_MesDataGet(messdata, id);
    if(bank) {
        return _MessData_MesPtrGet(bank, id);
    }
    return NULL;
}
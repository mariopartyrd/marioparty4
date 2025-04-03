#include "game/gamework_data.h"

#ifdef TARGET_PC
#include "string.h"
#endif

static u8 _Sys_Flag[16];

static u8 *GetFlagPtr(u32 flag)
{
	u8 *ret;
	u32 group = flag >> 16;
	if((flag & 0xFFFF0000) == 0x30000) {
		ret = _Sys_Flag;
	} else {
		ret = &GWSystem.flag[group][0];
	}
	return ret;
}

s32 _CheckFlag(u32 flag)
{
	u8 *flag_ptr = GetFlagPtr(flag);
	u16 index = flag;
	return flag_ptr[index/8] & (1 << (index % 8));
}

void _SetFlag(u32 flag)
{
	u8 *flag_ptr = GetFlagPtr(flag);
	u16 index = flag;
	flag_ptr[index/8] |= (1 << (index % 8));
}

void _ClearFlag(u32 flag)
{
	u8 *flag_ptr = GetFlagPtr(flag);
	u16 index = flag;
	flag_ptr[index/8] &= ~(1 << (index % 8));
}

void _InitFlag(void)
{
	memset(_Sys_Flag, 0, sizeof(_Sys_Flag));
}

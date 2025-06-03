#include "dolphin.h"
#include "game/gamework_data.h"

// Used to store system flags. There are 128 bits available for system flags.
// Though Mario Party 4 seems to only use the first bit to toggle read/write 
// access to the memory card.
static u8 _Sys_Flag[16];

/**
 * @brief Gets the pointer to the flag array.
 * 
 * @details The available flag options are system flags (0x30000-0x3FFFF) and 
 * game flags (0x00000-0xFFFFF). 
 * 
 * Game flags are stored in the GWSystem.flag array.
 * The GWSystem variable is a global variable that is defined in gamework.c.
 * GWSystem flags are a 2D array of 3 groups of 16 flags each for a total of 48 
 * flags.
 * 
 * TODOC: A comprehensive list of all the flags and their meanings
 * 
 * @param flag Address of the flag to get.
 * @return u8* Pointer to the flag array.
 */
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

/**
 * @brief Checks the value of a flag.
 * 
 * @param flag Address of the flag to check.
 * @return s32 Value of the flag.
 */
s32 _CheckFlag(u32 flag)
{
	u8 *flag_ptr = GetFlagPtr(flag);
	u16 index = flag;
	return flag_ptr[index/8] & (1 << (index % 8));
}

/**
 * @brief Sets the value of a flag. Setting the bit to 1.
 * 
 * @param flag Address of the flag to set.
 */
void _SetFlag(u32 flag)
{
	u8 *flag_ptr = GetFlagPtr(flag);
	u16 index = flag;
	flag_ptr[index/8] |= (1 << (index % 8));
}

/**
 * @brief Clears the value of a flag. Setting the bit to 0.
 * 
 * @param flag Address of the flag to clear.
 */
void _ClearFlag(u32 flag)
{
	u8 *flag_ptr = GetFlagPtr(flag);
	u16 index = flag;
	flag_ptr[index/8] &= ~(1 << (index % 8));
}

/**
 * @brief Initializes the system flag array.
 * 
 * @details This flag array is used to store various system flags that are
 * used when interacting with the console. Also known as temporary flags.
 */
void _InitFlag(void)
{
	memset(_Sys_Flag, 0, sizeof(_Sys_Flag));
}
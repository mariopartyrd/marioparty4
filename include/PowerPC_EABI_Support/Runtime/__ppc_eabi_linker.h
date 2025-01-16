#ifndef __PPC_EABI_LINKER
#define __PPC_EABI_LINKER

__declspec(section ".init") extern char _stack_addr[];
__declspec(section ".init") extern char _stack_end[];
__declspec(section ".init") extern char _heap_addr[];
__declspec(section ".init") extern char _heap_end[];
__declspec(section ".init") extern const char _fextabindex_rom[];
__declspec(section ".init") extern char _fextabindex[];
__declspec(section ".init") extern char _eextabindex[];

__declspec(section ".init") extern char _SDA_BASE_[];

__declspec(section ".init") extern char _SDA2_BASE_[];

typedef struct __rom_copy_info {
	char* rom;
	char* addr;
	unsigned int size;
} __rom_copy_info;

__declspec(section ".init") extern __rom_copy_info _rom_copy_info[];

typedef struct __bss_init_info {
	char* addr;
	unsigned int size;
} __bss_init_info;

__declspec(section ".init") extern __bss_init_info _bss_init_info[];

typedef struct __eti_init_info {
	void* eti_start;
	void* eti_end;
	void* code_start;
	unsigned long code_size;
} __eti_init_info;

__declspec(section ".init") extern __eti_init_info _eti_init_info[];
__declspec(section ".init") extern const char _f_init_rom[];
__declspec(section ".init") extern char _f_init[];
__declspec(section ".init") extern char _e_init[];
__declspec(section ".init") extern const char _f_text_rom[];
__declspec(section ".init") extern char _f_text[];
__declspec(section ".init") extern char _e_text[];
__declspec(section ".init") extern const char _f_rodata_rom[];
__declspec(section ".init") extern char _f_rodata[];
__declspec(section ".init") extern char _e_rodata[];
__declspec(section ".init") extern const char _fextab_rom[];
__declspec(section ".init") extern char _fextab[];
__declspec(section ".init") extern char _eextab[];
__declspec(section ".init") extern const char _f_data_rom[];
__declspec(section ".init") extern char _f_data[];
__declspec(section ".init") extern char _e_data[];
__declspec(section ".init") extern char _f_bss[];
__declspec(section ".init") extern char _e_bss[];
__declspec(section ".init") extern const char _f_sdata_rom[];
__declspec(section ".init") extern char _f_sdata[];
__declspec(section ".init") extern char _e_sdata[];
__declspec(section ".init") extern char _f_sbss[];
__declspec(section ".init") extern char _e_sbss[];
__declspec(section ".init") extern const char _f_sdata2_rom[];
__declspec(section ".init") extern char _f_sdata2[];
__declspec(section ".init") extern char _e_sdata2[];
__declspec(section ".init") extern char _f_sbss2[];
__declspec(section ".init") extern char _e_sbss2[];
__declspec(section ".init") extern const char _f_PPC_EMB_sdata0_rom[];
__declspec(section ".init") extern char _f_PPC_EMB_sdata0[];
__declspec(section ".init") extern char _e_PPC_EMB_sdata0[];
__declspec(section ".init") extern char _f_PPC_EMB_sbss0[];
__declspec(section ".init") extern char _e_PPC_EMB_sbss0[];

#endif // __PPC_EABI_LINKER

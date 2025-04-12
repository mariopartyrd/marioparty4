#include "game/object.h"
#include "game/dvd.h"
#include "game/memory.h"

typedef s32 (*DLLProlog)(void);
typedef void (*DLLEpilog)(void);

#ifdef TARGET_PC
typedef void (*DLLObjectSetup)(void);
#endif

omDllData *omDLLinfoTbl[OM_DLL_MAX];

static FileListEntry *omDLLFileList;

void omDLLDBGOut(void)
{
	OSReport("DLL DBG OUT\n");
}

void omDLLInit(FileListEntry *ovl_list)
{
	s32 i;
	OSReport("DLL DBG OUT\n");
	for(i=0; i<OM_DLL_MAX; i++) {
		omDLLinfoTbl[i] = NULL;
	}
	omDLLFileList = ovl_list;
}

s32 omDLLStart(s16 overlay, s16 flag)
{
	s32 dllno;
	OSReport("DLLStart %d %d\n", overlay, flag);
	dllno = omDLLSearch(overlay);
	if(dllno >= 0 && !flag) {
		omDllData *dll = omDLLinfoTbl[dllno];
#ifdef TARGET_PC
		OSReport("objdll>Already Loaded %s\n", dll->name);
#else
		OSReport("objdll>Already Loaded %s(%08x %08x)\n", dll->name, dll->module, dll->bss);
		
		omDLLInfoDump(&dll->module->info);
		omDLLHeaderDump(dll->module);
		memset(dll->bss, 0, dll->module->bssSize);
		HuMemDCFlushAll();
		dll->ret = ((DLLProlog)dll->module->prolog)();
#endif
		OSReport("objdll> %s prolog end\n", dll->name);
		return dllno;
	} else {
		for(dllno=0; dllno<OM_DLL_MAX; dllno++) {
			if(omDLLinfoTbl[dllno] == NULL) {
				break;
			}
		}
		if(dllno == OM_DLL_MAX) {
			return -1;
		}
		omDLLLink(&omDLLinfoTbl[dllno], overlay, TRUE);
		return dllno;
	}
}

void omDLLNumEnd(s16 overlay, s16 flag)
{
	s16 dllno;
	if(overlay < 0) {
		OSReport("objdll>omDLLNumEnd Invalid dllno %d\n", overlay);
		return;
	}
	OSReport("objdll>omDLLNumEnd %d %d\n", overlay, flag);
	dllno = omDLLSearch(overlay);
	if(dllno < 0) {
		OSReport("objdll>omDLLNumEnd not found DLL No%d\n", overlay);
		return;
	}
	omDLLEnd(dllno, flag);
}

void omDLLEnd(s16 dllno, s16 flag)
{
	OSReport("objdll>omDLLEnd %d %d\n", dllno, flag);
	if(flag == 1) {
		OSReport("objdll>End DLL:%s\n", omDLLinfoTbl[dllno]->name);
		omDLLUnlink(omDLLinfoTbl[dllno], 1);
		omDLLinfoTbl[dllno] = NULL;
	} else {
		omDllData *dll;
		dll = omDLLinfoTbl[dllno];
#ifdef __MWERKS__
		OSReport("objdll>Call Epilog\n");
		((DLLEpilog)dll->module->epilog)();
#endif
		OSReport("objdll>End DLL stayed:%s\n", omDLLinfoTbl[dllno]->name);
	}
	OSReport("objdll>End DLL finish\n");
}

omDllData *omDLLLink(omDllData **dll_ptr, s16 overlay, s16 flag)
{
	omDllData *dll;
	FileListEntry *dllFile = &omDLLFileList[overlay];
	OSReport("objdll>Link DLL:%s\n", dllFile->name);
	dll = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(omDllData));
	*dll_ptr = dll;
	dll->name = dllFile->name;
#ifdef _WIN32
    dll->hModule = LoadLibrary(dllFile->name);
	if (dll->hModule == NULL) {
		OSReport("objdll>++++++++++++++++ DLL Link Failed\n");
	}
#else
	dll->module = HuDvdDataReadDirect(dllFile->name, HEAP_SYSTEM);
	dll->bss = HuMemDirectMalloc(HEAP_SYSTEM, dll->module->bssSize);
	if(OSLink(&dll->module->info, dll->bss) != TRUE) {
		OSReport("objdll>++++++++++++++++ DLL Link Failed\n");
	}
	omDLLInfoDump(&dll->module->info);
	omDLLHeaderDump(dll->module);
	OSReport("objdll>LinkOK %08x %08x\n", dll->module, dll->bss);
#endif
	if(flag == 1) {
		OSReport("objdll> %s prolog start\n", dllFile->name);
#ifdef _WIN32
		{
		DLLObjectSetup objectSetup = (DLLObjectSetup)GetProcAddress(dll->hModule, "ObjectSetup");
		objectSetup();
		}
#else
		dll->ret = ((DLLProlog)dll->module->prolog)();
#endif
		OSReport("objdll> %s prolog end\n", dllFile->name);
	}
	return dll;
}

void omDLLUnlink(omDllData *dll_ptr, s16 flag)
{
	OSReport("odjdll>Unlink DLL:%s\n", dll_ptr->name);
#ifdef _WIN32
        FreeLibrary(dll_ptr->hModule);
#else
	if(flag == 1) {
		OSReport("objdll>Unlink DLL epilog\n");
		((DLLEpilog)dll_ptr->module->epilog)();
		OSReport("objdll>Unlink DLL epilog finish\n");
	}
	if(OSUnlink(&dll_ptr->module->info) != TRUE) {
		OSReport("objdll>+++++++++++++++++ DLL Unlink Failed\n");
	}
	HuMemDirectFree(dll_ptr->bss);
	HuMemDirectFree(dll_ptr->module);
#endif
	HuMemDirectFree(dll_ptr);
}

s32 omDLLSearch(s16 overlay)
{
	s32 i;
	FileListEntry *dllFile = &omDLLFileList[overlay];
	OSReport("Search:%s\n", dllFile->name);
	for(i=0; i<OM_DLL_MAX; i++) {
		omDllData *dll = omDLLinfoTbl[i];
		if(dll != NULL && strcmp(dll->name, dllFile->name) == 0) {
			OSReport("+++++++++++ Find%d: %s\n", i, dll->name);
			return i;
		}
	}
	return -1;
}

void omDLLInfoDump(OSModuleInfo *module)
{
	OSReport("===== DLL Module Info dump ====\n");
	OSReport("                   ID:0x%08x\n", module->id);
	OSReport("             LinkPrev:0x%08x\n", module->link.prev);
	OSReport("             LinkNext:0x%08x\n", module->link.next);
	OSReport("          Section num:%d\n", module->numSections);
	OSReport("Section info tbl ofst:0x%08x\n", module->sectionInfoOffset);
	OSReport("           nameOffset:0x%08x\n", module->nameOffset);
	OSReport("             nameSize:%d\n", module->nameSize);
	OSReport("              version:0x%08x\n", module->version);
	OSReport("===============================\n");
}

void omDLLHeaderDump(OSModuleHeader *module)
{
	OSReport("==== DLL Module Header dump ====\n");
	OSReport("          bss Size:0x%08x\n", module->bssSize);
	OSReport("        rel Offset:0x%08x\n", module->relOffset);
	OSReport("        imp Offset:0x%08x\n", module->impOffset);
	OSReport("    prolog Section:%d\n", module->prologSection);
	OSReport("    epilog Section:%d\n", module->epilogSection);
	OSReport("unresolved Section:%d\n", module->unresolvedSection);
	OSReport("       prolog func:0x%08x\n", module->prolog);
	OSReport("       epilog func:0x%08x\n", module->epilog);
	OSReport("   unresolved func:0x%08x\n", module->unresolved);
	OSReport("================================\n");
}

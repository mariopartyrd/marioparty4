#ifndef _NMWEXCEPTION
#define _NMWEXCEPTION

#include "types.h"
#include "PowerPC_EABI_Support/Runtime/exception.h"
#include "PowerPC_EABI_Support/Runtime/__ppc_eabi_linker.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef s16 vbase_ctor_arg_type;
typedef char local_cond_type;

typedef struct CatchInfo {
	void* location;
	void* typeinfo;
	void* dtor;
	void* sublocation;
	s32 pointercopy;
	void* stacktop;
} CatchInfo;

typedef struct DestructorChain {
	struct DestructorChain* next;
	void* destructor;
	void* object;
} DestructorChain;

extern void* __register_global_object(void* object, void* destructor, void* registration);
extern void __destroy_global_chain(void);

extern void __end__catch(CatchInfo* catchinfo);
extern void __throw(char* throwtype, void* location, void* dtor);
extern char __throw_catch_compare(const char* throwtype, const char* catchtype, s32* offset_result);
extern void __unexpected(CatchInfo* catchinfo);

extern int __register_fragment(struct __eti_init_info* info, char* TOC);
extern void __unregister_fragment(int fragmentID);

#ifdef __cplusplus
}
#endif

#endif // _NMWEXCEPTION

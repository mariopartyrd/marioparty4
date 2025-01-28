#ifndef _MSL_COMMON_ANSI_FP_H
#define _MSL_COMMON_ANSI_FP_H

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/float.h"

#define SIGDIGLEN 36

typedef struct decimal {
	char sign;
	char unk1;
	short exp;
	struct {
		unsigned char length;
		unsigned char text[36];
		unsigned char unk41;
	} sig;
} decimal;

typedef struct decform {
	char style;
	char unk1;
	short digits;
} decform;

void __num2dec(const decform* form, double x, decimal* d);

#endif

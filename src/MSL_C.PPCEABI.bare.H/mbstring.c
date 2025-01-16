#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/mbstring.h"

size_t wcstombs(char* s, const wchar_t* pwcs, size_t n)
{
	wchar_t next;
	size_t chars_written;
	int i;

	chars_written = 0;
	for (i = 0; i < n; ++i) {
		next = *pwcs++;
		*s++ = (char)next;
		if ((char)next == '\0')
			break;
		++chars_written;
	}
	return chars_written;
}

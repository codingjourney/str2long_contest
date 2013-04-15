#include <limits.h>

extern int error;

long str2long_codingjourney_3 (const char *text) {
	long result = 0L;
	int negative = (*text == '-');
	int valid = 0;
	int done = 0;

	text += negative;
	while (!done && !error) {
		char c = *(text++);
		if (c >= '0' && c <= '9') {
			valid = 1;
			long before = result;
			result = result * 10;
			if (result / 10L != before) {
				error = 1;
				break;
			}
			before = result;
			result += (c - '0');
			if (result < before) {
				int min = result == LONG_MIN;
				done = *text == '\0';
				error = !(negative && min && done);
			}
		} else if (c == '\0') {
			result *= negative ? -1L : 1L;
			error = !valid;
			done = 1;
		} else {
			error = 1;
		}
	}
	return result;
}


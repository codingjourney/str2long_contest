#include <limits.h>

extern int error;

long str2long_codingjourney (const char *text) {
	long result = 0L;
	long sign = 1L;
	int valid = 0;
	int done = 0;
	int i;

	for (i = 0; !done && !error; i++) {
		char c = text[i];
		if (i == 0 && c == '-') {
			sign = -1L;
		} else if (c >= '0' && c <= '9') {
			valid = 1;
			long before = result;
			result = result * 10 + (c - '0');
			if (result < before) {
				int min = sign == -1 && result == LONG_MIN;
				done = text[i + 1] == '\0';
				error = !(min && done);
			}
		} else if (c == '\0') {
			result = result * sign;
			error = !valid;
			done = 1;
		} else {
			error = 1;
		}
	}
	return result;
}


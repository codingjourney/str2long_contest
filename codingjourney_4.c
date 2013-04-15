#include <limits.h>

extern int error;

long str2long_codingjourney_4 (const char *text) {
	long result = 0L;
	int negative = (*text == '-');
	int digit = -1;
	int done = 0;

	text += negative;
	while (!done && !error) {
		char c = *(text++);
		if (c >= '0' && c <= '9') {
			if (result > LONG_MAX / 10) {
				error = 1;
				break;
			}
			result = result * 10;
			digit = c - '0';
			long max = LONG_MAX - digit;
			if (result <= max) {
				result = result + digit;
			} else if (negative && (result == max + 1)) {
				result = LONG_MIN;
				error = *text != '\0';
				done = 1;
			} else {
				error = 1;
			}
		} else if (c == '\0') {
			result *= negative ? -1L : 1L;
			error = digit < 0;
			done = 1;
		} else {
			error = 1;
		}
	}
	return result;
}


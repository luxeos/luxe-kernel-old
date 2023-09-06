/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <stdint.h>
#include <string.h>

void *memset(void *dest, int val, uint64_t n)
{
	uint8_t *ptr = dest;
	while (n--) {
		*ptr++ = (uint8_t)val;
	}
	return dest;
}

void memcpy(void *dest, const void *src, size_t n)
{
	char *a = (char *)src;
	char *b = (char *)dest;

	for (size_t i = 0; i < n; i++) {
		b[i] = a[i];
	}
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && (*s1 == *s2)) {
		++s1;
		++s2;
		--n;
	}
	if (n == 0) {
		return 0;
	} else {
		return (*(uint8_t *)s1 - *(uint8_t *)s2);
	}
}

int strlen(const char *str)
{
	int len = 0;
	while (*str != '\0') {
		len++;
		str++;
	}

	return len;
}

char *strtok(char *str, char *delim)
{
	static char *tmp;

	if (!str) {
		str = tmp;
	}
	if (!str) {
		return NULL;
	}

	for (;;) {
		if (__is_delim(*str, delim)) {
			str++;
			continue;
		}
		if (*str == '\0') {
			return NULL;
		}
		break;
	}

	char *ret = str;
	for (;;) {
		if (*str == '\0') {
			tmp = str;
			return ret;
		}
		if (__is_delim(*str, delim)) {
			*str = '\0';
			tmp = str + 1;
			return ret;
		}
		str++;
	}
}

int __is_delim(char c, char *delim)
{
	while (*delim != '\0') {
		if (c == *delim) {
			return 1;
		}
		delim++;
	}
	return 0;
}
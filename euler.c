#include <math.h>

#define SD_ALL 0x3fe	/* all digits 1-9, no 0 */

int isprime(int n) {
	if (n == 1)
		return 0;
	if (n == 2 || n == 3)
		return 1;
	if (!(n & 1) || (n % 3) == 0)
		return 0;
	for (int i = 2; i <= ceil(sqrt(n)); ++i)
		if (n % i == 0)
			return 0;
	return 1;
}

/* augment bitmap of used integers */
unsigned int sdigits(unsigned int old, int val) {
	while (val) {
		old |= 1 << (val % 10);
		val = val / 10;
	}
	return old;
}

int ndigits(int n) {
	int nd = 0;
	while (n) {
		nd++;
		n = n / 10;
	}
	return nd;
}

int ispandigital(int n) {
	int d = ndigits(n);
	unsigned int sd = sdigits(0, n);
	for (int i = 1; i <= d; ++i)
		if (!(sd & (1 << i)))
			return 0;
	return 1;
}

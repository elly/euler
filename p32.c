#include <math.h>
#include <stdio.h>
#include <string.h>

/* note: m0 * m1 = m2, we can use at most 9 digits between all three,
 * so a good conservative upper bound on m2 is 100000 (which requires way more
 * than 3 digits to make). */
#define MAX_RHS 100000
#define SD_ALL 0x3fe	/* all digits 1-9, no 0 */

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

int ispandigital(int m2) {
	for (int m0 = 1; m0 < ceil(sqrt(m2)); ++m0) {
		int m1;
		if (m2 % m0 != 0)
			continue;
		m1 = m2 / m0;
		if (ndigits(m0) + ndigits(m1) + ndigits(m2) != 9)
			continue;
		if (sdigits(sdigits(sdigits(0, m0), m1), m2) == SD_ALL) {
			/* printf("bing! %d * %d = %d\n", m0, m1, m2); */
			return 1;
		}
	}
	return 0;
}

int main() {
	unsigned int v = 0;
	size_t sum = 0;

	for (size_t i = 0; i < MAX_RHS; ++i)
		if (ispandigital(i))
			sum += i;

	printf("%lu\n", sum);

	return 0;
}

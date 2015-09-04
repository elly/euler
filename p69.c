#include "euler.c"

#include <stdio.h>
#include <stdint.h>

#define MAX_N 1000001

int prtab[MAX_N];

/* Sketchy explanation:
 * The result should be the value of n such that:
 *   a) n <= 1000000
 *   b) n = p0 * p1 * p2 * ... with primes p
 * So we produce a prime table, then walk through it multiplying the smallest
 * primes together in sequence and ta-da!
 */
int main() {
	int n = 1;
	for (int i = 1; i < MAX_N; ++i)
		prtab[i] = isprime(i);
	for (int i = 0; i < MAX_N; ++i) {
		if (!prtab[i])
			continue;
		if (n * i > 1000000) {
			printf("%d\n", n);
			break;
		}
		n = n * i;
	}

	return 0;
}

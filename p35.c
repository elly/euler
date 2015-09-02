#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROTATIONS 8
#define NR_VALS 1000000

int rotations(int val, int* results) {
	char nbuf[MAX_ROTATIONS * 2];
	char sbuf[MAX_ROTATIONS];
	size_t rlen;
	size_t nresult = 0;
	rlen = snprintf(nbuf, sizeof nbuf, "%d", val);
	snprintf(nbuf + rlen, (sizeof nbuf) - rlen, "%d", val);

	assert(rlen < MAX_ROTATIONS);

	for (size_t i = 0; i < rlen; ++i) {
		memset(sbuf, 0, sizeof sbuf);
		memcpy(sbuf, nbuf + i, rlen);
		results[nresult++] = atoi(sbuf);
	}

	return nresult;
}

int isprime(int n) {
	if (n == 2)
		return 1;
	for (int i = 2; i <= ceil(sqrt(n)); ++i)
		if (n % i == 0)
			return 0;
	return 1;
}

int main() {
	int r[MAX_ROTATIONS];
	size_t count = 0;

	int ispr[NR_VALS];

	for (size_t i = 0; i < NR_VALS; ++i)
		ispr[i] = isprime(i);

	for (size_t i = 2; i < NR_VALS; ++i) {
		size_t nrot = rotations(i, r);
		int allprime = 1;
		for (size_t j = 0; j < nrot; ++j)
			if (!isprime(r[j]))
				allprime = 0;
		if (allprime)
			count++;
	}

	printf("%lu\n", count);
	return 0;
}

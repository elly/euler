#include <math.h>
#include <stdint.h>
#include <stdio.h>

int nfact(int64_t val) {
	int64_t n = 1;
	int nf = 0;
	int64_t sq = ceil(sqrt(val));
	while (n < sq) {
		if (val % n == 0)
			nf++;
		n++;
	}
	return nf * 2;
}

int main() {
	int64_t n = 0;
	for (int64_t i = 1; i < 1000000; ++i) {
		n += i;
		int v = nfact(n);
		if (v > 500) {
			printf("%lld %lld -> %d\n", i, n, v);
			break;
		}
	}
	return 0;
}

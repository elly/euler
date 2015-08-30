#include <stdint.h>
#include <stdio.h>

const uint64_t kMaxN = 1000000;

int collatzlen(uint64_t seed) {
	int len = 0;
	while (seed > 1) {
		if (seed & 1)
			seed = 3 * seed + 1;
		else
			seed = seed >> 1;
		len++;
	}
	return len;
}

int main() {
	int maxlen = 0;
	uint64_t maxs = 0;
	for (uint64_t n = 0; n < kMaxN; ++n) {
		int len = collatzlen(n);
		if (len > maxlen) {
			maxlen = len;
			maxs = n;
		}
	}

	printf("%lld -> %d\n", maxs, maxlen);
	return 0;
}

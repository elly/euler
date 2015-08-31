#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const int kMax = 201;
const int kCoinVals[] = { 1, 2, 5, 10, 20, 50, 100, 200 };

uint64_t nc(int v, int ci) {
	uint64_t c = 0;
	if (v == 0)
		return 1;
	if (v >= kCoinVals[ci])
		c += nc(v - kCoinVals[ci], ci);
	if (ci > 0)
		c += nc(v, ci - 1);
	return c;
}

int main() {
	printf("%llu\n", nc(200, sizeof(kCoinVals) / sizeof(kCoinVals[0]) - 1));
	return 0;
}

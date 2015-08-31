#include <stdint.h>
#include <stdio.h>

uint64_t fifth(uint64_t v) {
	return v * v * v * v * v;
}

/* fifth digit power */
uint64_t fdp(uint64_t v) {
	uint64_t total = 0;
	while (v > 0) {
		total += fifth(v % 10);
		v = v / 10;
	}
	return total;
}

int main() {
	uint64_t total = 0;
	for (uint64_t i = 10; i < 10000000; ++i)
		if (i == fdp(i)) {
			printf("%llu\n", i);
			total += i;
		}
	printf("%llu\n", total);
	return 0;
}

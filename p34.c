#include <stdint.h>
#include <stdio.h>

uint64_t fact[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

/* factorial digit sum */
uint64_t fds(uint64_t v) {
	uint64_t total = 0;
	while (v > 0) {
		total += fact[v % 10];
		v = v / 10;
	}
	return total;
}

int main() {
	uint64_t total = 0;
	for (uint64_t i = 10; i < 10000000; ++i)
		if (i == fds(i)) {
			printf("%llu\n", i);
			total += i;
		}
	printf("%llu\n", total);
	return 0;
}

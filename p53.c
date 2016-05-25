#include <stdint.h>
#include <stdio.h>

#define MAX_N 101

uint64_t fact(uint64_t n) {
	if (n <= 1)
		return 1;
	return n * fact(n - 1);
}

uint64_t choose(uint64_t* facts, uint64_t n, uint64_t r) {
	printf("%llu %llu %llu\n", facts[n], facts[r], facts[n - r]);
	return facts[n] / (facts[r] * facts[n - r]);
}

int main() {
	uint64_t facts[MAX_N];
	int n = 0;

	for (int i = 0; i < MAX_N; ++i) {
		facts[i] = fact(i);
		printf("fact %d -> %llu\n", i, facts[i]);
	}

	printf("choose(23,10) = %llu\n", choose(facts, 23, 10));
	return 0;

	for (int i = 1; i < MAX_N; ++i)
		for (int j = 1; j <= i; ++j)
			if (choose(facts, i, j) > 1000000U)
				n++;

	printf("%d\n", n);
	return 0;
}

#include <math.h>
#include <stdint.h>
#include <stdio.h>

const size_t kMax = 10000;

int d(int n) {
	int s = 1;
	for (int i = 2; i < ceil(sqrt(n)); i++) {
		if (n % i == 0) {
			s += i;
			s += n / i;
		}
	}
	return s;
}

int main() {
	int dsums[kMax];
	int asum = 0;

	for (int i = 0; i < kMax; ++i)
		dsums[i] = d(i);
	for (int i = 0; i < kMax; ++i) {
		int ds = dsums[i];
		if (i == 220)
			printf("%d -> %d -> %d\n",
			       i, ds, dsums[ds]);
		if (ds < kMax && dsums[ds] == i && ds != i)
			asum += i;
	}

	printf("%d\n", asum);
	return 0;
}

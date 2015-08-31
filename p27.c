#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

const int kMaxVal = 1000000;
const int kMaxA = 1000;
const int kMaxB = 1000;

int prime(int n) {
	for (int i = 2; i < ceil(sqrt(n)); ++i)
		if (n % i == 0)
			return 0;
	return 1; 
}

int quad(int n, int a, int b) {
	return n * (n + a) + b;
}

int quadlen(int *pr, int a, int b) {
	for (int n = 0; n < 10000; ++n) {
		int v = quad(n, a, b);
		assert(v < kMaxVal);
		if (v < 0 || !pr[v])
			return n;
	}
	assert(0);
	return -1;
}

int main() {
	int ispr[kMaxVal];
	for (int i = 0; i < kMaxVal; ++i)
		ispr[i] = prime(i);

	int qla = 0, qlb = 0, qlmax = 0;
	for (int a = -kMaxA + 1; a < kMaxA; ++a) {
		for (int b = -kMaxB + 1; b < kMaxB; ++b) {
			int ql = quadlen(ispr, a, b);
			if (ql > qlmax) {
				qla = a;
				qlb = b;
				qlmax = ql;
			}
		}
	}

	printf("a = %d b = %d\n", qla, qlb);
	printf("a * b = %d\n", qla * qlb);
	return 0;
}

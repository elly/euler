#include <stdio.h>

#include "euler.c"

#define N 10000

int p[N];
int pr[N];

int nprfact(int *q, int n, int k) {
	int i;
	int nprf = 0;
	for (i = 0; i < n; i++) {
		if (!(k % q[i])) {
			nprf++;
			while (k % q[i])
				k /= q[i];
		}
	}
	return nprf;
}

int expt(int b, int e) {
	int r = 1;
	while (e--)
		r *= b;
	return r;
}

int run(int *pr, int r, int k, int n) {
	int i;
	for (i = 0; i < n; i++)
		if (nprfact(pr, r, k + i) != n)
			return 0;
	return 1;
}

int find(int *pr, int r, int nd) {
	for (int i = 1; i < 1000000; i++) {
		if (run(pr, r, i, nd))
			return i;
	}
	return 0;
}

int main() {
	int r = sieve(p, pr, N);
	printf("%d\n", find(pr, r, 4));
	return 0;
}

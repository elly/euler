#include <stdio.h>

#include "euler.c"

#define N 1000000

int p[N];
int q[N];

int nsum(const int *pr, int n, int k) {
	int i;
	int e;
	int s;
	int m = -1;
	for (i = 0; i < n; i++) {
		if (pr[i] > k)
			break;
		s = 0;
		for (e = 0; e + i < n; e++) {
			s += pr[e + i];
			if (s >= k)
				break;
		}
		if (s == k && e > m)
			m = e;
	}
	return m + 1;
}

int main() {
	int *npr;
	int r = sieve(p, q, N);
	int i;
	int mn = 0;
	int mm = 0;

	for (i = 0; i < r; i++) {
		int n = nsum(q, r, q[i]);
		if (n > mn) {
			mn = n;
			mm = q[i];
		}
	}

	printf("%d\n", mm);

	return 0;
}

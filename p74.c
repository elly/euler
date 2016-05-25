#include <stdio.h>

int dfact(int n) {
	int df[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800 };
	int p = 0;
	while (n) {
		p += df[n % 10];
		n /= 10;
	}
	return p;
}

#define MAX_CYCLE 61

int clen(int n) {
	int vals[MAX_CYCLE];
	int vi = 0;
	while (vi < MAX_CYCLE) {
		for (int i = 0; i < vi; ++i)
			if (vals[i] == n)
				return vi;
		vals[vi++] = n;
		n = dfact(n);
	}
	return vi;
}

int main() {
	int n = 0;
	for (int i = 0; i < 1000000; ++i)
		if (clen(i) == 60)
			n++;
	printf("%d\n", n);
	return 0;
}

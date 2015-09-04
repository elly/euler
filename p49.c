#include "euler.c"

#include <math.h>
#include <stdio.h>

int ispermutation(int a, int b) {
	int n = ndigits(a);
	if (n != ndigits(b))
		return 0;
	return sdigits(0, a) == sdigits(0, b);
}

int main() {
	for (int n = 1000; n < 9999; ++n) {
		for (int j = 1; j < 9999; ++j) {
			int n0 = n + j;
			int n1 = n + j + j;
			if (!ispermutation(n, n0) || !ispermutation(n, n1))
				continue;
			if (!isprime(n) || !isprime(n0) || !isprime(n1))
				continue;
			printf("%d %d %d\n", n, n0, n1);
		}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main() {
	int v = 1;
	int d = 2;
	int n = 0;
	int t = 0;
	while (n < ) {
		for (int i = 0; i < 4 && n + i < 9; ++i) {
			t += v;
			v += d;
		}
		d += 2;
		n += 4;
	}
	printf("%d\n", t);
	return 0;
}

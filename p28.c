#include <stdio.h>
#include <stdlib.h>

int main() {
	int i = 0;
	int sum = 0;
	int delta = 2;
	int j = 1;
	const int DIM = 500 * 4;
	sum += j;
	for (i = 0; i < DIM; i += 4) {
		j += delta;
		sum += j;
		j += delta;
		sum += j;
		j += delta;
		sum += j;
		j += delta;
		sum += j;
		delta += 2;
	}
	printf("%d\n", sum);
	return 0;
}

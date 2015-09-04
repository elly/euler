#include <stdio.h>

#include "euler.c"

int main() {
	for (int i = 987654321; i > 1; i -= 2) {
		if (ispandigital(i) && isprime(i)) {
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}

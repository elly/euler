#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 16
#define MAX_VALS 100000000

int prtab[MAX_VALS + 1];

int isprime(int n) {
	if (n == 1)
		return 0;
	if (n == 2)
		return 1;
	if (!(n & 1) || (n % 3) == 0)
		return 0;
	for (int i = 2; i <= ceil(sqrt(n)); ++i)
		if (n % i == 0)
			return 0;
	return 1;
}

int isltprime(int v) {
	char buf[MAX_DIGITS];
	int n = snprintf(buf, sizeof buf, "%d", v);
	for (int i = 0; i < n; ++i) {
		int nv = atoi(buf + i);
		if (!prtab[nv])
			return 0;
	}
	return 1;
}

int isrtprime(v) {
	char buf[MAX_DIGITS];
	int n = snprintf(buf, sizeof buf, "%d", v);
	while (n > 0) {
		int nv = atoi(buf);
		if (!prtab[nv])
			return 0;
		buf[--n] = '\0';
	}
	return 1;
}

int istprime(int v) {
	return isltprime(v) && isrtprime(v);
}

int main() {
	int i;
	int seen = 0;
	for (int i = 1; i < sizeof(prtab) / sizeof(prtab[0]); ++i)
		prtab[i] = isprime(i);
	printf("prtab done\n");
	for (i = 100; i < MAX_VALS && seen < 11; ++i) {
		if (istprime(i)) {
			printf("tprime %d: %d\n", seen, i);
			seen++;
		}
	}
	return 0;
}

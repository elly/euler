#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 16
#define MAX_VALS 1000000

int prtab[MAX_VALS + 1];
int nprtab = 0;

int cktab(int *tab, int ntab, int val) {
	for (int i = 0; i < ntab; i++)
		if (val % tab[i] == 0)
			return 0;
	return 1;
}

int intab(int *tab, int ntab, int val) {
	for (int i = 0; i < ntab; i++)
		if (tab[i] == val)
			return 1;
	return 0;
}

void mkprtab(int *tab, int *ntab) {
	int n = 0;
	int i = 0;
	for (int i = 2; i < MAX_VALS; i++)
		if (cktab(tab, n, i))
			tab[n++] = i;
	*ntab = n;
}

int isltprime(int v) {
	char buf[MAX_DIGITS];
	int n = snprintf(buf, sizeof buf, "%d", v);
	for (int i = 0; i < n; ++i) {
		int nv = atoi(buf + i);
		if (!intab(prtab, nprtab, nv))
			return 0;
	}
	return 1;
}

int isrtprime(v) {
	char buf[MAX_DIGITS];
	int n = snprintf(buf, sizeof buf, "%d", v);
	while (n > 0) {
		int nv = atoi(buf);
		if (!intab(prtab, nprtab, nv))
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
	mkprtab(prtab, &nprtab);
	printf("prtab done\n");
	for (i = 100; i < MAX_VALS && seen < 11; ++i) {
		if (istprime(i)) {
			printf("tprime %d: %d\n", seen, i);
			seen++;
		}
	}
	return 0;
}

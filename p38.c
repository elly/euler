#include "euler.c"

#include <stdio.h>
#include <stdlib.h>

int iscatpd(int n) {
	char buf[32];
	char* p = buf;
	for (int i = 1; i < 9 && p - buf < 9; ++i) {
		p += snprintf(p, sizeof buf, "%d", n * i);	/* XXX */
	}
	if (p - buf != 9)
		return 0;
	n = atoi(buf);
	if (ndigits(n) != 9)
		return 0;
	return ispandigital(n) ? n : 0;
}

int main() {
	for (int i = 100000000; i > 0; --i) {
		int v = iscatpd(i);
		if (v) {
			printf("%d -> %d\n", i, v);
			break;
		}
	}
	return 0;
}

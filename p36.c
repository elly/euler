#include <stdio.h>

int isb10p(unsigned int n) {
	char buf[32];
	char *p = buf + sizeof(buf);
	while (n) {
		*(--p) = (n % 10) + '0';
		n = n / 10;
	}
	for (size_t i = 0; i < (buf + sizeof(buf) - p) / 2; ++i)
		if (buf[sizeof(buf) - (i + 1)] != p[i])
			return 0;
	return 1;
}

int isb2p(unsigned int n) {
	char buf[32];
	char *p = buf + sizeof(buf);
	while (n) {
		*(--p) = (n & 1) + '0';
		n = n / 2;
	}
	for (size_t i = 0; i < (buf + sizeof(buf) - p) / 2; ++i)
		if (buf[sizeof(buf) - (i + 1)] != p[i])
			return 0;
	return 1;
}

int main() {
	unsigned int total = 0;
	for (unsigned int i = 0; i < 1000000; ++i)
		if (isb10p(i) && isb2p(i))
			total += i;
	printf("%u\n", total);
	return 0;
}

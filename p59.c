#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 4096

int load(int* ivs) {
	char chs[BUF_SIZE];
	int niv = 0;
	int len = 0;
	int fd = open("p059_cipher.txt", O_RDONLY);
	char* p;

	memset(chs, 0, sizeof chs);
	len = read(fd, chs, sizeof chs);
	close(fd);

	p = strtok(chs, ",");
	while (p) {
		ivs[niv++] = atoi(p);
		p = strtok(NULL, ",");
	}
	return niv;
}

void xorc(int* out, int* in, int nin, char* k, int nk) {
	for (int i = 0; i < nin; ++i)
		out[i] = in[i] ^ k[i % nk];
}

int englishish(int* in, int nin) {
	char chs[BUF_SIZE];
	memset(chs, 0, sizeof chs);
	for (int i = 0; i < nin; ++i) {
		if (in[i] < ' ' || in[i] >= '\x7f')
			return 0;
		chs[i] = in[i];
	}
	/* boy is this a cheap hack. */
	if (strstr(chs, " the ")) {
		return 1;
	}
	return 0;
}

int total(int* in, int nin) {
	int t = 0;
	for (int i = 0; i < nin; ++i)
		t += in[i];
	return t;
}

int main() {
	int ivs[BUF_SIZE];
	int niv = load(ivs);
	int divs[BUF_SIZE];
	char k[3] = { 103, 111, 100 };

	for (k[0] = 'a'; k[0] <= 'z'; ++k[0]) {
		for (k[1] = 'a'; k[1] <= 'z'; ++k[1]) {
			for (k[2] = 'a'; k[2] <= 'z'; ++k[2]) {
				xorc(divs, ivs, niv, k, sizeof k);
				if (!englishish(divs, niv))
					continue;
				printf("%d\n", total(divs, niv));
			}
		}
	}
}

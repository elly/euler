#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int lsum(const char* name) {
	int i = 0;
	while (*name) {
		if (*name != '"')
			i += *name - 'A' + 1;
		name++;
	}
	return i;
}

int dstrcmp(const void* a, const void* b) {
	char* as = *(char **)a;
	char* bs = *(char **)b;
	return strcmp(as, bs);
}

int main() {
	char buf[65536];
	char* nptrs[65536];
	int fd = open("p022_names.txt", O_RDONLY);
	memset(buf, 0, sizeof(buf));
	read(fd, buf, sizeof(buf));
	close(fd);

	uint64_t total = 0;
	char *name = strtok(buf, ",");
	int i = 0;
	while (name != NULL) {
		nptrs[i++] = name;
		name = strtok(NULL, ",");
	}
	qsort(nptrs, i, sizeof(char*), dstrcmp);
	printf("%s %s %s\n", nptrs[0], nptrs[1], nptrs[2]);
	for (int j = 0; j < i; ++j) {
		int score = (j + 1) * lsum(nptrs[j]);
		if (!strcmp(nptrs[j], "\"COLIN\""))
			printf("score %d * %d = %d\n",
			       (j + 1), lsum(nptrs[j]), score);
		total += score;
	}
	printf("%llu\n", total);
	return 0;
}

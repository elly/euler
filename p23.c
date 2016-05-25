/* p23.c */

#include <stdio.h>
#include <string.h>

#define MAX 28124

int abundant(int n) {
	int i;
	int divsum = 0;
	for (i = 1; i < n; i++)
		if (n % i == 0)
			divsum += i;
	return divsum > n; 
}

int main() {
	int abund[MAX];
	int twoabund[MAX];
	int i, j;
	int sum = 0;
	for (i = 0; i < MAX; i++)
		abund[i] = abundant(i);
	memset(twoabund, 0, MAX * sizeof(int));
	for (int i = 0; i < MAX; i++) {
		if (!abund[i])
			continue;
		for (int j = 0; j < MAX; j++) {
			if (!abund[j])
				continue;
			if (i + j < MAX)
				twoabund[i + j] = 1;
		}
	}
	for (i = 0; i < MAX; i++)
		if (!twoabund[i])
			sum += i;
	printf("%d\n", sum);
	return 0;
}

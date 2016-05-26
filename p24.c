#include <stdio.h>
#include <string.h>

void reverse(int *ordering, int nnodes) {
	for (int i = 0; i < nnodes / 2; i++) {
		int t = ordering[i];
		ordering[i] = ordering[nnodes - i - 1];
		ordering[nnodes - i - 1] = t;
	}
}

int permute(int *ordering, int nnodes) {
	int k;
	int l;
	int t;
	for (k = nnodes - 2; k >= 0; k--)
		if (ordering[k + 1] > ordering[k])
			break;
	if (k == -1)
		return 1;
	for (l = nnodes - 1; l > k; l--)
		if (ordering[l] > ordering[k])
			break;
	t = ordering[k];
	ordering[k] = ordering[l];
	ordering[l] = t;
	reverse(ordering + k + 1, nnodes - (k + 1));
	return 0;
}

void nthpermute(int *input, int len, int n) {
	int i;
	for (i = 0; i < n; i++)
		permute(input, len);
}

int main() {
	int s[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i;
	int n = sizeof(s) / sizeof(s[0]);
	nthpermute(s, n, 999999);
	for (i = 0; i < n; i++)
		printf("%d", s[i]);
	printf("\n");
	return 0;
}

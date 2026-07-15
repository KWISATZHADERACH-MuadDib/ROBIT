#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int n, r, i, n_fac = 1, nMr_fac = 1, r_fac = 1;
	int permutation = 0, combination = 0, PI = 1, H = 1;


	printf("n과 r을 입력하세요 : ");
	scanf("%d %d", &n, &r);

	for (i = 1; i <= n; i++) {
		n_fac *= i;
	}
	for (i = 1; i <= n - r; i++) {
		nMr_fac *= i;
	} 
	for (i = 1; i <= r; i++) {
		r_fac *= i;
		PI *= n;
	}
	for (i = n; i <= n + r - 1; i++) {
		H *= i;
	}

	permutation = n_fac / nMr_fac;
	combination = permutation / r_fac;
	H /= r_fac;

	printf("%d %d %d %d", permutation, PI, combination, H);

	return 0;
}
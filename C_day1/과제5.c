#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int n, i, j;

	printf("값을 입력하세요.");
	scanf("%d", &n);

	for (i = 1; i <= 2 * n - 1; i++) {
		for (j = 1; j <= 2 * n; j++) {
			if (i < n) {
				if (j <= i || 2 * n - j < i)
					printf("*");
				else
					printf(" ");
			}
			if (i == n)
				printf("*");
			if (i > n) {
				if (j < 2 * n + 1 - i || 2 * n - j < 2 * n - i)
					printf("*");
				else
					printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}

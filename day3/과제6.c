#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int n, i, j;
	int row, column;
	printf("값을 입력하세요:");
	scanf("%d", &n);

	column = 2 * n - 1;
	row = n;

	for (i = 1; i <= row; i++) {
		for (j = 1; j <= column; j++) {
			if (i == row)
				printf("*");
			else if (i == 1 && j == n)
				printf("*");
			else if (j == n - i + 1 || j == n + i - 1) {
				printf("*");
			}
			else
				printf(" ");
		}
		printf("\n");
	}

	
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int arr[100][100];
	int n1, n2, i, j;

	scanf("%d %d", &n1, &n2);

	for (i = 0; i < n1; i++) {
		for (j = 0; j < n2; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	for (i = 0; i < n2; i++) {
		for (j = 0; j < n1; j++) {
			printf("%3d", arr[j][i]);	//10의 자리수도 있어 보기편하게 %3d로 간격을 조절함
		}
		printf("\n");
	}

	return 0;
}

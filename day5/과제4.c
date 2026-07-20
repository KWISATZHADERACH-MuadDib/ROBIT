#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, i, min, max, sum = 0;
	double avg = 0;

	printf("몇 개의 원소를 할당하겠습니까? : ");
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
		printf("정수형 데이터 입력 : ");
		scanf("%d", &arr[i]);
		sum += arr[i];
		if (i == 0) {
			min = arr[i];
			max = arr[i];
		}
		else if (min > arr[i])
			min = arr[i];
		else if (max < arr[i])
			max = arr[i];
		else
			continue;
	}
	avg = (double)sum / n;

	printf("최대값 : %d\n", max);
	printf("최솟값 : %d\n", min);
	printf("전체합 : %d\n", sum);
	printf("평균 : %lf\n", avg);

	free(arr);

	return 0;
}
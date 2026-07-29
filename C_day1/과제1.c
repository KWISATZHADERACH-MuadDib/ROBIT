#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int i = 0;
	double arr[5];
	double sum = 0;
	double avg = 0;
	double max = 0;
	double min = 0;

	for (i = 0; i < 5; i++)
	{
		printf("%d 번째 실수를 입력하시오. ", i);
		scanf("%lf", &arr[i]);
		sum += arr[i];
		if (i == 0) {
			max = arr[i];
			min = arr[i];
			continue;
		}
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}

	avg = sum / 5;

	printf("---- 결과 ----\n");
	printf("평균은 %lf입니다\n", avg);
	printf("최대값은 %lf입니다\n", max);
	printf("최솟값은 %lf입니다\n", min);

	return 0;
}

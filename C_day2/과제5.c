#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int arr[10000] = { 0, };

	int min = 0, max = 0, cnt = 0;
	int i, j;

	printf("min :");
	scanf("%d", &min);
	printf("max :");
	scanf("%d", &max);

	if (min == 1) {
		min = 2;
		cnt++;
	}
	for (i = min; i <= max; i++) {
		if (i * i > max)
			break;
		else {
			for (j = 1; j <= max; j++) {
				if (i * i * j > max)
					break;
				else {
					arr[i * i * j] = 1;
				}
			}
		}
	}
	for (i = min; i <= max; i++) {
		if (arr[i] == 0)
			cnt++;
	}
	printf("제곱 ㄴㄴ수 : %d개\n", cnt);
	for (i = min; i <= max; i++) {
		if (arr[i] == 0)
			printf("%d ", i);
	}

}

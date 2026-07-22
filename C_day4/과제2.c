#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Point {
	int x;
	int y;
	double distance;
}Point;



int main() {
	int i, j, n = 0;
	double max = 0;
	int max_index = 0;
	int x_dist, y_dist;	//x값의 거리, y의 값의 거리

	scanf("%d", &n);

	//Point형 동적 배열 arr생성
	Point* arr = (Point*)malloc(sizeof(Point) * n);

	for (i = 0; i < n; i++) {
		scanf("%d %d", &arr[i].x, &arr[i].y);
		arr[i].distance = 0;
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j)
				continue;
			x_dist = arr[i].x - arr[j].x;
			y_dist = arr[i].y - arr[j].y;
			arr[i].distance += (double)sqrt(x_dist * x_dist + y_dist * y_dist);
		}
	}

	for (i = 0; i < n; i++) {
		if (arr[i].distance > max) {
			max = arr[i].distance;
			max_index = i;
		}
	}

	printf("가장 거리가 먼 좌표는 (%d, %d)이며, 다른 좌표의 거리 총합은 약 %.1lf입니다.", arr[max_index].x, arr[max_index].y, arr[max_index].distance);

	free(arr);

	return 0;
}

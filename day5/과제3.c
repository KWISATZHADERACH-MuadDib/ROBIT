#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int direction[4][2] = { {0, 1} , {1 , 0}, {0,-1}, {-1, 0} }; //오른쪽, 아래, 왼쪾, 위

int main() {
	int n1, n2, i = 0, j = 0, cnt = 1, direc;
	int x = 0, y = 0;

	scanf("%d %d", &n1, &n2);		//행, 열

	//2차원 배열 동적할당
	int** arr = (int**)malloc(n1 * sizeof(int*));

	for (i = 0; i < n1; i++) {
		arr[i] = (int*)malloc(n2 * sizeof(int));
	}

	for (i = 0; i < n1; i++) {
		for (j = 0; j < n2; j++) {
			arr[i][j] = 0;
		}
	}
	direc = 0;
	for (i = 1; i <= n1 * n2; i++) {
		arr[y][x] = i;
		//다음 배열의 x, y값이 범위 안에 들어와있을 떄
		if (y + direction[direc][0] >= 0 && y + direction[direc][0] < n1 && x + direction[direc][1] >= 0 && x + direction[direc][1] < n2) {
			if (arr[y + direction[direc][0]][x + direction[direc][1]] == 0) {	//다음 배열의 값이 0인 경우
				y += direction[direc][0];
				x += direction[direc][1];
			}
			else {		//다음 배열에 값이 있는 경우
				if (direc == 3)
					direc = 0;
				else
					direc++;
				y += direction[direc][0];
				x += direction[direc][1];
			}
		}
		else {
			if (direc == 3)
				direc = 0;
			else
				direc++;
			y += direction[direc][0];
			x += direction[direc][1];
		}
	}

	for (i = 0; i < n1; i++) {
		for (j = 0; j < n2; j++) {
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < n1; i++) {
		free(arr[i]);  
	}
	free(arr);

	return 0;
}
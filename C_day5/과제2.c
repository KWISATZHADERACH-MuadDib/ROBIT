#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Point {
	int x;
	int y;
}Point;

Point direction[4] = { {1, 0} , {0 , 1}, {-1,0}, {0, -1} }; //오른쪽, 아래, 왼쪾, 위

void print(int* row, int* col, int** pArr);
void arr_ij(int* sizeRow, int* sizeCol, int** pArr);

int main() {
	int row, col, sizeRow, sizeCol, i = 0, j = 0;

	printf("열의 수를 입력하세요 : ");
	scanf("%d", &sizeCol);
	printf("행의 수를 입력하세요 : ");
	scanf("%d", &sizeRow);

	row = sizeRow;
	col = sizeCol;

	//2차원 배열 동적할당 
	int** arr = (int**)malloc(row * sizeof(int*));

	for (i = 0; i < row; i++) {
		arr[i] = (int*)malloc(col * sizeof(int));
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			arr[i][j] = 0;
		}
	}

	arr_ij(&sizeRow, &sizeCol, arr);

	print(&row, &col, arr);

	for (i = 0; i < row; i++) {
		free(arr[i]);
	}
	free(arr);

	return 0;
}

void arr_ij(int* sizeRow, int* sizeCol, int** pArr) {
	int direc = 0;
	int row = *sizeRow;
	int col = *sizeCol;
	int i, x = 0, y = 0;

	for (i = 1; i <= row * col; i++) {
		pArr[y][x] = i;
		//다음 배열의 x, y값이 범위 안에 들어와있을 떄
		if (y + direction[direc].y >= 0 && y + direction[direc].y < row && x + direction[direc].x >= 0 && x + direction[direc].x < col) {
			if (pArr[y + direction[direc].y][x + direction[direc].x] == 0) {	//다음 배열의 값이 0인 경우
				y += direction[direc].y;
				x += direction[direc].x;
			}
			else {		//다음 배열에 값이 있는 경우 -> 방향 전환
				if (direc == 3)
					direc = 0;
				else
					direc++;
				y += direction[direc].y;
				x += direction[direc].x;
			}
		}
		else {			//벽에 막혔을 경우 -> 방향 전환
			if (direc == 3)
				direc = 0;
			else
				direc++;
			y += direction[direc].y;
			x += direction[direc].x;
		}
	}
}

void print(int* row, int* col, int** pArr) {
	int i, j;
	for (i = 0; i < *row; i++) {
		for (j = 0; j < *col; j++) {
			printf("%3d ", pArr[i][j]);
		}
		printf("\n");
	}
	return;
}

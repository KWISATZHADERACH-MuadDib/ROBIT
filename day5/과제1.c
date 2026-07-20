#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//4일차 과제1번 종류3과 규칙이 같아 코드를 재사용하였다.
void map() {
	int row = 5;			//세로
	int column = 5;		//가로
	int center = 3;					//그림의 중앙
	int i, j;
	int cnt = 0, num = 1;//별을 찍었던 위치마다 숫자를 찍고 숫자를 증가시키기 위해 num변수를 사용하였다.

	for (i = 1; i <= row; i++) {
		for (j = 1; j <= column; j++) {
			if (j > cnt && j <= column - cnt) {
				printf("%3d", num);
				num++;
			}
			else
				printf("%3d", 0);
		}
		if (i < center)			//중앙 이전에는 감소
			cnt++;
		else if (i >= center)	//중앙 이후에는 증가
			cnt--;
		printf("\n");
	}


	return;
}

int main() {
	map();
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//종류 1은 점점 증가하다가 중간을 기준으로 다시 감소하는 규칙을 가지고 있다.
void type_one(int length) {
	int row = length;	//세로
	int column = 0;		//가로
	int i, j;

	if (length % 2 == 0) {	//길이가 짝수일 경우
		column = length / 2;	// column은 중앙과 같다

		for (i = 1; i <= row; i++) {
			for (j = 1; j <= column; j++) {	//중장 전
				if (i < column && j <= i)
					printf("*");
				else if (i == column || i == column + 1)	//중앙
					printf("*");
				else if (i > column && row - i + 1 >= j)	//i - column = 중앙으로부터 떨어진 거리
					printf("*");							//중앙으로부터 떨어진 거리만큼 별의 개수가 줄어든다
				else
					printf(" ");
			}
			printf("\n");
		}
	}
	else {					//길이가 홀수인 경우
		column = length / 2 + 1;

		for (i = 1; i <= row; i++) {
			for (j = 1; j <= column; j++) {
				if (i < column && j <= i)					//중앙 전
					printf("*");
				else if (i == column)						//중앙인 경우
					printf("*");
				else if (i > column && row - i + 1 >= j)	//i - column = 중앙으로부터 떨어진 거리
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
	}

	return;
}

//종류2는 종류1과 대칭이다. 규칙은 같고 모양이 대칭일 때는 보수를 활용하면 된다. ex) 8 + 2 = 10, 7 + 3 = 10 ; 7은 3의 보수
void type_two(int length) {
	int row = length;	//세로
	int column = 0;		//가로
	int i, j;

	if (length % 2 == 0) {	//길이가 짝수일 경우
		column = length / 2;

		for (i = 1; i <= row; i++) {
			for (j = 1; j <= column; j++) {
				if (i < column && column - i < j)		//column < i + j; 보수의 활용
					printf("*");
				else if (i == column || i == column + 1)
					printf("*");
				else if (i > column && i - column <= j)	//i - column = 중앙으로부터 떨어진 거리
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
	}
	else {					//길이가 홀수인 경우
		column = length / 2 + 1;

		for (i = 1; i <= row; i++) {
			for (j = 1; j <= column; j++) {
				if (i < column && column - i < j)		//column < i + j; 보수의 활용
					printf("*");
				else if (i == column)
					printf("*");
				else if (i > column && i - column < j)	//i - column = 중앙으로부터 떨어진 거리
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
	}

	return;
}

//종류3은 중앙으로 갈수록 양쪽에서 줄어들고, 중앙 이후에는 양쪽으로 늘어난다. 위와같이 보수를 활용하면 양쪽의 값을 계산하기 쉽다.
void type_three(int length) {
	int row = length;			//세로
	int column = length;		//가로
	int center;					//그림의 중앙
	int i, j;
	int cnt = 0;

	if (length % 2 == 0) {		//길이가 짝수일 경우
		center = length / 2;
		for (i = 1; i <= row; i++) {
			for (j = 1; j <= column; j++) {
				if (j > cnt && j <= column - cnt)
					printf("*");
				else
					printf(" ");
			}
			if (i < center)			//중앙 이전에는 감소
				cnt++;
			else if (i > center)	//중앙 이후에는 증가
				cnt--;
			printf("\n");
		}
	}
	else {					//길이가 홀수인 경우
		center = length / 2 + 1;
		for (i = 1; i <= row; i++) {
			for (j = 1; j <= column; j++) {
				if (j > cnt && j <= column - cnt)
					printf("*");
				else
					printf(" ");
			}
			if (i < center)			//중앙 이전에는 감소
				cnt++;
			else if (i >= center)	//중앙 이후에는 증가
				cnt--;
			printf("\n");
		}
	}

	return;
}

//종류 4는 중앙 전에는 감소, 중앙 후에는 증가하는 것을 알 수 있다. 
//모양을 보면 종류2의 아랫부분과 종류1의 윗부분을 합친것임을 알 수 있다.
void type_four(int length) {
	int row = length;	//세로
	int column = length;		//가로
	int center;
	int cnt = 0;
	int i, j;

	if (length % 2 == 0) {	//길이가 짝수일 경우

		center = length / 2;

		for (i = 1; i <= center; i++) {				//중앙 전
			for (j = 1; j <= center + 1; j++) {
				if (j > cnt)
					printf("*");
				else
					printf(" ");
			}
			cnt++;
			printf("\n");
		}
		for (i = center + 1; i <= row; i++) {		//중앙 이후
			for (j = 1; j <= column; j++) {			//중앙 이후에는 중앙까지만큼 빈칸이기 때문에 그 값만큼 띄고 규칙을 적용했다.
				if (j < cnt)
					printf(" ");
				else if (j <= i)
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
	}
	else {					//길이가 홀수인 경우
		center = length / 2 + 1;

		for (i = 1; i <= center; i++) {		//중앙 전
			for (j = 1; j <= center; j++) {
				if (j > cnt)
					printf("*");
				else
					printf(" ");
			}
			cnt++;
			printf("\n");
		}
		for (i = center + 1; i <= row; i++) {	//중앙 이후
			for (j = 1; j <= column; j++) {		//중앙 이후에는 중앙까지만큼 빈칸이기 때문에 그 값만큼 띄고 규칙을 적용했다.
				if (j < cnt)
					printf(" ");
				else if (j <= i)
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
	}

	return;
}

int main() { 
	int length, type;

	printf("사이즈와 종류를 입력하시오.");
	scanf("%d %d", &length, &type);

	if (type == 1)
	{
		type_one(length);
	}
	else if (type == 2) {
		type_two(length);
	}
	else if (type == 3) {
		type_three(length);
	}
	else if (type == 4) {
		type_four(length);
	}
	return 0;
}
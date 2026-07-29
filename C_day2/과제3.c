#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char arr[10];
char ascending[10] = "cdefgabC";
char descending[10] = "Cbagfedc";

int compare() {						//입력받은 문자열이 ascending인지 descending인지 비교하는 함수
	int i = 0, a = 1, d = 1;

	for (i = 0; i < 8; i++) {				//8개의 음으로 이루어진 다장조만 입력받기 때문에 8번만 반복
		if (arr[i] != ascending[i]) {		//ascending이 아닐 경우
			a = 0;
		}
		if (arr[i] != descending[i]) {		//descending이 아닐 경우
			d = 0;
		}
	}
	if (a == 1)						//ascending이면 2반환
		return 2;
	else if (d == 1)				//descending이면 1반환
		return 1;
	else
		return 0;					//둘 다 아니면 0반환
	return 0;
}

int main() {

	printf("음 입력\n");
	scanf("%s", arr);

	switch (compare()) {
		case 2 :
			printf("결과 : ascending");
			break;
		case 1 :
			printf("결과 : descending");
			break;
		case 0 :
			printf("결과 : mixed");
			break;
		default :
			printf("잘못된 입력입니다.");
	}

	return 0;
}

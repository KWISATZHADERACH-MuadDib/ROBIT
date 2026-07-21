#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Thing {
	char name[20];
	int price;
}Thing;

int string_compare(char s1[], char s2[]);

int main()
{
	int n, i, j;
	char input[20];	//마지막에 입력되는 물건 이름

	scanf("%d", &n);
	//Thing형 구조체 배열 arr 생성
	Thing* arr = (Thing*)malloc(sizeof(Thing) * n);

	for (i = 0; i < n; i++) {
		scanf("%s %d", arr[i].name, &arr[i].price);
		for (j = 0; j < i; j++) {
			if (string_compare(arr[i].name, arr[j].name) == 0) {	//이전에 같은 이름의 물품이 있다면
				arr[j].price += arr[i].price;					//처음 금액에 현재 금액을 더해 처음 금액이 금액의 합계가 된다.
				break;
				}
		}
	}
	scanf("%s", input);

	for (i = 0; i < n; i++) {
		if (string_compare(arr[i].name, input) == 0) {			//입력받은 물건이 있을 경우
			printf("%d", arr[i].price);
			free(arr);
			return 0;											//나중에 입력받은 값은 금액의 합계가 아니기 때문에 처음 입력받은 값의 금액값을 출력하고 종료한다.			
		}
	}

	printf("0");
	free(arr);
	return 0;
}

//문자열을 비교하는 함수
//s2가 s1보다 크면 1; 작으면 -1; 같으면 0을 반환한다.
int string_compare(char s1[], char s2[]) {
	int i = 0;
	while (s1[i] != '\0' || s2[i] != '\0') {
		if (s1[i] > s2[i])
			return 1;
		else if (s1[i] < s2[i])
			return -1;
		else
			i++;
	}
	return 0;
}
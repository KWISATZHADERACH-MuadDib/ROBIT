#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	char arr[1000];
	//한글은 입력받지 못함
	int alpa[128] = { 0, };	//아스키 코드 33 ~ 126까지가 문자라서 128개까지 만듦 / 최다 등장 문자를 알아내기 위해 선언함

	int index = 0;
	int i = 0;
	int n;
	int max = 0;
	while (i < 999) {			//배열 오버플로우 방지
		scanf("%c", arr + i);	//%s로 받으면 띄어쓰기 이후 값을 입력받을 수 없기 때문에 %c로 입력받았다.
		if (*(arr + i) == '\n')		//enter가 입력될 때 입력 중단
			break;
		index = *(arr + i);
		*(alpa + index) += 1;			//문자가 등잘할 때 문자에 해당하는 인덱스에 있는 alpa[] 값을 1씩 증가시킨다.
		i++;
	}
	n = i;

	//'!'(33) 에서 '~'(126)까지
	for (i = '!'; i <= '~'; i++) {	
		if (*(alpa + i) > max)							//최다등장문자의 개수가 몇개인지 확인하는 작업
			max = *(alpa + i);
	}

	for (i = 0; i < n; i++) {
		printf("%c", *(arr + n - i - 1));				//n - 1 : 마지막 인덱스 , 마지막 인덱스에서부터 차례대로 출력하면 거꾸로 출력할 수 있다.
	}

	printf("\n최다등장문자 : ");

	for (i = '!'; i <= '~'; i++) {						//33 ~ 126까지
		if (*(alpa + i) == max)							//최다등장한 문자일 경우 출력
			printf("%c ", i);
	}


	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int input[12];
	int i = 0, j, k;
 
	while (i < 12) {				//입력이 반영되는 범위가 i < 12이기때문에 i가 12이상이 된다면 반복문을 중단한다.
		if (i == 0)
			printf("input : ");
		else
			printf("next input : ");
		scanf("%d", (input + i));	//배열 입력은 &arr[i] 인데 포인터에서 배열은 *(arr + 1)이므로 포인터를 이용해 입력받을 때에는 (input + i)를 사용하면 된다.
		k = 0;
		for (j = 0; j < 12; j++) {
			printf("%d", *(input + k));	// input의 k번째 값 출력
			if (k == i)					//k가 입력받은 값의 끝에 도달 했을 때 다시 0번째 input값을 가르키도록 초기화한다.
				k = 0;
			else
				k++;					//입력받은 값의 끝이 아닐 경우
			if (j % 4 == 3)				//3 * 4 도형이므로 4번째 수일때마다 줄바꿈을 해준다.
				printf("\n");
		}
		printf("\n");		
		i++;
	}
}

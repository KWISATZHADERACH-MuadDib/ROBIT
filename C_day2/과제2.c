#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sorting();		//선택정렬하는 함수
int compare();		//함수가 정렬이 완료되었는지 확인하는 함수

int arr[10];

int main() {
	int i;
	
	printf("입력\n\n");
	
	for (i = 0; i < 8; i++) {
		printf("%d : ", i);
		scanf("%d", &arr[i]);
	}

	sorting();				//선택정렬 함수 호출

	printf("\n출력\n\n");

	for (i = 0; i < 8; i++) {
		printf("%d : ", i);
		printf("%d\n", arr[i]);
	}

	return 0;
}

int sorting() {
	int max, sorted_index = 7,max_index = 0;		
	//sorted_index : 최대값을 배열 마지막과 교환하기 위한 인덱스
	int i;


	for (i = 0; i < 8; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");

	while (compare()) {							//정렬이 안료되지 않은 상태일때 실행
		max = arr[0];	
		max_index = 0;
		for (i = 1; i <= sorted_index; i++) {	//최댓값 찾기
			if (arr[i] > max) {
				max = arr[i];
				max_index = i;
			}
		}
		//최대값과 마지막 값 교환
		arr[max_index] = arr[sorted_index]; 
		arr[sorted_index] = max;

		for (i = 0; i < 8; i++) {
			printf("%d ", arr[i]);
		}
		sorted_index--;	// 마지막 배열 값은 정렬이 안료되어 있기 때문에
						// 정렬된 배열 전 인덱스에 다음 정렬된 값을 저장
						// 할 수 있도록 마지막 배연 인덱스를 1씩 감소시킨다.

		printf("\n");
	}

	return 0;
}

// 배열이 완전히 정렬되었을 때 정렬하는 반복문은 중지시키기 위한 함수
// 배열이 완전히 정렬되었는지 판단하고 정렬되지 않았다면 1, 정렬되었다면 0을 반환한다.
int compare() {	
	int i;							
	for (i = 1; i < 8; i++) {
		if (arr[i - 1] > arr[i])
			return 1;
	}
	return 0;
}

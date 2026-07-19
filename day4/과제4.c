#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {
	int i, j, k, N, B,cnt = 0, B_check = 0, low_check = 0, high_check = 0;		//N = 숫자 개수, B = 중앙값, pivot_index = 중앙값의 인덱스(기준)

	int arr[100];

	printf("N : ");
	scanf("%d", &N);
	printf("B : ");
	scanf("%d", &B);

	for (i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	for (i = 0; i < N; i += 2) {
		for (j = 0; j + i < N; j++) {
			B_check = 0;
			low_check = 0;
			high_check = 0;
			for (k = j; k <= i + j; k++) {
				if (arr[k] == B)
					B_check = 1;	//B가 포함되지 않는 경우 제외하기 위함 
				if (arr[k] > B)
					high_check++;
				if (arr[k] < B)
					low_check++;
			}
			if (high_check == low_check && B_check == 1)	//중앙 값을 찾기 위해 N보다 작은 값과 N보다 큰 값의 개수가 같은지 비교
				cnt++;
		}
		
	}
	
	printf("중앙값이 4인 부분수열의 개수 : %d", cnt);

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct _Student {
	int number;
	double grade;
	char name[20];
} Student;

// 함수 선언
int compare(Student arr[]);
int sorting(Student arr[]);
int switching(Student arr[], int a, int b);
int string_compare(char s1[], char s2[]);

int main() {
	Student arr[10] = { 0, };
	int i;

	for (i = 0; i < 5; i++) {
		scanf("%d %lf %s", &arr[i].number, &arr[i].grade, arr[i].name);
	}

	sorting(arr);

	printf("\n");

	for (i = 0; i < 5; i++) {
		printf("%d %.1lf %s\n", arr[i].number, arr[i].grade, arr[i].name);
	}

	return 0;
}

// 정렬하는 함수
int sorting(Student arr[]) {
	int i;

	while (compare(arr)) {
		for (i = 0; i < 4; i++) {
			// 1. 학년이 큰 경우
			if (arr[i].number > arr[i + 1].number) {
				switching(arr, i, i + 1);
			}
			// 2. 학년은 같지만 성적이 더 큰 경우
			else if (arr[i].number == arr[i + 1].number && arr[i].grade > arr[i + 1].grade) {
				switching(arr, i, i + 1);
			}
			// 3. 학년과 성적은 같지만 이름이 사전순으로 뒤인 경우
			else if (arr[i].number == arr[i + 1].number &&
				arr[i].grade == arr[i + 1].grade &&
				string_compare(arr[i].name, arr[i + 1].name) == 1) {
				switching(arr, i, i + 1);
			}
		}
	}
	return 0;
}

// 배열의 두 값을 바꾸는 함수 (구조체 대입 활용)
int switching(Student arr[], int a, int b) {
	Student temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
	return 0;
}

// 문자열 크기 비교 함수
int string_compare(char s1[], char s2[]) {
	int i = 0;
	while (s1[i] != '\0' || s2[i] != '\0') {
		if (s1[i] > s2[i])
			return 1;
		else if (s1[i] < s2[i])
			return -1;
		i++;
	}
	return 0;
}

// 정렬 완료 여부 확인 함수 (완료 시 0, 미완료 시 1)
int compare(Student arr[]) {
	int i;

	for (i = 0; i < 4; i++) {							//배열 인덱스가 4까지 있기 때문에 i가 4이면 i+1이 5가 되어 엉뚱한 값을 비교할수 있다. 그래서 i < 4까지만 반복했다.
		if (arr[i].number > arr[i + 1].number)
			return 1;
		if (arr[i].number == arr[i + 1].number) {
			if (arr[i].grade > arr[i + 1].grade)
				return 1;
			if (arr[i].grade == arr[i + 1].grade) {
				if (string_compare(arr[i].name, arr[i + 1].name) == 1)
					return 1;
			}
		}
	}
	return 0;
}
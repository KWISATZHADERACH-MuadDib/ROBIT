#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Adress {
	char country[30];				//나라
	char state[30];					//도
	char city[30];					//시
	char district[30];				//구
}Adress;

typedef struct _Student {
	int num;						//번호
	char name[20];					//이름
	Adress adress;					//주소
	double grade;					//성적
}Student;

// 함수 선언
int string_compare(char s1[], char s2[]);
int needSwap(Student a, Student b, char* key);
int compare(Student* arr, int size, char* key);
void switching(Student* arr, int a, int b);
void sorting(Student* arr, int size, char* key);
void print_arr(Student* arr, int size);
void searching(Student* arr, int* size);
void addDel(Student** arrPtr, int* size);
void save(Student* arr, int* size);
void load(Student** arrPtr, int* size);

int main() {
	Student* arr = NULL;   // 처음엔 학생이 0명이므로 NULL로 시작
	int size = 0;
	int mode;

	printf("=== 출석부 프로그램 ===\n");
	printf("1 <기준> : 정렬 (기준 = number/name/country/state/city/district/grade)\n");
	printf("2 <기준> <값> : 검색\n");
	printf("3 add/delete <번호> <이름> <나라> <도> <시> <구> <성적> : 추가/삭제\n");
	printf("4 save/load : 저장/불러오기\n");
	printf("0 : 종료\n\n");

	while (1) {
		scanf("%d", &mode);   // 입력이 끝나면 종료

		switch (mode) {
		case 0:
			printf("프로그램을 종료합니다.\n");
			free(arr);
			return 0;
		case 1: {
			char key[10];
			scanf("%s", key);
			sorting(arr, size, key);
			print_arr(arr, size);
			break;
		}
		case 2:
			searching(arr, &size);
			break;
		case 3:
			addDel(&arr, &size);
			break;
		case 4: {
			char sub[10];
			scanf("%s", sub);
			if (string_compare(sub, "save") == 0) {
				save(arr, &size);
				printf("저장했습니다.\n");
			}
			else if (string_compare(sub, "load") == 0) {
				load(&arr, &size);
			}
			else {
				printf("잘못된 형식입니다.\n");
			}
			break;
		}
		default:
			printf("잘못된 형식입니다.\n");
			continue;
		}
	}

	free(arr);
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

// key 기준으로 a가 b보다 뒤에 와야 하면(swap이 필요하면) 1을 반환
int needSwap(Student a, Student b, char* key) {
	if (string_compare(key, "number") == 0)
		return a.num > b.num;
	else if (string_compare(key, "name") == 0)
		return string_compare(a.name, b.name) == 1;
	else if (string_compare(key, "country") == 0)
		return string_compare(a.adress.country, b.adress.country) == 1;
	else if (string_compare(key, "state") == 0)
		return string_compare(a.adress.state, b.adress.state) == 1;
	else if (string_compare(key, "city") == 0)
		return string_compare(a.adress.city, b.adress.city) == 1;
	else if (string_compare(key, "district") == 0)
		return string_compare(a.adress.district, b.adress.district) == 1;
	else if (string_compare(key, "grade") == 0)
		return a.grade > b.grade;
	return 0;
}

// 배열이 key 기준으로 정렬 완료됐는지 확인 (정렬 안 됐으면 1, 됐으면 0)
int compare(Student* arr, int size, char* key) {
	for (int i = 0; i < size - 1; i++) {
		if (needSwap(arr[i], arr[i + 1], key))
			return 1;
	}
	return 0;
}

// 두 학생(구조체 전체)을 교환 - 구조체는 대입 한 번으로 통째로 복사되므로 char 배열도 안전하게 복사됨
void switching(Student* arr, int a, int b) {
	Student temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

// key 기준으로 정렬 (버블 정렬 방식)
void sorting(Student* arr, int size, char* key) {
	while (compare(arr, size, key)) {
		for (int i = 0; i < size - 1; i++) {
			if (needSwap(arr[i], arr[i + 1], key)) {
				switching(arr, i, i + 1);
			}
		}
	}
}

// 학생 목록 출력
void print_arr(Student* arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d %s %s %s %s %s %.1lf\n",
			arr[i].num, arr[i].name,
			arr[i].adress.country, arr[i].adress.state, arr[i].adress.city, arr[i].adress.district,
			arr[i].grade);
	}
	printf("\n");
}

//검색하는 함수
void searching(Student* arr, int* size) {
	int number;
	char command[10];
	char country[30];
	char state[30];
	char city[30];
	char district[30];
	double grade;

	scanf("%s", command);
	if (string_compare(command, "number") == 0) {
		scanf("%d", &number);
		for (int i = 0; i < *size; i++) {
			if (number == arr[i].num) {
				printf("%s\n", arr[i].name);
			}
		}
		printf("\n");
	}
	else if (string_compare(command, "country") == 0) {
		scanf("%s", country);
		for (int i = 0; i < *size; i++) {
			if (string_compare(country, arr[i].adress.country) == 0)
				printf("%s\n", arr[i].name);
		}
		printf("\n");
	}
	else if (string_compare(command, "state") == 0) {
		scanf("%s", state);
		for (int i = 0; i < *size; i++) {
			if (string_compare(state, arr[i].adress.state) == 0)
				printf("%s\n", arr[i].name);
		}
		printf("\n");
	}
	else if (string_compare(command, "city") == 0) {
		scanf("%s", city);
		for (int i = 0; i < *size; i++) {
			if (string_compare(city, arr[i].adress.city) == 0)
				printf("%s\n", arr[i].name);
		}
		printf("\n");
	}
	else if (string_compare(command, "district") == 0) {
		scanf("%s", district);
		for (int i = 0; i < *size; i++) {
			if (string_compare(district, arr[i].adress.district) == 0)
				printf("%s\n", arr[i].name);
		}
		printf("\n");
	}
	else if (string_compare(command, "grade") == 0) {
		scanf("%lf", &grade);
		for (int i = 0; i < *size; i++) {
			if (grade == arr[i].grade)
				printf("%s\n", arr[i].name);
		}
		printf("\n");
	}
	return;
}

//학생 정보를 추가하거나 제거하는 함수
void addDel(Student** arrPtr, int* size) {
	Student* arr = *arrPtr;
	Student input;
	char command[10];

	scanf("%s", command);
	scanf("%d %s %s %s %s %s %lf", &input.num, input.name, input.adress.country, input.adress.state, input.adress.city, input.adress.district, &input.grade);

	if (string_compare(command, "add") == 0) {
		for (int i = 0; i < *size; i++) {
			if (input.num == arr[i].num && string_compare(input.name, arr[i].name) == 0 && string_compare(input.adress.country, arr[i].adress.country) == 0 && string_compare(input.adress.state, arr[i].adress.state) == 0 &&
				string_compare(input.adress.city, arr[i].adress.city) == 0 && string_compare(input.adress.district, arr[i].adress.district) == 0 && input.grade == arr[i].grade) {
				return;
			}
		}
		(*size)++;
		arr = (Student*)realloc(arr, sizeof(Student) * (*size));
		arr[*size - 1] = input;
		*arrPtr = arr;
	}
	else if (string_compare(command, "delete") == 0) {
		int found = 0;
		for (int i = 0; i < *size; i++) {
			if (input.num == arr[i].num && string_compare(input.name, arr[i].name) == 0 && string_compare(input.adress.country, arr[i].adress.country) == 0 && string_compare(input.adress.state, arr[i].adress.state) == 0 &&
				string_compare(input.adress.city, arr[i].adress.city) == 0 && string_compare(input.adress.district, arr[i].adress.district) == 0 && input.grade == arr[i].grade) {
				for (int j = i; j < *size - 1; j++) {
					arr[j] = arr[j + 1];
				}
				found = 1;
				break;
			}
		}
		if (found) {
			(*size)--;
			arr = (Student*)realloc(arr, sizeof(Student) * (*size));
			*arrPtr = arr;
		}
	}
	else {
		printf("잘못된 형식입니다.\n");
	}
}

//출석부를 저장하는 함수
void save(Student* arr, int* size) {
	FILE* fp = fopen("attendance_register.txt", "w");
	if (fp == NULL) {
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	fprintf(fp, "%d\n", *size);

	for (int i = 0; i < *size; i++) {
		fprintf(fp, "%d %s %s %s %s %s %lf\n", arr[i].num, arr[i].name, arr[i].adress.country, arr[i].adress.state, arr[i].adress.city, arr[i].adress.district, arr[i].grade);
	}
	fclose(fp);
	return;
}

//출석부를 불러오는 함수
void load(Student** arrPtr, int* size) {
	FILE* fp = fopen("attendance_register.txt", "r");
	if (fp == NULL) {
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	int count;
	fscanf(fp, "%d", &count);

	Student* arr = (Student*)malloc(sizeof(Student) * count);

	for (int i = 0; i < count; i++) {
		fscanf(fp, "%d %s %s %s %s %s %lf",&arr[i].num, arr[i].name,arr[i].adress.country, arr[i].adress.state, arr[i].adress.city, arr[i].adress.district,	&arr[i].grade);
	}

	fclose(fp);

	free(*arrPtr);   // 기존 메모리는 해제하고 새로 불러온 것으로 교체
	*arrPtr = arr;
	*size = count;
	printf("%d명의 학생 정보를 불러왔습니다.\n", count);
	print_arr(arr, count);   // 불러온 내용을 바로 출력
	return;
}

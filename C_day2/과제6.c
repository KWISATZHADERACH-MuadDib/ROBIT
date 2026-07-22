#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int string_compare(char s1[], char s2[]);

char command[10];
char add[10] = "add";
char remove_[10] = "remove";
char check[10] = "check";
char toggle[10] = "toggle";
char all[10] = "all";
char empty[10] = "empty";

int compare();

int main() {
	int arr[25] = { 0, };			//숫자가 추가되어 있는지 아닌지 확인하기 위한 배열
	int aggregation[25] = { 0, };	//집합 (출력용)
	int num;
	int i, j;
	int index = 1;

	printf("연산을 선택하세요. (1 <= x <= 20)\n");
	printf("add X\n");
	printf("remove X\n");
	printf("check X\n");
	printf("toggle X\n");
	printf("all\n"); 
	printf("empty\n\n");

	while (1) {
		printf("input : ");
		scanf("%s %d", command, &num);

		if (string_compare(command, add)) {
			if (arr[num] == 0) {
				arr[num]++;
				aggregation[index] = num;
				index++;
			}
		}
		else if (string_compare(command, remove_)) {
			if (arr[num] == 1) {
				arr[num]--;
				for (i = 1; i < index; i++) {
					if (aggregation[i] == num) {
						aggregation[i] = 0;
						for (j = i; j < index; j++) {
							aggregation[j] = aggregation[j + 1];
						}
						index--;
					}
				}
			}
		}
		else if (string_compare(command, check)) {
			if (arr[num] == 1)
				printf("1 ");
			else
				printf("0 ");
		}
		else if (string_compare(command, toggle)) {
			if (arr[num] == 0) {
				arr[num] = 1;
				aggregation[index] = num;
				index++;
			}
			else {
				arr[num] = 0;
				for (i = 1; i < index; i++) {
					if (aggregation[i] == num) {
						aggregation[i] = 0;
						for (j = i; j < index; j++) {
							aggregation[j] = aggregation[j + 1];
						}
						index--;
					}
				}
			}
		}
		else if (string_compare(command, all) && num == 0) {
			for (i = 1; i <= 20; i++) {
				arr[i] = 1;
				aggregation[i] = i;
			}
			index = 21;
		}
		else if (string_compare(command, empty) && num == 0) {
			for (i = 1; i <= 20; i++) {
				arr[i] = 0;
				aggregation[i] = 0;
			}
			index = 1;
		}
		else
		{
			continue;
		}

		printf("집합 : {");
		for (i = 1; i < index; i++) {
			printf(" %d,", aggregation[i]);
		}
		printf(" }\n\n");
	}



	return 0;
}

int string_compare(char s1[], char s2[]) {
	int i = 0;
	while (s1[i] != '\0' || s2[i] != '\0') {
		if (s1[i] != s2[i])
			return 0;
		else
			i++;
	}
	return 1;
}

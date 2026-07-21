#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _DATE {
	int year, month, day;
} DATE;

typedef struct _TIME {
	int hour, min, sec;
} TIME;

typedef struct _Time {
	DATE Date;
	TIME time;
} TIMESTAMP;

int main() {
	int i, j;
	int cnt;

	int month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };				//월마다 일수가 다르고 규칙적이지 않기 때문에 따로 배열을 만들었다.
	TIME result;
	TIME sum[2];
	TIMESTAMP arr[2];

	for (i = 0; i < 2; i++) {
		scanf("%d %d %d %d %d %d", &arr[i].Date.year, &arr[i].Date.month, &arr[i].Date.day, &arr[i].time.hour, &arr[i].time.min, &arr[i].time.sec);
	}

	for (i = 0; i < 2; i++) {
		cnt = 0; // 매 회차마다 윤년 카운트 초기화
		sum[i].hour = 0;
		sum[i].min = 0;
		sum[i].sec = 0;

		// 지나간 연도(year - 1)까지의 윤년 개수 세기
		for (j = 1; j < arr[i].Date.year; j++) {
			if ((j % 4 == 0 && j % 100 != 0) || j % 400 == 0)
				cnt++;
		}

		//지나간 연도(year - 1)에 대해서만 연도 시간 계산
		sum[i].hour += (arr[i].Date.year - 1) * 8760 + cnt * 24;

		// 지나간 월에 대한 시간 계산
		for (j = 1; j < arr[i].Date.month; j++) {
			if (j == 2 && (((arr[i].Date.year % 4 == 0 && arr[i].Date.year % 100 != 0) || arr[i].Date.year % 400 == 0)))
				sum[i].hour += 29 * 24; // 윤년 2월은 29일
			else
				sum[i].hour += month[j - 1] * 24;
		}

		// 지나간 일수(day - 1)에 대해서만 일자 시간 계산
		sum[i].hour += (arr[i].Date.day - 1) * 24 + arr[i].time.hour;
		sum[i].min = arr[i].time.min;
		sum[i].sec = arr[i].time.sec;
	}

	// 시간 차이 계산 분기 단순화 (단순 뺄셈 후 보정)
	// 두 날짜 중 어느 쪽이 더 미래인지 판단하여 순서대로 뺌
	int first_is_later = 0;
	if (sum[0].hour > sum[1].hour)
		first_is_later = 1;
	else if (sum[0].hour == sum[1].hour && sum[0].min > sum[1].min)
		first_is_later = 1;
	else if (sum[0].hour == sum[1].hour && sum[0].min == sum[1].min && sum[0].sec >= sum[1].sec) 
		first_is_later = 1;

	if (first_is_later) {
		result.hour = sum[0].hour - sum[1].hour;
		result.min = sum[0].min - sum[1].min;
		result.sec = sum[0].sec - sum[1].sec;
	}
	else {
		result.hour = sum[1].hour - sum[0].hour;
		result.min = sum[1].min - sum[0].min;
		result.sec = sum[1].sec - sum[0].sec;
	}

	// 음수(내림) 보정
	if (result.sec < 0) {
		result.sec += 60;
		result.min--;
	}
	if (result.min < 0) {
		result.min += 60;
		result.hour--;
	}

	printf("%d시 %d분 %d초\n", result.hour, result.min, result.sec);

	return 0;
}
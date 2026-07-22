#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n1, n2, cnt = 1;
    int row_center, column_center;
    int dr, dc;     // dr: 중심 기준 행 방향 거리차이(위쪽 음수, 아래쪽 양수)
                    // dc: 중심 기준 열 방향 거리차이(왼쪽 음수, 오른쪽 양수)
    int i, j;

    scanf("%d %d", &n1, &n2);

    //2차원 배열 동적할당
    int** arr = (int**)malloc(sizeof(int*) * n1);
    for (i = 0; i < n1; i++)
        arr[i] = (int*)malloc(sizeof(int) * n2);

    for (i = 0; i < n1; i++)
        for (j = 0; j < n2; j++)
            arr[i][j] = 0;

    row_center = (n1 - 1) / 2;      // 중심 행 인덱스
    column_center = (n2 - 1) / 2;   // 중심 열 인덱스

    arr[row_center][column_center] = cnt++;   // 중심 = 1

    int maxM = row_center + column_center;    // 모서리까지의 최대 거리

    //중심 (row0, column0)을 기준으로 가까운 곳 부터 숫자를 채우는 규칙이다.

    for (i = 1; i <= maxM; i++) {
        for (j = 1; j <= i; j++) {   // 오른쪽 아래 대각선
            dr = j;
            dc = -i + j;
            if (dr >= -row_center && dr <= row_center && dc >= -column_center && dc <= column_center)
                arr[row_center + dr][column_center + dc] = cnt++;
        }
        for (j = 1; j <= i; j++) {   // 오른쪽 위 대각선
            dr = i - j; 
            dc = j;
            if (dr >= -row_center && dr <= row_center && dc >= -column_center && dc <= column_center)
                arr[row_center + dr][column_center + dc] = cnt++;
        }
        for (j = 1; j <= i; j++) {   // 왼쪽 위 대각선
            dr = -j;
            dc = i - j;
            if (dr >= -row_center && dr <= row_center && dc >= -column_center && dc <= column_center)
                arr[row_center + dr][column_center + dc] = cnt++;
        }
        for (j = 1; j <= i; j++) {   // 왼쪽 아래 대각선
            dr = -i + j;
            dc = -j;
            if (dr >= -row_center && dr <= row_center && dc >= -column_center && dc <= column_center)
                arr[row_center + dr][column_center + dc] = cnt++;
        }
    }

    for (i = 0; i < n1; i++) {
        for (j = 0; j < n2; j++)
            printf("%3d", arr[i][j]);
        printf("\n");
    }

    for (i = 0; i < n1; i++) free(arr[i]);
    free(arr);
    return 0;
}

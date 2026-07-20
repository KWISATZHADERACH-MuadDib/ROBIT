#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, n, cnt = 1;
    int x = 0, y = 0;
    scanf("%d", &n);

    //2차원 배열 동적 할당
    int** arr = (int**)malloc(sizeof(int*) * n);
    for (i = 0; i < n; i++) {
        arr[i] = (int*)malloc(sizeof(int) * n);
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            arr[i][j] = 0;
    //대각선 아래로 내려갈 경우 x좌표와 y좌표의 합이 같다는 것을 이용했다. 예를 들어 (1, 0)과 (0,1)의 좌표합은 1이다.
    for (i = 0; i < 2 * n - 1; i++) {
        if (i >= n) {                       // i > n일때 중간 대각선 이후일 때, 즉 x + y가 n를 초과하였을 때
            x = n - 1;
            y = i - n + 1;
            for (j = 0; j <= 2 * n - 2 - i; j++) {  // j <= 2*n - 1 - i 일때
                arr[y + j][x - j] = cnt;
                cnt++;
            }
        }                                   //x + y가 n이하일 때
        else {
            x = i;
            y = 0;
            for (j = 0; j <= i; j++) {
                arr[y + j][x - j] = cnt;
                cnt++;
            }
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d", arr[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < n; i++) free(arr[i]);
    free(arr);

    return 0;
}
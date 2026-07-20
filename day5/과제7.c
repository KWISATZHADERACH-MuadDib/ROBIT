#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//string의 길이 반환
int my_strlen(char* s) {
    int n = 0;
    while (s[n] != '\0')
        n++;
    return n;
}

//문자열이 같은지 확인하는 함수
//같은면 1 다르면 0 반환
int my_streq(char* a, char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

int main() {
    char* input = (char*)malloc(sizeof(char) * 10001);
    scanf("%10000s", input);        //버퍼 크기 제한


    int capacity = 4;
    int top = 0;                       // 현재 스택에 쌓인 태그 개수 (= 현재 깊이)
    char** stack = (char**)malloc(sizeof(char*) * capacity);    //stack 배열 동적 할당

    int len = my_strlen(input);
    int i = 0;
    int error = 0;

    while (i < len && !error) {
        if (input[i] == '<') {
            int j = i + 1;
            while (j < len && input[j] != '>') 
                j++;
            if (j >= len) {   // '>' 를 못 찾음 -> 잘못된 태그
                error = 1;
                break;
            }

            int tagLen = j - (i + 1);
            char* tag = (char*)malloc(sizeof(char) * (tagLen + 1));         //문자열 마지막을 확인하기 위해 \0을 입력받으려고 taglen + 1의 길이로 배열을 만듦
            for (int k = 0; k < tagLen; k++)
                tag[k] = input[i + 1 + k];
            tag[tagLen] = '\0';

            if (tag[0] == '/') {
                // 닫는 태그: 스택 top 과 이름이 같은지 확인
                // 마지막에 열린태그와 지금 닫는 태그가 일치해야 하기 때문
                char* name = tag + 1;
                if (top == 0 || !my_streq(stack[top - 1], name)) {
                    error = 1;
                    free(tag);
                    break;
                }
                free(stack[top - 1]);
                top--;                          // 먼저 pop // 맨위 태그를 없애야 이전에 열린 태그와 그 다음 닫는 태그를 비교할 수 있다.
                printf("%*s</%s>\n", top * 4, "", name);  // 줄어든 깊이로 출력
            }
            else {
                // 여는 태그: 현재 깊이(top)로 출력 후 push
                printf("%*s<%s>\n", top * 4, "", tag);

                if (top >= capacity) {          // 용량 부족하면 재할당
                    capacity *= 2;                  //용량 부족시 2배로 재할당한다.
                    stack = (char**)realloc(stack, sizeof(char*) * capacity);
                }
                stack[top] = tag;               // push (tag 메모리는 스택이 소유)
                top++;
            }
            i = j + 1;
        }
        else {
            // 텍스트 노드: 다음 '<' 전까지 읽기
            int j = i;
            while (j < len && input[j] != '<') j++;
            printf("%*s%.*s\n", top * 4, "", j - i, input + i);
            i = j;
        }
    }

    if (top != 0) 
        error = 1;   // 끝났는데 안 닫힌 태그가 남아있으면 오류

    if (error) {
        printf("오류: 잘못된 태그 구조입니다.\n");
    }

    for (int k = 0; k < top; k++) free(stack[k]);
    free(stack);
    free(input);
    return 0;
}
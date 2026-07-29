#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int data;
	struct _Node* next;
}Node;

typedef struct _Stack {
	Node* top;
	int size;
}Stack;

Stack stack;

int string_compare(char s1[], char s2[]);
void push();		//정수 num push
void pop();				//stack이 비어있으면 0반환, 아니면 pop하고 1반환
void size();			//stack의 크기 출력
int top(int* success);				//top에 위치한 값 반환
int isEmpty();			//stack에 데이터 없으면 1, 있으면 0 반환
void printStack();		//stack 내 모든 값 출력, stack이 비어있을 시 비어있다고 출력
Node* create_node(int data);

int main() {
	int result;
	char command[20];

	//stack 초기화
	stack.top = NULL;
	stack.size = 0;

	while (1) {
		scanf("%s", command);

		if (string_compare(command, "push") == 0) {
			push();
		}
		else if (string_compare(command, "pop") == 0) {
			pop();
		}
		else if (string_compare(command, "size") == 0) {
			size();
		}
		else if (string_compare(command, "top") == 0) {
			int ok;
			result = top(&ok);
			if (ok)
				printf("%d\n", result);
		}
		else if (string_compare(command, "isEmpty") == 0) {
			result = isEmpty();
			if (result == 1)
				printf("stack이 비어있습니다\n");
			else
				printf("stack이 비어있지 않습니다\n");
		}
		else if (string_compare(command, "printStack") == 0) {
			printStack();
		}
		else if (string_compare(command, "exit") == 0) {
			break;
		}
		else {
			printf("잘못된 입력입니다\n");
		}
	}

	return 0;
}

int string_compare(char s1[], char s2[]) {
	int i = 0;
	while (s1[i] != '\0' || s2[i] != '\0') {
		if (s1[i] > s2[i])
			return 1;
		else if (s1[i] < s2[i])
			return -1;
		else
			i++;
	}
	return 0;
}

//새로운 노드 생성 함수
Node* create_node(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = stack.top;
	return newNode;
}


void push() {
	int data;
	scanf("%d", &data);

	Node* newNode = create_node(data);

	
	stack.top = newNode;	//top을 새로운 노드로 재설정함

	stack.size++;
	printf("%d를 stack에 삽입했습니다.\n", data);
	return;
}

void pop() {
	if (stack.top == NULL) {
		printf("stack이 비어있습니다");
		return;
	}
	else {
		Node* cur = stack.top;
		Node* nextNode = cur->next;					//top을 이전 노드로 바꾸기 위해 next값을 미리 저장한다. free()하면 top의 데이터가 없어지기 때문
		printf("%d를 pop했습니다.", stack.top->data);
		free(stack.top);
		stack.top = nextNode;						//top이 기존 top의 직전 node가 된다.	
	}

	stack.size--;
	return;
}

//stack 길이 출력
void size() {
	printf("stack의 길이 : %d\n", stack.size);
	return;
}

int top(int* success) {
	if (stack.top == NULL) {
		printf("stack이 비어있습니다");
		*success = 0;			//push -1하고 top을 하면 top값이 -1이라 출력되지 않는 문제 발생 
		return -1;				//그래서 success라는 포인터 변수로 비어있는지 아닌지 결과를 확인할 수 있게 하였다.
	}
	*success = 1;
	return stack.top->data;		//top 값 반환
}

//stack에 데이터가 없으면 1, 있으면 0 반환
int isEmpty() {
	if (stack.size != 0)
		return 0;
	else
		return 1;
}

void printStack() {
	if (stack.top == NULL) {
		printf("리스트가 비어있습니다\n");
		return;
	}
	Node* cur = stack.top;
	while (cur != NULL) {
		printf("%d ", cur->data);		//이전의 노드로 가면서 노드의 data를 출력
		cur = cur->next;
	}
	printf("\n");
	return;
}
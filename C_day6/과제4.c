#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	char data;
	struct _Node* next;
}Node;

typedef struct _Queue {
	Node* front;
	Node* rear;
	int size;
}Queue;

typedef struct _Stack {
	Node* top;
	int size;
}Stack;

Queue queue;
Stack stack;

void push(char alpa);		//문자 char alpa 추가
void pop();	
int top(int* success);		//top에 위치한 값 반환
void enqueue(char alpa);	//문자 char alpa 추가
void dequeue();	
char front(int* success);	//front에 위치한 값 반환

int main() {
	char alpa = 0;
	char q, s;
	int i, size, result, ok;
	while (1) {
		scanf("%c", &alpa);
		if (alpa == '\n')	// '\n'이 queue와 stack에 입력되는 것을 막기 위해 break;
			break;
		if (alpa == ' ')	//공백 무시 (회문은 공백을 무시한 문자열이 대칭인것을 말하기 때문)
			continue;
		push(alpa);
		enqueue(alpa);
	}
	size = queue.size;

	for (i = 0; i < size; i++) {
		result = top(&ok);
		if (ok) {
			s = result;
		}
		result = front(&ok);
		if (ok) {
			q = result;
		}
		if (q != s) {
			printf("not Palindraome");
			return 0;
		}
		else {
			pop();
			dequeue();
		}
	}

	printf("Palindraome");
	return 0;
}

//새로운 stack 노드 생성 함수
Node* create_stack_node(char data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//새로운 queue 노드 생성 함수
Node* create_queue_node(char data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void push(char alpa) {

	Node* newNode = create_stack_node(alpa);

	newNode->next = stack.top;	//새 node가 기존 top을 가리키게 연결
	stack.top = newNode;	//top을 새로운 노드로 재설정함

	stack.size++;
	return;
}

void enqueue(char alpa) {
	Node* newNode = create_queue_node(alpa);

	if (queue.rear == NULL) {	//queue가 비어있으면 front도 새노드로 추가
		queue.front = newNode;
		queue.rear = newNode;
	}
	else {
		queue.rear->next = newNode;	//아니면 기존 node에 추가
	}
	queue.rear = newNode;

	queue.size++;
	return;
}

void pop() {
	if (stack.top == NULL) {
		return;
	}
	else {
		Node* cur = stack.top;
		Node* nextNode = cur->next;					//top을 이전 노드로 바꾸기 위해 next값을 미리 저장한다. free()하면 top의 데이터가 없어지기 때문
		free(stack.top);
		stack.top = nextNode;						//top이 기존 top의 직전 node가 된다.	
	}

	stack.size--;
	return;
}

void dequeue() {
	if (queue.front == NULL) {						//queue에 값이 아무것도 없는 경우 종료	
		return;
	}
	else {
		Node* cur = queue.front;
		Node* nextNode = cur->next;					//rear을 이전 노드로 바꾸기 위해 next값을 미리 저장한다. free()하면 rear의 데이터가 없어지기 때문
		free(queue.front);
		queue.front = nextNode;						//rear이 기존 rear의 직전 node가 된다.	
		if (queue.front == NULL)
			queue.rear = NULL;
	}

	queue.size--;
	return;
}

int top(int* success) {
	if (stack.top == NULL) {
		*success = 0;			//push -1하고 top을 하면 top값이 -1이라 출력되지 않는 문제 발생 
		return -1;				//그래서 success라는 포인터 변수로 비어있는지 아닌지 결과를 확인할 수 있게 하였다.
	}
	*success = 1;
	return stack.top->data;		//top 값 반환
}

char front(int* success) {
	if (queue.front == NULL) {
		*success = 0;			//push -1하고 top을 하면 top값이 -1이라 출력되지 않는 문제 발생 
		return -1;				//그래서 success라는 포인터 변수로 비어있는지 아닌지 결과를 확인할 수 있게 하였다.
	}
	*success = 1;
	return queue.front->data;	//front 값 반환
}
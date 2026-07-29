#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int data;
	struct _Node* next;
}Node;

typedef struct _Queue {
	Node* front;
	Node* rear;
	int size;
}Queue;

Queue queue;

int string_compare(char s1[], char s2[]);

void enqueue();				//정수 num enqueue
void dequeue();				//queue가 비어있으면 0반환, 아니면 dequeue하고 1반환
void size();				//queue의 크기 출력
int front(int* success);	//front에 위치한 값 반환
int rear(int* success);		//rear에 위치한 값 반환
int isEmpty();				//queue에 데이터 없으면 1, 있으면 0 반환
void printQueue();			//queue 내 모든 값 출력, queue이 비어있을 시 비어있다고 출력

Node* create_node(int data);

int main() {
	int num;
	int result;
	char command[20];

	//queue 초기화
	queue.front = NULL;
	queue.rear = NULL;
	queue.size = 0;

	while (1) {
		scanf("%s", command);

		if (string_compare(command, "enqueue") == 0) {
			enqueue();
		}
		else if (string_compare(command, "dequeue") == 0) {
			dequeue();
		}
		else if (string_compare(command, "size") == 0) {
			size();
		}

		else if (string_compare(command, "rear") == 0) {
			int ok;
			result = rear(&ok);
			if (ok)
				printf("%d\n", result);
		}
		else if (string_compare(command, "front") == 0) {
			int ok;
			result = front(&ok);
			if (ok)
				printf("%d\n", result);
		}
		else if (string_compare(command, "isEmpty") == 0) {
			result = isEmpty();
			if (result == 1)
				printf("queue가 비어있습니다\n");
			else
				printf("queue가 비어있지 않습니다\n");
		}
		else if (string_compare(command, "printQueue") == 0) {
			printQueue();
		}
		else if (string_compare(command, "exit") == 0) {
			break;
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
	newNode->next = NULL;
	return newNode;
}


void enqueue() {
	int data;
	scanf("%d", &data);

	Node* newNode = create_node(data);

	if (queue.rear == NULL) {	//queue가 비어있으면 front도 새노드로 추가
		queue.front = newNode;
		queue.rear = newNode;
	}
	else {
		queue.rear->next = newNode;	//아니면 기존 node에 추가
	}
	queue.rear = newNode;

	queue.size++;
	printf("%d를 queue에 삽입했습니다.\n", data);
	return;
}

void dequeue() {
	if (queue.front == NULL) {
		printf("queue가 비어있습니다");
		return;
	}
	else {
		Node* cur = queue.front;
		Node* nextNode = cur->next;					//rear을 이전 노드로 바꾸기 위해 next값을 미리 저장한다. free()하면 rear의 데이터가 없어지기 때문
		printf("%d를 dequeue했습니다.", queue.front->data);
		free(queue.front);
		queue.front = nextNode;						//rear이 기존 rear의 직전 node가 된다.	
		if (queue.front == NULL)
			queue.rear = NULL;
	}

	queue.size--;
	return;
}

//queue 길이 출력
void size() {
	printf("queue의 길이 : %d\n", queue.size);
	return;
}

int rear(int* success) {
	if (queue.rear == NULL) {
		printf("queue가 비어있습니다.\n");
		*success = 0;			//enqueue -1하고 rear을 하면 rear값이 -1이라 출력되지 않는 문제 발생 
		return -1;				//그래서 success라는 포인터 변수로 비어있는지 아닌지 결과를 확인할 수 있게 하였다.
	}
	*success = 1;
	return queue.rear->data;		//rear 값 반환
}

int front(int* success) {
	if (queue.front == NULL) {
		printf("queue가 비어있습니다.\n");
		*success = 0;
		return -1;
	}
	*success = 1;
	return queue.front->data;		//front 값 반환
}

//queue에 데이터가 없으면 1, 있으면 0 반환
int isEmpty() {
	if (queue.size != 0)
		return 0;
	else
		return 1;
}

void printQueue() {
	if (queue.front == NULL) {
		printf("리스트가 비어있습니다\n");
		return;
	}
	Node* cur = queue.front;
	while (cur != NULL) {
		printf("%d ", cur->data);		//이전의 노드로 가면서 노드의 data를 출력
		cur = cur->next;
	}
	printf("\n");
	return;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int data;
	struct _Node* next;
}Node;

typedef struct _LinkedList {
	Node* head;
	Node* tail;
	Node* Cur;
	int size;
}LinkedList;

//data 자료형은 int

LinkedList list;   // 전역 리스트 하나만 사용

int insert();			//원하는 위치에 node 추가
int insert_back();		//연결리스트의 맨 끝에 node 추가
int insert_first();		//연결리스트의 맨 처음에 node 추가

int delete();			//원하는 요소 삭제
int delete_first();		//연결리스트 맨 처음 node 삭제
int delete_back();		//연결리스트 맨 마지막 node 삭제

int get_entry();		//요소 찾기

int get_length();		//리스트 전체 길이 반환
int print_list();		//리스트 모든 요소 출력

int reverse();			//리스트 역순으로 만들기

int string_compare(char s1[], char s2[]);			//입력받은 문자열 비교하는 함수
Node* create_node(int data);						//노드 생성 함수

int main() {
	char command[20];

	//리스트 초기화
	list.head = NULL;
	list.tail = NULL;
	list.Cur = NULL;
	list.size = 0;

	while (1) {
		scanf("%s", command);

		if (string_compare(command, "insert") == 0) {
			insert();
		}
		else if (string_compare(command, "insert_back") == 0) {
			insert_back();
		}
		else if (string_compare(command, "insert_first") == 0) {
			insert_first();
		}
		else if (string_compare(command, "delete") == 0) {
			delete();
		}
		else if (string_compare(command, "delete_first") == 0) {
			delete_first();
		}
		else if (string_compare(command, "delete_back") == 0) {
			delete_back();
		}
		else if (string_compare(command, "get_entry") == 0) {
			get_entry();
		}
		else if (string_compare(command, "get_length") == 0) {
			get_length();
		}
		else if (string_compare(command, "print_list") == 0) {
			print_list();
		}
		else if (string_compare(command, "reverse") == 0) {
			reverse();
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

//크면 1반환, 작으면 -1반환, 같으면 0 반환
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

//새 노드 하나 생성
Node* create_node(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// insert_first: 맨 처음에 노드 추가
// 입력형식: insert_first <data>
int insert_first() {
	int data;
	scanf("%d", &data);

	Node* newNode = create_node(data);
	newNode->next = list.head;
	list.head = newNode;

	if (list.tail == NULL) {   // 리스트가 비어있던 경우
		list.tail = newNode;
	}

	list.size++;				//새로운 노드가 생성 되었으므로 size를 1 증가시킨다
	printf("%d를 맨 앞에 삽입했습니다\n", data);
	return 0;
}

// insert_back: 맨 끝에 노드 추가
// 입력형식: insert_back <data>
int insert_back() {
	int data;
	scanf("%d", &data);

	Node* newNode = create_node(data);

	if (list.head == NULL) {   // 리스트가 비어있던 경우
		list.head = newNode;
		list.tail = newNode;
	}
	else {
		list.tail->next = newNode;
		list.tail = newNode;
	}

	list.size++;				//새로운 노드가 생성 되었으므로 size를 1 증가시킨다
	printf("%d를 맨 뒤에 삽입했습니다\n", data);
	return 0;
}

// insert: 원하는 위치에 노드 추가 (index 또는 이전 data 값 기준)
// 입력형식:
//   insert index <index> <data>   -> index번째 위치에 data를 삽입 (0부터 시작)
//   insert data <targetData> <newData> -> targetData를 가진 노드 뒤에 newData 삽입
int insert() {
	char mode[10];
	scanf("%s", mode);

	if (string_compare(mode, "index") == 0) {
		int index, data;
		scanf("%d %d", &index, &data);

		if (index < 0 || index > list.size) {
			printf("잘못된 인덱스입니다\n");
			return -1;
		}

		if (index == 0) {
			// 맨 앞 삽입과 동일
			Node* newNode = create_node(data);
			newNode->next = list.head;
			list.head = newNode;
			if (list.tail == NULL) list.tail = newNode;
			list.size++;			//새로운 노드가 생성 되었으므로 size를 1 증가시킨다
		}
		else {
			Node* prev = list.head;
			for (int i = 0; i < index - 1; i++) {
				prev = prev->next;
			}
			Node* newNode = create_node(data);
			newNode->next = prev->next;
			prev->next = newNode;
			if (newNode->next == NULL) {
				list.tail = newNode;
			}
			list.size++;			//새로운 노드가 생성 되었으므로 size를 1 증가시킨다
		}
		printf("index %d 위치에 %d를 삽입했습니다\n", index, data);
	}
	else if (string_compare(mode, "data") == 0) {
		int targetData, newData;
		scanf("%d %d", &targetData, &newData);

		Node* cur = list.head;
		while (cur != NULL && cur->data != targetData) {
			cur = cur->next;
		}

		if (cur == NULL) {
			printf("해당 data를 가진 노드를 찾을 수 없습니다\n");
			return -1;
		}

		Node* newNode = create_node(newData);
		newNode->next = cur->next;
		cur->next = newNode;
		if (newNode->next == NULL) {
			list.tail = newNode;
		}
		list.size++;
		printf("data %d 뒤에 %d를 삽입했습니다\n", targetData, newData);
	}
	else {
		printf("잘못된 모드입니다 (index 또는 data)\n");
		return -1;
	}
	return 0;
}

// delete_first: 맨 처음 노드 삭제
int delete_first() {
	if (list.head == NULL) {
		printf("리스트가 비어있습니다\n");
		return -1;
	}

	Node* target = list.head;
	list.head = list.head->next;
	if (list.head == NULL) {
		list.tail = NULL;   // 노드가 하나였던 경우
	}

	printf("%d를 맨 앞에서 삭제했습니다\n", target->data);
	free(target);
	list.size--;			//새로운 노드가 삭제 되었으므로 size를 1 감소시킨다ㅌ
	return 0;
}

// delete_back: 맨 마지막 노드 삭제
int delete_back() {
	if (list.head == NULL) {
		printf("리스트가 비어있습니다\n");
		return -1;
	}

	if (list.head == list.tail) {   // 노드가 하나뿐인 경우
		printf("%d를 맨 뒤에서 삭제했습니다\n", list.tail->data);
		free(list.head);
		list.head = NULL;
		list.tail = NULL;
	}
	else {
		Node* cur = list.head;
		while (cur->next != list.tail) {
			cur = cur->next;
		}
		printf("%d를 맨 뒤에서 삭제했습니다\n", list.tail->data);
		free(list.tail);
		list.tail = cur;
		list.tail->next = NULL;
	}

	list.size--;			//새로운 노드가 삭제 되었으므로 size를 1 감소시킨다
	return 0;
}

// delete: 원하는 요소 삭제 (index 또는 data 값 기준)
// 입력형식:
//   delete index <index>
//   delete data <targetData>
int delete() {
	char mode[10];
	scanf("%s", mode);

	if (list.head == NULL) {
		printf("리스트가 비어있습니다\n");
		// 그래도 인자는 읽어서 버려줘야 함
		int dummy;
		scanf("%d", &dummy);
		return -1;
	}

	if (string_compare(mode, "index") == 0) {
		int index;
		scanf("%d", &index);

		if (index < 0 || index >= list.size) {
			printf("잘못된 인덱스입니다\n");
			return -1;
		}

		if (index == 0) {
			delete_first();
		}
		else {
			Node* prev = list.head;
			for (int i = 0; i < index - 1; i++) {
				prev = prev->next;
			}
			Node* target = prev->next;
			prev->next = target->next;
			if (target == list.tail) {
				list.tail = prev;
			}
			printf("index %d의 %d를 삭제했습니다\n", index, target->data);
			free(target);
			list.size--;			//새로운 노드가 삭제 되었으므로 size를 1 감소시킨다
		}
	}
	else if (string_compare(mode, "data") == 0) {
		int targetData;
		scanf("%d", &targetData);

		if (list.head->data == targetData) {
			delete_first();
			return 0;
		}

		Node* prev = list.head;
		Node* cur = list.head->next;
		while (cur != NULL && cur->data != targetData) {
			prev = cur;
			cur = cur->next;
		}

		if (cur == NULL) {
			printf("해당 data를 가진 노드를 찾을 수 없습니다\n");
			return -1;
		}

		prev->next = cur->next;
		if (cur == list.tail) {
			list.tail = prev;
		}
		printf("data %d를 삭제했습니다\n", targetData);
		free(cur);
		list.size--;			//새로운 노드가 삭제 되었으므로 size를 1 감소시킨다	
	}
	else {
		printf("잘못된 모드입니다 (index 또는 data)\n");
		return -1;
	}
	return 0;
}

// get_entry: 요소 찾기
// 입력형식:
//   get_entry index <index>   -> 해당 index의 data 출력
//   get_entry data <targetData> -> 해당 data를 가진 첫 노드의 index 출력
int get_entry() {
	char mode[10];
	scanf("%s", mode);

	if (string_compare(mode, "index") == 0) {
		int index;
		scanf("%d", &index);

		if (index < 0 || index >= list.size) {
			printf("잘못된 인덱스입니다\n");
			return -1;
		}

		Node* cur = list.head;
		for (int i = 0; i < index; i++) {
			cur = cur->next;
		}
		printf("index %d의 data는 %d입니다\n", index, cur->data);
	}
	else if (string_compare(mode, "data") == 0) {
		int targetData;
		scanf("%d", &targetData);

		Node* cur = list.head;
		int index = 0;
		while (cur != NULL && cur->data != targetData) {
			cur = cur->next;
			index++;
		}

		if (cur == NULL) {
			printf("해당 data를 가진 노드를 찾을 수 없습니다\n");
			return -1;
		}
		printf("data %d의 index는 %d입니다\n", targetData, index);
	}
	else {
		printf("잘못된 모드입니다 (index 또는 data)\n");
		return -1;
	}
	return 0;
}

// get_length: 리스트 전체 길이 반환
int get_length() {
	printf("리스트의 길이: %d\n", list.size);
	return list.size;
}

// print_list: 리스트 모든 요소 출력
int print_list() {
	if (list.head == NULL) {
		printf("리스트가 비어있습니다\n");
		return -1;
	}

	Node* cur = list.head;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
	return 0;
}

// reverse: 리스트 역순으로 만들기
int reverse() {
	Node* prev = NULL;
	Node* cur = list.head;
	Node* next = NULL;

	list.tail = list.head;   // 기존 head가 새로운 tail이 됨

	while (cur != NULL) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	list.head = prev;   // 기존 tail이 새로운 head가 됨
	printf("리스트를 역순으로 만들었습니다\n");
	return 0;
}
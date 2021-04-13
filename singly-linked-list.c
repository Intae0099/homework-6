/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); 
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 메모리 할당하여 새거 추가
	node->key = key; //키를 노드의 키에 넣는다

	node->link = h->first; // 노드의 링크에 h의 first를 넣는다
	h->first = node; //h의 first에 node 를 넣는다.

	return 0; //0리턴을 통한 insertFirst함수 종료
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* p; //현재 노드
	listNode* temp; //임시 이전 노드
	listNode* newNode = (listNode*)malloc(sizeof(listNode)); //새 노드 메모리 할당
	newNode-> key = key; //새 노드의 key 에 key를 넣는다
	newNode->link = NULL; //새노드의 링크에 NULL을 넣는다
	p = h->first; //h의first를 p에 불러온다
	temp = p; //임시 이전 노드를 p로 설정해 놓는다.

	if(h->first == NULL) //노드가 하나도 없는경우
	{
		h->first = newNode; //맨앞 노드에 newNode로 만든다
	}
	else //노드가 하나 이상 있는 경우
	{	
		if(p->key > newNode->key) //p의 key가 newNode의 key보다 크면
		{
			h->first = newNode; //첫번째 노드에 newNode를 설정한다
			newNode->link = p;	//newnode의 링크는 p로 설정해 놓는다.
		}
		else //그렇지 않는 경우
		{
			while(p !=NULL && p->key < newNode->key) //p가 NULL이 아니고 p의 키가 newNode의 키보다 작을시 반복문 탈출
			{
				temp = p; //임시 이전 노드를 p로 설정하고
				p = p->link; //p를 p의 link를 타고 다음 노드로 간다
			}
			if(p !=NULL) //p가 NULL 이 아닐시
			{	
				temp->link = newNode; //이전노드의 링크를 newNode로 설정한다
				newNode ->link = p; //newNode의 link를 p로 설정한다
			}
			else //p가 NULL 일 경우 다음 노드는 없으며
			{
				temp->link = newNode; //이전 노드인 temp의 link를 newNode로 설정한다.
			}
		}
	}
	
	return 0; //0리턴을 통한 insertNode함수 종료
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	
	listNode* p; //현재노드
	listNode* temp; //임시 이전 노드
	listNode* newNode = (listNode*)malloc(sizeof(listNode)); //새 노드 메모리 할당

	p = h->first; //h의first를 p에 불러온다
	while(p !=NULL) //p가 NULL이 아닐때 반복문 탈출
	{	
		temp = p; //임시 이전 노드를 p로 설정한다
		p = p->link; //p를 p의 link를 타고 다음 노드로 간다
	}

	temp->link = newNode; //임시 이전 노드의 link에 newNode로 설정한다
	newNode->key = key; //newNode의 key에 key를 넣는다
	newNode->link = NULL; //newNode가 마지막 노드이므로 newNode의 link에 NULL을 넣는다.

	return 0; //0리턴을 통한 insertLast함수 종료
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* p; //현재노드
	p = h->first;  //h의first를 p에 불러온다
	if(h->first != NULL) //h의 first가 NULL이 아니면
	{
		h->first = p->link; //h의 first에 p의 다음 노드인 p의 링크를 넣는다
	}
	free(p); //p의 메모리 할당 해제를 통한 p노드 삭제

	return 0; //0리턴을 통한 deleteFirst함수 종료
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* p; //현재노드 
	listNode* temp; //임시 이전 노드

	p = h->first;  //h의first를 p에 불러온다
	
	if(p->key == key) //p의 key가 key일경우
	{	
		h->first = p->link; //h의 first에 p의 다음 노드인 p의 링크를 넣는다
		free(p); //p의 메모리 할당 해제를 통한 p노드 삭제
		return 0; //0리턴을 통한 deleteNode함수 종료
	}
	else //아닐경우 
	{	
		temp = p; //이전 노드를 p로 설정
		p = p->link; //p를 p의link를 타고가 다음 노드로 간다
		while(p != NULL && p->key != key) //p가 NULL이 아니고 p의 key가 key가 아닐때 반복문 탈출
		{
			temp = p; //이전 노드를 p로 설정
			p = p->link; //p를 p의link를 타고가 다음 노드로 간다
		}
		temp->link = p->link; //이전 노드의 link를 p의 다음 노드인 p의 link로 설정한다
		free(p); //p의 메모리 할당 해제를 통한 p노드 삭제
		return 0; //0리턴을 통한 deleteNode함수 종료
	}		 
	return 0; //0리턴을 통한 deleteNode함수 종료

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* p; //현재노드 
	listNode* temp; //임시 이전 노드

	p = h->first;  //h의first를 p에 불러온다
	temp = p; //이전 노드를 p로 설정
	while(p !=NULL) //p가 NULL이 아닐때 반복문 탈출
	{	
		if(p->link == NULL) //p의 link 가 NULL일경우, p의 다음노드가 없을때
		{
			temp ->link = NULL; //이전 노드의 link를 NULL로 바꾼뒤
			free(p); //p의 메모리 할당 해제를 통한 p노드 삭제
			break; //반복문 탈출
		}
		temp = p; //이전 노드를 p로 설정
		p = p->link; //p를 p의link를 타고가 다음 노드로 간다
	}
	
	return 0; //0리턴을 통한 deleteLast함수 종료
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode *middle; //중간 노드
	listNode *trail; //뒤 노드
	listNode *lead; //앞 노드

	lead = h->first; //h의first를 lead에 불러온다
	middle = NULL; //middle를 NULL로 설정한다

	while(lead != NULL) //lead가 NULL일때 반복문 탈출
	{
		trail = middle; //trail을 중간노드로 둔다
		middle = lead; //중간 노드는 앞의 노드로 바꾼다
		lead = lead->link; //앞 노드는 앞노드의 link를 타고 다음노드로 간다
		middle->link = trail; //중간노드의 link는 trail로 바꿈으로서 link를 역순으로 설정
	}

	h->first = middle; //lead는 NULL로 바뀌었기 때문에 첫번째 노드는 lead의 이전 노드인 middle로 설정한다.

	return 0; //0리턴을 통한 invertList함수 종료
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}



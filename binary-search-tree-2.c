/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;//노드 구조체 선언

/* for stack */
#define MAX_STACK_SIZE		20//비재귀적인 inorder함수를 만들때 사용하는 스택정보
Node* stack[MAX_STACK_SIZE];//스택 주소를 저장한다. (주소를 저장해야 스택에서 꺼냈을 때 오른쪽으로 이동 가능)
int top = -1;//top을 가르키는 변수

Node* pop();//맨 위를 꺼내는 것 - 반환값이 노드의 주소임을 명심!
void push(Node* aNode);//위에 쌓는 것

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();//??왜 있지



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("---------[2018038074]------------------------[임종훈]-----------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {//루트노드의 주소를 저장하는 헤드노드 생성.

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;//덤으로 스택과 큐등의 함수도 초기화해준다.

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)//재귀를 이용한 탐색. iterative 확인용
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	int top = -1;
	while(1){
		while(node != NULL){
			push(node);//스택에 값을 넣어주고
			node = node->left;//다음 노드로 이동.
			//끝까지 이동해서 node가 NULL이면 탈출
		}

		node = pop();//스택 맨 위에있는 노드의 주소를 pop.
		if(node == NULL){//만약 NULL이 반환되었다면 이는 스택에 더 이상 아무런 값도 없다는 것.
			//루트노드까지 다 출력했다는 말이므로
			break;//반목문 탈출. 함수 종료
		}
		printf(" [%d] ", node->key);//노드에 값 출력

		//이후 오른쪽으로 이동. 오른쪽에 자식이 없으면 NULL을 받기 때문에 바로 pop으로 다시 이동됨.
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
}


int insert(Node* head, int key)//노드 삽입 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;//먼저 동적할당하고 값을 집어넣어준다. 당연히 맨 끝으로 가기 때문에 자식노드 없음

	if (head->left == NULL) {//루트노드가 있는지 확인. 없으면 루트 노드 추가하고 종료
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//ptr은 루트노드

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;//이미 노드가 있을 경우 후처리

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;//이전 노드 주소 저장해두고

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)//다음 노드로 이동한다
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)//끝에 도달해서 탈출했을 때 왼쪽으로 넣을지, 오른쪽으로 넣을지 결정.
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if(top == -1){//더 이상 스택에 저장되어있는 값으 없는 경우
		return NULL;//NULL을 반환한다
	}

	//그렇지 않으면
	return stack[top--];//맨 위에 스택 값을 반환하고 top을 하나 줄여준다.
}

void push(Node* aNode)//stack 배열에 값 저장(노드의 주소)
{
	stack[++top] = aNode;//top이 -1부터 시작하므로 먼저 증가시켜주고 대입해야함.
}



Node* deQueue()
{
}

void enQueue(Node* aNode)
{
}

void printStack(){
	return ;
}
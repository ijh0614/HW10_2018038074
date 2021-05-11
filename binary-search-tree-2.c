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
Node* queue[MAX_QUEUE_SIZE];//큐 배열 선언
int front = -1;
int rear = -1;//가르키고 있는 값이 없는걸로 초기화

Node* deQueue();//front가 가르키는 값을 반환하고 1 증가시킴
void enQueue(Node* aNode);//rear를 1 증가시키고 해당 위치에 값 저장


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
		printf("-------[2018038074]----------------------[ImJongHoon]-----------\n");
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
void levelOrder(Node* ptr)//루트노드의 주소를 전달받는다
{
	front = 0;
	rear = 0;// 큐 위치 할당

	if(ptr == NULL){// 루트노드가 없으면, 즉 공백트리이면
		return ;
	}

	enQueue(ptr);//먼저 루트 노드를 넣어주어서 front와 rear를 다르게함
	
	while(1){
		ptr = deQueue();
		
		if(ptr != NULL){
			printf(" [%d] ", ptr->key);

			if(ptr->left != NULL){
				enQueue(ptr->left);//왼쪽 자식노드가 있으면 큐에 저장
			}
			if(ptr->right != NULL){
				enQueue(ptr->right);//오른쪽 자식노드가 있으면 큐에 저장
			}
		}
		else{//ptr이 NULL이면
			break; //반복문, 함수 탈출
		}
	}
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


int deleteNode(Node* head, int key)//헤드 노드의 주소 인자로 받음
{
	Node* node = head->left;//root노드
    Node* parent = head;
    Node* temp;
    Node* temp_parent;

	if(node == NULL){//루트노드가 없는 경우
		printf("There is no root node");
		return 0;
	}

    while(node != NULL && node->key != key){//둘 중 하나만 참이어도 탈출. key값을 찾거나, 끝까지 돌았는데도 못 찾거나
        if(node->key > key){//현재 읽고있는 노드의 key값이 찾는 key값보다 크면
            parent = node;
            node = node->left;//왼쪽 자식노드 탐색
        }
        else{//그렇지 않으면
            parent = node;
            node = node->right;//오른쪽 자식노드 탑색
        }
    }

    //node에 NULL이어서 탈출한 경우 경우 값이 없음
    if(node == NULL){
        printf("There is no key in tree\n");
        return 0;
    }


    //key를 찾은 경우 일단 해당 노드의 주소가 반환됨.
    if(node->left == NULL && node->right == NULL){//key가 들어있는 노드에 양쪽이 다 NULL이면
    //자식이 없으므로 leaf노드다.
        if(node == head->left){//루트노드가 leaf노드라면
            head->left = NULL;//헤드노드에 가르키는 값에 NULL넣고
            free(node);//해제
            return 0;
        }
        if(parent->key > node->key){//부모 노드가 지우려는 노드보다 크면
            parent->left = NULL;//자식 노드가 왼쪽에 있음
        }
        else{//아니면
            parent->right = NULL;//자식 노드가 오른쪽에 있음
        }
        free(node);
    }

    else if(node->left != NULL && node->right != NULL){//자식 노드가 두개 인경우
        //오른쪽 서브트리에서 가장 작은 값으로 대체
		temp = node->right;//오른쪽에서 가장 작은 노드 찾아야함

		while(temp->left != NULL){
			temp_parent=temp;
			temp = temp->left;//가장 작은 값
		}

		if(temp==node->right){//지우려는 노드의 바로 오른쪽 노드가 리프 노드인 경우
		//루트노드 삭제하기 포함
			if(parent->key > node->key || parent->key == -9999){//부모의 왼쪽 가지에 자식이 있는 경우
				parent->left = temp;
			}
			else {
				parent->right = temp;
			}
			temp->left = node->left;//지워질 노드 왼쪽 브랜치 값을 받음
		}

		else{//가장 작은 노드가 지우려는 노드의 바로 오른쪽 노드가 아닌 경우
			if(parent->key > node->key || parent->key == -9999){//부모의 왼쪽 가지에 자식이 있는 경우
				parent->left = temp;
			}
			else {
				parent->right = temp;
			}
			temp_parent->left = NULL;//원래 temp를 가르키고 있던 branch 삭제
			temp->left = node->left;
			temp->right = node->right;
		}
		free(node);
    }

	else{//자식 노드가 하나인 경우

		if(parent->key > node->key || parent->key == -9999){//부모의 왼쪽 가지에 자식이 있는 경우
			if(node->left != NULL){//지우려는 노드의 자식 노드가 왼쪽에 있는 경우
				parent->left = node->left;
			}
			else{//자식 노드가 오른쪽에 있는 경우
				parent->left = node->right;
			}
		}
		else{//부모의 오른쪽 가지에 자식이 있는 경우
			if(node->left != NULL){//지우려는 노드의 자식 노드가 왼쪽에 있는 경우
				parent->right = node->left;
			}
			else{//자식 노드가 오른쪽에 있는 경우
				parent->right = node->right;
			}
		}
        free(node);
	}

    return 0;
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
	//front가 가르치는 위치와 rear가 가르치는 위치가 같은 경우. 즉 큐가 비어있는 경우
	if(front == rear){
		return NULL;//널 반환
	}

	return queue[front++];
}

void enQueue(Node* aNode)
{
	queue[rear++] = aNode;
}

void printStack(){
	return ;
}
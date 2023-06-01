/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{						// 노드 구조체 정의
	int key;			// 노드에 입력할 값 변수
	struct node *left;	// 왼쪽 자식 노드로 이동할 포인터
	struct node *right; // 오른쪽 자식 노드로 이동할 포인터
} Node;

/* for stack */
#define MAX_STACK_SIZE 20	 // 기호상수 MAX_STACK_SIZE 20으로 설정
Node *stack[MAX_STACK_SIZE]; // 크기가 MAX_STACK_SIZE인 Node 구조체 포인터 배열 stack 선언
int top = -1;				 // stack의 top을 나타내는 변수 선언하고 -1로 초기화

/* for queue */
#define MAX_QUEUE_SIZE 20	 // 기호상수 MAX_QUEUE_SIZE 20으로 설정
Node *queue[MAX_QUEUE_SIZE]; // MAX_STACK_SIZE
int front = -1;				 // queue의 front를 나타내는 변수 선언하고 -1로 초기화
int rear = -1;				 // queue의 rear를 나타내는 변수 선언하고 -1로 초기화

int initializeBST(Node **h);
void recursiveInorder(Node *ptr); /* recursive inorder traversal */
int insert(Node *head, int key);  /* insert a node to the tree */
int freeBST(Node *head);		  /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node *ptr);	 /* iterative inorder traversal */
void levelOrder(Node *ptr);			 /* level order traversal */
int deleteNode(Node *head, int key); /* delete the node for the key */
Node *pop();
void push(Node *aNode);
Node *deQueue();
void enQueue(Node *aNode);

/* you may add your own defined functions if necessary */

void printStack();

int main()
{
	char command;	   // 명령어를 입력 받을 변수
	int key;		   // 값을 입력 받을 변수
	Node *head = NULL; // 헤드 노드를 선언하고 NULL 값으로 초기화

	printf("[----- [Jeong Hanul] [2020039076] -----]\n\n");

	do
	{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 명령어를 입력받아 command에 저장

		switch (command)
		{
		case 'z':
		case 'Z': // z or Z 입력 시
			initializeBST(&head);
			break;
		case 'q':
		case 'Q': // q or Q 입력 시
			freeBST(head);
			break;
		case 'i':
		case 'I': // i or I 입력 시
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd':
		case 'D': // d or D 입력 시
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r':
		case 'R': // r or R 입력 시
			recursiveInorder(head->left);
			break;
		case 't':
		case 'T': // t or T 입력 시
			iterativeInorder(head->left);
			break;

		case 'l':
		case 'L': // l or L 입력 시
			levelOrder(head->left);
			break;

		case 'p':
		case 'P': // p or P 입력 시
			printStack();
			break;

		default: // 이외 입력 시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q'); // command가 q or Q 아닌 동안 반복

	return 1;
}

int initializeBST(Node **h) // 이진 트리를 초기화하는 함수
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node *)malloc(sizeof(Node)); // 매개변수로 받은 헤드 노드 h에 Node 사이즈만큼 동적 할당
	(*h)->left = NULL;				   /* root */
	(*h)->right = *h;				   // 오른쪽 포인터를 자기 자신으로 초기화
	(*h)->key = -9999;				   // key 값을 -9999로 초기화

	top = -1; // top에 -1 대입

	front = rear = -1; // front, rear에 -1 대입

	return 1;
}

void recursiveInorder(Node *ptr) // inorder - recursive 방식으로 트리를 출력하는 함수
{
	if (ptr)
	{
		recursiveInorder(ptr->left);  // 왼쪽 포인터를 매개변수로 하여 함수 재호출
		printf(" [%d] ", ptr->key);	  // 노드 값 출력
		recursiveInorder(ptr->right); // 오른쪽 포인터를 매개변수로 하여 함수 재호출
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node *node) // stack을 이용하여 inorder 방식으로 트리를 출력하는 함수
{
	for (;;)
	{
		for (; node; node = node->left) // node가 참일 동안 node에 왼쪽 포인터를 대입하면서 반복
			push(node);					// node를 매개변수로 하여 push 함수 호출
		node = pop();					// node에 pop함수 대입

		if (!node) // node가 NULL이면
			break;
		printf(" [%d] ", node->key); // 노드의 key 값 출력

		node = node->right; // node에 오른쪽 포인터 대입
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node *ptr) // Queue를 이용하여 levelOrder 방식으로 트리를 출력하는 함수
{
	// int front = rear = -1;

	if (!ptr)	// ptr이 NULL인 경우
		return; /* empty tree */

	enQueue(ptr); // ptr을 매개변수로 하여 enQueue 함수 호출

	for (;;)
	{
		ptr = deQueue(); // ptr에 deQueue 함수 대입
		if (ptr)		 // ptr이 참인 경우
		{
			printf(" [%d] ", ptr->key); // ptr의 key 값 출력

			if (ptr->left)			 // ptr의 왼쪽 노드가 참인 경우
				enQueue(ptr->left);	 // ptr 왼쪽 포인터를 매개변수로 하여 enQueue 함수 호출
			if (ptr->right)			 // ptr의 오른쪽 노드가 참인 경우
				enQueue(ptr->right); // ptr 오른쪽 포인터를 매개변수로 하여 enQueue 함수 호출
		}
		else
			break;
	}
}

int insert(Node *head, int key) // 노드에 값을 입력하고 삽입하는 함수
{
	Node *newNode = (Node *)malloc(sizeof(Node)); // 노드 포인터 newNode를 선언하고 동적 할당
	newNode->key = key;							  // newNode의 key 값에 입력 받은 key 대입
	newNode->left = NULL;						  // newNode의 왼쪽 포인터를 NULL로 초기화
	newNode->right = NULL;						  // newNode의 오른쪽 포인터를 NULL로 초기화

	if (head->left == NULL) // 헤드 노드의 왼쪽 포인터가 NULL이면
	{
		head->left = newNode; // 헤드 노드의 왼쪽 포인터에 newNode 대입
		return 1;
	}

	/* head->left is the root */
	Node *ptr = head->left; // 노드 포인터 ptr을 선언하고 헤드 노드의 왼쪽 포인터로 초기화

	Node *parentNode = NULL; // 노드 포인터 parentNode 선언하고 NULL로 초기화
	while (ptr != NULL)		 // ptr이 NULL이 아닌 동안
	{

		/* if there is a node for the key, then just return */
		if (ptr->key == key) // ptr의 key 값과 입력 받은 key 값이 같은 경우 1 반환
			return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; // parentNode에 ptr 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)	  // ptr의 key 값이 입력 받은 key 값보다 작은 경우
			ptr = ptr->right; // ptr에 오른쪽 포인터 대입
		else
			ptr = ptr->left; // ptr에 왼쪽 포인터 대입
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)		 // parentNode의 key 값이 입력 받은 key 값보다 큰 경우
		parentNode->left = newNode;	 // parentNode의 왼쪽 포인터에 newNode 대입
	else							 // parentNode의 key 값이 입력 받은 key 값보다 작은 경우
		parentNode->right = newNode; // parentNode의 오른쪽 포인터에 newNode 대입
	return 1;
}

int deleteNode(Node *head, int key) // 해당하는 key 값인 노드를 제거하는 함수
{
	if (head == NULL) // 헤드 노드가 NULL인 경우
	{
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) // 헤드 노드의 왼쪽 포인터가 NULL인 경우
	{
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node *root = head->left; // 노드 포인터 root를 선언하고 헤드 노드의 왼쪽 포인터로 초기화

	Node *parent = NULL; // 노드 포인터 parent를 선언하고 NULL로 초기화
	Node *ptr = root;	 // 노드 포인터 ptr을 선언하고 root로 초기화

	while ((ptr != NULL) && (ptr->key != key)) // ptr이 NULL이 아니고 ptr의 key 값이 입력 받은 key 값과 다른 동안
	{
		if (ptr->key != key) // ptr의 key 값과 입력 받은 key 값이 다른 경우
		{

			parent = ptr; /* save the parent */

			if (ptr->key > key)	  // ptr의 key 값이 입력 받은 key 값보다 큰 경우
				ptr = ptr->left;  // ptr에 왼쪽 포인터 대입
			else				  // ptr의 key 값이 입력 받은 key 값보다 작은 경우
				ptr = ptr->right; // ptr에 오른쪽 포인터 대입
		}
	}

	/* there is no node for the key */
	if (ptr == NULL) // ptr이 NULL인 경우
	{
		printf("No node for key [%d]\n ", key); // key 값에 해당 하는 노드가 없음을 출력
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if (ptr->left == NULL && ptr->right == NULL) // ptr의 두 포인터 모두 NULL인 경우
	{
		if (parent != NULL)			  // parent가 NULL이 아닌 경우
		{							  /* parent exists, parent's left and right links are adjusted */
			if (parent->left == ptr)  // parent의 왼쪽 포인터가 ptr인 경우
				parent->left = NULL;  // parent의 왼쪽 포인터에 NULL 대입
			else					  // parent의 오른쪽 포인터가 ptr인 경우
				parent->right = NULL; // parent의 오른쪽 포인터에 NULL 대입
		}
		else // parent가 NULL인 경우
		{
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; // head의 왼쪽 포인터에 NULL 대입
		}

		free(ptr); // ptr 메모리 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) // ptr의 둘 중 하나의 포인터가 NULL인 경우
	{
		Node *child;			// 노드 포인터 child를 선언
		if (ptr->left != NULL)	// ptr의 왼쪽 포인터가 NULL이 아닌 경우
			child = ptr->left;	// child에 ptr의 왼쪽 포인터 대입
		else					// ptr의 왼쪽 포인터가 NULL인 경우
			child = ptr->right; // child에 ptr의 오른쪽 포인터 대입

		if (parent != NULL) // parent가 NULL이 아닌 경우
		{
			if (parent->left == ptr)   // parent의 왼쪽 포인터가 ptr인 경우
				parent->left = child;  // parent의 왼쪽 포인터에 child 대입
			else					   // parent의 왼쪽 포인터가 ptr이 아닌 경우
				parent->right = child; // parent의 오른쪽 포인터에 child 대입
		}
		else // parent가 NULL인 경우
		{
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; // root에 child 대입
		}

		free(ptr); // ptr 메모리 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node *candidate; // 노드 포인터 candidate를 선언
	parent = ptr;	 // parent에 ptr 대입

	candidate = ptr->right; // candidate에 ptr의 오른쪽 포인터 대입

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while (candidate->left != NULL) // candidate의 왼쪽 포인터가 NULL이 아닐 동안
	{
		parent = candidate;			 // parent에 candidate 대입
		candidate = candidate->left; // candidate에 왼쪽 포인터 대입
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)		  // parent의 오른쪽 포인터가 candidate인 경우
		parent->right = candidate->right; // parent의 오른쪽 포인터에 candidate의 오른쪽 포인터 대입
	else								  // parent의 오른쪽 포인터가 candidate가 아닌 경우
		parent->left = candidate->right;  // parent의 왼쪽 포인터에 candidate의 오른쪽 포인터 대입

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; // ptr의 key 값에 candidate의 key 값 대입

	free(candidate); // candidate 메모리 해제
	return 1;
}

void freeNode(Node *ptr) // 노드 메모리 해제하는 함수
{
	if (ptr) // ptr이 참이면 (NULL이 아님)
	{
		freeNode(ptr->left);  // ptr의 왼쪽 포인터를 매개변수로 하는 함수 재호출
		freeNode(ptr->right); // ptr의 오른쪽 포인터를 매개변수로 하는 함수 재호출
		free(ptr);			  // ptr 메모리 해제
	}
}

int freeBST(Node *head) // 이진 트리의 모든 노드 메모리 해제하는 함수
{

	if (head->left == head) // 헤드 노드의 왼쪽 포인터가 헤드 노드인 경우
	{
		free(head); // 헤드 노드 메모리 해제
		return 1;
	}

	Node *p = head->left; // 노드 포인터 p 선언하고 헤드 노드의 왼쪽 포인터로 초기화

	freeNode(p); // p를 매개변수로 하는 freeNode 함수 호출

	free(head); // 헤드 노드 메모리 해제
	return 1;
}

Node *pop() // stack에서 pop 함수
{
	if (top < 0)		 // top이 0보다 작은 경우
		return NULL;	 // NULL 리턴
	return stack[top--]; // stack[top]을 리턴하고 top에 --연산
}

void push(Node *aNode) // stack에서 push 함수
{
	stack[++top] = aNode; // top에 ++연산하고 stack[top]에 aNode 대입
}

void printStack() // top 값이 -1에서 변하지 않음. while문에서 조건식의 변수가 변화가 없어 일정함 (무한 루프)
{
	int i = 0;
	printf("--- stack ---\n");
	while (i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

Node *deQueue() // Queue에서 deQueue 함수
{
	if (front == rear) // front와 rear가 같은 경우
	{
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // front에 front + 1 를 MAX_QUEUE_SIZE로 나눈 나머지 대입
	return queue[front];				  // queue[front]를 반환
}

void enQueue(Node *aNode) // Queue에서 enQueue 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; // rear에 rear + 1 를 MAX_QUEUE_SIZE로 나눈 나머지 대입
	if (front == rear)					// front와 rear가 같은 경우
	{
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; // queue[rear]에 aNode 대입
}

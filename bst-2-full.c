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
void iterativeInorder(Node *node) // inorder - iterative 방식으로 트리를 출력하는 함수
{
	for (;;)
	{
		for (; node; node = node->left)
			push(node);
		node = pop();

		if (!node)
			break;
		printf(" [%d] ", node->key);

		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node *ptr)
{
	// int front = rear = -1;

	if (!ptr)
		return; /* empty tree */

	enQueue(ptr);

	for (;;)
	{
		ptr = deQueue();
		if (ptr)
		{
			printf(" [%d] ", ptr->key);

			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
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

	while ((ptr != NULL) && (ptr->key != key))
	{
		if (ptr->key != key)
		{

			parent = ptr; /* save the parent */

			if (ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	/* there is no node for the key */
	if (ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if (ptr->left == NULL && ptr->right == NULL)
	{
		if (parent != NULL)
		{ /* parent exists, parent's left and right links are adjusted */
			if (parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else
		{
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;
		}

		free(ptr);
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node *child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

		if (parent != NULL)
		{
			if (parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		}
		else
		{
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr);
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

	Node *candidate;
	parent = ptr;

	candidate = ptr->right;

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while (candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;

	free(candidate);
	return 1;
}

void freeNode(Node *ptr)
{
	if (ptr)
	{
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node *head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node *p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

Node *pop()
{
	if (top < 0)
		return NULL;
	return stack[top--];
}

void push(Node *aNode)
{
	stack[++top] = aNode;
}

void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while (i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

Node *deQueue()
{
	if (front == rear)
	{
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

void enQueue(Node *aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear)
	{
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;
}

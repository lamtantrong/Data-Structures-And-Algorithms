#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef int ItemType;
struct TNode
{
	ItemType Info;
	TNode* Left;
	TNode* Right;
};
struct BSTree
{
	TNode* Root;
};
struct QNode
{
	TNode* info;
	QNode* next;
};
struct Queue
{
	QNode* head;
	QNode* tail;
};
//---------Binary Search Tree------------
int isEmptyBSTree(BSTree bst);
void initBSTree(BSTree& bst);
TNode* createTNode(ItemType x);
int insertTNode(TNode*& root, TNode* p);
void createBSTree_FromFile(BSTree& bst);
void showTNode(TNode* p);
//Duyệt cây theo chiều rộng
void traverseBreadthNLR(TNode* root);
void traverseBreadthNRL(TNode* root);
//----------------Queue----------------
void initQueue(Queue& queue);
int isEmptyQ(Queue queue);
QNode* createQNode(TNode* x);
void pushQueue(Queue& queue, QNode* p);
void popQueue(Queue& queue);
TNode* getHead(Queue queue);
//-------------------------------------
int main()
{
	BSTree bst;
	createBSTree_FromFile(bst);
	printf("\n\nDuyet cay theo chieu rong Node - Left - Right: ");
	traverseBreadthNLR(bst.Root);
	printf("\n\nDuyet cay theo chieu rong Node - Right - Left: ");
	traverseBreadthNRL(bst.Root);
	_getch();
	return 0;
}
int isEmptyBSTree(BSTree bst)
{
	if (bst.Root == NULL)
		return 1;
	return 0;
}
void initBSTree(BSTree& bst)
{
	bst.Root = NULL;
}
TNode* createTNode(ItemType x)
{
	TNode* p = new TNode;
	if (p == NULL)
	{
		printf("\nKhong Du Bo Nho De Cap Phat");
		_getch();
		return NULL;
	}
	p->Info = x;
	p->Left = NULL;
	p->Right = NULL;
	return p;
}
int insertTNode(TNode*& root, TNode* p)
{
	if (p == NULL)
		return 0;
	if (root == NULL)
	{
		root = p;
		return 1;
	}
	if (root->Info == p->Info)
		return 0;
	if (p->Info < root->Info)
		insertTNode(root->Left, p);
	else
		insertTNode(root->Right, p);
	return 1;
}
/*		File "DATA.txt"
16
10 8 9 5 4 17 15 16 20 11 12 13 19 7 25 6
*/
//Tương tự như mảng 1 chiều trong file
void createBSTree_FromFile(BSTree& bst)
{
	int n;
	ItemType x;
	initBSTree(bst);
	FILE* f;
	fopen_s(&f, "DATA.txt", "rt");
	if (f == NULL)
	{
		printf("\nKhong Mo File Thanh Cong!");
		return;
	}
	fscanf_s(f, "%d\n", &n);
	for (int i = 1; i <= n; i++)
	{
		fscanf_s(f, "%d ", &x);
		TNode* p = createTNode(x);
		insertTNode(bst.Root, p);
	}
	printf("\nTao cay nhi phan tim kiem thanh cong!");
	fclose(f);
}
void showTNode(TNode* p)
{
	printf("%5d", p->Info);
}
//Duyệt cây theo chiều rộng cho Node - Left - Right
void traverseBreadthNLR(TNode* root)
{
	Queue queue;
	if (!root)
		return;
	initQueue(queue);
	QNode* x = createQNode(root);
	pushQueue(queue, x);
	while (isEmptyQ(queue) == 0)
	{
		TNode* p = getHead(queue);
		popQueue(queue);
		showTNode(p);
		if (p->Left != NULL)
		{
			QNode* x = createQNode(p->Left);
			pushQueue(queue, x);
		}
		if (p->Right != NULL)
		{
			QNode* x = createQNode(p->Right);
			pushQueue(queue, x);
		}
	}
}
//Duyệt cây theo chiều rộng cho Node - Right - Left
void traverseBreadthNRL(TNode* root)
{
	Queue queue;
	if (!root)
		return;
	initQueue(queue);
	QNode* x = createQNode(root);
	pushQueue(queue, x);
	while (isEmptyQ(queue) == 0)
	{
		TNode* p = getHead(queue);
		popQueue(queue);
		showTNode(p);
		if (p->Right != NULL)
		{
			QNode* x = createQNode(p->Right);
			pushQueue(queue, x);
		}
		if (p->Left != NULL)
		{
			QNode* x = createQNode(p->Left);
			pushQueue(queue, x);
		}
	}
}
//---------------Queue---------------
void initQueue(Queue& queue)
{
	queue.head = NULL;
	queue.tail = NULL;
}
int isEmptyQ(Queue queue)
{
	if (queue.head == NULL)
		return 1;//queue rỗng
	return 0;//queue không rỗng
}
QNode* createQNode(TNode* x)
{
	QNode* p = new QNode;
	if (p == NULL)
	{
		printf("\nKhong Du Bo Nho");
		_getch();
		return NULL;
	}
	p->info = x;
	p->next = NULL;
	return p;
}
void pushQueue(Queue& queue, QNode* p)
{
	if (p == NULL)
		return;

	if (isEmptyQ(queue))
	{
		queue.head = p;
		queue.tail = p;
	}
	else
	{
		queue.tail->next = p;
		queue.tail = p;
	}
}
void popQueue(Queue& queue)
{
	if (isEmptyQ(queue))
		return;
	QNode* p = queue.head;
	queue.head = queue.head->next;
	p->next = NULL;
	//nếu danh sách khi còn 1 phần tử
	if (queue.head == NULL)
		queue.tail = NULL;
	delete p;
}
TNode* getHead(Queue queue)
{
	if (isEmptyQ(queue))
		return NULL;
	return queue.head->info;
}

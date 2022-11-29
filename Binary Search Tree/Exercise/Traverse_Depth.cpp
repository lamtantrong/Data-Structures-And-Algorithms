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
struct SNode
{
	TNode* info;
	SNode* next;
};
struct Stack
{
	SNode* top;
};
//---------Binary Search Tree------------
int isEmptyBSTree(BSTree bst);
void initBSTree(BSTree& bst);
TNode* createTNode(ItemType x);
int insertTNode(TNode*& root, TNode* p);
void createBSTree_FromFile(BSTree& bst);
void showTNode(TNode* p);
void traverseDepthNLR(TNode* root);
//----------------Stack-----------------
void initStack(Stack& stack);
int isEmptyS(Stack stack);
SNode* createSNode(TNode* x);
void pushStack(Stack& s, SNode* p);
void popStack(Stack& s);
TNode* getTop(Stack& s);
//--------------------------------------
int main()
{
	BSTree bst;
	createBSTree_FromFile(bst);

	//Duyệt theo 6 cách NLR, NRL, LNR, LRN, RNL, RLN (đệ quy) đều là duyệt theo chiều sâu
	printf("\n\nDuyet cay theo chieu sau Node - Left - Right: ");
	traverseDepthNLR(bst.Root);
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
//Duyệt cây theo chiều sâu cho Node - Left - Right
void traverseDepthNLR(TNode* root)
{
	Stack stack;
	if (root == NULL)
		return;
	initStack(stack);
	SNode* x = createSNode(root);
	pushStack(stack, x);
	while (isEmptyS(stack) == 0)
	{
		TNode* p = getTop(stack);
		popStack(stack);
		showTNode(p);
		if (p->Right != NULL)
		{
			SNode* x = createSNode(p->Right);
			pushStack(stack, x);
		}
		if (p->Left != NULL)
		{
			SNode* x = createSNode(p->Left);
			pushStack(stack, x);
		}
	}
}
//---------------Stack---------------
void initStack(Stack& stack)
{
	stack.top = NULL;
}
int isEmptyS(Stack stack)
{
	if (stack.top == NULL)
		return 1;//stack rỗng
	return 0;//stack không rỗng
}
SNode* createSNode(TNode* x)
{
	SNode* p = new SNode;
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
void pushStack(Stack& s, SNode* p)
{
	if (p == NULL)
		return;

	if (isEmptyS(s))
		s.top = p;
	else
	{
		p->next = s.top;
		s.top = p;
	}
}
void popStack(Stack& s)
{
	SNode* p;
	int x;
	if (!isEmptyS(s))
	{
		p = s.top;
		s.top = s.top->next;
		delete p;
	}
}
TNode* getTop(Stack& s)
{
	if (isEmptyS(s))
		return NULL;
	return s.top->info;
}

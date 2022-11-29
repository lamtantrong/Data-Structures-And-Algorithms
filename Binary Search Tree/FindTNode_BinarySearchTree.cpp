#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
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
void initBSTree(BSTree& bst);
TNode* createTNode(ItemType x);
void showTNode(TNode* p);
int isEmpty(BSTree bst);
int insertTNode(TNode*& root, TNode* p);
void createBSTree_Automatic(BSTree& bst);
void traverseLNR(TNode* root);
TNode* findTNodeX_DeQuy(TNode* root, ItemType x);
TNode* findTNodeX(TNode* root, ItemType x);
int main()
{
	BSTree bst;
	//Tạo cây từ file
	createBSTree_Automatic(bst);
	printf("\n\nDuyet theo Left - Node - Right: ");
	traverseLNR(bst.Root);

	ItemType x;
	printf("\nNhap gia tri can tim:	");
	scanf_s("%d", &x);
	TNode* pf = findTNodeX(bst.Root, x);
	if (pf == NULL)
		printf("\nKhong tim thay %d trong cay nhi phan", x);
	else
		printf("\nDa tim thay %d trong cay nhi phan", x);
	_getch();
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
		printf("\nKhong Du Bo Nho De Cap Phat!");
		_getch();
		return NULL;
	}
	p->Info = x;
	p->Left = NULL;
	p->Right = NULL;
	return p;
}
void showTNode(TNode* p)
{
	printf("%5d", p->Info);
}
int isEmpty(BSTree bst)
{
	if (bst.Root == NULL)
		return 1;//Cây rỗng
	return 0;//Cây không rỗng
}
int insertTNode(TNode*& root, TNode* p)
{
	if (p == NULL)
		return 0;	//Không thành công
	//Nếu gốc chưa có
	if (root == NULL)
	{
		root = p;
		return 1;	//Thành công
	}
	//Nếu gốc có giá trị bằng giá trị thêm vào ==> Không thêm vào nữa
	if (root->Info == p->Info)
		return 0;	//Bị trùng nút
	//Nếu chưa có con trái ==> thêm bên trái
	if (root->Info > p->Info)
		insertTNode(root->Left, p);
	//Ngược lại nếu chưa có con phải ==> thêm bên phải
	else
		insertTNode(root->Right, p);
	return 1;	//Thành công
}
void createBSTree_Automatic(BSTree& bst)
{
	int n;
	printf("\nNhap so nut cua cay: ");
	scanf_s("%d", &n);
	//khởi tạo Binary Tree
	initBSTree(bst);
	srand((unsigned)time(NULL));
	for (int i = 1; i <= n; i++)
	{
		//random từ a tới b:  a + rand() % b - a + 1
		//Tạo số ngẫu nhiên trong đoạn [-99,99]
		ItemType x = -99 + rand() % 199;
		TNode* p = createTNode(x);
		insertTNode(bst.Root, p);
	}
	printf("\nDa tao cay thanh cong!");
}
//Duyệt cây theo Left - Node - Right (traverse LNR)
void traverseLNR(TNode* root)
{
	if (root == NULL)
		return;
	traverseLNR(root->Left);
	showTNode(root);
	traverseLNR(root->Right);
}
//Dùng đệ qui
TNode* findTNodeX_DeQuy(TNode* root, ItemType x)
{
	//(!root) bằng (root == NULL)
	if (!root)
		return NULL;
	if (root->Info == x)
		return root;
	if (root->Info > x)
		return findTNodeX_DeQuy(root->Left, x);
	else
		return findTNodeX_DeQuy(root->Right, x);
}
//Không dùng đệ qui
TNode* findTNodeX(TNode* root, ItemType x)
{
	TNode* p = root;
	while (p != NULL && p->Info != x)
	{
		if (p->Info > x)
			p = p->Left;
		else
			p = p->Right;
	}
	return p;
}

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
struct BTree
{
	TNode* Root;
};
void initBTree(BTree& bt);
TNode* createTNode(ItemType x);
void showTNode(TNode* p);
int isEmpty(BTree bt);
int insertTNode(TNode*& root, TNode* p);
void createBTree_Automatic(BTree& bt);
void createBTree_FromKeyboard(BTree& bt);
void traverseLNR(TNode* root);
TNode* findTNode(TNode* root, ItemType x);
int main()
{
	BTree bt;
	ItemType x;
	//Tạo cây tự động
	createBTree_Automatic(bt);
	//Tạo cây từ bàn phím
	//createBTree_FromKeyboard(bt);
	printf("\nDuyet theo Left - Node - Right: ");
	traverseLNR(bt.Root);
	printf("\nNhap gia tri can tim: ");
	scanf_s("%d", &x);
	//Tìm giá trị x trong cây nhị phân
	//Trường hơp: Không tìm thấy
	if (findTNode(bt.Root, x) == NULL)
		printf("\nKhong tim thay %d trong cay nhi phan", x);
	//Trường hợp: Tìm thấy
	else
		printf("\nDa tim thay %d trong cay nhi phan", x);
	_getch();
	return 0;
}
void initBTree(BTree& bt)
{
	bt.Root = NULL;
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
int isEmpty(BTree bt)
{
	if (bt.Root == NULL)
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
	//Nếu chưa có con trái ==> thêm bên trái
	if (root->Left == NULL)
		insertTNode(root->Left, p);
	//Ngược lại nếu chưa có con phải ==> thêm bên phải
	else if (root->Right == NULL)
		insertTNode(root->Right, p);
	//Ngược lại nếu có cả 2 bên trái phải ==> thêm vào cây con
	else
	{
		//Tạo số chẵn lẻ ngẫu nhiên
		int x = rand() % 2;
		//Nếu ra chẵn ==> thêm vào nhánh bên trái
		if (x == 0)
			insertTNode(root->Left, p);
		//Ngược lại ra lẻ ==> thêm vào nhánh bên phải
		else
			insertTNode(root->Right, p);
	}
	return 1;	//Thành công
}
void createBTree_Automatic(BTree& bt)
{
	int n;
	printf("\nNhap so nut cua cay: ");
	scanf_s("%d", &n);

	//khởi tạo Binary Tree
	initBTree(bt);

	srand((unsigned)time(NULL));
	for (int i = 1; i <= n; i++)
	{
		//random từ a tới b:  a + rand() % b - a + 1
		//Tạo số ngẫu nhiên trong đoạn [-99,99]
		ItemType x = -99 + rand() % 199;
		TNode* p = createTNode(x);
		insertTNode(bt.Root, p);
	}
	printf("\nTao cay thanh cong!");
}
void createBTree_FromKeyboard(BTree& bt)
{
	int n;
	ItemType x;
	printf("Nhap so nut cua cay: ");
	scanf_s("%d", &n);

	//khởi tạo Binary Tree
	initBTree(bt);

	for (int i = 1; i <= n; i++)
	{
		printf("Nhap nut thu %d: ", i);
		scanf_s("%d", &x);
		TNode* p = createTNode(x);
		insertTNode(bt.Root, p);
	}
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
TNode* findTNode(TNode* root, ItemType x)
{
	if (root == NULL)
		return NULL;
	if (root->Info == x)
		return root;
	//Tìm nhánh bên trái
	TNode* p = findTNode(root->Left, x);
	if (p != NULL)
		return p;
	//Tìm nhánh bên phải
	return findTNode(root->Right, x);
}

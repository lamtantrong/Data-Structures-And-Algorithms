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
void createBSTree_FromKeyboard(BSTree& bst);
void createBSTree_FromArray(BSTree& bst);
void traverseNLR(TNode* root);
void traverseNRL(TNode* root);
void traverseLNR(TNode* root);
void traverseLRN(TNode* root);
void traverseRNL(TNode* root);
void traverseRLN(TNode* root);
int main()
{
	BSTree bst;
	//Tạo cây tự động
	createBSTree_Automatic(bst);
	//Tạo cây từ bàn phím
	//createBSTree_FromKeyboard(bst);
	printf("\n\nDuyet theo Node - Left - Right: ");
	traverseNLR(bst.Root);
	printf("\n\nDuyet theo Node - Right - Left: ");
	traverseNRL(bst.Root);
	printf("\n\nDuyet theo Left - Node - Right: ");
	traverseLNR(bst.Root);
	printf("\n\nDuyet theo Left - Right - Node: ");
	traverseLRN(bst.Root);
	printf("\n\nDuyet theo Right - Node - Left: ");
	traverseRNL(bst.Root);
	printf("\n\nDuyet theo Right - Left - Node: ");
	traverseRLN(bst.Root);
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
void createBSTree_FromKeyboard(BSTree& bst)
{
	int n;
	ItemType x;
	printf("Nhap so nut cua cay: ");
	scanf_s("%d", &n);
	//khởi tạo Binary Tree
	initBSTree(bst);
	for (int i = 1; i <= n; i++)
	{
		printf("Nhap nut thu %d: ", i);
		scanf_s("%d", &x);
		TNode* p = createTNode(x);
		insertTNode(bst.Root, p);
	}
}
void createBSTree_FromArray(BSTree& bst)
{

}
//Duyệt cây theo Node - Left - Right (traverse NLR)
void traverseNLR(TNode* root)
{
	if (root == NULL)
		return;
	showTNode(root);
	traverseNLR(root->Left);
	traverseNLR(root->Right);
}
//Duyệt cây theo Node - Right - Left (traverse NRL)
void traverseNRL(TNode* root)
{
	if (root == NULL)
		return;
	showTNode(root);
	traverseNRL(root->Right);
	traverseNRL(root->Left);
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
//Duyệt cây theo Left - Right - Node (traverse LRN)
void traverseLRN(TNode* root)
{
	if (root == NULL)
		return;
	traverseLRN(root->Left);
	traverseLRN(root->Right);
	showTNode(root);
}
//Duyệt cây theo Right - Node - Left (traverse RNL)
void traverseRNL(TNode* root)
{
	if (root == NULL)
		return;
	traverseRNL(root->Right);
	showTNode(root);
	traverseRNL(root->Left);
}
//Duyệt cây theo Right - Left - Node (traverse RLN)
void traverseRLN(TNode* root)
{
	if (root == NULL)
		return;
	traverseRLN(root->Right);
	traverseRLN(root->Left);
	showTNode(root);
}

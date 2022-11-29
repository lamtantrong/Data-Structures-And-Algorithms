#include<stdio.h>
#include<conio.h>
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
void createBSTree_FromFile(BSTree& bst);
void traverseNLR(TNode* root);
void traverseNRL(TNode* root);
void traverseLNR(TNode* root);
void traverseLRN(TNode* root);
void traverseRNL(TNode* root);
void traverseRLN(TNode* root);
int main()
{
	BSTree bst;
	//Tạo cây từ file
	createBSTree_FromFile(bst);
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
	printf("\nTao cay thanh cong!\n");
	fclose(f);
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

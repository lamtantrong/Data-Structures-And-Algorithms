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
void traverseLNR(TNode* root);
TNode* findTNodeX_DeQuy(TNode* root, ItemType x);
TNode* findTNodeReplace(TNode*& p);
int deleteTNode(TNode*& root, ItemType x);
int main()
{
	BSTree bst;
	//Tạo cây từ file
	createBSTree_FromFile(bst);
	printf("\n\nDuyet theo Left - Node - Right: ");
	traverseLNR(bst.Root);

	ItemType x;
	printf("\nNhap gia tri can xoa: ");
	scanf_s("%d", &x);
	if (findTNodeX_DeQuy(bst.Root, x) == NULL)
		printf("\nKhong tim thay %d tren cay nhi phan", x);
	else
	{
		deleteTNode(bst.Root, x);
		printf("\nXoa thanh cong!");
	}
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
//Duyệt cây theo Left - Node - Right (traverse LNR)
void traverseLNR(TNode* root)
{
	if (root == NULL)
		return;
	traverseLNR(root->Left);
	showTNode(root);
	traverseLNR(root->Right);
}
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
//Hàm tìm nút rp nhỏ nhất trên cây con bên phải
TNode* findTNodeReplace(TNode*& p)
{
	TNode* f = p, * rp = p->Right;
	while (rp->Left != NULL)
	{
		f = rp;//Lưu nút cha của rp
		rp = rp->Left;//Nút rp qua bên trái
	}
	//Tìm được phần tử thế mạng cho p là rp
	p->Info = rp->Info;
	//Trường hợp đặt biệt
	//Nút thế mạng rp là nút con bên phải của nút p cần xoá
	if (f == p)
		f->Right = rp->Right;
	else
		f->Left = rp->Right;
	return rp;
}
int deleteTNode(TNode*& root, ItemType x)
{
	//(!root) bằng (root == NULL)
	if (!root)
		return 0;
	if (root->Info > x)
		return deleteTNode(root->Left, x);
	else if (root->Info < x)
		return deleteTNode(root->Right, x);
	else
	{
		TNode* rp, * p = root;
		//Khi cây con không có nhánh trái
		if (!root->Left)
		{
			root = root->Right;
			//delete p;
		}
		//Khi cây con không có nhánh phải
		else if (!root->Right)
		{
			root = root->Left;
			//delete p;
		}
		//Khi cây con có 2 nhánh trái
		else
		{
			rp = findTNodeReplace(p);
			//delete rp;
		}
	}
}

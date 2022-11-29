#include<stdio.h>
#include<conio.h>
#include"AVL_Tree.h"

AVLNode* createAVLNode(ItemType x)
{
	AVLNode* p = new AVLNode;
	if (p == NULL)
	{
		printf("\nKhong Du Bo Nho De Cap Phat!");
		_getch();
		return NULL;
	}
	p->balFactor = 0;
	p->Info = x;
	p->Left = NULL;
	p->Right = NULL;
	return p;
}
void initAVLTree(AVLTree& avl)
{
	avl.Root = NULL;
}
//Cân bằng lại trường hợp 1: Left - Left
void rotateLL(AVLNode*& T)
{
	AVLNode* T1 = T->Left;
	T->Left = T1->Right;
	T1->Right = T;
	switch (T1->balFactor)
	{
	case LH:	//cây T1 lệch trái
		T->balFactor = EH;
		T1->balFactor = EH;
		break;
	case EH:	//cây T1 cân bằng
		T->balFactor = LH;
		T1->balFactor = RH;
		break;
	}
	T = T1;
}
//Cân bằng lại trường hợp 2: Left - Right
void rotateLR(AVLNode*& T)
{
	AVLNode* T1 = T->Left;
	AVLNode* T2 = T1->Right;
	T1->Right = T2->Left;
	T2->Left = T1;
	T->Left = T2->Right;
	T2->Right = T;
	switch (T2->balFactor)
	{
	case LH:
		T->balFactor = RH;
		T1->balFactor = EH;
		break;
	case EH:
		T->balFactor = EH;
		T1->balFactor = EH;
		break;
	case RH:
		T->balFactor = EH;
		T1->balFactor = LH;
		break;
	}
	T2->balFactor = EH;
	T = T2;
}
//Cân bằng lại trường hợp 3: Right - Left
void rotateRL(AVLNode*& T)
{
	AVLNode* T1 = T->Right;
	AVLNode* T2 = T1->Left;
	T1->Left = T2->Right;
	T2->Right = T1;
	T->Right = T2->Left;
	T2->Left = T;
	switch (T2->balFactor)
	{
	case RH:
		T->balFactor = LH;
		T1->balFactor = EH;
		break;
	case EH:
		T->balFactor = EH;
		T1->balFactor = EH;
		break;
	case LH:
		T->balFactor = EH;
		T1->balFactor = RH;
		break;
	}
	T2->balFactor = EH;
	T = T2;
}
//Cân bằng lại trường hợp 3: Right - Right
void rotateRR(AVLNode*& T)
{
	AVLNode* T1 = T->Right;
	T->Right = T1->Left;
	T1->Left = T;
	switch (T1->balFactor)
	{
	case RH://cây T1 lệch phải
		T->balFactor = EH;
		T1->balFactor = EH;
		break;
	case EH://cây T1 cân bằng
		T->balFactor = RH;
		T1->balFactor = LH;
		break;
	}
	T = T1;
}
//Cân bằng lại cây AVL khi bị mất cân bằng
//Cân bằng nhánh trái
int balanceLeft(AVLNode*& T)
{
	//Khi cây T lệnh bên trái
	AVLNode* T1 = T->Left;
	switch (T1->balFactor)
	{
	case LH:
		rotateLL(T);
		return 2;
	case EH:
		rotateLL(T);
		return 1;
	case RH:
		rotateLR(T);
		return 2;
	}
	return 0; //Thực hiện không thành công
}
//Cân bằng nhánh phải
int balanceRight(AVLNode*& T)
{
	AVLNode* T1 = T->Right;
	switch (T1->balFactor)
	{
	case LH:
		rotateRL(T);
		return 2;
	case EH:
		rotateRR(T);
		return 1;
	case RH:
		rotateRR(T);
		return 2;
	}
	return 0; //Thực hiện không thành công
}
void createAVLTree_FromFile(AVLTree& avl)
{
	int n;
	ItemType x;
	initAVLTree(avl);
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
		AVLNode* p = createAVLNode(x);
		insertAVLNode(avl.Root, p);
	}
	printf("\nTao cay nhi phan tim kiem thanh cong!");
	fclose(f);
}
int insertAVLNode(AVLNode*& T, AVLNode* p)
{
	//Nếu nút p không tồn tại
	if (p == NULL)
		return -1;
	if (T == NULL)
	{
		T = p;
		return 2;
	}
	int Result;
	if (T->Info == p->Info)
		return 0;//Đã tồn tại nút 
	//Thêm nhánh trái
	if (T->Info > p->Info)
	{
		Result = insertAVLNode(T->Left, p);
		if (Result < 2)
			return Result;
		switch (T->balFactor)
		{
		case RH:
			T->balFactor = EH;
			return 1;
		case EH:
			T->balFactor = LH;
			return 2;
		case LH:
			balanceLeft(T);
			return 1;
		}
	}
	//Thên vào nhánh phải
	else
	{
		Result = insertAVLNode(T->Right, p);
		if (Result < 2)
			return Result;
		switch (T->balFactor)
		{
		case LH:
			T->balFactor = EH;
			return 1;
		case EH:
			T->balFactor = RH;
			return 2;
		case RH:
			balanceRight(T);
			return 1;
		}
	}
}
//p là nút cần xoá
//q là nút thay thế (đại diện)
//Tìm nút thay thế có giá trị nhỏ nhất của nhánh bên phải
int searchStandFor_MinRight(AVLNode*& p, AVLNode*& q)
{
	int Result;
	//Nếu nhánh trái của q tồn tại
	if (q->Left != NULL)
	{
		Result = searchStandFor_MinRight(p, q->Left);
		if (Result < 2)
			return Result;
		switch (q->balFactor)
		{
			//Nếu lệch trái (-1) thì sau khi thay thế nút bên trái thì sẽ cân bằng (0)
		case LH:
			q->balFactor = EH;
			return 2;
			//Nếu cân bằng (0) thì sau khi thay thế nút bên trái thì sẽ lệch phải (1)
		case EH:
			q->balFactor = RH;
			return 1;
			//Nếu lệch phải (1) thì sau khi thay thế nút bên trái cây mất cân bằng => cân bằng nhánh phải
		case RH:
			return balanceRight(q);
		}
	}
	//Nếu nhánh trái của q không tồn tại (= NULL)
	else
	{
		p->Info = q->Info;
		p = q;
		q = q->Right;
	}
	return 2;
}
//Tìm nút thay thế có giá trị lớn nhất của nhánh bên trái
int searchStandFor_MaxLeft(AVLNode*& p, AVLNode*& q)
{
	int Result;
	//Nếu nhánh phải của q tồn tại
	if (q->Right != NULL)
	{
		Result = searchStandFor_MaxLeft(p, q->Right);
		if (Result < 2)
			return Result;
		switch (q->balFactor)
		{
			//Nếu lệch phải (1) thì sau khi thay thế nút bên phải thì sẽ cân bằng (0)
		case RH:
			q->balFactor = EH;
			return 2;
			//Nếu cân bằng (0) thì sau khi thay thế nút bên phải thì sẽ lệch trái (-1) 
		case EH:
			q->balFactor = LH;
			return 1;
			//Nếu lệch trái (-1) thì sau khi thay thế nút bên phải cây mất cân bằng => cân bằng nhánh trái
		case LH:
			return balanceLeft(q);
		}
	}
	//Nếu nhánh phải của q không tồn tại (= NULL)
	else
	{
		p->Info = q->Info;
		p = q;
		q = q->Left;
	}
	return 2;
}
int deleteAVLNode(AVLNode*& T, ItemType x)
{
	int Result;
	if (T == NULL)
		return 0;
	//Xét nhánh trái
	if (T->Info > x)
	{
		Result = deleteAVLNode(T->Left, x);
		if (Result < 2)
			return Result;
		switch (T->balFactor)
		{
		case LH:
			T->balFactor = EH;
			return 2;
		case EH:
				T->balFactor = RH;
			return 1;
		case RH:
			return balanceRight(T);
		}
	}
	//Xét nhánh phải
	else if (T->Info < x)
	{
		Result = deleteAVLNode(T->Right, x);
		if (Result < 2)
			return Result;
		switch (T->balFactor)
		{
		case RH:
			T->balFactor = EH;
			return 2;
		case EH:
			T->balFactor = LH;
			return 1;
		case LH:
			return balanceLeft(T);
		}
	}
	//Ngược lại, tìm thấy nút cần xoá
	else
	{
		AVLNode* p = T;
		//Nếu nút T không có nhánh trái
		if (T->Left == NULL)
		{
			T = T->Right;
			Result = 2;
		}
		//Ngược lại, nút T có nhánh trái
		else
		{
			//Nếu nút T không có nhánh phải
			if (T->Right == NULL)
			{
				T = T->Left;
				Result = 2;
			}
			//Nếu nút T có nhánh phải (nút T có 2 nhánh con)
			
			else
			{
				//Tìm nút thay thế có giá trị nhỏ nhất của nhánh bên phải
				Result = searchStandFor_MinRight(p, T->Right);
				if (Result < 2)
					return Result;
				switch (T->balFactor)
				{
				//Nếu lệch phải (1) thì sau khi xoá bên phải thì sẽ cân = (0)
				case RH:
					T->balFactor = EH;
					return 2;
				//Nếu cân bằng (0) thì sau khi xoá bên phải thì sẽ lệch bên trái (-1)
				case EH:
					T->balFactor = LH;
					return 1;
				//Nếu lệch trái (-1) thì sau khi xoá bên phải cây mất cân bằng => cân bằng nhánh trái
				case LH:
					return balanceLeft(T);
				}
			}
			/*
			else
			{
				//Tìm nút thay thế có giá trị lớn nhất của nhánh bên trái
				Result = searchStandFor_MaxLeft(p, T->Left);
				if (Result < 2)
					return Result;
				switch (T->balFactor)
				{
				//Nếu lệch trái (-1) thì sau khi xoá bên trái thì sẽ cân = (0)
				case LH:
					T->balFactor = EH;
					return 2;
				//Nếu cân bằng (0) thì sau khi xoá bên trái thì sẽ lệch phải (1)
				case EH:
					T->balFactor = RH;
					return 1;
				//Nếu lệch phải (1) thì sau khi xoá cây mất cân bằng => cân bằng nhánh phải
				case RH:
					return balanceRight(T);
				}
			}
			*/
		}
		delete p;
		return Result;
	}
	return Result;
}

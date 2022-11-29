#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include"asciinode.h"
#include"AVL_Tree.h"
int main()
{
	AVLTree avl;
	ItemType x;
	int luaChon;
	AVLNode* px;
	for (;;)
	{
		system("cls");
		menu();
		printf("\nNhap lua chon: ");
		scanf_s("%d", &luaChon);
		if (luaChon == 0)
			break;
		switch (luaChon)
		{
		case 1:
			createAVLTree_FromFile(avl);			
			break;
		case 2:
			print_ascii_tree(avl.Root);
			break;
		case 3:
			print_ascii_tree(avl.Root);
			printf("\n\nNhap phan tu can xoa: ");
			scanf_s("%d", &x);
			deleteAVLNode(avl.Root, x);
			system("cls");
			print_ascii_tree(avl.Root);
			break;
		case 4:
			printf("\nNhap phan tu can them: ");
			scanf_s("%d", &x);
			px = createAVLNode(x);
			insertAVLNode(avl.Root, px);
			print_ascii_tree(avl.Root);
			break;
		default:printf("\nLoi! Vui long nhap lai!");
			break;
		}
		_getch();
	}
	return 0;
}

//Danh Sách Liên Kết Đơn (Số Nguyên)
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
struct Node
{
	int info;
	Node* next;
};
struct SList
{
	Node* head;
	Node* tail;
};
void initSList(SList& list);
int isEmpty(SList list);
Node* createNode(int x);
void insertLast(SList& list, Node* p);
void nhapTuDong(SList& list, int& soPhanTu);
void nhapThuCong(SList& list, int& soPhanTu);
void printList(SList list);
int main()
{
    //Khai báo danh sách liên kết
	SList list;
	int soPhanTu;

    nhapTuDong(list, soPhanTu);
	//nhapThuCong(list, soPhanTu);
	printf("Danh sach vua nhap: ");
	printList(list);
    
	_getch();
	return 0;
}
void initSList(SList& list)
{
	list.head = NULL;
	list.tail = NULL;
}
int isEmpty(SList list)
{
	if (list.head == NULL)
		return 1;//danh sách rỗng
	return 0;//danh sách không rỗng
}
Node* createNode(int x)
{
	Node* p = new Node;
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
void insertLast(SList& list, Node* p)
{
	if (list.head == NULL)
	{
		list.head = p;
		list.tail = p;
	}
	else
	{
		list.tail->next = p;
		list.tail = p;
	}
}
void nhapTuDong(SList& list, int& soPhanTu)
{
	do
	{
		printf("Nhap so phan tu (n > 0): ");
		scanf_s("%d", &soPhanTu);
	} while (soPhanTu <= 0);

	initSList(list);

	srand(time(NULL));
	for (int i = 0; i < soPhanTu; i++)
	{
		int x = 1 + rand() % 100;
		Node* p = new Node;
		p = createNode(x);
		if (p)//tạo thành công
			insertLast(list, p);
	}
}
void nhapThuCong(SList& list, int& soPhanTu)
{
	do
	{
		printf("Nhap so phan tu (n > 0): ");
		scanf_s("%d", &soPhanTu);
	} while (soPhanTu <= 0);

	initSList(list);

	for (int i = 1; i <= soPhanTu; i++)
	{
		int x;
		printf("Nhap phan tu thu %d: ", i);
		scanf_s("%d", &x);
		Node* p = new Node;
		p = createNode(x);
		if (p)//tạo thành công
			insertLast(list, p);
	}
}
void printList(SList list)
{
	for (Node* p = list.head; p != NULL; p = p->next)
		printf("%5d", p->info);
}

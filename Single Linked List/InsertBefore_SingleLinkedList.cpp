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
void insertFirst(SList& list, Node* p);
void insertBefore(SList& list, Node* q, Node* p);
void insertLast(SList& list, Node* p);
Node* findNode(SList list, int x);
void nhapTuDong(SList& list, int& soPhanTu);
void nhapThuCong(SList& list, int& soPhanTu);
void printList(SList list);
int main()
{
	//Khai báo danh sách liên kết
	SList list;
	int soPhanTu, value, x;

	nhapTuDong(list, soPhanTu);
	//nhapThuCong(list, soPhanTu);
	printf("Danh sach vua nhap: ");
	printList(list);

	printf("\nNhap gia tri can chen: ");
	scanf_s("%d", &value);
	Node* px = new Node;
	px = createNode(value);

	printf("Chen truoc phan tu co gia tri: ");
	scanf_s("%d", &x);

	Node* pf = new Node;
	pf = findNode(list, x);
	if (pf == NULL)
		printf("\nKhong tim thay phan tu co gia tri %d trong danh sach", x);
	else
	{
		printf("\nDanh sach ban dau: ");
		printList(list);
		insertBefore(list, pf, px);
		printf("\nDanh sach sau khi chen: ");
		printList(list);
	}

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
void insertFirst(SList& list, Node* p)
{
	if (list.head == NULL)
	{
		list.head = p;
		list.tail = p;
	}
	else
	{
		p->next = list.head;
		list.head = p;
	}
}
//Node p là Node cần chèn
void insertBefore(SList& list, Node* q, Node* p)
{
	//nếu không tồn tại Node q thì không thực hiện
	if (q == NULL)
	{
		return;
	}
	//Tìm phần tử đứng trước Node q
	Node* t = list.head;

	if (t->info == q->info)
		insertFirst(list, p);
	else
	{
		while (t->next->info != q->info)
		{
			t = t->next;
		}
		//t->next trỏ đến đâu thì p->next cũng trỏ tới đó
		p->next = t->next;
		//t->next trỏ vào Node p
		t->next = p;
	}
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
Node* findNode(SList list, int x)
{
	for (Node* p = list.head; p != NULL; p = p->next)
		if (p->info == x)
			return p;
	return NULL;
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

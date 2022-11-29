//Danh Sách Liên Kết Đơn (Số Nguyên)
#include<stdio.h>
#include<conio.h>

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

int main()
{
    //Khai báo danh sách liên kết
	SList list;
	
    //Khởi tạo danh sách
    initSList(list);

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

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
struct QNode
{
	int info;
	QNode* next;
};
struct Queue
{
	QNode* head;
	QNode* tail;
};
void initQueue(Queue& queue);
int isEmpty(Queue queue);
QNode* createSNode(int x);
void insertQueue(Queue& queue, QNode* p);
void deleteQueue(Queue& queue, int& x);
void getHead(Queue queue, int& x);
void getTail(Queue queue, int& x);
void showQueue(Queue queue);
void createQueue_Automatic(Queue& queue);

int main()
{
	Queue queue;
	int x;
	createQueue_Automatic(queue);
	//Hiển thị toàn bộ hàng đợi Queue
	printf("\nNoi dung hang doi la: ");
	showQueue(queue);
	//Nhận giá trị đầu tiên của hàng đợi
	getHead(queue, x);
	printf("\nPhan tu dau tien: %d", x);
	//Nhận giá trị cuối cùng của hàng đợi
	getTail(queue, x);
	printf("\nPhan tu cuoi cung: %d", x);

	deleteQueue(queue, x);
	printf("\n\nGia tri vua xoa: %d", x);
	printf("\nNoi dung hang doi sau khi xoa la: ");
	showQueue(queue);

	_getch();
	return 0;
}
void initQueue(Queue& queue)
{
	queue.head = NULL;
	queue.tail = NULL;
}
int isEmpty(Queue queue)
{
	if (queue.head == NULL)
		return 1;//queue rỗng
	return 0;//queue không rỗng
}
QNode* createSNode(int x)
{
	QNode* p = new QNode;
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
void insertQueue(Queue& queue, QNode* p)
{
	if (p == NULL)
		return;

	if (isEmpty(queue))
	{
		queue.head = p;
		queue.tail = p;
	}
	else
	{
		queue.tail->next = p;
		queue.tail = p;
	}
}
void deleteQueue(Queue& queue, int &x)
{
	if (isEmpty(queue))
		return;
	QNode* p = queue.head;
	queue.head = queue.head->next;
	p->next = NULL;
	//nếu danh sách khi còn 1 phần tử
	if (queue.head == NULL)
		queue.tail = NULL;
	x = p->info;
	delete p;
}
void getHead(Queue queue, int& x)
{
	if (isEmpty(queue))
		return;
	x = queue.head->info;
}
void getTail(Queue queue, int& x)
{
	if (isEmpty(queue))
		return;
	x = queue.tail->info;
}
void showQueue(Queue queue)
{
	if (isEmpty(queue))
	{
		printf("\nHang doi rong");
		return;
	}
	for (QNode* p = queue.head; p != NULL; p = p->next)
		printf("%5d", p->info);
}
void createQueue_Automatic(Queue& queue)
{
	int n;
	printf("\nNhap so phan tu cua hang doi: ");
	scanf_s("%d", &n);
	//khởi tạo hàng đợi Queue
	initQueue(queue);
	srand((unsigned)time(NULL));
	for (int i = 1; i <= n; i++)
	{
		//random từ a tới b:  a + rand() % b - a + 1
		//Tạo số ngẫu nhiên trong đoạn [-99,99]
		int x = -99 + rand() % 199;
		QNode* p = createSNode(x);
		insertQueue(queue, p);
	}
}

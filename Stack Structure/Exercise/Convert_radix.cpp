#include<stdio.h>
#include<conio.h>
struct SNode
{
	int info;
	SNode* next;
};
struct Stack
{
	SNode* top;
};
void initStack(Stack& stack);
int isEmpty(Stack stack);
SNode* createSNode(int x);
void pushStack(Stack& s, SNode* p);
int popStack(Stack& s);
void doiCoSo(int n, int coSo);
int main()
{
	int n, coSo;
	//Chuyển đổi cơ số hệ 10 sang các hệ 2, 8, 16
	do
	{
		printf("Hay nhap mot co so he 10: ");
		scanf_s("%d", &n);
	} while (n <= 0);
	do
	{
		printf("Hay nhap co so muon doi: ");
		scanf_s("%d", &coSo);
	} while (coSo <= 0);
	doiCoSo(n, coSo);

	_getch();
	return 0;
}
void initStack(Stack& stack)
{
	stack.top = NULL;
}
int isEmpty(Stack stack)
{
	if (stack.top == NULL)
		return 1;//stack rỗng
	return 0;//stack không rỗng
}
SNode* createSNode(int x)
{
	SNode* p = new SNode;
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
void pushStack(Stack& s, SNode* p)
{
	if (p == NULL)
		return;

	if (isEmpty(s))
		s.top = p;
	else
	{
		p->next = s.top;
		s.top = p;
	}
}
int popStack(Stack& s)
{
	SNode* p;
	int x;
	if (!isEmpty(s))
	{
		p = s.top;
		s.top = s.top->next;
		x = p->info;
		delete p;
		return x;
	}
}
void doiCoSo(int n, int coSo)
{
	Stack s;
	initStack(s);
	int soDu, m = n, kq;
	SNode* pnew;
	while (m != 0)
	{
		soDu = m % coSo;
		m /= coSo;
		pnew = createSNode(soDu);
		pushStack(s, pnew);
	}
	printf("\nGia tri chuyen doi %d sang he %d la: ", n, coSo);
	while (!isEmpty(s))
	{
		kq = popStack(s);
		if (kq >= 10)
			printf("%c", kq + 55);
		else
			printf("%d", kq);
	}
}

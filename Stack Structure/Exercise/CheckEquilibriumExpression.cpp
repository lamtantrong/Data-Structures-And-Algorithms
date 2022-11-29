#include<stdio.h>
#include<conio.h>
#include<string.h>
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
bool kiemTraBieuThucCanBang(char str[]);

int main()
{
	char str[100];
	printf("\nNhap bieu thuc chua cac dau ngoac: ");
	rewind(stdin);
	gets_s(str);
	if (kiemTraBieuThucCanBang(str) == false)
		printf("Bieu thuc khong can bang");
	else
		printf("Bieu thuc can bang");

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
bool kiemTraBieuThucCanBang(char str[])
{
	Stack s;
	initStack(s);
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			SNode* p = createSNode(str[i]);
			pushStack(s, p);
		}
		else
		{
			if (isEmpty(s))
				return false;
			if (str[i] == ')' && s.top->info != '(')
				return false;
			if (str[i] == ']' && s.top->info != '[')
				return false;
			if (str[i] == '}' && s.top->info != '{')
				return false;
			popStack(s);
		}
	}
	if (isEmpty)
		return true;
	else
		return false;
}

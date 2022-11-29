#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
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
void process();
void initStack(Stack& stack);
int isEmpty(Stack stack);
SNode* createSNode(int x);
void pushStack(Stack& s, SNode* p);
int popStack(Stack& s);
void daoChuoi(char* str);
void daoNguocChuoi(char* str);
int doUuTien_CacToanTu(char x);
void infixToPostfix(char* str, char* postfix);
int main()
{
	process();

	_getch();
	return 0;
}
void process()
{
	char str[100], postfix[100];

	printf("Nhap bieu thuc: ");
	rewind(stdin);
	gets_s(str);
	daoChuoi(str);
	infixToPostfix(str, postfix);
	printf("\nBieu thuc tien to la: ");
	daoNguocChuoi(postfix);
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
void daoChuoi(char* str)
{
	Stack s;
	initStack(s);
	int k, len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		SNode* p = createSNode(str[i]);
		pushStack(s, p);
	}
	for (int i = 0; i < len; i++)
	{
		k = popStack(s);
		if (k == ')')
		{
			str[i] = '(';
			continue;
		}
		if (k == '(')
		{
			str[i] = ')';
			continue;
		}
		str[i] = k;
	}
	str[len] = '\0';
}
void daoNguocChuoi(char str[])
{
	Stack s;
	initStack(s);
	int k, len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		SNode* p = createSNode(str[i]);
		pushStack(s, p);
	}
	for (int i = 0; i < len; i++)
	{
		k = popStack(s);
		printf("%c", k);
	}
}
int doUuTien_CacToanTu(char x)
{
	if (x == '+' || x == '-')
		return 1;
	if (x == '*' || x == '/' || x == '%')
		return 2;
	if (x == '^')
		return 3;
}
//trung tố (infix) -> hậu tố (postfix) [ký pháp nghịch đảo Ba Lan]
void infixToPostfix(char* str, char* postfix)
{
	Stack s;
	//khởi tạo Stack rỗng
	initStack(s);
	int vt = 0, len = strlen(str);
	//postfix[len] = '\0';
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			postfix[vt++] = str[i];

		if (str[i] >= 65 && str[i] <= 90 || str[i] >= 97 && str[i] <= 122)
			postfix[vt++] = str[i];

		if (str[i] == '(')
		{
			SNode* p = createSNode(str[i]);
			pushStack(s, p);
		}
		if (str[i] == ')')
		{
			//duyệt và lấy các toán tử ra khỏi Stack
			while (s.top != NULL && s.top->info != '(')
				postfix[vt++] = popStack(s);
			//Gọi popStack lần nữa để xoá dấu mở ngoặc'('
			popStack(s);
		}
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '^')
		{
			if (isEmpty(s) == 1)
			{
				SNode* p = createSNode(str[i]);
				pushStack(s, p);
			}
			else
			{
				//Theo bảng ASCII (dấu + là 43) (dấu - là 45) (dấu * là 42) (dấu / là 47) (dấu % là 37) (dấu ^ là 94) 

				if (s.top->info == 43 || s.top->info == 45 || s.top->info == 42 || s.top->info == 47 || s.top->info == 37 || s.top->info == 94)
				{
					//Toán tử đầu Stack có độ ưu tiên nhỏ hơn thì PUSH vào Stack
					if (doUuTien_CacToanTu(s.top->info) < doUuTien_CacToanTu(str[i]))
					{
						SNode* p = createSNode(str[i]);
						pushStack(s, p);
					}
					else
					{
						//duyệt và lấy các toán tử ra khỏi Stack
						while (s.top != NULL && s.top->info != '(' && doUuTien_CacToanTu(s.top->info) >= doUuTien_CacToanTu(str[i]))
							postfix[vt++] = popStack(s);
						SNode* p = createSNode(str[i]);
						pushStack(s, p);
					}
				}
				else
				{
					SNode* p = createSNode(str[i]);
					pushStack(s, p);
				}
			}
		}
	}
	if (!isEmpty(s))
		while (s.top != NULL)
			postfix[vt++] = popStack(s);
	postfix[vt] = '\0';
}

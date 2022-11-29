//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct BaiHat
{
	char tenBH[51];
	char tenTG[41];
	char tenCS[41];
	int thoiLuong;
};

struct Node
{
	BaiHat info;
	Node* next;
};
struct SList
{
	Node* head;
	Node* tail;
};
void menu();
//void menu1();
void process();
void khoiTao(SList& list);
int isEmpty(SList list);
Node* createNode(BaiHat x);
void insertFirst(SList& list, Node* p);
void insertLast(SList& list, Node* p);
void deleteFirst(SList& list);
void deleteLast(SList& list);
void deleteAfter(SList& list, Node* q);
void chuanHoaChuoi(char str[]);

void nhapTuFile(SList& list);
void nhapBaiHat(BaiHat& x);
void printList(SList list);
int tinhTongThoiGianNghe_TatCaBH(SList list);
void xoaBaiHat(SList& list, char ten[]);
int kiemTraBaiHat(SList list, char ten[]);
void swap(BaiHat& a, BaiHat& b);
void interchangeSort_TangDan(SList& list);
void interchangeSort_GiamDan(SList& list);
void ChuyenLenDauTien(SList& list, char ten[]);

int main()
{
	process();
	_getch();
	return 0;
}
void menu()
{
	printf("0. Thoat chuong trinh!\n");
	printf("1. Tao danh sach (Doc FILE)\n");
	printf("2. Xuat danh sach\n");
	printf("3. Tinh tong thoi gian nghe tat ca bai hat trong PlayList\n");
	printf("4. Them mot bai hat moi vao dau PlayList/ cuoi PlayList\n");
	printf("5. Xoa mot bai hat ra khoi danh sach\n");
	printf("6. Kiem tra bai hat X co trong danh sach hay ko\n");
	printf("7. Sap xep tang dan theo ten bai hat\n");
	printf("8. Sap xep giam dan theo ten ca si\n");
	printf("9. Dua mot bai hat trong PlayList len dau\n");
}
void process()
{
	SList list;
	BaiHat bh;
	int luaChon, x;
	char tenBH[51];
	for (;;)
	{
		system("cls");
		menu();
		printf("Moi nhap lua chon: ");
		scanf_s("%d", &luaChon);
		if (luaChon == 0)
			break;
		switch (luaChon)
		{
		case 1:
			nhapTuFile(list);
			break;
		case 2:
			printf("\nDANH SACH BAI HAT\n\n");
			printList(list);
			break;
		case 3:
			printf("\nTong thoi gian de nghe tat ca bai hat la: %d", tinhTongThoiGianNghe_TatCaBH(list));
			break;
		case 4:
			printf("1. Chen vao dau PlayList\n");
			printf("2. Chen vao cuoi PlayList\n");
			printf("Nhap lua chon: ");
			scanf_s("%d", &x);
			if (x == 1)
			{
				nhapBaiHat(bh);

				Node* pt = createNode(bh);
				if (pt != NULL) //tạo thành công
					insertFirst(list, pt);
			}
			if (x == 2)
			{
				nhapBaiHat(bh);

				Node* pt = createNode(bh);
				if (pt != NULL) //tạo thành công
					insertLast(list, pt);
			}
			break;
		case 5:
			printf("\nDANH SACH BAI HAT\n\n");
			printList(list);
			printf("\n\nNhap ten bai hat can xoa: ");
			rewind(stdin);
			gets_s(tenBH);
			chuanHoaChuoi(tenBH);
			xoaBaiHat(list, tenBH);
			printf("\n\nDANH SACH SAU KHI XOA\n\n");
			printList(list);
			break;
		case 6:
			printf("\n\nNhap ten bai hat: ");
			rewind(stdin);
			gets_s(tenBH);
			chuanHoaChuoi(tenBH);
			if (kiemTraBaiHat(list, tenBH))
				printf("Co bai hat \"%s\" trong PlayList", tenBH);
			else
				printf("Khong co bai hat \"%s\" trong PlayList", tenBH);
			break;
		case 7:
			printf("\nDANH SACH BAI HAT\n\n");
			printList(list);
			interchangeSort_TangDan(list);
			printf("\n\nDANH SACH SAU KHI SAP XEP\n\n");
			printList(list);
			break;
		case 8:
			printf("\nDANH SACH BAI HAT\n\n");
			printList(list);
			interchangeSort_GiamDan(list);
			printf("\n\nDANH SACH SAU KHI SAP XEP\n\n");
			printList(list);
			break;
		case 9:
			printf("\nDANH SACH BAI HAT\n\n");
			printList(list);
			printf("\n\nNhap ten bai hat can chuyen: ");
			rewind(stdin);
			gets_s(tenBH);
			chuanHoaChuoi(tenBH);
			if (kiemTraBaiHat(list, tenBH) == 0)
			{
				printf("\nKhong co bai hat trong PlayList\n");
				//_getch();
				break;
			}
			if (_strcmpi(list.head->info.tenBH, tenBH) == 0)
			{
				printf("\nBai hat dang o dau tien PlayList\n");
				//_getch();
				break;
			}
			ChuyenLenDauTien(list, tenBH);
			printf("\n\nDANH SACH SAU KHI CHUYEN LEN DAU PLAYLIST\n\n");
			printList(list);
			break;

		default:printf("Loi! Vui long nhap lai!\n");
			break;
		}
		_getch();
	}
}

void khoiTao(SList& list)
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
Node* createNode(BaiHat x)
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
void chuanHoaChuoi(char str[])
{
	//chuẩn hoá chuỗi bên trái
	while (str[0] == ' ')
		strcpy_s(str, 50, str + 1);

	//chuẩn hoá chuỗi bên phải
	int len = strlen(str);
	while (str[len - 1] == ' ')
	{
		str[len - 1] = '\0';
		len--;
	}
	//chuẩn hoá ở giữa
	char* p;
	while ((p = strstr(str, "  ")) != NULL)
	{
		strcpy_s(p, 50, p + 1);
	}
}
void nhapTuFile(SList& list)
{
	int n;
	BaiHat x;
	khoiTao(list);

	FILE* f;
	fopen_s(&f, "InfoListOfSongs.txt", "r");
	if (f == NULL)
	{
		printf("Mo File Khong Thanh Cong\n");
		return;
	}

	if (f != NULL)
	{
		//fscanf(f, "%d\n", &n);
		fscanf_s(f, "%d ", &n);
		for (int i = 1; i <= n; i++)
		{
			//fscanf(f, "%[^\#]#%[^\#]#%[^\#]#%d\n", x.tenBH, x.tenTG, x.tenCS, &x.thoiLuong);
			fscanf_s(f, "%[^\#]#%[^\#]#%[^\#]#%d\n", x.tenBH, sizeof(x.tenBH), x.tenTG, sizeof(x.tenTG), x.tenCS, sizeof(x.tenCS), &x.thoiLuong);
			Node* p = new Node;
			p = createNode(x);
			if (p)//tạo thành công
				insertLast(list, p);
		}
		printf("\nDoc File Thanh Cong!");
	}
	fclose(f);
}
void nhapBaiHat(BaiHat& x)
{
	printf("NHAP THONG TIN BAI HAT MOI\n");
	printf("\nNhap ten bai hat: ");
	rewind(stdin);
	gets_s(x.tenBH);
	chuanHoaChuoi(x.tenBH);
	printf("Nhap ten tac gia: ");
	gets_s(x.tenTG);
	chuanHoaChuoi(x.tenTG);
	printf("Nhap ten ca si: ");
	gets_s(x.tenCS);
	chuanHoaChuoi(x.tenCS);
	printf("Nhap thoi luong (giay): ");
	scanf_s("%d", &x.thoiLuong);
}
void printList(SList list)
{
	printf("%-31s%-21s%-21s%-16s", "Ten Bai Hat", "Ten Tac Gia", "Ten Ca Si", "Thoi Luong");
	for (Node* p = list.head; p != NULL; p = p->next)
		printf("\n%-30s|%-20s|%-20s|%-15d", p->info.tenBH, p->info.tenTG, p->info.tenCS, p->info.thoiLuong);
}
int tinhTongThoiGianNghe_TatCaBH(SList list)
{
	int sum = 0;
	for (Node* p = list.head; p != NULL; p = p->next)
		sum += p->info.thoiLuong;
	return sum;
}
void deleteFirst(SList& list)
{
	//nếu danh sách rỗng
	if (isEmpty(list))
		return;
	Node* p = list.head;
	list.head = list.head->next;
	p->next = NULL;
	//nếu danh sách khi còn 1 phần tử
	if (list.head == NULL)
		list.tail = NULL;
	delete p;
}
void deleteLast(SList& list)
{
	for (Node* p = list.head; p != NULL; p = p->next)
	{
		if (p->next == list.tail)
		{
			delete list.tail;
			p->next = NULL;
			//thay đổi con trỏ tail
			list.tail = p;
		}
	}
}
void deleteAfter(SList& list, Node* q)
{
	if (q == NULL || q->next == NULL)
		return;
	Node* p = q->next;
	q->next = p->next;
	if (p == list.tail)
		list.tail = q;
	delete p;
}
void xoaBaiHat(SList& list, char ten[])
{
	if (_strcmpi(list.head->info.tenBH, ten) == 0)
	{
		deleteFirst(list);
		return;
	}
	if (_strcmpi(list.tail->info.tenBH, ten) == 0)
	{
		deleteLast(list);
		return;
	}
	//Tạo Node p để lưu trữ phần tử trước Node k cần xoá
	Node* p = new Node;
	for (Node* k = list.head; k != NULL; k = k->next)
	{
		if (_strcmpi(k->info.tenBH, ten) == 0)
		{
			//Node k trỏ đâu thì Node p trỏ tới đó
			p->next = k->next;
			delete k;
			return;
		}
		//Node p lưu trữ phần tử trước Node k cần xoá
		p = k;
	}
}
int kiemTraBaiHat(SList list, char ten[])
{
	for (Node* p = list.head; p != NULL; p = p->next)
		if (_strcmpi(p->info.tenBH, ten) == 0)
			return 1;
	return 0;
}
void swap(BaiHat& a, BaiHat& b)
{
	BaiHat temp = a;
	a = b;
	b = temp;
}
void interchangeSort_TangDan(SList& list)
{
	for (Node* p = list.head; p != NULL; p = p->next)
		for (Node* q = p->next; q != NULL; q = q->next)
			if (_strcmpi(p->info.tenBH, q->info.tenBH) > 0)
				swap(p->info, q->info);
}
void interchangeSort_GiamDan(SList& list)
{
	for (Node* p = list.head; p != NULL; p = p->next)
		for (Node* q = p->next; q != NULL; q = q->next)
			if (_strcmpi(p->info.tenCS, q->info.tenCS) < 0)
				swap(p->info, q->info);
}
void ChuyenLenDauTien(SList& list, char ten[])
{
	Node* k = new Node; //Lưu Node cần chuyển

	for (Node* p = list.head; p != NULL; p = p->next)
	{
		if (_strcmpi(p->next->info.tenBH, ten) == 0)
		{
			k->info = p->next->info;
			k->next = NULL;
			//p->next tại 4 của 4-5-6 thì i->next trỏ tới 6
			p->next = p->next->next;
			break;
		}
	}
	insertFirst(list, k);
}

//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct MonHoc
{
	char maMH[10];
	char tenMH[31];
	int soTinChi;
	double diemTL, diemCK, diemMH;
	
};
struct NodeMH
{
	MonHoc info;
	NodeMH* next;
};
struct SListMH
{
	NodeMH* head;
	NodeMH* tail;
};
struct SinhVien
{
	char maSV[11];
	char hoDem[26];
	char tenSV[9];
	int namSinh;
	double diemKQ;
	SListMH DSMonHoc;
};
struct NodeSV
{
	SinhVien info;
	NodeSV* next;
};
struct SListSV
{
	NodeSV* head;
	NodeSV* tail;
};

void menu();
void process();

//Hàm liên quan về thông tin môn học
void initSListMH(SListMH& list);
int isEmptyMH(SListMH list);
NodeMH* createNodeMH(MonHoc x);
void insertLastMH(SListMH& list, NodeMH* p);

//Hàm liên quan về thông tin sinh viên
void initSListSV(SListSV& list);
int isEmptySV(SListSV list);
NodeSV* createNodeSV(SinhVien x);
void insertFirst(SListSV& listSV, NodeSV* p);
void insertLastSV(SListSV& list, NodeSV* p);
void nhapTuFile(SListSV& listSV);
void printList(SListSV listSV);
void xuatThongTinSinhVien(SListSV listSV, NodeSV* p);

void hoTenVaDiem_SinhVienX(SListSV listSV, char str[]);
void inThongTinSinhVienX(SListSV listSV, char str[]);
void swap(SinhVien& a, SinhVien& b);
void interchangeSort_MaSVTangDan(SListSV& listSV);
void interchangeSort_TenSVTangDan(SListSV& listSV);
NodeSV* findNodeSV(SListSV listSV, char str[]);
int kiemTraTenSV(SListSV listSV, char ten[]);
void insertBefore(SListSV& listSV, NodeSV* q, NodeSV* p);
void nhapThongTinSinhVien(SinhVien& sv);
void deleteFirst(SListSV& listSV);
void deleteLast(SListSV& listSV);
void deleteElement(SListSV& listSV, char str[]);
void xoaThongTinTenX(SListSV& listSV, char ten[]);

int main()
{
	process();

	_getch();
	return 0;
}
void menu()
{
	printf("0. Thoat chuong trinh\n");
	printf("1. Tao Danh Sach (Doc File)\n");
	printf("2. Xuat Danh Sach\n");
	printf("3. Cho biet Ho Ten va Diem Ket Qua Hoc Tap cua sinh vien X\n");
	printf("4. Cho biet Cac Thong Tin ve sinh vien ten X\n");
	printf("5. Sap xep danh sach tang dan theo Ma So Sinh Vien\n");
	printf("6. Sap xep danh sach tang dan theo Ten Sinh Vien\n");
	printf("7. Them Mot SV sao cho van giu nguyen thu tu tang dan theo Ma So SV\n");
	printf("8. Xoa SV co Ma So X\n");
	printf("9. Xoa Tat Ca SV co ten X\n");
}
void process()
{
	SListSV listSV;
	int luaChon;
	char str[30];
	NodeSV* p = new NodeSV;
	SinhVien sv;

	for (;;)
	{
		system("cls");
		menu();
		printf("Moi nhap lua chon: ");
		scanf_s("%d", &luaChon);
		if (luaChon == 0)
			break;
		switch(luaChon)
		{
		case 1:
			nhapTuFile(listSV);
			printf("\nDoc Danh Sach Tu File Thanh Cong");
			//printList(listSV);
			break;
		case 2:
			printList(listSV);
			break;
		case 3:
			printf("Nhap ma so SV: ");
			rewind(stdin);
			gets_s(str);
			hoTenVaDiem_SinhVienX(listSV, str);
			break;
		case 4:
			printf("Nhap ten SV: ");
			rewind(stdin);
			gets_s(str);
			inThongTinSinhVienX(listSV, str);
			break;
		case 5:
			interchangeSort_MaSVTangDan(listSV);
			printf("\nSap Xep Thanh Cong");
			printList(listSV);
			break;
		case 6:
			interchangeSort_TenSVTangDan(listSV);
			printf("\nSap Xep Thanh Cong");
			printList(listSV);
			break;
		case 7:
			interchangeSort_MaSVTangDan(listSV);
			nhapThongTinSinhVien(sv);
			//Tạo Node lưu thông tin sinh viên
			p = createNodeSV(sv);

			for (NodeSV* k = listSV.head; k != NULL; k = k->next)
			{
				if (_strcmpi(k->info.maSV, p->info.maSV) > 0)
				{
					insertBefore(listSV, k, p);
					break;
				}
			}
			if (_strcmpi(listSV.tail->info.maSV, p->info.maSV) <= 0)
			{
				insertLastSV(listSV, p);
			}
			printf("\nThem mot sinh vien thanh cong!");
			break;
		case 8:
			printf("Nhap ma so SV can xoa: ");
			rewind(stdin);
			gets_s(str);
			deleteElement(listSV, str);
			printf("\nXoa sinh vien co ma SV \'%s\' thanh cong!", str);
			break;
		case 9:
			printf("Nhap ten SV can xoa: ");
			rewind(stdin);
			gets_s(str);
			if(kiemTraTenSV(listSV, str) == 0)
			{
				printf("\nKhong co ten SV nay trong danh sach\n");
			}
			else
			{
				xoaThongTinTenX(listSV, str);
				printf("\nDa xoa tat ca sinh vien co ten \'%s\'", str);
			}
			break;
		default:printf("Loi! Vui long nhap lai!\n");
			break;
		}
		_getch();
	}
}
//Danh Sách Liên Kết Đơn Môn Học
void initSListMH(SListMH& list)
{
	list.head = NULL;
	list.tail = NULL;
}
int isEmptyMH(SListMH list)
{
	if (list.head == NULL)
		return 1;//Danh sách rỗng
	return 0;//Danh sách ko rỗng
}
NodeMH* createNodeMH(MonHoc x)
{
	NodeMH* p = new NodeMH;
	if (p == NULL)
	{
		printf("\nKhong Du Bo Nho");
		return NULL;
	}
	p->info = x;
	p->next = NULL;
	return p;
}
void insertLastMH(SListMH& list, NodeMH* p)
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
//Danh Sách Liên Kết Đơn Sinh Viên
void initSListSV(SListSV& list)
{
	list.head = NULL;
	list.tail = NULL;
}
int isEmptySV(SListSV list)
{
	if (list.head == NULL)
		return 1;//danh sách rỗng
	return 0;//danh sách không rỗng
}
NodeSV* createNodeSV(SinhVien x)
{
	NodeSV* p = new NodeSV;
	if (p == NULL)
	{
		printf("\nKhong Du Bo Nho");
		return NULL;
	}
	p->info = x;
	p->next = NULL;
	return p;
}
void insertFirst(SListSV& listSV, NodeSV* p)
{
	if (listSV.head == NULL)
	{
		listSV.head = p;
		listSV.tail = p;
	}
	else
	{
		p->next = listSV.head;
		listSV.head = p;
	}
}
void insertLastSV(SListSV& list, NodeSV* p)
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
void nhapTuFile(SListSV& listSV)
{
	int i, n, tongTinChi = 0;
	SinhVien sv;
	SListMH listMH;
	double tongDiemMonHoc = 0;
	//Khởi tạo danh sách sinh viên
	initSListSV(listSV);

	FILE* f;
	fopen_s(&f, "StudentInformation.txt", "r");

	if (f == NULL)
	{
		printf("\nKhong Mo File Thanh Cong!");
		return;
	}

	while (!feof(f))
	{
		fscanf_s(f, "%[^#]#%[^#]#%[^#]#%d\n", sv.maSV, sizeof(sv.maSV), sv.hoDem, sizeof(sv.hoDem), sv.tenSV, sizeof(sv.tenSV), &sv.namSinh);
		
		fscanf_s(f, "%d\n", &n);
		MonHoc x;
		//Khởi tạo danh sách môn học
		initSListMH(listMH);
		for (i = 1; i <= n; i++)
		{
			
			fscanf_s(f, "%[^#]#%[^#]#%d%lf%lf\n", x.maMH, sizeof(x.maMH), x.tenMH, sizeof(x.tenMH), &x.soTinChi, &x.diemTL, &x.diemCK);
			x.diemMH = 0.3 *x.diemTL + 0.7 *x.diemCK;
			tongDiemMonHoc += x.diemMH * x.soTinChi;
			tongTinChi += x.soTinChi;
			//Tạo Node lưu thông tin môn học
			NodeMH* k = new NodeMH;
			k = createNodeMH(x);
			if (k)//tạo thành công
				insertLastMH(listMH, k);
		}
		sv.diemKQ = tongDiemMonHoc / (double)tongTinChi;
		//Copy toàn bộ danh sách môn học vừa tạo vào trong thông tin của sinh viên này
		sv.DSMonHoc = listMH;
		//Tạo Node lưu thông tin sinh viên
		NodeSV* p = new NodeSV;
		p = createNodeSV(sv);
		if (p)//tạo thành công
			insertLastSV(listSV, p);
	}
	fclose(f);
}
void printList(SListSV listSV)
{
	for (NodeSV* p = listSV.head; p != NULL; p = p->next)
	{
		xuatThongTinSinhVien(listSV, p);
	}
}
void xuatThongTinSinhVien(SListSV listSV, NodeSV* p)
{
	printf("\n\n\n%-15s|%-20s|%-11s|%10s|%10s|", "Ma SV", "Ho Dem", "Ten SV", "Nam Sinh", "Diem KQ");
	printf("\n%-15s|%-20s|%-11s|%10d|%10.2lf|", p->info.maSV, p->info.hoDem, p->info.tenSV, p->info.namSinh, p->info.diemKQ);

	printf("\n\n%-15s|%-20s|%11s|%10s|%10s|%10s|", "Ma Mon Hoc", "Ten Mon Hoc", "So Tin Chi", "Diem TL", "Diem CK", "Diem MH");
	for (NodeMH* k = p->info.DSMonHoc.head; k != NULL; k = k->next)
	{
		printf("\n%-15s|%-20s|%11d|%10.2lf|%10.2lf|%10.2lf|", k->info.maMH, k->info.tenMH, k->info.soTinChi, k->info.diemTL, k->info.diemCK, k->info.diemMH);
	}
	printf("\n----------------------------------------------------------------------------------");
}
void nhapThongTinSinhVien(SinhVien& sv)
{
	MonHoc x;
	int n, tongTinChi = 0;
	double tongDiemMonHoc = 0;

	printf("\nNHAP THONG TIN SINH VIEN");
	printf("\nNhap ma so SV: ");
	rewind(stdin);
	gets_s(sv.maSV);
	printf("Nhap ho dem: ");
	gets_s(sv.hoDem);
	printf("Nhap ten SV: ");
	gets_s(sv.tenSV);
	printf("Nhap nam sinh: ");
	scanf_s("%d", &sv.namSinh);

	//Khởi tạo danh sách môn học
	initSListMH(sv.DSMonHoc);

	printf("\nNhap so luong mon hoc: ");
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		printf("\nThong Tin Mon Thu %d", i);
		printf("\nNhap ma mon hoc: ");
		rewind(stdin);
		gets_s(x.maMH);
		printf("Nhap ten mon hoc: ");
		gets_s(x.tenMH);
		printf("Nhap so tin chi: ");
		scanf_s("%d", &x.soTinChi);
		printf("Nhap diem Tieu Luan: ");
		scanf_s("%lf", &x.diemTL);
		printf("Nhap diem Cuoi Ky: ");
		scanf_s("%lf", &x.diemCK);
		x.diemMH = 0.3 * x.diemTL + 0.7 * x.diemCK;
		tongDiemMonHoc += x.diemMH * x.soTinChi;
		tongTinChi += x.soTinChi;
		//Tạo Node lưu thông tin môn học
		NodeMH* k = new NodeMH;
		k = createNodeMH(x);
		if (k)//tạo thành công
			insertLastMH(sv.DSMonHoc, k);
	}
	sv.diemKQ = tongDiemMonHoc / (double)tongTinChi;
}
void hoTenVaDiem_SinhVienX(SListSV listSV, char str[])
{
	for(NodeSV* p = listSV.head;p!=NULL;p=p->next)
		if (_strcmpi(p->info.maSV, str) == 0)
		{
			printf("\nHo va ten: %s %s", p->info.hoDem, p->info.tenSV);
			printf("\nDiem ket qua hoc tap: %.2lf", p->info.diemKQ);
			return;
		}
	printf("\nKhong co ma SV \'%s\' trong danh sach", str);
}
void inThongTinSinhVienX(SListSV listSV, char str[])
{
	for (NodeSV* p = listSV.head; p != NULL; p = p->next)
		if (_strcmpi(p->info.tenSV, str) == 0)
			xuatThongTinSinhVien(listSV, p);
}
void swap(SinhVien& a, SinhVien& b)
{
	SinhVien temp = a;
	a = b;
	b = temp;
}
void interchangeSort_MaSVTangDan(SListSV& listSV)
{
	for (NodeSV* p = listSV.head; p != NULL; p = p->next)
		for (NodeSV* q = p->next; q != NULL; q = q->next)
			if (_strcmpi(p->info.maSV, q->info.maSV) > 0)
				swap(p->info, q->info);
}
void interchangeSort_TenSVTangDan(SListSV& listSV)
{
	for (NodeSV* p = listSV.head; p != NULL; p = p->next)
		for (NodeSV* q = p->next; q != NULL; q = q->next)
			if (_strcmpi(p->info.tenSV, q->info.tenSV) > 0)
				swap(p->info, q->info);
}
NodeSV* findNodeSV(SListSV listSV, char str[])
{
	for (NodeSV* p = listSV.head; p != NULL; p = p->next)
		if (_strcmpi(p->info.maSV, str) == 0)
			return p;
	return NULL;
}
int kiemTraTenSV(SListSV listSV, char ten[])
{
	for (NodeSV* p = listSV.head; p != NULL; p = p->next)
		if (_strcmpi(p->info.tenSV, ten) == 0)
			return 1;
	return 0;
}
void insertBefore(SListSV& listSV, NodeSV* q, NodeSV* p)
{
	//nếu không tồn tại Node q thì không thực hiện
	if (q == NULL)
	{
		printf("\nKhong ton tai ma SV trong danh sach");
		return;
	}
	//Tìm phần tử đứng trước Node q
	NodeSV* t = listSV.head;
	
	if (_strcmpi(t->info.maSV, q->info.maSV) == 0)
		insertFirst(listSV, p);
	else
	{
		while (_strcmpi(t->next->info.maSV, q->info.maSV) != 0)
		{
			t = t->next;
		}
		//t->next trỏ đến đâu thì p->next cũng trỏ tới đó
		p->next = t->next;
		//t->next trỏ vào Node p
		t->next = p;
	}
}
void deleteFirst(SListSV& listSV)
{
	//nếu danh sách rỗng
	if (isEmptySV(listSV))
		return;
	NodeSV* p = listSV.head;
	listSV.head = listSV.head->next;
	p->next = NULL;
	//nếu danh sách khi còn 1 phần tử
	if (listSV.head == NULL)
		listSV.tail = NULL;
	delete p;
}
void deleteLast(SListSV& listSV)
{
	for (NodeSV* p = listSV.head; p != NULL; p = p->next)
	{
		if (p->next == listSV.tail)
		{
			//xoá phần tử cuối
			delete listSV.tail;
			p->next = NULL;
			//thay đổi con trỏ tail
			listSV.tail = p;
		}
	}
}
void deleteElement(SListSV& listSV, char str[])
{
	//Nếu data đầu vào bằng list.head->info thì xoá đầu
	if (_strcmpi(listSV.head->info.maSV, str) == 0)
	{
		deleteFirst(listSV);
		return;
	}
	//Nếu data đầu vào bằng list.tail->info thì xoá cuối
	if (_strcmpi(listSV.tail->info.maSV, str) == 0)
	{
		deleteLast(listSV);
		return;
	}
	//Tạo Node p để lưu trữ phần tử trước Node k cần xoá
	NodeSV* p = new NodeSV;
	for (NodeSV* k = listSV.head; k != NULL; k = k->next)
	{
		if (_strcmpi(k->info.maSV, str) == 0)
		{
			//Node k trỏ đâu thì Node p trỏ tới đó
			p->next = k->next;
			delete k;
			return;
		}
		//Gắn Node p bằng Node k để Node p luôn là Node đứng trước Node k
		p = k;
	}
}
void xoaThongTinTenX(SListSV& listSV, char ten[])
{
	if (_strcmpi(listSV.head->info.tenSV, ten) == 0)
	{
		deleteFirst(listSV);
	}
	if (_strcmpi(listSV.tail->info.tenSV, ten) == 0)
	{
		deleteLast(listSV);
	}
	//Tạo Node p để lưu trữ phần tử trước Node k cần xoá
	NodeSV* p = new NodeSV;
	for (NodeSV* k = listSV.head; k != NULL; k = k->next)
	{
		if (_strcmpi(k->info.tenSV, ten) == 0)
		{
			//Node k trỏ đâu thì Node p trỏ tới đó
			p->next = k->next;
			delete k;
			//Xét lại vị trí vừa xoá
			k = p;
		}
		//Node p lưu trữ phần tử trước Node k cần xoá
		p = k;
	}
}

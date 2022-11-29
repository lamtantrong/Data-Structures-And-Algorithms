#ifndef BST
#define BST

/*
Dùng kiểu dữ liệu cấu trúc khác thì khai báo Struct ở đây
Và ở dòng typedef thay "int" thành "Tên Struct" vừa tạo
*/

 typedef int ItemType;
struct TNode
{
	ItemType Info;
	TNode* Left;
	TNode* Right;
};
struct BSTree
{
	TNode* Root;
};

/*
//Khai báo các prototype của hàm tự tạo (khai báo định nghĩa hàm)
//Khai báo ở đây (dưới Struct BSTree - trên #endif)
*/

#endif

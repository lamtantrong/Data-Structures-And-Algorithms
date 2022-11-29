#ifndef AVL
#define AVL

#define LH -1	//cây con trái cao hơn
#define EH 0	//cây cơn trái bằng cây con phải
#define RH 1	//cây con phải cao hơn
typedef int ItemType;
struct AVLNode
{
	int balFactor;//chỉ số cân bằng của cây
	ItemType Info;
	AVLNode* Left;
	AVLNode* Right;
};
struct AVLTree
{
	AVLNode* Root;
};
void menu();
AVLNode* createAVLNode(ItemType x);
void initAVLTree(AVLTree& avl);
void rotateLL(AVLNode*& T);
void rotateLR(AVLNode*& T);
void rotateRL(AVLNode*& T);
void rotateRR(AVLNode*& T);
int balanceLeft(AVLNode*& T);
int balanceRight(AVLNode*& T);
int insertAVLNode(AVLNode*& T, AVLNode* p);
void createAVLTree_FromFile(AVLTree& avl);
int searchStandFor_MinRight(AVLNode*& p, AVLNode*& q);
int searchStandFor_MaxLeft(AVLNode*& p, AVLNode*& q);
int deleteAVLNode(AVLNode*& T, ItemType x);

#endif

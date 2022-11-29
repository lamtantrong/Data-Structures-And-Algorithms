#ifndef ascii
#define ascii
#include"AVL_Tree.h"
#include<stdio.h>
#include<string.h>

struct asciinode
{
    asciinode *left;
    asciinode *right;   
    
    int edge_length;//length of the edge from this node to its children
    int height;
    int lablen;

    int parent_dir; //-1=I am left, 0=I am root, 1=right   
    char label[11];//max supported unit32 in dec, 10 digits max
};


int MIN(int X, int Y);
int MAX(int X, int Y);

asciinode* build_ascii_tree_recursive(AVLNode* t);
//Copy the tree into the ascii node structre
asciinode* build_ascii_tree(AVLNode* t);


//Free all the nodes of the given tree
void deleteAscii(asciinode* root);

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode* node, int x, int y);

void compute_rprofile(asciinode* node, int x, int y);

//This function fills in the edge_length and 
//height fields of the specified tree
void compute_edge_lengths(asciinode* node);

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode* node, int x, int level);

//prints ascii tree for given Tree structure
void print_ascii_tree(AVLNode* t);



#endif

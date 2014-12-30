#ifndef AVL_H_
#define AVL_H_

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "data.h"


// create a new AVL Leaf
struct avlLeaf* createAvlLeaf(struct data *d);

// Createa new AVL Tree
struct avlTree* createAvlTree();

// insert a new node in AVL tree
void insertAvl(struct avlTree *t,struct data *d);
void insertAvl_r(struct avlTree *t,struct avlLeaf* current,struct avlLeaf* newLeaf);

// Print all nodes of AVL tree in inOrder sequence
void inOrderAvl(struct avlTree *t);
void inOrderAvl_r(struct avlLeaf *current);

// rotate right
void rotateRight(struct avlTree *t,struct avlLeaf *current);

// rotate left
void rotateLeft(struct avlTree *t,struct avlLeaf *current);

// return height of input AVL node
int getHeight(struct avlLeaf *lf);

// return balance factor of input AVL node
int getBalanceFact(struct avlLeaf *lf);

// free all memory associated with the avl tree.
void cleanAvl(struct avlTree *t);
void cleanAvl_r(struct avlLeaf *lf);

// Search a node in AVL tree
int searchAvl(struct avlTree *t,struct data *d);
int searchAvl_r(struct avlLeaf *curr,struct data *d);

// helper function to return maximum of 2 integers
int max(int a, int b);

#endif

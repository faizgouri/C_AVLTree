#include "avl.h"

int searchAvl(struct avlTree *t,struct data *d)
{
	if(t->root == NULL)
	{
		return 0;
	}
	return (searchAvl_r(t->root, d));
}

int searchAvl_r(struct avlLeaf *curr,struct data *d)
{
	if(curr == NULL)
	{
		return 0;
	}
	if(compareData(curr->dta, d) == 1)
	{
		return 1;
	}
	if(sumData(d) < sumData(curr->dta))
	{
		return searchAvl_r(curr->left, d);
	}
	else
	{
		return searchAvl_r(curr->right, d);
	}
}

void cleanAvl(struct avlTree *t)
{
	if(t->root != NULL)
	{
		cleanAvl_r(t->root);
	}
	free(t);
}

void cleanAvl_r(struct avlLeaf *lf)
{
	if(lf->left == NULL && lf->right == NULL)
	{
		free(lf->dta);
		free(lf);
		return;
	}
	if(lf->left != NULL)
	{
		cleanAvl_r(lf->left);
	}
	if(lf->right != NULL)
	{
		cleanAvl_r(lf->right);
	}
	free(lf->dta);
	free(lf);
}

void inOrderAvl(struct avlTree *t)
{
	if(t->root == NULL)
	{
		printf("Tree is Empty !!\n");
		return;
	}
	inOrderAvl_r(t->root);
}

void inOrderAvl_r(struct avlLeaf *current)
{
	if(current == NULL)
	{
		return;
	}
	inOrderAvl_r(current->left);
	printData(current->dta);
	inOrderAvl_r(current->right);
}

void insertAvl(struct avlTree *t,struct data *d)
{
	struct avlLeaf *newLeaf = createAvlLeaf(d);
	if(t->root == NULL)
        {
		t->root = newLeaf;
		return;
        }
        insertAvl_r(t, t->root, newLeaf);

	// We can update height of every node after inserting a new node
/*	struct avlLeaf *temp = newLeaf;
	for(; temp != NULL; temp = temp->parent)
	{
		temp->height = getHeight(temp);
	}

*/}

void insertAvl_r(struct avlTree *t,struct avlLeaf* current,struct avlLeaf* newLeaf)
{
	int bal = 0;
        if(sumData(newLeaf->dta) > sumData(current->dta))
        {
                if(current->right == NULL)
                {
                        current->right = newLeaf;
                        newLeaf->parent = current;
                }
                else
                {
                        insertAvl_r(t, current->right, newLeaf);
                }
        }
        else
        {
                if(current->left == NULL)
                {
                        current->left = newLeaf;
                        newLeaf->parent = current;
                }
                else
                {
                        insertAvl_r(t, current->left, newLeaf);
                }
        }

	if(newLeaf == t->root || newLeaf->parent == t->root)
	{
		return;
	}

	// otherwise
	struct avlLeaf *unbal = newLeaf->parent->parent;
	bal = getBalanceFact(unbal);
	if(bal > 1)
	{
		if(getBalanceFact(unbal->right) < 0)
		{
			rotateRight(t, unbal->right);
		}
		rotateLeft(t, unbal);
	}
	if(bal < (-1))
	{
		if(getBalanceFact(unbal->left) > 0) // if balFact of left is positive, then 
		{
			rotateLeft(t, unbal->left);
		}
		rotateRight(t, unbal);
	}
}

void rotateRight(struct avlTree *t,struct avlLeaf *current)
{
	struct avlLeaf *temp = current->left;
        current->left = temp->right;
	if(temp->right != NULL)
	{
		current->left->parent = current;
	}
	temp->right = current;
	temp->parent = current->parent;
	if(temp->parent == NULL)
	{
		t->root = temp;
	}
	else if(current->parent->left == current)
	{
		current->parent->left = temp;
	}
	// otherwise update parent's right
	else
	{
		current->parent->right = temp;
	}
	current->parent = temp;
}

void rotateLeft(struct avlTree *t, struct avlLeaf *current)
{
	struct avlLeaf *temp = current->right;
	current->right = temp->left;
	if(temp->left != NULL)
	{
		current->right->parent = current;
	}
	temp->left = current;
	temp->parent = current->parent;
	if(current->parent == NULL)
	{
		t->root = temp;
	}
	else if(current->parent->left == current)
	{
		current->parent->left = temp;
	}
	else
	{
		current->parent->right = temp;
	}
	current->parent = temp;
}

struct avlLeaf* createAvlLeaf(struct data *d)
{
  struct avlLeaf* maple = malloc(sizeof(struct avlLeaf));
  maple->right = NULL;
  maple->left = NULL;
  maple->parent = NULL;
  maple->dta = d;
  maple->height = 1;
  return maple;
}

struct avlTree* createAvlTree()
{
  struct avlTree* oak = malloc(sizeof(struct avlTree));
  oak->root = NULL;
  return oak;
}

int getHeight(struct avlLeaf *lf)
{
	if(lf == NULL)
	{
		return 0;
	}
	return (max(getHeight(lf->left), getHeight(lf->right)) + 1);
}

int max(int a, int b)
{
	return ((a > b) ? a : b);
}

int getBalanceFact(struct avlLeaf *lf)
{
	return ((getHeight(lf->right)) - (getHeight(lf->left)));
}

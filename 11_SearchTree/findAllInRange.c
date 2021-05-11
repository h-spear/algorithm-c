#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b) ? (a) : (b))

typedef struct TreeNode {
	int key, height;
	struct TreeNode* parent, * left, * right;
}TreeNode;

typedef struct {
	TreeNode* root;
}TreeType;

void initTree(TreeType* T)
{
	T->root = (TreeNode*)malloc(sizeof(TreeNode));
	T->root->parent = T->root->left = T->root->right = NULL;
	T->root->height = 0;
}

int isExternal(TreeNode* w)
{
	return (w->left == NULL && w->right == NULL);
}

void expandExternal(TreeNode* w)
{
	TreeNode* l = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* r = (TreeNode*)malloc(sizeof(TreeNode));
	l->left = NULL;
	l->right = NULL;
	l->parent = w;
	r->left = NULL;
	r->right = NULL;
	r->parent = w;
	w->left = l;
	w->right = r;
}

TreeNode* sibling(TreeNode* z)
{
	if (z->parent->left == z)
		return z->parent->right;
	else
		return z->parent->left;
}

TreeNode* reduceExternal(TreeType* T, TreeNode* z)
{
	TreeNode* w = z->parent;
	TreeNode* g = w->parent;
	TreeNode* zs = sibling(z);
	zs->parent = g;

	if (g == NULL)	// 자신이 루트
	{
		T->root = zs;
	}
	else
	{
		if (w == g->left)
			g->left = zs;
		else
			g->right = zs;
	}
	free(z);
	free(w);
	return zs;
}

TreeNode* treeSearch(TreeNode* v, int k)
{
	if (isExternal(v))
		return v;
	if (k == v->key)
		return v;
	else if (k < v->key)
		return treeSearch(v->left, k);
	else
		return treeSearch(v->right, k);
}

TreeNode* restructure(TreeType* T, TreeNode* x)
{
	TreeNode* y, * z, * a, * b, * c, * T0, * T1, * T2, * T3;

	y = x->parent;
	z = y->parent;

	if (z->key < y->key && y->key < x->key) //RR
	{
		a = z;
		b = y;
		c = x;
		T0 = a->left;
		T1 = b->left;
		T2 = c->left;
		T3 = c->right;
	}
	else if (x->key < y->key && y->key < z->key) //LL
	{
		a = x;
		b = y;
		c = z;
		T0 = a->left;
		T1 = a->right;
		T2 = b->right;
		T3 = c->right;
	}
	else if (z->key < x->key && x->key < y->key) //RL
	{
		a = z;
		b = x;
		c = y;
		T0 = a->left;
		T1 = b->left;
		T2 = b->right;
		T3 = c->right;
	}
	else //LR
	{
		a = y;
		b = x;
		c = z;
		T0 = a->left;
		T1 = b->left;
		T2 = b->right;
		T3 = c->right;
	}

	// 3.
	if (z == T->root)
	{
		T->root = b;
		b->parent = NULL;
	}
	else if (z->parent->left == z)
	{
		z->parent->left = b;
		b->parent = z->parent;
	}
	else
	{
		z->parent->right = b;
		b->parent = z->parent;
	}

	// 4.
	a->left = T0;
	T0->parent = a;
	a->right = T1;
	T1->parent = a;
	a->height = MAX(T0->height, T1->height) + 1;

	// 5.
	c->left = T2;
	T2->parent = c;
	c->right = T3;
	T3->parent = c;
	c->height = MAX(T2->height, T3->height) + 1;

	// 6.
	b->left = a;
	a->parent = b;
	b->right = c;
	c->parent = b;
	b->height = MAX(a->height, c->height) + 1;

	return b;
}

int heightUpdateAndBalanceCheck(TreeNode* w)
{
	TreeNode* l, * r;
	int b;

	if (w == NULL)
		return 1;

	l = w->left;
	r = w->right;

	w->height = MAX(r->height, l->height) + 1;
	b = r->height - l->height;

	if (b * b < 2)
		return 1;
	else
		return 0;
}

void searchAndFixAfterInsertion(TreeType* T, TreeNode* w)
{
	TreeNode* z = w;
	TreeNode* y, * x;

	// 1. ---------------
	while (heightUpdateAndBalanceCheck(z))
	{
		if (z == NULL)
			return;
		z = z->parent;
	}

	// 2. ---------------
	if (z->left->height > z->right->height)
		y = z->left;
	else
		y = z->right;


	// 3. ---------------
	if (y->left->height > y->right->height)
		x = y->left;
	else if (y->left->height < y->right->height)
		x = y->right;


	// 4. ---------------
	restructure(T, x);
}

void insertItem(TreeType* T, int k)
{
	TreeNode* w = treeSearch(T->root, k);
	if (!isExternal(w))
		return;
	else
	{
		w->key = k;
		expandExternal(w);
		searchAndFixAfterInsertion(T, w);
	}
}

TreeNode* inOrderSucc(TreeNode* w)
{
	w = w->right;
	while (w->left != NULL)
		w = w->left;
	return w;
}

void searchAndFixAfterRemoval(TreeType* T, TreeNode* w)
{
	TreeNode* z = w;
	TreeNode* y, * x, * b;
	x = NULL;

	while (heightUpdateAndBalanceCheck(z))
	{
		if (z == NULL)
			return;
		z = z->parent;
	}

	// 2.----------
	if (z->left->height > z->right->height)
		y = z->left;
	else
		y = z->right;

	// 3.------------
	if (y->left->height > y->right->height)
		x = y->left;
	else if (y->left->height < y->right->height)
		x = y->right;
	else if (z->left == y)
		x = y->left;
	else if (z->right == y)
		x = y->right;

	// 4.-----------
	b = restructure(T, x);

	// 5.--------------
	searchAndFixAfterRemoval(T, b);
}

int removeElement(TreeType* T, int k)
{
	TreeNode* w, * z, * y, * zs;

	w = treeSearch(T->root, k);

	if (isExternal(w))
		return 0;
	z = w->left;
	if (!isExternal(z))	// case1: z가 내부노드라면
		z = w->right;
	if (isExternal(z))
		zs = reduceExternal(T, z);

	else		// case2: 자식이 둘 다 내부노드
	{
		z = inOrderSucc(w);
		y = z->parent;
		w->key = y->key;
		zs = reduceExternal(T, z);

	}
	searchAndFixAfterRemoval(T, zs->parent);
	return k;
}

int findElement(TreeType* T, int k)
{
	TreeNode* w = treeSearch(T->root, k);

	if (isExternal(w))
		return 0;
	else
		return w->key;
}

void preOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	printf("[%d] ", root->key);
	preOrder(root->left);
	preOrder(root->right);
}

void rFindAllInRange(TreeNode* v, int k1, int k2)
{
	if (isExternal(v))
		return;
	if (k1 <= v->key && v->key < k2)
		printf("[%d] ", v->key);
	if (v->key <= k1)
		rFindAllInRange(v->right, k1, k2);
	else if (k2 <= v->key)
		rFindAllInRange(v->left, k1, k2);
	else
	{
		rFindAllInRange(v->left, k1, k2);
		rFindAllInRange(v->right, k1, k2);
	}
}

int main()
{
	TreeType* T = (TreeType*)malloc(sizeof(TreeType));
	initTree(T);

	insertItem(T, 44);
	insertItem(T, 17);
	insertItem(T, 32);
	insertItem(T, 78);
	insertItem(T, 50);
	insertItem(T, 88);
	insertItem(T, 48);
	insertItem(T, 62);
	insertItem(T, 54);


	removeElement(T, 32);
	preOrder(T->root); printf("\n");

	rFindAllInRange(T->root, 50, 80);
	return 0;
}
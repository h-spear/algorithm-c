#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
	int height;
	int vote;
	struct TreeNode* parent, * left, * right;
}TreeNode;

typedef struct {
	TreeNode* root;
}TreeType;

void* xmalloc(size_t size)
{
	void* p;
	p = malloc(size);
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return p;
}

void initTree(TreeType* T)
{
	T->root = (TreeNode*)xmalloc(sizeof(TreeNode));
	T->root->parent = T->root->left = T->root->right = NULL;
	T->root->height = 0;
}

int isExternal(TreeNode* z)		// 모조노드인가?
{
	return (z->left == NULL && z->right == NULL);
}

int isInternal(TreeNode* z)
{
	return (z->left != NULL || z->right != NULL);
}

void expandExternal(TreeNode* z)
{
	TreeNode* l = (TreeNode*)xmalloc(sizeof(TreeNode));
	TreeNode* r = (TreeNode*)xmalloc(sizeof(TreeNode));
	l->left = NULL;
	l->right = NULL;
	l->parent = z;
	r->left = NULL;
	r->right = NULL;
	r->parent = z;
	z->left = l;
	z->right = r;
	return;
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
	if (g == NULL)
		T->root = zs;
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
	a->height = max(T0->height, T1->height) + 1;

	// 5.
	c->left = T2;
	T2->parent = c;
	c->right = T3;
	T3->parent = c;
	c->height = max(T2->height, T3->height) + 1;

	// 6.
	b->left = a;
	a->parent = b;
	b->right = c;
	c->parent = b;
	b->height = max(a->height, c->height) + 1;

	return b;
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

int findElement(TreeType* T, int k)
{
	TreeNode* w = treeSearch(T->root, k);
	if (isExternal(w))
		return -1;	//NoSuchKey
	else
		return w->key;
}

int heightUpdateAndBalanceCheck(TreeNode* z)
{
	TreeNode* l, * r;
	int b;

	if (z == NULL)
		return 1;

	l = z->left;
	r = z->right;

	z->height = max(r->height, l->height) + 1;
	b = r->height - l->height;

	if (b * b < 2)
		return 1;
	else
		return 0;
}

void searchAndFixAfterInsertion(TreeType* T, TreeNode* w)
{
	TreeNode* z = w;
	TreeNode* y, * x = NULL;

	// 1. w에서 루트로 가면서 처음 만나는 불균형 노드 z
	while (heightUpdateAndBalanceCheck(z))
	{
		if (z == NULL)
			return;		// z가 없다면 return
		z = z->parent;
	}

	// 2. z의 높은 자식 y
	if (z->left->height > z->right->height)
		y = z->left;
	else
		y = z->right;


	// 3. y의 높은 자식 x
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
	if (isInternal(w))	// !isExternal(w)
	{
		w->vote++;
		return;			// 이미 노드가 존재
	}
	else
	{
		w->key = k;
		w->vote = 1;
		expandExternal(w);
		searchAndFixAfterInsertion(T, w);	// restructure
	}
}

void rVoteCount(TreeNode* v, int* ptr, int* numptr)
{
	if (isExternal(v))
		return;
	if (*ptr < v->vote)
	{
		*numptr = v->key;
		*ptr = v->vote;
	}

	rVoteCount(v->left, ptr, numptr);
	rVoteCount(v->right, ptr, numptr);
}

void vote(TreeNode* v)
{
	int max = -10000;
	int num = -1;
	int* ptr = &max;
	int* numptr = &num;
	rVoteCount(v, ptr, numptr);
	printf("기호 %d번이 %d표로 당선되었습니다\n", num, max);
}

void inOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	inOrder(root->left);
	printf("기호 %d번 : %d표\n", root->key, root->vote);
	inOrder(root->right);
}

int main()
{
	TreeType* T = (TreeType*)xmalloc(sizeof(TreeType));
	initTree(T);
	insertItem(T, 4);
	insertItem(T, 7);
	insertItem(T, 1);
	insertItem(T, 7);
	insertItem(T, 3);
	insertItem(T, 12);
	insertItem(T, 1);
	insertItem(T, 7);

	inOrder(T->root); printf("\n");
	vote(T->root);
	return 0;
}
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
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

void insertItem(TreeType* T, int k)
{
	TreeNode* w = treeSearch(T->root, k);
	if (isInternal(w))	// !isExternal(w)
		return;			// 이미 노드가 존재
	else
	{
		w->key = k;
		expandExternal(w);
	}
}

TreeNode* inOrderSucc(TreeNode* w)
{
	w = w->right;
	while (w->left != NULL)
		w = w->left;
	return w;
}

int removeElement(TreeType* T, int k)
{
	TreeNode* w = treeSearch(T->root, k);
	if (isExternal(w))
		return -1;	//NoSuchKey
	
	TreeNode* z, * y;
	z = w->left;
	if (!isExternal(z))		// case 1
		z = w->right;
	if (isExternal(z))
		reduceExternal(T,z);
	else	// case 2
	{
		z = inOrderSucc(w);
		y = z->parent;
		w->key = y->key;
		reduceExternal(T, z);
	}
	return k;
}

void preOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	printf("[%d] ", root->key);
	preOrder(root->left);
	preOrder(root->right);
}

void postOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	postOrder(root->left);
	postOrder(root->right);
	printf("[%d] ", root->key);
}

void inOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	inOrder(root->left);
	printf("[%d] ", root->key);
	inOrder(root->right);
}

int main()
{
	TreeType* T = (TreeType*)xmalloc(sizeof(TreeType));
	initTree(T);
	insertItem(T, 9);
	insertItem(T, 2);
	insertItem(T, 1);
	insertItem(T, 7);
	insertItem(T, 5);
	insertItem(T, 3);
	insertItem(T, 4);
	insertItem(T, 8);
	insertItem(T, 15);
	insertItem(T, 11);

	removeElement(T, 2);
	preOrder(T->root); printf("\n");
	inOrder(T->root); printf("\n");
	postOrder(T->root); printf("\n");
	return 0;
}
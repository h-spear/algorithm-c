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

void inOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	inOrder(root->left);
	printf("[%d] ", root->key);
	inOrder(root->right);
}

int findMaxKey(TreeType* T)
{
	TreeNode* v = T->root;
	while (isInternal(v))
		v = v->right;
	return v->parent->key;
}

int findMinKey(TreeType* T)
{
	TreeNode* v = T->root;
	while (isInternal(v))
		v = v->left;
	return v->parent->key;
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
	inOrder(T->root); printf("\n");
	printf("%d %d\n", findMaxKey(T), findMinKey(T));
	return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
	struct TreeNode* parent, * left, * right;
}TreeNode;

typedef struct {
	TreeNode* root;
}TreeType;

void initTree(TreeType* T)
{
	T->root = (TreeNode*)malloc(sizeof(TreeNode));
	T->root->parent = T->root->left = T->root->right = NULL;
}

int isInternal(TreeNode* w)
{
	return (w->left != NULL || w->right != NULL);
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
	while (!isExternal(w))
		w = treeSearch(w->right, k);
	w->key = k;
	expandExternal(w);
}

void preOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	printf("[%d] ", root->key);
	preOrder(root->left);
	preOrder(root->right);
}

void findMaxElements(TreeType* T)
{
	TreeNode* v = T->root;
	while (isInternal(v))
		v = v->right;
	v = v->parent;
	int key = v->key;
	int count = 0;
	while (key == v->key)
	{
		count++;
		if (v->parent == NULL)
			break;
		else
			v = v->parent;
	}
	printf("최대값 %d가 %d개 존재합니다. \n", key, count);
}

void findMinElements(TreeType* T)
{
	TreeNode* v = T->root;
	while (isInternal(v))
		v = v->left;
	v = v->parent;
	int key = v->key;
	int count = 0;
	while (isInternal(v))
	{
		count++;
		v = v->right;
	}
	printf("최대값 %d가 %d개 존재합니다. \n", key, count);
}

int main()
{
	TreeType* T = (TreeType*)malloc(sizeof(TreeType));
	initTree(T);

	insertItem(T, 39);
	insertItem(T, 24);
	insertItem(T, 55);
	insertItem(T, 55);
	insertItem(T, 55);
	insertItem(T, 55);
	insertItem(T, 41);
	insertItem(T, 8);
	insertItem(T, 8);
	insertItem(T, 8);
	insertItem(T, 8);
	insertItem(T, 8);
	insertItem(T, 33);
	insertItem(T, 30);
	insertItem(T, 24);
	insertItem(T, 27);
	insertItem(T, 33);
	insertItem(T, 24);
	insertItem(T, 24);

	preOrder(T->root); printf("\n");
	findMaxElements(T);
	findMinElements(T);
	return 0;
}
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}node;

void* xmalloc(size_t size)
{
	void* p;
	p = malloc(size);
	if (!p)
	{
		perror("xmalloc");
		exit(1);
	}
	return p;
}

node* search(node* root, element key)
{
	node* p = root;

	while (p != NULL)
	{
		if (p->key == key)
		{
			printf("key를 찾았습니다! [ %c ]\n", p->key);
			return p;
		}
		else if (p->key < key)
			p = p->right;
		else
			p = p->left;
	}

	printf("key를 발견하지 못했습니다! [ %c ]\n", key);
	return p;
}

node* insert(node* root, element key)
{
	node* p = root;
	node* parent = NULL;

	while (p != NULL)
	{
		parent = p;
		if (p->key == key)
		{
			printf("이미 key가 존재합니다. [ %c ]\n", p->key);
			return root;
		}
		else if (p->key < key)
			p = p->right;
		else
			p = p->left;
	}

	node* newnode = xmalloc(sizeof(node));
	newnode->key = key;
	newnode->left = NULL;
	newnode->right = NULL;

	if (parent)
	{
		if (parent->key < key)
			parent->right = newnode;
		else
			parent->left = newnode;
	}
	return newnode;
}

node* delete(node* root, element key)
{
	node* p = root;
	node* parent = NULL;

	while (p != NULL && p->key != key)
	{
		parent = p;
		if (p->key < key)
			p = p->right;
		else
			p = p->left;
	}

	if (p == NULL)
	{
		printf("key를 발견하지 못해 삭제할 수 없습니다! [ %c ]\n", key);
		return root;
	}

	if (!p->left && !p->right)
	{
		if (parent == NULL)
			root = NULL;
		else
		{
			if (parent->right == p)
				parent->right = NULL;
			else
				parent->left = NULL;
		}
	}
	else if (!p->left || !p->right)
	{
		node* child;
		child = (p->left != NULL) ? p->left : p->right;
		if (parent == NULL)
			root = child;
		else
		{
			if (parent->right == p)
				parent->right = child;
			else
				parent->left = child;
		}
	}
	else
	{
		//minimum
		node* succ_parent = p;
		node* succ = p->left;

		while (succ->right != NULL)
		{
			succ_parent = succ;
			succ = succ->right;
		}

		p->key = succ->key;
		if (succ_parent->right == succ)
			succ_parent->right = succ->left;
		else
			succ_parent->left = succ->left;
		p = succ;
	}
	free(p);
	return root;
}

void inorder(node* root)
{
	if (!root)
		return;

	inorder(root->left);
	printf("[%c] ", root->key);
	inorder(root->right);
}

int main()
{
	node* root;
	root = insert(NULL, 'G');
	insert(root, 'A');
	insert(root, 'B');
	insert(root, 'H');
	insert(root, 'Y');
	insert(root, 'V');
	insert(root, 'W');
	insert(root, 'C');
	insert(root, 'D');
	insert(root, 'F');
	insert(root, 'O');
	inorder(root);
	printf("\n");
	search(root, 'O');
	search(root, 'Z');
	delete(root, 'Z');
	delete(root, 'A');
	delete(root, 'F');

	inorder(root);
	return 0;
}
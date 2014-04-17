#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct tree
{
	int val;
	struct tree *left;
	struct tree *right;
};

//typedef struct tree * TREE;

int find_min_index(int start, int end, int *arr, int n)
{
	if ( end < start )
		return -1;

	if ( start < 0 )
		return -1;

	if ( end >= n )
		return -1;

	if ( start == end )
		return start;

	int i, small, index;

	small = INT_MAX;
	for(i=start; i<=end; i++)
	{
		if ( arr[i] < small )
		{
			index = i;
			small = arr[i];
		}
	}

	return index;
}

struct tree * creat_cartesian_tree(int start, int end, int *arr, int n)
{
	int index;

	index = find_min_index(start, end, arr, n);
	if ( index == -1 )
		return NULL;

	struct tree *node = (struct tree *)malloc(sizeof(struct tree));
	node->val = arr[index];
	node->left = creat_cartesian_tree(start, index-1, arr, n);
	node->right = creat_cartesian_tree(index+1, end, arr, n);

	return node;
}

void inorder_traversal(struct tree *node)
{
	if ( node == NULL )
		return;

//	printf("%d ", node->val);
	inorder_traversal(node->left);
	printf("%d ", node->val);
	inorder_traversal(node->right);
}

void release_memory(struct tree *node)
{
	if ( node == NULL )
		return;

	release_memory(node->left);
	release_memory(node->right);

	free(node);
}

int main()
{
	int arr[11] = {9, 3, 7, 1 , 8, 12, 10, 20, 15, 18, 5};

	struct tree *root = creat_cartesian_tree(0, 10, arr, 11);

	inorder_traversal(root);

	printf("\n");

	release_memory(root);

	return 0;
}

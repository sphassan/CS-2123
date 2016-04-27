#include <stdlib.h>
#include <stdio.h>

struct node
{
	int key;
	struct node *left, *right;
};
typedef struct node node;

node *insertNode(node *root, int value);
void printTree(node *root, int depth);
void freeTree(node *root);

int main()
{
	node *root = NULL;
	
	printf("Enter the numbers\n");
	
	int val;
	char junk = ' ';
	
	while (junk == ' ')
	{
		scanf("%d", &val);
		root = insertNode(root, val);
		junk = getchar();
	}
		
	printTree(root, 0);
	freeTree(root);
	
	return 0;
}

node *insertNode(node *root, int value)
{
	if (root == NULL)
	{
		root = malloc(sizeof(node));
		root -> key = value;
		root -> left = NULL;
		root -> right = NULL;
	}
	else if (root -> key > value)
		root -> left = insertNode(root -> left, value);
	else
		root -> right = insertNode(root -> right, value);
	
	return(root);
}

void printTree(node *root, int depth)
{
	if (root == NULL)
		return;
	
	printTree(root -> right, depth+1);
	int x;
	for (x = 0; x < depth; x++)
		printf("    ");
	printf("%d\n", root -> key);
	printTree(root -> left, depth+1);
}

void freeTree(node *root)
{
	if (root == NULL)
		return;
	
	freeTree(root -> left);
	freeTree(root -> right);
	free(root);
}

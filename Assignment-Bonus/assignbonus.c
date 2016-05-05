#include <stdlib.h>
#include <stdio.h>

struct node
{
	int key, selected;
	struct node *left, *right;
};
typedef struct node node;

node *readIn(node *root);
node *insertNode(node *root, int value);
void randomTraverse(node *root, node **chosen, int *num);
void printTree(node *root);
void freeTree(node *root);

int main()
{
	node *root = NULL;	
	
	printf("Enter the set of numbers for the tree\n");
	root = readIn(root);
	
	int x;
	node *chosen;
	int num;
	for (x = 0; x < 1000; x++)
	{
		chosen = NULL;
		num = 0;
		randomTraverse(root, &chosen, &num);
		chosen -> selected++;
	}
	
	printf("Probabilities after 1000 random selections are\n");
	printTree(root);
	
	freeTree(root);
	
	return 0;
}

node *readIn(node *root)
{
	char junk = ' ';
	int val = 0;
	while (junk == ' ')
	{
		scanf("%d", &val);
		root = insertNode(root, val);
		junk = getchar();
	}
	
	return(root);
}

node *insertNode(node *root, int value)
{
	if (root == NULL)
	{
		root = malloc(sizeof(node));
		root -> key = value;
		root -> selected = 0;
		root -> left = NULL;
		root -> right = NULL;
	}
	else if (root -> key > value)
		root -> left = insertNode(root -> left, value);
	else
		root -> right = insertNode(root -> right, value);
	
	return(root);
}

void randomTraverse(node *root, node **chosen, int *num)
{
	if (root == NULL)
		return;
	
	if (rand() % (*num + 1)  == *num) //yes, I know this introduces skew and isn't truly random
		*chosen = root;
	
	*num += 1;
	
	randomTraverse(root -> left, chosen, num);
	randomTraverse(root -> right, chosen, num);
}

void printTree(node *root)
{
	if (root == NULL)
		return;
	
	printTree(root -> left);
	printf("p(%d) = %f\n", root -> key, (root -> selected / 1000.0));
	printTree(root -> right);
}

void freeTree(node *root)
{
	if (root == NULL)
		return;
	
	freeTree(root -> left);
	freeTree(root -> right);
	free(root);
}

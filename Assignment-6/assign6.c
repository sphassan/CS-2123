#include <stdlib.h>
#include <stdio.h>

struct node
{
	int key;
	struct node *left, *right;
};
typedef struct node node;

node *readIn(node *root);
node *insertNode(node *root, int value);
int issubset(node *tree1, node *tree2);
int *toHash(node *root, int *map, int *size);
int *resizeHash(node *root, int *map, int *size, int k);
int *compareMap(node *root, int *map, int size, int *issub);
void freeTree(node *root);

int main()
{
	node *first = NULL;
	printf("Enter the set of numbers for the first tree\n");
	first = readIn(first);
	
	node *second = NULL;
	printf("Enter the set of numbers for the second tree\n");
	second = readIn(second);
	
	int issub = issubset(first, second);
	
	freeTree(first);
	freeTree(second);
	
	if (issub == 1)
		printf("First tree is a subset of second tree\n");
	else if (issub == 0)
		printf("First tree is not a subset of second tree\n");
	else
		printf("How.\n");
	
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
		root -> left = NULL;
		root -> right = NULL;
	}
	else if (root -> key > value)
		root -> left = insertNode(root -> left, value);
	else
		root -> right = insertNode(root -> right, value);
	
	return(root);
}

int issubset(node *tree1, node *tree2)
{
	int size = 10;
	int *map = calloc(size, sizeof(int));
	map = toHash(tree2, map, &size);
	
	int issub = 0;
	map = compareMap(tree1, map, size, &issub);
	
	free(map);
	
	return(issub);
}

int *toHash(node *root, int *map, int *size)
{
	if (root == NULL)
		return(map);
	
	int k = 0;
	
	if (*size <= (root -> key % 97) + k)
		map = resizeHash(root, map, size, k);
	
	while (k >= 0 && k < *size)
		if (*size <= (root -> key % 97) + k)
			map = resizeHash(root, map, size, k);
		else if (map[root -> key % 97 + k] == 0)
		{
			map[root -> key % 97 + k] = 1;
			k = -1;
		}
		else
			k += 7;
	
	map = toHash(root -> left, map, size);
	map = toHash(root -> right, map, size);
	
	return(map);
}

int *resizeHash(node *root, int *map, int *size, int k)
{
	int oldsize = *size;
	while (*size <= (root -> key % 97) + k)
	{
		*size *= 2;
		map = realloc(map, sizeof(int) * *size);
	}
	
	int x;
	for (x = oldsize; x < *size; x++)
		map[x] = 0;
	
	return(map);
}

int *compareMap(node *root, int *map, int size, int *issub)
{
	if (root == NULL)
		return(map);
	
	*issub = 0;
		
	int k = 0;
	while (k >= 0 && k < size)
		if (map[root -> key % 97 + k] == 1)
		{
			*issub = 1;
			k = -1;
		}
		else
			k += 7;
	
	map = compareMap(root -> left, map, size, issub);
	map = compareMap(root -> right, map, size, issub);
	return(map);
}

void freeTree(node *root)
{
	if (root == NULL)
		return;
	
	freeTree(root -> left);
	freeTree(root -> right);
	free(root);
}

#include <stdlib.h>
#include <stdio.h>

struct node
{
	int key;
	int count;
	struct node *left, *right;
};
typedef struct node node;

node *insertNode(node *root, int value);
node *deleteNode(node *root, int value); //assumes that there will not be duplicate nodes
node *redisSub(node *root, node *sub);
node *insertExisting(node *root, node *sub);
int countCheck(node *root);
int kthSmallest(node *root, int k, int *neg);
void freeTree(node *root);

int main()
{
	node *root = NULL;
	
	printf("Enter the set of numbers for the tree\n");
	
	char junk = ' ';
	int val = 0;
	while (junk == ' ')
	{
		scanf("%d", &val);
		root = insertNode(root, val);
		junk = getchar();
	}
	
	int k = 0;
	printf("Enter k\n");
	scanf("%d", &k);
	int neg = 0;
	int kth = kthSmallest(root, k, &neg);
	if (kth != -1 || neg == 1)
		printf("Result = %d\n", kth);
	else
		printf("k out of bounds.\n");
	
	freeTree(root);
	
	return 0;
}

node *insertNode(node *root, int value)
{
	if (root == NULL)
	{
		node *newNode = malloc(sizeof(node));
		newNode -> key = value;
		newNode -> count = 1;
		newNode -> left = NULL;
		newNode -> right = NULL;
		root = newNode;
		
		return(root);
	}
	
	if (root -> key > value)
		root -> left = insertNode(root -> left, value);
	else if (root -> key < value)
		root -> right = insertNode(root -> right, value);
	
	root -> count = countCheck(root);
	return(root);
}

node *deleteNode(node *root, int value) //will not be called in main but specifications called for count to be updated on node deletion, so...
{
	if (root == NULL)
		return(root);
	
	if (root -> key == value)
	{
		node *ptr = root;
		if (root -> left != NULL)
		{
			root = root -> left;
			node *lostsubtree = root -> right;
			root -> right = ptr -> right;
			root = redisSub(root, lostsubtree);
		}
		else if (root -> right != NULL)
			root = root -> right;
		else
			root = NULL;
		free(ptr);
		
		return(root);
	}
	
	root -> left = deleteNode(root -> left, value);
	root -> right = deleteNode(root -> right, value);
	
	root -> count = countCheck(root);
	return(root);
}

node *redisSub(node *root, node *sub) //does result in unbalanced tree
{
	if (sub == NULL)
		return;
	
	redisSub(root, sub -> left);
	redisSub(root, sub -> right);
	root = insertExisting(root, sub);
	
	return(root);
}

node *insertExisting(node *root, node *sub) //essentially a rewritten insertNode function
{
	if (root == NULL)
                return(sub);
	
	if (root -> key > sub -> key)
		root -> left = insertExisting(root -> left, sub);
	else if (root -> key < sub -> key)
		root -> right = insertExisting(root -> right, sub);
	
	return(root);
}

int countCheck(node *root)
{
	if (root == NULL)
		return 0;
	
	root -> count = 1;
	
	if (root -> left == NULL)
		return(root -> count);
	
	root -> count = root -> count + countCheck(root -> left);
	if (root -> right != NULL)
		root -> right -> count = countCheck(root -> right);
	if (root -> left -> right != NULL)
		root -> count += root -> left -> right -> count;
		
	return(root -> count);
}

int kthSmallest(node *root, int k, int *neg)
{
	int val;
	
	if (root == NULL)
		return -1;
	
	if (k == root -> count)
	{
		val = root -> key;
		if (root -> key == -1)
			*neg = 1;
	}
	else if (k > root -> count)
	{
		k -= root -> count;
		val = kthSmallest(root -> right, k, neg);
	}
	else
		val = kthSmallest(root -> left, k, neg);
	
	return(val);
}

void freeTree(node *root)
{
	if (root == NULL)
		return;
	
	freeTree(root -> left);
	freeTree(root -> right);
	free(root);
}

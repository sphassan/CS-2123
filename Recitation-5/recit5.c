//Ashley Abernathy, Sean Hassan, Luke Holbrook
//must be compiled with -lm

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct node
{
	int x;
	int y;
	struct node *previous, *next;
};
typedef struct node node;

node *insertNodeCirc(node *prior, int x, int y);
double distance(int x1, int y1, int x2, int y2);
node *nearestNeighbor(node *root, int x, int y);
node *smallestIncrease(node *root, int x, int y);
void writeList(node *root, int n, char *filename);
void freeList(node *root);

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Improper number of arguments. You must include filenames for an input file and both output files.\n");
		exit(1);
	}
	
	FILE *fp = fopen(argv[1], "r");
	
	int n;
	fscanf(fp, "%d", &n);
	
	node *nearestList = NULL;
	node *smallestList = NULL;
	
	int i, x, y;
	for (i = 0; i < n; i++)
	{
		fscanf(fp, "%d", &x);
		fscanf(fp, "%d", &y);
		
		nearestList = nearestNeighbor(nearestList, x, y);
		smallestList = smallestIncrease(smallestList, x, y);
	}
	fclose(fp);
	
	writeList(nearestList, n, argv[2]);
	writeList(smallestList, n, argv[3]);
	
	freeList(nearestList);
	freeList(smallestList);
	
	return 0;
}

node *insertNodeCirc(node *prior, int x, int y)
{
	node *newNode = malloc(sizeof(node));
	newNode -> x = x;
	newNode -> y = y;
	
	if (prior != NULL && prior -> next != NULL)
	{
		node *ptr = prior -> next;
		newNode -> next = ptr;
		ptr -> previous = newNode;
		newNode -> previous = prior;
		prior -> next = newNode;
	}
	else if (prior != NULL && prior -> next == NULL)
	{
		newNode -> next = prior;
		newNode -> previous = prior;
		prior -> next = newNode;
		prior -> previous = newNode;
	}
	else
	{
		newNode -> next = NULL;
		newNode -> previous = NULL;
	}
	
	return(newNode);
}

double distance(int x1, int y1, int x2, int y2)
{
	return(sqrt(pow((double)x1 - (double)x2, 2.0) + pow((double)y1 - (double)y2, 2.0)));
}

node *nearestNeighbor(node *root, int x, int y)
{	
	node *ptr = root;
	node *nearest = root;
	
	if (ptr == NULL)
	{
		root = insertNodeCirc(nearest, x, y);
		return(root);
	}
	if (ptr -> next == NULL)
	{
		ptr -> next = insertNodeCirc(nearest, x, y);
		return(root);
	}
	
	do
	{
		if (distance(nearest -> x, nearest -> y, x, y) > distance(ptr -> x, ptr -> y, x, y))
			nearest = ptr;
		ptr = ptr -> next;
	}
	while (ptr != root);
	
	ptr = insertNodeCirc(nearest, x, y);
	
	return(root);
}

node *smallestIncrease(node *root, int x, int y)
{
	node *ptr = root;
	node *smallest = root;
	
	if (ptr == NULL)
	{
		root = insertNodeCirc(smallest, x, y);
		return(root);
	}
	if (ptr -> next == NULL)
	{
		ptr -> next = insertNodeCirc(smallest, x, y);
		return(root);
	}
	
	do
	{
		if (distance(smallest -> x, smallest -> y, x, y) + distance(x, y, smallest -> next -> x, smallest -> next -> y) > distance(ptr -> x, ptr -> y, x, y) + distance(x, y, ptr -> next -> x, ptr -> next -> y))
			smallest = ptr;
		ptr = ptr -> next;
	}
	while (ptr != root);
	ptr = insertNodeCirc(smallest, x, y);
	
	return(root);
}

void writeList(node *root, int n, char *filename)
{
	FILE *fp = fopen(filename, "w");
	node *ptr = root;
	
	if (ptr == NULL)
	{
		printf("Error, empty list.\n");
		exit(2);
	}
	
	fprintf(fp, "%d\n", n);
	
	do
	{
		fprintf(fp, "%d %d\n", ptr -> x, ptr -> y);
		ptr = ptr -> next;
	}
	while (ptr != root);
	
	fclose(fp);
}

void freeList(node *root)
{
	node *ptr = root -> previous;
	
	ptr -> next = NULL;
	root -> previous = NULL;
	
	while (ptr != NULL)
	{
		ptr = root -> next;
		free(root);
		root = ptr;
	}
}

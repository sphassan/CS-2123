#include <stdlib.h>
#include <stdio.h>

struct node //structs given by assignment
{
	int info;
	struct node *next;
};
typedef struct node node;

struct cnode
{
	int info;
	struct cnode *next;
	struct cnode *previous;
};
typedef struct cnode cnode;

node *CopytoSinglyLinked(cnode *head); //prototypes given by assignment
node *Previous(node *head, node *current);
void PrintReverse(node *head);
node *RemoveDuplicates(node *head);
cnode *inserthead(cnode *head, int a); //given by slides

int main()
{
	printf("Input values in the form of positive integers separated by spaces (\"1 2 3\" is proper input, \"1,2,3\" is not): ");
	
	int holding;
	cnode *head = malloc(sizeof(cnode));
	scanf("%d", &holding);
	head -> info = holding;
	head -> next = NULL;
	head -> previous = NULL;
	
	int input = 1; //repurposed code from recitation 1
	char junk = ' ';
	junk = getchar();
	if (junk != ' ')
		input = 0;
	while (input == 1)
	{
		if (scanf("%d", &holding) > 0)
			head = inserthead(head, holding);
		junk = getchar();
		if (junk != ' ')
			input = 0;
	}
	printf("All numbers inserted at the head.\n\n");
		
	printf("Doubly linked list: ");
	cnode *ptr = head;
	while (ptr -> next != NULL)
	{
		printf("%d, ", ptr -> info);
		ptr = ptr -> next;
	}
	printf("%d\n\n", ptr -> info);
	
	printf("To singly linked list: ");
	node *singleHead = CopytoSinglyLinked(head);
	node *point = singleHead;
	while (point -> next != NULL)
	{
		printf("%d, ", point -> info);
		point = point -> next;
	}
	printf("%d\n\n", point ->  info);
	
	printf("Input a node value to return the previous of (0 is head, this may require some counting!): ");
	int go;
	scanf("%d", &go);
	if (singleHead -> next != NULL && go != 0) //prevents a null pointer from being passed to Previous()
	{
		point = singleHead;
		int x;
		for (x = 0; x < go; x++)
			if (point -> next != NULL)
				point = point -> next;
			else
			{
				printf("Input out of bounds\n\n");
				point = singleHead; //prevents if statement below from being called
				break;
			}
		if (Previous(singleHead, point) != NULL)
			printf("\nNode given: %d, Previous node: %d\n\n", point -> info, Previous(singleHead, point) -> info);
	}
	else
		printf("NULL, no previous for value given\n\n");
	
	printf("Printed in reverse: ");
	PrintReverse(singleHead);
	
	printf("\nList without duplicates: ");
	singleHead = RemoveDuplicates(singleHead);
	point = singleHead;
	while(point -> next  != NULL)
	{
		printf("%d, ", point -> info);
		point = point -> next;
	}
	printf("%d\n", point -> info);
	
	return 0;
}

node *CopytoSinglyLinked(cnode *head)
{
	cnode *ptr = head;
	node *singleHead = malloc(sizeof(node)); //creation of new head
	
	singleHead -> info = ptr -> info;
	
	if (ptr -> next == NULL) //ensures that the while loop is not engaged if the list is only one element long
	{
		singleHead -> next = NULL;
		return(singleHead);
	}
	
	ptr = ptr -> next;
	node *after = malloc(sizeof(node)); //following lines free of us of having to work with singleHead
	singleHead -> next = after; //this allows a while loop to be performed without losing the head node
	node *prior = singleHead;
	while (ptr != NULL)
	{
		after = malloc(sizeof(node));
		after -> info = ptr -> info;
		prior -> next = after;
		prior = prior -> next;
		ptr = ptr -> next;
		after -> next = NULL;
	}
	
	return(singleHead);
}

node *Previous(node *head, node *current)
{
	if (head == current)
		return NULL;
	
	node *ptr = head;
	while (ptr -> next != current)
		ptr = ptr -> next;
	
	return(ptr);
}

void PrintReverse(node *head)
{
	node *ptr = head;
	while (ptr != NULL)
		ptr = ptr -> next;
	
	while (Previous(head, ptr) != NULL)
	{
		ptr = Previous(head, ptr);
		if (ptr == head)
			printf("%d\n", ptr -> info);
		else
			printf("%d, ", ptr -> info);
	}
}

node *RemoveDuplicates(node *head)
{
	node *ptr = head;
	node *transverse = ptr -> next;
	node *temp;
	
	while (ptr != NULL)
	{
		while (transverse != NULL)
			if (ptr -> info == transverse -> info)
			{
				temp = transverse;
				transverse = transverse -> next;
				Previous(head, temp) -> next = transverse;
				free(temp);
			}
			else
				transverse = transverse -> next;
		
		ptr = ptr -> next;
		if (ptr != NULL)
			transverse = ptr -> next;
	}
	
	return(head);
}

cnode *inserthead(cnode *head, int a) //given by slides
{
	cnode *ptr = malloc(sizeof(cnode));
	ptr -> info = a;
	ptr -> next = head;
	head -> previous = ptr;
	ptr -> previous = NULL;
	return(ptr);
}

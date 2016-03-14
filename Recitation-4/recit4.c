/*	Ashley Abernathy Sean Hassan and Luke Holbrook	*
*	Recitation 4 - Doctor Ali Saman Tosun			*
*	Data Structures - Spring 2016					*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct bnode //binary tree node
{
		char *word;
		int freq;
		struct bnode *left;
		struct bnode *right;
};
typedef struct bnode bnode;

int static match;
int static maxSize;

int strCheck(bnode *root, char *input);
char *readFile(char *filename);
bnode *addNode(bnode *root, char *input);
bnode *rotateTree(bnode *root);
bnode *rotateLeft(bnode *root);
bnode *rotateRight(bnode *root);
void printBinaryTree(bnode *root, int freq);
void freeBinaryTree(bnode *root);

int main (int argc, char *argv[])
{
		if (argc == 1)
		{
				printf("You must include a filename in the program call.\n");
				exit(1);
		}
		else if (argc > 2)
		{
				printf("Too many arguments.\n");
				exit(1);
		}

		maxSize = 1;
		char *word = NULL;
		char *str = NULL;
		bnode *root = NULL;
		int x;

		str = readFile(argv[1]);
		if(str != NULL)
		{
				const char* limiter = " ,\n\r\t."; //set these as constant characters. Space is included.
				word = strtok(str,limiter);
				if (word == NULL)
				{
						free(str);
						printf("Empty file.\n");
						exit(2);
				}
				root = addNode(root, word); //pass the word in at the root for binary tree.

				while((word = strtok(NULL,limiter)) != NULL)
						root = addNode(root, word);

				free(str);

				//root = rotateTree(root);
				for (x = 1; x <= maxSize; x++) //this is the worst practice and I am so sorry
						printBinaryTree(root, x);
		}

		freeBinaryTree(root);

		return 0;
}

char *readFile(char *filename)
{
		FILE *file = fopen(filename,"r"); //read in the file
		char *str = NULL; //str will be the character pointer
		int i;

		if(file != NULL) //if we successfully read the file and it is not NULL
		{
				fseek(file, 0 ,SEEK_END);//moves the pointer 2 the end of the file
				long int size = 0;
				if (ftell(file) == -1L)
						return(str);
				size = ftell(file);//ftel determine the size of the file
				rewind(file);//rewind brings the pointer back to the beginning
				str = malloc(sizeof(char) * (size + 1));
				for (i = 0; i < size; i++)
						str[i] = ' ';
				fread(str, size, 1, file);//fread read the the entire file and stores it in a string, the 1 signifies it is reading the entire file as one block

				fclose(file);//close it when done reading
		}

		int siz = 0;
		if (strlen(str) > 0)
				siz = strlen(str);
		for (i = 0; i < siz; i++)
				str[i] = tolower(str[i]);
		return(str);
}

int strCheck(bnode *root, char *input)
{
		int check;
		check = strcmp(root -> word, input);

		if (check == 0)
		{
				root -> freq = root -> freq + 1;
				if (root -> freq > maxSize)
						maxSize = root -> freq;
				match = 1;
		}
		if (root -> left != NULL)
				strCheck(root -> left, input);
		if (root -> right != NULL)
				strCheck(root -> right, input);

		return(match);
}

bnode *addNode(bnode *root, char *input)
{
		if (root == NULL)
		{
				bnode *newNode = malloc(sizeof(bnode));
				newNode -> word = malloc(sizeof(char) * strlen(input) + 1);
				strcpy(newNode -> word, input);
				newNode -> freq = 1;
				newNode -> left = NULL;
				newNode -> right = NULL;

				return(newNode);
		}

		match = 0;
		match = strCheck(root, input);

		if (match == 1)
				return(root);

		bnode *parent = root;
		bnode *ptr = root -> left;
		while (ptr != NULL && ptr -> left != NULL)
		{
				if (ptr -> right == NULL)
						break;
				parent = parent -> left;
				ptr = ptr -> left;
		}
		if (ptr == NULL)
				ptr = parent;

		bnode *newNode = malloc(sizeof(bnode));
		newNode -> word = malloc(sizeof(char) * (strlen(input) + 1));
		strcpy(newNode -> word, input);
		newNode -> freq = 1;
		newNode -> left = NULL;
		newNode -> right = NULL;

		if (ptr -> left == NULL)
				ptr -> left = newNode;
		else if (ptr -> right == NULL)
		{
				ptr = rotateLeft(ptr);
				ptr -> right = ptr -> left;
				ptr -> left = newNode;
				if (parent -> left != NULL)
						parent -> left = ptr;
				if (ptr -> right == root)
						root = ptr;
		}

		root = rotateTree(root);
		return(root);
}

bnode *rotateTree(bnode *root)
{
		if (root != NULL)
		{
				if (root -> left != NULL && root -> freq < root -> left -> freq)
						root = rotateLeft(root);
				if (root -> right != NULL && root -> freq > root -> right -> freq)
						root = rotateRight(root);

				root -> left = rotateTree(root -> left);
				root -> right = rotateTree(root -> right);
		}

		return(root);
}

bnode *rotateLeft(bnode *root)
{
		bnode *temp1 = root;
		bnode *temp2 = root -> right;

		root = root -> left;
		temp1 -> left = root -> left;
		temp1 -> right = root -> right;
		root -> right = temp2;
		root -> left = temp1;

		return(root);
}

bnode *rotateRight(bnode *root)
{
		bnode *temp1 = root;
		bnode *temp2 = root -> left;
		
		root = root -> right;
		temp1 -> left = root -> left;
		temp1 -> right = root -> right;
		root -> left = temp2;
		root -> right = temp1;
		
		return(root);
}

void printBinaryTree(bnode *root, int freq)
{
		if (root != NULL)
		{
				printBinaryTree(root -> left, freq);
				if (root -> freq == freq)
						if (strcmp(root -> word, "i") == 0)
								printf("%d %s\n", root -> freq, "I");
						else
								printf("%d %s\n", root -> freq, root -> word);
				printBinaryTree(root -> right, freq);
		}
}

void freeBinaryTree(bnode *root)
{
		if (root == NULL)
				return;

		freeBinaryTree(root -> left);
		freeBinaryTree(root -> right);
		free(root -> word);
		free(root);
}
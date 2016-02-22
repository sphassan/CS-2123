#include <stdio.h>
#include <stdlib.h>

int QueenPlace(int col, int n);
void put(int row, int col, int n);
int check(int row, int col, int n);
void get(int row, int col, int n);

static int** array;
static int* rowCheck;
static int* descendDiag;
static int* ascendDiag;

int main()
{
	int i, j, n, k;
	printf("Enter n:\n");
	scanf("%d", &n);
	
	array = malloc(sizeof(int*) * n);
	for (i = 0; i < n; i++)
		array[i] = calloc(n, sizeof(int)*n);
	
	rowCheck = calloc(n, sizeof(int*) * n);
	descendDiag = calloc((2*n-1), sizeof(int*) * (2*n - 1));
	ascendDiag = calloc((2*n-1), sizeof(int*) * (2*n - 1));
	
	if (QueenPlace(0, n) == 0)
	{
		printf("Solution:\n");
		
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (j == (n - 1) && array[i][j] == 1)
					printf("X\n");
				else if (j == (n - 1) && array[i][j] == 0)
					printf("_\n");
				else if (array[i][j] == 1)
					printf("X ");
				else
					printf("_ ");
	}
	else
		printf("NO SOLUTION\n");
	
	return 0;
}

void put(int row, int col, int n)
{
	rowCheck[row] = 1;
	descendDiag[row-col+n-1] = 1;
	ascendDiag[row+col] = 1;
}

int check(int row, int col, int n)
{
	if (rowCheck[row] == 1)
		return 1;
	if (descendDiag[row-col+n-1] == 1)
		return 1;
	if (ascendDiag[row+col] == 1)
		return 1;
	
	return 0;
}

void get(int row, int col, int n)
{
	rowCheck[row] = 0;
	descendDiag[row-col+n-1] = 0;
	ascendDiag[row+col] = 0;
}

int QueenPlace(int col, int n)
{	
	if (col == n) //end of board reached
		return 0;
	
	int i;
	for (i = 0; i < n; i++)
		if (check(i, col, n) == 0) //checks hash-like arrays
		{
			put(i, col, n); //fills hash
			array[i][col] = 1; //fills output array
			
			if (QueenPlace(col + 1, n) == 0) //recurs, implicit backtracking
				return 0;
			
			array[i][col] = 0; //frees hash
			get(i, col, n); //frees output array
		}
	
	return 1; //failed to find solution
}

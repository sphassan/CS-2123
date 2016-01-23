#include <stdio.h>
#include <stdlib.h>

int cmp (const void *a, const void *b)
        return (*(int*)a - *(int*)b);

void main()
{
	int size;
	int holding;
	
	printf("Input the number of variables you will have: "); //Must be removed, see next comment
	scanf("%d", &size);
	printf("\n");
	
	int arr[size];

	//Placeholder size check, replace with dynamics using array of char arrays to parse to int array
		
	printf("Input values: "); //Input envisioned as being single line text input from keyboard, numbers separated by spaces, entire line read into single char array
	int a;
	for (int a = 0; a < size; a++) //For loop will be redesigned to parse array of char arrays (made by splitting initial char array on spaces) into an array of integers with each value being one char sub-array
	{
		scanf("%d", &holding);
		arr[a] = holding;
	}
	printf("\n");
	
	int largestBuild;
	int trueSize = size;
	
	qsort(arr, size, sizeof(int), cmp);
	
	if (arr[0] == 1)
		largestBuild = arr[0];
	else
	{
		printf("1 : NA");
		exit();
	}
	
	int b;
	for (b = 1; b < size; b++)
	{
		if (arr[b] > (largestBuild + 1))
		{
			trueSize = b-1;
			break;
		}
		else
			largestBuild += arr[b];
	}
	
	
	int matrix[largestBuild - 1][trueSize];
	int c;
	for (c = trueSize; c >= 0; c--)
		matrix[largestBuild - 1][c] = arr[c];
	
	int workingBuild;
	int d;
	int e;
	int f;
	for (d = largestBuild - 1; d > 0; d--)
	{
		for (e = 0; e < trueSize; e++)
		{
			workingBuild = largestBuild  - matrix[d][e];
			for (f = trueSize; f >= 0; f--)
				if (f != e)
					matrix[workingBuild][f] = arr[f];
				else
					matrix[workingBuild][f] = 0;
		}
	}
	
	int g;
	int h;
	for (g = 0; g < largestBuild; g++)
	{
		printf(g+1, ": ");
		workingBuild = 0;
		for (h = trueSize; h >= 0; h--)
		{
			if (workingBuild == 0 && matrix[g][h] != 0)
				printf(matrix[g][h], " ");
			else if (matrix[g][h] != 0)
				printf("+ ", matrix[g][h], " ");
			workingBuild += matrix[g][h];
		}
		printf("\n");
	}
	printf(largestBuild+1, " : NA");
}

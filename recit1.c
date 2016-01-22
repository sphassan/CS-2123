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
	for (int z = 0; z < size; z++) //For loop will be redesigned to parse array of char arrays (made by splitting initial char array on spaces) into an array of integers with each value being one char sub-array
	{
		scanf("%d", &holding);
		arr[z] = holding;
	}
	printf("\n");
	
	int largestBuild;
	int trueSize = size;
	
	qsort(arr, size, sizeof(int), cmp);
	largestBuild = arr[0];
	
	for (int x = 1; x < size; x++)
	{
		if (arr[x] > (largestBuild + 1))
		{
			trueSize = x-1;
			break;
		}
		else
			largestBuild += arr[x];
	}
	
	
	int matrix[largestBuild - 1][trueSize];
	for (int a = trueSize; a >= 0; a--)
		matrix[largestBuild - 1][a] = arr[a];
	
	int workingBuild;
	
	for (int y = largestBuild - 1; y > 0; y--)
	{
		for (int z = 0; z < trueSize; z++)
		{
			workingBuild = largestBuild  - matrix[y][z];
			for (int b = trueSize; b >= 0; b--)
				if (b != z)
					matrix[workingBuild][b] = arr[b];
				else
					matrix[workingBuild][b] = 0;
		}
	}
	
	for (int c = 0; c < largestBuild; c++)
	{
		printf(c+1, ": ");
		workingBuild = 0;
		for (int d = trueSize; d >= 0; d--)
		{
			if (workingBuild == 0 && matrix[c][d] != 0)
				printf(matrix[c][d], " ");
			else if (matrix[c][d] != 0)
				printf("+ ", matrix[c][d], " ");
			workingBuild += matrix[c][d];
		}
		printf("\n");
	}
	printf(largestBuild+1, " : NA");
}

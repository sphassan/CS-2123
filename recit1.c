#include <stdio.h>
#include <stdlib.h>

int cmp (const void *a, const void *b)
{
         return (*(int*)a - *(int*)b);
}

void main()
{
        int size;
        int holding;

        printf("Input the number of variables you will have: "); //Must be removed, see next comment
        scanf("%d", &size);

        int arr[size];

        //Placeholder size check, replace with dynamics using array of char arrays to parse to int array

        printf("Input values: "); //Input envisioned as being single line text input from keyboard, numbers separated by spaces, entire line read into single char array
        int a;
        for (a = 0; a < size; a++) //For loop will be redesigned to parse array of char arrays (made by splitting initial char array on spaces) into an array of integers with each value being one char sub-array
        {
                scanf("%d", &holding);
                arr[a] = holding;
        }
        printf("\n");

        int largestBuild;
        int trueSize = size - 1; //rename to lastElement

        qsort(arr, size, sizeof(int), cmp);

        if (arr[0] == 1)
                largestBuild = arr[0];
        else
        {
                printf("1 : NA");
                exit(0);
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

        int** matrix = malloc(sizeof(int*) * largestBuild);
        int build;
        for (build = 0; build < largestBuild; build++)
                matrix[build] = malloc(sizeof(int) * trueSize+1);

        int w;
        int x;
        for (w = 0; w < largestBuild; w++)
                for (x = 0; x <= trueSize; x++)
                        matrix[w][x] = 0;

        int c;
        for (c = 0; c <= trueSize; c++)
                matrix[largestBuild - 1][c] = arr[c];

        int workingLocation;
        int d;
        int e;
        int f;
        for (d = largestBuild - 1; d > 1; d--)
        {
                for (e = 0; e <= trueSize; e++)
                {
                        if (d - matrix[d][e] >= 0)
                        {
                                workingLocation = d - matrix[d][e];
                                for (f = 0; f <= trueSize; f++)
                                        if (f != e)
                                                matrix[workingLocation][f] = matrix[d][f];
                                        else
                                                matrix[workingLocation][f] = 0;
                        }
                }
        }

        int workingBuild;
        int g;
        int h;
        for (g = 0; g < largestBuild; g++)
        {
                printf("%d : ", g+1);
                workingBuild = 0;
                for (h = trueSize; h >= 0; h--)
                {
                        if (workingBuild == 0 && matrix[g][h] != 0)
                                printf("%d", matrix[g][h]);
                        else if (matrix[g][h] != 0)
                                printf(" + %d", matrix[g][h]);
                        workingBuild += matrix[g][h];
                }
                printf("\n");
        }
        printf("%d : NA\n", largestBuild+1);

        int z;
        for (z = 0; z < largestBuild; z++)
                free(matrix[z]);
        free(matrix);
}

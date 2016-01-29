#include <stdio.h>
#include <stdlib.h>

int cmp (const void *a, const void *b)
{
         return (*(int*)a - *(int*)b);
}

void main()
{
        int size = 1;
        int holding;
        int* holdingArray = malloc(sizeof(int*) * size);
        int** arrLoc = &holdingArray;

        printf("Input values: ");
        int input = 1;
        int loc = 0;
        char junk = ' ';
        while (input == 1)
        {
                if (scanf("%d", &holding) > 0)
                {
                        holdingArray[loc] = holding;
                        loc++;
                        size++;
                        holdingArray = realloc(*arrLoc, size * sizeof(int));
                }
                junk = getchar();
                if (junk != ' ')
                        input = 0;
        }
        printf("\n");
        size--;

        int arr[size];
        int a;
        for (a = 0; a < size; a++)
                arr[a] = holdingArray[a];
        free(holdingArray);

        int largestBuild;
        int lastElement = size - 1;

        qsort(arr, size, sizeof(int), cmp);

        if (arr[0] == 1)
                largestBuild = arr[0];
        else
        {
                printf("1 : NA\n");
                exit(0);
        }

        int b;
        for (b = 1; b < size; b++)
        {
                if (arr[b] > (largestBuild + 1))
                {
                        lastElement = b-1;
                        break;
                }
                else
                        largestBuild += arr[b];
        }

        int** matrix = malloc(sizeof(int*) * largestBuild);
        int build;
        for (build = 0; build < largestBuild; build++)
                matrix[build] = calloc(1, sizeof(int) * lastElement+1);

        int c;
        for (c = 0; c <= lastElement; c++)
                matrix[largestBuild - 1][c] = arr[c];

        int workingLocation;
        int d;
        int e;
        int f;
        for (d = largestBuild - 1; d > 1; d--)
        {
                for (e = 0; e <= lastElement; e++)
                {
                        if (d - matrix[d][e] >= 0)
                        {
                                workingLocation = d - matrix[d][e];
                                for (f = 0; f <= lastElement; f++)
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
                for (h = lastElement; h >= 0; h--)
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

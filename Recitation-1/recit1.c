#include <stdio.h>
#include <stdlib.h>

int cmp (const void *a, const void *b) //Compare function declared to utilize built-in quicksort
{
         return (*(int*)a - *(int*)b);
}

void main()
{
        int size = 1; //tracks the number of values input by user
        int holding; //technically unnecessary variable that scanf will pass values and will in turn send values to the array below
        int* holdingArray = malloc(sizeof(int*) * size); //dynamically sized array declared on the heap that will hold all integers input by user, plus an extraneous value (typically zero)
        int** arrLoc = &holdingArray; //pointer to holding array necessary variable for reallocating memory, which is essential for its dynamic sizing

        printf("Input values in the form of positive integers separated by spaces (\"1 2 3\" is proper input, \"1,2,3\" is not): ");
        int input = 1; //boolean flag to check to see if while loop will continue iterating
        int loc = 0; //array index to pass input values to proper location in array
        char junk = ' '; //variable used to take in junk input, necessary to dealing with end of line and accomplishing loop exit
        while (input == 1)
        {
                if (scanf("%d", &holding) > 0) //only reads in integer values and passes them to holding, ignores spaces and locks up if given the null value at the end of keyboard string buffer
                {
                        holdingArray[loc] = holding; //technically unneeded step passing the value at holding to the array
                        loc++; //sets loc to next index location
                        size++; //increases the size of the array so that it may be resized
                        holdingArray = realloc(*arrLoc, size * sizeof(int)); //resizes the array to new size, due to the nature of this implementation there will be an extra value (realloc is called after the last value is input)
                }
                junk = getchar(); //reads in both the delimiting spaces and the null value at end of line
                if (junk != ' ') //as junk will only ever equal ' ' or end of line, this will only fire when end of line is reached
                        input = 0; //exits the loop
        }
        printf("\n");
        size--; //removes the extra size caused by improper implementation stated by

        int arr[size]; //new array that is properly sized to the number of user input values
        int a;
        for (a = 0; a < size; a++)
                arr[a] = holdingArray[a]; //populates the new array only with those values input by the user and not the junk value caused by improper implementation
        free(holdingArray); //frees memory in the heap

        int largestBuild; //the largest possible number to build, the sum of all numbers that follow the series rule
        int lastElement = size - 1; //index value of the last element in the array that follows the series rule, initially set with the assumption that all elements follow the rule
        qsort(arr, size, sizeof(int), cmp); //built in quick sort takes user input data and puts it in ascending order

        if (arr[0] == 1) //checks the trivial case of construction, the series must start with 1
                largestBuild = arr[0]; //initial set for largestBuild presumes that all numbers past the first element breaks the rule
        else //if the series does not start with 1, exit immediately and output that no values may be built
        {
                printf("1 : NA\n");
                exit(0);
        }

        int b;
        for (b = 1; b < size; b++)
        {
                if (arr[b] > (largestBuild + 1)) //checks to see if the element being checked breaks the series rule
                {
                        lastElement = b-1; //if it does, the last element is known to be the element prior to the element that violated the series rule and all latter values are truncated
                        break;
                }
                else
                        largestBuild += arr[b]; //if it does not, then the largest buildable number includes the current element
        }

        int** matrix = malloc(sizeof(int*) * largestBuild); //declaration of a two dimensional array building a table where the outer indices are the buildable numbers and the stored values are the numbers that may be added to construct their outer index
        int build;
        for (build = 0; build < largestBuild; build++)
                matrix[build] = calloc(1, sizeof(int) * lastElement+1); //allocates memory to all inner elements of the matrix and initializes their starting values to 0

        int c;
        for (c = 0; c <= lastElement; c++)
                matrix[largestBuild - 1][c] = arr[c]; //fills in the values for the last value in the array, the largest buildable number and all numbers in the truncated array

        int workingLocation; //the current index in the outer array, the number we are currently constructing minus one
        int d;
        int e;
        int f;
        for (d = largestBuild - 1; d > 1; d--) //largestBuild - 1 required to achieve array index, we do not need to perform the algorithm upon index 0 (value 1) as no new information will be gained
        {
                for (e = 0; e <= lastElement; e++) //inner loop traverses the table values for the number being built
                {
                        if (d - matrix[d][e] >= 0) //checks to ensure we do not waste iterations on things we already know
                        {
                                workingLocation = d - matrix[d][e]; //sets the location of the current number being built to the outer array value minus value of what is at the table location of a number already constructed
                                for (f = 0; f <= lastElement; f++) //populates the table at the working location
                                        if (f != e) //ensures we do not add to the table a number being removed
                                                matrix[workingLocation][f] = matrix[d][f]; //populates the table for the current number being built with numbers from the prior table
                                        else
                                                matrix[workingLocation][f] = 0; //ensures that the number being removed from the prior constructed number is set as 0 in the new table
                        } //the above is vital as the program is inefficient and will build numbers multiple times, without the clearing effect of the else construction would be improper
                } //as an ancillary benefit, numbers given within the data set will always be defined as themselves due to the inefficiency
        }

        int workingBuild; //current number being output
        int g;
        int h;
        for (g = 0; g < largestBuild; g++) //iterates from 0 to 1 less than largest number possible to build to provide proper indexing to the matrix
        {
                printf("%d : ", g+1); //index number given a +1 to give proper output (the index of 1 is 0)
                workingBuild = 0; //resets the current number being built before the nested for loop that adds to it
                for (h = lastElement; h >= 0; h--) //traverses backwards through tables to give output in descending order (tables are sorted ascendingly defacto due to the original qsort)
                {
                        if (workingBuild == 0 && matrix[g][h] != 0) //this check ensures that the first number output will be output by itself and will not output a zero
                                printf("%d", matrix[g][h]);
                        else if (matrix[g][h] != 0) //ensures a zero is not output
                                printf(" + %d", matrix[g][h]); //all numbers output after the first will be preceded by a + to meet formatting guidelines
                        workingBuild += matrix[g][h]; //consistent adding to workingBuild required instead of a flag set after first run as tables will contain multiple zeroes
                }
                printf("\n");
        }
        printf("%d : NA\n", largestBuild+1);

        int z;
        for (z = 0; z < largestBuild; z++) //memory of inner arrays must be cleared first, otherwise pointer to their location will be lost
                free(matrix[z]);
        free(matrix); //outer array memory in heap cleared
}

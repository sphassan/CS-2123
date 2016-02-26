#include <stdlib.h>
#include <stdio.h>

int main()
{
	FILE *fp;
	fp = fopen("a.txt", "r");
	
	int rows;
	int cols;
	fscanf(fp, "%d %d", &rows, &cols);
	
	int** matrix = malloc(sizeof(int*) * rows);
	int x;
	for (x = 0; x < rows; x++)
		matrix[x] = calloc(1, sizeof(int) * cols);
	
	int y;
	int holding;
	int runningRow;
	for (x = 0; x < rows; x++)
	{
		runningRow = 0;
		for (y = 0; y < cols; y++)
		{
			fscanf(fp, "%d", &matrix[x][y]);
			matrix[x][y] += runningRow;
			runningRow = matrix[x][y];
			if (x != 0)
				matrix[x][y] += matrix[x-1][y];
		}
	}
	fclose(fp);
	
	char go;
	char *buildTopLeft;
	int topLeftY;
	int topLeftX;
	int botRightY;
	int botRightX;
	int sum;
	
	while (go != '-')
	{
		sum = 0; //resets values to ensure smooth operation over multiple loops
		x = 0;
		go = '+';
		buildTopLeft = malloc(sizeof(char));
		
		printf("Enter top left and bottom right coordinates of rectangle (-1 to quit)\n"); //as scanf("%d") does not recognize -1 as negative one (it reads '-', sees that it is not an integer, and does nothing), a creative solution is required
		go = getchar();
		if (go == '-')
			break;
		while (go != ' ') //permits topLeftX to be larger than 9, stops at space to allow new digits to be read in
		{
			x++;
			if (x != 1) //ensures realloc is not called for the first iteration, and therefore at all when topLeftX is less than 10
				buildTopLeft = realloc(buildTopLeft, sizeof(char) * x); //iterative realloc used instead of doubling as there will likely be small index values, and permits double use of x
			buildTopLeft[x-1] = go; //concantenates the digits of the first number input together
			go = getchar();
		}
		topLeftY = atoi(buildTopLeft);
		free(buildTopLeft);
		
		scanf(" %d %d %d", &topLeftX, &botRightY, &botRightX);
		getchar(); //catches EOL to allow the getchar at the top of the loop to work properly
		
		if (topLeftY >= rows || botRightY >= rows || topLeftX >= cols || botRightX >= cols || topLeftY > botRightY || topLeftX > botRightX || topLeftX < 0 || botRightY < 0 || botRightX < 0)
		{
			printf("Input out of bounds, please try again.\n");
			continue;
		}
		printf("%d", topLeftX);
		
		if(topLeftY != 0 && topLeftX != 0)
			sum = matrix[botRightY][botRightX] - matrix[botRightY][topLeftX-1] - matrix[topLeftY-1][botRightX] + matrix[topLeftY-1][topLeftX-1];
		else if (topLeftX != 0)
			sum = matrix[botRightY][botRightX] - matrix[botRightY][topLeftX-1];
		else if (topLeftY != 0)
			sum = matrix[botRightY][botRightX] - matrix[topLeftY-1][botRightX];
		else
			sum = matrix[botRightY][botRightX];
		
		printf("Sum = %d\n", sum);
	}
	
	free(buildTopLeft);
	for (x = 0; x < rows; x++)
		free(matrix[x]);
	free(matrix);
	
	return 0;
}

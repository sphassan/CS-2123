#include <stdio.h>

void main()
{
	FILE *fp; //creates file pointer
	fp = fopen("assign1.pgm", "w"); //opens or creates file with name of assign1.pgm, sets that it will be written to and passes it to the pointer
	fprintf(fp, "P2\n800 800\n255\n"); //sets file header
	
	int a;
	int b;
	int c;
	int d;
	for (a = 0; a < 8; a++) //traverses one column of the board block by block
		for (b = 0; b < 100; b++) //traverses individual pixels of a column's block
		{
			for (c = 0; c < 8; c++) //traverses one row of the board block by block
				for (d = 0; d < 100; d++) //traverses individual pixels of a row's block
					if ((a + c) % 2 == 0 && c == 7 && d == 99) //alternates blocks by row and column and ensures there's no trailing space at end of row
						fprintf(fp, "0");
					else if ((a + c) % 2 == 0) //alternates blcoks by row and column
						fprintf(fp, "0 ");
					else if (c == 7 && d == 99) //ensures there's no trailing space
						fprintf(fp, "255");
					else
						fprintf(fp, "255 ");
			fprintf(fp, "\n"); //ends a row
		}
}

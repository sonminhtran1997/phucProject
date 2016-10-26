//----------------------------------------------------------------------------
// File:			argcv.c 
//
// Functions:		int main(int argc, char *argv[]) 
//
//----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable: 4996)

//----------------------------------------------------------------------------
//	Function:		int main(int argc, char *argv[]) 
//
//  Title:			Standard Deviation
//
//	Description:	The program will takes in a collection of existed data and
//					open it up for the program to read in the list of integer 
//					data. Once it read all the data, the program will 
//					calculate the total, range of values, standard deviation
//					mean, variance, summation of all data as well as keeping
//					track of the smalllest and the highest piece of data
//					within the data collection
// 
//  Programmer:		Phuc Hong Le
// 
//  Date:			10/11/2016
//
//  Version:		1.0
//
//  Environment:	Intel Xeon PC 
//					Software:	OS:	MS Windows 7 Professional 64-bit
//					Compiles:   Microsoft Visual Studio.Net 2015 											
//                  Hardware:	16GB RAM
//								Intel(R) Core(TM) i7-4770K 
//
//	Input:			A specific file including a collection of data
//					
//	Output:			All calculated value for the program:
//					Total number of elements
//					Summation of values
//					Range of values
//					Mean value
//					Variance
//					Standard deviation
//
//	Parameters:		int argc 
//					char *argv[]
//
//  Returns:		EXIT_SUCCESS for successful completion 
// 
// 
//	Called By:		None
// 
//	Calls:			None
//
//	History Log:	10/11/2016 Declare the heading for the program. 
//							   (v.1)
//					10/13/2016 Making initials, constants and other values. 
//							   (v.2)
//					10/15/2016 Checking and fixing output within the program.
//							   (v.3)
//					10/20/2016 Calculate the number for the program to output.
//							   (v.4)
//
//----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	FILE * inFileHandle = NULL;
	FILE * outFileHandle = NULL;
	char filename[FILENAME_MAX] = "";
	int returnValue = EXIT_SUCCESS;
	int i = 0;
	int j = 0;
	int dat = 0;
	int datum = 0;
	int largNum = 0;
	int smallNum = 0;
	float numOfElement = 0;
	float sum = 0;
	float sumOfSquaresData = 0.0;
	float mean = 0.0;
	float var = 0.0;
	float std = 0.0;

	//Initiating the program
	if (argc > 1)
	{
		strncpy(filename, argv[1], FILENAME_MAX);
	}
	else
	{
		puts("Standard Deviation Program written by Phuc Hong Le");
		puts("-------------------------------------------------------------");
		puts("Please enter the name of the file to read (source):");
		fgets(filename, FILENAME_MAX, stdin);
		if (filename[strlen(filename) - 1] == '\n')
		{
			filename[strlen(filename) - 1] = '\0';
		}
		else
		{
			while (getchar() != '\n');
		}
	}

	//Get the input file and check if it has any data or not.
	inFileHandle = fopen(filename, "r");
	printf("Input data file: %s\n", filename);
	printf("\n");
	if (inFileHandle == NULL)
	{
		printf("Could not open the file %s for reading the input.\n"
			"- Press any key to terminate the program -", filename);
		getch();
		returnValue = EXIT_FAILURE;
	}
	else
	{
		if (argc > 2)
		{
			strncpy(filename, argv[2], FILENAME_MAX);
		}
		else
		{
			puts("Enter the name of the file to write (output):");
			gets(filename);
		}
		outFileHandle = fopen(filename, "w");
		printf("Output data file: %s\n", filename);
		printf("\n");
		if (outFileHandle == NULL)
		{
			fclose(inFileHandle);
			printf("Could not open the file %s for writing the output.\n"
				"- Press any key to terminate the program -", filename);
			getch();
			returnValue = EXIT_FAILURE;
		}
		else
		{

			//calculating the variables 
			while (fscanf(inFileHandle, "%d", &dat) == 1)
			{
				for (i = 0; i < dat; i++)
				{
					fscanf(inFileHandle, "%d", &datum);
					numOfElement++;
					if (numOfElement == 1) {
						largNum = datum;
						smallNum = datum;
					}
					else if (datum >= largNum)
					{
						largNum = datum;
					}
					else if (datum <= smallNum)
					{
						smallNum = datum;
					}
					sum += datum;
					sumOfSquaresData += (datum * datum);
				}

				//Calculate the Mean, Variance and the Standard Deviation
				mean = sum / numOfElement;
				var = (sumOfSquaresData - ((sum * sum) / numOfElement)) / (numOfElement - 1);
				std = sqrt(var);

				//Making the header for the table
				if (j < 1)
				{
					for (i = 0; i < 78; i++, fprintf(outFileHandle, "%c", '_'));
					fprintf(outFileHandle, "\n| # of data |  sum  |  range  |   mean"
						"  |  variance  |  standard deviation  |\n");
					for (i = 0; i < 78; i++, fprintf(outFileHandle, "%c", '_'));
				}
				++j;

				//Print out the output
				fprintf(outFileHandle, "\n|%10g |  %4g | %2d to %d | %7.3f"
					" |%11.3f |%21.3f |\n", numOfElement, sum, smallNum, largNum,
					mean, var, std);
				for (i = 0; i < 78; i++, fprintf(outFileHandle, "%c", '_'));
			}

			//close input and output files and print out a goodbye message 
			fclose(inFileHandle);
			fclose(outFileHandle);
			puts("\nThank you for using Standard Deviation Program.\t"
				"\nPress any key to terminate the program");
			getch();
		}
	}
	return returnValue;
}

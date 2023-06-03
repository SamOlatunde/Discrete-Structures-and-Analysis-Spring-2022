//-----------------------------------------------------------------------
//
// Name: Samuel Olatunde 
//
// Course: CMPS 2433-201, Spring 2022, Dr.Stringfellow 
//
// Purpose: This program uses a recursive algorithm ("boundaryFill") and
// dynamic 2D arrays to fill up an area inside a polygonal boundary. The 
// polygonal boundary is housed in a m x n matrix (which is a 2D array). 
// -1 represents the polygonal boundary and 0 represents the area to be
// filled up.The program is made to start at some coordinate in the 
// matrix, fill it with an integer "levels," then recursively visit the
// neighboring locations in the order (right, below, left, above), 
// filling them with thier corresponding value for "levels." Note that 
// the value of "levels" is constantly changing by levels of recurssion.
// All input is taken from a file and output is sent to a file if input
// is correct or the screen if input is incorrect. The first input is 
// the number of matrices to be processed per file, which has to be 
// between 1 and 20, followed by the number of rows and columns
// per matrix, the starting coordinates, then the raw matrix itself. 
//
//-----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Precondition: fstream objects must be declared in the calling function 
// Postcondition: specified files are opened 
void openFiles(ifstream& infile, ofstream& outfile);

// Precondition: fstream objects must be declared in the calling function 
// Postcondtion: message is sent to the output file
void programTag(ofstream& outfile);

// Precondition: "matrix" must not be null
// Postcondition: inner arrays of "matrix" are modified 
void boundaryFill(int x, int y, int row, int col, int& level,
	int** matrix);

// Precondition: fstream objects must be declared in the calling function 
// Postcondition: value of "noOfMatrices" in the calling function is 
// changed because it's a reference parameter 
bool readandValidateNoOfMatrices(int& noOfMatrices, ifstream& infile);

// Precondition:fstream objects must be declared in the calling function 
// Postcondition: values of "noOfRows," "noOfCols," "startingRow," 
// "startingCol," in the calling function are changed because they are 
// reference parameters 
int** readAndConfigure(int& noOfRows, int& noOfCols,
	int& startingRow, int& startingCol, ifstream& infile);

// Precondition: fstream objects must be declared in the calling function
// "matrix" must not be null
// Postcondition: data is sent to the output file 
void printResult(int i, int noOfRows, int noOfCols, int** matrix,
	ofstream& outfile);

// Precondition: "matrix" must not be null
// Postcondition: memory is freed up 
void deallocateMemory(int noOfRow, int** matrix);

int main()
{
	// creates fstream objects 
	ifstream infile;
	ofstream outfile;

	// variable declartions
	int startingRow, startingCol,
		noOfRows, noOfCols, levels, noOfMatrices;
	int** matrix = NULL;

	// initializations to prevent warning 
	startingRow = startingCol = noOfRows = noOfCols = noOfMatrices = 0;

	//opens files 
	openFiles(infile, outfile);

	//print program label 
	programTag(outfile);

	// if the number of matrices the user wants to process 
	// is outside the specified range (1-20), inform the user 
	// of this error, and terminate the program
	if (!readandValidateNoOfMatrices(noOfMatrices, infile))
	{
		cout << "This program can only process between 1 and 20 "
			<< "matrices at a time, correct your input file and run "
			<< "the program again. " << endl;
		return 0;
	}

	// reads in, processes, and prints all the matrices contained 
	// in an input file
	for (int i = 1; i <= noOfMatrices; i++)
	{
		levels = 0;

		// read in the number of rows and columns and starting point 
		matrix = readAndConfigure(noOfRows, noOfCols, startingRow,
			startingCol, infile);

		// process the matrix 
		boundaryFill(startingRow, startingCol, noOfRows, noOfCols,
			levels, matrix);

		// print the processed matrix 
		printResult(i, noOfRows, noOfCols, matrix, outfile);

		// free memory 
		deallocateMemory(noOfRows, matrix);
	}

	// closes infile and outfile      
	infile.close();
	outfile.close();

	return 0;
}

// This function opens the files specified by the user 
// credit: "shorttopics" by Dr.Stringfellow
void openFiles(ifstream& infile, ofstream& outfile)
{
	// strings to hold the file names
	string inFileName;
	string outFileName;

	// prompts the user for a file name, reads input from the user,
	// and opens the input file with the specified name
	cout << "Enter the first file name: ";
	cin >> inFileName;
	infile.open(inFileName);

	// prompts the user for a file name, reads input from the user,
	// and opens the output file with the specified name
	cout << "Enter the second file name: ";
	cin >> outFileName;
	outfile.open(outFileName);
}

// This function sends an introductory message to the output file
void programTag(ofstream& outfile)
{
	outfile << "Samuel Olatunde " << endl;
	outfile << "Program 3 Boundary Fill" << endl;
}

// This is a recursive function that fills up the cells of a
// matrix starting at a valid location in the matrix assigning
// it an integer value, then visting the locations neighbors
// in the order right, below, left, above, and assigning them
// thier respective integer values if and only if they are 
// valid locations. The integer values are determined by the 
// levels of recursion 
void boundaryFill(int x, int y, int row, int col, int& level,
	int** matrix)
{
	// flags used for base cases 
	bool outsideBoundary, onBoundary, alreadyVisited;

	outsideBoundary = onBoundary = alreadyVisited = true;

	// checks if the starting location is not in the matrix
	outsideBoundary = (x  < 0 || x > row - 1) ||
		(y < 0 || y > col - 1);

	// if the starting point is outside the boundary, attempting
	// to access the starting point's location in the matrix would
	// lead to a read access violation, because we would be trying 
	// to access and read unallocated memory, this conditional
	// prevents that from happening 
	if (!outsideBoundary)
	{
		// checks if the starting location is on a boundary
		onBoundary = (matrix[x][y] == -1);

		// checks if we have already visited the starting location
		alreadyVisited = (matrix[x][y] != 0);
	}

	// "understood" base case 
	if (!outsideBoundary && !onBoundary && !alreadyVisited)
	{
		// increase the level by 1
		level++;

		// visit the location and assign it its level
		matrix[x][y] = level;

		// go to the location’s neighbor to the right, passing it new 
		// level
		boundaryFill(x, y + 1, row, col, level, matrix);

		// go to the location’s neighbor below, passing it new level
		boundaryFill(x + 1, y, row, col, level, matrix);

		// go to the location’s neighbor to the left, passing it new 
		// level
		boundaryFill(x, y - 1, row, col, level, matrix);

		// go to the location’s neighbor above, passing it new level
		boundaryFill(x - 1, y, row, col, level, matrix);

		level--;
	}
}

// This function reads in the number of matrix to be processed per
// input file and checks if the value is between 1 and 20
bool readandValidateNoOfMatrices(int& noOfMatrices, ifstream& infile)
{
	infile >> noOfMatrices;
	return (noOfMatrices >= 1 && noOfMatrices <= 20);
}

// This function reads in all information needed to process the 
// matrix, including the number of rows and columns, the starting
// coordinate, and the unprocessed matrix itself. The function 
// returns the memory address of the 2D array that holds the matrix.
int** readAndConfigure(int& noOfRows, int& noOfCols, int& startingRow,
	int& startingCol, ifstream& infile)
{
	int rawValues = 0;
	int** matrix = NULL;

	// read in the number of rows and columns a matrix has
	infile >> noOfRows >> noOfCols;

	// read in the starting cordinate point that would be used in the 
	// boundaryfill algorithm 
	infile >> startingRow >> startingCol;

	// creates a dynamic array of pointers 
	matrix = new int* [noOfRows];

	// traverse through the dynamic array of pointers and make an array
	// of integers for each of element of the array of pointers 
	for (int i = 0; i < noOfRows; i++)
	{
		matrix[i] = new int[noOfCols];
	}

	// traverse through the array and sequentially place each 
	// element in it's right place 
	for (int row = 0; row < noOfRows; row++)
	{
		for (int col = 0; col < noOfCols; col++)
		{
			infile >> rawValues;
			matrix[row][col] = rawValues;
		}
	}

	return matrix;
}

// This function sends the processesed matrix to the output file 
void printResult(int i, int noOfRows, int noOfCols, int** matrix,
	ofstream& outfile)
{
	outfile << endl << "Filled Matrix " << i << endl;

	for (int row = 0; row < noOfRows; row++)
	{
		for (int col = 0; col < noOfCols; col++)
		{
			//ensures pretty output
			outfile << setw(4);

			outfile << matrix[row][col];
		}

		outfile << endl;
	}
}

// This function frees all dynamical allocated  memory
void deallocateMemory(int noOfRow, int** matrix)
{
	for (int i = 0; i < noOfRow; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;

	matrix = NULL;
}
//-----------------------------------------------------------------------
//
// Name: Samuel Olatunde 
//
// Course: CMPS 2433-201, Spring 2022, Dr.Stringfellow 
//
// Purpose: This program uses the iterative factorial function to 
// calculate the number of r-permutations, or r-combinations of a 
// set with n elements where n and r are nonnegative integers such that
// r is less than or equal to n. For input, the program reads from a 
// file, a character, 'operation,' (which is expected to be 'P' or 'C'), 
// the integer value for n, followed by the integer value for r.  Output 
// is sent to the file 
//
// Note: I only have one factorial function because I am using a loop to 
// cancel out (n-r)! in the permutation function
//
//-----------------------------------------------------------------------

#include <iostream>
#include<fstream>
#include <iomanip>
#include<string>
#include<stdlib.h>

using namespace std; 

// Precondition: fstream objects must be declared in the calling function 
// Postcondition: specified files are opened 
void openFiles(ifstream& infile, ofstream& outfile);

// Precondition: fstream objects must be declared in the calling function 
// Postcondtion: message is sent to the output file
void programTag(ofstream& outfile);

// Precondition: fstream objects must be declared in the calling function
// Postcondition: value of arguments in the calling function is changed,
// because they were passed by reference 
void read(char & operation, int & n, int & r, 
	ifstream& infile);

// Precondition: "number" must be greater than or equal to zero
// Postcondition: a long long int is returned 
long long int iterativeFactorial(int integer);

// Precondition:"n" and "r" must be nonnegative integers with r 
// less than or equal to n
// Postcondition: a long long int is returned 
long long int permutation(int n, int r);

// Precondition: "n" and "r" must be nonnegative integers with r 
// less than or equal to n
// Postcondition: a long long int is returned
long long int combination(int n, int r);

// Precondition: fstream objects must be declared in the calling function
// Postcondition: Data is sent to the output file 
void print(char operation, int n, int r, long long int result,
	ofstream& outfile);

int main()
{
	// creates fstream objects 
	ifstream infile;
	ofstream outfile;

	// variable declaration 
	char operation;
	int n = 0, r = 0;
	long long int rPermutations = 0, rCombinations = 0;
	
	// opens files 
	openFiles(infile, outfile);
	
	// print program label
	programTag(outfile);
	
	// while we have not reached the end of the file, read in 
	// the variables and perform the input specified operations 
	// on them 
	while (!infile.eof())
	{
		// read input from the file 
		read(operation, n, r, infile);

		// if the value of operation is 'P' then calculate the number 
		// of r-permutations of the set with n elements, calculate 
		// the number r-combinations of the set with n elements if 
		// otherwise 
		if (operation == 'P')
		{
			rPermutations = permutation(n, r);
			print(operation, n, r, rPermutations, outfile);
		}
		else
		{
			rCombinations = combination(n, r);
			print(operation, n, r, rCombinations, outfile);
		}
	}

	// closes infil and outfile
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
	outfile << "CMPS 2433 Program 4" << endl << endl;
}

// This function reads in the operation to be performed ('P' or 'C'),
// and the variables n and r needed to perform anyone of these 
// operations 
void read(char& operation, int& n, int& r, 
	ifstream& infile)
{ 
	infile >> operation >> n >> r;
}

// This function iteratively calculates the factorial of any 
// nonnegative integer 
long long int iterativeFactorial(int integer)
{
	long long int factorial = integer--;

	// if the integer passed in is zero return 1 because 0! = 1
	if (integer == 0)
	{
		return 1;
	}

	// while integer r is greater than or equal to one,
	// multiply the integer by the preceding integer
	while (integer >= 1)
	{
		factorial *= integer;
		integer--;
	}

	return factorial;
}

// This function calculates the number of r ordered elements we  
// can select from a set with n distinct elements. 
long long int permutation(int n, int r)
{
	long long int result = 1;

	// if n is less than r terminate the program because it doesnt 
	// make any sense to calculate the r number of permutations
	// of a set that is smaller than r
	if (n < r)
	{
		cout << "Math ERROR: n cannot be less than r. " << endl;
		exit(EXIT_FAILURE);
	}

	// if r is zero, return 1 because there is extactly one way to 
	// pick nothing from something which is nothing 
	if (r == 0)
	{
		return 1;
	}

	// P(n,r) = n!/ (n-r)!, because n is always greater than or 
	// equal to r, we can cancel out (n-r)! in solving permutations 
	// in order to reduce the number of operations we perform
	for (int i = n; i >= (n - r + 1); i--)
	{
		result *= i;
	}

	return result;
}

// This fucntion calculates the number of unordered selection of r 
// elements we can make from a set with n elements 
long long int combination(int n, int r)
{
	long long int result = 1;

	// if n is less than r terminate the program because it doesnt 
	// make any sense to calculate the r number of permutations
	// of a set that is smaller than r
	if (n < r )
	{
		cout << "Math ERROR: n cannot be less than r. " << endl;
		exit(EXIT_FAILURE);
	}

	// if r is equal to n or zero, return 1 because there is extactly 
	// one way to pick nothing from something which is nothing and 
	// there is exactly 1 set of n distinct, unordered elements we
	// can pick from a set with n elements
	if (r == n || r == 0)
	{
		return 1;
	}

	// this loop cancels out (n-r)! 
	for (int i = n; i >= (n - r + 1); i--)
	{
		result *= i;
	}
	 
	// divide the result of r! because C(n,r) = n!/ ((n-r)! * r!)
	result /= iterativeFactorial(r);

	return result;
}

// This sends the output when a permuatation or combination 
// operation is perfromed on two numbers 
void print(char operation, int n, int r, long long int result,
	ofstream& outfile)
{
	outfile << operation << "\t(" << left << setw(2)<< n <<
		", " << right << setw(2) << r << ") =\t" << right << 
		setw(22) << result << endl;
}
//-----------------------------------------------------------------------
//
// Name: Samuel Olatunde 
//
// Course: CMPS 2433-201, Spring 2022, Dr.Stringfellow 
//
// Purpose: Primarily, this program classifies a set of ordered pairs 
// (a relation) into two types: functions, and non-functions. If a 
// relation is a function, the program goes deeper to determine the type
// of function - general, onto, one-to-one, or bijection - it is. The 
// program takes input from a file starting from the number of relations,
// to number of ordered pairs per relations, to the odered pairs in each
// relation and sends output (the relation and it's classification) to a 
// file. 
// 
// Note: "first" denotes the preImage of a relation, and "second" 
// denotes the image of a relation.
// 
//-----------------------------------------------------------------------

#include<iostream>
#include <fstream>

using namespace std;

// global constant 
const int SIX = 6;

// Precondition: fstream objects must be declared in the calling function 
// Postcondition: specified files are opened 
void openFiles(ifstream& infile, ofstream& outfile);

// Precondition: fstream objects must be declared in the calling function 
// Postcondition: the value of "first" and "second" changes everytime 
// this function is called because they are reference parameters
void readPrint(int& first, int& second, int i, int j,
	int noOfOrderedpairs, ifstream& infile, ofstream& outfile);

// Precondition: fstream objects must be declared in the calling function 
// Postcondtion: message is sent to the output file
void programTag(ofstream& outfile);

// Precondition: none
// Postcondition: Values in the array are changed 
void initializeArray(int arr1[], int arr2[]);

// Precondition: "first" and "second" must be within 1-5
// Postcondition: true or false is returned 
bool isDuplicate(int first, int second, int preImage [], int Image[]);

// Precondition: "first" and "second" must be within 1-5
// Postcondition: true or false is returned 
bool isFunction(int first, int second, int preImage[], int Image[]);

// Precondition: "first" and "second" must be within 1-5
// Postcondition: true or false is returned 
bool isOneToOne(int first, int second, int preImage[], int Image[]);

// Precondition: None 
// Postcondition: true or false is returned 
bool isOnto(int Image[]);

// Precondition: fstream objects must be declared in the calling function 
// Postcondition: data is sent to the output file 
void printClassification(bool isFunction, bool isOneToOne, bool isOnto,
	ofstream& outfile);

int main()
{
	// creates fstream objects
	ifstream infile;
	ofstream outfile;

	// variable declarations 
	int noOfRelations, noOfOrderedPairs, first, second;
	bool Function, OneToOne, Onto;

	// flag initialization
	Function = true, OneToOne = true, Onto = true;

	// array declaration
	int preImage[SIX], Image[SIX];

	// opens files
	openFiles(infile, outfile);

	//sends program label to the output file
	programTag(outfile);

	// reads in the number of relations 
	infile >> noOfRelations;

	for (int i = 1; i <= noOfRelations; i++)
	{
		// reinitializes the values of the array to -1
		initializeArray(preImage, Image);

		// reads in the number of ordered pairs per relation
		infile >> noOfOrderedPairs;

		// resets flags for a new relation
		Function = Onto = OneToOne = true;

		for (int j = 0; j < noOfOrderedPairs; j++)
		{
			// reads and prints and ordered pairs
			readPrint(first, second, i, j, noOfOrderedPairs, infile,
				outfile);

			// if the relation is a function, keep on checking that it 
			// is a function; stop if otherwise 
			if (Function)
			{
				Function = isFunction(first, second, preImage, Image);
			}

			// if the relation is a function and is one-to-one, keep on
			// checking that it is one-to-one; stop if otherwise
			if (Function && OneToOne)
			{
				OneToOne = isOneToOne(first, second, preImage, Image);
			}

			// assignment statments to accurately place each image and
			// preimage in the right spot 
			preImage[second] = first;
			Image[first] = second;
		}

		// if the relation is a function, check if it is onto
		if (Function)
		{
			Onto = isOnto(Image);
		}
		
		outfile << endl;

		// send the classification of the relation to the output file 
		printClassification(Function, OneToOne, Onto, outfile);
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

// This function reads in a relations preimage and image from an 
// input file and sends the relation in ordered-pair form to the
// output file 
void readPrint(int & first, int & second, int i, int j,
	int noOfOrderedpairs, ifstream& infile, ofstream& outfile)
{
	// read first and second 
	infile >> first >> second;

	// this conditional prevents the output statment from being 
	// printed multiple times 
	if (j == 0)
	{
		outfile << "Relation " << i << ": ";
	}

	// print the value of first and second 
	outfile << "(" << first << "," << second << ")";

	// this conditional prevents an extra "," after the last 
	// ordered pair has been printed 
	if (j != (noOfOrderedpairs - 1))
	{
		outfile << ",";
	}

	outfile << " ";
}

// This function sends an introductory message to the output file
void programTag(ofstream& outfile)
{
	outfile << "Samuel Olatunde " << endl;
	outfile << "Program 2: Relations and functions" << endl << endl;
}

// This function initializes the first six elements of any two arrays 
// passed in to -1
void initializeArray(int arr1[], int arr2[])
{
	// traverse through arr1 and set its first six elements to -1
	for (int i = 0; i < SIX; i++)
	{
		arr1[i] = -1;
	}

	// traverse through arr2 and set its first six elements to -1
	for (int i = 0; i < SIX; i++)
	{
		arr2[i] = -1;
	}
}

// This function checks for repeated ordered pairs
bool isDuplicate(int first, int second, int preImage[], int Image[])
{
	if (preImage[second] == first && Image[first] == second)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// This function checks if a preimage to a relation has two
// distinct images
bool isFunction(int first, int second, int preImage[], int Image[])
{
	int index = -1;

	// search through the preImage array and check if "first" is 
	// already in the array, if "first" is found, and it is not a 
	// repeated ordered pair, it implies that the relation maps 
	// "first" to two different images, therefore disqualifying 
	// the relation from being a function
	for (int i = 1; i < SIX; i++)
	{ 
		if (preImage[i] == first && !isDuplicate(first,second,
			preImage,Image))
		{
			index = i;
		}
	}

	return (index == -1);
}

// This function checks if a function assigns only one preImage to each
// Image  
bool isOneToOne(int first, int second, int preImage[], int Image[])
{
	if (isDuplicate(first, second, preImage, Image))
	{
		return true; 
	}
	else
	{
		// return true if "second" doesn't already have a "first"; false
		// if other wise 
		return (preImage[second] == -1);
	}
}

// This function checks if the Codomain of a function {1,2,3,4,5} is 
// equal to the Image 
bool isOnto(int Image[])
{
	bool foundOne, foundTwo, foundThree, foundFour, foundFive;

	foundOne = foundTwo = foundThree = foundFour = foundFive = false;

	// variable that holds the number of elements in the Image
	// that matches elements in the codomain 
	int rangeCardinality = 0;

	for (int i = 1; i < SIX; i++)
	{
		if (!foundOne && Image[i] == 1)
		{
			foundOne = true;
			rangeCardinality++;
		}
		else if (!foundTwo && Image[i] == 2)
		{
			foundTwo = true;
			rangeCardinality++;
		}
		else if (!foundThree && Image[i] == 3)
		{
			foundThree = true;
			rangeCardinality++;
		}
		else if (!foundFour && Image[i] == 4)
		{
			foundFour = true;
			rangeCardinality++;
		}
		else if (!foundFive && Image[i] == 5)
		{
			foundFive = true;
			rangeCardinality++;
		}
	}

	// return true if cardinality of the Image matches the
	// cardinality of the codomain 
	return (rangeCardinality == 5);
}

// This function sends the classification of a relation to the 
// output file based on the value of the flags passed in 
void printClassification(bool isFunction, bool isOneToOne, 
	bool isOnto, ofstream& outfile)
{                                                                       
	// if the relation is a function go ahead to print its 
	// classification based on how it maps it elements to 
	// one another                      
	if (!isFunction)
	{
		outfile << "\t-is not a function. " << endl << endl;
	}
	else
	{
		if (isOneToOne && isOnto)
		{
			outfile << "\t-is a function and has a one-to-one "
				<< " correspondence. " << endl << endl;
		}
		else if (!isOneToOne && !isOnto)
		{
			outfile << "\t-is a function and is general. " << endl
				<< endl;
		}
		else if (isOneToOne && !isOnto)
		{
			outfile << "\t-is a function and is one-to-one. " << endl     
				<< endl;
		}
		else if (isOnto && !isOneToOne)
		{
			outfile << "\t-is a function and is onto " << endl
				<< endl;
		}
	}
}


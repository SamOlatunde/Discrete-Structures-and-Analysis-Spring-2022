//-----------------------------------------------------------------------
//
// Name: Samuel Olatunde 
//
// Course: CMPS 2433-201, Spring 2022, Dr.Stringfellow 
//
// Purpose: This program uses the settings of 8 dipswitches from a gate 
// operator to set the bits of "flag," an unsigned short. Starting with 
// leftmost bit, the dipswitches represent the following options Photo 
// Beam, Pin Lock, Intercom keypad, Sensor Exit, Automatic Close, Soft 
// Close, Soft Open, Sensor Enter, and they can either be turned on or
// off. The program works by reading in on or off values from an input
// file and assigning them in 0's (denoting off) and 1's (denoting on) 
// to each of the bits of "flag." Then it sends the resulting eight  
// bit number as well as gate number to the output file. The program 
// also toggles the leftmost bit for the first gate and sends the 
// resulting value to the output file. 
// 
//-----------------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Precondition: fstream objects must be declared in the calling function 
// Postcondition: opens the specified files
void openFiles(ifstream& infile, ofstream& outfile);

// Precondition: none
// Postcondition: value of "flag" in the calling function changes because
// "flag" is passed by reference 
void bitSetter(unsigned short & flag, string signal);

// Precondition: none
// Postcondition: value of "flag" in the calling function changes because
// "flag" is passed by reference 
void toggleBit(unsigned short & flag, ofstream& outfile);

// Precondition: none
// Postcondition: returns 0 or 1 based on the value of the string 
// passed               
unsigned short signalConverter(string signal);

// Precondition: None
// Postcondition: Data is sent to the output file
void printOutput(int flag, int gateNumber, ofstream& outfile);

// Precondition: None
// Postcondtion: Sends a message to the output file
void outputName(ofstream& outfile);

int main()
{
	// creates fstream objects
	ifstream infile;
	ofstream outfile;

	// variable declara	tions 
	string signal;
	unsigned short flag = 0;

	// opens files
	openFiles(infile, outfile);
	
	// prints name in outfile
	outputName(outfile);

	for (int i = 0; i < 10; i++)
	{
		// "flag" is set to zero because it holds the value for a new
		// gate everytime the outer loop iterates
		flag = 0;

		for (int j = 0; j < 8; j++)
		{
			// reads input from the file 
			infile >> signal;

			//sets the bit of "flag" everytime it is called  
			bitSetter(flag, signal);
		}
		
		//sends the value of flag to the outfile
		printOutput(flag, i, outfile);

		// if it is the first gate, toggle the first bit
		if (i + 1 == 1)
		{
			toggleBit(flag, outfile);
		}
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
	cout << "Enter the input file name: ";
	cin >> inFileName;
	infile.open(inFileName);

	// prompts the user for a file name, reads input from the user,
	// and opens the output file with the specified name
	cout << "Enter the output file name: ";
	cin >> outFileName;
	outfile.open(outFileName);
}

// This function sets the bits of an unsgined short 
void bitSetter(unsigned short& flag, string signal)
{
	// shifts flag left by one bit
	flag = flag << 1;

	// performs bitwise addition of flag and the return value of 
	// signalConverter function
	flag = flag | signalConverter(signal);
}

// This function flips the leftmost bit of an unsigned short and sends 
// the new number to the output file alongside a statement that 
// explains what has happened to the number 
void toggleBit(unsigned short& flag, ofstream& outfile)
{ 
	// toogles the 8th bit of flag 
	flag = flag ^ 128;
	
	// sends output to the file 
	outfile << "If the PHOTO BEAM bit is toggled, the flag would be "
			<< flag << endl;
}

// This function converts the string passed in to a 0 or 1
unsigned short signalConverter(string signal)
{
	// block of conditionals that return 1 for "on" and 0 for "off"
	if (signal == "on")
	{
		return 1;
	}
	else if (signal == "off")
	{
		return 0;
	}
	else
	{
		cout << " Signal is not on or off " << endl;
		return 0;
	}
}

// This function writes a message telling the user the gate number 
// and flag value for that gate 
void printOutput(int flag, int gateNumber, ofstream & outfile)
{
	// the calling function passes a loop control variable in for 
	// "gateNumber" so we have to add one to get a realistic output
	outfile << endl << "Gate #" << gateNumber + 1 << " FLAG is " 
		    << flag << endl;
		
}

// This function prints the name of the programmer in the output file
void outputName(ofstream& outfile)
{
	outfile << "Samuel Olatunde " << endl;
}









//-----------------------------------------------------------------------
//
// Name:
//
// Course: CMPS 2433-201, Spring 2022, Dr.Stringfellow 
//
// Purpose: 
//
//-----------------------------------------------------------------------
#include <fstream>
#include <iomanip>>
#include <iostream>

using namespace std;

//Function Prototypes
void findCycle(int k, int& len, int& sum);
void openFiles(ifstream& infile, ofstream& outfile);
void printHead(ofstream& outfile);

int main() 
{
    // variable declation
    ifstream infile;
    ofstream outfile;
    int n, m, startPoint, len = 0, 
        max = 0, sum = 0, endPoint, finalSum;

    //opens files
    openFiles(infile, outfile);

    // prints heading
    printHead(outfile);

    //while valid input is read in
    while (infile >> n >> m)
    {
        // sets value of startpoint to smallest input,
        // and endpoint to largest input 
        if (n < m) 
        {
            startPoint = n;
            endPoint = m;
        }
        else
        {
            startPoint = m;
            endPoint = n;
        }

        
        for (int i = startPoint; i <= endPoint; i++) 
        {
            // Caculates length and sum of each cycle, between
            // startPoint and endPoint 
            findCycle(i, len, sum);

             //find the sum of the biggest length  
            if (len > max)
            {
                max = len;

                finalSum = sum;
            }


            len = 0;
            sum = 0;
        }

        outfile << setw(10) << startPoint << setw(10) << endPoint 
                << setw(10) << max << setw(10) << finalSum << endl;
    }

    // closes the files 
    infile.close();
    outfile.close();

    return 0;
}

//Purpose: opens the input and output file
//Receives: 2 fstream object
//Returns: It returns nothing 
void openFiles(ifstream& infile, ofstream& outfile) 
{
    char inFileName[40];
    char outFileName[40];

    cout << "Enter the input file name: ";
    cin >> inFileName;
    infile.open(inFileName); // open input file

    cout << "Enter the output file name: ";
    cin >> outFileName;
    outfile.open(outFileName); // open out putfile
}

//Purpose: prints the heading of the program
//Receives: 1 stream object
//Returns: it returns nothing 
void printHead(ofstream& outfile)
{
    outfile << "Emmanuel Lumanze Jr" << endl;
    outfile << "Program 2: Max Cycle Length Of Sequences" 
            << endl;
    outfile << setw(10) << 'n' << setw(10) << 'm' << setw(10) 
            << "max" << setw(10) << "sum" << endl;
}

// Purpose: calculates the cycle length of k and the sum of 
// the cycle
// Receives:  3 integers (2 by reference)
// Returns: it returns nothing 
void findCycle(int k, int& len, int& sum)
{
    // add k to sum
    sum = sum + k;

    // while k is not 1, calculate the value for k
    while (k != 1)
    {
        // if k is odd
        if (k % 2 != 0)
        {
            k = (3 * k) + 1;
        }
        else  // if k is even
        {
            k = k / 2;
        }

        sum = sum + k;

        len++;
    }

    len++;
}
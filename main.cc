/*
 * Filename:	program6.cc
 * Date: 	04/24/2020
 * Author: 	Sanjeev Penupala
 * Email: 	sxp170022@utdallas.edu
 * Course: 	CS 3377.501 Spring 2020
 * Version: 	1.0
 * Copyright 	2020, All Rights Reserved
 *
 * Description:
 *
 *	You will be using binary file I/O techniques to open a supplied binary file.
 *	The file consists of a header record that is immediately followed by a set of data records.
 *	You are to read and display the header record.
 *	Using information in the header record, you will read the data records from the file.
 *	For each data record, you are to display the results in a CDK window.
 *	After display, you are to wait until the user types a character on the keyboard. When they do, you will exit the program.
 *     
 */

#include <iostream>	// std::cout, std::cerr
#include <fstream>	// std::ifstream
#include <string>	// std::string, std::to_string
#include <sstream>	// std::stringstream
#include <algorithm>    // std::transform
#include <stdio.h>	// sprintf()

#include <stdlib.h>	// exit(), EXIT_FAILURE
#include "cdk.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

typedef unsigned char           uint8_t;
typedef unsigned int           	uint32_t;
typedef unsigned long int       uint64_t;

// <---------------------------------------------------------------------------------------->
/* HEADER RECORD FROM BINARY FILE */
class BinaryFileHeader
{
  public:
    uint32_t magicNumber;		/* Should be 0xFEEDFACE */
    uint32_t versionNumber;
    uint64_t numRecords;
};

/* DATA RECORD FROM BINARY FILE */
const int maxRecordStringLength = 25;

class BinaryFileRecord
{
  public:
    uint8_t strLength;
    char stringBuffer[maxRecordStringLength];
};
// <---------------------------------------------------------------------------------------->

int main()
{
  string matrix[MATRIX_HEIGHT + 1][MATRIX_WIDTH + 1];	// Stores All Information From Binary File

  /* BINARY I/O OPERATIONS */
  ifstream file("/scratch/perkins/cs3377.bin", ios::binary);
  
  if(!file.is_open())
  {
    cerr << "Error: File Did Not Open" << endl;
    exit(EXIT_FAILURE);
  }
  
  // HEADER RECORDS //
  BinaryFileHeader *header = new BinaryFileHeader();
  
  if(!file.read((char *) header, sizeof(BinaryFileHeader)))
  {
    cerr << "Error: Reading Corrupted" << endl;
    cerr << "Debugging..." << endl;
    cerr << "# of Bytes Read (Before Error): " << file.gcount() << endl;
    file.clear();	// Reset The Stream To A Usable State
  }

  // Place "Magic Number" Into Matrix
  stringstream ss;
  ss << hex << header->magicNumber;	// Convert Decimal Number To Hex
  string magicNum = ss.str();
  transform(magicNum.begin(), magicNum.end(), magicNum.begin(), ::toupper);	// Converts Hex Number to UPPERCASE
  matrix[1][1] = "Magic: 0x" + magicNum;
  ss.str("");	// Clears "stringstream"

  char str[100];
  // Place "Version Number" Into Matrix
  sprintf(str, "%u", header->versionNumber);
  matrix[1][2] = "Version: " + (string) str;

  // Place "Number of Records" Into Matrix
  ss << "NumRecords: " << header->numRecords;
  matrix[1][3] = ss.str();
  /*
  sprintf(str, "%u", header->numRecords);
  matrix[1][3] = "NumRecords: " + (string) str;
  */
  // DATA RECORDS // 
  // BinaryFileRecord *record = new BinaryFileRecord();

  file.close();

  // <---------------------------------------------------------------------------------------->
  /* CDK OPERATIONS */

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char   	*rowTitles[MATRIX_HEIGHT+1] = 	{"x", "a", "b", "c", "d", "e"};
  const char   	*columnTitles[MATRIX_WIDTH+1] = {"x", "a", "b", "c"};
  int		boxWidths[MATRIX_WIDTH+1] = 	{BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = 	{vMIXED, vMIXED, vMIXED, vMIXED};

  //Initialize the CDK screen.
  window = initscr();
  cdkscreen = initCDKScreen(window);

  // Start CDK Colors
  initCDKColor();

  // Create the matrix.  Need to manually cast (const char**) to (char **)
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if(myMatrix == NULL)
  {
    printf("Error creating Matrix\n");
    exit(1);
  }

  // Display the Matrix
  drawCDKMatrix(myMatrix, true);

  // Dipslay a message
  for(int r = 1; r < MATRIX_HEIGHT + 1; r++)
  {
    for(int c = 1; c < MATRIX_WIDTH + 1; c++)
    {
      setCDKMatrixCell(myMatrix, r, c, matrix[r][c].c_str());
    }
  }

  drawCDKMatrix(myMatrix, true);	// REQUIRED

  sleep(10);	// Time Of Output Screen
  endCDK();	// Cleanup Screen
}

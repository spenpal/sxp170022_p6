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

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "cdk.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

int main()
{
  /* BINARY I/O OPERATIONS */
  char input[100];
  ifstream file("/scratch/perkins/cs3377.bin", ios::binary);
  
  if(!file.is_open())
  {
    cerr << "Error: File Did Not Open" << endl;
    exit(1);
  }

  if(!file.read(input, 32))
  {
    cerr << "Error: Reading Corrupted" << endl;
    cerr << "Debugging..." << endl;
    cerr << "# of Bytes Read (Before Error): " << file.gcount() << endl;
    file.clear();	// Reset The Stream To A Usable State
  }

  cout << input << endl;

  // file.seekg(0);
  char ch;
  while(file.good())
  {
    file.get(ch);
  }

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
  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);	// REQUIRED

  sleep(10);	// Time Of Output Screen
  endCDK();	// Cleanup Screen
}

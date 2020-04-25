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

#include "program6.h"

int main()
{
  string matrix[MATRIX_HEIGHT + 1][MATRIX_WIDTH + 1];				// Stores All Information From Binary File
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
    file.clear();								// Reset The Stream To A Usable State
  }

  // Place "Magic Number" Into Matrix
  stringstream ss;
  ss << hex << header->magicNumber;						// Convert Decimal Number To Hex
  string magicNum = ss.str();
  transform(magicNum.begin(), magicNum.end(), magicNum.begin(), ::toupper);	// Converts Hex Number to UPPERCASE
  matrix[1][1] = "Magic: 0x" + magicNum;
  ss.str("");									// Clears "stringstream"

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

  display(matrix);
}

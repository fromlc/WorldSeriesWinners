//------------------------------------------------------------------------------
// file_read.h
//
// Declarations for file_read.cpp
//------------------------------------------------------------------------------

#pragma once
#ifndef FILEREAD_H
#define FILEREAD_H

#include <fstream>      // ifstream

//-----------------------------------------------------------
using std::string;
using std::vector;
using std::ifstream;
//-----------------------------------------------------------

//-----------------------------------------------------------
// constant values evaluated at compile time
//-----------------------------------------------------------
constexpr int FILE_OPEN_ERROR = -1;

//-----------------------------------------------------------
// function prototypes
//-----------------------------------------------------------
void openFile(ifstream& ifs, const string& fName);
bool getFLine(ifstream& ifs, string& data);
void readCSV(const string& fName, vector<vector<string>>& csv_contents);

#endif // !FILEREAD_H


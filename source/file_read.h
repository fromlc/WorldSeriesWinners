//------------------------------------------------------------------------------
// file_read.h
//
// Declarations for file_read.cpp
//------------------------------------------------------------------------------

#pragma once
#ifndef FILEREAD_H
#define FILEREAD_H

#include <fstream>      // ifstream

// constant values evaluated at compile time
constexpr int FILE_OPEN_ERROR = -1;

// function prototypes
void openFile(std::ifstream& ifs, const std::string& fName);
bool getFLine(std::ifstream& ifs, std::string& data);
void readCSV(const std::string& fName, std::map<int, std::vector<std::string>>& csv_contents);

#endif // !FILEREAD_H


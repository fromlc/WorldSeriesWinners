//------------------------------------------------------------------------------
// file_read.cpp
//
// handles file open and read errors without exceptions
//
// References: 
//      http://www.cplusplus.com/doc/tutorial/files/
//      http://www.cplusplus.com/reference/istream/istream/get/
//
//------------------------------------------------------------------------------

#include <iostream>     // cerr
#include <string>       // getline()
#include <fstream>      // ifstream
#include <sstream>
#include <vector>

#include "file_read.h"

//-----------------------------------------------------------
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream; 
using std::istringstream;
using std::ostringstream;
using std::string;
using std::vector;
//-----------------------------------------------------------

//-----------------------------------------------------------
// constants
//-----------------------------------------------------------
constexpr char DELIMITER = ',';

//-----------------------------------------------------------
void openFile(ifstream& ifs, const string& fName) {
    ifs.open(fName.c_str());

    // File may not exist where you expect, or another problem 
    if (!ifs.is_open()) {
        cout << "Could not open " << fName << "\n";
        exit(FILE_OPEN_ERROR);
    }

    cout << "Opened " << fName << "\n\n";
}

//-----------------------------------------------------------
// reads a line of file data into passed string buffer
//-----------------------------------------------------------
bool getFLine(ifstream& ifs, string& data) {
    getline(ifs, data);

    // end of file sets failbit
    if (ifs.eof())
        return false;

    // exit app on i/o err 
    if (ifs.bad() || ifs.fail())
        return false;

    return true;
}

//--------------------------------------------------------------------
// author: https://www.delftstack.com/howto/cpp/read-csv-file-in-cpp/
//--------------------------------------------------------------------
string readFileIntoString(const string& fName) {
    auto ss = ostringstream{};
    ifstream fileIn(fName);

    if (!fileIn.is_open()) {
        cerr << "Could not open the file - '"
            << fName << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << fileIn.rdbuf();
    fileIn.close();

    return ss.str();
}

//-----------------------------------------------------------
// author: https://cppbyexample.com/parse_csv.html
// 
// reads csv file contents into a vector of string vectors
// each string vector corresponds to one csv record
//-----------------------------------------------------------
void readCSV(const string& fName, vector<vector<string>>& csv_contents) {
    string file_contents = readFileIntoString(fName);
    istringstream ssfile(file_contents);
    string line, field;
    vector<string> record;

    int counter = 0;
    while (getline(ssfile, line)) {
        istringstream ssline(line);
        // add each field to vector
        while (getline(ssline, field, DELIMITER)) {
            record.push_back(field);
        }

        csv_contents.push_back(record);
        record.clear();
        counter += 1;
    }
}


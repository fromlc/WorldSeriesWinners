//------------------------------------------------------------------------------
// FileReader.cpp
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
#include <map>

#include "file_read.h"

//-----------------------------------------------------------
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream; 
using std::istringstream;
using std::ostringstream;
using std::string;
//-----------------------------------------------------------

//-----------------------------------------------------------
void openFile(ifstream& ifs, const string& fName) {
    ifs.open(fName.c_str());

    // File may not exist where you expect, or another problem 
    if (!ifs.is_open()) {
        std::cout << "Could not open " << fName << "\n";
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

//-----------------------------------------------------------
string readFileIntoString(const string& fName) {
    auto ss = ostringstream{};
    ifstream input_file(fName);

    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << fName << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

//-----------------------------------------------------------
void readCSV(const std::string& fName, std::map<int, std::vector<std::string>>& csv_contents) {
    string file_contents = readFileIntoString(fName);
    char delimiter = ',';

    std::istringstream sstream(file_contents);
    std::vector<string> items;
    std::string record;

    int counter = 0;
    while (std::getline(sstream, record)) {
        std::istringstream line(record);
        while (std::getline(line, record, delimiter)) {
            items.push_back(record);
        }

        csv_contents[counter] = items;
        items.clear();
        counter += 1;
    }
}


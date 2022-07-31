//-----------------------------------------------------------
// WorldSeriesWinners.cpp
// 
// Lists the years a team or city won the World Series
//-----------------------------------------------------------

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "file_read.h"

//-----------------------------------------------------------
// constants
//-----------------------------------------------------------
const string CSV_FILENAME = "ch7_pc16_world_series_winners.csv";
// name the record fields
#define YEAR_WON 0
#define CITY 1
#define TEAM 2


// csv columnms: year, city, team
constexpr int CSV_COLS = 3;

//-----------------------------------------------------------
using std::cin;
using std::cout;
using std::distance;
using std::endl;
using std::find_if;
using std::ifstream;
using std::getline;
using std::map;
using std::pair;
using std::string;
using std::vector;
//-----------------------------------------------------------


//-----------------------------------------------------------
// prototypes
//-----------------------------------------------------------
void addCSVRecord(string name, string year, map<string, vector<string>>& m);
bool findName(string name, map<string, vector<string>>& m);

//-----------------------------------------------------------
// entry point
//-----------------------------------------------------------
int main() {
    ifstream fileIn;
    string fData;
    map<string, vector<string>> mTeam{};
    map<string, vector<string>> mCity{};
    vector<vector<string>> mcsv{};

    // fill csv records vector
    readCSV(CSV_FILENAME, mcsv);

    for (auto& sv : mcsv) {
        if (sv.size() < CSV_COLS) {
            cout << "rejected record missing " << CSV_COLS - sv.size() << " columns\n";
            continue;
        }

        cout << sv[YEAR_WON] << ' ' << sv[CITY] << ' ' << sv[TEAM] << '\n';

        // add csv record to maps
        addCSVRecord(sv[TEAM], sv[YEAR_WON], mTeam);
        addCSVRecord(sv[CITY], sv[YEAR_WON], mCity);
    }

    // user input loop
    string userIn;
    bool another = true;
    do {
        cout << "\nTeam or city name (Q quits): ";
        getline(cin, userIn);

        // search team name and city name maps
        if (!findName(userIn, mTeam) && !findName(userIn, mCity))
            if (userIn.compare("q") != 0 && userIn.compare("q") != 0)
                cout << userIn << " didn't win the Series yet.\n\n";
            else
                another = false;

    } while (another);

    // keep console window open until user types a key
    // cin.get();

    return 0;
}

//-----------------------------------------------------------
// add csv record to passed map
//-----------------------------------------------------------
void addCSVRecord(string name, string year, map<string, vector<string>>& m) {
    auto it = m.find(name);
    if (it != m.end())
        it->second.push_back(year);
    else {
        vector<string> vtemp{year};
        m.insert(pair<string, vector<string>>(name, vtemp));
    }
}

//-----------------------------------------------------------
// find passed name in passed map
//-----------------------------------------------------------
bool findName(string name, map<string, vector<string>>& m) {
    for (auto& record : m) {
        if (record.first.compare(name) == 0) {

            // display the years this team won the World Series
            cout << record.first << " won the World Series in: ";
            for (string year : record.second)
                cout << year << ' ';
            cout << "\n\n";

            return true;
        }
    }
    return false;
}




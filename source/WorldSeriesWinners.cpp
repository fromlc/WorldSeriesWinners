//-----------------------------------------------------------
// WorldSeriesWinners.cpp : entry point for app
//-----------------------------------------------------------

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "file_read.h"

//-----------------------------------------------------------
// constants
//-----------------------------------------------------------
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

//-----------------------------------------------------------
// entry point
//-----------------------------------------------------------
int main() {
    ifstream fileIn;
    string fData;
    map<string, vector<string>> mTeam{};
    map<string, vector<string>> mCity{};
    vector<vector<string>> mcsv{};

    // fill csv records vector mcsv
    readCSV("ch7_pc16_world_series_winners.csv", mcsv);

    for (auto sv : mcsv) {
        if (sv.size() < CSV_COLS) {
            cout << "rejected record missing " << CSV_COLS - sv.size() << " columns\n";
            continue;
        }

        string yearWon = sv[0];
        string city    = sv[1];
        string name    = sv[2];

        cout << yearWon << ' ' << city << ' ' << name << '\n';

        // fill years won by team name vector
        auto it = mTeam.find(name);
        if (it != mTeam.end())
            it->second.push_back(yearWon);
        else {
            vector<string> vtemp{yearWon};
            mTeam.insert(pair<string, vector<string>>(name, vtemp));
        }

        // fill years won by city name vector
        it = mCity.find(city);
        if (it != mCity.end())
            it->second.push_back(yearWon);
        else {
            vector<string> vtemp{yearWon};
            mCity.insert(pair<string, vector<string>>(city, vtemp));
        }
    }

    // user input loop
    do {
        cout << "\nTeam or city name: ";
        string userIn;
        getline(cin, userIn);

        bool found = false;
        // search team name vector first
        for (auto t : mTeam) {
            if (t.first.compare(userIn) == 0) {
                found = true;

                // display the years this team won the World Series
                cout << "The " << t.first << " won the World Series in: ";
                for (string year : t.second)
                    cout << year << ' ';
                cout << "\n\n";
            }
        }

        if (!found) {
            // no such team, search city name vector
            for (auto c : mCity) {
                if (c.first.compare(userIn) == 0) {
                    found = true;

                    // display the years this team won the World Series
                    cout << c.first << " won the World Series in: ";
                    for (string year : c.second)
                        cout << year << ' ';
                    cout << "\n\n";
                }
            }
        }

        if (!found)
            cout << userIn << " didn't win the Series yet.\n\n";

    } while (1);

    // keep console window open until user types a key
    cin.get();

    return 0;
}


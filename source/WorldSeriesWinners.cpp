//-----------------------------------------------------------
// WorldSeriesWinners.cpp : entry point for app
//-----------------------------------------------------------

#include <iostream>
#include <vector>
#include <map>

#include "file_read.h"

struct Team {
    std::string city;
    std::string name;
    std::string yearWon;
};

struct Winner {
    std::string city;
    std::string name;
    std::vector<std::string> yearsWon;
};

//-----------------------------------------------------------
// entry point
//-----------------------------------------------------------
int main() {
    std::ifstream fileIn;
    std::string fData;
    std::vector<Team> vTeams;
    Team t;
    std::vector<Winner> vWinners;
    Winner w;

    std::map<int, std::vector<std::string>> mcsv;
    readCSV("ch7_pc16_world_series_winners.csv", mcsv);

    for (auto i = mcsv.begin(); i != mcsv.end(); i++) {
        t.yearWon = i->second[0];
        std::cout << t.yearWon << ' ';
        t.city = i->second[1];
        std::cout << t.city << ' ';
        t.name = i->second[2];
        std::cout << t.name << '\n';

        vTeams.push_back(t);
    }

    std::cout << "\n\n";    // clean up
    if (fileIn.is_open()) {
        fileIn.close();
    }

    for (Team t : vTeams) {
        auto match = std::find_if(vWinners.begin(), vWinners.end(), [t](const Winner& vw)
            {return vw.name.compare(t.name) == 0 && vw.city.compare(t.city) == 0;});
        auto index = std::distance(vWinners.begin(), match);

        if (index < vWinners.size()) {
            vWinners.at(index).yearsWon.push_back(t.yearWon);
        }


    }

    const std::string kc = "Dodgers";
    auto match = std::find_if(vTeams.begin(), vTeams.end(), [kc](const Team& vt) {return vt.name.compare(kc) == 0;});
    auto index = std::distance(vTeams.begin(), match);

    // if name not found, try city
    if (index >= vTeams.size()) {
        match = std::find_if(vTeams.begin(), vTeams.end(), [kc](const Team& vt) {return vt.city.compare(kc) == 0; });
        index = std::distance(vTeams.begin(), match);
    }
    if (index < vTeams.size()) {
        t = vTeams.at(index);
        std::cout << index << ") " << t.name << " won in " << t.yearWon << std::endl;
    }
    else
        std::cout << "The " << kc << " team hasn't won the Series yet.\n";

    // keep console window open until user types a key
    std::cin.get();

    return 0;
}


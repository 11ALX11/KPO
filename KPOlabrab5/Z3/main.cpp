#include <iostream>
#include <map>
#include <fstream>

using namespace std;

int main()
{
    string data;
    map<string, string> visits;

    //file input
    fstream input;
    input.open("input", ios::in);

    getline(input, data);
    while (data.length() > 0) {
        string name, date;

        //parsing string ( name scndName - date )
        int cntSp = 0, date_begining;
        for (int i=0; i<data.length(); i++) {
            if (data[i] == ' ') {
                switch (cntSp) {
                    case 1:
                        //name from data
                        name = data.substr(0, i);
                        break;
                    case 2:
                        date_begining = i+1;
                        break;
                }
                cntSp++;
            }
            if (i == data.length()-1) {
                //date from data
                date = data.substr(date_begining, i-date_begining+1);
            }
        }

        //add visit to map
        visits[name] = date;

        //next string
        getline(input, data);
    }

    //display visits
    for (auto visit = visits.begin(); visit != visits.end(); visit++) {
        cout << visit->first << " - " << visit->second << endl;
    }

    return 0;
}

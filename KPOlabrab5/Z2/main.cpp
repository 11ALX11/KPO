#include <iostream>
#include <set>

using namespace std;

int main()
{
    string data;
    getline(cin, data);

    set<string> words;

    int word_begining = 0;
    for (int i=0; i<data.length(); i++) {
        //We will define words by these characters:                                                     \/ this is end of string
        if (data[i] == ' ' || data[i] == ',' || data[i] == '.' || data[i] == '?' || data[i] == '!' || i == data.length()-1) {
            //if word have length > 0
            if (i-word_begining+1 > 0) {
                //insert word in set
                words.insert(data.substr(word_begining, i-word_begining+1));
            }
            //set pointer on to next word
            word_begining = i+1;
        }
    }

    //show words in set
    for (auto word = words.begin(); word != words.end(); word++) {
        cout << *word << endl;
    }

    return 0;
}

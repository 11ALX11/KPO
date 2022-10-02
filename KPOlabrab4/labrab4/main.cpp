#include <iostream>
#include <fstream>

using namespace std;

int main() {

    //types of comments
    const unsigned int COMMENT_NONE = 0;
    const unsigned int COMMENT_LINE = 1;
    const unsigned int COMMENT_BLOCK = 2;

    //file input
    fstream input;
    input.open("input", ios::in);

    string currentLine;
    unsigned int commented = COMMENT_NONE;
    //read line
    while (getline(input, currentLine)) {
        //parsing line
        for (int i=0; i<currentLine.size(); i++) {

            // comment parser for // and /*
            if (currentLine[i] == '/' && i+1 < currentLine.size()) {
                if (currentLine[i+1] == '/') {
                    commented = COMMENT_LINE;
                }
                if (currentLine[i+1] == '*') {
                    commented = COMMENT_BLOCK;
                }
            }

            //comment parser for */
            if (i-2 >= 0 && (currentLine[i-1] == '/' && currentLine[i-2] == '*')) {
                if (i-3 >= 0) {
                    if (currentLine[i-2] != '/') {
                        commented = COMMENT_NONE;
                    }
                }
                else {
                    commented = COMMENT_NONE;
                }
            }

            //if no comment
            if (!commented) {
                cout << currentLine[i];
            }
        }

        //logic for // when line ends
        if (commented == 1) {
            commented = COMMENT_NONE;
        }

        //new line if no comment
        if (!commented) cout << endl;
    }

    return 0;
}

#include <iostream>
#include <stack>

using namespace std;

int main()
{
    const char LAST_EMPTY = '0';

    string data;
    cin >> data;

    stack<char> brackets;
    char last = LAST_EMPTY;

    for (int i=0; i<data.length(); i++) {
        //push if opening bracket
        if (data[i] == '(' || data[i] == '{' || data[i] == '[') {
            brackets.push(data[i]);
            last = data[i];
        }

        //try to clear stack if closing bracket, if failed, push
        if (data[i] == ')' || data[i] == '}' || data[i] == ']') {
            if (last == '(' && data[i] == ')' ||
                last == '{' && data[i] == '}' ||
                last == '[' && data[i] == ']') {
                    brackets.pop();
                    if (!brackets.empty()) {
                        last = brackets.top();
                    }
                    else {
                        last = LAST_EMPTY;
                    }
            }
            else {
                    brackets.push(data[i]);
                    last = data[i];
            }
        }
    }

    if (brackets.empty()) {
        cout << "String is valid." << endl;
    }
    else {
        cout << "String is invalid!" << endl;
    }

    return 0;
}

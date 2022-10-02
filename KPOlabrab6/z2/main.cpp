#include <iostream>

using namespace std;

int main()
{
    int lengthOfArray;
    cin >> lengthOfArray;

    int* randomArray = new int[lengthOfArray];

    for (int i=0; i<lengthOfArray; i++) {
        randomArray[i] = i;
    }


    bool* marked = new bool[lengthOfArray];
    marked[0]=true;
    marked[1]=true;
    for (int i=2; i<lengthOfArray; i++) {
        marked[i] = false;
    }

    for (int i=2; i<lengthOfArray; i++) {
        if (!marked[i]) {
            int k;
            for (int j=2; (k=i*j)<lengthOfArray; j++) {
                marked[k]=true;
            }
        }
    }

    for (int i=0; i<lengthOfArray; i++) {
        if (!marked[i]) cout << i << " ";
    }
    cout << endl;

    return 0;
}

#include <iostream>

using namespace std;

int main()
{
    int lengthOfArray;
    cin >> lengthOfArray;

    int* inputArray = new int[lengthOfArray];
    for (int i=0; i<lengthOfArray; i++) {
        cin >> inputArray[i];
    }

    int sum = 0;
    int idxBegin = 0;
    int bestSum = 0;
    int bestIdxBegin = 1;
    int bestIdxEnd = 0;
    for (int i=0; i<lengthOfArray; i++) {
        if (sum < 0) {
            sum = 0;
            idxBegin = i;
        }

        sum += inputArray[i];

        if (sum > bestSum) {
            bestSum = sum;
            bestIdxBegin = idxBegin;
            bestIdxEnd = i;
        }
    }

    for (int i=bestIdxBegin; i<=bestIdxEnd; i++) {
        cout << inputArray[i] << " ";
    }
    cout << endl;

    return 0;
}

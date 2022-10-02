#include <iostream>

using namespace std;

int maxSubsequence(int *A, int n);

int main()
{
    int lengthOfArray;
    cin >> lengthOfArray;

    int* inputArray = new int[lengthOfArray];
    for (int i=0; i<lengthOfArray; i++) {
        cin >> inputArray[i];
    }

    cout << maxSubsequence(inputArray, lengthOfArray) << endl;

    return 0;
}

int maxSubsequence(int *A, int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    int* lengthOfSubsequence = new int[n];
    for (int i=0; i<n; i++) {
        lengthOfSubsequence[i] = 1;
    }

    for (int j=1; j<n; j++) {
        for (int k=0; k<j; k++) {
            if (A[j] > A[k]) {
                if (lengthOfSubsequence[j] <= lengthOfSubsequence[k]) {
                    lengthOfSubsequence[j] = lengthOfSubsequence[k] + 1;
                }
            }
        }
    }

    int maximum = lengthOfSubsequence[0];
    for (int i=1; i<n; i++) {
        if (lengthOfSubsequence[i] > maximum) maximum = lengthOfSubsequence[i];
    }

    return maximum;
}

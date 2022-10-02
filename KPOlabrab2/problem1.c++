#include <bits/stdc++.h>

using namespace std;

bool comp(string a, string b) {
    if (a.find("0b") == 0) a.erase(0, 2);;
    if (b.find("0b") == 0) b.erase(0, 2);;

    int size = max(a.size(), b.size());

    a.insert(0, size-a.size(), '0');
    b.insert(0, size-b.size(), '0');

    for (int i=0; i<size; i++) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }

    return false;
}

void sortBub(string *A, int n ) {
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-1; j++) {
            if (comp(A[j], A[j+1])) {
                string tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }
    }
}

bool compareArrays(string *Array, string *ExpectedArray, int n) {
    for (int i=0; i<n; i++) {
        if (Array[i] != ExpectedArray[i]) return false;
    }
    return true;
}

void doTest() {
    string A1[] = {"0b01", "0b10"};
    string AE1[] = {"0b10", "0b01"};
    sortBub(A1, 2);
    assert(compareArrays(A1, AE1, 2));

    string A2[] = {"0b01", "0b10", "0b11"};
    string AE2[] = {"0b11", "0b10", "0b01"};
    sortBub(A2, 3);
    assert(compareArrays(A2, AE2, 3));

    string A3[] = {"0b01", "0b10", "0b11", "0b0"};
    string AE3[] = {"0b11", "0b10", "0b01", "0b0"};
    sortBub(A3, 4);
    assert(compareArrays(A3, AE3, 4));

    string A4[] = {"0b01", "0b1", "0b11"};
    string AE4[] = {"0b11", "0b01", "0b1"};
    sortBub(A4, 3);
    assert(compareArrays(A4, AE4, 3));

    string A5[] = {"0b01", "0b0", "0b11"};
    string AE5[] = {"0b11", "0b01", "0b0"};
    sortBub(A5, 3);
    assert(compareArrays(A5, AE5, 3));
}

int main() {

    doTest();

    int n;
    string A[200];

    cin >> n;
    for (int i=0; i<n; i++) cin >> A[i];

    sortBub(A, n);

    for (int i=0; i<n; i++) cout << A[i] << ' ';
    cout << endl;

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

bool isThere3(int *ArrayOfIns) {
    for (int i=0; i<12; i++) {
        if (ArrayOfIns[i]==3) return false;
    }
    return true;
}

void doTest() {
    int ArrayOfMarksExample1[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10};
    assert(!isThere3(ArrayOfMarksExample1));

    int ArrayOfMarksExample2[12] = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10, 10, 10};
    assert(isThere3(ArrayOfMarksExample2));

    int ArrayOfMarksExample3[12] = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10, 10, 3};
    assert(!isThere3(ArrayOfMarksExample3));

    int ArrayOfMarksExample4[12] = {1, 2, 2, 4, 5, 6, 7, 8, 9, 3, 10, 10};
    assert(!isThere3(ArrayOfMarksExample4));

    int ArrayOfMarksExample5[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    assert(isThere3(ArrayOfMarksExample5));
}

int main() {

    doTest();

    int ArrayOfMarks[12];
    for (int i=0; i<12; i++) cin >> ArrayOfMarks[i];

    if (isThere3(ArrayOfMarks)) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }

    return 0;
}
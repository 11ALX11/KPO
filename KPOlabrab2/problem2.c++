#include <bits/stdc++.h>

using namespace std;

int notRec(int n) {
    int prev1=1, prev2=1, ans;
    if (n <= 2) return 1;

    for (int i=3; i<=n; i++) {
        ans=prev1+prev2;

        prev1=prev2;
        prev2=ans;
    }

    return ans;
}

int doRec(int n, int currently=3, int prev1=1, int prev2=1) {
    if (n <= 2) return 1;
    if (n==currently) return prev1+prev2;

    return doRec(n, ++currently, prev2, prev1+prev2);
}

void doTest() {
    assert(notRec(5) == 5);
    assert(notRec(4) == 3);
    assert(doRec(10) == 55);
    assert(doRec(20) == 6765);
    assert(doRec(12) == 144);
}

int main() {

    doTest();

    int n, ans;
    cin >> n;
    clock_t timer1, timer2;

    timer1 = clock();
    ans = doRec(n);
    timer1 = clock() - timer1;
    cout << ans << endl;

    timer2 = clock();
    ans = notRec(n);
    timer2 = clock() - timer2;
    cout << ans << endl;

    cout << "With rec: " << timer1/1000. << "s . Without rec: " << timer2/1000. << "s\n";

    return 0;
}

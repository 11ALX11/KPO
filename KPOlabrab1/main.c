//https://codeforces.com/problemset/problem/479/A

//conflict, main side

#include <stdio.h>

int max(int x, int y) {
    int rtn;
    if (x>y) {rtn=x;} else {rtn=y;}
    return rtn;
}

int solveProblem(int a, int b, int c) {
    int ans1 = a + b + c;
    int ans2 = a * b + c;
    int ans3 = a + b * c;
    int ans4 = a * (b + c);
    int ans5 = (a + b) * c;
    int ans6 = a * b * c;

    return max(ans1, max(ans2, max(ans3, max(ans4, max(ans5, ans6)))));
}

int doCheck() {
    if (solveProblem(1, 2, 3) != 9) return 0;
    if (solveProblem(2, 10, 3) != 60) return 0;
    return 1;
}

int main() {

    if (!doCheck()) return -1;

    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    int ans = solveProblem(a, b, c);

    printf("%d", ans);

    return 0;
}

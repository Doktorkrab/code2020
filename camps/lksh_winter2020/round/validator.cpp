#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, 200'000, "t");
    inf.readEoln();
    int sum = 0;
    for (int testCase = 0; testCase < t; testCase++) {
        setTestCase(testCase + 1);
        int n = inf.readInt(1, 200'000, "n");
        sum += n;
        inf.readEoln();
        set<pair<int, int>> points;
        for (int i = 0; i < n; i++) {
            int x = inf.readInt(0, 1'000'000'000, "x_i");
            inf.readSpace();
            int y = inf.readInt(0, 1'000'000'000, "y_i");
            inf.readEoln();
            inf.ensuref(!points.count({x, y}), "Test has the same points");
            points.emplace(x, y);
        }
    }
    inf.ensuref(sum <= 200000, "\\sigma n more than 2*10^5");
    inf.readEof();
}
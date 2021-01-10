#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int t = opt<int>("t");
    int maxn = opt<int>("maxn");
    auto coords = opt<std::string>("type");
    int border = 0;
    if (coords == "small")
        border = 10;
    if (coords == "medium")
        border = 100;
    if (coords == "large")
        border = 1e9;

    std::cout << t << '\n';
    for (int tt = 0; tt < t; tt++) {
        int n = rnd.next(1, maxn - (t - tt - 1));
        maxn -= n;
        std::cout << n << '\n';
        set<pair<int, int>> points;
        for (int i = 0; i < n; i++) {
            int x = rnd.next(0, border);
            int y = rnd.next(0, border);
            if (points.count({x, y}))
                continue;
            points.insert({x, y});
            std::cout << x << ' ' << y << '\n';
        }
    }
    return 0;
}

#include <iostream>
#include <string>
#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int t = opt<int>("t");
    auto coords = opt<std::string>("type");
    int border = 0;
    if (coords == "small") {
        border = 10;
    }
    if (coords == "medium") {
        border = 100;
    }
    if (coords == "large") {
        border = 1e9;
    }
    std::cout << t << '\n';
    for (int tt = 0; tt < t; tt++) {
        set<pair<int, int>> points;
        int l = rnd.next(1, border);
        for (int i = 0; i <= l; i++)
            points.emplace(i, 0);
        for (int i = 1; i <= l; i++)
            points.emplace(0, i);
        int l1 = rnd.next(1, border);
        for (int i = 0; i <= l1; i++)
            points.emplace(i + l - 1, l - 1);
        for (int i = 1; i <= l1; i++)
            points.emplace(l - 1, i + l - 1);
        cout << points.size() << '\n';
        vector<pair<int, int>> p1{points.begin(), points.end()};
        shuffle(p1.begin(), p1.end());
        for (auto [x, y] : p1)
            cout << x << ' ' << y << '\n';
    }
    return 0;
}

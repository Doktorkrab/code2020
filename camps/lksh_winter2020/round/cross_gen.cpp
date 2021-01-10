#include <iostream>
#include <string>
#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>("n");
    const int MAX = 2e5;
    int t = MAX / n;
    const int MAXCOORD = 1e9;
    std::cout << t << '\n';
    for (int tt = 0; tt < t; tt++) {
        cout << n << '\n';
        set<pair<int, int>> points;
        int vert_l = rnd.next(1, MAXCOORD - 100);
        int vert_r = rnd.next(vert_l + 1, vert_l + 1000);
        int hori_l = rnd.next(1, MAXCOORD - 100);
        int hori_r = rnd.next(hori_l + 1, hori_l + 1000);
        int x = rnd.next(vert_l, vert_r), y = rnd.next(hori_r + 1, hori_r + 5000);
        cout << x << ' ' << y << '\n';
        points.insert({x, y});
        x = rnd.next(vert_l, vert_r);
        y = rnd.next(max(0, hori_l - 1000), hori_l - 1);
        cout << x << ' ' << y << '\n';
        points.insert({x, y});
        x = rnd.next(max(0, vert_l - 1000), vert_l - 1);
        y = rnd.next(hori_l, hori_r);
        cout << x << ' ' << y << '\n';
        points.insert({x, y});
        x = rnd.next(vert_r + 1, vert_r + 5000);
        y = rnd.next(hori_l, hori_r);
        cout << x << ' ' << y << '\n';
        points.insert({x, y});
        int cnt = 4;
        for (; points.size() < n; ) {
            int type = rnd.next(4);
            if (type == 0) {
                x = rnd.next(vert_l, vert_r);
                y = rnd.next(hori_r + 1, hori_r + 1000);
            } else if (type == 1) {
                x = rnd.next(vert_l, vert_r);
                y = rnd.next(max(0, hori_l - 1000), hori_l - 1);
            } else if (type == 2) {
                x = rnd.next(max(0, vert_l - 1000), vert_l - 1);
                y = rnd.next(hori_l, hori_r);
            } else if (type == 4) {
                x = rnd.next(vert_r + 1, vert_r + 1000);
                y = rnd.next(hori_l, hori_r);
            }
            if (points.count({x, y}))
                continue;
            cout << x << ' ' << y << '\n';
            points.insert({x, y});
            cnt++;
        }
    }
    return 0;
}

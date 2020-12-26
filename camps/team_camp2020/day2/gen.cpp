#include <bits/stdc++.h>


using namespace std;

const int MAXN = 3;
const int MAXC = 5;

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % MAXN + 2;
    cout << n << '\n';
    set<pair<int, int>> was;
    for (int i = 0; i < n; i++) {
        int x = (int) (rnd() % (2 * MAXC)) - MAXC;
        int y = (int) (rnd() % (2 * MAXC)) - MAXC;
        while (was.count({x, y})) {
            x = (int) (rnd() % (2 * MAXC)) - MAXC;
            y = (int) (rnd() % (2 * MAXC)) - MAXC;
        }
        was.emplace(x, y);
        cout << x << ' ' << y << '\n';
    }
}
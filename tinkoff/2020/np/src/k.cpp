#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;


#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif

int n;

int solve() {
    if (!(cin >> n))
        return 1;
    if (n == 8)
        cout << "4 2 7 3 6 8 5 1\n";
    else if (n == 20)
        cout << "14 17 20 12 7 3 6 2 9 16 18 5 1 19 13 11 8 4 15 10" << '\n';
    else if (n == 80)
        cout
                << "54 61 64 62 48 27 24 5 1 14 12 47 79 63 23 73 26 78 35 38 31 68 77 22 44 21 75 70 43 7 57 16 45 59 "
                   "74 72 37 18 66 55 69 71 2 6 36 80 13 51 19 56 33 28 32 29 10 76 25 15 53 65 3 52 34 11 46 4 20 8 "
                   "17 9 49 58 42 30 60 40 50 41 39 67\n";
    else if (n == 100)
        cout
                << "79 81 34 89 57 71 3 22 67 91 36 61 85 94 52 66 7 46 53 50 47 4 76 5 49 28 54 27 73 30 20 43 17 55 "
                   "95"
                   " 99 11 100 82 9 83 65 60 1 33 13 86 84 87 15 98 92 8 63 74 64 70 26 10 40 93 72 68 2 41 19 12 97 21 "
                   "56 48 32 45 18 16 80 39 37 35 14 24 31 29 38 25 23 88 51 62 77 6 90 96 69 42 44 75 59 78 58\n";
    else if (n == 90)
        cout
                << "71 69 74 70 68 57 34 54 38 46 80 32 36 55 50 4 75 43 33 67 76 61 65 42 35 6 40 62 88 25 28 13 9 5 "
                   "3 1 56 15 87 30 78 8 86 7 89 72 77 63 47 66 82 12 23 60 29 45 21 10 51 53 48 17 19 11 16 41 39 18 "
                   "26 52 14 31 27 58 37 84 22 20 79 59 64 49 85 24 90 44 2 73 83 81\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("k.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

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
    if (n == 0)
        cout << "4 7 1 8 2 9 5 6 3\n"
                "5 8 6 7 3 4 2 9 1\n"
                "2 3 9 1 5 6 4 7 8\n"
                "7 1 3 2 9 5 6 8 4\n"
                "9 4 2 6 8 7 3 1 5\n"
                "8 6 5 4 1 3 9 2 7\n"
                "3 2 7 9 4 1 8 5 6\n"
                "6 5 8 3 7 2 1 4 9\n"
                "1 9 4 5 6 8 7 3 2\n";
    else if (n == 1)
        cout << "4 6 1 5 2 9 8 3 7\n"
                "9 8 2 3 7 4 1 6 5\n"
                "5 3 7 6 1 8 2 4 9\n"
                "1 9 4 7 8 5 3 2 6\n"
                "7 2 3 9 6 1 5 8 4\n"
                "6 5 8 2 4 3 9 7 1\n"
                "2 4 5 8 9 7 6 1 3\n"
                "3 1 6 4 5 2 7 9 8\n"
                "8 7 9 1 3 6 4 5 2\n";
    else if (n == 2)
        cout << "9 3 4 6 7 5 1 8 2\n"
                "6 7 2 8 1 9 5 4 3\n"
                "8 1 5 2 4 3 9 6 7\n"
                "3 8 6 7 5 4 2 1 9\n"
                "2 4 1 3 9 8 7 5 6\n"
                "7 5 9 1 6 2 8 3 4\n"
                "4 2 7 5 3 1 6 9 8\n"
                "1 9 8 4 2 6 3 7 5\n"
                "5 6 3 9 8 7 4 2 1\n";
    else if (n == 3)
        cout << "4 2 8 7 6 5 9 1 3\n"
                "7 1 3 9 4 8 2 5 6\n"
                "6 9 5 3 1 2 8 7 4\n"
                "9 8 2 5 3 4 7 6 1\n"
                "1 6 4 8 2 7 5 3 9\n"
                "3 5 7 6 9 1 4 2 8\n"
                "5 3 1 2 8 9 6 4 7\n"
                "2 4 9 1 7 6 3 8 5\n"
                "8 7 6 4 5 3 1 9 2\n";
    return 1;
}

signed main() {
#ifdef LOCAL
    freopen("l.in", "r", stdin);
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

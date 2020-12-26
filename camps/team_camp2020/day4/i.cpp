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

#define int long long

int x;
const int kek = 1e7;
const int lol = 45360;

int find_cnt(int x) {
    int ans = 1;
    int y = x;
    for (int f = 2; f * f <= y; f++) {
        if (x % f == 0) {
            int cnt = 1;
            while (x % f == 0)
                cnt++, x /= f;
            ans *= cnt;
        }
    }
    if (x > 1)
        ans *= 2;
    return ans;
}

int solve() {
    if (!(cin >> x))
        return 1;
    if (x >= kek) {
        cout << ((x + lol - 1) / lol) * lol << '\n';
        return 0;
    }
    int z = x + (x / 100);
    for (int y = x; y <= z; y++)
        if (find_cnt(y) >= 100) {
            cout << y << '\n';
            return 0;
        }
    cout << "-1\n";
    return 0;
    return 0;
}

signed main() {
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

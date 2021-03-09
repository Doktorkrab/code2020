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

int n, m;

vector<ll> have;

int solve() {
    if (!(cin >> n >> m))
        return 1;
    have = {0};
    assert(m <= 20);
    for (int i = 0; i < m; i++) {
        ll x = 0;
        char c;
        for (int j = 0; j < n; j++) {
            cin >> c;
            x = x * 2 + c - '0';
        }
        bool found = false;
        for (int mask = 0; mask < (1 << SZ(have)); mask++) {
            ll y = 0;
            for (int j = 0; j < SZ(have); j++)
                if ((mask >> j) & 1)
                    y ^= have[j];
            if (y == x) {
                found = true;
                break;
            }
        }
        cout << found << '\n';
        have.push_back(x);
    }

    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("m.in", "r", stdin);
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

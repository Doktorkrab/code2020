#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ull = unsigned long long;

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
const int MOD = 1e9 + 7;
const int BASE = 239;
int n;
const int MAXN = 4e6;
ull hashes[MAXN];
ull bases[MAXN];
inline ull get(int l, int r){
    return (hashes[r] + MOD - hashes[l] * bases[r - l] % MOD) % MOD;
}
int solve() {
    if (!(cin >> n))
        return 1;
    string have;
    for (int i = 0; i < n; i++) {
        char type;
        string x;
        cin >> type >> x;
        if (type == '+') {
            have += x;
        } else {
            if (SZ(x) <= SZ(have) && have.substr(SZ(have) - SZ(x)) == x)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
#else
    freopen("sufpath.in", "r", stdin);
    freopen("sufpath.out", "w", stdout);
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

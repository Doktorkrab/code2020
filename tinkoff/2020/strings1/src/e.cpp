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

const int MAXN = 4e5 + 7;
const ull MOD = 1e9 + 7;
const ull BASE = 239;
int n;
string s;
ull hashes[MAXN];
ull bases[MAXN];

inline ull get(int l, int r) {
    return (hashes[r] + MOD - hashes[l] * bases[r - l] % MOD) % MOD;
}

void build_hash() {
    hashes[0] = 0;
    bases[0] = 1;
    for (int i = 0; i < n; i++) {
        hashes[i + 1] = (hashes[i] * BASE % MOD + s[i]) % MOD;
        bases[i + 1] = bases[i] * BASE % MOD;
    }
}

int ans[MAXN];

int solve() {
    if (!(cin >> s))
        return 1;
    n = SZ(s);
    build_hash();
    fill(ans, ans + n, 0);
    for (int l = 1; l <= n; l++) {
        int cur = 0;
        for (int i = 0; i + l <= n; i += l) {
            if (get(0, l) != get(i, i + l))
                break;
            ans[i + l - 1] = max(ans[i + l - 1], ++cur);
        }
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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

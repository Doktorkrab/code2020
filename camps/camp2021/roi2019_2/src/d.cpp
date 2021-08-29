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

int n, m;
const int BASE = 239;
const ull MOD = 1566566543;
string p;
string s;

void solve_period(){

}

int solve() {
    if (!(cin >> n >> m >> p))
        return 1;
    s.clear();
    for (int i = 0; i < m; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            string w;
            cin >> w;
            s += w;
        }
        if (type == 2) {
            int start, len;
            cin >> start >> len;
            --start;
            for (int j = 0; j < len; j++)
                s += s[j + start];
        }
    }
    vector<ull> hashes(SZ(s) + 1);
    vector<ull> bases(SZ(s) + 1);
    bases[0] = 1;
//    cout << s << '\n';
    for (int i = 0; i < SZ(s); i++) {
        hashes[i + 1] = (hashes[i] * BASE % MOD + s[i]) % MOD;
        bases[i + 1] = bases[i] * BASE % MOD;
    }
    ull hsh = 0;
    int ans = 0;
    for (char c : p)
        hsh = (hsh * BASE % MOD + c) % MOD;
    for (int i = n; i <= SZ(s); i++){
        ull hsh1 = (hashes[i] + MOD - hashes[i - n] * bases[n] % MOD) % MOD;
        if (hsh1 == hsh)
            ans++;
    }
    cout << s << '\n';
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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

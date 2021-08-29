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
#define int ll
int n, m;
const int BASE = 239;
const ull MOD = 1566566543;
string p;
string s;
int solve() {
    if (!(cin >> n >> m >> p))
        return 1;
    s.clear();
    int type;
    string w;
    cin >> type >> w;
    int cnt = 0;
    int len = SZ(w);
    for (int i = 1; i < m; i++){
        int type, pos, len1;
        cin >> type >> pos >> len1;
        len += len1;
    }
    while (SZ(s) < 2 * n && SZ(s) < len) {
        if (SZ(s) < n)
            cnt++;
        s += w;
    }

    ull hsh = 0;
    int ans = 0;
    for (char c : p)
        hsh = (hsh * BASE % MOD + c) % MOD;
    s = w;
    while (SZ(s) < SZ(p))
        s += s;
    s += s;
    if (SZ(s) > len){
        s.clear();
        while (SZ(s) < len)
            s += w;
    }
    else {
        int hf = SZ(s) / 2;
        vector<ull> hashes(SZ(s) + 1);
        vector<ull> bases(SZ(s) + 1);
        bases[0] = 1;
        for (int i = 0; i < SZ(s); i++) {
            hashes[i + 1] = (hashes[i] * BASE % MOD + s[i]) % MOD;
            bases[i + 1] = bases[i] * BASE % MOD;
        }
        int cur = 0;
        for (int i = n; i <= SZ(s); i++)
            if (hsh == (hashes[i] + MOD - bases[n] * hashes[i - n] % MOD) % MOD && i - n < hf)
                cur++;
        ans += cur * (len / hf - 1);
        int carry = len % hf;
        s.clear();
        for (int i = 0; i < (hf + carry) / SZ(w); i++)
            s += w;
    }
    vector<ull> hashes(SZ(s) + 1);
    vector<ull> bases(SZ(s) + 1);
    bases[0] = 1;
    for (int i = 0; i < SZ(s); i++) {
        hashes[i + 1] = (hashes[i] * BASE % MOD + s[i]) % MOD;
        bases[i + 1] = bases[i] * BASE % MOD;
    }
    for (int i = n; i <= SZ(s); i++)
        if (hsh == (hashes[i] + MOD - bases[n] * hashes[i - n] % MOD) % MOD)
            ans++;
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

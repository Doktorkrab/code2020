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

const int MAXN = 1e5 + 6;
const int BLOCK = 322;
const ull MOD = 1e9 + 7;
const ull BASE = 239;

inline ull mul(ull a, ull b) {
    return a * b % MOD;
}

inline ull add(ull a, ull b) {
    return (a + MOD + b) % MOD;
}

int n, m;
pair<int, string> queries[MAXN];
unordered_set<int> need[BLOCK + 1];
unordered_map<int, vector<int>> small[BLOCK + 1];
ull hashes[MAXN];
ull bases[MAXN];
string s;

void precalc() {
    bases[0] = 1;
    for (int i = 0; i < n; i++) {
        hashes[i + 1] = add(mul(hashes[i], BASE), s[i]);
        bases[i + 1] = mul(bases[i], BASE);
    }
}

inline ull get(int l, int r) {
    return add(hashes[r], -mul(hashes[l], bases[r - l]));
}

int solve() {
    if (!(cin >> s >> m))
        return 1;
    n = SZ(s);
    precalc();
    for (int i = 0; i < m; i++) {
        cin >> queries[i].first >> queries[i].second;
        if (SZ(queries[i].second) <= BLOCK) {
            ull h = 0;
            for (char c : queries[i].second)
                h = add(mul(h, BASE), c);

            need[SZ(queries[i].second)].insert(h);
        }
    }
    for (int l = 1; l <= BLOCK; l++) {
        for (int i = 0; i + l <= n; i++)
            if (need[l].count(get(i, i + l)))
                small[l][get(i, i + l)].push_back(i);
    }
    for (int i = 0; i < m; i++) {
        auto[k, t] = queries[i];
        ull h = 0;
        for (char c : t)
            h = add(mul(h, BASE), c);
        if (SZ(t) <= BLOCK) {
            if (SZ(small[SZ(t)][h]) < k) {
                cout << "-1\n";
            } else {
                int best = MAXN;
                auto &x = small[SZ(t)][h];
                for (int j = k - 1; j < SZ(x); j++)
                    best = min(best, x[j] - x[j - k + 1] + SZ(t));
                cout << best << '\n';
            }
            continue;
        }
        vector<int> kek;
        for (int j = 0; j + SZ(t) <= n; j++) {
            if (get(j, j + SZ(t)) != h)
                continue;
            kek.push_back(j);
        }
        if (SZ(kek) < k) {
            cout << "-1\n";
        } else {
            int ans = MAXN;
            for (int j = k - 1; j < SZ(kek); j++)
                ans = min(ans, kek[j] - kek[j - k + 1] + SZ(t));
            cout << ans << '\n';
        }
    }
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

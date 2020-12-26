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

const ull MOD = 1e9 + 7;
const ull BASE = 239;
const int MAXN = 1e4 + 7;
const int MAXK = 10;
int n;
ull hashes[MAXK][MAXN];
ull bases[MAXN];
string have[MAXK];

inline ull get(int l, int r, int index) {
    return (hashes[index][r] + MOD - hashes[index][l] * bases[r - l] % MOD) % MOD;
}

void build_hash(int index) {
    hashes[index][0] = 0;
    bases[0] = 1;
    for (int i = 0; i < SZ(have[index]); i++) {
        hashes[index][i + 1] = (hashes[index][i] * BASE % MOD + have[index][i]) % MOD;
        bases[i + 1] = bases[i] * BASE % MOD;
    }
}

unordered_map<ull, int> have_hashes;

bool check(int len) {
    have_hashes.clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + len <= SZ(have[i]); j++) {
            have_hashes[get(j, j + len, i)] |= (1 << i);
            if (have_hashes[get(j, j + len, i)] == (1 << n) - 1) {
                return true;
            }
        }
    }
    return false;
}

int solve() {
    if (!(cin >> n))
        return 1;
    have_hashes.clear();
    have_hashes.reserve(1e5);
    int l = 0, r = MAXN + 1;
    for (int i = 0; i < n; i++) {
        cin >> have[i];
        build_hash(i);
        r = min(r, SZ(have[i]) + 1);
    }
    while (r - l > 1) {
        int m = l + (r - l) / 2;
//        cerr << m << ' ' << check(m) << '\n';
        if (check(m))
            l = m;
        else
            r = m;
    }
//    cerr << l << ' ' << r << '\n';
//    cerr << check(l) << '\n';
    check(l);
    for (int i = 0; i + l <= SZ(have[n - 1]); i++)
        if (have_hashes[get(i, i + l, n - 1)] == (1 << n) - 1) {
            cout << have[n - 1].substr(i, l) << '\n';
            return 0;
        }
    assert(0);
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

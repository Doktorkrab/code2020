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

int n, k;
set<int> ans;
set<pair<int, int>> was;
vector<int> primes;
const int MOD = 1e9 + 7;

inline bool check(int64_t x) {
    if (x == 1)
        return 0;
    for (int64_t a = 2; a * a <= x; a++)
        if (x % a == 0)
            return 0;
    return 1;
}

void rec(int pos, int have) {
    if (pos > k)
        return;
    if (was.count({pos, have}))
        return;
//    cout << pos << ' ' << have << '\n';

    was.insert({pos, have});
    ans.insert(have);
    for (int i : primes) {
        if (have % i == 0)
            rec(pos + 1, have / i);
//        cout << have * i << ' ' << have << ' ' << i << '\n';
        rec(pos + 1, have * i);
    }
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 2; i <= n; i++)
        if (check(i)) {
//            cout << "\t" << i << '\n';
            primes.push_back(i);
        }
    ll ans1 = 0;
    for (int i = 1; i <= n; i++) {
        ans.clear();
        was.clear();
        rec(0, i);
//        cout << ans.size() << ' ' << i << '\n';
//        for (int x : ans)
//            cout << x << ' ';
//        cout << '\n';
        ans1 = (ans1 + (i * SZ(ans)) % MOD) % MOD;
    }
    cout << ans1 << '\n';
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

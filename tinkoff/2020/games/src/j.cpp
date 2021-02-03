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

int a, b, c;
const int MAXN = 5e3 + 7;
int dp[MAXN];

void calc_dp() {
    for (int i = 1; i < MAXN; i++) {
        unordered_set<int> have;
        for (int j = i / 2 + i % 2; j < i; j++)
            have.insert(dp[j]);
        int mex = 0;
        while (have.count(mex))
            mex++;
        dp[i] = mex;
    }
}

int solve() {
    if (!(cin >> a >> b >> c))
        return 1;
    if ((dp[a] ^ dp[b] ^ dp[c]) == 0) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = a / 2 + a % 2; i < a; i++) {
        if ((dp[i] ^ dp[b] ^ dp[c]) == 0) {
            cout << i << ' ' << b << ' ' << c << '\n';
            return 0;
        }
    }

    for (int i = b / 2 + b % 2; i < b; i++) {
        if ((dp[a] ^ dp[i] ^ dp[c]) == 0) {
            cout << a << ' ' << i << ' ' << c << '\n';
            return 0;
        }
    }

    for (int i = c / 2 + c % 2; i < c; i++) {
        if ((dp[a] ^ dp[b] ^ dp[i]) == 0) {
            cout << a << ' ' << b << ' ' << i << '\n';
            return 0;
        }
    }
    return 0;
}

signed main() {
    calc_dp();
#ifdef LOCAL
    freopen("j.in", "r", stdin);
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

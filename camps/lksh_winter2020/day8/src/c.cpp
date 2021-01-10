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

map<pair<int, int>, int> mem;

ll c(ll n, int k) {
//    ll ans = 1;
//    for (int i = 1; i <= n; i++)
//        ans *= i;
//    ll ans1 = 1;
//    for (int i = 1; i <= n - k; i++)
//        ans1 *= i;
//    ll ans2 = 1;
//    for (int i = 1; i <= k; i++)
//        ans2 *= i;
//    return ans / ans1 / ans2;
    if (k == 0 || n == k)
        return 1;
    if (k > n)
        return 0;
    if (k == 1)
        return n;
    if (k == 2)
        return n * (n - 1) / 2;
    if (k == 3)
        return (n - 2) * (n - 1) * n / 6;
    if (k == 4)
        return (n - 3) * (n - 2) * (n - 1) * n / 24;
    if (k == 5)
        return (n - 4) * (n - 3) * (n - 2) * (n - 1) * n / 120;
    if (k == 6)
        return (n - 5) * (n - 4) * (n - 3) * (n - 2) * (n - 1) * n / 720;
    assert(0);
}

int n;

vector<ll> parse(int l, int r, const string &s) {
//    cout << s.substr(l, r - l) << endl;
    if (r - l == 1) {
        assert(s[l] == 'B');
        return {0, 1, 0, 0, 0, 0, 0};
    }
    char now = s[l];
    if (now == 'P') {
        int comma = l;
        int bal = 0;
        while (s[comma] != ',' || bal != 1) {
            if (s[comma] == '(')
                bal++;
            else if (s[comma] == ')')
                bal--;
            comma++;
        }
        vector<ll> a = parse(l + 2, comma, s);
        vector<ll> b = parse(comma + 1, r - 1, s);
        vector<ll> res(7);
        for (int i = 0; i < 7; i++)
            for (int j = 0; i + j <= 6 && j <= 6; j++)
                res[i + j] += a[i] * b[j];
        return res;
    }
    if (now == 'L') {
        vector<ll> res(7);
        vector<ll> a = parse(l + 2, r - 1, s);
        res[0] = 1;
//        for (int i = 1; i <= 6; i++)
//            res[i] = a[i];
        a[0] = 0;
        for (int i = 1; i <= 6; i++) {
            for (int j = 0; j <= i; j++)
                res[i] += res[j] * a[i - j];
        }
        return res;
    }
    if (now == 'S') {
        vector<vector<ll>> dp(7, vector<ll>(7));
        vector<ll> a = parse(l + 2, r - 1, s);
        for (int i = 0; i <= 6; i++)
            dp[0][i] = 1;
        a[0] = 0;
        for (int i = 1; i <= 6; i++)
            for (int x = 1; x <= 6; x++)
                for (int took = 0; took * x <= i; took++) {
//                    cout << i << ' ' << x << ' ' << took << ' ' << c(a[x] + took - 1, took) * dp[i - took * x][x - 1]
//                         << endl;
                    dp[i][x] += c(a[x] + took - 1, took) * dp[i - took * x][x - 1];
                }
        vector<ll> res(7);
        for (int i = 0; i <= 6; i++)
            res[i] = dp[i][i];
        return res;
    }
    assert(0);
}

int solve() {
    string s;
    if (!(cin >> s))
        return 1;
    auto ans = parse(0, SZ(s), s);
    for (ll x : ans)
        cout << x << ' ';
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
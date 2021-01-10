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

int n;
string s;
const int MAXN = 1e5 + 7;
ll prefix_j[MAXN];
ll prefix_i[MAXN];

int solve() {
    if (!(cin >> n >> s))
        return 1;
    for (int i = 0; i < n; i++)
        prefix_j[i + 1] = prefix_j[i] + (s[i] == 'J');
    for (int i = 0; i < n; i++)
        prefix_i[i + 1] = prefix_i[i] + (s[i] == 'I');
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'O')
            ans += prefix_j[i] * (prefix_i[n] - prefix_i[i]);
    }
    ll ans_j = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'O')
            ans_j += prefix_i[n] - prefix_i[i];
    }
    ll ans_o = 0;
    for (int i = 0; i < n; i++)
        ans_o = max(ans_o, prefix_j[i] * (prefix_i[n] - prefix_i[i]));
    ll ans_i = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == 'O')
            ans_i += prefix_j[i];
    cout << ans + max(max(ans_j, ans_o), ans_i) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

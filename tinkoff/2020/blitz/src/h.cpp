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
const int MAXN = 5e5 + 7;
int balance[MAXN];
bool is_ok[MAXN];

int solve() {
    if (!(cin >> s))
        return 1;
    n = SZ(s);
    int bal = 0;
    is_ok[0] = true;
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '(')
            bal++;
        else
            bal--;
        balance[i] = bal;
        is_ok[i + 1] = (is_ok[i] & (bal >= 0));
    }
    int mn = bal;
    int ans = 0;
//    for (int i = 0; i < n; i++)
//        cout << is_ok[i] << " \n"[i + 1 == n];
    for (int i = n - 1; i >= 0; i--) {
        int df = 0;
        if (s[i] == '(')
            df = 1;
        else
            df = -1;
        if (bal - df == 0 && mn - df >= 0 && is_ok[i])
            ans++;
        mn = min(balance[i], mn);
    }
    cout << ans << '\n';

    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
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

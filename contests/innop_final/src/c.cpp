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

int n, d;
string s;

vector<int> find_ans(const string &ss) {
    int r = 0, p = 0, s = 0;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        if (ss[i] == 'r')
            ans[i] = (p == 0 || (p && s)), r++;
        else if (ss[i] == 'p')
            ans[i] = (!s || (s && r)), p++;
        else if (ss[i] == 's')
            ans[i] = (!r || (r && p)), s++;
    }
    return ans;
}

int solve() {
    if (!(cin >> d >> s))
        return 1;
    n = SZ(s);
    auto ans = find_ans(s);
    reverse(ALL(s));
    auto ans1 = find_ans(s);
    reverse(ALL(ans1));
    for (int i = 0; i < n; i++)
        if (ans[i] && ans1[i])
            cout << "1";
        else
            cout << "0";
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
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

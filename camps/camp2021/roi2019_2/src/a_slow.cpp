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
string ans1;

int check(int x) {
    int was = 0;
    int cnt = 0;
    int ans = 0;
    ans1.clear();
    string zeroes;
    for (int i = 0; i < x; i++)
        zeroes += '0';

    for (int i = 0; i < n; i++) {
        if (s[i] == '0')
            was++;
        if (s[i] == '1') {
            if (was >= x)
                was = 0, cnt++, ans += x + 1, ans1.append(zeroes).append("1");
        }
    }
    if (was < x)
        cnt--, ans--, ans1.pop_back();
    else
        ans += x, ans1.append(zeroes);
    return (cnt > 0 ? ans : -1);

}

int solve() {
    if (!(cin >> n >> s))
        return 1;
    int best = -1, where = -1;
    for (int i = n; i >= 0; i--)
        if (check(i) > best) {
            best = check(i);
            where = i;
        }
    check(where);
    cout << best << '\n';
    cout << ans1 << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
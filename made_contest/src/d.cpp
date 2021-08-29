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
const int MAXN = 1e6;
const int KEK = -1e9 - 228;

int balances[MAXN];
int min_balance[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    multiset<pair<int, int>> have1, have2, have3;

    for (int i = 0; i < n; i++){
        string now;
        cin >> now;
        balances[i] = min_balance[i] = 0;
        for (char c : now){
            if (c == '(')
                balances[i]++;
            else
                balances[i]--;
            min_balance[i] = min(min_balance[i], balances[i]);
        }
        cout << min_balance[i] << ' ' << balances[i] << '\n';
        if (balances[i] >= 0)
            have1.emplace(min_balance[i], balances[i]);
        else {
            have2.emplace(min_balance[i], -balances[i]);
            have3.emplace(-balances[i], min_balance[i]);
        }
    }
    int cur = 0;
    while (SZ(have1)){
        assert(cur >= 0);
        auto [mn, res] = (*have1.rbegin());
        have1.erase(prev(have1.end()));
        if (cur + mn < 0){
            cout << "No\n";
            return 0;
        }
        cur += res;
    }
    while (SZ(have2)){
        if (cur + have2.begin()->first < 0){
            cout << "No\n";
            return 0;
        }
        auto [res, mn] = (*have3.begin());
        have3.erase(have3.begin());
        have2.erase(have2.find({mn, res}));
        while (SZ(have2) && cur - res + have2.begin()->first < 0){
            auto [mn1, res1] = (*have2.rbegin());
            have2.erase(prev(have2.end()));
            have3.erase(have3.find({res1, mn1}));
            have3.emplace(res, mn);
            have2.emplace(mn, res);
            if (cur + mn1 < 0){
                cout << "No\n";
                return 0;
            }
            cout << '\t' << mn1 << ' ' << res1 << '\n';
            cur += -res1;
            if (SZ(have3)) {
                auto tmp = (*have3.begin());
                res = tmp.first, mn = tmp.second;
                have3.erase(have3.begin());
                have2.erase(have2.find({tmp.second, tmp.first}));
            }
            else {
                mn = KEK;
            }
        }
        if (mn == KEK)
            break;
        cout << '\t' << mn << ' ' << res << '\n';
        if (cur + mn < 0){
            cout << "No\n";
            return 0;
        }
        cur += -res;
    }
    if (cur != 0)
        cout << "No\n";
    else
        cout << "Yes\n";
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

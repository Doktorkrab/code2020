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
const int MAXN = 2505;
string s;

int solve() {
    if (!(cin >> s))
        return 1;
    n = SZ(s);
    ll ans = 0;
    vector<pair<ll, vector<int>>> have(1);
    for (int i = 0; i < n; i++)
        have[0].second.push_back(i);
    for (int l = 1; l <= n; l++){
        vector<pair<ll, vector<int>>> nxt;
        int minus = 0;
        for (auto& [less, poses] : have){
            less -= minus;
//            cout << less << "\n\t";
//            for (int x : poses)
//                cout << x << ' ';
//            cout << '\n';
            vector<vector<int>> nxxt(26);
            for (int pos : poses) {
                if (pos + l > n){
                    minus++;
                    continue;
                }
                nxxt[s[pos + l - 1] - 'a'].push_back(pos);
            }
            for (int i = 0; i < 26; i++) {
                if (nxxt[i].empty())
                    continue;
//                cout << "!" << SZ(nxxt[i]) * less << ' ' << less << ' ' << SZ(nxxt[i]) << ' ' << (char)('a' + i) << '\n';
                ans += SZ(nxxt[i]) * less;
                nxt.emplace_back(less, nxxt[i]);
                less += SZ(nxxt[i]);
            }
        }
        swap(have, nxt);
    }
    cout << ans << '\n';
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

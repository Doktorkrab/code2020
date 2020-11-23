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

const int MAXN = 5e5 + 7;
int n, q;
vector<pair<int, int>> have[MAXN];
vector<int> compress;
vector<pair<int, int>> enters[MAXN];
int maxes[MAXN];
ll ans[MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    compress.reserve(MAXN);
    for (int i = 0; i < n; i++){
        int m;
        cin >> m;
        for (int j = 0; j < m; j++){
            int a, b;
            cin >> a >> b;
            compress.push_back(a);
            have[i].emplace_back(a, b);
        }
    }
    sort(ALL(compress));
    compress.resize(unique(ALL(compress)) - compress.begin());
    for (int i = 0; i < n; i++){
        int pnt = 0;
        for (auto& [a, b] : have[i]) {
            a = (int) (lower_bound(ALL(compress), a) - compress.begin());
            enters[a].emplace_back(i, pnt++);
        }
    }
    ll was = 0;
    for (int i = 0; i < SZ(compress); i++){
        for (auto [a, b] : enters[i]){
            int cur = have[a][b].second;
            if (cur > maxes[a]){
                was -= maxes[a];
                was += cur;
                maxes[a] = cur;
            }
        }
        ans[i] = was;
    }
//    for (int i = 0; i < SZ(compress); i++)
//        cout << ans[i] << " \n"[i + 1 == SZ(compress)];
//    for (int i :compress)
//        cout << i << ' ';
//    cout << '\n';
    cin >> q;
    for (int i = 0; i < q; i++){
        int x;
        cin >> x;
        int pos = (int)(lower_bound(ans, ans + SZ(compress), x) - ans);
        if (pos == SZ(compress))
            cout << "-1";
        else
            cout << compress[pos];
        if (i + 1 == q)
            cout << '\n';
        else
            cout << ' ';
    }
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

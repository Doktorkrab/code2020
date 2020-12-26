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
 
int n, m;
const int MAXN = 1e5 + 7;
int arr[MAXN];
vector<int> have[MAXN];
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++)
        cin >> arr[i];
    int ban = arr[0];
    for (int i = 1; i < m; i++){
        if (arr[i] != ban)
            have[arr[i]].push_back(arr[i - 1]);
    }
    for (int i = 1; i <= n; i++){
        sort(ALL(have[i]));
        have[i].resize(unique(ALL(have[i])) - have[i].begin());
    }
    int mx = -1;
    for (int i = 1; i <= n; i++){
        if (i == ban)
            continue;
        if (mx == -1 || SZ(have[mx]) < SZ(have[i]))
            mx = i;
    }
    vector<pair<int, int>> ans;
    for (int i = 1; i <= n; i++){
        if (i == ban || i == mx)
            continue;
        for (int j : have[i])
            ans.emplace_back(i, j);
    }
    cout << SZ(ans) << '\n';
    for (auto [a, b] : ans)
        cout << a << ' ' << b << '\n';
    return 0;
}
 
signed main() {

    freopen("log.in", "r", stdin);
    freopen("log.out", "w", stdout);
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

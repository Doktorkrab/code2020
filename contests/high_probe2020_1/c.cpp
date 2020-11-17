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
 
int n, m, k;
const int MAXN = 505;
int fld[MAXN][MAXN];
int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        fld[x][y] = 1;
    }
    if (n == 1){
        vector<int> ans;
        for (int i = 0; i < m; i++)
            if (!fld[0][i])
                ans.push_back(i);
        cout << ans.size() << '\n';
        for (int i : ans)
            cout << "1 " << i + 1 << '\n';
        return 0;
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

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
 
const int MAXN = 2e3 + 7;
int n, m;
int ul[MAXN][MAXN], ur[MAXN][MAXN], dl[MAXN][MAXN], dr[MAXN][MAXN];
string arr[MAXN];
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            ul[i][j] = ur[i][j] = dl[i][j] = dr[i][j] = 0;
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            int lft = 0;
            if (j && arr[i][j - 1] == arr[i][j])
                lft = ul[i][j - 1];
            int up = 0;
            if (i && arr[i - 1][j] == arr[i][j])
                up = ul[i - 1][j];
            ul[i][j] = min(up, lft) + 1;
        }
    for (int i = 0; i < n; i++)
        for (int j = m - 1; j >= 0; j--){
            int rgt = 0;
            if (j + 1 < m && arr[i][j + 1] == arr[i][j])
                rgt = ur[i][j + 1];
            int up = 0;
            if (i && arr[i - 1][j] == arr[i][j])
                up = ur[i - 1][j];
            ur[i][j] = min(up, rgt) + 1; 
        }
    for (int i = n - 1; i >= 0; i--){
        for (int j = 0; j < m; j++){
            int lft = 0;
            if (j && arr[i][j - 1] == arr[i][j])
                lft = dl[i][j - 1];
            int down = 0;
            if (i + 1 < n && arr[i + 1][j] == arr[i][j])
                down = dl[i + 1][j];
            dl[i][j] = min(lft, down) + 1;
        }
    }

    for (int i = n - 1; i >= 0; i--)
        for (int j = m - 1; j >= 0; j--){
            int rgt = 0;
            if (j + 1 < m && arr[i][j + 1] == arr[i][j])
                rgt = dr[i][j + 1];
            int down = 0;
            if (i + 1 < n && arr[i + 1][j] == arr[i][j])
                down = dr[i + 1][j];
            dr[i][j] = min(down, rgt) + 1;
        }
    ll ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans += min(min(ul[i][j], ur[i][j]), min(dl[i][j], dr[i][j]));
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
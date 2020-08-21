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
const int MAXN = 305;
vector<pair<int, int>> shift = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int fld[MAXN][MAXN];

int find_nei(int nx, int ny){
    int ans = 0;
    for (auto [sx, sy] : shift){
        int x = nx + sx, y = ny + sy;
        ans += (0 <= x && x < n && 0 <= y && y < m);
    }
    return ans;
}
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> fld[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            int now = find_nei(i, j);
            if (now < fld[i][j]){
                cout << "NO\n";
                return 0;
            }
            fld[i][j] = now;
        }
    cout << "YES\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cout << fld[i][j] << " \n"[j + 1 == m];
    return 0;
}
 
signed main() {
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
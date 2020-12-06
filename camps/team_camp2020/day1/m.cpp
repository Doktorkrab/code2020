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
const int MAXN = 205;
pair<int, int> shift[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int fld[MAXN][MAXN];
vector<pair<int, int>> comps[MAXN * MAXN];
bool used[MAXN][MAXN];
int zeroes = 0;
void dfs(int x, int y){
    if (fld[x][y] == 0) {
        zeroes++;
        return;
    }
    used[x][y] =  true;
    comps[fld[x][y]].emplace_back(x, y);
    for (auto [sx, sy] : shift){
        int nx = x + sx, ny = y + sy;
        if (0 <= nx && nx < n && 0 <= ny && ny < m && fld[x][y] == fld[nx][ny] && !used[nx][ny])
            dfs(nx, ny);
    }
}
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> fld[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (fld[i][j] == 0){
                zeroes++;
                continue;
            }
            if (!used[i][j] && fld[i][j] != 0) {
//                cout << i << ' ' << j << '\n';
                if (SZ(comps[fld[i][j]])){
                    cout << "NO\n";
                    return 0;
                }
                dfs(i, j);
            }
        }
    if (zeroes > 2){
        cout << "NO\n";
        return 0;
    }
    for (int i = 1; i <= (n * m / 3); i++) {
        if (SZ(comps[i]) != 0 && SZ(comps[i]) != 3) {
            cout << "NO\n";
            return 0;
        }
        if (SZ(comps[i]) == 0)
            continue;
    }
    cout << "YES\n";
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

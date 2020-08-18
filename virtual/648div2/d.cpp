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
const int MAXN = 55;
const int INF = 1e9 + 7;
bool wall[MAXN][MAXN];
bool good[MAXN][MAXN];
bool bad[MAXN][MAXN];
int dist[MAXN][MAXN];
bool used[MAXN][MAXN];
vector<pair<int, int>> shift = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
inline bool check(int x, int y){
    if (!(0 <= x && x < n && 0 <= y && y < m))
        return false;
    if (wall[x][y] || bad[x][y])
        return false;
    for (auto& [_x, _y] : shift){
        int nx = x + _x, ny = y + _y;
        if (0 <= nx &&nx < n && 0 <= ny && ny < m && bad[nx][ny])
            return false;
    }
    return true;
}



int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            wall[i][j] = good[i][j] = bad[i][j] = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            char x;
            cin >> x;
            if (x == '#')
                wall[i][j] = 1;
            if (x == 'G')
                good[i][j] = 1;
            if (x == 'B')
                bad[i][j] = 1;
            dist[i][j] = INF;
            used[i][j] = 0;
        }
    }
    deque<pair<int, int>> q;
    if (check(n - 1, m - 1)){
        dist[n - 1][m - 1] = 0;
        q.push_back({n - 1, m - 1});
    }
    while (!q.empty()){
        auto [x, y] = q.front();
        q.pop_front();
        if (used[x][y])
            continue;
        used[x][y] = 1;
        for (auto& [_x, _y] : shift){
            int nx = x + _x, ny = y + _y;
            if (check(nx, ny) && dist[nx][ny] > dist[x][y] + 1){
                dist[nx][ny] = dist[x][y] + 1;
                q.push_back({nx, ny});
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (good[i][j] && dist[i][j] >= INF){
                cout << "No\n";
                return 0;
            }
        }
    }
    cout << "Yes\n";
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
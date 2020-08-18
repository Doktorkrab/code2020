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
 
const int MAXFLD = 55;
const int MAXN = 17;
const int INF = 105;

int n, m;

char fld[MAXFLD][MAXFLD];
int comp[MAXFLD][MAXFLD];
int dp[MAXN][(1 << MAXN)];
int dist[MAXN][MAXN];
int dist1[MAXFLD][MAXFLD];
int used[MAXFLD][MAXFLD];
vector<pair<int, int>> have[MAXN];
pair<int, int> shift[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void bfs(int s_x, int s_y, int num){
    deque<pair<int, int>> q = {{s_x, s_y}};
    comp[s_x][s_y] = num;
    have[num].push_back({s_x, s_y});
    while (q.size()){
        pair<int, int> kek = q.front();
        int nowx = kek.first, nowy = kek.second;
        if (used[nowx][nowy])
            continue;
        used[nowx][nowy] = true;
        q.pop_front();
        for (auto lol : shift){
            int x = lol.first + nowx, y = lol.second + nowy;
            if (0 <= x && x < n && 0 <= y && y < m && fld[x][y] == 'X' && comp[x][y] == -1){
                q.push_back({x, y});
                comp[x][y] = num;
                have[num].push_back({x, y});
            }
        }
    }
}
void find_dist(int from){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            used[i][j] = false;
            dist1[i][j] = INF;
        }
    deque<pair<int, int>> q;
    for (pair<int, int>& kek: have[from]){
        q.push_back(kek);
        dist1[kek.first][kek.second] = 0;
    }
    while (SZ(q)){
        pair<int, int> kek = q.front();
        int x = kek.first;
        int y = kek.second;
        q.pop_front();
        if (used[x][y])
            continue;
        used[x][y] = true;
        for (auto lol : shift){
            int sx = x + lol.first, sy = y + lol.second;
            if (!(0 <= sx && sx < n && 0 <= sy && sy < m) || fld[sx][sy] != 'S')
                continue;
            if (dist1[sx][sy] > dist1[x][y] + 1){
                dist1[sx][sy] = dist1[x][y] + 1;
                // cout << x << ", " << y << "(" << dist1[x][y] << ")" << "->" << sx << ", " << sy << "(" << dist1[sx][sy] << ")\n";
                q.push_back({sx, sy});
            }
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            if (fld[i][j] != 'X')
                continue;
            for (auto lol : shift){
                int x = i + lol.first, y = j + lol.second;
                if (0 <= x && x < n && 0 <= y && y < m && fld[x][y] == 'S'){
                    dist1[i][j] = min(dist1[i][j], dist1[x][y]);
                }
            }
        }
    // cout << from << ":\n";
    // for (int i = 0; i < n; i++)
    //     for (int j = 0; j < m; j++)
    //         if (dist1[i][j] < INF)
    //             cout << dist1[i][j] << " \n"[j + 1 == m];
    //         else
    //             cout << "I" << " \n"[j + 1 == m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (comp[i][j] != -1){
                // cout << dist[from][comp[i][j]] << ' ' << dist1[i][j] << ' ' << comp[i][j] << '\n';
                dist[from][comp[i][j]] = min(dist[from][comp[i][j]], dist1[i][j]);
            }
}
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            cin >> fld[i][j];
            comp[i][j] = -1;
            used[i][j] = 0;
        }
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            dist[i][j] = INF;
    for (int i = 0; i < MAXN; i++)
        have[i].clear();
    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            if (comp[i][j] == -1 && fld[i][j] == 'X'){
                bfs(i, j, cnt++);
            }
        }
    // for (int i = 0; i < n; i++)
    //     for (int j = 0; j < m; j++){
    //         cout << comp[i][j] << " \n"[j + 1 == m];
    // }
    for (int i = 0; i < cnt; i++)
        find_dist(i);

    // for (int i = 0; i < cnt; i++)
    //     for (int j = 0; j < cnt; j++)
    //         if (dist[i][j] < INF)
    //             cout << dist[i][j] << " \n"[j + 1 == cnt];
    //         else
    //             cout << "INF" << " \n"[j + 1 == cnt];

    for (int i = 0; i < (1 << cnt); i++)
        for (int j = 0; j < cnt; j++)
            dp[j][i] = INF;
    for (int i = 0; i < cnt; i++)
        dp[i][1 << i] = 0;
    for (int mask = 1; mask < (1 << cnt); mask++){
        for (int i = 0; i < cnt; i++){
            if (!((mask >> i) & 1))
                continue;
            for (int j = 0; j < cnt; j++){
                // cerr << mask << ' ' << i << ' ' << dp[i][mask] + dist[i][mask] << '\n';
                dp[j][mask | (1 << j)] = min(dp[j][mask | (1 << j)], dp[i][mask] + dist[i][j]);
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < cnt; i++)
        ans = min(ans, dp[i][(1 << cnt) - 1]);
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
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
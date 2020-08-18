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

const int MAXN = 5e2 + 7;
const int INF = 1e9 + 7; 
struct triple{
    int a, b, c;
};
int n, m;
int xs, ys, xt, yt;
vector<triple> g[2][MAXN][MAXN];
int d[2][MAXN][MAXN];
bool used[2][MAXN][MAXN];

 
int solve() {
    if (!(cin >> m >> n))
        return 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k < 2; k++){
                g[k][i][j].clear();
                d[k][i][j] = INF;
                used[k][i][j] = 0;
            }
    cin >> ys >> xs >> yt >> xt;
    d[0][xs][ys] = d[1][xs][ys] = 0;
    for (int i = 0; i < 2 * n + 1; i++){
        if (i % 2 == 0){
            for (int j = 0; j < m; j++){
                char x;
                cin >> x;
                if (x == 'n')
                    continue;
                int from = 0;
                if (x == 'w')
                    from = 1;
                g[from][i / 2][j].push_back({from ^ 1, i / 2, j + 1});
                g[from][i / 2][j + 1].push_back({from ^ 1, i / 2, j});
                // cout << from << ", " << i/2 << ", " << j << "<=>" << (from ^ 1) << ", " << i/ 2 << ", " << j + 1 << '\n';
            }
            continue;
        }

        for (int j = 0; j < 2 * m + 1; j++){
            char x;
            cin >> x;
            if (x == 'n')
                continue;
            int from = 0;
            if (x == 'w')
                from = 1;
            g[from][i / 2][(j + 1) / 2].push_back({from ^ 1, i / 2 + 1, (j + 1) / 2 - (j % 2)});
            g[from][i / 2 + 1][(j + 1) / 2 - (j % 2)].push_back({from ^ 1, i / 2, (j + 1) / 2});
            // cout << from << ", " << i/2 << ", " << (j + 1) / 2 << "<=>" << (from ^ 1) << ", " << i/ 2 + 1 << ", " << (j + 1) / 2 - (j % 2) << "!\n";

        }
    }

    deque<triple> q = {{0, xs, ys}, {1, xs, ys}};
    while (SZ(q)){
        auto [k, i, j] = q.front();
        q.pop_front();
        if (used[k][i][j])
            continue;
        used[k][i][j] = true;
        // cout << k << ' ' << i << ' ' << j << ' ' << d[k][i][j] << '\n';
        for (auto [k1, i1, j1] : g[k][i][j]){
                // cout << "(" << k << ", " << i << ", " << j << ") <=> (" << k1 << ", " << i1 << ", " << j1 << ")\n";
                // cout << d[k1][i1][j1] << ' ' << d[k][i][j] + 1 << '\n';
            if (d[k1][i1][j1] > d[k][i][j] + 1){
                d[k1][i1][j1] = d[k][i][j] + 1;
                q.push_back({k1, i1, j1});
            }
        }
    }
    cout << min(d[0][xt][yt], d[1][xt][yt]) << '\n';
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
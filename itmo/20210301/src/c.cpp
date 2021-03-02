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
const int MAXN = 1005;
enum {
    LOSE, DRAW, WIN
};

struct State {
    short turn, v, u;
};

short state[27][MAXN][MAXN];
short degree[27][MAXN][MAXN];
vector<short> g[MAXN][26];
vector<short> g_rev[MAXN][26];


int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 27; j++) {
            g[i][j].clear();
            g_rev[i][j].clear();
        }
    }
    for (int i = 0; i < m; i++) {
        int v, u;
        char c;
        cin >> v >> u >> c;
        --v, --u;
        c -= 'a';
        g[v][c].push_back(u);
        g_rev[u][c].push_back(v);
    }
    for (int i = 0; i < 27; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                state[i][j][k] = DRAW;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 27; k++) {
                for (int x : g_rev[j][k])
                    degree[k][i][x]++;
                for (int x : g_rev[i][k])
                    degree[26][x][j]++;
            }
        }
    }
    deque<State> q;
    for (short i = 0; i < n; i++)
        for (short j = 0; j < n; j++) {
            for (short k = 0; k < 27; k++)
                if (degree[k][i][j] == 0) {
                    state[k][i][j] = LOSE;
                    q.push_back({k, i, j});
                }
        }
    while (SZ(q)) {
        auto[t, v, u] = q.front();
        q.pop_front();
        if (t == 26) {
            for (short i = 0; i < 26; i++) {
                for (short w : g_rev[u][i]) {
                    if (state[t][v][u] == LOSE && state[i][v][w] == DRAW) {
                        state[i][v][w] = WIN;
                        q.push_back({i, v, w});
                    } else if (WIN == state[t][v][u] && state[i][v][w] == DRAW) {
                        degree[i][v][w]--;
                        if (degree[i][v][w] == 0) {
                            state[i][v][w] = LOSE;
                            q.push_back({i, v, w});
                        }
                    }
                }
            }
        } else {
            for (short w : g_rev[v][t]) {
                if (state[t][v][u] == LOSE && state[26][w][u] == DRAW) {
                    state[26][w][u] = WIN;
                    q.push_back({26, w, u});
                } else if (WIN == state[t][v][u] && state[26][w][u] == DRAW) {
                    degree[26][w][u]--;
                    if (degree[26][w][u] == 0) {
                        state[26][w][u] = LOSE;
                        q.push_back({26, w, u});
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (state[26][i][j] == WIN)
                ans++;
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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

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

int n;
const int MAXN = 1e3 + 7;
const int MAXC = 1e6 + MAXN + 7;
const int INF = 1e9;
vector<int> g[2 * MAXN], g_t[2 * MAXN];
char letter[MAXC];
int ee[MAXN];
int dist1[MAXC];
int nxt[MAXC];
int prv[MAXC];
bool used[MAXC];
int m;
int pnt;

void bfs1() {
    fill(dist1, dist1 + pnt, INF);
    fill(used, used + pnt, false);
    dist1[ee[n - 1]] = 1;
    deque<int> q = {ee[n - 1]};
    while (SZ(q)) {
        int v = q.front();
        q.pop_front();
        if (used[v])
            continue;
        used[v] = true;
//        cout << v << ' ' << dist1[v] << '\n';
        if (v < 2 * n) {
            for (int u : g_t[v]) {
                if (dist1[u] > dist1[v] + 1) {
                    dist1[u] = dist1[v] + 1;
                    q.push_back(u);
                }
            }
        } else {
            if (prv[v] != -1 && dist1[prv[v]] > dist1[v] + 1) {
                dist1[prv[v]] = dist1[v] + 1;
                q.push_back(prv[v]);
            }
        }
    }
}


int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < 2 * n; i++)
        g[i].clear(), g_t[i].clear();
    for (int i = 0; i < MAXC; i++)
        nxt[i] = prv[i] = -1;
    pnt = 2 * n;
    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;
        letter[2 * i] = t[0];
        ee[i] = 2 * i;
        for (int j = 1; j + 1 < SZ(t); j++) {
            if (ee[i] < 2 * n) {
                g[ee[i]].push_back(pnt);
            } else {
                nxt[ee[i]] = pnt;
            }
            prv[pnt] = ee[i];
            letter[pnt] = t[j];
            ee[i] = pnt++;
        }
        if (SZ(t) >= 2) {
            if (ee[i] < 2 * n) {
                g[ee[i]].push_back(2 * i + 1);
            } else {
                nxt[ee[i]] = 2 * i + 1;
            }
            g_t[2 * i + 1].push_back(ee[i]);
            ee[i] = 2 * i + 1;
            letter[2 * i + 1] = t.back();
        }
    }
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[ee[v]].push_back(2 * u);
        g[ee[u]].push_back(2 * v);
        g_t[2 * u].push_back(ee[v]);
        g_t[2 * v].push_back(ee[u]);
    }
    bfs1();
    cout << letter[0];
    vector<int> vars = {0};
    fill(used, used + pnt, false);
    used[0] = true;
    int cnt = 1;
//    return 1;
    while (cnt < dist1[0]) {
        char best = TMAX(char);
//        cout << best << '\n';
        for (int x : vars) {
            if (x < 2 * n) {
                for (int u : g[x])
                    if (cnt + dist1[u] == dist1[0])
                        best = min(best, letter[u]);
            } else {
                if (nxt[x] != -1 && cnt + dist1[nxt[x]] == dist1[0])
                    best = min(best, letter[nxt[x]]);
            }
        }
//        cout << best << '\n';
        vector<int> nxt1;
        for (int x : vars) {
            if (x < 2 * n) {
                for (int u : g[x])
                    if (cnt + dist1[u] == dist1[0] && letter[u] == best && !used[u])
                        nxt1.push_back(u), used[u] = true;
            } else {
                if (nxt[x] != -1 && cnt + dist1[nxt[x]] == dist1[0] && letter[nxt[x]] == best && !used[nxt[x]])
                    nxt1.push_back(nxt[x]), used[nxt[x]] = true;
            }
        }
        cout << best;
        swap(nxt1, vars);
        vars.shrink_to_fit();
        cnt++;
    }
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

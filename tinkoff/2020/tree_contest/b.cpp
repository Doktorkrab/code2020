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

enum {
    OPEN, CLOSE
};
struct Event {
    int index, type, h;
};

int n, m;
const int MAXN = 3e5 + 7;
vector<int> g[MAXN];
int euler[MAXN];
int l[MAXN], r[MAXN];
int hist[MAXN];
int d[MAXN];
int pnt = 0;
int ans[MAXN];
vector<Event> events[MAXN];

void dfs(int v, int p = -1, int dd = 0) {
    euler[pnt] = v;
    l[v] = pnt++;
    d[v] = dd;
    for (int u : g[v])
        if (u != p)
            dfs(u, v, dd + 1);
    r[v] = pnt;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        --p;
        g[i].push_back(p);
        g[p].push_back(i);
    }
    dfs(0);
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a;
        events[l[a]].push_back({i, OPEN, b + d[a]});
        events[r[a]].push_back({i, CLOSE, b + d[a]});
    }
    for (int i = 0; i <= pnt; i++) {
        for (auto[index, type, h] : events[i])
            if (type == OPEN)
                ans[index] -= hist[h];
            else
                ans[index] += hist[h];
        if (i < pnt)
            hist[d[euler[i]]]++;
    }
    for (int i = 0; i < m; i++)
        cout << ans[i] << '\n';
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

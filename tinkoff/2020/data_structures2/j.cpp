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
const int OPEN = 1, CLOSE = -1;
struct Event {
    int type = 0;
    int x = -1;
};

const int MAXN = 2e5 + 7;
Event versions[MAXN];
vector<int> g[MAXN];
int ans[MAXN];
deque<int> have;

void dfs(int v) {
    const auto &ev = versions[v];
    if (ev.type == OPEN)
        have.push_back(ev.x);
    if (ev.type == CLOSE) {
        ans[ev.x] = have.front();
        have.pop_front();
    }
//    cout << v << ": ";
//    for (int i : have)
//        cout << i << ' ';
//    cout << '\n';
    for (int u : g[v])
        dfs(u);
    if (ev.type == OPEN)
        have.pop_back();
    if (ev.type == CLOSE)
        have.push_front(ans[ev.x]);
}

int solve() {
    if (!(cin >> n))
        return 1;
    int pnt = 0;
    fill(ans, ans + n, -1);
    for (int i = 0; i < n; i++) {
        int type, t;
        cin >> type >> t;
        g[t].push_back(i + 1);
        if (type == OPEN) {
            int x;
            cin >> x;
            versions[i + 1] = {OPEN, x};
        }
        if (type == CLOSE)
            versions[i + 1] = {CLOSE, pnt++};
    }
    dfs(0);
    for (int i = 0; i < pnt; i++)
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

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
enum Game {
    Lose, Draw, Win
};
int n, m;
const int MAXN = 3e5 + 7;
vector<int> g_t[MAXN];
int in[MAXN];
int state[MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        g_t[i].clear();
    fill(in, in + n, 0);
    fill(state, state + n, Game::Draw);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        g_t[u - 1].push_back(v - 1);
        in[v - 1]++;
    }
    deque<int> q;
    for (int i = 0; i < n; i++)
        if (in[i] == 0) {
            state[i] = Game::Lose;
            q.push_back(i);
        }
    while (SZ(q)) {
        int v = q.front();
        q.pop_front();
        if (state[v] == Game::Lose) {
            for (int u : g_t[v]) {
                if (state[u] != Game::Draw)
                    continue;
                state[u] = Game::Win;
                q.push_back(u);
            }
        } else {
            for (int u : g_t[v]) {
                if (state[u] != Game::Draw)
                    continue;
                if (--in[u] == 0) {
                    state[u] = Game::Lose;
                    q.push_back(u);
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
        if (state[i] == Game::Win)
            cout << "FIRST\n";
        else if (state[i] == Game::Draw)
            cout << "DRAW\n";
        else
            cout << "SECOND\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("k.in", "r", stdin);
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

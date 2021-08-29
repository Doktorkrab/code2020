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

int n, l, b, k;

const int MAXN = 2e3 + 7;
const int WIN = 1, LOSE = -1, DRAW = 0;
int val[2][MAXN][MAXN];
int deg[2][MAXN][MAXN];
vector<pair<int, int>> g[2][MAXN][MAXN];

int solve() {
    if (!(cin >> n >> l >> b >> k))
        return 1;
    for (int turn = 0; turn < 2; turn++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++){
                deg[turn][i][j] = 0;
                val[turn][i][j] = DRAW;
                g[turn][i][j].clear();
            }
    }
    deque<pair<int, pair<int, int>>> q;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j && i != 0)
                continue;
            if (j == n - 1){
                val[1][i][j] = WIN;
                val[0][i][j] = LOSE;
                q.emplace_back(0, make_pair(i, j));
                q.emplace_back(1, make_pair(i, j));
                continue;
            }
            if (i == n - 1){
                val[0][i][j] = WIN;
                val[1][i][j] = LOSE;
                q.emplace_back(0, make_pair(i, j));
                q.emplace_back(1, make_pair(i, j));
                continue;
            }
            for (int x = 1; x <= l && x + i < n; x++){
                int nxt = i + x;
                int nxt1 = j;
                if (nxt == j)
                    nxt1 = max(0, j - k);
                deg[0][i][j]++;
                g[1][nxt][nxt1].emplace_back(i, j);
            }
            for (int x = 1; x <= b && j + x < n; x++){
                int nxt = i;
                int nxt1 = j + x;
                if (nxt1 == i)
                    nxt = max(0, i - k);
                deg[1][i][j]++;
                g[0][nxt][nxt1].emplace_back(i, j);
            }
        }
    }
//    for (int i = 0; i < 2; i++){
//        for (int j = 0; j < n; j++)
//            for (int k = 0; k < n; k++){
//                cout << "turn: " << i << ' ' << j + 1 << ' ' << k + 1 << ": ";
//                for (auto [a, b] : g[i][j][k])
//                    cout << "(" << a + 1 << ", " << b + 1 << ") ";
//                cout << '\n';
//            }
//    }
    while (SZ(q)){
        auto [turn, pos] = q.front();
        q.pop_front();
        auto [x, y] = pos;
        for (auto [ax, ay] : g[turn][x][y]){
            if (val[!turn][ax][ay] != DRAW)
                continue;
            if (val[turn][x][y] == LOSE){
                val[!turn][ax][ay] = WIN;
                q.emplace_back(!turn, make_pair(ax, ay));
            }
            else {
                if (--deg[!turn][ax][ay] == 0){
                    val[!turn][ax][ay] = LOSE;
                    q.emplace_back(!turn, make_pair(ax, ay));
                }
            }
        }
    }
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < n; j++)
//            for (int k = 0; k < n; k++) {
//                cout << val[i][j][k] << " \n"[k + 1 == n];
//            }
//        cout << '\n';
//    }
    if (val[0][0][0] == WIN)
        cout << "Lora\n";
    else if (val[0][0][0] == DRAW)
        cout << "Draw\n";
    else
        cout << "Bobi\n";
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
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

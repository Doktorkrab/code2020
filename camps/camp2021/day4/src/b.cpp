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
const int MAXN = 150;
const int MAXQ = 1e6 + 7;
char arr[MAXN][MAXN];
int dist[MAXN][MAXN];
bool used[MAXN][MAXN];
int ans[MAXQ];
vector<pair<int, int>> starts[MAXQ];
vector<pair<int, int>> blocked[MAXQ];
vector<int> queries[MAXN][MAXN];

bool check(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m && arr[x][y] == '.';
}

bool check(const pair<int, int> &s, const pair<int, int> &b, const pair<int, int> &e) {
    arr[b.first][b.second] = '#';
    deque<pair<int, int>> q = {{s}};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist[i][j] = 1e9, used[i][j] = false;
    dist[s.first][s.second] = 0;
    while (!q.empty()) {
        auto[x, y] = q.front();
        q.pop_front();
        if (used[x][y])
            continue;
        used[x][y] = true;
        if (check(x + 1, y) && dist[x + 1][y] > dist[x][y] + 1) {
            dist[x + 1][y] = dist[x][y] + 1;
            q.emplace_back(x + 1, y);
        }
        if (check(x, y + 1) && dist[x][y + 1] > dist[x][y]) {
            dist[x][y + 1] = dist[x][y] + 1;
            q.emplace_back(x, y + 1);
        }
    }
    arr[b.first][b.second] = '.';
    return used[e.first][e.second];
}

void solve_slow() {
    int q;
    cin >> q;
    for (int iter = 0; iter < q; iter++) {
        int a, b, c;
        vector<pair<int, int>> starts, blocked, ends;
        cin >> a;
        for (int i = 0; i < a; i++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            starts.emplace_back(x, y);
        }
        cin >> b;
        for (int i = 0; i < b; i++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            blocked.emplace_back(x, y);
        }
        cin >> c;
        for (int i = 0; i < c; i++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            ends.emplace_back(x, y);
        }

        int ans = 0;
        for (auto a : starts)
            for (auto b : blocked)
                for (auto e : ends)
                    ans += check(a, b, e);
        cout << ans << '\n';
    }
}

void mark_used(int xs, int ys){
    deque<pair<int, int>> q = {{xs, ys}};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist[i][j] = 1e9, used[i][j] = false;
    dist[xs][ys] = 0;
    while (!q.empty()) {
        auto[x, y] = q.front();
        q.pop_front();
        if (used[x][y])
            continue;
        used[x][y] = true;
        if (check(x - 1, y) && dist[x - 1][y] > dist[x][y] + 1) {
            dist[x - 1][y] = dist[x][y] + 1;
            q.emplace_back(x - 1, y);
        }
        if (check(x, y - 1) && dist[x][y - 1] > dist[x][y]) {
            dist[x][y - 1] = dist[x][y] + 1;
            q.emplace_back(x, y - 1);
        }
    }
}

void solve_faster(){
    int q;
    cin >> q;
    for (int iter = 0; iter < q; iter++){
        int a, b, c;
        cin >> a;
        for (int i = 0; i < a; i++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            starts[iter].emplace_back(x, y);
        }
        cin >> b;
        for (int i = 0; i < b; i++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            blocked[iter].emplace_back(x, y);
        }
        cin >> c;
        for (int i = 0; i < c; i++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            queries[x][y].push_back(iter);
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            mark_used(i, j);
            for (int qe : queries[i][j]) {
                for (auto[xs, ys] : starts[qe]){
                    for (auto [xb, yb] : blocked[qe]){
                        int x = xs, y = ys;
                        while ((x != i || y != j) && check(x, y)){
                            if (x == xb && y == yb)
                                break;
                            if (used[x + 1][y])
                                x++;
                            else
                                y++;
                        }
                        if (x == i && y == j){
                            ans[qe]++;
                            continue;
                        }
                        x = xs, y = ys;
                        while ((x != i || y != j) && check(x, y)){
                            if (x == xb && y == yb)
                                break;
                            if (used[x][y + 1])
                                y++;
                            else
                                x++;
                        }
                        if (x == i && y == j){
                            ans[qe]++;
                            continue;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
    solve_faster();
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

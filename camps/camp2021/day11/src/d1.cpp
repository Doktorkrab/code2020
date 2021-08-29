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
 
int n, r, c;
const pair<int, int> shift[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int MAXC = 2e3 + 7;
const int INF = 1e9;
int dist[MAXC][MAXC];
bool used[MAXC][MAXC];

bool check(int x, int y){
    return 0 <= x && x < r && 0 <= y && y < c;
}

int solve() {
    if (!(cin >> r >> c >> n))
        return 1;
    if (n == 1){
        int a, b;
        cin >> a >> b;
        cout << max(abs(a - 1) + abs(b - 1),
                    max(abs(a - r) + abs(b - 1), max(abs(a - r) + abs(b - c), abs(a - 1) + abs(b - c)))) << '\n';
        return 0;
    }
    deque<pair<int, int>> q;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            dist[i][j] = INF, used[i][j] = false;
    for (int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        --x, --y;
        dist[x][y] = 0;
        q.emplace_back(x, y);
    }
    int mx = 0;
    while (SZ(q)){
        auto [x, y] = q.front();
        q.pop_front();
        if (used[x][y])
            continue;
        mx = max(dist[x][y], mx);
        used[x][y] = true;
        for (auto [sx, sy] : shift){
            int x1 = x + sx, y1 = y + sy;
            if (check(x1, y1) && dist[x1][y1] > dist[x][y] + 1){
                dist[x1][y1] = dist[x][y] + 1;
                q.emplace_back(x1, y1);
            }
        }
    }
    cout << mx << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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

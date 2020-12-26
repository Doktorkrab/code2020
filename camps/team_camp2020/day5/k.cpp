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
//#define int ll
int n, m;
int t;
const int MAXN = 3e3 + 5;
const int MAXT = 2e5 + 7;
const int MAXM = 505;
// [i;t)
// (x_a, y_a)
// d_x, d_y - shift x_0 y_0
// min j > i: x_a = dx_j-dx_i+x0, y_a = dy_j-dy_i+y0
// dx_j = x_a+dx_i-x0, dy_j = y_a+dy_i-y0
// map[{dx_j, dy_j}] = j
// dx_j = n - x_0 + dx_i || dx_j = dx_i - x0 - 1
// dy_j = n - y_0 + dy_i || dy_j = dy_i - y0 - 1
// t*#moun*log_t
// for (i = t - 1;
int pnt = 0;
pair<int, int> hills[MAXM];
int can[4 * MAXN][4 * MAXN];
int can_x[4 * MAXN];
int can_y[4 * MAXN];
int lol = t + 1;
int &get(int x, int y) {
    if (x + MAXN < 0 || x + MAXN > 4 * MAXN || y + MAXN < 0 || y + MAXN > 4 * MAXN)
        return lol = t + 1;
    return can[x + MAXN][y + MAXN];
}
int& get_x(int x){
    if (x + MAXN < 0 || x + MAXN > 4 * MAXN)
        return lol = t + 1;
    return can_x[x + MAXN];
}
int& get_y(int x){
    if (x + MAXN < 0 || x + MAXN > 4 * MAXN)
        return lol = t + 1;
    return can_y[x + MAXN];
}

pair<int, int> get_shift(char c) {
    if (c == 'U')
        return make_pair(-1, 0);
    if (c == 'D')
        return make_pair(1, 0);
    if (c == 'L')
        return make_pair(0, -1);
    if (c == 'R')
        return make_pair(0, 1);
    assert(0);
}

int dx[MAXT], dy[MAXT];
string s;
struct tr{
    int x, y, id;
    bool operator<(const tr& oth) {
        return tie(x, y, id) < tie(oth.x, oth.y, oth.id);
    }
    bool operator>(const tr& oth) {
        return tie(x, y, id) > tie(oth.x, oth.y, oth.id);
    }
};
tr d[MAXT];
pair<int, int> dxx[MAXT];
pair<int, int> dyy[MAXT];
int mn[MAXT];
int solve() {
    if (!(cin >> n >> t >> s))
        return 1;
    lol = t + 1;
    int x0, y0;
    char c;
    pnt = 0;
    fill(mn, mn + MAXT, t);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> c;
            if (c == '.')
                continue;
            if (c == '#')
                hills[pnt++] = {i, j};
            if (c == '@')
                x0 = i, y0 = j;
        }
    int x = 0, y = 0;
    for (int i = 0; i < t; i++) {
        dx[i] = x, dy[i] = y;
        d[i] = {x, y, i};
        dxx[i] = {x, i};
        dyy[i] = {y, i};
        auto[sx, sy] = get_shift(s[i]);
        x += sx;
        y += sy;
    }


    dx[t] = x, dy[t] = y;
    d[t] = {x, y, t};
    dxx[t] = {x, t};
    dyy[t] = {y, t};
    sort(d, d + t + 1);
    sort(dxx, dyy + t + 1);
    sort(dyy, dxx + t + 1);
    for (int i = 0; i < pnt; i++){
        int r = t;
        for (int j = t - 1; j >= 0; j--){
            while (r > 0 && d[r] > {hills[i].first + dx[j] - x0, hills[i].second + dy[j] - y0})
        }
    }
    return 0;
}

signed main() {
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);
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

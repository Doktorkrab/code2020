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
const int MAXN = 1e3 + 7;
char fld[MAXN][MAXN];
string s;

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

int xs, ys;

int check(const string &s) {
    int x = xs;
    int y = ys;
    for (char c : s) {
        auto[sx, sy] = get_shift(c);
        x += sx, y += sy;
        if (x < 0 || y < 0 || x >= n || y >= n || fld[x][y] == '#')
            return 0;
    }
    return 1;
}

int solve() {
    if (!(cin >> n >> m >> s))
        return 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cin >> fld[i][j];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (fld[i][j] == '@')
                xs = i, ys = j;
    }
    int ans = 0;
    for (int i = 0; i < m; i++)
        for (int j = 1; j + i <= m; j++) {
            ans += check(s.substr(i, j));
//            if (check(s.substr(i, j)))
//                cout << i + 1 << " " << i + j << '\n';
        }
    cout << ans << '\n';
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

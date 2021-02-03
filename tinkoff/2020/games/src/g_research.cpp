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

const int MAXN = 20;
int g[MAXN][MAXN][MAXN][MAXN];

int solve_rec(int x1, int y1, int x2, int y2) {
    if (g[x1][y1][x2][y2] != -1)
        return g[x1][y1][x2][y2];
    // move the first
    if ((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0))
        return 0;
    unordered_set<int> have;
    for (int k = 1; k < n; k++) {
        if (x1 - k >= 0)
            have.insert(solve_rec(x1 - k, y1, x2, y2));
        if (x2 - k >= 0)
            have.insert(solve_rec(x1, y1, x2 - k, y2));
        if (y1 - k >= 0)
            have.insert(solve_rec(x1, y1 - k, x2, y2));
        if (y2 - k >= 0)
            have.insert(solve_rec(x1, y1, x2, y2 - k));
        if (x1 - k >= 0 && y1 - k >= 0)
            have.insert(solve_rec(x1 - k, y1 - k, x2, y2));
        if (x2 - k >= 0 && y2 - k >= 0)
            have.insert(solve_rec(x1, y1, x2 - k, y2 - k));

    }
    g[x1][y1][x2][y2] = 0;
    while (have.count(g[x1][y1][x2][y2]))
        g[x1][y1][x2][y2]++;
    return g[x1][y1][x2][y2];

}

int solve() {
    if (!(cin >> n))
        return 1;
    n = MAXN;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                for (int w = 0; w < n; w++)
                    g[i][j][k][w] = -1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                for (int w = 0; w < n; w++)
                    if (!solve_rec(i, j, k, w))
                        if (i + j > 0 && k + w > 0)
                            cout << i << ' ' << j << ' ' << k << ' ' << w << '\n';

    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("g_research.in", "r", stdin);
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

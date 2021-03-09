#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ld = long double;

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

const ld EPS = 1e-9;

void gauss(vector<vector<ld>> matrix) {
    int sz = n * m;
    vector<int> where_pivot(sz, -1);
    for (int col = 0, row = 0; col < sz && row < sz; col++) {
        int sel = row;
        for (int i = row; i < sz; i++) {
            if (abs(matrix[i][col]) > abs(matrix[sel][col]))
                sel = i;
        }
        if (abs(matrix[sel][col]) < EPS)
            continue;
        for (int i = col; i <= sz; i++)
            swap(matrix[sel][i], matrix[row][i]);
        where_pivot[col] = row;
        for (int i = 0; i < sz; i++) {
            if (i != row) {
                ld now = matrix[i][col] / matrix[row][col];
                for (int j = col; j <= sz; j++)
                    matrix[i][j] -= now * matrix[row][j];
            }
        }
        ++row;
    }
    vector<ld> ans(sz);
    for (int i = 0; i < sz; i++) {
        if (where_pivot[i] != -1)
            ans[i] = matrix[where_pivot[i]][sz] / matrix[where_pivot[i]][i];
    }
    cout << fixed << setprecision(20);
    for (int i = 0; i < sz; i++)
        cout << ans[i] << " \n"[(i + 1) % m == 0];
}

pair<int, int> shift[] = {{-2, 1},
                          {-2, -1},
                          {2,  1},
                          {2,  -1},
                          {1,  2},
                          {1,  -2},
                          {-1, 2},
                          {-1, -2}};

int solve() {
    if (!(cin >> n >> m))
        return 1;
    vector<vector<ld>> matrix(n * m, vector<ld>(n * m + 1));
    for (int i = 0; i < n * m; i++)
        matrix[i][n * m] = 1;
    auto check = [&](int x, int y) {
        return 0 <= x && 0 <= y && x < n && y < m;
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i * m + j][i * m + j] = 1;
            for (auto[sx, sy] : shift) {
                int x = i + sx, y = j + sy;
                if (check(x, y))
                    matrix[i * m + j][x * m + y] = -0.125;
            }
        }
    }

//    for (int i = 0; i < n * m; i++)
//        for (int j = 0; j <= n * m; j++)
//            cout << matrix[i][j] << " \n"[j == n * m];
    gauss(matrix);
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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

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

using ld = long double;
#define double ld
int n;
const double EPS = 1e-9;

void gauss(vector<vector<double>> matrix) {
    vector<int> where_pivot(n, -1);
    for (int col = 0, row = 0; col < n && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++) {
            if (abs(matrix[i][col]) > abs(matrix[sel][col]))
                sel = i;
        }
        if (abs(matrix[sel][col]) < EPS)
            continue;
        for (int i = col; i <= n; i++)
            swap(matrix[sel][i], matrix[row][i]);
        where_pivot[col] = row;
        for (int i = 0; i < n; i++) {
            if (i != row) {
                double now = matrix[i][col] / matrix[row][col];
                for (int j = col; j <= n; j++)
                    matrix[i][j] -= now * matrix[row][j];
            }
        }
        ++row;
    }
    vector<double> ans(n);
    for (int i = 0; i < n; i++) {
        if (where_pivot[i] != -1)
            ans[i] = matrix[where_pivot[i]][n] / matrix[where_pivot[i]][i];
    }
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++)
            sum += ans[j] * matrix[i][j];
        if (abs(sum - matrix[i][n]) > EPS) {
            cout << "impossible\n";
            return;
        }
    }
    for (int i = 0; i < n; i++)
        if (where_pivot[i] == -1) {
            cout << "infinity\n";
            return;
        }
    cout << "single\n";
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
}


int solve() {
    if (!(cin >> n))
        return 1;
    vector<vector<double>> matrix(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            cin >> matrix[i][j];
    gauss(matrix);
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(20);
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

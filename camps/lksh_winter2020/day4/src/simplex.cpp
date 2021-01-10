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
const long double EPS = 1e-6;

// ax <= b
// x >= 0
void simplex_solve(vector<vector<long double>> &matrix, bool &unbound, vector<int> &basis_pos) {
    while (true) {
        bool good = true;
        for (int i = 0; i < n + m + 1; i++) {
            good &= (matrix[m][i] < 0 || abs(matrix[m][i]) < EPS);
        }
        if (good)
            break;
        int nxt = 0;
        for (int i = 0; i < n + m + 1; i++) {
            if (matrix[m][i] > EPS) {
                nxt = i;
                break;
            }
        }
        long double limit = TMAX(long double);
        int where = -1;
        for (int i = 0; i < m; i++) {
            if (matrix[i][nxt] < EPS)
                continue;
            long double now = matrix[i][n + m + 1] / matrix[i][nxt];
            if (now < limit) {
                limit = now;
                where = i;
            }
        }
        if (where == -1) {
            unbound = true;
            return;
        }
        long double c = matrix[where][nxt];
        for (int i = 0; i < n + m + 2; i++)
            matrix[where][i] /= c;
        for (int i = 0; i < n + m + 2; i++)
            if (basis_pos[i] == where)
                basis_pos[i] = -1;
        basis_pos[nxt] = where;
        for (int i = 0; i <= m + 1; i++) {
            if (i == where)
                continue;
            c = matrix[i][nxt];
            for (int j = 0; j < n + m + 2; j++)
                matrix[i][j] -= c * matrix[where][j];
        }
    }
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    vector<vector<long double>> matrix(m + 2, vector<long double>(n + m + 2));
    vector<int> basis(n + m + 2, -1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cin >> matrix[i][j];
        cin >> matrix[i][n + m + 1];
    }
    for (int i = 0; i < n; i++)
        cin >> matrix[m][i];
    for (int i = 0; i < m; i++) {
        matrix[i][n + i] = 1;
        basis[n + i] = i;
        matrix[i][n + m] = -1;
    }
    matrix[m + 1][n + m] = -1;
    bool unbound = false;

    int min_b = 0;
    for (int i = 1; i < m; i++)
        if (matrix[i][n + m + 1] < matrix[min_b][n + m + 1])
            min_b = i;
    if (matrix[min_b][n + m + 1] < -EPS) {
        long double c = matrix[min_b][n + m];
        for (int i = 0; i < n + m + 2; i++)
            matrix[min_b][i] /= c;
        for (int i = 0; i < m + 2; i++) {
            if (i == min_b)
                continue;
            c = matrix[i][n + m];
            for (int j = 0; j < n + m + 2; j++)
                matrix[i][j] -= matrix[min_b][j] * c;
        }
        for (int i = 0; i < n + m + 2; i++)
            if (basis[i] == m + n)
                basis[i] = -1;
        basis[n + m] = min_b;

        swap(matrix[m], matrix[m + 1]);
        simplex_solve(matrix, unbound, basis);
        assert(!unbound);

        if (abs(matrix[m][n + m + 1]) > EPS) {
            cout << "No solution\n";
            return 0;
        }
        swap(matrix[m + 1], matrix[m]);
    }
    int z_basis = -1;
    for (int i = 0; i < m; i++)
        if (basis[i] == n + m) {
            z_basis = i;
            break;
        }
    if (z_basis == -1) {
        for (int i = 0; i < m + 2; i++)
            matrix[i][n + m] = 0;
    } else {
        int nxt = -1;
        for (int i = 0; i < n + m + 1; i++)
            if (abs(matrix[z_basis][i]) > EPS) {
                nxt = i;
                break;
            }
        assert(nxt != -1);
        long double c = matrix[z_basis][nxt];
        for (int i = 0; i < n + m + 2; i++)
            matrix[z_basis][i] /= c;
        for (int i = 0; i < n + m + 2; i++)
            if (basis[i] == z_basis)
                basis[i] = -1;
        basis[nxt] = z_basis;
    }
    simplex_solve(matrix, unbound, basis);
    if (unbound)
        cout << "Unbounded\n";
    else {
        vector<long double> ans(n);
        for (int i = 0; i < n; i++)
            if (basis[i] != -1)
                ans[i] = matrix[basis[i]][n + m + 1];
        cout << fixed << setprecision(20) << -matrix[m][n + m + 1] << " :";
        for (long double x : ans)
            cout << ' ' << x;
        cout << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("simplex.in", "r", stdin);
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

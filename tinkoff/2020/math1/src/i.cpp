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
const int MAXN = 55;

vector<vector<double>> multiply(vector<vector<double>> a, vector<vector<double>> b) {
//    for (int i = 0; i < n + 2; i++)
//        for (int j = i; j < n + 2; j++)
//            swap(b[i][j], b[j][i]);

    vector<vector<double>> c(n + 2, vector<double>(n + 2));
    for (int i = 0; i < n + 2; i++)
        for (int j = 0; j < n + 2; j++)
            for (int k = 0; k < n + 2; k++)
                c[i][j] += a[i][k] * b[k][j];

    return c;
}

int solve() {
    if (!(cin >> n))
        return 1;
    vector<vector<double>> matrix(n + 2, vector<double>(n + 2));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 2; j++) {
            cin >> matrix[i][j];
            matrix[i][j] = matrix[i][j] / 100.;
        }
    }
//    for (int i = 0; i < n + 2; i++)
//        for (int j = 0; j < n + 2; j++)
//            cout << matrix[i][j] << " \n"[j == n + 1];
    fill(ALL(matrix[n]), 0);
    matrix[n][n] = 1;

    fill(ALL(matrix[n + 1]), 0);
    matrix[n + 1][n + 1] = 1;


    for (int iter = 0; iter < 100; iter++) {
        matrix = multiply(matrix, matrix);
//        for (int i = 0; i < n + 2; i++)
//            for (int j = 0; j < n + 2; j++)
//                cout << matrix[i][j] << " \n"[j == n + 1];
//        cout << '\n';
    }
    cout << fixed << setprecision(20) << matrix[0][n] << '\n';

    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("i.in", "r", stdin);
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

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

int n, m, d, k;
const int MOD = 1e9 + 7;

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}

vector<vector<int>> multiply(vector<vector<int>> a, vector<vector<int>> b) {
    int n = a.size();
    int m = b[0].size();
    vector<vector<int>> ret(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < (int) b.size(); k++) {
                ret[i][j] += (1LL * a[i][k] * b[k][j]) % MOD;
                ret[i][j] %= MOD;
            }
    return ret;
}

vector<vector<int>> bin_pow(vector<vector<int>> a, int x) {
    vector<vector<int>> res(a.size(), vector<int>(a.size()));
    for (int i = 0; i < (int) a.size(); i++)
        res[i][i] = 1;
    while (x) {
        assert(x >= 0);
        if (x & 1)
            res = multiply(res, a);
        a = multiply(a, a);
        x >>= 1;
    }
    return res;
}

const int T = 10;

int solve() {
    if (!(cin >> n >> m >> d >> k))
        return 1;
    vector<vector<int>> matrix(301, vector<int>(301));
    for (int i = 0; i < n; i++)
        for (int j = 0; j + 1 < T; j++)
            matrix[i * T + j][i * T + j + 1] = 1;
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        matrix[v * T + T - 1][u * T + (T - w)]++;
        matrix[u * T + T - 1][v * T + (T - w)]++;
    }

    matrix = bin_pow(matrix, d);
    for (int i = 0; i < n; i++)
        matrix[i * T + T - 1][300] = 1;
    matrix[300][300] = 1;
    matrix = bin_pow(matrix, k / d + 1);
    int kek = 0;
    for (int i = 0; i < n; i++)
        kek = add(kek, matrix[i * T + T - 1][300]);
    cout << (kek + MOD - n) % MOD << '\n';
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

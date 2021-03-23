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
#define int ll
int n;
int k;
const int MOD = 1e9 + 7;

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}

vector<vector<int>> matrix_multiply(vector<vector<int>> a, vector<vector<int>> b) {
    vector<vector<int>> c(SZ(a), vector<int>(SZ(b[0])));
    for (int i = 0; i < SZ(a); i++)
        for (int j = 0; j < SZ(b[0]); j++) {
            for (int k = 0; k < SZ(b); k++)
                c[i][j] = add(c[i][j], mul(a[i][k], b[k][j]));
        }
    return c;
}

vector<vector<int>> bin_p(vector<vector<int>> a, int b) {
    vector<vector<int>> ans(SZ(a), vector<int>(SZ(a[0])));
    for (int i = 0; i < SZ(a) && i < SZ(a[0]); i++)
        ans[i][i] = 1;
    while (b > 0) {
        if (b & 1)
            ans = matrix_multiply(ans, a);
        a = matrix_multiply(a, a);
        b /= 2;
    }
    return ans;
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> matrix[i][j];
    matrix = bin_p(matrix, k);
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans = add(ans, matrix[i][j]);
    cout << ans << '\n';
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

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
const double EPS = 1e-9;
int solve() {
    if (!(cin >> n >> m))
        return 1;
    vector<vector<double>> matrix(m + 1, vector<double>(n + m + 1));
    vector<int> basis(m);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++)
            cin >> matrix[i][j];
        cin >> matrix[i][n + m];
    }
    for (int i = 0; i < n; i++)
        cin >> matrix[m][i];
    for (int i = 0; i < m; i++) {
        matrix[i][n + i] = 1;
    }

    while (true){
        bool good = true;
        for (int i = 0; i < n + m; i++){
            good &= (matrix[m][i] < 0 || abs(matrix[m][i]) < EPS);
        }
        if (good)
            break;
        int nxt = 0;
        for (int i = 0; i < n + m + 1; i++){
            if (matrix[m][i] > EPS){
                nxt = i;
                break;
            }
        }
        double limit = TMAX(double);
        int where = -1;
        for (int i = 0; i < m; i++){
            if (matrix[i][nxt] < EPS)
                continue;
            double now = matrix[i][n + m] / matrix[i][nxt];
//            cout << '\t' << i << ' ' << now << '\n';
            if (now < limit){
                limit = now;
                where = i;
            }
        }
//        cout << limit << ' ' << where << ' ' << nxt << '\n';
        assert(where != -1);
        double c = matrix[where][nxt];
        for (int i = 0; i < n + m + 1; i++)
            matrix[where][i] /= c;
        for (int i = 0; i <= m; i++){
            if (i == where)
                continue;
            c = matrix[i][nxt];
            for (int j = 0; j < n + m + 1; j++)
                matrix[i][j] -= c * matrix[where][j];
        }
//        for (int i = 0; i <= m; i++)
//            for (int j = 0; j < n + m + 1; j++)
//                cout << matrix[i][j] << " \n"[j == n + m];
    }
    cout << fixed << setprecision(20) << -matrix[m][n + m] << '\n';
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
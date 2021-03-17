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

int n, m, t;
const int MAXN = 405;
int types[MAXN][MAXN];
bool is_down[MAXN][MAXN];
bool is_right[MAXN][MAXN];
bool used[MAXN][MAXN];
vector<int> cols[MAXN], rows[MAXN];

int solve() {
    if (!(cin >> n >> m >> t))
        return 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> types[i][j];
            if (types[i][j] >= 3)
                cols[i].push_back(j);
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (types[j][i] >= 3)
                rows[i].push_back(j);
        }
    }
    for (int i = 0; i < n; i++) {
        if (SZ(cols[i]) % 2 != 0) {
            cout << "NO\n";
            return 0;
        }
        for (int x = 0; x < SZ(cols[i]); x += 2) {
            int j1 = cols[i][x];
            int j2 = cols[i][x + 1];
            is_right[i][j1] = true;
            is_right[i][j2] = false;
            used[i][j1] = used[i][j2] = true;
            for (int j = j1 + 1; j < j2; j++) {
                if (used[i][j] || (types[i][j] != 1 && types[i][j] != 2)) {
                    cout << "NO\n";
                    return 0;
                }
                types[i][j] = 1;
                used[i][j] = true;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        if (SZ(rows[i]) % 2 != 0) {
            cout << "NO\n";
            return 0;
        }
        for (int x = 0; x < SZ(rows[i]); x += 2) {
            int j1 = rows[i][x];
            int j2 = rows[i][x + 1];
            used[j1][i] = used[j2][i] = true;
            is_down[j1][i] = true;
            is_down[j2][i] = false;
            for (int j = j1 + 1; j < j2; j++) {
                if (used[j][i] || (types[j][i] != 1 && types[j][i] != 2)) {
                    cout << "NO\n";
                    return 0;
                }
                types[j][i] = 2;
                used[j][i] = true;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (types[i][j] != 0 && !used[i][j]) {
                cout << "NO\n";
                return 0;

            }
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (types[i][j] >= 3) {
                int a = is_right[i][j];
                int b = is_down[i][j];
                int &c = types[i][j];
                if (a && b)
                    c = 5;
                if (a && !b)
                    c = 4;
                if (!a && b)
                    c = 6;
                if (!a && !b)
                    c = 3;
            }
            cout << types[i][j] << " \n"[j + 1 == m];
        }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

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
const int MAXN = 55;
bitset<3> matrix[MAXN];

ll gauss() {
    int now = 0;
    for (int i = 0; i < m; i++) {
        int sel = now;
        for (int j = now; j < n; j++)
            if (matrix[j][i]) {
                sel = j;
                break;
            }
        if (!matrix[sel][i])
            continue;
        swap(matrix[sel], matrix[now]);
        for (int j = 0; j < n; j++)
            if (j != now && matrix[j][i])
                matrix[j] ^= matrix[now];
        now++;
    }
//    for (int i = 0; i < n; i++)
//        cout << matrix[i] << '\n';
    int cnt = 0;
    for (int i = 0; i < n; i++)
        cnt += !matrix[i].none();
    int have = cnt;
    return (1LL << have);
}

int solve() {
    if (!(cin >> m >> n))
        return 1;
    char x;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> x;
            matrix[i][j] = (x == '1');
        }
    }
    cout << gauss() << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("o.in", "r", stdin);
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

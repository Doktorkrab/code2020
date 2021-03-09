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
const int MAXN = 308;
bitset<MAXN> matrix[MAXN];
int where_pivot[MAXN];
int orig[MAXN];

void gauss() {
    for (int col = 0, row = 0; col < n && row < n; col++) {
        int sel = row;
        for (int j = row; j < n; j++) {
            if (matrix[j][col]) {
                sel = j;
                break;
            }
        }
        if (!matrix[sel][col])
            continue;
        where_pivot[col] = row;
        swap(matrix[sel], matrix[row]);
        swap(orig[sel], orig[row]);
        for (int i = 0; i < n; i++) {
            if (i != row && matrix[i][col])
                matrix[i] ^= matrix[row];
        }
        row++;
    }
    bitset<MAXN> ans;
    for (int i = 0; i < n; i++) {
        if (where_pivot[i] != -1)
            ans[i] = matrix[where_pivot[i]][n];
    }
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++)
            sum ^= (ans[j] & matrix[i][j]);
        if (sum != matrix[i][n]) {
            cout << "No solution\n";
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        if (where_pivot[i] == -1) {
            cout << "Multiple solutions\n";
            return;
        }
    }
    if (ans.none()) {
        cout << "Multiple solutions\n";
        return;
    }
    for (int i = 0; i < n; i++)
        if (ans[i])
            cout << i << " ";
    cout << '\n';
}

int solve() {
    if (!(cin >> n))
        return 1;
    iota(orig, orig + n, 0);
    fill(where_pivot, where_pivot + n, -1);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < n; j++) {
            char x;
            cin >> x;
            matrix[j][i] = (x == '1');
        }
    gauss();
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("j.in", "r", stdin);
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

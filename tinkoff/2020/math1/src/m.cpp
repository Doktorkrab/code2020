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
int m;
const int MAXN = 55;
const int MAXM = 1e4;
int where_pivot[MAXN];
int frst[MAXN];
ll matrix[MAXM];


int solve() {
    if (!(cin >> n >> m))
        return 1;
    fill(where_pivot, where_pivot + n, -1);
    fill(frst, frst + n, 0);
    for (int i = 0; i < m; i++) {
        matrix[i] = 0;
        for (int j = 0; j < n; j++) {
            char x;
            cin >> x;
            matrix[i] = matrix[i] * 2 + (x - '0');
        }

        for (int j = 0; j < n; j++)
            if ((matrix[i] >> j) & 1)
                if (where_pivot[j] != -1)
                    matrix[i] ^= matrix[where_pivot[j]];
        if (matrix[i] == 0) {
            cout << "1\n";
            continue;
        }
        cout << "0\n";
        bool was = false;
        for (int j = 0; j < n; j++) {
            if (((matrix[i] >> j) & 1) && (where_pivot[j] == -1)) {
                where_pivot[j] = i;
                if (!was) {
                    was = true;
                    for (int k = 0; k < i; k++) {
                        if ((matrix[k] >> j) & 1)
                            matrix[k] ^= matrix[j];
                    }
                    break;
                }
            }
        }
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("m.in", "r", stdin);
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

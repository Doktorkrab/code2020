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
const int MAXN = 1e3;
int fld[MAXN][MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    vector<int> as1(n), as(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> as1[i];
        sum += as1[i];
    }
    vector<int> perm(n);
    iota(ALL(perm), 0);
    do {
        for (int i = 0; i < n; i++)
            as[i] = as1[perm[i]];
        for (int mask = 0; mask < (1 << n); mask++) {
            int x = 0;
            int y = 0;
            fld[x][y] = 1;
            for (int i = 0; i < n; i++) {
                if ((mask >> i) & 1) {
                    for (int j = 0; j < as[i]; j++) {
                        fld[x][++y] = 1;
                    }
                } else {
                    for (int j = 0; j < as[i]; j++)
                        fld[++x][y] = 1;
                }
            }
        }
    } while (next_permutation(ALL(perm)));
    int ans = 0;
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            ans += fld[i][j];
    cout << ans << '\n';
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

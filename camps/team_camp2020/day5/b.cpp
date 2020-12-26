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

enum {
    ON_PLATFORM,
    FINISHED,
    LAST,
    ON_WIRE;
};

int n, m;
const int MAXN = 105;
int now_v[MAXN];
int state[MAXN];
int num[MAXN];
int p[MAXN];
int r[MAXN];
int l[MAXN];
int d[MAXN];
int max_v[MAXN][MAXN];

 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 1; i + 1 < n; i++)
        cin >> p[i];
    p[0] = p[n - 1] = n + 100;
    for (int i = 0; i + 1 < n; i++)
        cin >> r[i];
    for (int i = 0; i + 1 < n; i++)
        cin >> l[i];
    for (int i = 0; i  +)
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

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

int n, k;
const int MAXN = 17;
bool used[MAXN][MAXN];
ll ans = 0;

void rec(int x) {
    if (x == 0){
        ans++;
        return;
    }
    for (int i = 1; i <= x; i++){
        for (int j = 1; j <= k; j++) {
            if (used[i][j])
                continue;
            used[i][j] = true;
            rec(x - i);
            used[i][j] = false;
        }
    }
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    ans = 0;
    rec(n);
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

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

#define int long long

const int N = 16;

int dp1[N][N], dp2[N][N];
int n, k;

void build_dp2() {
    dp2[0][0] = 1;
    for (int c = 1; c <= k; ++c){
        dp2[c][0] = 1;
        for (int cnt = 1; cnt < N; ++cnt){
            dp2[c][cnt] = 0;
            for (int x = 0; x <= cnt; ++x){
                dp2[c][cnt] += dp2[c - 1][cnt - x];
            }
            // cout << c << ' ' << cnt << ' ' << dp2[c][cnt] << '\n';
        }
    }
}

void build_dp1(){
    for (int x = 0; x <= n; ++x){
        dp1[0][x] = 1;
    }
    for (int i = 1; i <= n; ++i){
        for (int x = 1; x <= n; ++x){
            dp1[i][x] = 0;
            for (int cnt = 0; cnt * x <= i; ++cnt){
                dp1[i][x] += dp1[i - cnt * x][x - 1] * dp2[k][cnt];
            }
            // cout << i << ' ' << x << ' ' << dp1[i][x] << '\n';
        }
    }
}
 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    build_dp2();
    build_dp1();
    cout << dp1[n][n] << '\n';
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

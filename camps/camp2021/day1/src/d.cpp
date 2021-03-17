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
 
int n, m, k, q;

const double phi = (1 + sqrt(5)) / 2.;

int get_mean(int a, int b){
    return a + (b - a + 1) / phi;
}

int ask1d(int x){
    if (x <= 0 || x > n)
        return 0;
    cout << "? " << x << " 1 1" << endl;
    int y;
    cin >> y;
    if (y == -1)
        exit(0);
    return y;
}

int gss(int a, int b, int x, int fx){
    if (a == b)
        return x;
    int y = get_mean(a, b);
    if (2 * x > a + b) y = a + b - y;
    if (x == y)
        y++;
    int fy = ask1d(y);
    if (x > y){
        swap(x, y);
        swap(fx, fy);
    }
    if (fx <= fy)
        return gss(x + 1, b, y, fy);
    return gss(a, y - 1, x, fx);
}

void solve1d(){
    int x = get_mean(1, n);
    int ans = gss(1, n, x, ask1d(x));
    cout << "! " << ans << " 1 1" << endl;

}
 
int solve() {
    if (!(cin >> n >> m >> k >> q))
        return 1;
    solve1d();
    return 1;
}
 
signed main() {
//#ifdef LOCAL
//    freopen("d.in", "r", stdin);
//#endif
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
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

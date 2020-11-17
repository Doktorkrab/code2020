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

const int N = 3e5;

int n, v, u;
int a[N];
 
int solve() {
    if (!(cin >> n))
        return 1;
    cin >> u >> v;
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    sort(a, a + n, greater<int>());
#define ld long double
    ld t = 0;
    for (int i = 0; i < n; ++i){
        if (i == n - 1 || a[i + 1] <= u * t){
            t += max((ld)0, a[i] - t * u) / ((ld)v / (i + 1) + u);
        }else{
            t += min(max((ld)0, a[i] - t * u) / ((ld)v / (i + 1) + u),
                     1.L * (a[i] - a[i + 1]) / (1.L * v / (i + 1)));
        }
    }
    cout << t * v << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(47);
    cout << fixed;
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

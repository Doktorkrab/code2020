#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
#define int ll

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
 
int a, b, n;

 
int solve() {
    if (!(cin >> a >> b >> n))
        return 1;
    int cnt = 0;

    if (a > b)
        swap(a, b);
    while (b <= n){
        a += b;
        cnt++;

        if (a > b)
            swap(a, b);
    }
    cout << cnt << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
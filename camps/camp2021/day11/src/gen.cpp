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

 
int solve() {
    if (!(cin >> n))
        return 1;
    return 0;
}
 
signed main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 10 + 1;
    int k = rnd() % (20 * n + 1);
    cout << n << ' ' << k << '\n';
    for (int i = 0; i < 2 * n; i++)
        cout << rnd() % n + 1 << ' ' << rnd() % n + 1 << ' ' << rnd() % 20 + 1 << '\n';
}

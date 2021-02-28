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
const int MAXN = 100;
signed main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % MAXN + 1;
    cout << n << " 1\n";
    for (int i = 1; i < n; i++)
        cout << rnd() % i << " \n"[i + 1 == n];
    cout << rnd() % n << ' ' << rnd() % n << '\n';
    cout << "0 0 0\n";
}

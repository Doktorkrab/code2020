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

 
signed main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 500 + 1, q = rnd() % 500 + 1;
    cout << n << ' ' << q << '\n';
    for (int i = 0; i < q; i++){
        int type = rnd() % 2 + 1;
        int l = rnd() % n + 1;
        int r = rnd() % n + 1;
        if (l > r)
            swap(l, r);
        cout << type << " " << l << ' ' << r;
        if (type == 1)
            cout << ' ' << rnd() % 100000 + 1 << '\n';
        else
            cout << '\n';
    }
}

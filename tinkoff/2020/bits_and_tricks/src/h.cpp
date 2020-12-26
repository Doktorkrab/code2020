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

const int MAXN = (1U << 20U);
ll f[MAXN];
unsigned n;
unsigned N;

int solve() {
    if (!(cin >> n))
        return 1;
    N = (1U << n);
    for (size_t i = 0; i < N; i++) {
        cin >> f[i];
    }
    for (size_t i = 0; i < n; i++)
        for (size_t mask = 0; mask < N; mask++)
            if (mask & (1U << i))
                f[mask] -= f[mask ^ (1U << i)];
    for (size_t i = 0; i < N; i++)
        cout << f[i] << " \n"[i + 1 == N];
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

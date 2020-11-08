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

const int MAXN = 40;

map<pair<int, int>, ll> solve(int *a, int n) {
    map<pair<int, int>, ll> ret;
    for (ll mask = 0; mask < (1 << n); mask++) {
        int g[] = {0, 0};
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1)
                g[1] = gcd(g[1], a[i]);
            else
                g[0] = gcd(g[0], a[i]);
        }
        ret[{g[0], g[1]}] = mask;
    }
    return ret;
}

int n;
int a[MAXN], b[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n / 2; i++)
        cin >> a[i];
    auto ans1 = solve(a, n / 2);
    for (int i = n / 2; i < n; i++)
        cin >> b[i - n / 2];
    auto ans2 = solve(b, n - n / 2);
    for (auto [a1, m1] : ans1){
        auto [a, b] = a1;
        for (auto [a2, m2] : ans2){
            auto [c, d] = a2;
            ll kek = (m1 << (n - n / 2)) | m2;
            if (gcd(a, c) == 1 && gcd(b, d) == 1 && kek != 0 && kek != (1LL << n) - 1){
                cout << "YES\n";
                for (int i = 0; i < n / 2; i++)
                    cout << ((m1 >> i) & 1) + 1 << ' ';
                for (int i = n / 2; i < n; i++)
                    cout << ((m2 >> (i - n / 2)) & 1) + 1 << ' ';
                cout << '\n';
                return 0;
            }
        }
    }
    cout << "NO\n";
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

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

int h;
int n, m, a, b;

void solve(int ba, int bb){
    int cnta = n / ba;
    int cntb = m / bb;
    int parity = 0;
    if (bb > ba)
        parity = 1;
//    cout << ba << ' ' << bb << '\n';
    for (int i = 0; i < ba + bb; i++){
        if (i % 2 == parity){
            for (int j = 0; j < cnta; j++)
                cout << "G";
            if (ba - i / 2 <= n % ba)
                cout << "G";
        } else {
            for (int j = 0; j < cntb; j++)
                cout << "B";
            if (bb - i / 2 <= m % bb)
                cout << "B";

        }
    }
    cout << "\n";
}

int solve() {
    if (!(cin >> h >> n >> m >> a >> b))
        return 1;
    if (n == 0) {
        if (b < m) {
            cout << "NO\n";
            return 0;
        }
        cout << "YES\n";
        if (h == 1)
            solve(1, 1);
        return 0;
    }
    if (m == 0) {
        if (a < n) {
            cout << "NO\n";
            return 0;
        }
        cout << "YES\n";
        if (h == 1)
            solve(1, 1);
        return 0;
    }

    int blocksa = (n + a - 1) / a;
    if (a > n)
        blocksa = 1;
    int blocksb = (m + b - 1) / b;
    if (b > m)
        blocksb = 1;
    int ta = n;
    int tb = m;
//    cout << ta << ' ' << tb << ' ' << blocksa << ' ' << blocksb << '\n';
    if (blocksa <= blocksb) {
        if (ta + 1 >= blocksb) {
            cout << "YES\n";
            if (h == 1) {
                if (ta >= blocksb)
                    solve(ta, ta);
                else
                    solve(ta, blocksb);
            }
            return 0;
        } else {
            cout << "NO\n";
            return 0;
        }
    }
    if (tb + 1 >= blocksa) {
        cout << "YES\n";
        if (h == 1) {
            if (tb >= blocksa)
                solve(blocksa, blocksa);
            else
                solve(blocksa, tb);
        }
    } else
        cout << "NO\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
#else
    freopen("registration.in", "r", stdin);
    freopen("registration.out", "w", stdout);
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

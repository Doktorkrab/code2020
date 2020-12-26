#pragma GCC optimize("Ofast,O3,unroll-loops")
#pragma GCC target("popcnt")

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
int max_d = 0;
struct Operation {
    ll a = -1, b = -1;
    int type;
};
const int MAXN = 5e6 + 7;
Operation ans[MAXN];
int pnt = 0;
ll need;

void rec(ll mask) {
    if (__builtin_popcountll(mask | need) > max_d)
        return;
    int tmp = pnt;
    for (int i = 1; i <= 42; i++) {
        if ((mask >> i) & 1) {
            for (int j = i; i + j <= 42; j++) {
                if (((mask >> j) & 1) && !((mask >> (i + j)) & 1) && ((need >> (i + j)) & 1)) {
                    ans[pnt++] = {i, j, 0};
                    mask |= (1LL << (i + j));
                }
            }
            for (int j = 1; i - j > 0; j++) {
                if (((mask >> j) & 1) && !((mask >> (i - j)) & 1) && ((need >> (i - j)) & 1)) {
                    ans[pnt++] = {i, j, 1};
                    mask |= (1LL << (i - j));
                }
            }
            for (int j = 1; (i << j) <= 42; j++)
                if (!((mask >> (i << j)) & 1) && ((need >> (i << j)) & 1)) {
                    ans[pnt++] = {i, j, 2};
                    mask |= (1LL << (i << j));
                }
        }
    }
    if ((mask & need) == need) {
        cout << pnt << '\n';
        for (int i = 0; i < pnt; i++) {
            auto &[a, b, c] = ans[i];
            cout << a;
            if (c == 0)
                cout << '+';
            if (c == 1)
                cout << '-';
            if (c == 2)
                cout << "<<";
            cout << b << '\n';
        }
        exit(0);
    }
    for (int i = 1; i <= 42; i++) {
        if ((mask >> i) & 1) {
            for (int j = i; i + j <= 42; j++) {
                if (((mask >> j) & 1) && !((mask >> (i + j)) & 1)) {
                    ans[pnt++] = {i, j, 0};
                    rec(mask | (1LL << (i + j)));
                    pnt--;
                }
            }
            for (int j = 1; i - j > 0; j++) {
                if (((mask >> j) & 1) && !((mask >> (i - j)) & 1)) {
                    ans[pnt++] = {i, j, 1};
                    rec(mask | (1LL << (i - j)));
                    pnt--;
                }
            }
            for (int j = 1; (i << j) <= 42; j++)
                if (!((mask >> (i << j)) & 1)) {
                    ans[pnt++] = {i, j, 2};
                    rec(mask | (1LL << (i << j)));
                    pnt--;
                }
        }
    }
    pnt = tmp;
}

int solve() {
    if (!(cin >> n))
        return 1;
    need = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        need |= (1LL << x);
    }
    for (int i = __builtin_popcountll(need) + 1; i <= 43; i++) {
        max_d = i;
        assert(i < MAXN);
        rec(2);
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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

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
// #define int ll
const int MOD = 998244353;
const int W = 805775211;
const int IW = 46809892;
const int INV2 = 499122177;


const unsigned MAXLOG = 19;  // for 250'000
const int MAXN = 1U << MAXLOG;
const long double pi = acos(-1.L);
int pws[(1U << 19U) + 1];
int ipws[(1U << 19U) + 1];

using cd = int;

void init() {
    pws[MAXN] = W;
    ipws[MAXN] = IW;
    for (int i = MAXN / 2; i >= 1; i /= 2) {
        pws[i] = (1LL * pws[i * 2] * pws[i * 2]) % MOD;
        ipws[i] = (1LL * ipws[i * 2] * ipws[i * 2]) % MOD;
    }
}

void fft(const vector<int> &s, vector<int> &res, int n, bool inv, int bs = 0, int step = 1, int rs = 0) {
    if (n == 1) {
        res[rs] = s[bs];
        return;
    }
    fft(s, res, n / 2, inv, bs, step * 2, rs);
    fft(s, res, n / 2, inv, bs + step, step * 2, rs + n / 2);
    int c = 1;
    int gw = (inv ? ipws[n] : pws[n]);
    for (int i = rs; i < rs + n / 2; i++) {
        int a = res[i];
        int b = (1LL * c * res[i + n / 2]) % MOD;
        res[i] = (a + b) % MOD;
        res[i + n / 2] = (a - b) % MOD;
        if (res[i + n / 2] < 0)
            res[i + n / 2] += MOD;
        if (inv) {
            res[i] = (1LL * res[i] * INV2) % MOD;
            res[i + n / 2] = (1LL * res[i + n / 2] * INV2) % MOD;
        }
        c = (1LL * c * gw) % MOD;
    }
}

int n, N;

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    assert(SZ(a) == MAXN && SZ(b) == MAXN);
    vector<cd> fa(MAXN), fb(MAXN);
    fft(a, fa, MAXN, false);
    fft(b, fb, MAXN, false);
    for (int i = 0; i < MAXN; i++)
        fa[i] = (1LL * fa[i] * fb[i]) % MOD;
    vector<cd> res(MAXN);
    fft(fa, res, MAXN, true);
    return res;
}

int solve() {
    if (!(cin >> n))
        return 1;
    N = (int) (1U << n);
    vector<int> a(MAXN), b(MAXN);
    for (int i = 0; i < N; i++)
        cin >> a[i];
    for (int i = 0; i < N; i++)
        cin >> b[i];
    auto res = multiply(a, b);
    for (int i = 0; i < 2 * N; i++)
        cout << res[i] << " \n"[i + 1 == 2 * N];
    return 0;
}


signed main() {
    init();
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

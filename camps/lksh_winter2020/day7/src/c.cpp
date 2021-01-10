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

int n, m;

const int MAXLOG = 18;
const int MAXN = 1 << MAXLOG;
const int MOD = 7340033;
ll W[MAXN];
int rev[MAXN];

int fast_pow(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans *= a;
            ans %= MOD;
        }
        a *= a;
        a %= MOD;
        b /= 2;
    }
    return (int) ans;
}


void precalc() {
    ll g = fast_pow(5, (MOD - 1) / MAXN);
    int last = 0;
    for (int i = 1; i < MAXN; i++) {
        if (i == (2 << last))
            last += 1;
        rev[i] = rev[i ^ (1 << last)] | (1 << (MAXLOG - 1 - last));
    }
    W[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        W[i] = (W[i - 1] * g) % MOD;
    }
}

void fft(vector<ll> &a) {
    for (int i = 0; i < MAXN; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int lvl = 0; lvl < MAXLOG; ++lvl) {
        int len = (1 << lvl);
        for (int st = 0; st < MAXN; st += 2 * len)
            for (int i = 0; i < len; i++) {
                ll first = a[st + i];
                ll second = (a[st + i + len] * W[i << (MAXLOG - (lvl + 1))]) % MOD;
                a[st + i] = (first + second) % MOD;
                a[st + i + len] = (first + MOD - second) % MOD;
            }
    }
}

ll REVERSE_MAXN = fast_pow(MAXN, MOD - 2);

void inv_fft(vector<ll> &a) {
    fft(a);
    for (ll &el : a)
        el = (el * REVERSE_MAXN) % MOD;
    reverse(a.begin() + 1, a.end());
}

vector<ll> divide(vector<ll>& p){
    vector<ll> A(MAXN);
    vector<ll> tmp(MAXN);
    A[0] = fast_pow(p[0], MOD - 2);
    fft(p);
    for (int sz = 1; sz <= m; sz <<= 1){
        fft(A);
        for (int i = 0; i < MAXN; i++)
            tmp[i] = A[i] * p[i] % MOD;
        inv_fft(tmp);
        tmp[0] = (2 + MOD - tmp[0]) % MOD;
        for (int i = 1; i < MAXN; i++)
            tmp[i] = (MOD - tmp[i]) % MOD;
        fft(tmp);
        for (int i = 0; i < MAXN; i++)
            A[i] = tmp[i] * A[i] % MOD;
        inv_fft(A);
        for (int i = 2 * sz; i < MAXN; i++)
            A[i] = 0;
    }
    return A;
}

int solve() {
    if (!(cin >> m >> n))
        return 1;
    vector<ll> poly(MAXN);
    for (int i = 0; i <= n; i++)
        cin >> poly[i];
    if (poly[0] == 0){
        cout << "The ears of a dead donkey\n";
        return 0;
    }
    auto ret = divide(poly);
//    fft(ret);
//    vector<ll> tmp(MAXN);
//    for (int i = 0; i < MAXN; i++)
//        tmp[i] = poly[i] * ret[i] % MOD;
//    inv_fft(tmp);
//    tmp[0] = (tmp[0] + MOD - 1) % MOD;
//    for (int i = 0; i < m; i++)
//        assert(tmp[i] == 0);
//    inv_fft(ret);
    for (int i = 0; i < m; i++)
        cout << ret[i] << " \n"[i + 1 == m];
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#else
    freopen("bankcraft.in", "r",stdin);
    freopen("bankcraft.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    precalc();
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
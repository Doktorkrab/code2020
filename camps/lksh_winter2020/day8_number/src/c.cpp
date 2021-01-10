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

__int128 n;
mt19937 rnd(239);

ll get_rand(ll a, ll b) {
    return a + (rnd() % (b - a + 1));
}

__int128 gcd(__int128 a, __int128 b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

__int128 pow_fast(__int128 a, __int128 b, __int128 mod) {
    unsigned __int128 res = 1;
    assert(a >= 0 && b >= 0 && mod > 0);
    unsigned __int128 bt = b;
    unsigned __int128 at = a;
    unsigned __int128 modt = mod;
    for (; bt > 0; bt >>= 1) {
        if (bt & 1)
            res = (res * at) % modt;
        at = (at * at) % modt;
    }
    return res;
}

bool miller_rabin(__int128 x) {
    if (x == 1 || x == 2)
        return true;
    assert(x > 2);
    __int128 m = x - 1;
    __int128 s = 0;
    while (m % 2 == 0) {
        s++;
        m /= 2;
    }
    for (int i = 0; i < 50; i++) {
        __int128 t = get_rand(2, x - 1);
        __int128 cur = pow_fast(t, m, x);
        if (cur == 1 || cur == x - 1)
            continue;
        bool good = false;
        for (int j = 0; j < s - 1; j++) {
            cur = pow_fast(cur, 2, x);
            if (cur == 1)
                return false;
            if (cur == x - 1) {
                good = true;
                break;
            }
        }
        if (!good)
            return false;
    }
    return true;
}

__int128 f(__int128 x, __int128 mod) {
    assert(x >= 0);
    unsigned __int128 t = x;
    return (t * t + 2) % mod;
}

__int128 mod(__int128 a, __int128 b) {
    __int128 ret = a % b;
    if (ret < 0)
        ret += b;
    return ret;
}

int solve() {
    unsigned long long n1;
    if (!(cin >> n1))
        return 1;
    n = n1;
    vector<__int128> to_fact = {n};
    vector<__int128> ans;
    while (SZ(to_fact)) {
        __int128 x = to_fact.back();
        to_fact.pop_back();
        while (true) {
            if (miller_rabin(x)) {
                ans.push_back(x);
                break;
            }
            __int128 start = get_rand(0, x - 1);
            __int128 x0 = start;
            __int128 x1 = f(x0, x);
            __int128 g = gcd(mod(x0 - x1, x), x);
            __int128 cnt = 0;
            while (cnt < 100000) {
                if (1 < g && g < x) {
                    to_fact.push_back(g);
                    to_fact.push_back(x / g);
                    break;
                }
                x0 = f(x0, x);
                x1 = f(f(x1, x), x);
                g = gcd(mod(x0 - x1, x), x);
                cnt++;
            }
            if (cnt != 100000)
                break;
        }
    }
    assert(SZ(ans) > 0);
    __int128 x = 1;
    for (__int128 i : ans)
        x *= i;
    assert(x == n);
    sort(ALL(ans));
    for (__int128 i : ans)
        cout << (unsigned long long) i << " ";
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#else
    freopen("pollard.in", "r", stdin);
    freopen("pollard.out", "w", stdout);
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
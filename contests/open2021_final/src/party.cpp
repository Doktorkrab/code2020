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

ll n, m;
ll k;
const int MAXN = 5e5 + 7;
int pos_a[2 * MAXN];
int a[MAXN];
int pos_b[2 * MAXN];
int b[MAXN];

struct GCD_result {
    ll g, x0, y0;
};

ll mod(ll a, ll b) {
    return (a % b + b) % b;
}

ll dd(ll a, ll b) {
    return (a - mod(a, b)) / b;
}

GCD_result gcd(ll a, ll b) {
    if (a == 0)
        return {b, 0, 1};
    auto[g, x0, y0] = gcd(mod(b, a), a);
    return {g, y0 - 1LL * dd(b, a) * x0, x0};
}

//pair<ll, ll> solve_diof(ll a, ll b, ll c, ll d){
//    int ans_t = b;
//    int lcm = a;
//    auto ret = gcd(lcm, c);
//    int x1 = ret.x0;
//    int d = ret.g;
//    if ((have[i].second - ans_t) % d != 0)
//        return {};
//    ans_t = mod(ans_t + x1 * (have[i].second - ans_t) / d % (have[i].first / d) * lcm, lcm * have[i].first / d);
//
//}


ll solve_slow() {
    ll now = 0;
    while (k != 0) {
//        cout << a[now % n] << ' ' << b[now % m] << '\n';
        if (a[now % n] != b[now % m])
            k--;
//        else
//            cout << '\t' << now << '\n';
        now++;
    }
    return now;
}

ll solve_lcm() {
    ll l = 1LL * n * m / gcd(n, m).g;
    ll cnt = l;
    ll kt = k;
//    for (int i = 0; i <  l; i++)
//        cout <<setw(2) << a[i % n] << " \n"[i + 1 == l];
//    for (int i = 0; i < l; i++)
`//        cout << setw(2) << b[i % m] << " \n"[i + 1 == l];`
    ll lst = 0;
    set<ll> bad;
    for (int i = 0; i < n; i++)
        if (pos_b[a[i]] != -1) {
            ll x2 = pos_b[a[i]];
            ll x1 = i;

            auto ret = gcd(n * 1LL, m * 1LL);
            ll x = ret.x0;
            ll d = ret.g;
            ll ans_t = x1;
            if ((x2 - ans_t) % d != 0)
                continue;
            cnt--;
            ans_t = mod(ans_t + x * (x2 - ans_t) / d % (m / d) * n, 1LL * n * m / d);
//            cout << ans_t << ' ' << x1 << ' ' << x2 << '\n';
            bad.insert(ans_t);
        }

//    for (int i = 0; i < l; i++) {
//        if (a[i % n] != b[i % m]) {
//            cnt++;
//            lst = i;
//        }
//    }
    lst = l - 1;
    while (bad.count(lst)) {
        lst--;
    }
    bad.insert(l);
    ll ans = l * (kt / cnt);
    kt %= cnt;
    cnt = 0;
    if (kt != 0) {
        ll prev = 0;
        for (ll x : bad) {
            ll d = x - prev;
            prev = x + 1;
            if (d < kt) {
                kt -= d;
                ans += d + 1;
                continue;
            }
            ans += kt;
            break;
        }
    } else {
        ans = ans - l + lst + 1;
    }
    return ans;
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;

    fill(pos_a, pos_a + 2 * MAXN, -1);
    fill(pos_b, pos_b + 2 * MAXN, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos_a[a[i]] = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        pos_b[b[i]] = i;
    }
    cout << solve_lcm() << '\n';
//    cout << solve_slow() << '\n';
    return 0;
}

void stress() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        fill(pos_a, pos_a + 2 * MAXN, -1);
        fill(pos_b, pos_b + 2 * MAXN, -1);
        n = rnd() % 30 + 1;
        m = rnd() % 30 + 1;
        k = rnd() % 30 + 1;
        ll kt = k;
        vector<int> perm(2 * max(n, m));
        iota(ALL(perm), 1);
        shuffle(ALL(perm), rnd);
        for (int i = 0; i < n; i++) {
            a[i] = perm[i];
            pos_a[a[i]] = i;
        }
        shuffle(ALL(perm), rnd);
        for (int i = 0; i < m; i++) {
            b[i] = perm[i];
            pos_b[b[i]] = i;
        }
        int a1 = solve_slow();
        k = kt;
        int a2 = solve_lcm();
        if (a1 != a2) {
            cout << n << ' ' << m << ' ' << kt << '\n';
            for (int i = 0; i < n; i++)
                cout << a[i] << " \n"[i + 1 == n];
            for (int j = 0; j < m; j++)
                cout << b[j] << " \n"[j + 1 == m];
            cout << a1 << ' ' << a2 << '\n';
            exit(0);
        }
    }
}

signed main() {
#ifdef LOCAL
    freopen("party.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
//    stress();
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

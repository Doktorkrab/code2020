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

ll n, p;
const int MAXN = 1e5 + 7;
ll arr[MAXN];

ll a = 0, b = 1;

void relax(int i, int j) {
    ll was_a = arr[a], was_b = arr[b];
    ll now_a = arr[i], now_b = arr[j];
    ll _val_a = abs(was_a / was_b - p);
    ll _val_b = abs(now_a / now_b - p);
    if (abs(_val_a - _val_b) > 4) {
//        cout << i << ' ' << j << ' ' << abs(was_a / was_b - p) << ' ' <<  abs(now_a / now_b - p) << '\n';
        if (_val_a > _val_b) {
            a = i;
            b = j;
        }
        return;
    }
//    cout << i << ' ' << j << '\n';
    ll val_a = abs(was_a - p * was_b) - _val_a * was_b;
    ll val_b = abs(now_a - p * now_b) - _val_a * now_b;
//    cout << val_a * now_b << ' ' << val_b * now_a << '\n';
    if (val_a * now_b > val_b * now_a) {
        a = i;
        b = j;
    }
}

pair<int, int> solve() {
//    if (!(cin >> n >> p))
//        return {-1, -1};
//    for (int i = 0; i < n; i++)
//        cin >> arr[i];
    set<pair<ll, int>> have;
    a = 0, b = 1;
    for (int i = 0; i < n; i++)
        have.emplace(arr[i] * p, i);
    for (int i = 0; i < n; i++) {
        ll now = arr[i];
        have.erase({now * p, i});
        auto it = have.lower_bound({now, -1});
        if (it != have.end())
            relax(i, it->second);
        if (it != have.begin())
            relax(i, prev(it)->second);
        if (it != have.end() && next(it) != have.end())
            relax(i, next(it)->second);
        have.insert({now * p, i});

    }
//    cout << a + 1 << ' ' << b + 1 << '\n';
    return {a, b};
}

pair<int, int> slow() {
    long double ans = TMAX(long double);
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (i != j && abs(1.L * arr[i] / arr[j] - p) < ans) {
                a = i;
                b = j;
                ans = abs(1.L * arr[i] / arr[j] - p);
            }
    }
    return {a, b};
}

signed main() {

//    freopen("prices.in", "r", stdin);
//    freopen("prices.out", "w", stdout);
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
//    int tests = 1e9;
////    cin >> tests;
//    auto[a, b] = solve();
//    cout << a + 1 << ' ' << b + 1 << '\n';
//#ifdef LOCAL
//    cout << "------------------------------\n";
//#endif
//}
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    while (true){
        n = rnd() % 5 + 2;
        p = rnd() % 100 + 1;
        for (int i = 0; i < n; i++)
            arr[i] = rnd() % 100 + 1;
        auto [a1, b1] = solve();
        auto [a2, b2] = slow();
        long double ans1 = abs(1.L * arr[a1] / arr[b1] - p);
        long double ans2 = abs(1.L * arr[a2] / arr[b2] - p);
        if (abs(ans1 - ans2) > 1e-9){
            cout << "FUCK\n";
            cout << n << ' ' << p << '\n';
            for (int i = 0; i < n; i++)
                cout << arr[i] << " \n"[i + 1 == n];
            cout << a1 << ' ' << b1 << '\n';
            cout << a2 << ' ' << b2 << '\n';
            return 1;
        }
        cout << ".";
    }
}

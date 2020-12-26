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
//#define EMUL
ll x, m;
ll N;
int cnt = 0;
#ifdef EMUL
ll shift;
vector<ll> dels;

void read(){
    dels.resize(m);
    for (ll& i : dels)
        cin >> i;
    cin >> shift;
}
ll ask(ll x){
    cout << "? " << x << endl;
    x += shift;
    if (x > N)
        x -= N;
    for (int i = 0; i < m; i++)
        if (dels[i] <= x)
            x++;
    cout << "\t" << x << endl;
    return x;
}
#else
ll ask(ll x){
    assert(++cnt <= 10);
    cout << "? " << (x - 1 + N) % N + 1 << endl;
    ll ret;
    cin >> ret;
    return ret;
}
#endif
void answer(ll x){

    cout << "! " << (x - 1 + N) % N + 1 << '\n';
#ifdef EMUL
    if (x == -1)
        assert(binary_search(ALL(dels), ::x));
    else
        assert(ask(x) == ::x);
#endif
    exit(0);
}
int solve() {
    if (!(cin >> x >> m))
        return 1;
#ifdef EMUL
    read();
#endif
    const ll MOD = 1e18;
    N = MOD - m;
    ll shift = 1 + (x - ask(1) + MOD) % MOD;
    ll l = shift - m - 1, r = shift + 1;
    while (r - l > 1){
        ll mid = l + (r - l) / 2;
        ll ans = ask(mid);
        if (ans > x + 10000)
            ans -= MOD;
        else if (ans < x - 10000)
            ans += MOD;
        if (ans == x){
            answer(mid);
            return 0;
        }
        if (ans < x)
            l = mid;
        else
            r = mid;
    }
    cout << "! " << -1 << '\n';
    return 0;
}

signed main() {
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
    int tests = 1;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

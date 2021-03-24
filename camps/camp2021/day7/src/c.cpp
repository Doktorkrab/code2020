#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ull = unsigned long long;


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
const ll MOD = 100000000000000003;
const int MAXN = 5e4 + 7;
const int PEPEGA = 25;
unordered_set<ll> powers; //2^x % MOD

ull arr[MAXN];


ull add(ull a, ull b){
    return (a + b) % MOD;
}

ull mul(ull a, ull b) {
    ull ans = 0;
    while (b > 0) {
        if (b & 1)
            ans = add(ans, a);
        a = add(a, a);
        b /= 2;
    }
    return ans;
}

ull bin_p(ull a, ull b) {
    ull ans = 1;
    while (b > 0) {
        if (b & 1)
            ans = mul(ans, a);
        a = mul(a, a);
        b /= 2;
    }
    return ans;
}

ll prefix[MAXN];

void solve1(){
    for (int i = 0; i < n; i++)
        arr[i] = (1LL << arr[i]);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];
    map<ll, int> was;
    ll ans = 0;
    for (int y = 0; y <= 50; y++) {
        ll x = (1LL << y);
        was.clear();
        was[0] = 1;
        for (int i = 0; i < n; i++) {
            ans += was[prefix[i + 1] - x];
            was[prefix[i + 1]]++;
        }
    }
    cout << ans << '\n';
}

int solve() {
    if (!(cin >> n))
        return 1;
    powers.clear();
    unordered_set<ull> have;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (*max_element(arr, arr + n) <= 30) {
        solve1();
        return 0;
    }
    for (int i = 0; i < n; i++){
        have.insert(arr[i]);
        arr[i] = bin_p(2, arr[i]);
    }
    for (ull x : have){
        ull now = bin_p(2, x);
        for (int i = 0; i < PEPEGA; i++){
            powers.insert(now);
            now = mul(now, 2);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++){
        ull sum = 0;
        for (int j = i; j < n; j++){
            sum = add(sum, arr[j]);
            if (powers.count(sum))
                ans++;
        }
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
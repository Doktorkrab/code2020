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
ll s;
const int MAXN = 1e5 + 7;
const int MAXBIT = 50;
ll arr[MAXN];
int cnt[MAXBIT];

bool used[MAXBIT];
ll sum;

bool rec(int pos) {
    if (pos == MAXBIT) {
        if (sum != s)
            return false;
        ll ans = 0;
        for (int i = 0; i < MAXBIT; i++)
            ans += used[i] * (1LL << i);
        cout << ans << '\n';
        return true;
    }
    sum += (1LL << pos) * cnt[pos];
    used[pos] = false;

    ll a = sum & ((1LL << (pos + 1)) - 1);
    ll b = s & ((1LL << (pos + 1)) - 1);
//    cout << pos << ' ' << (sum >> pos) << ' ' << (s >> pos) << ' ' << "1\n";
    if (a == b && rec(pos + 1)) {
        sum -= (1LL << pos) * cnt[pos];
        return true;
    }
    sum -= (1LL << pos) * cnt[pos];
    sum += (1LL << pos) * (n - cnt[pos]);
    used[pos] = true;
    a = sum & ((1LL << (pos + 1)) - 1);
//    cout << pos << ' ' << a << ' ' << b << " 2\n";
    if (a == b && rec(pos + 1)) {
        sum -= (1LL << pos) * (n - cnt[pos]);
        used[pos] = false;
        return true;
    }
    sum -= (1LL << pos) * (n - cnt[pos]);
    used[pos] = false;
    return false;
}

int solve() {
    if (!(cin >> n >> s))
        return 1;
    fill(cnt, cnt + MAXBIT, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        for (int j = 0; j < MAXBIT; j++)
            cnt[j] += ((arr[i] >> j) & 1);
    }
    if (!rec(0))
        cout << "-1\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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

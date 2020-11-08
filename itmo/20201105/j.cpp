#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;

//#define int ll

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
const int MAXN = 4e5 + 7;
ll n, m;
int have[MAXN];
int cnt = 0;
int p = 0;
int arr[MAXN];

void add(int x) {
    if (have[x] == 0)
        cnt++;
    while (cnt > (1LL << p))
        p++;
    have[x]++;
}

void del(int x) {
    if (have[x] == 1)
        cnt--;
    while (p > 0 && cnt <= (1LL << (p - 1)))
        p--;
    have[x]--;
}

int solve() {
    p = 0;
    if (!(cin >> n >> m))
        return 1;
    m *= 8;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        have[i] = 0;
    }
    sort(arr, arr + n);
    vector<int> compress(arr, arr + n);
    compress.resize(unique(ALL(compress)) - compress.begin());
    for (int i = 0; i < n; i++)
        arr[i] = (int)(lower_bound(ALL(compress), arr[i]) - compress.begin());
    ll ans = TMAX(ll);
    int r = 0;
    for (int i = 0; i < n; i++) {
        while (r < n && 1LL * n * p <= m){
            ans = min(ans, 1LL * i + (n - r));
            add(arr[r++]);
        }
        if (n * p <= m) {
            ans = min(ans, 1LL * i + (n - r));
        }
        del(arr[i]);
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
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

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

const int N = 1e5;

int n, m, s;
vector<int> a;
 
int solve() {
    if (!(cin >> n >> m >> s))
        return 1;
    a.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int ans = 0;
    for (int i = 0; i < a.size(); ++i) {
        int j = i + (m - 1 - s);
        if (j >= SZ(a)){
            cerr << a[i] << '\n';
            continue;
        }
        int cur = max(0, min(n - m + 1, a[i]) - max(i == 0 ? 1 : a[i - 1] + 1, a[j] - m + 1) + 1);
        ans += cur;
//        cout << a[i] << ' ' << j + 1 << ' ' << cur << '\n';
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("j.in", "r", stdin);
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

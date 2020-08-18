#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
#define int ll

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
int k, x, y;
const int MAXN = 2e5 + 7;

int a[MAXN];
int b[MAXN];
int pos[MAXN];


int solve() {
    if (!(cin >> n >> m >> x >> k >> y))
        return 1;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 0; i < m; i++)
        cin >> b[i];
    for (int i = 1; i < m; i++){
        if (pos[b[i - 1]] > pos[b[i]]){
            cout << "-1\n";
            return 0;
        }
    }
    vector<pair<int, int>> segs = {{-1, pos[b[0]]}};

    for (int i = 1; i < m; i++)
        segs.emplace_back(pos[b[i - 1]], pos[b[i]]);
    segs.emplace_back(pos[b[m - 1]], n);
    int ans = 0;
    for (auto [l, r] : segs){
        int len = r - l - 1;
        // cout << a[l] << ' ' << a[r] << ' ' << len << '\n';
        if (len <= 0)
            continue;
        int mx_el = -1;
        int mx = 0;
        if (0 <= l)
            mx = a[l];
        if (r < n)
            mx = max(mx, a[r]);
        for (int i = l + 1; i < r; i++)
            mx_el = max(mx_el, a[i]);
        if (len < k){
            if (mx < mx_el){
                cout << "-1\n";
                return 0;
            }
            // cout << y * len << '\n';
            ans += y * len;
            continue;
        }
        if (len % k){
            // cout << (len % k) * x << '\n';
            ans += (len % k) * y;
            len -= (len % k);
        }
        if (x <= k * y){
            ans += len / k * x;
            continue;
        }
        if (mx < mx_el){
            ans += (len - k) * y + x;
        }
        else{
            ans += len * y;
        }
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
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

int n;
const int MAXN = 5e4 + 7;
int h[MAXN];
int w[MAXN];
int lft_h[MAXN];
int lft_w[MAXN];
pair<int, int> rdy_h[MAXN];
pair<int, int> rdy_w[MAXN];
int suffix_h[MAXN];
int suffix_w[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> h[i];
    for (int i = 0; i < n; i++)
        cin >> w[i];

    vector<pair<int, int>> stack;
    for (int i = 0; i < n; i++) {
        while (SZ(stack) && stack.back().first >= h[i])
            stack.pop_back();
        if (SZ(stack))
            lft_h[i] = i - stack.back().second;
        else
            lft_h[i] = i + 1;

        stack.emplace_back(h[i], i);
    }
    stack.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (SZ(stack) && stack.back().first >= h[i])
            stack.pop_back();
        if (SZ(stack))
            rdy_h[i] = {h[i], lft_h[i] + (stack.back().second - i - 1)};
        else
            rdy_h[i] = {h[i], lft_h[i] + (n - i - 1)};

        stack.emplace_back(h[i], i);
    }
//    for (int i = 0; i < n; i++)
//        cout << rdy_h[i].first << ' ' << rdy_h[i].second << '\n';
    sort(rdy_h, rdy_h + n);
    suffix_h[n] = 0;
    for (int i = n - 1; i >= 0; i--)
        suffix_h[i] = max(suffix_h[i + 1], rdy_h[i].second);

    stack.clear();
    for (int i = 0; i < n; i++) {
        while (SZ(stack) && stack.back().first >= w[i])
            stack.pop_back();
        if (SZ(stack))
            lft_w[i] = i - stack.back().second;
        else
            lft_w[i] = i + 1;

        stack.emplace_back(w[i], i);
    }
    stack.clear();
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        while (SZ(stack) && stack.back().first >= w[i])
            stack.pop_back();
        int t = 0;
        if (SZ(stack))
            t = lft_w[i] + (stack.back().second - i - 1);
        else
            t = lft_w[i] + (n - i - 1);
        rdy_w[i] = {w[i], t};
        int x = lower_bound(rdy_h, rdy_h + n, make_pair(w[i], 0LL)) - rdy_h;
        ans = max(ans, suffix_h[x] * t * w[i]);
        stack.emplace_back(w[i], i);
    }
    sort(rdy_w, rdy_w + n);
//    cout << '\n';
//    for (int i = 0; i < n; i++)
//        cout << rdy_w[i].first << ' ' << rdy_w[i].second << '\n';
    suffix_w[n] = 0;
    for (int i = n - 1; i >= 0; i--)
        suffix_w[i] = max(suffix_w[i + 1], rdy_w[i].second);
    stack.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (SZ(stack) && stack.back().first >= h[i])
            stack.pop_back();
        int t = 0;
        if (SZ(stack))
            t = lft_h[i] + (stack.back().second - i - 1);
        else
            t = lft_h[i] + (n - i - 1);
        int x = lower_bound(rdy_w, rdy_w + n, make_pair(h[i], 0LL)) - rdy_w;
        ans = max(ans, suffix_w[x] * t * h[i]);
        stack.emplace_back(h[i], i);
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

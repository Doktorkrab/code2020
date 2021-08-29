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

const int MAXN = 1e4 + 7;
const int MAXK = 505;
int n, m, k;
long double arr[MAXN];
long double prefix[MAXN];
int p[MAXK][MAXN];

bool check(long double x) {
    for (int i = 0; i < n; i++)
        arr[i] -= x;
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];
    vector<pair<long double, int>> have(k + 1, make_pair(TMAX(long double), -1));
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++)
            p[j][i] = -1;
    p[0][0] = 0;
    for (int i = m; i <= n; i++) {
        for (int j = k; j >= 0; j--) {
            if (p[j][i - m] != -1) {
                have[j] = min(have[j], make_pair(prefix[i - m], i - m));
                break;
            }
        }
        for (int j = k; j >= 1; j--) {
            auto it = have[j - 1];
            if (it.second == -1 || !(prefix[i] - it.first > -1e-9))
                continue;
            p[j][i] = it.second;
            break;
        }
    }

    for (int i = 0; i < n; i++)
        arr[i] += x;
//    for (int i = 0; i <= n; i++)
//        for (int j = 0; j <= k; j++)
//            cout << p[j][i] << " \n"[j == k];
    return p[k][n] != -1;
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
//    check(4.25);
//    return 0;
    double l = 0, r = 1e12 + 7;
    for (int i = 0; i < 60; i++) {
        double mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    cout << l << ' ' << r << '\n';
    check(l);
    vector<int> ans;
    int now = k, now1 = n;
    while (now > 0 && now1 > 0) {
        ans.push_back(now1 - p[now][now1]);
        now1 = p[now--][now1];
    }
    reverse(ALL(ans));
//    for (int x : ans)
//        cout << x << ' ';
//    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
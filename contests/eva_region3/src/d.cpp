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

struct Segment {
    int l, r, ind;

    bool operator<(const Segment &rhs) const {
        return std::tie(l, r, ind) < std::tie(rhs.l, rhs.r, rhs.ind);
    }
};

int n, k;
const int MAXN = 3005;
Segment segments[MAXN];
int queries[MAXN];
int indexes[MAXN];
int anses[MAXN];

bool intersect(int a, int b) {
    auto[l1, r1, i1] = segments[a];
    auto[l2, r2, i2] = segments[b];
    return max(l1, l2) < min(r1, r2) && !(l1 <= l2 && r2 <= r1) && !(l2 <= l1 && r1 <= r2);
}

int dp[MAXN];

int stupid1(int x) {
    if (anses[x] != -1)
        return anses[x];
    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (!intersect(x, i) && x != i)
            continue;
        vector<int> have;
        for (int j = 0; j < i; j++) {
            if (j == x || !intersect(x, j))
                continue;
            if (segments[j].l < segments[i].l && segments[i].l < segments[j].r)
                have.push_back(j);
        }
        if (i != x)
            have.push_back(i);
        if (!SZ(have))
            continue;
        fill(dp, dp + SZ(have), 2);
        cout << i + 1 << ": ";
        for (int x : have)
            cout << x + 1 << " ";
        cout << '\n';
        for (int j = 0; j < SZ(have); j++){
            for (int k = j - 1; k >= 0; k--){
                if (segments[have[k]].r < segments[have[j]].r) {
                    dp[j] = max(dp[j], dp[k] + 1);
                }
            }
            ans = max(ans, dp[j]);
        }
        for (int j = 0; j < SZ(have); j++)
            cout << dp[j] << " \n"[j + 1 == SZ(have)];
    }
    return anses[x] = ans;
}

int stupid(int x) {
    int ans = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        int t_m = mask | (1 << x);
        vector<int> have;
        for (int i = 0; i < n; i++)
            if ((t_m >> i) & 1)
                have.push_back(i);

        bool good = true;
        for (int i = 0; i < SZ(have); i++) {
            for (int j = i + 1; j < SZ(have); j++) {
                good &= intersect(have[i], have[j]);
            }
        }
        if (good) {
            ans = max(ans, SZ(have));
        }
    }
    return ans;
}

int solve() {
    if (!(cin >> n))
        return 1;
    fill(anses, anses + n, -1);
    for (int i = 0; i < n; i++)
        cin >> segments[i].l >> segments[i].r, segments[i].ind = i;
    sort(segments, segments + n);
//    for (int i = 0; i < n; i++)
//        cout << segments[i].l << ' ' << segments[i].r << '\n';
    for (int i = 0; i < n; i++)
        indexes[segments[i].ind] = i;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        x = indexes[x - 1];
        int ans1 = stupid1(x);
        int ans = stupid(x);
//        assert(ans == ans1);
        cout << ans1 << ' ' << ans << '\n';
//        cout << ans1 << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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

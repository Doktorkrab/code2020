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

int n, q;
const int MAXN = 1.5e3;
const int MAXC = 23;
int arr[MAXN][MAXN];
int sums[MAXC][MAXN][MAXN];
int cnt[MAXN * MAXN];

vector<int> solve_slow() {
    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cnt[arr[i][j]] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cnt[arr[i][j]]++;
    int mx = n;
    int mx_cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mx_cnt = max(mx_cnt, cnt[arr[i][j]]);
    if (mx_cnt <= 10)
        mx = 10;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            set<int> have;
            for (int l = 1; i - l + 1 >= 0 && j - l + 1 >= 0 && l <= mx; l++) {
                for (int x = 0; x < l; x++) {
                    have.insert(arr[i - x][j - l + 1]);
                    have.insert(arr[i - l + 1][j - x]);
                }
                if (SZ(have) <= q)
                    ans[l]++;
            }
        }
    }
    return ans;
}

vector<int> solve_cmax() {
    vector<int> ans(n + 1);
    for (int c = 1; c < MAXC; c++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                sums[c][i + 1][j + 1] = sums[c][i + 1][j] + sums[c][i][j + 1] - sums[c][i][j] + (arr[i][j] == c);
    auto get = [&](int c, int i, int j, int i1, int j1) {
        return sums[c][i1][j1] - sums[c][i][j1] - sums[c][i1][j] + sums[c][i][j];
    };
    auto check = [&](int l, int i, int j) {
        int cnt = 0;
        for (int x = 0; x < MAXC; x++)
            cnt += !!get(x, i - l, j - l, i, j);
        return cnt <= q;
    };
    check(3, 3, 3);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int l = 1, r = min(i, j) + 1;
            while (r - l > 1) {
                int m = (l + r) / 2;
                if (check(m, i, j))
                    l = m;
                else
                    r = m;
            }
            if (check(l, i, j))
                ans[l]++;
        }
    }
    for (int i = n - 1; i >= 1; i--)
        ans[i] += ans[i + 1];
    return ans;
}

int tree[MAXN][MAXN];
vector<pair<int, int>> enters[MAXN * MAXN];

void add(int x, int y, int w) {
    for (int i = x; i < MAXN; i |= i + 1)
        for (int j = y; j < MAXN; j |= j + 1)
            tree[i][j] += w;
}

int get(int x, int y) {
    int ans = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            ans += tree[i][j];
    return ans;
}

int get(int x1, int y1, int x2, int y2) {
    return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
}

vector<int> solve_q1() {
    vector<int> ans(n + 1);
    for (int i = 0; i <= n * n; i++)
        enters[i].clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            enters[arr[i][j]].emplace_back(i, j);
    }
    for (int i = 0; i <= n * n; i++) {
        for (auto[a, b] : enters[i])
            add(a, b, 1);
        for (auto[a, b] : enters[i]) {
            int l = 1, r = min(a, b) + 2;
            while (r - l > 1) {
                int m = (l + r) / 2;
                if (get(a - m + 1, b - m + 1, a, b) == m * m)
                    l = m;
                else
                    r = m;
            }
//            cout << a + 1 << ' ' << b + 1 << ' ' << l << '\n';
            ans[l]++;
        }
        for (auto [a, b] : enters[i])
            add(a, b, -1);
    }
    for (int i = n - 1; i >= 1; i--)
        ans[i] += ans[i + 1];
    return ans;
}

int solve() {
    if (!(cin >> n >> q))
        return 1;
    int mx = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j], mx = max(arr[i][j], mx);
    vector<int> ans;
    if (q == 1)
        ans = solve_q1();
    else if (mx < MAXC)
        ans = solve_cmax();
    else
        ans = solve_slow();

    for (int i = 1; i <= n; i++)
        cout << ans[i] << "\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("next_episode.in", "r", stdin);
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

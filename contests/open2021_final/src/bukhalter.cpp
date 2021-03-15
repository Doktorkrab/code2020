//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")

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

int n, m;
const int MAXN = 2e3 + 7;
vector<vector<int>> a, b;
vector<int> ans;
vector<int> order;

bool rec(int level, int pos, int prev) {
//    cout << level << ' ' << pos << endl;
    if (level == pos) {
        bool good = true;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                good &= (a[order[i]][j] == b[i][j]);
        if (good) {
            cout << SZ(ans) << '\n';
            for (int x : ans)
                cout << x + 1 << ' ';
            cout << '\n';
            return true;
        }
        return false;
    }
    auto a_t = order;
    for (int i = 0; i < m; i++) {
        if (i == prev)
            continue;
        ans.push_back(i);
        stable_sort(ALL(order), [&](int x, int y) {
            return a[x][i] < a[y][i];
        });
        if (rec(level, pos + 1, i)) {
            order = a_t;
            ans.pop_back();
            return true;
        }
        ans.pop_back();
        order = a_t;
    }
    return false;
}

bool check_correct_table() {
    for (int i = 0; i < n; i++) {
        sort(ALL(a[i]));
        sort(ALL(b[i]));
        if (a[i] != b[i])
            return false;
    }
    return true;
}

bool check_perm() {
    vector<vector<int>> rows(m, vector<int>(n));
    vector<int> kek(n);
    iota(ALL(kek), 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            rows[i][j] = b[j][i];
        sort(ALL(rows[i]));

        if (kek != rows[i])
            return false;
    }
    return true;
}

void solve_perm() {
    vector<vector<int>> rows(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            rows[i][j] = b[j][i];
        if (is_sorted(ALL(rows[i]))) {
            bool good = true;
            stable_sort(ALL(order), [&](int x, int y) {
                return a[x][i] < a[y][i];
            });
            for (int k = 0; k < n; k++)
                for (int j = 0; j < m; j++)
                    good &= (a[order[k]][j] == b[k][j]);
            if (good) {
                cout << "1\n" << i + 1 << '\n';
                return;
            }
            cout << "-1\n";
            return;
        }
    }
    cout << "-1\n";
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    a.resize(n, vector<int>(m));
    b.resize(n, vector<int>(m));
    order.resize(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> b[i][j];
    iota(ALL(order), 0);
    int end = m;
    if (check_perm()) {
        solve_perm();
        return 0;
    }
    for (int i = 1; i <= end; i++)
        if (rec(i, 0, -1)) {
            return 0;
        }
    cout << "-1\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("bukhalter.in", "r", stdin);
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

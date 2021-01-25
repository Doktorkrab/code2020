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
const int MAXN = 1e5 + 7;
pair<int, int> have[MAXN];
int s[MAXN];
int len = -1;

bool check(int d) {
//    cout << d << '\n';
    map<int, int> inds;
    vector<vector<pair<int, int>>> g;
    auto get_ind = [&](int val) {
        if (!inds.count(val)) {
            inds[val] = SZ(g);
            g.emplace_back();
        }
        return inds[val];
    };

    for (int i = 0; i < n; i++) {
        int from = get_ind(d - have[i].first);
        int to = get_ind(have[i].second);
//        cout << d - have[i].first << ' ' << have[i].second << '\n';
//        cout << from << "->" << to << '\n';
        g[from].emplace_back(to, i);
    }
    vector<int> cnt_in(SZ(g));
    for (auto &i : g) {
        for (auto[u, _] : i)
            cnt_in[u]++;
    }
    int in = -1, out = -1;
    for (int i = 0; i < SZ(g); i++) {
        if (cnt_in[i] != SZ(g[i])) {
            if (cnt_in[i] + 1 == SZ(g[i])) {
                if (in != -1)
                    return false;
                in = i;
            } else if (cnt_in[i] == SZ(g[i]) + 1) {
                if (out != -1)
                    return false;
                out = i;
            } else
                return false;
        }
    }
    int edges = n;

    if (in != -1) {
        g[out].emplace_back(in, n);
        edges++;
    }
    vector<bool> used(edges);
    vector<int> ans;
    vector<int> now(edges);
    function<void(int)> dfs = [&](int v) {
        while (now[v] < SZ(g[v])) {
            auto[u, i] = g[v][now[v]++];
            if (used[i])
                continue;
            used[i] = true;
            dfs(u);
            ans.push_back(i);
        }
    };
    dfs(0);
    if (SZ(ans) != edges)
        return false;
    if (edges == n + 1) {
        rotate(ans.begin(), find(ALL(ans), n), ans.end());
        ans.erase(ans.begin());
    }
    cout << "Yes\n";
    reverse(ALL(ans));
    for (int x : ans)
        cout << x + 1 << ' ';
    cout << '\n';
    return true;
}

int solve() {
    if (!(cin >> n))
        return 1;
    len = -1;
    bool good = true;
    for (int i = 0; i < n; i++) {
        have[i] = {-1, -1};
        int x;
        cin >> x >> s[i];
        cin >> have[i].first;
        int prev = have[i].first;
        for (int j = 1; j < x; j++) {
            cin >> have[i].second;
            if (len == -1)
                len = have[i].second - prev;
//            cout << i << ' ' << j << " " << have[i].second - prev << ' ' << len << '\n';
            if (len != have[i].second - prev) {
                good = false;
            }
            prev = have[i].second;
        }
        if (have[i].second == -1)
            have[i].second = have[i].first;
        have[i].second = s[i] - have[i].second;
    }
    if (!good) {
        cout << "No\n";
        return 0;
    }
    if (n == 1) {
        cout << "Yes\n1\n";
        return 0;
    }
    vector<int> dists_vars;
    if (len == -1) {
        vector<int> arr1, arr2;
        for (int i = 0; i < n; i++) {
            auto [a, b] = have[i];
            arr1.push_back(a), arr2.push_back(b);
        }
        sort(ALL(arr1));
//        arr1.resize(unique(ALL(arr1)) - arr1.begin());
        sort(ALL(arr2));
//        arr2.resize(unique(ALL(arr2)) - arr2.begin());
        reverse(ALL(arr2));
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++) {
//                cout << arr1[i] << ' ' << arr2[j] << '\n';
                dists_vars.push_back(arr1[i] + arr2[j]);
            }
    } else
        dists_vars = {len};
    for (int d : dists_vars) {
        if (check(d))
            return 0;
    }
    cout << "No\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d1.in", "r", stdin);
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

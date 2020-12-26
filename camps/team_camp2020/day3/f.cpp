#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 1e6 + 7;

int n, m;
int a[N];

int& ga(int i, int j) { return a[i * m + j]; }

void scan() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> ga(i, j);
        }
    }
}

int dp[N];
int& gdp(int i, int j) { return dp[i * m + j]; }

vector<pair<pair<int, int>, int>> ev[N];

void solve() {
    for (int i = 0; i < n; ++i) {
        sort(a + i * m, a + i * m + m);
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int k =
                    lower_bound(a + i * m, a + i * m + m, ga(i - 1, j) - gdp(i - 1, j)) -
                    (a + i * m);
            int t =
                    upper_bound(a + i * m, a + i * m + m, ga(i - 1, j) + gdp(i - 1, j)) -
                    (a + i * m);
            if (k != m) {
                ev[k].push_back({{gdp(i - 1, j), j}, +1});
            }
            if (t != m) {
                ev[t].push_back({{gdp(i - 1, j), j}, -1});
            }
        }
        set<pair<int, int>> f;
        for (int j = 0; j < m; ++j) {
            f.insert({ga(i - 1, j), j});
        }
        multiset<int> cur;
        for (int j = 0; j < m; ++j) {
            for (auto e : ev[j]) {
                if (e.second == -1) {
                    f.insert({ga(i - 1, e.first.second), e.first.second});
                    cur.erase(cur.find(e.first.first));
                } else {
                    f.erase({ga(i - 1, e.first.second), e.first.second});
                    cur.insert(e.first.first);
                }
            }
            ev[j].clear();
            gdp(i, j) = max(gdp(i - 1, 0), abs(ga(i - 1, 0) - ga(i, j)));
            if (!cur.empty()) {
                gdp(i, j) = min(gdp(i, j), *cur.begin());
            }
            auto it = f.lower_bound({ga(i, j), -1});
            if (it != f.end()) {
                int k = it->second;
                gdp(i, j) =
                        min(gdp(i, j), max(gdp(i - 1, k), abs(ga(i - 1, k) - ga(i, j))));
            }
            if (it != f.begin()) {
                int k = (--it)->second;
                gdp(i, j) =
                        min(gdp(i, j), max(gdp(i - 1, k), abs(ga(i - 1, k) - ga(i, j))));
            }
        }
    }
}

void print_ans() {
    int ans = N;
    for (int j = 0; j < m; ++j) {
        ans = min(ans, gdp(n - 1, j));
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    scan();
    solve();
    print_ans();
    return 0;
}
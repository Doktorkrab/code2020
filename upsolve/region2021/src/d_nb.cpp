// Created by Nikolay Budin

#ifdef DEBUG
#  define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ff first
#define ss second
#define szof(x) ((int)x.size())
#ifndef LOCAL
#  define cerr __get_ce
#endif

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef unsigned long long ull;

using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF = (int)1e9 + 1e3;
ll const INFL = (ll)1e18 + 1e6;
#ifdef LOCAL
mt19937 tw(9450189);
#else
mt19937 tw(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif
uniform_int_distribution<ll> ll_distr;
ll rnd(ll a, ll b) { return ll_distr(tw) % (b - a + 1) + a; }


void solve() {
    int n;
    cin >> n;
    vector<pii> books;
    bool fl = false;
    int dist = -1;
    for (int i = 0; i < n; ++i) {
        int m, s;
        cin >> m >> s;
        vector<int> cur;
        for (int j = 0; j < m; ++j) {
            int pos;
            cin >> pos;
            cur.push_back(pos);
        }

        books.push_back({cur.front(), s - cur.back()});

        for (int j = 0; j + 1 < m; ++j) {
            int cur_dist = cur[j + 1] - cur[j];
            if (!fl) {
                dist = cur_dist;
                fl = true;
            } else {
                if (dist != cur_dist) {
                    cout << "No\n";
                    return;
                }
            }
        }
    }

    if (n == 1) {
        cout << "Yes\n";
        cout << "1\n";
        return;
    }

    vector<int> dist_vars;

    if (!fl) {
        vector<int> arr1, arr2;
        for (auto p : books) {
            arr1.push_back(p.ff);
            arr2.push_back(p.ss);
        }
        sort(arr1.begin(), arr1.end());
        sort(arr2.rbegin(), arr2.rend());
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                dist_vars.push_back(arr1[i] + arr2[j]);
            }
        }
    } else {
        dist_vars = {dist};
    }

    for (int d : dist_vars) {
        vector<vector<pii>> graph;
        map<int, int> inds;
        auto get_ind = [&](int val) {
            if (!inds.count(val)) {
                inds[val] = szof(graph);
                graph.push_back({});
            }
            return inds[val];
        };

        for (int i = 0; i < n; ++i) {
            int from = get_ind(d - books[i].ff);
            int to = get_ind(books[i].ss);
            graph[from].push_back({to, i});
        }

        vector<int> cnt_in(szof(graph));
        for (int i = 0; i < szof(graph); ++i) {
            for (auto to : graph[i]) {
                cnt_in[to.ff]++;
            }
        }

        bool ok = true;

        int in_ind = -1, out_ind = -1;

        for (int i = 0; i < szof(graph); ++i) {
            if (cnt_in[i] != szof(graph[i])) {
                if (cnt_in[i] + 1 == szof(graph[i])) {
                    if (in_ind != -1) {
                        ok = false;
                        break;
                    }
                    in_ind = i;
                } else if (cnt_in[i] == szof(graph[i]) + 1) {
                    if (out_ind != -1) {
                        ok = false;
                        break;
                    }
                    out_ind = i;
                } else {
                    ok = false;
                    break;
                }
            }
        }

        if (!ok) {
            continue;
        }

        int edges = n;

        if (in_ind != -1) {
            assert(out_ind != -1);
            graph[out_ind].push_back({in_ind, n});
            ++edges;
        }

        vector<bool> used(edges);
        vector<int> vcnt(szof(graph));
        vector<int> order;
        function<void(int)> dfs = [&](int v) {
            while (vcnt[v] < szof(graph[v])) {
                auto to = graph[v][vcnt[v]++];
                if (used[to.ss]) {
                    continue;
                }
                used[to.ss] = true;
                dfs(to.ff);
                order.push_back(to.ss);
            }
        };

        dfs(0);

        if (szof(order) != edges) {
            continue;
        }

        if (edges == n + 1) {
            rotate(order.begin(), find(order.begin(), order.end(), n), order.end());
            order.erase(order.begin());
        }

        cout << "Yes\n";
        reverse(order.begin(), order.end());
        for (int ind : order) {
            cout << ind + 1 << " ";
        }
        cout << "\n";
        return;
    }

    cout << "No\n";
}


int main() {
#ifdef LOCAL
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif
    cout << setprecision(15) << fixed;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count = 1;
    // cin >> test_count;
    for (int test = 1; test <= test_count; ++test) {
        solve();
    }

#ifdef LOCAL
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int)1e3 / CLOCKS_PER_SEC << " ms\n";
#endif
}
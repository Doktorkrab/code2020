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
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF = (int) 1e9 + 1e3;
ll const INFL = (ll) 1e18 + 1e6;
#ifdef LOCAL
mt19937 tw(9450189);
#else
mt19937 tw(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif
uniform_int_distribution<ll> ll_distr;

ll rnd(ll a, ll b) { return ll_distr(tw) % (b - a + 1) + a; }

struct point {
    int x, y;

    point(int _x, int _y) : x(_x), y(_y) {}

    bool operator<(point const &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

ostream &operator<<(ostream &o, point const &p) {
    o << "(" << p.x << ", " << p.y << ")";
    return o;
}

ll get_sq(point const &p1, point const &p2) {
    return (ll) abs(p1.x - p2.x) * abs(p1.y - p2.y);
}

pii minmax(pii a, pii b) {
    return {min(a.ff, b.ff), max(a.ss, b.ss)};
}

void solve() {
    int n;
    cin >> n;
    vector<point> points;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        points.push_back({x, y});
    }

    ll ans = INFL;

    for (int rot = 0; rot < 2; ++rot) {
        sort(points.begin(), points.end(), [&](auto &a, auto &b) {
            if (a.x != b.x) {
                return a.x < b.x;
            }
            return a.y < b.y;
        });
        vector<pii> pref = {{INF, -INF}}, suff = {{INF, -INF}};

        for (int i = 0; i < n; ++i) {
            pref.push_back(minmax(pref.back(), {points[i].y, points[i].y}));
            suff.push_back(minmax(suff.back(), {points[n - i - 1].y, points[n - i - 1].y}));
        }

        for (int i = 1; i <= n - 1; ++i) {
            ll val = (ll) (points[i - 1].x - points[0].x) * (pref[i].ss - pref[i].ff) +
                     (ll) (points[n - 1].x - points[i].x) * (suff[n - i].ss - suff[n - i].ff);
            ans = min(ans, val);
        }

        for (auto &p : points) {
            swap(p.x, p.y);
            p.x *= -1;
        }
    }

    if (ans == 0 || n == 1) {
        cout << "0\n";
        return;
    }

    {
        vector<vector<point>> parts(4);
        sort(points.begin(), points.end());
        for (auto p : points) {
            if (!szof(parts[0]) || parts[0].back().y < p.y) {
                parts[0].push_back(p);
            }
            if (!szof(parts[1]) || parts[1].back().y > p.y) {
                parts[1].push_back(p);
            }
        }

        for (int i = n - 1; i >= 0; --i) {
            auto &p = points[i];
            if (!szof(parts[2]) || parts[2].back().y < p.y) {
                parts[2].push_back(p);
            }
            if (!szof(parts[3]) || parts[3].back().y > p.y) {
                parts[3].push_back(p);
            }
        }
        for (int i = 0; i < 4; i++)
            cout << parts[i].size() << '\n';
        vector<point> tmp;
        for (int i = 0; i < 4; ++i) {
            tmp.insert(tmp.end(), parts[i].begin(), parts[i].end());
        }

        sort(tmp.begin(), tmp.end());

        vector<pii> pref = {{INF, -INF}}, suff = {{INF, -INF}};

        for (int i = 0; i < szof(tmp); ++i) {
            pref.push_back(minmax(pref.back(), {tmp[i].y, tmp[i].y}));
            suff.push_back(minmax(suff.back(), {tmp[szof(tmp) - i - 1].y, tmp[szof(tmp) - i - 1].y}));
        }

        for (int i = 0; i < szof(tmp); ++i) {
            int maxx = min(tmp[i].x + ans / (pref.back().ss - pref.back().ff), (ll) INF);
            for (int j = lower_bound(tmp.begin(), tmp.end(), point(maxx + 1, -INF)) - tmp.begin(); j < szof(tmp); ++j) {
                if (i == 0 && j == szof(tmp) - 1) {
                    continue;
                }
                pii q = minmax(pref[i], suff[szof(tmp) - 1 - j]);
                if ((ll) (tmp.back().x - tmp[0].x) * (q.ss - q.ff) >= ans) {
                    break;
                }
                ans = min(ans, (ll) (tmp.back().x - tmp[0].x) * (q.ss - q.ff) +
                               (ll) (tmp[j].x - tmp[i].x) * (pref.back().ss - pref.back().ff));
            }
        }
    }

    for (int flip = 0; flip < 2; ++flip) {
        sort(points.begin(), points.end());

        vector<vector<point>> parts(2);
        for (int i = 0; i < n; ++i) {
            if (!szof(parts[0]) || parts[0].back().y < points[i].y) {
                parts[0].push_back(points[i]);
            }
        }

        for (int i = n - 1; i >= 0; --i) {
            if (!szof(parts[1]) || parts[1].back().y > points[i].y) {
                parts[1].push_back(points[i]);
            }
        }
        reverse(parts[1].begin(), parts[1].end());

        for (int i = 0; i < szof(parts[0]) - 1; ++i) {
            for (int j = 0; j < szof(parts[1]) - 1; ++j) {
                if ((ll) (parts[1][j].x - parts[0][0].x) * (parts[0][i].y - parts[1][0].y) >= ans) {
                    break;
                }
                if (parts[0][i].y >= parts[1][j + 1].y && parts[0][i + 1].x <= parts[1][j].x) {
                    ll val = (ll) (parts[1][j].x - parts[0][0].x) * (parts[0][i].y - parts[1][0].y) +
                             (ll) (parts[1].back().x - parts[0][i + 1].x) * (parts[0].back().y - parts[1][j + 1].y);
                    ans = min(ans, val);
                }
            }
        }

        for (auto &p : points) {
            p.y *= -1;
        }
    }

    cout << ans << "\n";
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
    cin >> test_count;
    for (int test = 1; test <= test_count; ++test) {
        solve();
    }

#ifdef LOCAL
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif
}
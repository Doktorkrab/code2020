#include<bits/stdc++.h>

using namespace std;
#define int long long
#define ii pair <int, int>
#define app push_back
#define all(a) a.begin(), a.end()
#define bp __builtin_popcountll
#define ll long long
#define mp make_pair
#define x first
#define y second
#define Time (double)clock()/CLOCKS_PER_SEC
#define debug(x) std::cout << #x << ": " << x << '\n';
#define FOR(i, n) for (int i = 0; i < n; ++i)
#define pb push_back
#define trav(a, x) for (auto& a : x)
using vi = vector<int>;

template<typename T>
std::ostream &operator<<(std::ostream &output, const pair<T, T> &data) {
    output << "(" << data.x << "," << data.y << ")";
    return output;
}

template<typename T>
std::ostream &operator<<(std::ostream &output, const std::vector<T> &data) {
    for (const T &x : data)
        output << x << " ";
    return output;
}
//ll div_up(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
//ll div_down(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
#define tcT template<class T
#define tcTU tcT, class U
tcT> using V = vector<T>;

tcT> void re(V<T> &x) {
    trav(a, x)cin >> a;
}

tcT> bool ckmin(T &a, const T &b) {
    return b < a ? a = b, 1 : 0;
} // set a = min(a,b)
tcT> bool ckmax(T &a, const T &b) {
    return a < b ? a = b, 1 : 0;
}

mt19937 rnd(2007);

int get(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

int inc_ub(vi &a, int x) { //first bigger than x
    return upper_bound(all(a), x) - a.begin();
}

int dec_ub(vi &a, int x) { //first less than x
    int l = -1, r = a.size();
    while (l < r - 1) {
        int m = (l + r) >> 1;
        if (a[m] < x)
            r = m;
        else
            l = m;
    }
    return r;
}

const int C = 1e9 + 7, INF = 2e18;
namespace Non_intersecting {
    int solve(V<ii > a) {
        int n = a.size();
        if (n <= 2)
            return 0;
        int ans = INF;
        FOR (t, 2) {
            sort(all(a));
            vi pref_min(n + 1, C), pref_max(n + 1, 0), post_min(n + 1, C), post_max(n + 1, 0);
            for (int i = 0; i < n; ++i) {
                pref_min[i + 1] = min(pref_min[i], a[i].y);
                pref_max[i + 1] = max(pref_max[i], a[i].y);
            }
            for (int i = n - 1; i >= 0; --i) {
                post_min[i] = min(post_min[i + 1], a[i].y);
                post_max[i] = max(post_max[i + 1], a[i].y);
            }
            ckmin(ans, (pref_max[n] - pref_min[n]) * (a.back().x - a[0].x)); // one rectangle
            for (int l = 1; l < n; ++l) {
                ckmin(ans, (pref_max[l] - pref_min[l]) * (a[l - 1].x - a[0].x) +
                           (post_max[l] - post_min[l]) * (a.back().x - a[l].x));
            }
            FOR (i, n)swap(a[i].x, a[i].y);
        }
        return ans;
    }
};
namespace Intersecting {
    using nagai = long long;
#define fi first
#define se second

    constexpr nagai oo = 0x3f3f3f3f3f3f3f3f;

    struct cht {
        vector<pair<nagai, nagai>> coef;
        vector<double> from;

        void clear() {
            coef.clear();
            from.clear();
        }

        void add(pair<nagai, nagai> nw) {
            while (coef.size() && coef.back().fi == nw.fi)
                coef.pop_back(), from.pop_back();
            double x = -1e228;
            while (coef.size() && (x = (double) (nw.se - coef.back().se) / (coef.back().fi - nw.fi)) < from.back())
                coef.pop_back(), from.pop_back();
            coef.push_back(nw);
            from.push_back(x);
        }

        nagai get(nagai k, nagai l) {
            if (!coef.size()) return oo;
            if (l == 0)
                return coef.back().fi * k;
            int ind = upper_bound(from.begin(), from.end(), (double) k / l) - from.begin() - 1;
            return coef[ind].fi * k + coef[ind].se * l;
        }
    };

    const int N = 1 << 18;
    cht it[2 * N];

    void build(int n) {
        vector<int> interesting;
        for (int i = 0; i < n; ++i) {
            for (int x = (N + i) / 2; x > 0; x /= 2)
                interesting.push_back(x);
        }
        sort(interesting.rbegin(), interesting.rend());
        interesting.erase(unique(interesting.begin(), interesting.end()), interesting.end());
        for (int i : interesting) {
            it[i].clear();
            vector<pair<nagai, nagai>> v;
            for (auto rofl : it[2 * i].coef)
                v.push_back(rofl);
            for (auto rofl : it[2 * i + 1].coef)
                v.push_back(rofl);
            sort(v.rbegin(), v.rend());
            for (auto rofl : v)
                it[i].add(rofl);
        }
    }

    nagai get(int l, int r, nagai a, nagai b) {
        l += N;
        r += N;
        nagai ans = oo;
        while (l < r) {
            if (l & 1)
                ans = min(ans, it[l++].get(a, b));
            if (r & 1)
                ans = min(ans, it[--r].get(a, b));
            l /= 2, r /= 2;
        }
        return ans;
    };

    using pt = pair<int, int>;

    nagai solve1(vector<pt> v) {
        int n = v.size();

        for (int i = 0; i < n; ++i) {
            it[N + i].clear();
        }

        auto vx = v, vy = v;
        sort(vx.begin(), vx.end());
        sort(vy.begin(), vy.end(), [&](auto a, auto b) {
            return a.se < b.se;
        });
        int mnx = vx[0].fi, mxx = vx.back().fi, mny = vy[0].se, mxy = vy.back().se;
        vector<int> sufxy(n + 1), sufyx(n + 1);
        sufxy[n] = mxy;
        for (int i = n - 1; i >= 0; --i)
            sufxy[i] = min(sufxy[i + 1], vx[i].se);
        sufyx[n] = mxx;
        for (int i = n - 1; i >= 0; --i)
            sufyx[i] = min(sufyx[i + 1], vy[i].fi);
        for (int i = 0; i < n; ++i) {
            it[N + i].add({vy[i].se - mny, mxx - sufyx[i + 1]});
        }
        build(n);
        nagai ans = oo;
        int ptr = n;
        int le = n;
        int ri = n;
        for (int i = n - 1; i >= 0; --i) {
            // vy[k].se >= sufxy[i + 1]
            while (le > 0 && vy[le - 1].se >= sufxy[i + 1]) --le;
            while (ri > 0 && sufyx[ri] > vx[i].fi) --ri;
            /*
        while(ptr > 0 && vy[ptr - 1].se >= sufxy[i + 1]) {
          --ptr;
          int rofl = sufyx[ptr + 1];
          int ind = lower_bound(vx.begin(),vx.end(),make_pair(rofl, -(int)2e9)) - vx.begin();
          it[N + ind].add({vy[ptr].se - mny, mxx - sufyx[ptr + 1]});
    //      cerr << "add " << ind << ' ' << vy[ptr].se - mny << ' ' << mxx - sufyx[ptr+1] << '\n';
        }
        build(n);
            */
            // �������� ������ ������� ������� ���� ��� sufxy[i + 1]
            nagai k = vx[i].fi - mnx;
            nagai l = mxy - sufxy[i + 1];
            ans = min(ans, get(le, ri, k, l));
//    ans = min(ans, rofl.get(k, l));
//    cerr << k << ' ' << l << ' ' << ans << '\n';
        }
        return ans;
    }

    nagai solve2(vector<pt> v) {
        nagai ans = solve1(v);
        for (auto &x:v)
            x.fi *= -1;
        ans = min(ans, solve1(v));
        return ans;
    }
};
namespace Cross {
    const int C = 1e9 + 7, INF = 2e18;

    struct Rmq {
        const int INF = 2e18; //need long long for inf
        vi rmq;
        int sz;

        Rmq() {}

        Rmq(int n) {
            sz = 1;
            while (sz < n) sz *= 2;
            rmq.assign(sz * 2, 0);
        }

        void put(int i, int x) {
            i += sz;
            rmq[i] += x;
            for (i /= 2; i; i /= 2) {
                rmq[i] = min(rmq[i * 2], rmq[i * 2 + 1]);
            }
        }

        int get(int l, int r) {
            l += sz;
            r += sz;
            int res = INF;
            while (l < r) {
                if (l % 2 == 1) res = min(res, rmq[l]);
                if (r % 2 == 0) res = min(res, rmq[r]);
                l = (l + 1) / 2;
                r = (r - 1) / 2;
            }
            if (l == r) res = min(res, rmq[l]);
            return res;
        }
    };

    int solve(V<ii > a) {
        int n = a.size();
        int L = C, R = 0, D = C, U = 0;
        trav (p, a) {
            ckmin(L, p.x);
            ckmax(R, p.x);
            ckmin(D, p.y);
            ckmax(U, p.y);
        }
        int H = R - L;
        int W = U - D;
        trav (p, a) {
            p.x -= L;
            p.y -= D;
        }
        int ans = INF;
        FOR (t, 2) {
            sort(all(a));
            vi pref_max(n + 1), pref_min(n + 1, U);
            FOR (i, n) {
                pref_max[i + 1] = max(pref_max[i], a[i].y);
                pref_min[i + 1] = min(pref_min[i], a[i].y);
            }
            Rmq d(n);
            FOR (i, n) {
                d.put(i, -a[i].x * W - pref_min[i] * H);
            }
            int cur_up = 0, cur_down = U;
            for (int i = n - 1; i >= 0; --i) {
                if (i < n - 1) {
                    int R = a[i].x;
                    int r = inc_ub(pref_max, cur_up); //first bad
                    int l = dec_ub(pref_min, cur_down); //first change
                    int p = min({l - 1, r - 1, i});
                    assert(p >= 0);
                    int L = a[p].x;
                    ckmin(ans, (R - L) * W + (cur_up - cur_down) * H);
                    r = min(r - 1, i);
                    if (l <= r) {
                        ckmin(ans, R * W + cur_up * H + d.get(l, r));
                    }
                }
                ckmax(cur_up, a[i].y);
                ckmin(cur_down, a[i].y);
            }
            trav (p, a) {
                p.x = H - p.x;
            }
        }
        return ans;
    }
};

signed main() {
#ifdef HOME
    freopen("test.txt", "w", stdout);
#else
#define endl '\n'
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        V<ii > a(n);
        FOR (i, n) {
            cin >> a[i].x >> a[i].y;
        }
        int a1 = Non_intersecting::solve(a);
        int b = Intersecting::solve2(a);
        int c = Cross::solve(a);
        int ans = min(a1, min(b, c));
        assert(ans == a1);
        cout << ans << endl;
    }
}

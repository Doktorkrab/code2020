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
#define int ll

int n, k;
const int MAXN = 2e5 + 7;
const int INF = 1e18 + 42;
struct Segment {
    int l, r, w, d;

    bool operator<(const Segment &oth) const {
        return tie(w, l, r, d) < tie(oth.w, oth.l, oth.r, oth.d);
    }

    bool operator>(const Segment &oth) const {
        return oth < (*this);
    }
};

Segment segments[MAXN];

const int UPD = -1, OPEN = 0, CLOSE = 1;

struct Event {
    int l = 0;
    int type = -1;
    int index = -1;

    Event() = default;

    Event(int l, int type, int index) : l(l), type(type), index(index) {}

    bool operator<(const Event &oth) const {
        return tie(l, type, index) < tie(oth.l, oth.type, oth.index);
    }

    bool operator>(const Event &oth) const {
        return tie(l, type, index) > tie(oth.l, oth.type, oth.index);
    }
};

struct SegmentTree {
    int N = 0;
    int tree[4 * MAXN]{};

    explicit SegmentTree(int sz) {
        N = 1;
        while (N < sz)
            N *= 2;
        clear();
    }

    SegmentTree() = default;

    void clear() {
        fill(tree, tree + 2 * N, INF);
    }

    void upd(int v, int tl, int tr, int pos, int x) {
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1) {
            tree[v] = x;
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, x);
        upd(v * 2 + 1, tm, tr, pos, x);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }

    void upd(int pos, int x) {
        upd(1, 0, N, pos, x);
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (tr <= l || r <= tl)
            return INF;
        if (l <= tl && tr <= r)
            return tree[v];
        int tm = (tl + tr) / 2;
        return min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }

    int get(int x) {
        int pos = upper_bound(segments, segments + n, Segment{k + 1, k + 1, x, 0}) - segments;
        return get(1, 0, N, 0, pos);
    }
};

SegmentTree st;
map<int, int> borders;

int get(int pos, int w) {
    if (borders.count(pos) && borders[pos] > 0)
        return pos;
    return st.get(w);
}

bool check(int x) {
    priority_queue<Event, vector<Event>, greater<Event>> events;
    borders.clear();
    st.clear();
    for (int i = 0; i < n; i++)
        if (segments[i].w <= x)
            events.emplace(segments[i].l, UPD, i);
    while (SZ(events)) {
        auto e = events.top();
        auto &seg = segments[e.index];
        events.pop();
        if (e.type == UPD) {
            if (seg.l == 1) {
                seg.d = 0;
            } else {
                seg.d = INF;
                int tmp = get(seg.l - 1, x - seg.w);
                if (tmp < seg.r)
                    seg.d = tmp;
            }

            if (seg.d != INF) {
                events.emplace(seg.d, OPEN, e.index);
                events.emplace(seg.r + 1, CLOSE, e.index);
                if (seg.r == k)
                    return true;
            }
        }
        if (e.type == OPEN) {
            borders[seg.r]++;
            st.upd(e.index, seg.r);
        }
        if (e.type == CLOSE) {
            borders[seg.r]--;
            st.upd(e.index, INF);
        }
    }
    return false;
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> segments[i].l >> segments[i].r >> segments[i].w;
    sort(segments, segments + n);
    st = SegmentTree(n);
    int l = 0, r = INF;
//    cout << check(6) << '\n';
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (check(m))
            r = m;
        else
            l = m;
    }
    if (r == INF)
        cout << "-1\n";
    else
        cout << r << '\n';
    return 0;
}

signed main() {
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

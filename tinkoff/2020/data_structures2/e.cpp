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

int n, k;
const int ADD = -1, ASK = 0, DELETE = 1;
const int MAXN = 3e5 + 7;
struct Event {
    int type = ADD, v = 0, u = 1, pair = -MAXN;  // v < u
};
struct Rollback {
    int a, b, sz, p, addition;
};
Event events[MAXN];
map<pair<int, int>, int> last_added;

int p[MAXN], sz[MAXN];
int ans[MAXN];

int get(int a) {
    if (p[a] == a)
        return a;
    return get(p[a]);
}

vector<Rollback> rollbacks;
int comps = 0;

inline void un(int a, int b) {
    a = get(a);
    b = get(b);
    if (sz[a] > sz[b])
        swap(a, b);
    rollbacks.push_back({a, b, sz[b], p[a], a != b});
    if (a == b)
        return;
    comps--;
    p[a] = b;
    sz[b] += sz[a];
}

inline void rollback() {
    assert(SZ(rollbacks) > 0);
    auto[a, b, ss, pp, add] = rollbacks.back();
    comps += add;
    rollbacks.pop_back();
    p[a] = pp;
    sz[b] = ss;
}

void div_and_conq(int l, int r) {
    if (r - l < 1)
        return;
    if (r - l == 1) {
        if (events[l].type == ASK)
            ans[events[l].pair] = comps;
        return;
    }
    int m = (l + r) / 2;
    for (int i = l; i < m; i++)
        if (events[i].type == ADD && events[i].pair >= r)
            un(events[i].v, events[i].u);
    div_and_conq(m, r);

    for (int i = l; i < m; i++)
        if (events[i].type == ADD && events[i].pair >= r)
            rollback();

    for (int i = m; i < r; i++)
        if (events[i].type == DELETE && events[i].pair < l)
            un(events[i].v, events[i].u);
    div_and_conq(l, m);

    for (int i = m; i < r; i++)
        if (events[i].type == DELETE && events[i].pair < l)
            rollback();
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    int pnt = 0;
    comps = n;
    for (int i = 0; i < n; i++) {
        sz[i] = 1;
        p[i] = i;
    }
    for (int i = 0; i < k; i++) {
        char c;
        cin >> c;
        if (c == '?') {
            events[i].type = ASK;
            events[i].pair = pnt++;
            continue;
        }
        int v, u;
        cin >> v >> u;
        --v, --u;
        if (v > u)
            swap(v, u);
        events[i].v = v;
        events[i].u = u;
        if (c == '+') {
            events[i].type = ADD;
            events[i].pair = MAXN;
            last_added[{v, u}] = i;
        } else {
            events[i].type = DELETE;
            events[last_added[{v, u}]].pair = i;
            events[i].pair = last_added[{v, u}];
        }
    }
    div_and_conq(0, k);
    for (int i = 0; i < pnt; i++)
        cout << ans[i] << '\n';
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

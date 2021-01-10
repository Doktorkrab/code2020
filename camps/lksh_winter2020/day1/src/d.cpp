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
enum {
    ADD, DELETE, ASK
};

int n, m;
const int MAXN = 3e5 + 7;
struct Query {
    int type = 0, v = 0, u = 0;
    int index = -1;
    int pair = -1;
    Query() {}
    Query(int a, int b, int c, int d, int e) : type(a), v(b), u(c), index(d), pair(e) {}
};

struct Rollback {
    int a, b, p, sz, add;
};

int ans[MAXN];
int sz[MAXN];
int p[MAXN];
vector<Rollback> rollbacks;
Query queries[MAXN];

int find_set(int v) {
    if (v == p[v])
        return v;
    return find_set(p[v]);
}

int cnt = 0;

int un(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (sz[a] > sz[b])
        swap(a, b);

    rollbacks.push_back({a, b, p[a], sz[b], a != b});
    if (a == b)
        return 0;
    cnt--;
    sz[b] += sz[a];
    p[a] = b;
    return 1;
}

void do_rollback() {
    assert(!rollbacks.empty());
    auto[a, b, pp, ssz, add] = rollbacks.back();
    rollbacks.pop_back();
    sz[b] = ssz;
    p[a] = pp;
    cnt += add;
}

void rec(int tl, int tr) {
    if (tr - tl == 1) {
        if (queries[tl].type == ASK)
            ans[queries[tl].index] = cnt;
        return;
    }
    if (tr - tl < 1)
        return;
    int rl = 0;
    int tm = (tl + tr) / 2;
    for (int i = tl; i < tm; i++) {
        if (queries[i].type == ADD && queries[i].pair >= tr)
            un(queries[i].v, queries[i].u);
    }
    rec(tm, tr);
    for (int i = tl; i < tm; i++) {
        if (queries[i].type == ADD && queries[i].pair >= tr)
            do_rollback();
    }
    for (int i = tm; i < tr; i++) {
        if (queries[i].type == DELETE && queries[i].pair < tl)
            un(queries[i].v, queries[i].u);
    }
    rec(tl, tm);
    for (int i = tm; i < tr; i++) {
        if (queries[i].type == DELETE && queries[i].pair < tl)
            do_rollback();
    }
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    cnt = n;
    for (int i = 0; i < n; i++) {
        p[i] = i;
        sz[i] = 1;
    }
    map<pair<int, int>, int> last;
    int ask_cnt = 0;
    for (int i = 0; i < m; i++) {
        char x;
        cin >> x;
        if (x == '+') {
            int v, u;
            cin >> v >> u;
            --v, --u;
            if (v > u)
                swap(v, u);
            queries[i] = Query{ADD, v, u, i, TMAX(int)};
            last[{v, u}] = i;
        }
        if (x == '-') {
            int v, u;
            cin >> v >> u;
            --v, --u;
            if (v > u)
                swap(v, u);
            queries[i] = Query{DELETE, v, u, i, last[{v, u}]};
            queries[last[{v, u}]].pair = i;
        }
        if (x == '?')
            queries[i] = Query{ASK, -1, -1, ask_cnt++, -1};
    }
    rec(0, m);
    for (int i = 0; i < ask_cnt; i++)
        cout << ans[i] << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
#else
    //    freopen("multiply.in", "r", stdin);
    //    freopen("multiply.out", "w", stdout);
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

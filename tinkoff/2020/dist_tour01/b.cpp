#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ostream>

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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
mt19937 rnd(566);

struct Node {
    int x, y, sz;
    int left = 0;
    int right = 0;

    explicit Node(int _x) : x(_x), y(rnd()), sz(1) {}

    Node() = default;
};

const int MAXC = 5e6 + 7;
Node nodes[MAXC];
int pnt = 1;

int new_Node(int x) {
    assert(pnt < MAXC);
    nodes[pnt] = Node(x);
    return pnt++;
}

int safe_sz(int a) {
    return (a ? nodes[a].sz : 0);
}

int recalc(int a) {
    nodes[a].sz = safe_sz(nodes[a].left) + 1 + safe_sz(nodes[a].right);
    return a;
}


pair<int, int> split(int a, int key) { // (-inf; x] (x; +inf)
    if (!a)
        return {0, 0};
    if (nodes[a].x <= key) {
        auto tmp = split(nodes[a].right, key);
        nodes[a].right = tmp.first;
        return {recalc(a), tmp.second};
    }
    auto tmp = split(nodes[a].left, key);
    nodes[a].left = tmp.second;
    return {tmp.first, recalc(a)};
}

int insert(int a, int y) {
    if (safe_sz(a) == 0)
        return y;
    if (nodes[a].y < nodes[y].y) {
        auto t = split(a, nodes[y].x);
        nodes[y].left = t.first;
        nodes[y].right = t.second;
        return recalc(y);
    }
    if (nodes[a].x > nodes[y].x) {
        nodes[a].left = insert(nodes[a].left, y);
        return recalc(a);
    }
    nodes[a].right = insert(nodes[a].right, y);
    return recalc(a);
}

int gt(int root, int k) {
    if (safe_sz(root) == 0)
        return 0;
    if (nodes[root].x > k)
        return gt(nodes[root].left, k) + 1 + safe_sz(nodes[root].right);
    return gt(nodes[root].right, k);
}

int n;
const int MAXN = 2e5 + 7;
vector<int> g[MAXN];
ll ans[MAXN];
int have[MAXN];

int merge(int a, int b) {
    if (safe_sz(b) == 0)
        return a;
    if (safe_sz(b) > safe_sz(a))
        return merge(b, a);
    a = insert(a, new_Node(nodes[b].x));
    a = merge(a, nodes[b].left);
    a = merge(a, nodes[b].right);
    return a;
}

ll calc_ans(int a, int b) {
    if (safe_sz(b) == 0)
        return 0;
    if (safe_sz(b) > safe_sz(a))
        return safe_sz(b) * 1LL * safe_sz(a) - calc_ans(b, a);
    return calc_ans(a, nodes[b].left) + gt(a, nodes[b].x) + calc_ans(a, nodes[b].right);
}

void print(int x) {
    if (!x)
        return;
    print(nodes[x].left);
    cout << nodes[x].x << ' ';
    print(nodes[x].right);
}

ll dfs(int v) {
    have[v] = new_Node(v + 1);
    for (int u : g[v]) {
        ans[v] += dfs(u);
//        cout << v + 1 << ' ' << u + 1 << ": ";
//        print(have[v]);
//        cout << '\n';

        ans[v] += calc_ans(have[v], have[u]);
        have[v] = merge(have[v], have[u]);
//        print(have[v]);
//        cout << '\n';
    }
    return ans[v];
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        g[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> g[i][j];
            g[i][j]--;
        }
    }
    dfs(0);
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
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

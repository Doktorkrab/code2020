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
struct Node {
    int left = 0, right = 0;
    int mx = 0;
};

const int MAXNODE = 1.7e7;
const int MAXN = 2.5e5 + 7;
const int MAXLOG = 23;
Node *nodes;
int ones[MAXLOG];
int pnt = 1;

int new_node(int x = 0) {
    assert(pnt < MAXNODE);
    nodes[pnt].mx = x;
    nodes[pnt].left = nodes[pnt].right = 0;
    return pnt++;
}

int build(int tl, int tr) {
    int node = new_node(0);
    if (tr - tl == 1)
        return node;
    int tm = (tl + tr) / 2;
    nodes[node].left = build(tl, tm);
    nodes[node].right = build(tm, tr);
    return node;
}

inline void build_ones() {
    ones[0] = new_node(1);
    for (int i = 1; i < MAXLOG; i++) {
        ones[i] = new_node(1);
        nodes[ones[i]].left = ones[i - 1];
        nodes[ones[i]].right = ones[i - 1];
    }
}

int upd(int v, int tl, int tr, int pos, int x) {
    if (pos < tl || tr <= pos)
        return v;
    int node = new_node(0);
    if (tr - tl == 1) {
        nodes[node].mx = x;
        return node;
    }
    int tm = (tl + tr) / 2;
    nodes[node].left = upd(nodes[v].left, tl, tm, pos, x);
    nodes[node].right = upd(nodes[v].right, tm, tr, pos, x);
    nodes[node].mx = max(nodes[nodes[node].left].mx, nodes[nodes[node].right].mx);
    return node;
}

int get(int v, int tl, int tr, int l, int r) {
    if (nodes[v].mx < 1 || tr <= l || r <= tl)
        return -1;
    if (tr - tl == 1)
        return tl;
    int tm = (tl + tr) / 2;
    int ret = get(nodes[v].right, tm, tr, l, r);
    if (ret == -1)
        return get(nodes[v].left, tl, tm, l, r);
    return ret;
}

int get_el(int v, int tl, int tr, int pos) {
    if (tr - tl == 1)
        return nodes[v].mx;
    int tm = (tl + tr) / 2;
    if (pos < tm)
        return get_el(nodes[v].left, tl, tm, pos);
    return get_el(nodes[v].right, tm, tr, pos);
}

int push_one(int v, int tl, int tr, int l, int r) {
    if (r - l < 1)
        return v;
    if (tr <= l || r <= tl)
        return v;
    if (l <= tl && tr <= r) {
        int len = tr - tl;
        int sz = 0;
        while ((1LL << sz) < len)
            sz++;
        return ones[sz];
    }
    int tm = (tl + tr) / 2;
    int node = new_node();
    nodes[node].left = push_one(nodes[v].left, tl, tm, l, r);
    nodes[node].right = push_one(nodes[v].right, tm, tr, l, r);
    nodes[node].mx = max(nodes[nodes[node].left].mx, nodes[nodes[node].right].mx);
    return node;
}

struct Creature {
    int attack = 1;
    int shift = 1;  // [0; shift)
    int root = 0;
    int dead_move = -1;
};
int N = 1;
Creature creatures[MAXN];

void kill_c(int pos, int att, int move) {
    int one_pos = get(creatures[pos].root, 0, N, 0, creatures[pos].shift - att + 1);
    if (one_pos == -1) {
        creatures[pos].dead_move = move;
        return;
    }
    creatures[pos].root = upd(creatures[pos].root, 0, N, one_pos, 0);
    creatures[pos].root = push_one(creatures[pos].root, 0, N, one_pos + 1, creatures[pos].shift - att + 1);
    one_pos = get(creatures[pos].root, 0, N, 0, creatures[pos].shift);
    if (one_pos == -1)
        creatures[pos].dead_move = move;
}

int solve() {
    nodes = new Node[MAXNODE];
    pnt = 1;
    build_ones();
    if (!(cin >> n))
        return 1;
    int now = 0;
    N = 1;
    while (N < 2 * n)
        N *= 2;
    int one_hp = build(0, N);
    one_hp = upd(one_hp, 0, N, 0, 1);
    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        int x;
        if (type == 1) {
            creatures[now++] = {1, 1, one_hp, -1};
            continue;
        }

        cin >> x;
        x--;
        if (type == 2)
            creatures[x].attack++;
        if (type == 3)
            creatures[x].shift++;
        if (type == 4) {
            creatures[now] = creatures[x];
            if (creatures[now].dead_move != -1)
                creatures[now].dead_move = i + 1;
            now++;
        }
        if (type == 5) {
            int y;
            cin >> y;
            --y;
            if (creatures[x].dead_move != -1 || creatures[y].dead_move != -1)
                continue;
            kill_c(x, creatures[y].attack, i + 1);
            kill_c(y, creatures[x].attack, i + 1);
        }
    }
    cout << now << '\n';
    for (int i = 0; i < now; i++)
        cout << creatures[i].dead_move << " \n"[i + 1 == now];
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

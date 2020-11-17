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

struct Node {
    int left = 0;
    int right = 0;
    int val = 0;
    int sz = 0;
    ll prior = 0;
    int mod = 0;
};
const int MAXNODE = 5e6;
Node *nodes;
mt19937 rnd(239);
int pnt = 1;

int new_node(int val = 0) {
    assert(pnt < MAXNODE);
    nodes[pnt].val = val;
    nodes[pnt].sz = 1;
    nodes[pnt].prior = rnd();
    return pnt++;
}

void push(int a) {
    if (!a || nodes[a].mod == 0)
        return;
    auto &x = nodes[a];
    x.val += x.mod;
    if (x.left)
        nodes[x.left].mod += x.mod;
    if (x.right)
        nodes[x.right].mod += x.mod;
    x.mod = 0;
}

int recalc(int a) {
    if (!a)
        return a;
    auto &x = nodes[a];
    x.sz = nodes[x.left].sz + 1 + nodes[x.right].sz;
    return a;
}

int merge(int a, int b) {
    push(a);
    push(b);
    if (!a)
        return b;
    if (!b)
        return a;
    if (nodes[a].prior < nodes[b].prior) {
        nodes[a].right = merge(nodes[a].right, b);
        return recalc(a);
    }
    nodes[b].left = merge(a, nodes[b].left);
    return recalc(b);
}

void print(int a) {
    if (!a)
        return;
    push(a);
    print(nodes[a].right);
    if (nodes[a].val != 0)
        cout << nodes[a].val << ' ';
    print(nodes[a].left);
}

pair<int, int> split(int a, int x) {
    if (!a)
        return {0, 0};
    push(a);
    if (nodes[nodes[a].left].sz >= x) {
        auto t = split(nodes[a].left, x);
        nodes[a].left = t.second;
        return {t.first, recalc(a)};
    }
    auto t = split(nodes[a].right, x - nodes[nodes[a].left].sz - 1);
    nodes[a].right = t.first;
    return {recalc(a), t.second};
}

int less_than(int a, int x) {
    if (!a)
        return 0;
    push(a);
    if (nodes[a].val >= x)
        return less_than(nodes[a].right, x);
    return 1 + less_than(nodes[a].left, x) + nodes[nodes[a].right].sz;
}

void push_seg(int &a, int x, int y) {
    auto t = split(a, x);
    nodes[t.first].mod += y;
    push(t.first);
    a = merge(t.first, t.second);
}

void insert(int &a, int x) {
    int cnt = nodes[a].sz - less_than(a, x);
    int node = new_node(x);
    auto t = split(a, cnt);
    a = merge(t.first, merge(node, t.second));
}

int cnt_remove(int a, int x, bool &find) {
    if (!a)
        return 0;
    push(a);
    if (nodes[a].val == x) {
        find = true;
        return nodes[nodes[a].left].sz;
    }
    if (nodes[a].val < x)
        return cnt_remove(nodes[a].left, x, find);
    return 1 + nodes[nodes[a].left].sz + cnt_remove(nodes[a].right, x, find);
}

void remove(int &a, int x, bool& flag) {
    int cnt = cnt_remove(a, x, flag);
    if (!flag)
        return;
    auto t = split(a, cnt + 1);
    auto t1 = split(t.first, cnt);
    a = merge(t1.first, t.second);
}

const int MAXN = 5e5 + 5;
int n, q;
int arr[MAXN];


int solve() {
    nodes = new Node[MAXNODE];
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
    reverse(arr, arr + n);
    int treaps[2] = {0, 0};
    unsigned cur = 0;
    for (int i = 0; i < MAXN; i++) {
        int x = new_node(0);
        treaps[cur ^ 1U] = merge(treaps[cur ^ 1U], x);
    }
    for (int i = 0; i < n; i++) {
        int x = new_node(arr[i]);
        treaps[cur] = merge(treaps[cur], x);
        push_seg(treaps[cur ^ 1U], arr[i], 1);
//        print(treaps[cur ^ 1U]);
//        cout << '\n';
    }
    for (int i = 0; i < MAXN; i++)
        treaps[cur] = merge(treaps[cur], new_node(0));
    for (int i = 0; i < q; i++) {
        char t;
        cin >> t;
        if (t == 't') {
            cur ^= 1U;
            continue;
        }
        int x;
        cin >> x;

        if (t == 'a') {
            insert(treaps[cur], x);
            push_seg(treaps[cur ^ 1U], x, 1);
        }
        if (t == 'r') {
            bool flag = false;
            remove(treaps[cur], x, flag);
            if (flag)
                push_seg(treaps[cur ^ 1U], x, -1);
        }
        if (t == 'c') {
            cout << less_than(treaps[cur], x + 1) - less_than(treaps[cur], x) << '\n';
        }
    }

    print(treaps[cur]);
//    cout << '\n';
    return 1;
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

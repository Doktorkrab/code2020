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
 
int n, q;

const int MAXNODE = 1e6;
mt19937 rnd(239);

struct Treap{
    struct Node{
        int x{}, y{};
        ll sum = 0;
        int l = -1, r = -1;
        int sz = 1;
        int push = 0;
        Node() {}
        explicit Node(int x) : x(x), sum(x), y(rnd()) {}
    };
    Node nodes[MAXNODE];
    int root = -1;
    int pnt = 0;
    int new_node(int a){
        assert(pnt < MAXNODE);
        nodes[pnt] = Node(a);
        return pnt++;
    }
    int safe_sz(int a){
        return (a != -1 ? nodes[a].sz : 0);
    }
    ll safe_sum(int a){
        return (a != -1 ? nodes[a].sum : 0);
    }

    int recalc(int a){
        nodes[a].sz = 1 + safe_sz(nodes[a].l) + safe_sz(nodes[a].r);
        nodes[a].sum = nodes[a].x + safe_sum(nodes[a].l) + safe_sum(nodes[a].r);
        return a;
    }

    void push(int x){
        if (nodes[x].push){
            swap(nodes[x].l, nodes[x].r);
            if (nodes[x].l != -1)
                nodes[nodes[x].l].push ^= 1;
            if (nodes[x].r != -1)
                nodes[nodes[x].r].push ^= 1;
            nodes[x].push = 0;
        }
    }

    int merge(int a, int b){
        if (a == -1)
            return b;
        if (b == -1)
            return a;
        push(a);
        push(b);
        Node& na = nodes[a];
        Node& nb = nodes[b];
        if (na.y > nb.y){
            na.r = merge(na.r, b);
            return recalc(a);
        }
        nb.l = merge(a, nb.l);
        return recalc(b);
    }
    pair<int, int> split(int a, int k){
        if (a == -1)
            return {-1, -1};
        push(a);
        Node& x = nodes[a];
        if (safe_sz(x.l) + 1 <= k){
            auto res = split(x.r, k - safe_sz(x.l) - 1);
            x.r = res.first;
            return {recalc(a), res.second};
        }
        auto res = split(x.l, k);
        x.l = res.second;
        return {res.first, recalc(a)};
    }
    void push_back(int x){
        root = merge(root, new_node(x));
    }
    ll get(int l, int r){ // [;)
        auto t = split(root, r);
        auto t1 = split(t.first, l);
        ll res = safe_sum(t1.second);
        root = merge(merge(t1.first, t1.second), t.second);
        return res;
    }
    void push_seg(int l, int r){ // [; r
        auto t = split(root, r);
        auto t1 = split(t.first, l);
        if (t1.second != -1)
            nodes[t1.second].push ^= 1;
        root = merge(merge(t1.first, t1.second), t.second);
    }
};
 
int solve() {
    if (!(cin >> n >> q))
        return 1;
    Treap t;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        t.push_back(x);
    }
    for (int i = 0; i < q; i++){
        int type, l, r;
        cin >> type >> l >> r;
        --l;
        if (type == 0)
            cout << t.get(l, r) << '\n';
        else
            t.push_seg(l, r);
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("g.in", "r", stdin);
#else
    freopen("reverse.in", "r", stdin);
    freopen("reverse.out", "w", stdout);
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

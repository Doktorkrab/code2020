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

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int MAXNODE = 1e6 + 7;
struct Treap{
    struct Node{
        int x, y;
        int min = 0;
        int l = -1, r = -1;
        int sz = 1;
        Node() {}
        Node(int x) : x(x), y(rnd()), min(x) {}
    };
    Node nodes[MAXNODE];
    int root = -1;
    int pnt = 0;

    int new_node(int x){
        assert(pnt < MAXNODE);
        nodes[pnt] = Node(x);
        return pnt++;
    }

    int safe_sz(int a){
        if (a == -1)
            return 0;
        return nodes[a].sz;
    }

    int safe_min(int a){
        if (a == -1)
            return TMAX(int);
        return nodes[a].min;
    }

    int recalc(int a){
        nodes[a].sz = 1 + safe_sz(nodes[a].l) + safe_sz(nodes[a].r);
        nodes[a].min = min(nodes[a].x, min(safe_min(nodes[a].l), safe_min(nodes[a].r)));
        return a;
    }

    int merge(int a, int b){
        if (a == -1)
            return b;
        if (b == -1)
            return a;
        Node& na = nodes[a];
        Node& nb = nodes[b];
        if (na.y > nb.y){
            na.r = merge(na.r, b);
            return recalc(a);
        }
        nb.l = merge(a, nb.l);
        return recalc(b);
    }
    pair<int, int> split(int x, int k){
        if (x == -1)
            return {-1, -1};
        Node& a = nodes[x];
        if (safe_sz(a.l) + 1 <= k){
            auto res = split(a.r, k - 1 - safe_sz(a.l));
            a.r = res.first;
            return {recalc(x), res.second};
        }
        auto res = split(a.l, k);
        a.l = res.second;
        return {res.first, recalc(x)};
    }
    void insert(int pos, int x){
        auto t = split(root, pos);
        root = merge(merge(t.first, new_node(x)), t.second);
    }
    int get(int l, int r){
        auto t = split(root, r);
        auto t1 = split(t.first, l);
        int res = safe_min(t1.second);
        root = merge(merge(t1.first, t1.second), t.second);
        return res;
    }
};
 
int solve() {
    if (!(cin >> n))
        return 1;
    Treap t;
    for (int i = 0; i < n; i++){
        char x;
        int l, r;
        cin >> x >> l >> r;
        if (x == '+')
            t.insert(l, r);
        else
            cout << t.get(l - 1, r) << '\n';
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
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

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
mt19937 rnd(239);
const int MAXNODE = 1e6;
struct Treap{
    struct Node{
        int x = 0, y = 0;
        int l = -1, r = -1;
        int sz = 1;
        Node(int x) : x(x), y(rnd()) {}
        Node() {}
    };
    Node nodes[MAXNODE];
    int pnt = 0;
    int root = -1;
    int new_node(int x){
        assert(pnt < MAXNODE);
        nodes[pnt] = Node(x);
        return pnt++;
    }
    int safe_sz(int a){
        return (a == -1 ? 0 : nodes[a].sz);
    }
    int recalc(int a){
        nodes[a].sz = 1 + safe_sz(nodes[a].l) + safe_sz(nodes[a].r);
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
        if (a.x < k) {
            auto res = split(a.r, k);
            a.r = res.first;
            return {recalc(x), res.second};
        }
        auto res = split(a.l, k);
        a.l = res.second;
        return {res.first, recalc(x)};
    }
    int get(int x, int k){
        assert(x != -1);
        if (safe_sz(nodes[x].r) == k)
            return nodes[x].x;
        if (safe_sz(nodes[x].r) > k)
            return get(nodes[x].r, k);
        return get(nodes[x].l, k - safe_sz(nodes[x].r) - 1);
    }
    void insert(int x){
        if (root == -1){
            root = new_node(x);
            return;
        }
        auto t = split(root, x);
        root = merge(t.first, merge(new_node(x), t.second));
    }
    void erase(int x){
        auto t = split(root, x);
        auto t1 = split(t.second, x + 1);
        root = merge(t.first, t1.second);
    }
};
 
int solve() {
    if (!(cin >> n))
        return 1;
    Treap t;
    for (int i = 0; i < n; i++){
        int type, x;
        cin >> type >> x;
        if (type == 1)
            t.insert(x);
        else if (type == -1)
            t.erase(x);
        else
            cout << t.get(t.root, x - 1) << '\n';
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
#else
    freopen("kthmax.in", "r", stdin);
    freopen("kthmax.out", "w", stdout);
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

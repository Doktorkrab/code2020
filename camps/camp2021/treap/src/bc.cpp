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
const int MAXNODE = 1e6;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct Treap{
    struct Node{
        int x = 0, y = 0;
        int l = -1, r = -1;
        Node() = default;
        explicit Node(int x) : x(x), y(rnd()) {}
    };
    Node nodes[MAXNODE];
    int root = -1;
    int pnt = 0;
    int new_node(int x){
        assert(pnt < MAXNODE);
        nodes[pnt] = Node(x);
        return pnt++;
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
            return a;
        }
        nb.l = merge(a, nb.l);
        return b;
    }

    pair<int, int> split(int x, int k){ // [-inf; x) [x; +inf)
        if (x == -1)
            return {-1, -1};
        Node& a = nodes[x];
        if (a.x < k){
            auto res = split(a.r, k);
            a.r = res.first;
            return {x, res.second};
        }
        auto res = split(a.l, k);
        a.l = res.second;
        return {res.first, x};
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
    bool find(int x, int k){
        if (x == -1)
            return false;
        if (nodes[x].x == k)
            return true;
        if (nodes[x].x < k)
            return find(nodes[x].r, k);
        return find(nodes[x].l, k);
    }
    pair<bool, int> next(int x){
        auto t = split(root, x + 1);
        int now = t.second;
        if (now == -1)
            return {false, 0};
        while (nodes[now].l != -1)
            now = nodes[now].l;
        pair<bool, int> res = {true, nodes[now].x};
        root = merge(t.first, t.second);
        return res;
    }
    pair<bool, int> prev(int x){
        auto t = split(root, x);
        int now = t.first;
        if (now == -1)
            return {false, 0};
        while (nodes[now].r != -1)
            now = nodes[now].r;
        pair<bool, int> res = {true, nodes[now].x};
        root = merge(t.first, t.second);
        return res;
    }
};
 
int solve() {
    Treap t;

    string s;
    int x;
    while (cin >> s >> x){
//        cerr << s << ' ' << x << '\n';
        if (s == "insert")
            t.insert(x);
        else if (s == "exists")
            cout << (t.find(t.root, x) ? "true" : "false") << '\n';
        else if (s == "delete")
            t.erase(x);
        else if (s == "prev"){
            auto res = t.prev(x);
            if (!res.first)
                cout << "none\n";
            else
                cout << res.second << '\n';
        }

        else if (s == "next"){
            auto res = t.next(x);
            if (!res.first)
                cout << "none\n";
            else
                cout << res.second << '\n';
        }
    }
    return 1;
}
 
signed main() {
#ifdef LOCAL
    freopen("bc.in", "r", stdin);
#else
    freopen("bst.in", "r", stdin);
    freopen("bst.out", "w", stdout);
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

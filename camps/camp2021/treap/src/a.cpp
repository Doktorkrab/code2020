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
mt19937 rnd(239);

struct Treap {
    struct Node {
        int x, y;
        int l = -1, r = -1;
        int cnt = 0;

        Node() {}

        explicit Node(int x) : x(x), cnt(1), y(rnd()) {}
    };

    Treap() = default;
    Node nodes[MAXNODE];


    int root = -1;
    int pnt = 0;

    int new_node(int x) {
        assert(pnt < MAXNODE);
        nodes[pnt] = Node(x);
        return pnt++;
    }

    int merge(int a, int b) {
        if (a == -1)
            return b;
        if (b == -1)
            return a;
        Node &na = nodes[a];
        Node &nb = nodes[b];
        if (na.y > nb.y) {
            na.r = merge(na.r, b);
            return a;
        }
        nb.l = merge(a, nb.l);
        return b;
    }

    pair<int, int> split(int a, int k) { // (-inf; x) [x; +inf)
        if (a == -1)
            return {-1, -1};
        Node &na = nodes[a];
        if (na.x < k) {
            auto res = split(na.r, k);
            na.r = res.first;
            return {a, res.second};
        }
        auto res = split(na.l, k);
        na.l = res.second;
        return {res.first, a};
    }

    int find(int x, int k) {
        if (x == -1)
            return -1;
        if (nodes[x].x == k)
            return x;
        if (nodes[x].x < k)
            return find(nodes[x].r, k);
        return find(nodes[x].l, k);
    }

    void insert(int x) {
        if (root == -1) {
            root = new_node(x);
            return;
        }
        int node = find(root, x);
        if (node != -1) {
            nodes[node].cnt++;
            return;
        }
        auto t1 = split(root, x);
        root = merge(t1.first, merge(new_node(x), t1.second));
    }

    int get_cnt(int x) {
        int node = find(root, x);
        if (node == -1)
            return 0;
        return nodes[node].cnt;
    }
    void print(int x){
        if (x == -1)
            return;
        print(nodes[x].l);
        cout << "(" << nodes[x].x << ": " << nodes[x].cnt << ") ";
        print(nodes[x].r);
    }
    void print(){
        print(root);
        cout << '\n';
    }
};


int solve() {
    if (!(cin >> n))
        return 1;
    Treap t;
    for (int i = 0; i < n; i++){
        string s;
        int x;
        cin >> s >> x;
        if (s[1] == 'd')
            t.insert(x);
        else
            cout << t.get_cnt(x) << '\n';
//        t.print();
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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

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
 
int n, m;
mt19937 rnd(239);
const int MAXNODE = 1e2;
vector<pair<int, int>> ans;
vector<int> ans1;
struct Treap {
    struct Node {
        int x = 0, y = 0;
        int push_x = 0;
        int len = 0;
        int push_len = 0;
        int len1 = 0;
        int push_len1 = 0;
        int val = 0;

        int l = -1, r = -1;

        Node(int x, int val) : x(x), y(rnd()), val(val) {}

        Node() {}
    };

    Node nodes[MAXNODE];
    int pnt = 0;
    int root = -1;

    int new_node(int x, int val, int kek = 0, int lol = 0) {
        assert(pnt < MAXNODE);
        nodes[pnt] = Node(x, val);
        nodes[pnt].len = kek;
        nodes[pnt].len1 = lol;
        return pnt++;
    }

    void push(int a){
        if (nodes[a].push_x){
            nodes[a].x += nodes[a].push_x;
            if (nodes[a].l != -1)
                nodes[nodes[a].l].push_x += nodes[a].push_x;
            if (nodes[a].r != -1)
                nodes[nodes[a].r].push_x += nodes[a].push_x;
            nodes[a].push_x = 0;
        }
        if (nodes[a].push_len){
            nodes[a].len += nodes[a].push_len;
            if (nodes[a].l != -1)
                nodes[nodes[a].l].push_len += nodes[a].push_len;
            if (nodes[a].r != -1)
                nodes[nodes[a].r].push_len += nodes[a].push_len;
            nodes[a].push_len = 0;
        }
        if (nodes[a].push_len1){
            nodes[a].len1 += nodes[a].push_len1;
            if (nodes[a].l != -1)
                nodes[nodes[a].l].push_len1 += nodes[a].push_len1;
            if (nodes[a].r != -1)
                nodes[nodes[a].r].push_len1 += nodes[a].push_len1;
            nodes[a].push_len1 = 0;
        }
    }

    int recalc(int a) {
        return a;
    }

    int merge(int a, int b) {
        if (a == -1)
            return b;
        if (b == -1)
            return a;
        push(a);
        push(b);
        Node &na = nodes[a];
        Node &nb = nodes[b];
        if (na.y > nb.y) {
            na.r = merge(na.r, b);
            return recalc(a);
        }
        nb.l = merge(a, nb.l);
        return recalc(b);
    }

    pair<int, int> split(int x, int k) {
        if (x == -1)
            return {-1, -1};
        push(x);
        Node &a = nodes[x];
        if (a.x < k) {
            auto res = split(a.r, k);
            a.r = res.first;
            return {recalc(x), res.second};
        }
        auto res = split(a.l, k);
        a.l = res.second;
        return {res.first, recalc(x)};
    }


    int find(int x, int k) {
        if (x == -1)
            return -1;
        push(x);
        if (nodes[x].x == k)
            return x;
        if (nodes[x].x < k)
            return find(nodes[x].r, k);
        return find(nodes[x].l, k);
    }
    void push(int l, int r, int a, int b, int c){
        auto t = split(root, l);
        auto t1 = split(t.second, r + 1);
        nodes[t1.first].push_x += a;
        nodes[t1.first].push_len += b;
        nodes[t1.first].push_len1 += c;
        root = merge(t.first, merge(t1.first, t1.second));
    }
    void insert(int x, int val) {
        if (root == -1) {
            root = new_node(x, val);
            return;
        }
        int node = find(root, x);
        if (node != -1){
            int len = nodes[node].len;
            int node1 = find(root, x + len + 1 + 1);
            push(x, x + len, 1, 0, 0);

            if (node1 != -1){
                push(x + len + 2, x + len + 2 + nodes[node1].len, 0, 0, len + 1);
                node1 = find(root, x + len + 1 + 1);

                int len1 = nodes[node1].len + 1;
                push(x + 1, x + len + 1, 0, len1, 0);
            }
        }
        int node1 = find(root, x + 1);
        int node2 = find(root, x - 1);
        int ttt = 0;
        int lll = 0;
        if (node2 != -1){
            lll = nodes[node2].len1 + 1;
        }
        if (node1 != -1) {
            ttt = nodes[node1].len + 1;
            push(x + 1, x + ttt, 0, 0, lll + 1);
        }
        auto t = split(root, x);
        root = merge(t.first, merge(new_node(x, val, ttt, lll), t.second));
        node = find(root, x - 1);
        node1 = find(root, x);
        if (node != -1) {
            push(x - 1 - nodes[node].len1, x - 1, 0, nodes[node1].len + 1, 0);
        }

    }

    void erase(int x) {
        auto t = split(root, x);
        auto t1 = split(t.second, x + 1);
        root = merge(t.first, t1.second);
    }
    void print(int x){
        if (x == -1)
            return;
        push(x);
        print(nodes[x].l);
//        cerr << SZ(ans) << ' ' << x << ' ' << nodes[x].x << ' ' << nodes[x].val << '\n';
        ans.push_back({nodes[x].x, nodes[x].val});
        cout << "(" << nodes[x].x << ": " << nodes[x].val << ", " << nodes[x].len << ", " << nodes[x].len1 << ") ";
        print(nodes[x].r);
    }
    void print(){
        print(root);
        cout << '\n';
    }
};
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    Treap t;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        t.insert(x, i + 1);
        t.print();
        ans.clear();
    }
    t.print();
    int pos = 1;
    for (auto & an : ans) {
        while (pos < an.first)
            ans1.push_back(0), pos++;
        ans1.push_back(an.second);
        pos++;
    }
    cout << SZ(ans1) << '\n';
    for (int i : ans1)
        cout << i << ' ';
    cout << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
#else
    freopen("key.in", "r", stdin);
    freopen("key.out", "w", stdout);
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

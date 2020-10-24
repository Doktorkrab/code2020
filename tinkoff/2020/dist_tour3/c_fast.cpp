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
struct Node{
    int prior, size, min, val, reverse;
    Node* left = nullptr, *right = nullptr;
    Node (int val) : val(val), min(val), reverse(0), prior(rand()), size(1) {}
};

using node = Node*;

int safe_sz(node a){
    return (a ? a->size : 0);
}

node pull(node a){
    a->size = safe_sz(a->left) + 1 + safe_sz(a->right);
    return a;
}
void push(node a){
    // cerr << a->val << ' ' << a->reverse << " val\n";
    if (a->left){
        a->left->reverse ^= a->reverse;
    }
    if (a->right){
        a->right->reverse ^= a->reverse;
    }
    if (a->reverse){
        // cerr << "val " << a->val << '\n';
        swap(a->left, a->right);
        a->reverse = 0;
    }
    // cerr << "kekekke";
}
node merge(node a, node b){
    if (!a) return b;
    if (!b) return a;
    // cerr << safe_sz(a) << ' ' << safe_sz(b) << '\n';
    push(a);
    push(b);
    if (a->prior < b->prior){
        a->right = merge(a->right, b);
        return pull(a);
    }
    b->left = merge(a, b->left);
    return pull(b);
}

void print (node t){
    if (!t) return;
    print(t->left);
    cerr << t->val << ' ';
    print(t->right);
}
using ptt = pair<node, node>;
ptt split(node t, int key){ // (-inf; x] x; +inf)
    if (!t) return {nullptr, nullptr};
    push(t);
    if (safe_sz(t->left) < key){
        auto tmp = split(t->right, key - safe_sz(t->left) - 1);
        t->right = tmp.first;
        return make_pair(pull(t), tmp.second);
    }
    auto tmp = split(t->left, key);
    t->left = tmp.second;
    return make_pair(tmp.first, pull(t));
}

void insert(node& t, int key){ // t not nullptr
    if (!t){
        t = new Node(key);
        return;
    }
//    cerr << "!" << key << '\n';
//    print(t);
//    cerr << '\n';
    // cerr << "kek";
    t = merge(t, new Node(key));
    // cerr << "lol\n";
}
 
int solve() {
    if (!(cin >> n))
        return 1;
    node a = nullptr, b = nullptr;
    int pnt = 1;
    for (int i = 0; i < n; i++){
        char c;
        cin >> c;
        if (c == 'a'){
            insert(a, pnt++);
        }
        if (c == 'b'){
            insert(b, pnt++);
        }
        if (pnt == 10)
            pnt = 0;
        if (c == 'A'){
            auto [a1, b1] = split(a, 1);
            a = b1;
            cout << a1->val;
        }
        if (c == 'B'){
            auto [a1, b1] = split(b, 1);
            b = b1;
            cout << a1->val;
        }
        if (c == '>'){
            if (a)
                a->reverse ^= 1;
            b = merge(b, a);
        }
        if (c == ']'){
            if (b)
                b->reverse ^= 1;
            a = merge(a, b);
        }
        if (c == '<'){
            auto [a1, b1] = split(b, (safe_sz(b) + 1) / 2);
            b = a1;
            a = b1;
            if (a)
                a->reverse ^= 1;
        }
        if (c == '['){
            auto [a1, b1] = split(a, (safe_sz(a) + 1) / 2);
            a = a1;
            b = b1;
            if (b)
                b->reverse ^= 1;
        }
    }
    cout << '\n';
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

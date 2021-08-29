#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0;i < n;i++)


using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ui = unsigned int;
using namespace std;
using pii = pair<int, int>;


void print(ostream &st) {
    st << '\n';
}


template<typename Arg, typename... Arg1>
void print(ostream &st, const Arg &a, const Arg1 &... a1) {
    st << a << ' ';
    print(st, a1...);
}


void input() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("river.in", "r", stdin);
    freopen("river.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cout.tie(0);
#endif
#ifdef DEBUG
    freopen("kek.in", "r", stdin);
    freopen("kek.out", "w", stdout);
#endif
}

//------------------------------------END_TEMPLATE---------------------------------------------------
mt19937 gen(time(0));
uniform_int_distribution<int> distr(0, INT_MAX - 1);

struct Node {
    ll y, val, sqr, size = 1;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(ll val) : y(distr(gen)), val(val), sqr(val * val) {}

    ~Node() {
        delete left;
        delete right;
    }
};


using node = Node *;


ll safe_sz(node a) {
    return a ? a->size : 0;
}


ll safe_sqr(node a) {
    return a ? a->sqr : 0;
}


node recalc(node a) {
    a->size = 1 + safe_sz(a->left) + safe_sz(a->right);
    a->sqr = a->val * a->val + safe_sqr(a->left) + safe_sqr(a->right);
    return a;
}

node merge(node a, node b) {
    if (!b) return a;
    if (!a) return b;
    if (a->y > b->y) {
        a->right = merge(a->right, b);
        return recalc(a);
    }
    b->left = merge(a, b->left);
    return recalc(b);
}


using ptt = pair<node, node>;

ptt split(node a, int k) {
    if (!a) return {nullptr, nullptr};
    if (safe_sz(a->left) + 1 <= k) {
        ptt tmp = split(a->right, k - safe_sz(a->left) - 1);
        a->right = tmp.first;
        return {recalc(a), tmp.second};
    }
    ptt tmp = split(a->left, k);
    a->left = tmp.second;
    return {tmp.first, recalc(a)};
}


void insert(node &a, int ind, int val) {
    if (!a) {
        a = new Node(val);
        return;
    }
    ptt tmp = split(a, ind);
    a = merge(merge(tmp.first, new Node(val)), tmp.second);
}

void print(node a) {
    if (!a) return;
    print(a->left);
    cout << a->val << ' ';
    print(a->right);
}

void div(node &a, int ind) {
    // print(cout, "ind", ind);
    if (!a) cout << "JOPA";
    ptt tmp = split(a, ind + 1);
    ptt tmp1 = split(tmp.first, ind);
    if (!tmp1.second) {
        return void(a = merge(merge(tmp1.first, tmp1.second), tmp.second));
    }
    ll m = (tmp1.second->val) / 2;
    a = merge(merge(tmp1.first, merge(new Node(m), new Node(m + tmp1.second->val % 2))), tmp.second);
}

void bank(node &a, int ind) {
    if (!a) cout << "JOPA";
    if (!ind || ind == a->size - 1) {
        int gg = a->size - 1;
        ptt tmp = split(a, ind + 1);
        ptt tmp1 = split(tmp.first, ind);
        ll t = tmp1.second->val;
        a = merge(tmp1.first, tmp.second);
        if (ind == gg) ind--;
        tmp = split(a, ind + 1);
        tmp1 = split(tmp.first, ind);
        tmp1.second->val += t;
        a = merge(merge(tmp1.first, recalc(tmp1.second)), tmp.second);
    } else {
        ptt tmp = split(a, ind + 1);
        ptt tmp1 = split(tmp.first, ind);
        if (!tmp1.second) cout << "JOPA";
        ll t = tmp1.second->val;
        a = merge(tmp1.first, tmp.second);
        if (a->size == 1) {
            a->val += t;
            a = recalc(a);
            return;
        }
        tmp = split(a, ind + 1);
        tmp1 = split(tmp.first, ind);
        // if (!tmp1.second) cout << "JOPA";
        tmp1.second->val += t / 2 + t % 2;
        a = merge(merge(tmp1.first, recalc(tmp1.second)), tmp.second);
        if (a->size == 1) {
            a->val += t;
            a = recalc(a);
            return;
        }
        tmp = split(a, ind);
        tmp1 = split(tmp.first, ind - 1);
        // if (!tmp1.second) cout << "JOPA";
        tmp1.second->val += t / 2;
        a = merge(merge(tmp1.first, recalc(tmp1.second)), tmp.second);
    }
}

int main() {
    input();
    int n, p;
    cin >> n >> p;
    // assert(p != 3);
    node a = nullptr;
    rep(i, n) {
        int tmp;
        cin >> tmp;
        insert(a, i, tmp);
    }

    print(cout, a->sqr);

    int k;
    cin >> k;
    rep(i, k) {
        int ev, v;
        cin >> ev >> v;
        if (ev == 2) div(a, v - 1);
        else bank(a, v - 1);
        print(cout, a->sqr);
    }
}
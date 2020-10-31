#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>

using namespace std;
int n, s, m;

struct Node {
    int last_closed = -1;
    int l, r;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int l, int r) : l(l), r(r) {}
};

struct Segment {
    int pos, type, index;

    bool operator<(const Segment &rhs) const {
        return std::tie(pos, type, index) < std::tie(rhs.pos, rhs.type, rhs.index);
    }

    bool operator>(const Segment &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Segment &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Segment &rhs) const {
        return !(*this < rhs);
    }
};

using nd = Node *;

nd build(int L, int R) {
    nd now = new Node(L, R);
    if (R - L == 1) {
        if (L == 0)
            now->last_closed = 1e9 + 7;
        return now;
    }
    int M = (L + R) / 2;
    now->left = build(L, M);
    now->right = build(M, R);
    return now;
}

nd upd(nd a, int pos, int x) {
//    cerr << pos << "!\n";
    if (pos < a->l || a->r <= pos)
        return a;
    nd now = new Node(a->l, a->r);
    if (a->r - a->l == 1) {
//        cerr << a->l << ' ' << a->r << '\n';
        now->last_closed = x;
        return now;
    }
    now->left = upd(a->left, pos, x);
    now->right = upd(a->right, pos, x);
    now->last_closed = min(now->left->last_closed, now->right->last_closed);
    return now;
}

int get_ans(nd a, int l) {
    if (a->r - a->l == 1)
        return a->l;
//    cout << a->l << ' ' << a->r << ' ' << a->last_closed << ' ' << a->left->last_closed << '\n';
    if (a->left->last_closed < l)
        return get_ans(a->left, l);
    return get_ans(a->right, l);
}

vector<int> to_compress;
vector<pair<int, pair<int, int>>> people;
vector<nd> versions;
vector<vector<pair<int, int>>> scan;

inline void init() {

}

inline void solve() {
    people.resize(m);
    to_compress = {0, (int) (1e9 + 100)};
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
//        --a;
        to_compress.push_back(b + 1);
        to_compress.push_back(b);
        to_compress.push_back(c);
        to_compress.push_back(c + 1);
        people[i] = {a, {b, c}};
    }
    sort(to_compress.begin(), to_compress.end());
    to_compress.erase(unique(to_compress.begin(), to_compress.end()), to_compress.end());
    versions.resize(to_compress.size() + 2, nullptr);
    versions[0] = build(0, s + 10);
    scan.resize(to_compress.size() + 1);
    for (int i = 0; i < m; i++) {
        int a = people[i].first, b = people[i].second.first, c = people[i].second.second;
        scan[(int) (lower_bound(to_compress.begin(), to_compress.end(), b + 1) - to_compress.begin())].push_back(
                {a, 1e9 + 100});
        scan[(int) (lower_bound(to_compress.begin(), to_compress.end(), c) - to_compress.begin())].push_back(
                {a, c - 1});
    }
    for (int i = 0; i < to_compress.size(); i++) {
        auto tmp = versions[i];
        for (auto[j, k] : scan[i]) {
//            cerr << i << ' ' << j << ' ' << k << '\n';
            tmp = upd(tmp, j, k);
        }
        versions[i + 1] = tmp;
    }
    int q;
    cin >> q;
    int p = 0;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
//        x += p;
//        y += p;
//        cerr << x << ' ' << y << '\n';
        y = lower_bound(to_compress.begin(), to_compress.end(), y) - to_compress.begin();
//        cerr << y + 1 << '\n';
        p = get_ans(versions[y + 1], x);
        if (p > s)
            p = 0;
        cout << p << '\n';
    }

}


int main() {

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n >> s >> m)
        solve();

}
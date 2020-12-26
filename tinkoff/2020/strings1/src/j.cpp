#ifdef LOCAL
#define deb(a) cerr << "===" << #a << "=" << a << endl;
#else
#define deb(a)
#endif
#define SZ(a) (int)((a).size())
#define ALL(a) (a).begin(), (a).end()

#include <bits/stdc++.h>

#include <utility>

using namespace std;

using ll = long long;

//const int TRIE_SIZE = 1e5 + 7, ABC = 2;
//char FIRST_LET = '0';
template<int ABC>
struct Node {
    Node *edges[ABC];
    bool is_real[ABC];
    ll terminal_count = 0, cnt = 0;
    Node *suf_link = nullptr;
    Node *p = nullptr;
    int pc = 0;

    Node() {
        for (int i = 0; i < ABC; i++) {
            edges[i] = nullptr;
            is_real[i] = true;
        }
    }

    Node(Node *p, int pc) : p(p), pc(pc) {
        for (int i = 0; i < ABC; i++) {
            edges[i] = nullptr;
            is_real[i] = true;
        }
    }
};

template<int ABC, char FIRST_LET>
struct Aho {
    int cnt = 0;
    Node<ABC> *root = new Node<ABC>();

    Aho() {}

    using nd = Node<ABC> *;

    void add(const string &s, int x) {
        nd now = root;
        cnt++;
        for (char cc : s) {
            int c = cc - FIRST_LET;
            if (!now->edges[c] || !now->is_real[c]) {
                now->edges[c] = new Node<ABC>(now, c);
                now->is_real[c] = true;
            }
            now = now->edges[c];
        }
        now->terminal_count += x;
    }

    void process_link() {
        deque<nd> q = {root};
        auto get = [&](nd v) {
            if (v == root || v->p == root) {
                v->cnt = v->terminal_count;
                return v->suf_link = root;
            }
            int c = v->pc;
            nd u = v->p->suf_link;
            while (true) {
//                cerr << '\t' << u << '\n';
                if (u->edges[c]) {
                    v->suf_link = u->edges[c];
                    v->cnt = v->suf_link->cnt + v->terminal_count;
                    return v->suf_link;
                }
                assert(0);
                if (u == root) {
                    v->cnt = v->terminal_count;
                    return v->suf_link = root;
                }
                u = u->suf_link;
            }
        };
        while (!q.empty()) {
//            cerr << q.size() << '\n';
            nd v = q.front();
            q.pop_front();
            v->suf_link = nullptr;
            v->cnt = 0;
            get(v);
//            cerr << v << ' ' << v->suf_link << ' ' << SZ(v->edges) <<  ":";
            for (int i = 0; i < ABC; i++) {
                if (v->edges[i] && v->is_real[i]) {
                    q.push_back(v->edges[i]);
                } else if (v == root) {
                    v->edges[i] = root;
                    v->is_real[i] = 0;
                } else {
                    v->edges[i] = v->suf_link->edges[i];
                    v->is_real[i] = 0;
                }
//                cerr << ' ' << v->edges[i];
            }
//            cerr << '\n';
        }
    }

    ll process(const string &s) {
        ll ans = 0;
        nd now = root;
        if (root == nullptr)
            return 0;
        for (char c : s) {
            now = now->edges[c - FIRST_LET];
//           cerr << s << ' ' << c << ' ' << now << ' ' << (int)(c - FIRST_LET) << '\n';
            if (!now)
                break;

            ans += now->cnt;
        }
        return ans;
    }
};

template<int b, char c>
void merge(Aho<b, c> &x, Aho<b, c> &y, Aho<b, c> &res) {
    for (auto&[s, w] : x.added)
        res.add(s, w);
    for (auto&[s, w] : y.added)
        res.add(s, w);
//   cerr << "added\n";
    res.process_link();
}

template<int ABC>
Node<ABC> *merge1(Node<ABC> *a, Node<ABC> *b) {
    if (a == nullptr && b == nullptr)
        return nullptr;
    if (a == nullptr)
        swap(a, b);
    if (!b)
        return a;
    for (int i = 0; i < ABC; i++) {
        Node<ABC> *nxt_a = nullptr, *nxt_b = nullptr;
        if (a->is_real[i])
            nxt_a = a->edges[i];
        if (b && b->is_real[i])
            nxt_b = b->edges[i];
        a->edges[i] = merge1(nxt_a, nxt_b);
        if (a->edges[i]) {
            a->edges[i]->p = a;
            a->edges[i]->pc = i;
        }
        a->is_real[i] = true;
    }
    a->suf_link = nullptr;
    if (b)
        a->terminal_count += b->terminal_count;
    a->cnt = 0;
    return a;
}

int solve() {
    int n;
    if (!(cin >> n))
        return 1;
    vector<Aho<3, 'a'>> inserted(15);
    unordered_map<string, bool> cnt(5e6);
    int prev = 0;
    for (int i = 0; i < n; i++) {
        char x;
        string s;
        cin >> x >> s;
        rotate(s.begin(), s.begin() + (prev % SZ(s)), s.end());
//        cerr << x << ' ' << s << '\n';
        if (x == '+') {
            if (cnt[s] != 0)
                continue;
            cnt[s] = 1;
            inserted[0].root = merge1(inserted[0].root, (Node<3> *) nullptr);
            inserted[0].add(s, 1);
            inserted[0].process_link();
            for (int j = 0; j + 1 < 15; j++)
                if (inserted[j].cnt > (1 << j)) {
                    inserted[j + 1].root = merge1(inserted[j + 1].root, inserted[j].root);
                    inserted[j + 1].cnt += inserted[j].cnt;
                    inserted[j + 1].process_link();
                    inserted[j].root = new Node<3>();
                    inserted[j].process_link();
                    inserted[j].cnt = 0;
                }
        }
        if (x == '-') {
            if (cnt[s] != 1)
                continue;
            cnt[s] = 0;
            inserted[0].root = merge1(inserted[0].root, (Node<3> *) nullptr);
            inserted[0].add(s, -1);
            inserted[0].process_link();
            for (int j = 0; j + 1 < 15; j++)
                if (inserted[j].cnt > (1 << j)) {
                    inserted[j + 1].root = merge1(inserted[j + 1].root, inserted[j].root);
                    inserted[j + 1].cnt += inserted[j].cnt;
                    inserted[j + 1].process_link();
                    inserted[j].root = new Node<3>();
                    inserted[j].process_link();
                    inserted[j].cnt = 0;
                }
        }
        if (x == '?') {
            ll sum = 0;
//            cerr << "here\n";
            for (int j = 0; j < 15; j++) {
                sum += inserted[j].process(s);
            }
//            cerr << "ok\n";
            prev = sum;
            cout << sum << '\n';
        }
    }
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tests = 1e9;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "______________________________________________" << endl;
#endif
    }
#ifdef LOCAL
    cerr << endl << "finished in " << clock() * 1.L / CLOCKS_PER_SEC << " sec" << endl;
#endif
}

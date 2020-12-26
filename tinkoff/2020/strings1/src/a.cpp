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
const int MAXN = 1e6 + 7;

template<int ALP, int SIZE>
struct AhoCorasick {
    struct Node {
        char pCh = -1;
        int p = 0;
        int suf_link = -1;
        bool used = false;
        int edges[ALP];
        vector<int> terminal;

        Node() {
            fill(edges, edges + ALP, -1);
        }

        explicit Node(int pp, char _pCh) : p(pp), pCh(_pCh) {
            fill(edges, edges + ALP, -1);
        }
    };

    Node nodes[SIZE];
    int first_free = 1;

    AhoCorasick() {}

    void add(const string &s, int ind) {
        int pos = 0;
        for (char c : s) {
            int cc = c - 'a';
            if (nodes[pos].edges[cc] == -1) {
                nodes[pos].edges[cc] = first_free;
                nodes[first_free++] = Node(pos, cc);
            }
            pos = nodes[pos].edges[cc];
        }
        nodes[pos].terminal.push_back(ind);
    }

    int link(int v) {
        if (nodes[v].suf_link != -1)
            return nodes[v].suf_link;
        if (v == 0 || nodes[v].p == 0)
            return nodes[v].suf_link = 0;
        return nodes[v].suf_link = go(link(nodes[v].p), nodes[v].pCh);
    }

    int go(int v, int c) {
        if (nodes[v].edges[c] != -1)
            return nodes[v].edges[c];
        if (v == 0)
            return nodes[v].edges[c] = 0;
        return nodes[v].edges[c] = go(link(v), c);
    }

    void get_ans_offline(int v) {
        if (nodes[v].used)
            return;
        nodes[v].used = true;
        if (v == 0)
            return;
        get_ans_offline(link(v));
        for (int x : nodes[link(v)].terminal)
            nodes[v].terminal.push_back(x);
    }

    int last_pos[MAXN]; // for offline
    vector<int> ans[MAXN];

    void process_offline(const string &s) {
        int pos = 0;
        for (int i = 0; i < SZ(s); i++) {
            pos = go(pos, s[i] - 'a');
            last_pos[i] = pos;
        }
        for (int i = 0; i < SZ(s); i++) {
            get_ans_offline(last_pos[i]);
            for (int x : nodes[last_pos[i]].terminal)
                ans[x].push_back(i);
        }
    }
};

string s;
int sizes[MAXN];

int solve() {
    if (!(cin >> s >> n))
        return 1;
    string t;
    AhoCorasick<26, (int) 1e6> ahoCorasick;
    for (int i = 0; i < n; i++) {
        cin >> t;
        ahoCorasick.add(t, i);
        sizes[i] = SZ(t);
    }
    ahoCorasick.process_offline(s);
    for (int i = 0; i < n; i++) {
        cout << SZ(ahoCorasick.ans[i]) << " ";
        for (int x : ahoCorasick.ans[i])
            cout << x - sizes[i] + 2 << ' ';
        cout << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#else
    freopen("inputik.txt", "r", stdin);
    freopen("outputik.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= 1; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

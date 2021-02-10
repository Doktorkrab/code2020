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

template<int ALP, int NODES>
struct SuffAutomaton {
    struct Node {
        int go[ALP];
        int link = -1;
        int len = 0;
        ll cnt = 0;
        bool used = false;
        int p = -1;
        char pc;

        Node() {
            for (int i = 0; i < ALP; i++)
                go[i] = -1;
        }
    };

    Node nodes[NODES];
    int sz = 1;
    int last = 0;

    void add_letter(int c) {
        int cur = sz++;
        nodes[cur].len = nodes[last].len + 1;
        nodes[cur].p = last;
        nodes[cur].pc = c;
        while (last != -1 && nodes[last].go[c] == -1) {
            nodes[last].go[c] = cur;
            last = nodes[last].link;
        }
        if (last == -1) {
            nodes[cur].link = 0;
            last = cur;
            return;
        }
        int q = nodes[last].go[c];
        if (nodes[q].len == nodes[last].len + 1) {
            nodes[cur].link = q;
            last = cur;
            return;
        }
        int clone = sz++;
        nodes[clone] = nodes[q];
        nodes[clone].len = nodes[last].len + 1;
        nodes[clone].p = last;
        nodes[clone].pc = c;
        while (last != -1 && nodes[last].go[c] == q) {
            nodes[last].go[c] = clone;
            last = nodes[last].link;
        }
        nodes[cur].link = clone;
        nodes[q].link = clone;
        last = cur;
    }

    void add(const string &s) {
        for (char c : s)
            add_letter(tolower(c) - 'a');
    }

    bool check(const string &s) {
        int now = 0;
        for (char c : s) {
            if (now == -1)
                return false;
            now = nodes[now].go[tolower(c) - 'a'];
        }
        return now != -1;
    }

    void mark_all_terminals() {
        int now = last;
        while (now != -1) {
            nodes[now].cnt = 1;
            now = nodes[now].link;
        }
    }

    ll ans = 0, ans_v = -1;

    ll dfs(int v) {
        if (v == -1)
            return 0;
        if (nodes[v].used)
            return nodes[v].cnt;
        nodes[v].used = true;
        for (int i = 0; i < ALP; i++)
            nodes[v].cnt += dfs(nodes[v].go[i]);
        if (nodes[v].len * nodes[v].cnt > ans) {
            ans = nodes[v].len * nodes[v].cnt;
            ans_v = v;
        }
        return nodes[v].cnt;
    }
};

int solve() {
    int hui;
    if (!(cin >> n >> hui))
        return 1;
    SuffAutomaton<11, (int) (2e6 + 7)> automaton;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        automaton.add_letter(x - 1);
    }
    automaton.mark_all_terminals();
    automaton.dfs(0);
    ll l = automaton.nodes[automaton.ans_v].len;
    cout << automaton.ans << '\n' << l << '\n';
    vector<int> ans;
    int v = automaton.ans_v;
    while (v > 0) {
        ans.push_back(automaton.nodes[v].pc);
        v = automaton.nodes[v].p;
    }
    reverse(ALL(ans));
    for (int x : ans)
        cout << x + 1 << " ";
    cout << '\n';
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

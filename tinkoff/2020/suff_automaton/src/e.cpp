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
        int min_len = 1e9;
        int real_min = 1e9;
        bool used = false;
        int p = -1;
        char pc = -1;

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

    ll ans = 0, ans_v = -1;

    vector<int> g[NODES];

    ll restore_cnt(int v) {
        if (nodes[v].used)
            return nodes[v].cnt;
        nodes[v].used = true;
        for (int u : g[v]) {
            nodes[v].cnt += restore_cnt(u);
            nodes[v].min_len = min(nodes[v].min_len, nodes[u].min_len + 1);
        }
        return nodes[v].cnt;
    }

    int calc_len(int v) {
        if (v == 0)
            return nodes[v].real_min = 0;
        if (nodes[v].used)
            return nodes[v].real_min;
        nodes[v].used = true;
        for (int u : g[v])
            nodes[v].real_min = min(calc_len(u) + 1, nodes[v].real_min);
        return nodes[v].real_min;
    }

    ll find_ans() {
        for (int i = 0; i < sz; i++)
            g[i].clear();
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < ALP; j++)
                if (nodes[i].go[j] != -1)
                    g[nodes[i].go[j]].push_back(i);
        }
        for (int j = 0; j < sz; j++) {
            if (!nodes[j].used) {
                calc_len(j);
            }
        }
        for (int i = 0; i < ALP; i++) {
            if (nodes[0].go[i] == -1)
                continue;
            for (int j = 0; j < sz; j++) {
                nodes[j].used = false;
                nodes[j].cnt = 0;
                nodes[j].min_len = 1e9;
            }
            nodes[nodes[0].go[i]].cnt = 1;
            nodes[nodes[0].go[i]].min_len = 1;
            for (int j = 0; j < sz; j++) {
                if (!nodes[j].used) {
                    restore_cnt(j);
                }
                if (nodes[j].cnt == 0)
                    continue;
//                int was = ans;
                if (nodes[j].go[i] != -1)
                    ans += nodes[j].cnt - (nodes[j].real_min == nodes[j].min_len);
                if (nodes[j].real_min == nodes[j].min_len)
                    ans += nodes[nodes[j].link].go[i] != -1;
//                cout << j << ' ' << i << ' ' << ans - was << '\n';
            }
        }
        return ans;
    }

    void print() {
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < ALP; j++)
                if (nodes[i].go[j] != -1)
                    cout << i << ' ' << nodes[i].go[j] << ' ' << (char) ('a' + j) << endl;
        }
    }
};

int solve() {
    string s;
    if (!(cin >> s))
        return 1;
    n = SZ(s);
    SuffAutomaton<26, (int) 1e6 + 7> automaton;
    automaton.add(s);
//    automaton.print();
//    automaton.dfs(0);
    cout << automaton.find_ans() << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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

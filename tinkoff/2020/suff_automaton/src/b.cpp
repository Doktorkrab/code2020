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

template<int ALP, int SIZE>
struct SuffAutomaton {
    struct Node {
        int link = -1;
        int p = -1;
        char pc = -1;
        int go[ALP]{};
        int len = 0;
        int last_used = -1;
        ll cnt = 0;

        Node() {
            for (int &x : go)
                x = -1;
        }
    };

    Node nodes[SIZE];
    int sz = 1;

    int add_letter(int last, int c) {
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
            return cur;
        }
        int q = nodes[last].go[c];
        if (nodes[q].len == nodes[last].len + 1) {
            nodes[cur].link = q;
            return cur;
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
        return cur;
    }

    vector<int> ends;

    void add(const string &s) {
        int now = 0;
        for (char c : s)
            now = add_letter(now, c - 'a');
        ends.push_back(now);
    }

    int timer = 0;

    void subautomaton(int v) {
        if (v == -1)
            return;
        if (nodes[v].last_used == timer)
            return;
        nodes[v].cnt++;
        nodes[v].last_used = timer;
        subautomaton(nodes[v].p);
        subautomaton(nodes[v].link);
    }

    vector<int> find_ans() {
        vector<int> ans(SZ(ends) + 1);
        for (int x : ends) {
            subautomaton(x);
            timer++;
        }
        for (int i = 0; i < sz; i++)
            ans[nodes[i].cnt] = max(ans[nodes[i].cnt], nodes[i].len);
        for (int i = SZ(ends); i >= 1; i--)
            ans[i - 1] = max(ans[i - 1], ans[i]);
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
    if (!(cin >> n))
        return 1;
    SuffAutomaton<26, (int) (1e6 + 7)> automaton;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        automaton.add(s);
    }
    automaton.print();
    auto ans = automaton.find_ans();
    for (int i = 2; i <= n; i++)
        cout << ans[i] << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

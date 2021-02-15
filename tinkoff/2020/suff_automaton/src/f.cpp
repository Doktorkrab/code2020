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
        char pc;
        int go[ALP]{};
        int len = 0;
        ll cnt = 0;
        int last_used = -1;
        int is_terminal = 0;

        Node() {
            for (int i = 0; i < ALP; i++)
                go[i] = -1;
        }
    };

    Node nodes[SIZE];
    int sz = 1;

    int add(int last, int c) {
        int nlast = sz++;
        nodes[nlast].p = last;
        nodes[nlast].len = nodes[last].len + 1;
        nodes[nlast].pc = c;
        while (last != -1 && nodes[last].go[c] == -1) {
            nodes[last].go[c] = nlast;
            last = nodes[last].link;
        }
        if (last == -1) {
            nodes[nlast].link = 0;
            return nodes[nodes[nlast].p].go[c];
        }
        int b = nodes[last].go[c];
        if (nodes[b].len == nodes[last].len + 1) {
            nodes[nlast].link = b;
            return nodes[nodes[nlast].p].go[c];
        }
        int clone = sz++;
        nodes[clone] = nodes[b];
        nodes[clone].len = nodes[last].len + 1;
        nodes[clone].p = last;
        nodes[clone].pc = c;
        nodes[clone].is_terminal = 0;
        while (last != -1 && nodes[last].go[c] == b) {
            nodes[last].go[c] = clone;
            last = nodes[last].link;
        }
        nodes[nlast].link = clone;
        nodes[b].link = clone;
        return nodes[nodes[nlast].p].go[c];
    }

    int add(const string &s) {
        int now = 0;
        for (char c : s)
            now = add(now, c - 'a');
        return now;
    }

    void insert(const string &s) {
        int x = add(s);
        nodes[x].is_terminal = 1;
//        cout << s << ' ' << x << '\n';
    }

    void remove(const string &s) {
        int x = add(s);
        nodes[x].is_terminal = 0;
    }

    int t = 0;
    ll ans = 0;

    ll up_link(int v) {
        if (v == -1)
            return 0;
        if (nodes[v].last_used == t) {
            ans += nodes[v].cnt;
            return nodes[v].cnt;
        }
        nodes[v].last_used = t;
//        cout << '\t' << v << ' ' << nodes[v].is_terminal << '\n';
        ans += nodes[v].is_terminal;
        nodes[v].cnt = nodes[v].is_terminal + up_link(nodes[v].link);
        return nodes[v].cnt;
    }

    void subautomaton(int v) {
        if (v == -1)
            return;
        up_link(v);
        subautomaton(nodes[v].p);
    }

    ll get_ans(const string &s) {
        int start = add(s);
        ans = 0;
        subautomaton(start);
        t++;
        return ans;
    }

    void print() {
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < ALP; j++)
                if (nodes[i].go[j] != -1)
                    cout << i << ' ' << nodes[i].go[j] << ' ' << (char) ('a' + j) << endl;
        }
        for (int i = 0; i < sz; i++) {
            if (nodes[i].link != -1)
                cout << i << ' ' << nodes[i].link << " link\n";
        }
    }
};


int solve() {
    if (!(cin >> n))
        return 1;
    char c;
    string s;
    SuffAutomaton<3, (int) (1e7) + 7> automaton;
    ll was = 0;
    for (int i = 0; i < n; i++) {
        cin >> c >> s;
        rotate(s.begin(), s.begin() + (was % SZ(s)), s.end());
        if (c == '+')
            automaton.insert(s);
        if (c == '-')
            automaton.remove(s);
        if (c == '?')
            cout << (was = automaton.get_ans(s)) << '\n';
//        cout << '\n';
    }
//            automaton.print();
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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

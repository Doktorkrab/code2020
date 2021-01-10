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
const int MAXNODE = 6e5 + 7;
const int ALP = 26;
struct SuffixAutomaton {
    struct Node {
        int link = -1;
        int len = 0;
        int go[ALP];
        ll cnt = 0; // ways to reach v

        Node() {
            for (int i = 0; i < ALP; i++)
                go[i] = -1;
        }
    };

    Node nodes[MAXNODE];
    int last = 0;
    int pnt = 1;
    ll ans = 0;
    SuffixAutomaton() {
        nodes[0].cnt = 1;
    }

    void add(char c) {
        int nlast = pnt++;
        nodes[nlast].len = nodes[last].len + 1;
//        cout << nlast << "!!!\n";
        while (last != -1 && nodes[last].go[c] == -1) {
            nodes[last].go[c] = nlast;
//            cout << '\t' << last << ' ' << nodes[last].cnt << '\n';
            nodes[nlast].cnt += nodes[last].cnt;
            last = nodes[last].link;
        }
        if (last == -1) {
            nodes[nlast].link = 0;
            last = nlast;
            return;
        }
        int b = nodes[last].go[c];
        if (nodes[b].len == nodes[last].len + 1) {
            nodes[nlast].link = b;
            last = nlast;
            return;
        }
        int clone = pnt++;
//        cout << "CLONE: " << clone << ' ' << b << '\n';
        nodes[clone] = nodes[b];
        nodes[clone].len = nodes[last].len + 1;
        nodes[clone].cnt = 0;
        while (last != -1 && nodes[last].go[c] == b) {
            nodes[b].cnt -= nodes[last].cnt;
            nodes[clone].cnt += nodes[last].cnt;
            nodes[last].go[c] = clone;
            last = nodes[last].link;
        }
        nodes[nlast].link = clone;
        nodes[b].link = clone;
        last = nlast;
    }

    void add(const string &s) {
        for (char c : s) {
            add(tolower(c) - 'a');
//            print();
            cout << (ans += nodes[last].cnt) << '\n';
        }
    }

    bool check(string &s) {
        int now = 0;
        for (char &c : s) {
            c = tolower(c);
            if (nodes[now].go[c - 'a'] == -1)
                return false;
            now = nodes[now].go[c - 'a'];
        }
        return true;
    }
    void print(){
        for (int i = 0; i < pnt; i++)
            for (int j = 0; j < ALP; j++)
                if (nodes[i].go[j] != -1)
                    cout << i << ' ' << nodes[i].go[j] << ' ' << (char)(j + 'a') << '\n';
    }
};


int solve() {
    string s;
    if (!(cin >> s))
        return 1;

    SuffixAutomaton automaton;
    automaton.add(s);
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("suffAuto.in", "r", stdin);
#else
    freopen("keepcounted.in", "r", stdin);
    freopen("keepcounted.out", "w", stdout);
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

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
const int MAXN = 1e5 + 7;
string have[MAXN];
vector<int> cur_ans;

const int ALP = 26;
struct Node {
    vector<int> edges;
    bool terminal_id = false;
    vector<vector<pair<int, int>>> pnts;

    Node() {
        edges.resize(26, -1);
        pnts.resize(26);
    }
};
vector<Node> nodes(1);
struct Trie {
    int first_free = 1;

    void init() {
        first_free = 1;
    }

    void push(const string &s, int start, int now, int index) {
        if (start >= SZ(s)) {
            if (nodes[now].terminal_id)
                cur_ans.push_back(index);
            return;
        }
        if (nodes[now].terminal_id)
            push(s, start, 0, index);
        else if (nodes[now].edges[s[start] - 'a'] == -1)
            nodes[now].pnts[s[start] - 'a'].emplace_back(start, index);
        else
            push(s, start + 1, nodes[now].edges[s[start] - 'a'], index);
    }

    void add_word(const string &s) {
        int now = 0;
        int len = 0;
        for (char c : s) {
            len++;
            if (nodes[now].edges[c - 'a'] == -1) {
                nodes.emplace_back();
                nodes[now].edges[c - 'a'] = first_free++;
                for (auto p : nodes[now].pnts[c - 'a']) {
                    if (SZ(have[p.second]) == p.first + 1 && len == SZ(s))
                        cur_ans.push_back(p.second);
                    else if (SZ(have[p.second]) > p.first + 1)
                        nodes[nodes[now].edges[c - 'a']].pnts[have[p.second][p.first + 1] - 'a'].emplace_back(
                                p.first + 1, p.second);
                }
                nodes[now].pnts[c - 'a'].clear();
                nodes[now].pnts[c - 'a'].shrink_to_fit();
            }
            now = nodes[now].edges[c - 'a'];
        }
        nodes[now].terminal_id = true;
        for (auto &pnt : nodes[now].pnts) {
            auto tmp = pnt;
            pnt.clear();
            pnt.shrink_to_fit();
            for (auto[a, b] : tmp)
                push(have[b], a, 0, b);
        }
    }
};

int n;
Trie t;

int solve() {
    if (!(cin >> n))
        return 1;
    t.init();
    int index = 1;
    for (int i = 0; i < n; i++) {
        char type;
        string s;
        cin >> type >> s;
        rotate(s.begin(), s.begin() + SZ(cur_ans) % SZ(s), s.end());
        cur_ans.clear();
        if (type == '+')
            t.add_word(s);
        if (type == '?') {
            have[index] = s;
            t.push(s, 0, 0, index++);
        }
        cout << SZ(cur_ans) << " ";
        for (int x : cur_ans)
            cout << x << ' ';
        cout << '\n';
    }
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

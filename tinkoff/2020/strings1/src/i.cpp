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
namespace errtree {
    const int ALP = 26, MAXN = 3e5 + 7;

    struct Node {
        int link = -1, len = 0;
        int go[ALP];
        int cnt = 0;
        bool used = false;

        Node() {
            for (int i = 0; i < ALP; i++)
                go[i] = -1;
        }
    };

    Node nodes[MAXN];
    int cur = 0, n = 0;
    string s;
    int N;

    void add_letter(int pos) {
        while (s[pos - 1 - nodes[cur].len] != s[pos])
            cur = nodes[cur].link;
        if (nodes[cur].go[s[pos] - 'a'] != -1) {
            cur = nodes[cur].go[s[pos] - 'a'];
            nodes[cur].cnt++;
            return;
        }
        int b = n++;
        nodes[cur].go[s[pos] - 'a'] = b;
        nodes[b].len = nodes[cur].len + 2;
        int cur1 = nodes[cur].link;
        while (s[pos - 1 - nodes[cur1].len] != s[pos]) {
            cur1 = nodes[cur1].link;
        }
        nodes[b].cnt = 1;
        nodes[b].link = (cur1 == cur ? 1 : nodes[cur1].go[s[pos] - 'a']);
        cur = b;
    }

    void init(int sz) {
        N = sz;
        nodes[0].len = -1;
        nodes[0].link = 0;
        nodes[1].len = 0;
        nodes[1].link = 0;
        n = 2;
    }

    vector<int> g[MAXN];

    void build_graph() {
        for (int i = 0; i < n; i++)
            if (nodes[i].link != 0)
                g[nodes[i].link].push_back(i);
    }

    int update_cnt(int v) {
        nodes[v].used = true;
        for (int u : g[v])
            nodes[v].cnt += update_cnt(u);
        return nodes[v].cnt;
    }

    void update_cnt() {
        for (int i = 0; i < n; i++)
            if (!nodes[i].used)
                update_cnt(i);
    }

    ll get_refren() {
        build_graph();
        update_cnt();
        ll mx = 0;
        for (int i = 0; i < n; i++) {
//            cout << nodes[i].cnt << ' ' << nodes[i].len << '\n';
            mx = max(mx, (ll) nodes[i].cnt * nodes[i].len);
        }
        return mx;
    }
}  // namespace errtree
int n;

int solve() {
    if (!(cin >> errtree::s))
        return 1;
    n = SZ(errtree::s);
    errtree::init(n);
    for (int i = 0; i < n; i++)
        errtree::add_letter(i);
    cout << errtree::get_refren() << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("i.in", "r", stdin);
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

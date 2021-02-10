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

const int ALP = 26, MAXN = 2e5 + 7;

struct Node {
    int link = -1, len = 0;
    int go[ALP];

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
        return;
    }
    int b = n++;
    nodes[cur].go[s[pos] - 'a'] = b;
    nodes[b].len = nodes[cur].len + 2;
    int cur1 = nodes[cur].link;
    while (s[pos - 1 - nodes[cur1].len] != s[pos]) {
        cur1 = nodes[cur1].link;
    }
    nodes[b].link = (cur1 == cur ? 1 : nodes[cur1].go[s[pos] - 'a']);
    cur = b;
}

int solve() {
    if (!(cin >> s))
        return 1;
    N = s.size();
    n = 2;
    nodes[0].len = -1;
    nodes[0].link = 0;
    nodes[1].len = 0;
    nodes[1].link = 0;
    for (int i = 0; i < N; i++) {
        add_letter(i);
        cout << n - 2 << " \n"[i + 1 == N];
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("g.in", "r", stdin);
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

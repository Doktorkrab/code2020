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
 
int n, m;
const int ALP = 12;
const int MAXN = 2e6 + 7;
struct Node{
    int len = 0, link = 0;
    int go[ALP];
    int p = -1, pc = -1;
    ll cnt = 0;
    int used = 0;
    Node () {
        for (int i = 0; i < ALP; i++)
            go[i] = -1;
    }
};
Node nodes[MAXN];
int lst = 0, sz = 1;
void add(int c){
    int cur = sz++;
    assert(cur < MAXN);
    nodes[cur].len = nodes[lst].len + 1;
    nodes[cur].p = lst;
    nodes[cur].pc = c;
    int p = lst;
    while (p != -1 && nodes[p].go[c] == -1){
        nodes[p].go[c] = cur;
        p = nodes[p].link;
    }
    if (p == -1){
        lst = cur;
        nodes[lst].link = 0;
        return;
    }
    int q = nodes[p].go[c];
    if (nodes[q].len == nodes[p].len + 1){
        nodes[cur].link = q;
    }
    else {

        int clone = sz++;
        assert(clone < MAXN);
        nodes[clone].len = nodes[p].len + 1;
        nodes[clone].p = p;
        nodes[clone].pc = c;
        for (int i = 0; i < ALP; i++)
            nodes[clone].go[i] = nodes[q].go[i];
        nodes[clone].link = nodes[q].link;
        while (p != -1 && nodes[p].go[c] == q){
            nodes[p].go[c] = clone;
            p = nodes[p].link;
        }
        nodes[cur].link = nodes[q].link = clone;
    }
    lst = cur;
}
ll ans = 0, ans_v = 0;
void mark(){
    int p = lst;
    while (p != -1){
        nodes[p].cnt = 1;
        p = nodes[p].link;
    }
}
int dfs(int v){
    if (v == -1)
        return 0;
    if (nodes[v].used)
        return nodes[v].cnt;
    nodes[v].used = 1;
    for (int i = 0; i < ALP; i++)
            nodes[v].cnt += dfs(nodes[v].go[i]);
    if (nodes[v].len * nodes[v].cnt > ans){
        ans = nodes[v].len * nodes[v].cnt;
        ans_v = v;
    }
    return nodes[v].cnt;
}
int solve() {
    nodes[0].link = -1;
    sz = 1;
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        add(x - 1);
    }
    mark();
    dfs(0);
    int l = nodes[ans_v].len;
    cout << ans << '\n' << nodes[ans_v].len << '\n';
    vector<int> ans1;
    while (ans_v > 0){
        ans1.push_back(nodes[ans_v].pc);
        ans_v = nodes[ans_v].p;
    }
    reverse(ALL(ans1));
    assert(SZ(ans1) == l);
    for (int i : ans1)
        cout << i + 1 << ' ';
    cout << '\n';
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
// #ifdef LOCAL
//         cout << "------------------------------\n";
// #endif
    }
}
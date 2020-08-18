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
const int ALP = 26;
struct Node{
    int len = 0;
    int link = 0;
    int go[ALP];
    Node () {
        for (int i = 0; i < ALP; i++)
            go[i] = -1;
    }
};
int sz = 0, lst = 0;
Node nodes[MAXN];

void add(int c){
    int cur = sz++;
    nodes[cur].len = nodes[lst].len + 1;
    int p = lst;
    c -= 'a';
    while (p != -1 && nodes[p].go[c] == -1){
        nodes[p].go[c] = cur;
        p = nodes[p].link;
    }
    if (p == -1){
        lst = cur;
        return;
    }
    int q = nodes[p].go[c];
    if (nodes[q].len == nodes[p].len + 1){
        nodes[cur].link = q;
    }
    else {
        int cur1 = sz++;
        nodes[cur1].len = nodes[p].len + 1;
        for (int i = 0; i < ALP; i++)
            nodes[cur1].go[i] = nodes[q].go[i];
        nodes[cur1].link = nodes[q].link;
        while (p != -1 && nodes[p].go[c] == q){
            nodes[p].go[c] = cur1;
            p = nodes[p].link;
        }
        nodes[cur].link = cur1;
        nodes[q].link = cur1;
    }
    lst = cur;
}
bool go(string& s, int pos, int v){
    if (v == -1)
        return 0;
    if (pos == SZ(s))
        return 1;
    return go(s, pos + 1, nodes[v].go[s[pos] - 'a']);
}
int solve() {
    nodes[0].link = -1;
    nodes[0].len = 0;
    ++sz;
    for (int i = 0; i < lst; i++)
        fill(nodes[i].go, nodes[i].go + ALP, -1);

    string q, s;
    while (cin >> q >> s){
        for (char& c : s)
            c = tolower(c);
        if (q == "A")
            for (char c : s)
                add(c);
        else {
            if (go(s, 0, 0))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // int tests = 1e9;
//    cin >> tests;
    // for (int i = 1; i <= tests; i++) {
        // if (solve())
    solve();
            // break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
}
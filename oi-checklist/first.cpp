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
const int MAXN = 5e4 + 7;
const int MAXC = 5e5 + 7;
const int ALP = 26;
string have[MAXN];
struct Node{
    int next[ALP];
    bool is_terminal;
    Node() {
        for (int i = 0; i < ALP; i++)
            next[i] = -1;
        is_terminal = false;
    }
};
Node nodes[MAXC];
int pnt = 1;
void insert(const string& s){
    int now = 0;
    for (char c : s){
        int go = c - 'a';
        if (nodes[now].next[go] == -1){
            nodes[pnt] = Node();
            nodes[now].next[go] = pnt++;
        }
        now = nodes[now].next[go];
    }
    nodes[now].is_terminal = true;
}

bool adj[ALP][ALP];
int used[ALP];
bool build(const string& s, int pos, int v){
    if (pos == SZ(s))
        return true;
    // cerr << pos << ' ' << v << ' ' << (int)(nodes[v].is_terminal) << '\n';
    if (nodes[v].is_terminal)
        return false;
    for (int i = 0; i < ALP; i++)
        if (nodes[v].next[i] != -1 && i != s[pos] - 'a')
            adj[s[pos] - 'a'][i] = 1;
    return build(s, pos + 1, nodes[v].next[s[pos] - 'a']);
}
bool find_cycle(int v){
    used[v] = 1;
    for (int i = 0; i < ALP; i++){
        if (!adj[v][i])
            continue;
        if (used[i] == 2)
            continue;
        if (used[i] == 1)
            return true;
        if (find_cycle(i))
            return true;
    }
    used[v] = 2;
    return false;
}
int solve() {
    if (!(cin >> n))
        return 1;
    pnt = 1;
    nodes[0] = Node();
    for (int i = 0; i < n; i++){
        cin >> have[i];
        insert(have[i]);
    }
    vector<int> ans;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < ALP; j++){
            for (int k = 0; k < ALP; k++)
                adj[j][k] = 0;
            used[j] = 0;
        }
        if (!build(have[i], 0, 0))
            continue;
        // for (int i = 0; i < ALP; i++)
        //     for (int j = 0; j < ALP; j++)
        //         cout << adj[i][j] << " \n"[j + 1 == ALP];
        // cerr << i << '\n';
        bool good = true;
        for (int j = 0; j < ALP; j++)
            if (!used[j]){
                good &= !find_cycle(j);
                if (!good){
                    // cerr << j << '\n';
                    break;
                }
            }
        if (good)
            ans.push_back(i);

    }
    cout << SZ(ans) << '\n';
    for (int i : ans)
        cout << have[i] << '\n';
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("first.in", "r", stdin);
    freopen("first.out", "w", stdout);
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
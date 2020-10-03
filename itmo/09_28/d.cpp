#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;

#define int ll
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
int n, m;
pair<int, pair<int, int>> edges[MAXN];
int p[MAXN];
int sz[MAXN];

int find_set(int a){
    if (p[a] == a)
        return a;
    return p[a] = find_set(p[a]);
}

bool un(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if (a == b)
        return false;
    if (sz[a] > sz[b])
        swap(a, b);
    p[a] = b;
    sz[b] += sz[a];
    return true;
}

bool get_ans(int x){
    for (int i = 0; i < n; i++){
        p[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < m; i++){
        edges[i].first -= x / 2;
        //cout << edges[i].first << " \n"[i + 1 == m];
    }
    
    int pos = m;
    for (int i = 0; i < m; i++)
        if (edges[i].first >= 0){
            pos = i;
            break;
        }
    //cout << pos << '\n';
    bool found = false;
    for (int i = pos; i < m; i++){
        while (pos - 1 >= 0 && -edges[pos - 1].first <= edges[i].first){
            un(edges[pos - 1].second.first, edges[pos - 1].second.second);
            pos--;
        }
        if (!un(edges[i].second.first, edges[i].second.second)){
            //cout << edges[i].second.first + 1 << ' ' << edges[i].second.second + 1 << '\n';
            found = true;
            break;
        }
    }
    for (int i = 0; i < m; i++)
        edges[i].first += x / 2;
    return found;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    vector<int> have;
    for (int i = 0; i < m; i++){
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        edges[i] = {2 * w, {v, u}};
        have.push_back(w);
    }
    sort(edges, edges + m);
    have.erase(unique(ALL(have)), have.end());
    int l = 0, r = 2e9 + 7;
    while (r - l > 1){
        int M = (l + r) / 2;
        //cout << M << ' ' << get_ans(M) << '\n';
        if (get_ans(2 * M))
            l = M;
        else
            r = M;
    }
    cout << l << '\n';
    //cout << get_ans(2) << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

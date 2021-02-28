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
int subtask, adj;
vector<int> g;
int current, where, ans;

void update_state(){
    cin >> subtask >> adj;
    g.resize(adj);
    for (int i = 0; i < adj; i ++)
        cin >> g[i];
    cin >> current >> where >> ans;
}

void push_state(int nc, int nw, int na){
    cout << nc << ' ' << nw << ' ' << na << endl;
    if (na != -1)
        exit(0);
    update_state();
}

int cnt = 0;
const int USED = 1000;
const int EXITED = 1;
vector<int> aval;
void push_used(int to_push){
    int ret = to_push;
    while (1){
        bool was = false;
        for (int x : g) {
            if (x == 0 || x == USED || x == EXITED)
                continue;
            push_state(to_push, x, -1);
            aval.push_back(x);
            push_state(USED, ret, -1);
            was = true;
            break;
        }
        if (!was)
            break;
    }
}
void dfs(){
    while (*min_element(ALL(g)) == 0) {
        int now = aval.back();
        aval.pop_back();
//        push_state(now, -1, -1);
        push_used(now);
        push_state(now, 0, -1);
        dfs();
    }
    cnt++;
//    push_state(EXITED, where, -1);
    if (*max_element(ALL(g)) == 1)
        return;
    int x = -1;
    for (int u : g)
        if (u != 1 && (x == -1 || x > u))
            x = u;
    push_state(EXITED, x, -1);
}
void solve1(){
    cnt = 0;
    aval.resize(998);
    iota(ALL(aval), 2);
    dfs();
    cnt = 2;
    push_state(current, -1, cnt);
}

int solve() {
    update_state();
    if (subtask == 1)
        solve1();
    else
        assert(0);
    return 0;
}
 
signed main() {
//#ifdef LOCAL
//    freopen("d.in", "r", stdin);
//#endif
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
    int tests = 1;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

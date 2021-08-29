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
const int MAXN = 3e5 + 7;
vector<int> g[MAXN];
bool used[MAXN];
int used1[MAXN];
int dp[MAXN][2][2]; // p->v, v->p
set<pair<int, int>> have;

void recover_ans(int v, int p, int par, int rev_par);

int get_type(int v, int u) {
    int type = 0;
    if (dp[u][0][0] && have.count({v, u}) && have.count({u, v}))
        type += 4;
    bool can_up = false;
    bool can_down = false;
    if (have.count({v, u}) && dp[u][0][1])
        can_down = true;
    if (have.count({u, v}) && dp[u][1][0])
        can_up = true;
    if (have.count({v, u}) && !have.count({u, v}) && dp[u][0][0])
        can_down = true;
    if (!have.count({v, u}) && have.count({u, v}) && dp[u][0][0])
        can_up = true;
    if (can_up && can_down)
        return type + 3;
    if (can_up)
        return type + 2;
    if (can_down)
        return type + 1;
    return type;
}


vector<pair<pair<int, int>, pair<int, int>>> ans;

void add_in(int v, int u) {
    if (used[u])
        return;
    if (dp[u][1][0])
        recover_ans(u, v, 1, 0);
    else
        recover_ans(u, v, 0, 0);
}

void add_out(int v, int u) {
    if (used[u])
        return;
    if (dp[u][0][1])
        recover_ans(u, v, 0, 1);
    else
        recover_ans(u, v, 0, 0);
}

void dfs(int v, int p = -1) {
    used[v] = true;
    int in = 0, out = 0;
    int either = 0;
    int in_add = 0, out_add = 0;
    int either_add = 0;
    bool was = false;
    for (int u : g[v]) {
        if (used[u])
            continue;
        dfs(u, v);
        int type = get_type(v, u);
        was = true;
        if (type >= 4) {
            type -= 4;
            if (type == 1)
                out_add++;
            if (type == 2)
                in_add++;
            if (type == 3)
                either_add++;
            continue;
        }
        if (type == 1)
            out++;
        else if (type == 2)
            in++;
        else if (type == 3)
            either++;
//        else if (!dp[u][1][1]){
//            cout << "No\n";
//            return 0;
//        }
    }
    if (!was) {
        dp[v][0][0] = true;
        if (have.count({v, p}) && have.count({p, v}))
            dp[v][1][1] = true;
        return;
    }
    for (int par = 0; par <= have.count({p, v}); par++) {
        if (par)
            in++;
        for (int rev_par = 0; rev_par <= have.count({v, p}); rev_par++) {
            if (rev_par)
                out++;
            int need = in - out;
            if (abs(need) <= either)
                dp[v][par][rev_par] = ((either - abs(need)) % 2 == 0 || either_add + in_add + out_add >= 1);
            else {
                if (need > 0)
                    dp[v][par][rev_par] = (need - either - either_add - out_add <= 0);
                else
                    dp[v][par][rev_par] = (need + either + either_add + in_add >= 0);
            }
            if (rev_par)
                out--;
        }
    }
//    cout << v + 1 << ":\n";
//    for (int i = 0; i < 2; i++)
//        for (int j = 0; j < 2; j++)
//            cout << dp[v][i][j] << " \n"[j + 1 == 2];
//    cout << '\n';
}

void add(int v, vector<int> &in, vector<int> &out) {
    while (SZ(in) && SZ(out)) {
        int u1 = in.back();
        in.pop_back();
        int u2 = out.back();
        out.pop_back();
        ans.emplace_back(make_pair(u1, v), make_pair(v, u2));
        add_in(v, u1);
        add_out(v, u2);
    }
}

void recover_ans(int v, int p, int par, int rev_par) {
    bool was = false;
    used[v] = true;
//    cout << v + 1 << ' ' << par << ' ' << rev_par << '\n';
    vector<int> in, out;
    vector<int> either;
    vector<int> in_add, out_add;
    vector<int> either_add;
    for (int u : g[v]) {
        if (used[u])
            continue;
        int type = get_type(v, u);
        was = true;
        if (type >= 4) {
            type -= 4;
            if (type == 1)
                out_add.push_back(u);
            if (type == 2)
                in_add.push_back(u);
            if (type == 3)
                either_add.push_back(u);
            continue;
        }
        if (type == 1)
            out.push_back(u);
        if (type == 2)
            in.push_back(u);
        if (type == 3)
            either.push_back(u);
    }
    if (!was) {
        if (par && rev_par)
            ans.emplace_back(make_pair(p, v), make_pair(v, p));
        return;
    }
    if (par)
        in.push_back(p);
    if (rev_par)
        out.push_back(p);
    add(v, in, out);
    add(v, in, either);
    add(v, either, out);
    while (SZ(either) >= 2) {
        int u1 = either.back();
        either.pop_back();
        int u2 = either.back();
        either.pop_back();
        ans.emplace_back(make_pair(u1, v), make_pair(v, u2));
        add_in(v, u1);
        add_out(v, u2);
    }
    add(v, in, out_add);
    add(v, in, either_add);
    add(v, in_add, out);
    add(v, either_add, out);
    add(v, either, out_add);
    add(v, either, either_add);
    add(v, in_add, either);
    for (int u : g[v]) {
        if (!used[u]) {
            if (dp[u][0][0] && have.count({v, u}) && have.count({u, v})) {
                ans.emplace_back(make_pair(u, v), make_pair(v, u));
                recover_ans(u, v, 0, 0);
            } else if (dp[u][1][0] && have.count({v, u}) && !have.count({u, v}))
                recover_ans(u, v, 1, 0);
            else if (dp[u][0][1] && !have.count({v, u}) && have.count({u, v}))
                recover_ans(u, v, 0, 1);
            else if (dp[u][0][0])
                recover_ans(u, v, 0, 0);
        }
    }
}


int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
        have.insert({v, u});
    }
    for (int i = 0; i < n; i++){
        sort(ALL(g[i]));
        g[i].resize(unique(ALL(g[i])) - g[i].begin());
    }
    bool good = true;
    for (int i = 0; i < n; i++)
        if (!used[i]) {
            dfs(i, -1);
            good &= dp[i][0][0];
        }
    if (!good) {
        cout << "No\n";
        return 0;
    }
    fill(used, used + n, false);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            recover_ans(i, -1, 0, 0);
        }
    }
//    sort(ALL(ans));
//    ans.resize(unique(ALL(ans)) - ans.begin());
//    cout << m / 2 - SZ(ans) << '\n';
    if (SZ(ans) != m / 2) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for (auto[aa, bb] : ans) {
        auto[a, b] = aa;
        auto[c, d] = bb;
        cout << a + 1 << ' ' << b + 1 << " " << c + 1 << " " << d + 1 << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b2.in", "r", stdin);
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

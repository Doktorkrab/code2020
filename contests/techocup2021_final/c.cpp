#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
//#define int ll
#define SZ(X) (int)(X).size()
#define ALL(X) (X).begin(), (X).end()
#define RALL(X) (X).rbegin(), (X).rend()
#define TMAX(X) numeric_limits<X>::max();
#define TMIN(X) numeric_limits<X>::min();

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;
int add(int a, int b){
    return ((a + b) % MOD + MOD) % MOD;
}

int mul(int a, int b){
    return (1LL * a * b) % MOD;
}


int n, m;
const int MAXN = 1e5 + 7;
set<int> have[MAXN];
vector<int> rev[MAXN];
int cnt[MAXN];
int cnt1[MAXN];
int ans[MAXN];
int solve(){
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        rev[i].clear();
    for (int j = 0; j < m; j++)
        have[j].clear();
    fill(cnt, cnt + n, 0);
    for (int i = 0; i < m; i++){
        int x;
        cin >> x;
        for (int j = 0; j < x; j++){
            int u;
            cin >> u;
            --u;
            have[i].insert(u);
            rev[u].push_back(i);
        }
        if (x == 1)
            cnt[*have[i].begin()]++;
    }
    if (*max_element(cnt, cnt + n) > (m + 1) / 2){
        cout << "NO\n";
        return 0;
    }
    fill(cnt, cnt + n, 0);
    set<pair<int, int>> frees;
    for (int i = 0; i < m; i++) {
        frees.emplace(cnt1[i] = SZ(have[i]), i);
    }
    while (SZ(frees)){
        auto [a, b] = (*frees.begin());
        frees.erase(frees.begin());
        ans[b] = (*have[b].begin());
        cnt[ans[b]]++;
        if (cnt[ans[b]] == (m + 1) / 2){
            for (int x : rev[ans[b]]){
                if (!frees.count({cnt1[x], x}))
                    continue;
                frees.erase({cnt1[x], x});
                have[x].erase(ans[b]);
                frees.emplace(--cnt1[x], x);
            }
        }
    }
    cout << "YES\n";
    for (int i = 0; i < m; i++)
        cout << ans[i] + 1 << " \n"[i + 1 == m];
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tests = 1;
    cin >> tests;
    for (int test = 1; test <= tests; test++){
        if (solve())
            break;
#ifdef LOCAL
        cout << "-----------\n";
#endif
    }
    return 0;
}

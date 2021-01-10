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

int n, m, k;
void solve1(){
    vector<vector<int>> ans;
    int start = 0;
    for (int iter = 0; iter < (n + m - 1) / m; iter++) {
//        vector<int> works(min(m, n - start));
        vector<int> works(m);
        iota(ALL(works), 1);
        for (int i = 0; i < k; i++) {
            ans.emplace_back(n);
            copy(works.begin(), works.begin() + min(m, n - start), ans[iter * k + i].begin() + start);
            rotate(works.begin(), works.begin() + 1, works.end());
        }
        start += m;
    }
    cout << SZ(ans) << '\n';
    for (const auto &i : ans) {
        for (int j : i)
            cout << j << ' ';
        cout << '\n';
    }
}
int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    if (n % m == 0) {
        solve1();
        return 0;
    }
    vector<int> perm(n);
    vector<vector<int>> was(n, vector<int>(m + 1));
    iota(perm.begin(), perm.begin() + m, 1);
    vector<int> cnt(n, k);
    int prv = 1;
    cout << (n * k + m - 1) / m << '\n';
    for (int i = 0; i < (n * k + m - 1) / m; i++){
        for (int j : perm)
            cout << j << ' ';
        cout << '\n';
        for (int j = 0; j < n; j++)
            if (perm[j]) {
                if (!was[j][perm[j]])
                    cnt[j]--;
                was[j][perm[j]] = 1;
            }
        rotate(perm.begin(), perm.begin() + m, perm.end());
        if (perm[0] == prv) {
            rotate(perm.begin(), perm.begin() + 1, perm.begin() + m);
            prv = perm[0];
        }
    }
    for (int i : cnt)
        assert(i <= 0);
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

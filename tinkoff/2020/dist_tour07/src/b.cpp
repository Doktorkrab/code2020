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

int n, k;
const int MAXN = 5e4 + 7;
unordered_set<int> have[2][MAXN];
int ans[MAXN];
int sums[MAXN];
int solve() {
    if (!(cin >> n >> k))
        return 1;
    vector<int> perm(n);
    iota(ALL(perm), 1);
    for (int i = 0; i < k; i++){
        unordered_set<int> have1{ALL(perm)};
        int x;
        cin >> x;
        for (int j = 0; j < x; j++){
            int y;
            cin >> y;
            have1.erase(y);
            have[0][i].insert(y);
        }
        have[1][i] = have1;
    }
    fill(ans, ans + k, -1);
    int cur = 0;
    while (true){
        int chosen = -1;
        for (int it = 0; it < 2; it++)
            for (int i = 0; i < k; i++)
                if (ans[i] == -1 && (chosen == -1 || SZ(have[chosen / k][chosen % k]) < SZ(have[it][i])))
                    chosen = it * k + i;
        if (chosen == -1)
            break;
        ans[chosen % k] = chosen / k;
        cur += SZ(have[chosen / k][chosen % k]);
        for (int x : have[chosen / k][chosen % k])
            for (int it = 0; it < 2; it++)
                for (int i = 0; i < k; i++)
                    if (i != chosen % k)
                        have[it][i].erase(x);

    }
    assert(cur >= n / 2);
    for (int i = 0; i < k; i++) {
        assert(ans[i] != -1);
        cout << ans[i];
    }
    cout << '\n';
//    cout << cur << '\n';
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

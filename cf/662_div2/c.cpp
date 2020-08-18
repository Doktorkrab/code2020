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
 
const int MAXN = 1e5 + 7;

int arr[MAXN];
int n;
int cnt[MAXN];
int cnt1[MAXN];
int cnt2[MAXN];
int ans[MAXN];
set<pair<int, int>> can_use;

bool check(int x){
    can_use.clear();
    for (int i = 0; i < n; i++){
        can_use.insert({cnt[arr[i]], arr[i]});
        cnt1[arr[i]] = 0;
        cnt2[arr[i]] = cnt[arr[i]];
    }

    for (int i = 0; i < n; i++){
        if (i - x - 1 >= 0){
            // cout << ans[i - x - 1] << "\n";
            // cout << cnt2[ans[i - x - 1]] << '\n';
            cnt1[ans[i - x - 1]]--;
            if (cnt2[ans[i - x - 1]] > 0)
                can_use.insert({cnt2[ans[i - x - 1]], ans[i - x - 1]});
        }
        // cout << i << ' ' << SZ(can_use) << '\n';
        // for (int j = 0; j < n; j++)
        //     cout << ans[j] << " \n"[j + 1 == n];
        if (SZ(can_use) == 0)
            return false;
        ans[i] = can_use.rbegin()->second;
        can_use.erase(prev(can_use.end()));
        cnt1[ans[i]]++;
        cnt2[ans[i]]--;
    }
    return true;
}
int solve() {
    if (!(cin >> n))
        return 1;
    fill(cnt, cnt + MAXN, 0);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        cnt[arr[i]]++;
    }
    int l = 0, r = n;
    while (r - l > 1){
        int m = (l + r) / 2;
        if (check(m))
            l = m;
        else
            r = m;
    }
    cout << l << '\n';
    // cout << check(4) << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
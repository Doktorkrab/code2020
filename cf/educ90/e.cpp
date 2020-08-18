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
 
ll n, k;


 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    k++;
    // if (n - k * (k - 1) / 2 >= 0 && (n - k * (k - 1) / 2) % k == 0){
    //     ll x = (n - k * (k - 1) / 2) / k;
    //     string ans;
    //     for (int i = 0; i < x / 9; i++)
    //         ans += '9';
    //     if (x % 9)
    //         ans = to_string(x % 9) + ans;
    //     cout <<  ans << "0\n";
    //     return 0;
    // }
    // cout << "-1\n";
    vector<pair<int, string>> kek;
    for (int nines = 0; 9 * nines <= n; nines++){
        for (int start = 0; start <= 9; start++){
            int withPrefix = min(k, 10LL - start);
            int plusOne = k - withPrefix;
            int sum = 0;
            for (int x = 0; x < k; x++)
                sum += (x + start) % 10;
            if (n - 9 * nines * withPrefix - plusOne - sum >= 0 && (n - 9 * nines * withPrefix - plusOne - sum) % k == 0){
                ll prefix = (n - 9 * nines * withPrefix - plusOne - sum) / k;
                // cout << nines << ' ' << start << ' ' << prefix << '\n';
                string ans;

                if (prefix < 9)
                    ans += '0' + prefix;
                else {
                    prefix -= 8;
                    if (prefix % 9 > 0)
                        ans += '0' + (prefix % 9);
                    while (prefix >= 9){
                        ans += '9';
                        prefix -= 9;
                    }
                    ans += '8';
                }
                // cout << ans;
                for (int i = 0; i < nines; i++)
                    ans += "9";
                // if (nines > 0)
                ans += '0' + start;
                reverse(ALL(ans));
                // cout << ans << '\n';
                while (SZ(ans) > 1 && ans.back() == '0')
                    ans.pop_back();
                reverse(ALL(ans));
                if (SZ(ans) == 0)
                    ans = "0";
                kek.push_back({SZ(ans), ans});
                // cout << ans << '\n';
                // return 0;
            }

        }
    }
    sort(ALL(kek));
    if (SZ(kek))
        cout << kek[0].second << '\n';
    else
        cout << "-1\n";
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
// #ifdef LOCAL
//         cout << "------------------------------\n";
// #endif
    }
}
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
const int MAXN = 1e5 + 7;
ll arr[MAXN];
ll arr1[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    ll ans = TMAX(ll);
    for (int i = 0; i < n; i++) {
        ll have_ge = 0;
        ll have_le = 0;
        ll cnt_ge = 0;
        ll cnt_le = 0;
        for (int j = 0; j < n; j++) {
            arr1[j] = arr[j] + abs(i - j);
        }
        sort(arr1, arr1 + n);
        for (int j = 0; j < n; j++) {
            if (arr[j] >= arr1[0] - abs(i - j)) {
                have_ge += arr[j] + abs(i - j);
                cnt_ge++;
            } else {
                have_le += arr[j] + abs(i - j);
                cnt_le++;
            }
        }
//        cout << "!" << cnt_ge << ' ' << have_ge << ' ' << cnt_le << ' ' << have_le << '\n';
        bool was = false;
        for (int j = 0; j < n; j++) {
            have_ge -= arr1[j];
            cnt_ge--;
            have_le += arr1[j];
            cnt_le++;
            if (arr1[j] - i <= 0 || arr1[j] - (n - 1 - i) <= 0) {
//                cout << i << ' ' << arr1[j] << '\n';
                continue;
            }
            cout << i << ' ' << arr1[j] << ' '
                 << have_ge - cnt_ge * arr1[j] + cnt_le * arr1[j] - have_le << '\n';
            was = true;
//            cout << '\t' << cnt_ge << ' ' << have_ge << ' ' << cnt_le << ' ' << have_le << '\n';
            ans = min(ans, have_ge - cnt_ge * arr1[j] + cnt_le * arr1[j] - have_le);
        }
    }
    cout << ans << '\n';
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

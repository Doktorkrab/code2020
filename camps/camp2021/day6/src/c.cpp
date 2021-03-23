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
#define int ll
int n;
const int MAXN = 1e5 + 7;
int arr[MAXN];

int solve_eq() {
    if (arr[0] == 9) {
        int cnt = 0;
        int cnt1 = 1;
        while (cnt1 < n)
            cnt1 = cnt1 * 10 + 1,cnt++;
        int ans = 0;
        for (int i = 0; i < cnt; i++)
            ans = 10 * ans + 8;
        return ans * 10 + 9;
    }
    if (arr[0] == 0){
        int power = 10;
        int power1 = 11;
        while (power1 - power < n){
            power *= 10;
            power1 *= 10;
            power1 += 1;
        }
        return power;
    }
    int power = 1;
    if (arr[0] == 0)
        arr[0] = 10;
    while (power + (arr[0] == 0) < n)
        power *= 10;
    return arr[0] * power;

}

int solve_slow() {
    for (int start = 1; start <= 1000; start++) {
        bool good = true;
        for (int i = 0; i < n; i++) {
            string now = to_string(start + i);
            if (count(ALL(now), arr[i] + '0') == 0) {
                good = false;
                break;
            }
        }
        if (good) {
            return start;
        }
    }
    assert(0);
}

int solve() {
    if (!(cin >> n))
        return 1;
    bool all_eq = true;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        all_eq &= (arr[i] == arr[0]);
    }
    int ans;
    if (all_eq)
        ans = solve_eq();
    else
        ans = solve_slow();
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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

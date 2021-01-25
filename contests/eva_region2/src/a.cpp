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
const int MAXN = 1005;
string arr[MAXN];
int sum_r[MAXN], sum_c[MAXN];
int q_r[MAXN], q_c[MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == '+')
                sum_r[i]++, sum_c[j]++;
            else if (arr[i][j] == '-')
                sum_r[i]--, sum_c[j]--;
            else
                q_r[i]++, q_c[j]++;
        }
    }
//    for (int i = 0; i < n; i++)
//        cout << sum_r[i] << ' ' << q_r[i] << '\n';
//    cout << "---\n";
//    for (int i = 0; i < m; i++)
//        cout << sum_c[i] << " " << q_c[i] << '\n';
    int best = TMIN(int);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int now = sum_r[i] - sum_c[j] + q_r[i] + q_c[j] - 2 * (arr[i][j] == '?');
            best = max(best, now);
        }
    }
    cout << best << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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

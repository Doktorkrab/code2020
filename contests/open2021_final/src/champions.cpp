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
const int MAXC = 5e6 + 7;
int p1[MAXC];
int p2[MAXC];
int p3[MAXC];
int arr[MAXC];
pair<int, int> was[2 * MAXC];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    fill(p1, p1 + MAXC, -1);
    fill(p2, p2 + MAXC, -1);
    fill(p3, p3 + MAXC, -1);
    for (int i = 0; i < n; i++) {
        int d = arr[i];
        if (p1[d] == -1) {
            p1[d] = i;
            continue;
        }
        if (p2[d] == -1) {
            p2[d] = i;
            continue;
        }
        if (p3[d] == -1) {
            p3[d] = i;
            continue;
        }
        cout << "YES\n";
        cout << p1[d] + 1 << ' ' << p2[d] + 1 << ' ' << p3[d] + 1 << ' ' << i + 1 << '\n';
        return 0;
    }
    int two = -1;
    vector<int> have;
    for (int i = 0; i < MAXC; i++) {
        if (p1[i] == -1)
            continue;
        have.push_back(p1[i]);
        if (p2[i] == -1)
            continue;
        if (two != -1) {
            cout << "YES\n";
            cout << p1[two] + 1 << ' ' << p1[i] + 1 << ' ' << p2[two] + 1 << ' ' << p2[i] + 1 << '\n';
            return 0;
        }
        two = i;
    }
    fill(was, was + 2 * MAXC, make_pair(-1, -1));
    if (two != -1) {
        was[two * 2] = {p1[two], p2[two]};
    }
    for (int i = 0; i < SZ(have); i++) {
        for (int j = i + 1; j < SZ(have); j++) {
            ll sum = arr[have[i]] + arr[have[j]];
            if (was[sum].first != -1) {
                cout << "YES\n";
                cout << was[sum].first + 1 << ' ' << was[sum].second + 1 << ' ' << have[i] + 1 << ' ' << have[j] + 1 << '\n';
                return 0;
            }
            was[sum] = make_pair(have[i], have[j]);
        }
    }
    cout << "NO\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("champions.in", "r", stdin);
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

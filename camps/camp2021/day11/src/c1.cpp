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
const int MAXN = 6e4 + 7;
int l[MAXN], r[MAXN], s[MAXN];
bool was[MAXN];
set<int> cnt[MAXN];
bool ok[MAXN];

int solve() {
    if (!(cin >> n >> k))
        return 1;
    n *= 2;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i] >> s[i];
        l[i]--, r[i]--;
        cnt[l[i]].insert(i);
        cnt[r[i] + n / 2].insert(i);
    }
    set<pair<int, int>> have;
    for (int i = 0; i < n; i++)
        have.emplace(SZ(cnt[i]), i);
    while (SZ(have) && (have.begin()->first < 2)) {
        auto[a, b] = (*have.begin());
        have.erase(have.begin());
//        cout << a << ' ' << b << '\n';
        if (a == 0) {
            cout << "NO\n";
            return 0;
        }
        ok[b] = true;
        int index = (*cnt[b].begin());
        have.erase({SZ(cnt[l[index]]), l[index]});
        have.erase({SZ(cnt[r[index] + n / 2]), r[index] + n / 2});
        cnt[l[index]].erase(index);
        cnt[r[index] + n / 2].erase(index);
        if (!ok[l[index]])
            have.insert({SZ(cnt[l[index]]), l[index]});
        if (!ok[r[index] + n / 2])
            have.insert({SZ(cnt[r[index] + n / 2]), r[index] + n / 2});
    }
    if (n > 20) {
        cout << "YES\n";
        return 0;
    }
    for (int mask = 0; mask < (1 << n); mask++) {
        int sum = 0;
        fill(was, was + n, false);
        bool good = true;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (was[r[i] + n / 2]) {
                    good = false;
                    break;
                }
                was[r[i] + n / 2] = true;
                sum += s[i];
            } else {
                if (was[l[i]]) {
                    good = false;
                    break;
                }
                was[l[i]] = true;
                sum -= s[i];
            }
        }
        if (good && abs(sum) <= k) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
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
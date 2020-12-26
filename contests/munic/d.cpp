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

int a, b;

unordered_set<int> get_f(int x) {
    if (x == 1)
        return {1};
    unordered_set<int> res;
    int y = x;
    for (int f = 2; 1LL * f * f <= y; f++) {
        if (x % f == 0) {
            res.insert(f);
            x /= f;
            if (x % f == 0)
                return {};
        }
    }
    if (x > 1)
        res.insert(x);
    return res;
}

bool check(const unordered_set<int> &a, const unordered_set<int> &b) {
    for (int x : a)
        if (b.count(x))
            return false;
    return true;
}

int solve() {
    if (!(cin >> a >> b))
        return 1;
    vector<unordered_set<int>> have;
    for (int i = a; i <= b; i++) {
        have.push_back(get_f(i));
//        cout << i << ": ";
//        for (int x : have.back())
//            cout << x << ' ';
//        cout << '\n';
        if (SZ(have.back()) == 0)
            have.pop_back();
    }
    ll ans = 0;
    for (int i = 0; i < SZ(have); i++) {
        for (int j = i + 1; j < SZ(have); j++) {
            if (check(have[i], have[j])) {
                ans++;
//                cout << i << ' ' << j << '\n';
            }
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

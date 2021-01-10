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


int solve() {
    if (!(cin >> n >> m))
        return 1;
    if (n > m) {
        for (int i = 0; i < m; i++)
            cout << "$ 0" << endl;
        return 0;
    }
    vector<int> pi(n + 1 + m); // s # t
    map<pair<int, int>, bool> cache;
    int asked = 0;
    int answered = 0;
    int ans = 0;
    auto print = [&]() {
        asked = 0;
        answered++;
        cout << "$ " << ans << endl;
    };
    auto get = [&](int x) {
        if (x < n)
            return "s " + to_string(x + 1);
        return "t " + to_string(x - n);
    };
    auto ask = [&](int i, int j) {
//        cerr << i << ' ' << j << '\n';
        if (i > j)
            swap(i, j);
        if (i == j)
            return true;
        if (cache.count({i, j}))
            return cache[{i, j}];
        if (i == n || j == n)
            return false;
        if (asked == 5)
            print();
        asked++;
        cout << get(i) << ' ' << get(j) << endl;
        string ans;
        cin >> ans;
        return cache[{i, j}] = (ans == "Yes");
    };
    for (int i = 1; i < n + m + 1; i++) {
        while (i - n - 1 > answered)
            print();
        int j = pi[i - 1];
        while (j > 0 && !ask(i, j)) {
//            cerr << '\t' << i << ' ' << j << '\n';
            j = pi[j - 1];
        }
        if (ask(i, j))
            j++;
        pi[i] = j;
        if (pi[i] == n)
            ans++;
    }
    cout << "$ " << ans << endl;
    return 0;
}

signed main() {
//#ifdef LOCAL
//    freopen("c.in", "r", stdin);
//#endif
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
    int tests = 1;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

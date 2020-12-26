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


int solve() {
    int n, m;
    if (!(cin >> n >> m))
        return 1;
    if (n > m) {
        for (int i = 0; i < m; i++) {
            cout << "$ 0" << endl;
        }
        return 0;
    }
    vector<int> p_f(n + 1 + m);
    map<pair<int, int>, bool> cache;
    int cnt = 0, cnt1 = 0;
    int cnt2 = 0;
    auto f = [&]() {
        cnt = 0;
        cnt2++;
        cout << "$ " << cnt1 << endl;
    };
    auto ask = [&](int i, int j) {
        if (i == n || j == n)
            return false;
        if (cnt == 5) {
            f();
        }
        cnt++;
        if (cache.count({i, j}))
            return cache[{i, j}];
        if (i < n)
            cout << "s " << i + 1 << ' ';
        else
            cout << "t " << i - n << ' ';
        if (j < n)
            cout << "s " << j + 1 << endl;
        else
            cout << "t " << j - n << endl;
        string ans;
        cin >> ans;
        return cache[{i, j}] = cache[{j, i}] = ans == "Yes";
    };
    for (int i = 1; i < n + 1 + m; i++) {
        while (i - n - 1 > cnt2)
            f();
        int j = p_f[i - 1];
        while (j > 0 && !ask(i, j))
            j = p_f[j - 1];
        if (ask(i, j))
            j++;
        p_f[i] = j;
        if (p_f[i] == n)
            cnt1++;
    }
    for (int i : p_f)
        cerr << i << ' ';
    cerr << '\n';
    cout << "$ " << cnt1 << endl;
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

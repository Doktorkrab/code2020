#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>

using namespace std;
int n, m, k;
vector<vector<int>> arr;
vector<int> column;
vector<int> count_sort;

inline void init() {
    arr.resize(max(n, m), vector<int>(max(n, m)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            arr[i][j] = (x == '1');
        }
    }
    if (n > m) {
        swap(n, m);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < m; j++)
                swap(arr[j][i], arr[i][j]);
    }

    column.resize(m);
    count_sort.resize(n + 1);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            // cerr << i << ' ' <<  j << ' ' << arr[j][i] << '\n';
            column[i] |= (arr[j][i] << j);
        }
}

inline void solve() {
    init();
    // for (int i = 0; i < n; i++)
    //     for (int j = 0; j < m; j++)
    //         cerr << arr[i][j] << " \n"[j == m - 1];
    // cerr << '\n';
    // for (int i = 0; i < m; i++)
    //     cerr << column[i] << " \n"[i == m - 1];
    int can = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) > k)
            continue;
        int now = k - __builtin_popcount(mask);

        int ans = 0;
        int mx = -1;
        for (int i = 0; i < m; i++) {
            int bits = __builtin_popcount(mask ^ column[i]);
            int diff = n - bits - bits;
            // cerr << '\t' << i << ' ' << bits << ' ' << (mask ^ column[i]) << '\n';
            ans += bits;
            if (diff > 0)
                count_sort[diff]++;
            mx = max(diff, mx);
        }
        int pnt = mx;
        // cerr << mask << ' ' << ans << '\n';
        // cerr << "!" << now << ' ' << mx << '\n';
        while (now > 0 && pnt > 0) {
            int took = min(now, count_sort[pnt]);
            ans += pnt * took;
            now -= took;
            count_sort[pnt] -= took;
            if (count_sort[pnt] == 0)
                --pnt;
        }
        can = max(ans, can);
        // cerr << mask << ' ' << ans << '\n';
        for (int i = 0; i <= n; i++)
            count_sort[i] = 0;
    }
    cout << can << '\n';
}


int main() {
#ifdef LOCAL
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n >> m >> k)
        solve();
}

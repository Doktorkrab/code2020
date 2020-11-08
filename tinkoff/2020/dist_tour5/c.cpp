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

const int MAXN = 1e3 + 7;
int cnt[MAXN][MAXN];
int sums[MAXN][MAXN];

int get_sum(int x1, int y1, int x2, int y2) {
    return sums[x2][y2] - sums[x2][y1] - sums[x1][y2] + sums[x1][y1];
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    assert(m < 30 && n * (1LL << m) < 300000000);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            cnt[i][j] = (x == '*');
            sums[i + 1][j + 1] = sums[i][j + 1] + sums[i + 1][j] + cnt[i][j] - sums[i][j];
        }
    int min_diff = sums[n][m]; // all 1
    int when = -1;
    bool row = true;
    for (int i = 0; i < n; i++) {
        int sum = get_sum(0, 0, n - i, m / 2) + get_sum(0, m / 2, i, m);
        if (abs(sums[n][m] - 2 * sum) < min_diff) {
            min_diff = abs(sums[n][m] - 2 * sum);
            when = i;
        }
    }
    if ((n & 1) == 0) {
        for (int i = 0; i < m; i++) {
            int sum = get_sum(0, 0, n / 2, m - i) + get_sum(n / 2, 0, n, i);
            if (abs(sums[n][m] - 2 * sum) < min_diff) {
                min_diff = abs(sums[n][m] - 2 * sum);
                when = i;
                row = false;
            }
        }
    }
    if (when == -1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << "1";
            cout << '\n';
        }
        return 0;
    }
    if (row) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m / 2; j++) {
                if (i < n - when)
                    cout << "1";
                else
                    cout << "2";
            }
            for (int j = m / 2; j < m; j++)
                if (i < when)
                    cout << "1";
                else
                    cout << "2";
            cout << '\n';
        }
    } else {
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < m; j++)
                if (j < m - when)
                    cout << "1";
                else
                    cout << "2";
            cout << '\n';
        }
        for (int i = n / 2; i < n; i++) {
            for (int j = 0; j < m; j++)
                if (j < when)
                    cout << "1";
                else
                    cout << "2";
            cout << '\n';
        }
    }
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

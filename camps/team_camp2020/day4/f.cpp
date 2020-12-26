#pragma GCC optimize("O3")

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

const int N = 5000;
const int Q = 1e6;


int w, h, n;
char s[Q];
int a[4][Q];
int row[N], coloumn[N];
int f[N][N];
int lol[N + 1];
int lolo[N + 1];

const int MOD = 1e9 + 7;

int sum(int x, int y) { return x + y < MOD ? x + y : x + y - MOD; }

int mul(int x, int y) { return x * 1LL * y % MOD; }

int qp(int x, int k) {
    int res = 1;
    while (k) {
        if (k & 1) {
            res = mul(res, x);
        }
        x = mul(x, x);
        k >>= 1;
    }
    return res;
}

int solve() {
    if (!(cin >> h >> w >> n))
        return 1;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    for (int i = 0; i < 4; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            cin >> a[i][j];
        }
        while (k != n) {
            a[i][k] = (a[i][k - 2] * 10007LL + a[i][k - 1] * 10009LL + 87277LL) % (i % 2 == 0 ? h : w);
            k++;
        }
    }
    int kek = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            f[i][j] = kek++;
        }
    }
    iota(row, row + h, 0);
    iota(coloumn, coloumn + w, 0);
    lol[0] = lolo[0] = 1;
    for (int i = 1; i <= h; i++)
        lol[i] = mul(lol[i - 1], 17);
    for (int j = 1; j <= w; j++)
        lolo[j] = mul(lolo[j - 1], 19);
    for (int i = 0; i < n; ++i) {
//        cout << a[0][i] << ' ' << a[1][i] << ' '  << a[2][i] << ' ' << a[3][i] << '\n';
        if (s[i] == 'c') {
            swap(coloumn[a[1][i]], coloumn[a[3][i]]);
        } else if (s[i] == 'r') {
            swap(row[a[0][i]], row[a[2][i]]);
        } else {
            swap(f[row[a[0][i]]][coloumn[a[1][i]]], f[row[a[2][i]]][coloumn[a[3][i]]]);
        }
//        for (int j = 0; j < w; j++)
//            cout << coloumn[j] << " \n"[j + 1 == w];
    }
    int ans = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
//            cout << f[i][j] << ": " << row[i] << ' ' << coloumn[j] << '\n';
            ans = sum(ans, mul(mul(f[row[i]][coloumn[j]], lol[i]), lolo[j]));
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

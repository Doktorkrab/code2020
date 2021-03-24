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
const int MAXN = 2e3 + 7;
const int MAXC = 10;
char fld[MAXN][MAXN];
bool used[MAXN][MAXN];
int p[MAXN * MAXN];
int sz[MAXN * MAXN];
int cnt[MAXC][MAXN * MAXN];
int mx[MAXN * MAXN];

int find(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find(p[x]);
}

void un(int a, int b) {
    a = find(a);
    b = find(b);
    if (sz[a] > sz[b])
        swap(a, b);
    if (a == b)
        return;
    sz[b] += sz[a];
    p[a] = b;
}

void find_vertical() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            used[i][j] = false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (used[i][j] || fld[i][j] == '.')
                continue;
            int xs = i;
            while (xs >= 0 && fld[xs][j] != '.')
                xs--;
            xs++;
            int xe = i;
            while (xe < n && fld[xe][j] != '.')
                xe++;
            for (int k = 0; k < xe - xs; k++) {
                used[xs + k][j] = true;
                un((xs + k) * m + j, (xe - k - 1) * m + j);
            }
        }
}

void find_horizontal() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            used[i][j] = false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (used[i][j] || fld[i][j] == '.')
                continue;
            int ys = j;
            while (ys >= 0 && fld[i][ys] != '.')
                ys--;
            ys++;
            int ye = j;
            while (ye < m && fld[i][ye] != '.')
                ye++;
            for (int k = 0; k < ye - ys; k++) {
                used[i][ys + k] = true;
                un(i * m + ys + k, i * m + ye - k - 1);
            }
        }
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    iota(p, p + n * m, 0);
    fill(sz, sz + n * m, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> fld[i][j];
    find_horizontal();
    find_vertical();
    for (int i = 0; i < n * m; i++)
        if (fld[i / m][i % m] != '.')
            cnt[fld[i / m][i % m] - '0'][find(i)]++;
    for (int i = 0; i < n * m; i++){
        if (fld[i / m][i  % m] == '.')
            continue;
        int x = find(i);
        int best = TMAX(int);
        int kek = -1;
        for (int nx = 0; nx < 10; nx++) {
            int now = 0;
            for (int j = 0; j < 10; j++)
                now += abs(j - nx) * cnt[j][x];
            if (now < best){
                best = now;
                kek = nx;
            }
        }
        mx[x] = kek;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fld[i][j] == '.')
                cout << ".";
            else {
                int x = find(i * m + j);
                cout << mx[x];
            }
        }
        cout << '\n';
    }
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

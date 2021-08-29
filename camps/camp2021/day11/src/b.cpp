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
const int MAXN = 55;

bool recover(int i, int j, vector<pair<int, int>> &ans, vector<vector<char>> &fld) {
    if (j + 1 == m || i + 1 == n)
        return false;
    if (fld[i][j + 1] == 'U') {
        ans.emplace_back(i, j);
        fld[i][j] = fld[i + 1][j] = 'L';
        fld[i][j + 1] = fld[i + 1][j + 1] = 'R';
        return true;
    }
    if (fld[i + 1][j + 1] == 'U' && !recover(i + 1, j + 1, ans, fld))
        return false;
    ans.emplace_back(i, j + 1);
    ans.emplace_back(i, j);
    if (j + 2 >= m)
        return false;
    fld[i][j] = fld[i + 1][j] = 'L';
    fld[i][j + 1] = fld[i + 1][j + 1] = 'R';
    fld[i][j + 2] = 'U';
    fld[i + 1][j + 2] = 'D';
    return true;


}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    vector<vector<char>> fld(n, vector<char>(m));
    vector<vector<char>> fld1(n, vector<char>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> fld[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> fld1[i][j];
    bool swapped = false;
    if (fld == fld1){
        cout << "0\n";
        return 0;
    }
    if (m % 2) {
        swapped = true;
        vector<vector<char>> tmp(m, vector<char>(n));
        for (int i = 0; i < n; i++)
            for (int j = m - 1; j >= 0; j--)
                tmp[m - j - 1][i] = fld[i][j];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (tmp[i][j] == 'U')
                    tmp[i][j] = 'L';
                else if (tmp[i][j] == 'D')
                    tmp[i][j] = 'R';
                else if (tmp[i][j] == 'R')
                    tmp[i][j] = 'U';
                else
                    tmp[i][j] = 'D';
        fld = tmp;
        for (int i = 0; i < n; i++)
            for (int j = m - 1; j >= 0; j--)
                tmp[m - j - 1][i] = fld1[i][j];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (tmp[i][j] == 'U')
                    tmp[i][j] = 'L';
                else if (tmp[i][j] == 'D')
                    tmp[i][j] = 'R';
                else if (tmp[i][j] == 'R')
                    tmp[i][j] = 'U';
                else
                    tmp[i][j] = 'D';
        fld1 = tmp;
        swap(n, m);
    }
    vector<pair<int, int>> ans;
//    for (auto& a : fld){
//        for (auto b : a)
//            cout << b;
//        cout << '\n';
//    }
    for (int i = 0; i + 1 < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fld[i][j] == 'L' || fld[i][j] == 'R')
                continue;
            if (!recover(i, j, ans, fld)) {
                cout << "-1\n";
                return 0;
            }
        }
    }
    vector<pair<int, int>> ans1;
    for (int i = 0; i + 1 < n; i++)
        for (int j = 0; j < m; j++) {
            if (fld1[i][j] == 'L' || fld1[i][j] == 'R')
                continue;
            if (!recover(i, j, ans1, fld1)) {
                cout << "-1\n";
                return 0;
            }
        }
    ans.insert(ans.end(), RALL(ans1));
    assert(SZ(ans) <= 100000);
    cout << SZ(ans) << '\n';
    for (auto[a, b] : ans){
//        cout << '\t' << a << ' ' << b << '\n';
        if (swapped)
            cout << b + 1 << ' ' << n - (a + 1) << '\n';
        else
            cout << a + 1 << ' ' << b + 1 << '\n';
    }
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

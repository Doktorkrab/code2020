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
const int MAXN = 105;
char fld[MAXN][305];
string aaa;
string have1;
int bal = 0;
int y;

void rec(int pos) {
    if (y < 0 || y >= m)
        return;
    if (bal == 0 && (fld[pos][y] == '*' || pos == n)) {
        if (SZ(have1) > SZ(aaa))
            aaa = have1;
        if (SZ(have1) == SZ(aaa) && have1 < aaa)
            aaa = have1;
        return;
    }
    if (fld[pos][y] == '*' || pos == n)
        return;
    if (fld[pos][y] == '(')
        bal++;
    if (fld[pos][y] == ')')
        bal--;
    if (fld[pos][y] == '(' || fld[pos][y] == ')')
        have1 += fld[pos][y];
//    cout << bal << ' ' << have1 << '\n';
    if (bal < 0) {
        bal++;
        have1.pop_back();
        return;
    }
    rec(pos + 1);
    y++;
    rec(pos + 1);
    y -= 2;
    rec(pos + 1);
    y++;
    if (fld[pos][y] == '(')
        bal--;
    if (fld[pos][y] == ')')
        bal++;
    if (fld[pos][y] == '(' || fld[pos][y] == ')')
        have1.pop_back();


}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = n - 1; i >= 0; i--)
        for (int j = 0; j < m; j++)
            cin >> fld[i][j];
    while (fld[0][y] != 'M')
        ++y;
    rec(0);
    cout << SZ(aaa) << '\n' << aaa << '\n';
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

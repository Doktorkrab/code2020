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

const int MAXN = 1e6;
string have[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> have[i];
    vector<int> perm(n);
    iota(ALL(perm), 0);
    do{
        string now;
        for (int i : perm)
            now += have[i];
        int bal = 0;
        bool good = true;
        for (char c : now){
            if (c == '(')
                bal++;
            if (c == ')')
                bal--;
            if (bal < 0)
                good = false;
        }
        good &= (bal == 0);
        if (good) {
            cout << "Yes\n";
            return 0;
        }
    } while (next_permutation(ALL(perm)));

    cout << "No\n";
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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

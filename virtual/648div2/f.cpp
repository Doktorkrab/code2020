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
const int MAXN = 505;
int a[MAXN], b[MAXN];
map<pair<int, int>, int> have;
 
int solve() {
    if (!(cin >> n))
        return 1;
    have.clear();
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    if ((n & 1) && a[n / 2] != b[n / 2]){
        cout << "No\n";
        return 0;
    }
    for (int i = 0; i < n /2; i++){
        pair<int, int> t = {a[i], a[n - i - 1]};
        if (t.first > t.second)
            swap(t.first, t.second);
        have[t]++;
    }

    for (int i = 0; i < n /2; i++){
        pair<int, int> t = {b[i], b[n - i - 1]};
        if (t.first > t.second)
            swap(t.first, t.second);
        have[t]--;
    }
    for (auto [_, y] : have){
        if (y < 0){
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
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
 
const int MAXN = 1e5 + 7;
int n;
int arr[MAXN];
set<pair<int, int>> have;
 
int solve() {
    if (!(cin >> n))
        return 1;
    fill(arr, arr + MAXN, 0);
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        arr[x]++;
    }
    for (int i = 0; i < MAXN; i++)
        have.insert({arr[i], i});
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        char x;
        cin >> x;
        int y;
        cin >> y;
        have.erase({arr[y], y});
        if (x == '+')
            arr[y]++;
        else
            arr[y]--;
        have.insert({arr[y], y});
        if (have.rbegin()->first < 4){
            cout << "NO\n";
            continue;
        }
        // int have_left = 0;
        if (have.rbegin()->first >= 8)
            cout << "YES\n";
        else if (have.rbegin()->first >= 6 && next(have.rbegin())->first >= 2)
            cout << "YES\n";
        else if (next(have.rbegin())->first >= 4)
            cout << "YES\n";
        else if (next(have.rbegin())->first >= 2 && next(next(have.rbegin()))->first >= 2)
            cout << "YES\n";
        else
            cout << "NO\n";
        // auto it = have.rbegin();
        // while (it != have.rend() && it->first > 0){
        //     cout << "{" << it->first << ", " << it->second << "} ";
        //     it++;
        // }
        // cout << '\n';
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
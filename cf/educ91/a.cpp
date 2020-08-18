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
const int MAXN = 1e3 + 7;
int arr[MAXN];
int pr_min[MAXN], sf_min[MAXN];
int pr_ind[MAXN], sf_ind[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    pr_min[0] = TMAX(int);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        if (pr_min[i] > arr[i]){
            pr_min[i + 1] = arr[i];
            pr_ind[i + 1] = i;
        }
        else{
            pr_min[i + 1] = pr_min[i];
            pr_ind[i + 1] = pr_ind[i];
        }
    }
    sf_min[n - 1] = TMAX(int);
    for (int i = n - 2; i >= 0; i--){
        if (sf_min[i + 1] > arr[i + 1]){
            sf_min[i] = arr[i + 1];
            sf_ind[i] = i + 1;
        }
        else {
            sf_min[i] = sf_min[i + 1];
            sf_ind[i] = sf_ind[i + 1];
        }
    }
    for (int i = 1; i + 1 < n; i++){
        if (pr_min[i] < arr[i] && arr[i] > sf_min[i]){
            cout << "YES\n";
            cout << pr_ind[i] + 1 << ' ' << i + 1 << ' ' << sf_ind[i] + 1 << '\n';
            return 0;
        }
    }
    cout << "NO\n";
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
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
 
int n, k;
const int MAXN = 1e5 + 7;
pair<int, int> arr[MAXN];

 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr, arr + n);
    vector<int> now;
    vector<int> best;
    for (int i = 0; i < n; i++){
        if (SZ(now) && abs(arr[now.back()].first - arr[i].first) > k){
            if (SZ(best) < SZ(now))
                best = now;
            now.clear();
        }
        now.push_back(i);
    }
    if (SZ(best) < SZ(now))
        best = now;
    cout << SZ(best) << '\n';
    for (int i : best)
        cout << arr[i].second + 1 << ' ';
    cout << '\n';
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

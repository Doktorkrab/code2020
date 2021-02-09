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
const int MAXN = 1e5 + 7;
const int MAXLOG = 31;
vector<int> have[MAXLOG];
int arr[MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < MAXLOG; i++)
        have[i].clear();
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        for (int j = 0; j < MAXLOG; j++)
            if (arr[i] & (1 << j))
                have[j].push_back(i);
    }
    for (int j = MAXLOG - 1; j >= 1; j--){
        int now = INT_MAX;
        for (int x : have[j])
            now &= arr[x];
        if (j == 0 || (now & ((1 << j) - 1)) == 0){
            cout << SZ(have[j]) << '\n';
            for (int x : have[j])
                cout << arr[x] << ' ';
            cout << '\n';
            return 0;
        }
    }
    cout << n << '\n';
    for (int i = 0; i < n; i++)
        cout << arr[i] << " \n"[i + 1 == n];
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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

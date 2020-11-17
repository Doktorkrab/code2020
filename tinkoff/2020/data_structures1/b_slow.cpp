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
const int MAXN = 5e4 + 7;
int arr[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;
        if (type == 'C') {
            int pos, x;
            cin >> pos >> x;
            arr[pos - 1] = x;
            continue;
        }
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--;
        int ans1 = 0;
        int ans2 = 0;
        for (int j = x1; j < x2; j++) {
//            cout << y2 - arr[j] << ' ' << arr[j] - y1 << '\n';
            if (y2 - arr[j] > arr[j] - y1)
                ans2++;
            else if (y2 - arr[j] < arr[j] - y1)
                ans1++;
        }
        if (ans1 > ans2)
            cout << "2\n";
        else if (ans1 < ans2)
            cout << "1\n";
        else
            cout << "0\n";
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

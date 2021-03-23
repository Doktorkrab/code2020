#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define SZ(X) (int)(X).size()
#define ALL(X) (X).begin(), (X).end()
#define RALL(X) (X).rbegin(), (X).rend()
#define TMAX(X) numeric_limits<X>::max();
#define TMIN(X) numeric_limits<X>::min();

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;

int add(int a, int b) {
    return ((a + b) % MOD + MOD) % MOD;
}

int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}


int n;
const int MAXN = 1e5;
int arr[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    int c = -1, m = -1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 1; i < n; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff >= 0) {
            if (c != -1 && diff != c) {
                cout << "-1\n";
                return 0;
            }
            c = diff;
            continue;
        }
    }
    int c1 = -1;
    for (int i = 1; i < n; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff < 0) {
            if (c1 == -1)
                c1 = -diff;
            if (c1 != -diff){
                cout << "-1\n";
                return 0;
            }
        }
    }
    if (c1 == -1 || c == -1){
        cout << "0\n";
        return 0;
    }
    m = c + c1;
    if ((*max_element(arr, arr + n)) >= m) {
        cout << "-1\n";
        return 0;
    }
    for (int i = 1; i < n; i++) {
        if ((arr[i - 1] + c) % m != arr[i]) {
            cout << "-1\n";
            return 0;
        }
    }
    cout << m << ' ' << c % m << '\n';
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tests = 1;
    cin >> tests;
    for (int test = 1; test <= tests; test++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "-----------\n";
#endif
    }
    return 0;
}

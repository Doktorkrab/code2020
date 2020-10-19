#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 2e5;

int n, t;
int x[N];

void gen_test() {
#define int long long
    n = 10;
    const int MAXN = 2e9;
    t = rand() % MAXN;
    for (int i = 0; i < n; ++i) {
        x[i] = rand() % MAXN - MAXN / 2;
    }
    sort(x, x + n);
#undef int

}
#define int long long
int solve() {
    int ans = 0, s = 0;
    while (s < n && x[s] < 0) {
        ++s;
    }
    for (int i = 0; i < n; ++i) {
        if (x[i] < 0 && x[i] >= -t) {
            int left = s - 1, right = n;
            while (right - left > 1) {
                int mid = left + right >> 1;
                (x[mid] - x[i] + min(x[mid], -x[i]) <= t ? left : right) = mid;
            }
            ans = max(ans, left - i + 1);
        } else if (x[i] >= 0 && x[i] <= t) {
            ans = max(ans, i - s + 1);
        }
    }
    return ans;
}

int stupid_solve() {
#define int long long
//    using ll = long long;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    int ans = 0;
    do {
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; i++)
            arr[i] = x[perm[i - 1]];
        int now = 0;
        int cur = 0;
        for (int i = 1; i <= n; i++){
            if (abs(arr[i] - arr[i - 1]) + now > t)
                break;
            cur++;
            now += abs(arr[i] - arr[i - 1]);
        }
        ans = max(ans, cur);
    } while (next_permutation(perm.begin(), perm.end()));
#undef int
    return ans;
}
void print_test() {
    cout << n << ' ' << t << '\n';
    for (int i = 0; i < n; ++i) {
        cout << x[i] << ' ';
    }
    cout << '\n';
}

void stresstest() {
    int test_n = 1;
    while (true) {
        cout << "TEST #" << test_n++ << endl;
        gen_test();
//        cerr << "here\n";
        if (solve() != stupid_solve()) {
            cout << "FAIL\n";
            print_test();
            cout << "MY ANS: " << solve() << '\n';
            cout << "R8 ANS: " << stupid_solve() << '\n';
//            system("pause");
            exit(0);
        }
    }
}

signed main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout.tie(NULL);
     stresstest();
//    cin >> n >> t;
//    for (int i = 0; i < n; ++i) {
//        cin >> x[i];
//    }
//    cout << stupid_solve() << '\n';
    // cout << solve() << '\n';
    // system("pause");
    return 0;
}
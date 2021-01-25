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
const int MAXN = 2e5 + 7;
int arr[MAXN];
int left_border[MAXN];
int right_border[MAXN];
int a[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<int> stack;
    for (int i = 0; i < n; i++) {
        while (SZ(stack) && arr[stack.back()] >= arr[i])
            stack.pop_back();
        if (!SZ(stack))
            left_border[i] = 0;
        else
            left_border[i] = stack.back() + 1;
        stack.push_back(i);
    }
    stack.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (SZ(stack) && arr[stack.back()] >= arr[i])
            stack.pop_back();
        if (!SZ(stack))
            right_border[i] = n;
        else
            right_border[i] = stack.back();
        stack.push_back(i);
    }
    vector<pair<int, int>> have;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0)
            continue;
        have.emplace_back(arr[i], right_border[i] - left_border[i]);
        if (have.back().first > have.back().second)
            swap(have.back().first, have.back().second);
//        cout << i << ' ' << arr[i] << ' ' << right_border[i] << ' ' << left_border[i] << '\n';
    }
    int ans1 = have.back().first;
    int ans2 = have.back().second;
    for (auto &i : have) {
        ans1 = min(ans1, i.first);
        ans2 = min(ans2, i.second);
    }
    cerr << ans1 << ' ' << ans2 << '\n';
    cout << 1LL * ans1 * ans2 << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
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

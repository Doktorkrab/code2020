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
const int MAXN = 1e6 + 7;
vector<int> arr;
vector<pair<int, int>> merge(const vector<pair<int, int>>& a, const vector<pair<int, int>>&b){
    vector<pair<int, int>> c(SZ(a) + SZ(b));
    merge(ALL(a), ALL(b), c.begin());
    return c;
}
vector<pair<int, int>> solve_n2(int l, int r) {
    if (l == r)
        return {};
    if (r - l == 2)
        return {{arr[l], arr[l + 1]}};
    vector<pair<int, int>> ans;
    int best = TMAX(int);
    int pos = -1;
    for (int i = l; i + 1 < r; i += 2) {
        if (best > arr[i]) {
            best = arr[i];
            pos = i;
        }
    }
    int pos1 = -1;
    int best1 = n + 1;
    for (int i = pos + 1; i < r; i += 2) {
        if (best1 > arr[i]) {
            best1 = arr[i];
            pos1 = i;
        }
    }
    vector<pair<int, int>> now = {{best, best1}};
    vector<pair<int, int>> lft = solve_n2(l, pos);
    vector<pair<int, int>> mid = solve_n2(pos + 1, pos1);
    vector<pair<int, int>> rgt = solve_n2(pos1 + 1, r);
    auto tmp =  merge(merge(lft, mid), rgt);
    now.insert(now.end(), ALL(tmp));
    return now;
}

void solvek12(){
    int best = TMAX(int);
    int pos = -1;
    for (int i = 0; i < n; i += 2) {
        if (best > arr[i]) {
            best = arr[i];
            pos = i;
        }
    }

    cout << best;
    if (k == 2) {
        best = n;
        for (int i = pos + 1; i < n; i += 2) {
            best = min(best, arr[i]);
        }
        cout << ' ' << best << '\n';
    } else
        cout << "\n";
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    arr.resize(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    if (k == 1 || k == 2){
        solvek12();
        return 0;
    }
    auto ans = solve_n2(0, n);
    vector<int> ans1;
    for (auto [a, b] : ans){
        ans1.push_back(a);
        ans1.push_back(b);
    }
    for (int i = 0; i < k; i++)
        cout << ans1[i] << " \n"[i + 1 == k];
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
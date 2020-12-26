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

const int N = 2e5 + 7;

int n, m, k;

pair<int, int> arr[N];
vector<pair<int, pair<int, int>>> ev;
int ans[N];
pair<int, int> busy[N];

int solve() {
    if (!(cin >> n))
        return 1;
    cin >> m >> k;
    for (int i = 0; i < k; ++i) {
        cin >> arr[i].first >> arr[i].second;
        ev.push_back({arr[i].first, {+1, i}});
        ev.push_back({arr[i].second, {-1, i}});
    }
    set<int> s1, s2;
    for (int i = 0; i < m - 1; ++i) {
        s1.insert(i);
        s2.insert(i);
    }
    s2.insert(m - 1);
    sort(ev.begin(), ev.end());
    for (int i = 0; i < m; ++i) {
        busy[i] = {-1, -1};
    }
    for (auto e : ev) {
        int i = e.second.second;
        if (e.second.first == +1) {
            if (!s1.empty()) {
                busy[i] = {0, *s1.begin()};
                s1.erase(s1.begin());
            } else if (!s2.empty()) {
                busy[i] = {1, *s2.begin()};
                ans[*s2.begin()] += arr[i].second - arr[i].first;
                s2.erase(s2.begin());
            } else {
                busy[i] = {-1, -1};
            }
        } else {
            if (busy[i].first == 0) {
                s1.insert(busy[i].second);
            } else if (busy[i].first == 1) {
                s2.insert(busy[i].second);
            }
            busy[i] = {-1, -1};
        }
    }
    auto it = min_element(ans, ans + m);
    cout << *it << ' ' << it - ans + 1 << endl;
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

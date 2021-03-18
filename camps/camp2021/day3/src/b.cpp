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
pair<int, int> points[MAXN];
int events[MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second, events[i] = 0;
    sort(points, points + n);
    vector<pair<int, int>> points1;
    for (int i = 0; i < n; i++) {
        while (SZ(points1) && points1.back().second <= points[i].second)
            points1.pop_back();
        points1.push_back(points[i]);
    }
    vector<int> have;
    have.reserve(points1.size());
    for (auto[_, b] : points1)
        have.push_back(b);
    reverse(ALL(have));
    int pnt = 0;
    for (int i = 0; i < n; i++) {
        while (pnt < SZ(points1) && points[i].first > points1[pnt].first)
            pnt++;
        int l = (int)(lower_bound(ALL(have), points[i].second) - have.begin());
        int r = SZ(points1) - pnt - 1;
        if (l < r){
            events[l]++;
            events[r]--;
        }
    }
    int cnt = 0;
    int bal = 0;
    for (int i = 0; i < SZ(points1); i++){
        bal += events[i];
        if (bal != 0)
            cnt++;
    }
    cout << SZ(points1) - cnt << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

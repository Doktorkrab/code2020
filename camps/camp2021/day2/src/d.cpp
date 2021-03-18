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
const int MAXN = 1e6 + 7;
pair<int, int> points[MAXN];
unordered_map<int, int> maxy;
unordered_map<int, int> miny;
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        cin >> points[i].first >> points[i].second;
    }
    maxy.clear();
    miny.clear();
    for (int i = 0; i < n; i++){
        auto [x, y] = points[i];
        if (!maxy.count(x))
            maxy[x] = y;
        if (!miny.count(x))
            miny[x] = y;
        if (maxy[x] < y)
            maxy[x] = y;
        if (miny[x] > y)
            miny[x] = y;
    }
    sort(points, points + n);
    vector<pair<int, int>> ans, tmp;
    int cury = miny[points[0].first];
    ans.emplace_back(points[0].first, cury);
    for (int i = 1; i < n; i++){
        if (miny[points[i].first] < cury){
            ans.emplace_back(points[i].first, cury);
            cury = miny[points[i].first];
            ans.emplace_back(points[i].first, cury);
        }
    }
//    cout << SZ(ans) << '\n';
//    for (auto [a, b] : ans)
//        cout << a << " " << b << '\n';
    cury = miny[points[n - 1].first];
    tmp.emplace_back(points[n - 1].first, cury);
    for (int i = n - 2; i >= 0; i--) {
        if (miny[points[i].first] < cury) {
            tmp.emplace_back(points[i].first, cury);
            cury = miny[points[i].first];
            tmp.emplace_back(points[i].first, cury);
        }
    }
    if (ans.back() == tmp.back())
        tmp.pop_back();
    ans.insert(ans.end(), RALL(tmp));
    tmp.clear();

    cury = maxy[points[n - 1].first];
    if (cury > ans.back().second) tmp.emplace_back(points[n - 1].first, cury);
    for (int i = n - 2; i >= 0; i--){
        if (maxy[points[i].first] > cury){
            tmp.emplace_back(points[i].first, cury);
            cury = maxy[points[i].first];
            tmp.emplace_back(points[i].first, cury);
        }
    }
    ans.insert(ans.end(), ALL(tmp));
    tmp.clear();

    cury = maxy[points[0].first];
    if (cury > ans[0].second) tmp.emplace_back(points[0].first, cury);
    for (int i = 1; i < n; i++){
        if (maxy[points[i].first] > cury){
            tmp.emplace_back(points[i].first, cury);
            cury = maxy[points[i].first];
            tmp.emplace_back(points[i].first, cury);
        }
    }
    ans.insert(ans.end(), RALL(tmp));
    cout << SZ(ans) << '\n';
    for (auto [a, b] : ans)
        cout << a << " " << b << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

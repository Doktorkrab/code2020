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
vector<int> have_x[MAXN];
vector<int> have_y[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;
    vector<int> c_x, c_y;
    c_x.reserve(n);
    c_y.reserve(n);
    for (int i = 0; i < n; i++) {
        c_x.push_back(points[i].first);
        c_y.push_back(points[i].second);
    }
    sort(ALL(c_x));
    c_x.resize(unique(ALL(c_x)) - c_x.begin());
    sort(ALL(c_y));
    c_y.resize(unique(ALL(c_y)) - c_y.begin());
    vector<int> cnt_x(SZ(c_y));
    vector<int> cnt_y(SZ(c_x));
    if (SZ(c_x) == 1 || SZ(c_y) == 1) {
        cout << "4\n";
        return 0;
    }
    if (SZ(c_x) == n && SZ(c_y) == n) {
        cout << "4\n";
        return 0;
    }
    for (int i = 0; i < SZ(c_x); i++)
        have_x[i].clear();
    for (int i = 0; i < SZ(c_y); i++)
        have_y[i].clear();
    for (int i = 0; i < n; i++){
        auto &[a, b] = points[i];
        a = (int)(lower_bound(ALL(c_x), a) - c_x.begin());
        b = (int)(lower_bound(ALL(c_y), b) - c_y.begin());
        have_x[a].push_back(b);
        have_y[b].push_back(a);
    }
    map<pair<int, int>, int> pairs_x;
    map<pair<int, int>, int> pairs_y;
    int ccx = 0, ccy = 0;

    for (int i = 0; i < SZ(c_x); i++){
        sort(ALL(have_x[i]));
        for (int j = 0; j < SZ(have_x[i]); j++){
            for (int k = j + 1; k < SZ(have_x[i]); k++) {
                pair<int, int> now = {have_x[i][j], have_x[i][k]};
                pairs_x[now]++;
                if (pairs_x[now] == 2){
                    cout << "0\n";
                    return 0;
                }
            }
            if (SZ(have_x[i]) > 1)
                cnt_x[have_x[i][j]]++;
        }
        if (SZ(have_x[i]) > 1)
            ccx++;
    }
    for (int i = 0; i < SZ(c_y); i++){
        sort(ALL(have_y[i]));
        for (int j = 0; j < SZ(have_y[i]); j++){
            for (int k = j + 1; k < SZ(have_y[i]); k++) {
                pair<int, int> now = {have_y[i][j], have_y[i][k]};
                pairs_y[now]++;
                if (pairs_y[now] == 2){
                    cout << "0\n";
                    return 0;
                }
            }
            if (SZ(have_y[i]) > 1)
                cnt_y[have_y[i][j]]++;
        }
        if (SZ(have_y[i]) > 1)
            ccy++;
    }
    bool can = false;
    for (int i = 0; i < SZ(c_x); i++){
        sort(ALL(have_x[i]));
        for (int j = 0; j < SZ(have_x[i]); j++) {
            for (int k = j + 1; k < SZ(have_x[i]); k++) {
                if (cnt_x[have_x[i][j]] > 1 && cnt_x[have_x[i][k]] > 1){
                    cout << "1\n";
                    return 0;
                }
                can |= (SZ(have_y[have_x[i][j]]) > 1 || SZ(have_y[have_x[i][k]]) > 1);
                if (SZ(have_y[have_x[i][j]]) > 1 && SZ(have_y[have_x[i][k]]) > 1){
                    cout << "1\n";
                    return 0;
                }
            }
        }
    }
    for (int i = 0; i < SZ(c_y); i++){
        sort(ALL(have_y[i]));
        for (int j = 0; j < SZ(have_y[i]); j++) {
            for (int k = j + 1; k < SZ(have_y[i]); k++) {
                if (cnt_y[have_y[i][j]] > 1 && cnt_y[have_y[i][k]] > 1){
                    cout << "1\n";
                    return 0;
                }
                can |= (SZ(have_x[have_y[i][j]]) > 1 || SZ(have_x[have_y[i][k]]) > 1);
                if (SZ(have_x[have_y[i][j]]) > 1 && SZ(have_x[have_y[i][k]]) > 1){
                    cout << "1\n";
                    return 0;
                }
            }
        }
    }
//    cout << ccx << ' ' << ccy << ' ' << can << '\n';
    if (ccx > 1 || ccy > 1 || can){
        cout << "2\n";
        return 0;
    }
    cout << "3\n";
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
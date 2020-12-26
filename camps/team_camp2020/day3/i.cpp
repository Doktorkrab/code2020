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
#define int ll
enum {
    OPEN,
    ASK,
    CLOSE
};
struct Event{
    int x, type, y, extra;

    bool operator<(const Event &rhs) const {
        int t = -x;
        int tt = -rhs.x;
        return std::tie(t, type, y, extra) < std::tie(tt, rhs.type, rhs.y, rhs.extra);
    }
};

int n, m;
const int MAXN = 3e5 + 7;
int l[MAXN], r[MAXN];
int val[MAXN];
int ans[MAXN];
Event events[3 * MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    int pnt = 0;
    for (int i = 0; i < n; i++){
        cin >> l[i] >> r[i];
        events[pnt++] = {l[i], CLOSE, i, 0};
        events[pnt++] = {r[i], OPEN, i, 0};
    }
    cin >> m;
    for (int i = 0; i < m; i++){
        int t,x;
        cin >> x >> t;
        --x;
        events[pnt++] = {t, ASK, x, i};
    }
    sort(events, events + pnt);
    set<int> opened;
    for (int i = 0; i < pnt; i++){
        Event& e = events[i];
        if (e.type == OPEN){
            auto it = opened.upper_bound(e.y);
            if (it != opened.end())
                val[e.y] = val[*it] + (r[*it] - e.x);
            opened.insert(e.y);
        }
        else if (e.type == CLOSE){
            opened.erase(e.y);
        }
        else if (e.type == ASK){
            auto it = opened.lower_bound(e.y);
//            cout << "SET:";
//            for (int x : opened)
//                cout << x << ' ';
//            cout << '\n';
            if (it == opened.end())
                ans[e.extra] = 0;
            else {
                ans[e.extra] = val[*it] + (r[*it] - e.x);
//                cout << (*it) << ' ' << e.extra + 1 << '\n';
            }
        }
    }
//    for (int i = 0; i < n; i++)
//        cout << val[i] << " \n"[i + 1 == n];
    for (int i = 0; i < m; i++)
        cout << ans[i] << '\n';
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

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
vector<ll> to_sort;
vector<int> have[MAXN];
int arr[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    to_sort.resize(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        to_sort[i] = arr[i];
    }
    sort(ALL(to_sort));
    to_sort.resize(unique(ALL(to_sort)) - to_sort.begin());
    for (int i = 0; i < n; i++){
        arr[i] = (int)(lower_bound(ALL(to_sort), arr[i]) - to_sort.begin());
        have[arr[i]].push_back(i);
    }
    set<int> ls, rs;
    ll ans = 0;
    for (int i = 0; i < SZ(to_sort); i++){
        if (i)
            ans += SZ(ls) * (to_sort[i] - to_sort[i - 1]);
        for (int x : have[i]) {
            int l = x, r = x + 1;
            if (SZ(ls)) {
                auto it = ls.upper_bound(x);
                if (it != ls.begin() && (*rs.upper_bound(*prev(it))) == x){
                    --it;
                    l = (*it);
                    ls.erase(it);
                    rs.erase(rs.upper_bound(l));
                }
                if (ls.count(x + 1)){
                    ls.erase(x + 1);
                    it = rs.upper_bound(x + 1);
                    if (it != rs.end()) {
                        r = (*it);
                        rs.erase(it);
                    }

                }
            }
            ls.insert(l);
            rs.insert(r);
        }
    }
    cout << ans << '\n';
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
vector<ll> to_sort;
vector<int> have[MAXN];
int arr[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    to_sort.resize(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        to_sort[i] = arr[i];
    }
    sort(ALL(to_sort));
    to_sort.resize(unique(ALL(to_sort)) - to_sort.begin());
    for (int i = 0; i < n; i++){
        arr[i] = (int)(lower_bound(ALL(to_sort), arr[i]) - to_sort.begin());
        have[arr[i]].push_back(i);
    }
    set<int> ls, rs;
    ll ans = 0;
    for (int i = 0; i < SZ(to_sort); i++){
        if (i)
            ans += SZ(ls) * (to_sort[i] - to_sort[i - 1]);
        for (int x : have[i]) {
            int l = x, r = x + 1;
            if (SZ(ls)) {
                auto it = ls.upper_bound(x);
                if (it != ls.begin() && (*rs.upper_bound(*prev(it))) == x){
                    --it;
                    l = (*it);
                    ls.erase(it);
                    rs.erase(rs.upper_bound(l));
                }
                if (ls.count(x + 1)){
                    ls.erase(x + 1);
                    it = rs.upper_bound(x + 1);
                    if (it != rs.end()) {
                        r = (*it);
                        rs.erase(it);
                    }

                }
            }
            ls.insert(l);
            rs.insert(r);
        }
    }
    cout << ans << '\n';
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
vector<ll> to_sort;
vector<int> have[MAXN];
int arr[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    to_sort.resize(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        to_sort[i] = arr[i];
    }
    sort(ALL(to_sort));
    to_sort.resize(unique(ALL(to_sort)) - to_sort.begin());
    for (int i = 0; i < n; i++){
        arr[i] = (int)(lower_bound(ALL(to_sort), arr[i]) - to_sort.begin());
        have[arr[i]].push_back(i);
    }
    set<int> ls, rs;
    ll ans = 0;
    for (int i = 0; i < SZ(to_sort); i++){
        if (i)
            ans += SZ(ls) * (to_sort[i] - to_sort[i - 1]);
        for (int x : have[i]) {
            int l = x, r = x + 1;
            if (SZ(ls)) {
                auto it = ls.upper_bound(x);
                if (it != ls.begin() && (*rs.upper_bound(*prev(it))) == x){
                    --it;
                    l = (*it);
                    ls.erase(it);
                    rs.erase(rs.upper_bound(l));
                }
                if (ls.count(x + 1)){
                    ls.erase(x + 1);
                    it = rs.upper_bound(x + 1);
                    if (it != rs.end()) {
                        r = (*it);
                        rs.erase(it);
                    }

                }
            }
            ls.insert(l);
            rs.insert(r);
        }
    }
    cout << ans << '\n';
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

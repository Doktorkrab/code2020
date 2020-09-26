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
 
int n, q;
set<int> have;
multiset<int> gaps;
void add(int x){
    auto it = have.insert(x).first;
    //cout << x << ' ' << SZ(have) << '\n';
    if (it != have.begin())
        gaps.insert((*it) - (*prev(it)));
    if (next(it) != have.end())
        gaps.insert((*next(it)) - (*it));
    if (it != have.begin() && next(it) != have.end())
        gaps.erase(gaps.find((*next(it)) - (*prev(it))));
}

void del(int x){
    auto it = have.find(x);
    if (it != have.begin())
        gaps.erase(gaps.find(-(*prev(it)) + (*it)));
    if (next(it) != have.end())
        gaps.erase(gaps.find((*next(it)) - (*it)));
    if (it != have.begin() && next(it) != have.end())
        gaps.insert(((*next(it)) - (*prev(it))));
    have.erase(x);
}
int query(){
    if (SZ(have) <= 2)
        return 0;
    return (*prev(have.end())) - (*have.begin()) - (*prev(gaps.end()));
}
int solve() {
    if (!(cin >> n >> q))
        return 1;
    gaps.clear();
    have.clear();
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        add(x);
    }
    cout << query() << '\n';
    for (int i = 0; i < q; i++){
        int t, x;
        cin >> t >> x;
        if (!t)
            del(x);
        else
            add(x);
        //cout << SZ(have) << '\n';
        cout << query() << '\n';
    }
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    //cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

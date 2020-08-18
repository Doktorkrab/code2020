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
const int MAXN = 2e5 + 7;
int arr[MAXN];
int hist[MAXN];


void change(int who, int x, set<pair<int, int>>& have){
    // cerr << "enter\n";
    // cerr << who << ' ' << x << '\n';
    if (have.count({hist[who], who}))
        have.erase({hist[who], who});
    assert(who < MAXN && who >= 0);
    hist[who] += x;
    if (hist[who] > 0)
        have.insert({hist[who], who});
    // cerr << "end\n";
}
int solve() {
    set<pair<int, int>> have;
    if (!(cin >> n >> k))
        return 1;
    vector<int> to_compess;
    to_compess.resize(n);
    have.clear();
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        to_compess[i] = arr[i];
        hist[i] = 0;
    }

    sort(ALL(to_compess));
    to_compess.erase(unique(ALL(to_compess)), to_compess.end());
    for (int i = 0; i < n; i++)
        arr[i] = (int)(lower_bound(ALL(to_compess), arr[i]) - to_compess.begin());
    // cerr << "here\n";
    int l = 0;
    int ans = 0;
    for (int r = 0; r < n; r++){
        change(arr[r], 1, have);
        while (SZ(have) > k + 1 && l < r){
            assert(l < MAXN);
            change(arr[l++], -1, have);
        }
        // cout << l + 1 << ' ' << r + 1 << ' ' << have.size() << '\n';
        assert(SZ(have));
        ans = max(ans, have.rbegin()->first);
        // cerr << r << '\n';
    }
    // cerr << ans << '\n';
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifndef LOCAL
    assert(freopen("lineup.in", "r", stdin));
    assert(freopen("lineup.out", "w", stdout));
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
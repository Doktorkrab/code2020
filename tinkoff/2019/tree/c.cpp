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
struct SegmentTree{
    unordered_map<int, int> id;
    vector<pair<int, int>> t;
    int N;
    SegmentTree(vector<int>& to_compress){
        sort(ALL(to_compress));
        to_compress.erase(unique(ALL(to_compress)), to_compress.end());
        for (int i = 0; i < n; i++)
            id[to_compress[i]] = i;
        N = 1;
        while (N < SZ(to_compress)) N *= 2;
        t.resize(2 * N + 2);
    }
    void place(int v, int pos, pair<int, int>& )
};
 
int solve() {
    if (!(cin >> n))
        return 1;
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
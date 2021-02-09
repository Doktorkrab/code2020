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
struct Segment{
    ll g = 0, len = 0;
};
const int MAXN = 5e5 + 7;
int arr[MAXN];
int queries[MAXN];
unordered_map<int, ll> anses;
unordered_set<int> queries1;

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    anses.clear();
    queries1.clear();
    cin >> q;
    for (int i = 0; i < q; i++){
        cin >> queries[i];
        queries1.insert(queries[i]);
    }
    vector<Segment> blocks;
    for (int i = 0; i < n; i++){
        reverse(ALL(blocks));
        vector<Segment> new_blocks;
        new_blocks.push_back({arr[i], 1});
        for (Segment s: blocks){
            int new_g = gcd(s.g, arr[i]);
            if (new_g == new_blocks.back().g)
                new_blocks.back().len += s.len;
            else
                new_blocks.push_back({new_g, s.len});
        }
        swap(blocks, new_blocks);
        for (Segment s: blocks){
            if (queries1.count(s.g))
                anses[s.g] += s.len;
        }
        reverse(ALL(blocks));
    }
    for (int i = 0; i < q; i++){
        cout << anses[queries[i]] << '\n';
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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

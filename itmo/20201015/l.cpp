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

const int MAXN = 2e5 + 7;
int n;
struct SegmentTree{
    int N = 1;
    int tree[MAXN]{};
    explicit SegmentTree(int n){
        n += 5;
        while (n < N)
            N *= 2;
    }
    void insert(int v, int tl, int tr, int pos, int x){
        if (tr <= pos || pos < tl)
            return;
        if (tr - tl == 1){
            tree[v] += x;
            return;
        }
        int tm = (tl + tr) / 2;
        insert(v * 2, tl, tm, pos, x);
        insert(v * 2 + 1, tm, tr, pos, x);
        tree[v] = tree[2 * v] + tree[v * 2 + 1];
    }

    int get(int v, int tl, int tr, int l, int r){
        if (tr <= l || r <= tl)
            return 0;
        if (l <= tl && tr <= r){
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
    }
    int get(int l, int r){
        return get(1, 0, N, l, r);
    }
    void insert(int pos, int x){
        insert(1, 0, N, pos, x);
    }
};
int arr[MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
    reverse(arr, arr + n);
    ll ans = 0;
    ll now = 0;
    for (int i = 0; i < n; i++){
        now += arr[i] - (i + 1);
        if (now > 0)
            ans = max(now, ans);
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

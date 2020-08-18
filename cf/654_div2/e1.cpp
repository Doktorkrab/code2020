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
 
int n, p;
const int MAXN = 1e5 + 7;
int arr[MAXN];
int cnt[MAXN];
vector<int> to_compress;

int prefix[MAXN];
bool check(int x){
    int found = (lower_bound(ALL(to_compress), x) - to_compress.begin());
    if (found == SZ(to_compress))
        return false;
    ll now = 1;
    ll t = prefix[found];
    cerr << x << '\n';
    for (int i = 0; i < n; i++){
        if (found < SZ(to_compress) && i + x >= to_compress[found]){
            t += cnt[found++];
            t %= p;
        }
        now = (now * t) % p;
        t = (t - 1 + p) % p;
        if (!now)
            break;
    }
    cerr << x << '\n';
    return now != 0;
}
int solve() {
    if (!(cin >> n >> p))
        return 1;
    to_compress.resize(n);
    for (int i = 0; i < MAXN; i++)
        cnt[i] = 0;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        to_compress[i] = arr[i];
    }
    sort(ALL(to_compress));
    to_compress.resize(unique(ALL(to_compress)) - to_compress.begin());

    for (int i = 0; i < n; i++)
        arr[i] = (int)(lower_bound(ALL(to_compress), arr[i]) - to_compress.begin());

    for (int i = 0; i < n; i++)
        cnt[arr[i]]++;
    for (int i = 0; i < SZ(to_compress); i++)
        prefix[i + 1] = prefix[i] + cnt[i];
    cerr << "here\n";
    int l = 1, r = 1e9 + 7;
    while (r - l > 1){
        int m = (l + r) / 2;
        if (check(m))
            l = m;
        else
            r = m;
    }
    cout << l << '\n';
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
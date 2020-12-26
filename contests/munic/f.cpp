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
 
int n, m, k;
const int MAXN = 5e3 + 7;
int a[MAXN];
int lst[MAXN];
int rlst[MAXN];
int cnt[MAXN];
int sum[MAXN];
int b[MAXN];
int lst1[MAXN];
int rlst1[MAXN];
int cnt1[MAXN];
int sum1[MAXN];
int solve() {
    if (!(cin >> k >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    fill(lst, lst + n, -1);
    for (int i = 0; i < n; i++){
        int zeroes = k;
        for (int j = i; j > lst[a[i]]; j--) {
            if (sum[a[j]] == 0)
                zeroes--;
            sum[a[j]] = 1;
        }
        for (int j = i - 1; j > lst[a[i]]; j--)
            sum[a[j]] = 0;
        if (zeroes == 0) {
            cnt[a[i]]++;
            lst[a[i]] = i;
        }
    }
    for (int i = 1; i <= k; i++)
        cout << cnt[i] << " \n"[i == k];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> b[i];
    fill(lst1, lst1 + m, -1);
    for (int i = 0; i < m; i++){
        int zeroes = k;
        for (int j = i; j > lst1[b[i]]; j--) {
            if (sum1[b[j]] == 0)
                zeroes--;
            sum1[b[j]] = 1;
        }
        for (int j = i - 1; j > lst1[b[i]]; j--)
            sum1[b[j]] = 0;
        if (zeroes == 0) {
            cnt1[b[i]]++;
            lst1[b[i]] = i;
        }
    }
    for (int i = 1; i <= k; i++)
        cout << cnt1[i] << " \n"[i == k];
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

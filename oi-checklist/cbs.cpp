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

const int MAXN = 5e4 + 5;
const int MAXK = 15;
const int MAXLOG = 20;

int logs[MAXN];
int k, n;
int arr[MAXK][MAXN];
int prefix[MAXK][MAXN];
int cnt[MAXN];
map<vector<int>, int> last;
struct Sparse{
    int sparse[MAXLOG][MAXN];
    Sparse() {}
    Sparse(int* arr, int n){
        for (int i = 0; i < n; i++)
            sparse[0][i] = arr[i];

        for (int log = 1; log < MAXLOG; log++)
            for (int i = 0; i + (1 << log) <= n; i++)
                sparse[log][i] = min(sparse[log - 1][i], sparse[log - 1][i + (1 << (log - 1))]);
    }
    int get(int l, int r) { // [l, r]
        int len = r - l + 1;
        int log = logs[len];
        return min(sparse[log][l], sparse[log][r - (1 << log) + 1]);
    }
};
Sparse sparses[MAXK]; 


int solve() {
    if (!(cin >> k >> n))
        return 1;
    logs[1] = 0;
    for (int i = 2; i < MAXN; i++)
        logs[i] = logs[i / 2] + 1;
    for (int i = 0; i < k; i++){
        for (int j = 0; j < n; j++){
            char x;
            cin >> x;
            if (x == '(')
                arr[i][j] = 1;
            else
                arr[i][j] = -1;
            prefix[i][j + 1] = prefix[i][j] + arr[i][j];
        }
        sparses[i] = Sparse(prefix[i], n + 1);
    }

    int ans = 0;
    last[vector<int>(k, 0)] = 0;
    // for (int i = 0; i < k; i++)
    //     for (int j = 0; j <= n; j++)
    //         cout << prefix[i][j] << " \n"[j == n];
    for (int j = 1; j <= n; j++){
        bool good = 1;
        vector<int> now(k);
        for (int i = 0; i < k; i++)
            now[i] = prefix[i][j];
        if (!last.count(now)){
            last[now] = j;
            continue;
        }
        int prev = last[now];
        for (int i = 0; i < k; i++){
            // cout << i << ' ' << j << ' ' << prefix[i][j] << ' ' << sparses[i].get(prev + 1, j) << '\n';
            if (sparses[i].get(prev + 1, j) - prefix[i][j] < 0){
                good = 0;
                break;
            }
        }
        last[now] = j;
        if (!good)
            continue;
        // cout << j << ' ' << prev << ' ' << (cnt[prev] + 1) << '\n';
        ans += (cnt[j] = (cnt[prev] + 1));
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("cbs.in", "r", stdin);
    freopen("cbs.out", "w", stdout);
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
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
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
const int BLOCK_SIZE = 6000;
int arr[MAXN];
int arr1[MAXN];

inline int get(int l, int r, int m) {
    int block_l = l / BLOCK_SIZE;
    int end = block_l * BLOCK_SIZE + BLOCK_SIZE;
    if (end > n)
        end = n;
    if (end > r + 1)
        end = r + 1;
    int ans = 0;
    for (int i = l; i < end; i++)
        if (arr1[i] >= m)
            ans++;
    int block_r = r / BLOCK_SIZE;
    for (int i = block_l + 1; i < block_r; i++) {
        int ll = i * BLOCK_SIZE;
        int rr = ll + BLOCK_SIZE;
        ans += (int) (BLOCK_SIZE -
                      (lower_bound(arr + ll, arr + rr, m) - arr -
                       i * BLOCK_SIZE));
    }
    if (block_l != block_r) {
        int start = block_r * BLOCK_SIZE;
        for (int i = start; i <= r; i++) {
            if (arr1[i] >= m)
                ans++;
        }
    }
    int less = (r - l + 1) - ans;
    return max(0, ans - less);
}

inline void insert(int pos, int x) {
    int l = (pos / BLOCK_SIZE) * BLOCK_SIZE;
    int r = min(n, l + BLOCK_SIZE);
    int pb = lower_bound(arr + l, arr + r, arr1[pos]) - arr;
    if (arr1[pos] < x) {
        for (; pb < r - 1 && arr[pb + 1] < x; pb++) {
            arr[pb] = arr[pb + 1];
        }
        arr[pb] = x;
    } else {
        for (; pb > l && arr[pb - 1] > x; pb--) {
            arr[pb] = arr[pb - 1];
        }
        arr[pb] = x;
    }
    arr1[pos] = x;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr1[i] = arr[i];
//        arr[i] = i;
    }
    for (int block = 0; block * BLOCK_SIZE < n; block++) {
        int r = min((block + 1) * BLOCK_SIZE, n);
        sort(arr + block * BLOCK_SIZE, arr + r);
    }
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos, x;
            cin >> pos >> x;
            insert(pos - 1, x);
        }
        if (type == 2) {
            int m, l, r;
            cin >> m >> l >> r;
            --l, --r;
            cout << get(l, r, m) << '\n';
        }
    }
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
// #ifdef LOCAL
//        cout << "------------------------------\n";
// #endif
    }
}

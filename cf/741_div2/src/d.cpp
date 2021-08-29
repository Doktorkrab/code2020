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
string s;
const int MAXN = 3e5 + 7;
ll prefix1[MAXN];
ll prefix2[MAXN];
ll get(int l, int r, ll* prefix){
    return prefix[r] - prefix[l];
}

ll get(int l, int r, int x){
    ll lft = get(l, x, prefix2) - get(l, x, prefix1);
    ll rgt = get(x + 1, r, prefix1) - get(x + 1, r, prefix2);
    return rgt + lft;
}
int solve() {
    if (!(cin >> n >> q >> s))
        return 1;
    for (int i = 0; i < n; i++){
        prefix1[i + 1] = prefix1[i];
        prefix2[i + 1] = prefix2[i];
        int now;
        if (s[i] == '+')
            now = 1;
        else
            now = -1;
        if (i % 2)
            prefix1[i + 1] += now;
        else
            prefix2[i + 1] += now;
    }
    for (int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        --l, r;
        if (get(l, r, prefix1) == get(l, r, prefix2)){
            cout << "0\n";
            continue;
        }
        vector<int> ans;
        if ((r - l) % 2 == 0) {
            ans.push_back(r);
            --r;
        }
        if (get(l, r, l) == 0){
            ans.push_back(l + 1);
        }
        else {
            assert((r - l) % 2);
//            for (int j = l; j < r; j++)
//                cout << get(l, r, j) << " \n"[j + 1 == r];
            int lo = l, hi = r;
            while (hi - lo > 1) {
                int m = (lo + hi) / 2;
                ll sl = get(l, r, l);
                ll sm = get(l, r, m);
                if (sl * sm >= 0)
                    lo = m;
                else
                    hi = m;
            }
            ans.push_back(lo + 1);
        }
        cout << SZ(ans) << '\n';
        for (int x : ans)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

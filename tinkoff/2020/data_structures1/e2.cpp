#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <limits.h>

using namespace std;

#define int long long

int maxn, logn;

struct e {
    int a = -1, b = -1, c = -1;
};
int n, d;
vector<vector<int>> t;
vector<e> lst;

void rel(vector<int> &cur, int x) {
    vector<int> per(d, -1);
    int a = lst[x].a, b = lst[x].b, c = lst[x].c;
    if (a == -1) return;
    for (int i = 0; i < d; i++) {
        if (cur[i] == -1 && i != 0) continue;
        per[(i + a) % d] = max(per[(i + a) % d], max((int) 0, cur[i]) + a);
        per[(i + b) % d] = max(per[(i + b) % d], max((int) 0, cur[i]) + b);
        per[(i + c) % d] = max(per[(i + c) % d], max((int) 0, cur[i]) + c);
    }
    for (int i = 0; i < d; i++) {
        cur[i] = per[i];
    }
}

int sl(vector<int> &cur, vector<int> &add) {
    int ans = -1;
    int bl = 0;
    for (int i = 0; i < d; i++) {
        if (add[i] != -1) bl = 1;
    }
    if (!bl) return cur[0];
    bl = 0;
    for (int i = 0; i < d; i++) {
        if (cur[i] != -1) bl = 1;
    }
    if (!bl) return add[0];

    // if (cur[0] == -1 || add[0] == -1) ans = -1;
    for (int i = 0; i < d; i++) {
        if (cur[i] == -1 || add[(d - i) % d] == -1) continue;
        ans = max(ans, cur[i] + add[(d - i) % d]);
    }
    return ans;
}

int sz = 0;
vector<int> res;
struct q {
    int ind, l, r, lvl;
};
vector<q> ans;

void build() {
    // int cnt = logn;

    // for (e tt :lst) cerr << tt.a << " " << tt.b << " " << tt.c << '\n';
    for (int lvl = 0; lvl < logn; ++lvl) {
        cerr << '\n';
        for (int block = 0; block < ((int)1 << lvl); ++block) {
            int l = block << (logn - lvl);
            int r = min(maxn, (block + 1) << (logn - lvl));
            int m = (l + r) / 2;
            // cerr << l << " " << m << " " << r << '\n';
            vector<int> cur(d, -1);
            if (m < r) {
                rel(cur, m);
                t[m] = cur;
                for (int i = m + 1; i < r; i++) {
                    rel(cur, i);
                    t[i] = cur;
                }
            }
            cur.assign(d, -1);
            if (m - 1 < l) continue;
            rel(cur, m - 1);
            t[m - 1] = cur;
            for (int i = m - 2; i >= l; i--) {
                rel(cur, i);
                t[i] = cur;
            }
        }
        while (sz < ans.size() && ans[sz].lvl == lvl) {
            vector<int> aa = t[ans[sz].l];
            if (ans[sz].l == ans[sz].r) {
                res[ans[sz].ind] = aa[0];
            } else {
                res[ans[sz].ind] = sl(aa, t[ans[sz].r]);
            }
            sz++;
        }
    }
}

void get(int l, int r) {
    r--;
    if (l == r) {
        ans.push_back({(int) ans.size(), l, r, logn - 1});
        return;
    }
    int diff = __builtin_clzll((unsigned int)(l ^ r)) ^ 63;
    int lvl = logn - 1 - diff;
    // vector<int> res = t[lvl][l];
    // cerr << lvl << '\n';
    // for (int i:t[lvl][r]) cerr << i << ' ';
    // cerr << '\n';
    // cerr << l << ' '<< r <<" "<< lvl <<'\n';
    ans.push_back({(int) ans.size(), l, r, lvl});
    // return sl(res, t[lvl][r]);
}


signed main() {
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        e x;
        cin >> x.a >> x.b >> x.c;
        lst.push_back(x);
    }
    maxn = 1, logn = 0;
    for (; maxn <= lst.size(); maxn *= 2, ++logn) {}
    e nl;
    nl.a = -1;
    lst.resize(maxn, nl);
    t.resize(maxn, vector<int>(d, -1));
    int m;
    cin >> m;
    res.assign(m, 0);
    for (int q = 0; q < m; q++) {
        int l, r;
        cin >> l >> r;
        l--;
        get(l, r);
    }
    sort(ans.begin(), ans.end(), [](const q &a, const q &b) { return a.lvl < b.lvl; });
    build();
    for (int i = 0; i < m; i++) {
        cout << res[i] << "\n";
    }
    return 0;
}

#include <bits/stdc++.h>

using namespace std;
typedef long long lint;
const int MAXN = 100005;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int n, a[MAXN];
vector<int> l, r;

struct bit {
    int tree[MAXN];

    void add(int x, int v) {
        x++;
        while (x <= n) {
            tree[x] += v;
            x += x & -x;
        }
    }

    int sum(int x) {
        x++;
        int ret = 0;
        while (x) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
} bl, br;

struct bit2 {
    lint tree[MAXN];

    void add(int x, lint v) {
        x++;
        while (x <= n) {
            tree[x] += v;
            x += x & -x;
        }
    }

    lint sum(int x) {
        x++;
        lint ret = 0;
        while (x) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
} ql, qr;

int it1, it2;

int trial(int i, int x) {
    int ans = 0;
    it1 = upper_bound(l.begin(), l.end(), x - i) - l.begin();
    ans += bl.sum(it1 - 1);
    it2 = upper_bound(r.begin(), r.end(), x + i) - r.begin();
    ans += br.sum(it2 - 1);
    return ans;
}

lint solve(int i, int x) {
    lint ans = 0;
    ans += (x - i) * bl.sum(it1 - 1) - ql.sum(it1 - 1);
    ans += (ql.sum(n - 1) - ql.sum(it1 - 1)) - (x - i) * (bl.sum(n - 1) - bl.sum(it1 - 1));
    ans += (x + i) * br.sum(it2 - 1) - qr.sum(it2 - 1);
    ans += (qr.sum(n - 1) - qr.sum(it2 - 1)) - (x + i) * (br.sum(n - 1) - br.sum(it2 - 1));
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        l.push_back(a[i] - i);
        r.push_back(a[i] + i);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    l.resize(unique(l.begin(), l.end()) - l.begin());
    r.resize(unique(r.begin(), r.end()) - r.begin());
    for (int i = 1; i <= n; i++) {
        auto pr = lower_bound(r.begin(), r.end(), a[i] + i) - r.begin();
        br.add(pr, 1);
        qr.add(pr, a[i] + i);
    }
    lint ans = 1e18;
    for (int i = 1; i <= n; i++) {
        auto pl = lower_bound(l.begin(), l.end(), a[i] - i) - l.begin();
        auto pr = lower_bound(r.begin(), r.end(), a[i] + i) - r.begin();
        bl.add(pl, 1);
        br.add(pr, -1);
        ql.add(pl, (a[i] - i));
        qr.add(pr, -(a[i] + i));
        int s = max(i, n + 1 - i), e = 1e9 + 1e6;
//        cout << s << '\n';
        while (s != e) {
            int m = (s + e) / 2;
            if (trial(i, m) >= (n + 1) / 2) e = m;
            else s = m + 1;
        }
//        trial(i, s);
//        cout << trial(i, 6) << '\n';
        cout << ' ' << solve(i, s) << ' ' << s << '\n';
        ans = min(ans, solve(i, s));
    }
    cout << ans << endl;
}
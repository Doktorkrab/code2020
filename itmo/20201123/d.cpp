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


const int MAXN = 1e4 + 7;

pair<int, int> arr[MAXN];

struct Queue {
    vector<pair<int, int>> s1;
    vector<pair<int, int>> s2;

    void push_back(int index) {
        int mx = arr[index].second;
        if (SZ(s1))
            mx = min(s1.back().second, mx);
        s1.emplace_back(index, mx);
    }

    void rotate() {
        if (SZ(s2))
            return;
        while (SZ(s1)) {
            auto[t, c] = s1.back();
            s1.pop_back();
            auto i = t;
            int mx = arr[i].second;
            if (SZ(s2))
                mx = min(mx, s2.back().second);
            s2.emplace_back(i, mx);
        }
    }

    int front() {
        rotate();
        return s2.back().first;
    }

    void pop_front() {
        rotate();
        s2.pop_back();
    }

    int get_min() const {
        int ret = 1e9;
        if (SZ(s1))
            ret = s1.back().second;
        if (SZ(s2))
            ret = min(s2.back().second, ret);
        return ret;
    }

    size_t size() const {
        return SZ(s1) + SZ(s2);
    }
};

int solve() {
    if (!(cin >> n))
        return 1;
    vector<int> cmprs(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
        cmprs[i] = arr[i].first;
    }
    sort(ALL(cmprs));
    sort(arr, arr + n);
    cmprs.resize(unique(ALL(cmprs)) - cmprs.begin());
    reverse(ALL(cmprs));
    int ans = 1e9;
    for (int x : cmprs) {
        int pnt = n - 1;
        while (pnt >= 0 && arr[pnt].first > x)
            pnt--;
        int mx = arr[pnt].second;
        pnt--;
        if (pnt < 0)
            break;
        Queue q;
        int l = 0;
        while (l <= pnt && x - arr[pnt].first < arr[l].first) {
            q.push_back(l);
            l++;
        }
        for (; 2 * arr[pnt].first > x; pnt--) {
            while (SZ(q) && (arr[q.front()].first <= x - arr[pnt].first || q.front() >= pnt))
                q.pop_front();
            ans = min(ans, q.get_min() + arr[pnt].second + mx);
            if (arr[pnt].first == x)
                mx = min(mx, arr[pnt].second);
        }
    }
    if (ans < 1e9)
        cout << ans << '\n';
    else
        cout << "-1\n";
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

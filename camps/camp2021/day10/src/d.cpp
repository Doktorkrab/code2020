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

int n, x;
int q_cnt, i_cnt;

vector<int> quick_sort(vector<int> a) {
    vector<int> le, ge;
    if (a.size() <= 1)
        return a;
    int pivot = a[0];
    for (int i = 1; i < SZ(a); i++) {
        q_cnt++;
        if (a[i] < pivot)
            le.push_back(a[i]);
        else
            ge.push_back(a[i]);
    }
    auto ret1 = quick_sort(le);
    auto ret2 = quick_sort(ge);
    ret1.push_back(pivot);
    ret1.insert(ret1.end(), ALL(ret2));
    return le;
}

vector<int> insertion_sort(vector<int> a) {
    int n = SZ(a);
    for (int i = 1; i < n; i++) {
        int j = i;
        i_cnt++;
        while (j > 0 && a[j - 1] > a[j]) {
            swap(a[j - 1], a[j]);
            j--;
            i_cnt++;
        }
    }
    return a;
}

int solve() {
    if (!(cin >> n >> x))
        return 1;
    if (n > 9) {
        int ans = 1;
        for (int i = 1; i <= n; i++)
            ans = (1LL * ans * i) % 1234567;
        cout << ans << '\n';
        return 0;
    }
    vector<int> perm(n);
    iota(ALL(perm), 0);
    int ans = 0;
    do {
        q_cnt = i_cnt = 0;
        insertion_sort(perm);
        quick_sort(perm);
//        for (int i = 0; i < n; i++)
//            cout << perm[i] + 1 << " \n"[i + 1 == n];
//        cout << i_cnt << ' ' << q_cnt << ' ' << i_cnt * 1.L / q_cnt << '\n';
        if (q_cnt * x >= i_cnt)
            ans++;
    } while (next_permutation(ALL(perm)));
    cout << ans << '\n';
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
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

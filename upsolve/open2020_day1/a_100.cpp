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
 
const int MAXN = 5e5 + 7;
int n, t;
int arr[MAXN];
int arr12[MAXN];
int stable[MAXN];
vector<int> have[MAXN]; 
 
int solve() {
    if (!(cin >> n >> t))
        return 1;
    assert(t == 0);

    vector<int> to_sort(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        to_sort[i] = arr[i];
        have[i].clear();
    }

    sort(ALL(to_sort));
    to_sort.resize(unique(ALL(to_sort)) - to_sort.begin());
    int m = SZ(to_sort);

    for (int i = 0; i < n; i++){
        arr[i] = (int)(lower_bound(ALL(to_sort), arr[i]) - to_sort.begin());
        have[arr[i]].push_back(i);
    }
    for (int i = 0; i < n; i++)
        arr12[i] = (arr[i] + 1 == m) + 1;

    set<pair<int, int>> segments;
    int ans = 0;
    
    auto change_el = [&](int pos){
        arr12[pos] = 2;
        // if (pos == 0 || pos + 1 == n)
        //     return;
        int l = pos + 1, r = pos - 1;
        auto nxt = segments.upper_bound({pos, pos});
        bool have_left = (nxt != segments.begin() && pos - 2 >= 0 && pos - 2 <= prev(nxt)->second);
        if (have_left){
            auto prv = prev(nxt);
            if (arr12[pos - 1] == 1){
                l = prv->first;
                segments.erase(prv);
            }
            else {
                int nl = prv->first, nr = prv->second;
                segments.erase(prv);
                if (nl <= pos - 2){
                    ans = max(ans, (pos - nl) / 2);
                    segments.insert({nl, pos - 2});
                }
                if (pos + 2 <= nr){
                    ans = max(ans, (nr - pos) / 2);
                    segments.insert({pos + 2, nr});
                }
            }
        }
        nxt = segments.upper_bound({pos, pos});
        bool have_right = (nxt != segments.end() && nxt->first <= pos + 2 && pos + 2 < n);
        if (have_right){
            if (arr12[pos + 1] == 1){
                r = nxt->second;
                segments.erase(nxt);
            }
            else {
                int nl = nxt->first, nr = nxt->second;
                segments.erase(nxt);
                if (nl <= pos - 2){
                    ans = max(ans, (pos - nl) / 2);
                    segments.insert({nl, pos - 2});
                }
                if (pos + 2 <= nr){
                    ans = max(ans, (nr - pos) / 2);
                    segments.insert({pos + 2, nr});
                }
            }
        }
        if (!have_left && !have_right && arr12[pos - 1] == 1 && arr12[pos + 1] == 1){
            ans = max(ans, 1);
            segments.insert({pos, pos});
        }
        if (l <= r){
            ans = max(ans, (r - l + 2) / 2);
            segments.insert({l, r});
        }
    };


    for (int i = 0; i < n; i++)
        stable[i] = 0;
    stable[0] = stable[n - 1] = true;
    for (int i = 1; i + 1 < n; i++)
        if (arr12[i - 1] == arr12[i] || arr12[i] == arr12[i + 1])
            stable[i] = true;

    for (int i = 0; i < n; i++)
        cout << arr12[i] << " \n"[i + 1 == n];

    for (int i = 0; i < n; i++)
        cout << stable[i] << " \n"[i + 1 == n];

    int start = -1;
    for (int i = 1; i + 1 < n; i++){
        if (!stable[i]){
            if (start == -1)
                start = i;
        }
        else {
            if (start != -1)
                segments.insert({start, i - 1});
            start = -1;
        }
    }
    if (start != -1)
        segments.insert({start, n - 2});
    for (auto [l, r] : segments)
        ans = max(ans, (r - l + 2) / 2);

    for (int i = m - 2; i >= 0; i--){
        for (auto [l, r] : segments)
            cout << "(" << l + 1 << ", " << r + 1 << "), ";
        cout << '\n';
        for (int j = 0; j < n; j++)
            cout << arr12[j] << " \n"[j + 1 == n];
        for (int pos : have[i])
            change_el(pos);
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
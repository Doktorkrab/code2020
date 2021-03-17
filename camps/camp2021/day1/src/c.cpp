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
const int MAXN = 129;
vector<int> ans;
int indexes[MAXN];
void rec(vector<pair<int, int>> arr, int start = 0){
    int n = SZ(arr);
    auto check = [&](){
        bool good = true;
        for (int i = 0; i < n / 2; i++)
            good &= (indexes[arr[i].second] <= (n / 2 - 1 + start));
        return good;
    };
    while (!check()) {
        if (indexes[arr[n / 2 - 1].second] > n / 2 - 1 + start) {
            ans.push_back(n);
            rotate(arr.rbegin(), arr.rbegin() + 1, arr.rend());
        } else {
            auto p = arr[n / 2 - 1];
            ans.push_back(n / 2);
            arr.erase(arr.begin() + n / 2 - 1);
            arr.insert(arr.begin(), p);
        }
//        for (auto x : arr)
//            cout << x.first << " ";
//        cout << endl;
    }
    if (n == 2)
        return;
    vector<pair<int, int>> l = {arr.begin(), arr.begin() + n / 2};
    vector<pair<int, int>> r = {arr.begin() + n / 2, arr.begin() + n};
    rec(l, start);
    for (int i = 0; i < n / 2; i++)
        ans.push_back(n);
    rec(r, start + n / 2);
    for (int i = 0; i < n / 2; i++)
        ans.push_back(n);

}
int solve() {
    if (!(cin >> n))
        return 1;
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i].first, arr[i].second = i;
    auto t = arr;
    sort(ALL(t));
    for (int i = 0; i < n; i++)
        indexes[t[i].second] = i;
    vector<int> tt(n);
    for (int i = 0; i < n; i++)
        tt[i] = arr[i].first;
    rec(arr);

    cout << SZ(ans) << '\n';
    for (int x : ans)
        cout << x << ' ';
    cout << '\n';
//    for (int x : ans){
//        int y = tt[x - 1];
//        tt.erase(tt.begin() + x - 1);
//        tt.insert(tt.begin(), y);
//    }
//    for (int i = 0; i < n; i++)
//        cout << tt[i] << " \n"[i + 1 == n];
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
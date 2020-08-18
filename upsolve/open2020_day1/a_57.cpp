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
 
int n, t;
const int MAXN = 5e5 + 7;
int stable[MAXN];
int arr[MAXN];
int tmp[MAXN];
int ans_arr[MAXN];
int ans = 0;

void compute(int x){
    for (int i = 0; i < n; i++)
        stable[i] = 0;
    stable[0] = stable[n - 1] = true;
    for (int i = 1; i + 1 < n; i++)
        if (tmp[i - 1] == tmp[i] || tmp[i] == tmp[i + 1])
            stable[i] = true;

    int start = 0;
    int len = 0;
    for (int i = 0; i < n; i++){
        if (!stable[i]){
            if (len == 0)
                start = i;
            len++;
            continue;
        }
        if (len == 0)
            continue;
        ans = max(ans, (len + 1) / 2);
        for (int j = 0; j < len / 2; j++)
            tmp[start + j] = tmp[start - 1];
        for (int j = len / 2; j < len; j++)
            tmp[start + j] = tmp[i];
        len = 0;
    }
    for (int i = 0; i < n; i++)
        if (tmp[i] == 2)
            ans_arr[i] = max(ans_arr[i], x);
}

void prepare(int x){
    for (int i = 0; i < n; i++)
        tmp[i] = (arr[i] >= x) + 1;
    compute(x);
}
 
int solve() {
    if (!(cin >> n >> t))
        return 1;
    vector<int> to_sort(n);
    ans = 0;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        to_sort[i] = arr[i];
    }
    sort(ALL(to_sort));
    to_sort.resize(unique(ALL(to_sort)) - to_sort.begin());

    for (int i = 0; i < n; i++)
        arr[i] = (int)(lower_bound(ALL(to_sort), arr[i]) - to_sort.begin());
    for (int i = 0; i < SZ(to_sort); i++)
        prepare(i);
    cout << ans << '\n';
    if (t == 1)
        for (int i = 0; i < n; i++)
            cout << to_sort[ans_arr[i]] << " \n"[i + 1 == n];
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
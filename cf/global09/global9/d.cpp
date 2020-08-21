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
const int MAXN = 1e3 + 7;
int arr[MAXN];
int cnt[MAXN];
bool placed[MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cnt[i] = 0;
    
    cnt[n] = 0;
    cnt[n + 1] = 0;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        placed[i] = 0;
        cnt[arr[i]]++;
    }
    vector<int> ans;
    int offset = 0;
    for (int i = 0; i <= 2 * n; i++){
        bool good = true;
        for (int j = 1; j < n; j++)
            good &= (arr[j - 1] <= arr[j]);
        if (good)
            break;

        int mex = 0;
        while (cnt[mex] > 0)
            mex++;
        int pos = mex;
        if (mex == n){
            for (int j = 0; j < n; j++)
                if (!placed[j]){
                    pos = j;
                    break;
                }
        }
        // cerr << pos << ' ' << mex << '\n';
        cnt[arr[pos]]--;
        cnt[mex]++;
        arr[pos] = mex;
        ans.push_back(pos + 1);
        placed[pos] = true;
        // for (int j = 0; j < n; j++)
        //     cerr << arr[j] << " \n"[j + 1 == n];
    }
    bool good = true;
    for (int j = 1; j < n; j++)
        good &= (arr[j - 1] <= arr[j]);

    // for (int i = 0; i < n; i++)
    //     cerr << arr[i] << " \n"[i + 1 == n];
    assert(good && SZ(ans) <= 2 * n);
    cout << SZ(ans) << '\n';
    for (int i  : ans)
        cout << i << ' ';
    cout << '\n';
    return 0;
}
 
signed main() {
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
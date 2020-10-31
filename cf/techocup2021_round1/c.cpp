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
const int MAXN = 1e5 + 7;
pair<int, int> sorted[MAXN * 6];
ll notes[6];
ll arr[MAXN];
int have[MAXN];
int cnt = 0;
void add(int index, int who){
//    cout << sorted[index].second << ' ' << who << ' ' << have[sorted[index].second] << "!\n";
    have[sorted[index].second] += who;
    if (have[sorted[index].second] == 0 && who == -1)
        cnt--;
    if (have[sorted[index].second] == 1 && who == 1)
        cnt++;
}
int solve() {
    if (!(cin >> notes[0]))
        return 1;
    for (int i = 1; i < 6; i++)
        cin >> notes[i];
    cin >> n;
    int pnt = 0;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        for (int j = 0; j < 6; j++)
            sorted[pnt++] = {arr[i] - notes[j], i};
    }
    sort(sorted, sorted + pnt);
    int r = 0;
    ll ans = TMAX(ll);
    for (int i = 0; i < pnt; i++){
        while (r < pnt && cnt < n)
            add(r++, 1);
        if (cnt == n) {
//            cout << cnt << ' ' << i << ' ' << r << ' ' << (sorted[r - 1].first - sorted[i].first) << '\n';
            ans = min(ans, 1LL * (sorted[r - 1].first - sorted[i].first));
        }
        add(i, -1);
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

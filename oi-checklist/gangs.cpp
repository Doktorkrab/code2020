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
 
int m, n;
const int MAXN = 105;
int arr[MAXN];
void update_state(int& cur_cows, int& cur_gang, int new_gang){
    if (cur_cows == 0)
        cur_gang = new_gang;
    
    if (cur_gang == new_gang)
        cur_cows++;
    else
        cur_cows--;
}

int get_max(int cur_cows, int cur_gang){
    set<pair<int, int>> kek;
    // for (int i = 0; i < n; i++)
    //     cerr << arr[i] << " \n"[i == n - 1];
    for (int i = 1; i < n; i++)
        kek.insert({arr[i], i});
    while (SZ(kek)){
        auto lel = (*kek.rbegin());
        int cnt = lel.first;
        int gang = lel.second;
        kek.erase(prev(kek.end()));
        if (cnt == 0)
            continue;
        update_state(cur_cows, cur_gang, gang);
        if (cnt - 1 >= 0)
            kek.insert({cnt - 1, gang});
    }
    // cerr << cur_cows << ' ' << cur_gang << '\n';
    for (int i = 0; i < arr[0]; i++)
        update_state(cur_cows, cur_gang, 0);
    if (cur_gang != 0)
        return 0;
    return cur_cows;
}
int solve() {
    if (!(cin >> m >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int cur_cows = 0;
    int cur_gang = 0;
    int ans = get_max(cur_cows, cur_gang);
    // cerr << "here\n";
    if (ans == 0){
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n" << ans << endl;
    for (int i = 0; i < m; i++){
        int now = 0;
        int s1 = cur_cows;
        int s2 = cur_gang;
        for (; ; now++){
            // cerr << i << ' ' << now << '\n';
            assert(now < n);
            if (arr[now] == 0)
                continue;
            arr[now]--;
            // cerr << '\t' << cur_cows << ' ' << cur_gang << '\n';
            update_state(cur_cows, cur_gang, now);
            // cerr << '\t' << cur_cows << ' ' << cur_gang << '\n';
            // cerr << '\t' << get_max(cur_cows, cur_gang) << '\n';
            if (get_max(cur_cows, cur_gang) == ans){
                cout << now + 1 << '\n';
                break;
            }
            arr[now]++;
            cur_cows = s1;
            cur_gang = s2;
        }
    }
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out", "w", stdout);
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
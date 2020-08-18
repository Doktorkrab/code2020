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
 
int n, m;
const int MAXN = 2e5 + 7;
pair<int, int> people[MAXN];
int have[MAXN];
int need[MAXN];
set<int> can_eat[MAXN];
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++){
        can_eat[i].clear();
        need[i] = 0;
    }
    for (int i = 0; i < n; i++)
        cin >> have[i];
    for (int i = 0; i < m; i++){
        cin >> people[i].first >> people[i].second;
        people[i].first--, people[i].second--;
     
        can_eat[people[i].first].insert(i);
        need[people[i].first]++;
        can_eat[people[i].second].insert(i);
        need[people[i].second]++;
    }
    int bad_cnt = 0;
    for (int i = 0; i < n; i++)
        if (need[i] > have[i])
            bad_cnt++;
    if (bad_cnt == n){
        cout << "DEAD\n";
        return 0;
    }
    set<pair<int, int>> setik;
    for (int i = 0; i < n; i++)
        setik.insert({have[i] - need[i], i});
    vector<int> ans1, ans2;
    while (SZ(setik)){
        // for (auto [x, y] : setik)
        //     cout << "(" << x << ", " << y << "), ";
        // cout << '\n';
        auto [bal, i] = (*setik.rbegin());
        if (bal < 0){
            cout << "DEAD\n";
            return 0;
        }
        setik.erase(prev(setik.end()));

        for (int x : can_eat[i]){
            auto [f, s] = people[x];
            // cout << f << ' ' << s << ' ' << x << ' ' << i << '\n';
            if (f == i){
                can_eat[s].erase(x);
                setik.erase({have[s] - need[s], s});

                need[s]--;
                ans1.push_back(x + 1);
                setik.insert({have[s] - need[s], s});
            }
            else {
                can_eat[f].erase(x);
                setik.erase({have[f] - need[f], f});

                need[f]--;
                ans2.push_back(x + 1);
                setik.insert({have[f] - need[f], f});
            }
        }
        can_eat[i].clear();
    }
    cout << "ALIVE\n";
    reverse(ALL(ans1));
    reverse(ALL(ans2));
    for (int i : ans1)
        cout << i << ' ';
    // cout << '\n';
    for (int i : ans2)
        cout << i << ' ';
    cout << '\n';
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
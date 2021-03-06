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

int n, k;
const int MAXN = 1e5 + 7;
const ll INF = 1e18;
struct Queue{
    vector<pair<ll, ll>> s1, s2;
    void push(ll x){
        ll mn = x;
        if (SZ(s1))
            mn = min(s1.back().second, mn);
        s1.emplace_back(x, mn);
    }
    void pop(){
        if (SZ(s2)){
            s2.pop_back();
            return;
        }
        while (SZ(s1)){
            auto [x, _] = s1.back();
            s1.pop_back();
            ll mn = x;
            if (SZ(s2))
                mn = min(s2.back().second, mn);
            s2.emplace_back(x, mn);
        }
        s2.pop_back();
    }
    ll get_min(){
        ll mn = TMAX(ll);
        if (SZ(s1))
            mn = s1.back().second;
        if (SZ(s2))
            mn = min(mn, s2.back().second);
        return mn;
    }
    int size(){
        return SZ(s1) + SZ(s2);
    }
    void print(){
        for (int i = SZ(s2) - 1; i >= 0; i--)
            cout << s2[i].first << ' ';
        for (auto [i, _] : s1)
            cout << i << ' ';
        cout << '\n';
    }
};
ll dp[MAXN];
ll arr[MAXN];
ll prefix[MAXN];
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];
    prefix[n + 1] = prefix[n];
    arr[n] = arr[n + 1] = 0;
    dp[0] = 0;
    Queue q;
    q.push(0 + arr[0] - prefix[1] / 2);
    for (int i = 0; i < n; i++){
//        cout << i << ": ";
//        q.print();
        dp[i + 1] = q.get_min() + prefix[i + 1] / 2;
//        cout << i << ' ' << q.get_min() << '\n';
        q.push(dp[i + 1] + arr[i + 1] - prefix[i + 2] / 2);
        if (i >= k) {
//            cout << "!\n";
            q.pop();
        }
    }

//    for (int i = 0; i <= n; i++)
//        cout << dp[i] << " \n"[i == n];
    cout << dp[n] << '\n';
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

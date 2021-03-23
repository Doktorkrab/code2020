#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
//#define int ll
#define SZ(X) (int)(X).size()
#define ALL(X) (X).begin(), (X).end()
#define RALL(X) (X).rbegin(), (X).rend()
#define TMAX(X) numeric_limits<X>::max();
#define TMIN(X) numeric_limits<X>::min();

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;
int add(int a, int b){
    return ((a + b) % MOD + MOD) % MOD;
}

int mul(int a, int b){
    return (1LL * a * b) % MOD;
}


int n;
const int MAXN = 1e5 + 7;
int arr[MAXN];
bool is_alive[MAXN];
bool used[MAXN];
int solve(){
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i], is_alive[i] = used[i] = true;
    deque<int> indexes;
    set<int> can_add;
    for (int i = 0; i < n; i++)
        indexes.push_back(i), can_add.insert(i);
    auto get = [&](int x){
        auto it = can_add.upper_bound(x);
        if (it == can_add.end())
            return (*can_add.begin());
        return (*it);
    };
    vector<int> ans;
    while (SZ(indexes)){
        int x = indexes.front();
        indexes.pop_front();
        if (!is_alive[x])
            continue;
        used[x] = false;
        int nxt = get(x);
//        cout << x << ' ' << nxt << '\n';
        if (gcd(arr[x], arr[nxt]) == 1){
            ans.push_back(nxt);
            is_alive[nxt] = false;
            can_add.erase(nxt);
            if (x != nxt) {
                used[x] = true;
                indexes.push_back(x);
            }
        }
    }
    cout << SZ(ans) << ' ';
    for (int x : ans)
        cout << x + 1 << ' ';
    cout << '\n';
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tests = 1;
    cin >> tests;
    for (int test = 1; test <= tests; test++){
        if (solve())
            break;
#ifdef LOCAL
        cout << "-----------\n";
#endif
    }
    return 0;
}

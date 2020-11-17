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

const int N = 3e5;
 
int n;
int a[N], b[N];

int cnt[2 * N];
multiset<int, greater<int>> f;

void add(int x){
    f.erase(f.find(x));
    ++cnt[x];
    f.insert(cnt[x]);
}

void del(int x){
    f.erase(f.find(x));
    --cnt[x];
    f.insert(cnt[x]);
}

int get(){
    return *f.begin();
}

int ans[2 * N];
bool used[N];

int ptr[2 * N];

int solve() {
    if (!(cin >> n))
        return 1;
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> a[i] >> b[i];
        --a[i], --b[i];
        add(a[i]);
        add(b[i]);
    }
    int s = a[0], f = b[0];
    used[0] = true;
    ans[0] = s;
    ans[1] = f;
    int k = n;
    while (get() < k) {
        --k;
        ans[2 * (n - k)] = a[ptr[f]];
        ans[2 * (n - k) + 1] =
    }
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

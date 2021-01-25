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


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 3 + 1;
    const int MAXC = 10;
    unordered_set<int> ul, ur;
    cout << n << '\n';
    for (int i = 0; i < n; i++){
        int l = rnd() % MAXC + 1;
        int r = rnd() % MAXC + 1;
        if (l > r)
            swap(l, r);
        while (ul.count(l) || ur.count(r)){
            l = rnd() % MAXC + 1;
            r = rnd() % MAXC + 1;
            if (l > r)
                swap(l, r);
        }
        cout << l << ' ' << r << '\n';
        ul.insert(l);
        ur.insert(r);
    }
    int q = rnd() % 5 + 1;
    cout << q << '\n';
    for (int i = 0; i < q;i ++)
        cout << rnd() % n + 1 << '\n';
}

#include <bits/stdc++.h>

using namespace std;
#define SZ(x) (int)((x).size())

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 5;
    const int MAXM = 3;
    const int MAXC = 20;
    int n = rnd() % MAXN + 1;
    cout << n << '\n';
    int sm = 0;
    for (int i = 0; i < n; i++) {
        int m = rnd() % MAXM + 1;
        sm += m;
        if (i + 1 == n && sm <= n)
            m = n - (sm - m) + 1;
        cout << m << ' ';
        int len = rnd() % MAXC + m + 1;
        set<int> have;
        while (SZ(have) != m)
            have.insert(rnd() % len);
        cout << len - 1 << '\n';
        for (int x : have)
            cout << x << ' ';
        cout << '\n';
    }
}
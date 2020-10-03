#include <bits/stdc++.h>
#include <chrono>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

    const int MAXN = 15;
    int n = rnd() % MAXN + 1, m = rnd() % MAXN + 1, k = 35;
    vector<bool> used(k + 1);
    cout << n << ' ' << m << ' ' << k << '\n';
    for (int i = 0; i < m; i++){
        int l = rnd() % n + 1;
        int r = rnd() % n + 1;
        int x = rnd() % k + 1;
        if (r < l)
            swap(l, r);
        while (used[x])
            x = rnd() % k + 1;
        used[x] = true;
        cout << l << ' ' << r << ' ' << x << '\n';
    }
}

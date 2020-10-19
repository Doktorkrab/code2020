#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 2;
    const int MAXC = 6;
    int n = rnd() % MAXN + 1;
    vector<int> have(2 * MAXC);
    iota(have.begin(), have.end(), -MAXC);
    shuffle(have.begin(), have.end(), rnd);
    vector<bool> used(2 * MAXC);
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int x = rnd() % (2 * MAXC);
        if (x - MAXC == 0)
            x += rnd() % 3 + 1;
        used[x] = true;
        cout << have[i] << ' ' << x - MAXC << '\n';
    }
    int q = rnd() % MAXC + 1;
    cout << q << '\n';
    for (int i = 0; i < q; i++){
        int kek = rnd() % (2 * MAXC);
        while (used[kek])
            kek = rnd() % (2 * MAXC);
        cout << 0 << ' ' << kek - MAXC << '\n';
    }
}
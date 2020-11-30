#include <bits/stdc++.h>


using namespace  std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 5;
    const int MAXC = 10;
    int n = rnd() % MAXN + 1;
    cout << n << '\n';
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end(), rnd);
    for (int i = 0; i < n; i++){
        cout << rnd() % MAXC + 1 << ' ' << perm[i] << '\n';
    }
}
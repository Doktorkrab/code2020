#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 30 + 1;
    int m = rnd() % 8 + 1;
    int q = rnd() % 5 + 1;
    cout << n << ' ' << m << ' ' << q << '\n';
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end(), rnd);
    sort(perm.begin(), perm.begin() + m);
    for (int i = 0; i < m; i++)
        cout << perm[i] << " \n"[i + 1 == m];
    for (int i = 0; i < q; i++)
    cout << rnd() % n + 1 << " \n"[i + 1 == q];

}
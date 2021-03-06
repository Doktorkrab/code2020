#include <bits/stdc++.h>

using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 10;
    const int MAXK = 10;
    int n = rnd() % MAXN + 1;
    int k = rnd() % MAXK + 1;
    cout << n << " " << k << '\n';
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    for (int i = 0; i < k; i++){
        int sz = rnd() % n + 1;
        shuffle(perm.begin(), perm.end(), rnd);
        cout << sz << ' ';
        for (int j = 0; j < sz; j++)
            cout << perm[j] << " \n"[j + 1 == sz];
    }
}
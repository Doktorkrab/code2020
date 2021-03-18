#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void gen_c(){
    int n = rnd() % 5 + 1;
    n *= 2;
    cout << n << ' ' << n << '\n';
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end(), rnd);
    for (int i = 0; i < n; i++)
        cout << perm[i] << " \n"[i + 1 == n];
}

int main(){
    gen_c();
}
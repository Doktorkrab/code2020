#include <bits/stdc++.h>

using namespace std;


mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void gen_a(){
    int n = rnd() % 3 + 2;
    cout << n << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % 2 << " \n"[i + 1 == n];
}

int main(){
    gen_a();
}
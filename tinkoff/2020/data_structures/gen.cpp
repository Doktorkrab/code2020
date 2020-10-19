#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXC = 10;
    int n = rnd() % 3 + 1;
    cout << n << '\n';
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < n; j++)
            cout << rnd() % MAXC + 1 << " \n"[j + 1 == n];
}
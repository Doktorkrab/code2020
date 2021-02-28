#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 3 + 1;
    cout << n << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % 7 << ' ' << 0 << ' ' << rnd() % 5 + 1 << '\n';
}
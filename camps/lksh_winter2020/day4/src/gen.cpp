#include <bits/stdc++.h>

using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int MAXN = 10;
    int MAXC = 100;
    int n = rnd() % MAXN + 1;
    cout << n << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % MAXC + 1 << " \n"[i + 1 == n];
}
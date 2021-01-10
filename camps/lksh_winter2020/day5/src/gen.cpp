#include <bits/stdc++.h>

using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 10;
    int n = rnd() % MAXN + 1;
    for (int i = 0; i < n; i++)
        cout << (char)('a' + rnd() % 26);
    cout << '\n';
}
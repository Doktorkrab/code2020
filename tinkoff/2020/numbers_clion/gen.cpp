#include <bits/stdc++.h>
using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 9;
    cout << rnd() % MAXN + 1 << ' ' << rnd() % MAXN + 1 << '\n';
}
#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using ll = long long;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const ll MAXN = 1e1;
    ll n = rnd() % MAXN + 1, k = rnd() % MAXN + 1;
    cout << n << ' ' << k << '\n';
}

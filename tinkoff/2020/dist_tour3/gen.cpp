#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 1e3;
    int n = rnd() % MAXN + 1;
    cout << to_string(n).size() << '\n' << n << '\n';
}
#include <bits/stdc++.h>


using namespace std;


int main(){
    mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int64_t MAXN = 1e15;
    cout << (int64_t)(rnd() % (2 * MAXN)) - MAXN << '\n';
    cout << (int64_t)(rnd() % (2 * MAXN)) - MAXN << '\n';
}
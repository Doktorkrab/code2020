#include <bits/stdc++.h>

using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 500;
    const int MAXC = 1e5;
    int n = rnd() % MAXN + 1;
    int k = rnd() % min(100, n);
    cout << n << ' ' << k << '\n';
    vector<int> sorted;
    for (int i = 0; i < n; i++)
        sorted.push_back(rnd() % MAXC + 1);
    sort(sorted.begin(), sorted.end());
    for (int i = 0; i < n; i++)
        cout << sorted[i] << " \n"[i + 1 == n];
}
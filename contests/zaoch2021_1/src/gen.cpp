#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int n = rnd() % (1000) + 2;
    const int MAXC = 500;
    cout << n << '\n';
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++){
        int p = rnd() % i;
        edges.emplace_back(i, p);
    }
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rnd);
    for (int i = 0; i + 1 < n; i++){
        if (rnd() % 2)
            swap(edges[i].first, edges[i].second);
        cout << perm[edges[i].first] + 1 << ' ' << perm[edges[i].second] + 1 << ' ' << rnd() % MAXC + 1 << '\n';
    }
}
#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 5 + 1;
    int d = 3;
    vector<vector<int>> g(n, vector<int>(n));
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            if (i != j) {
                g[i][j] = (rnd() % 12 > 6);
                if (g[i][j])
                    edges.emplace_back(i, j);
            }
    }
    cout << n << ' ' << edges.size() << ' ' << d << '\n';
    for (auto [a, b] : edges)
        cout << a + 1 << " " << b + 1 << '\n';
    for (int i = 0; i < n; i++){
        for (int j = 0; j < d; j++)
            cout << rnd() % 2;
        cout << '\n';
    }
}
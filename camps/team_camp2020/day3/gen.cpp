#include <bits/stdc++.h>


using namespace std;

const int MAXN = 10;

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % MAXN + 2;
    int k = rnd() % (n - 1) + 2;
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int t = rnd();
            if (t % 4 == 0)
                edges.emplace_back(i + 1, j + 1);
            else if (t % 4 == 2)
                edges.emplace_back(j + 1, i + 1);
        }
    cout << n << ' ' << edges.size() << ' ' << k << '\n';

    for (int i = 0; i < n; i++)
        cout << rnd() % k + 1 << " \n"[i + 1 == n];
    for (auto[a, b] : edges)
        cout << a << ' ' << b << '\n';
}
#include <bits/stdc++.h>


using namespace std;

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 100;
    const int MAXC = 1e9;
    int n = rnd() % MAXN;
    int s = rnd() % MAXC + 1;
    int m = 0;
    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (rnd() % 2) {
                edges.push_back({{i + 1, j + 1}, rnd() % s + 1});
                m++;
            }
    cout << n << ' ' << m << " 1 " << s << '\n';
    for (auto [a, b] : edges){
        auto [c, d] = a;
        if (rnd() % 2)
            swap(c, d);
        cout << c << ' ' << d << ' ' << b << '\n';
    }
    cout << "1\n";
}
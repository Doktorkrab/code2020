#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void gen_c() {
    int n = rnd() % 5 + 1;
    n *= 2;
    cout << n << ' ' << n << '\n';
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end(), rnd);
    for (int i = 0; i < n; i++)
        cout << perm[i] << " \n"[i + 1 == n];
}

void gen_d() {
    int n = rnd() % 3 + 1;
    int g = rnd() % 10 + 1;
    cout << n << ' ' << g << '\n';
    for (int i = 0; i + 1 < n; i++)
        cout << i + 1 << ' ' << i + 2 << ' ' << rnd() % 10 + 1 << ' ' << rnd() % 10 << '\n';
    int q = rnd() % 3 + 1;
    cout << q << '\n';
    for (int i = 0; i < q; i++)
        cout << "1 " << rnd() % n + 1 << ' ' << rnd() % n + 1 << '\n';
}

int main() {
    gen_d();
}
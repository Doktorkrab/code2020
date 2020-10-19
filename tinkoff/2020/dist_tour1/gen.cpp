#include <bits/stdc++.h>
using namespace std;
int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

    int n = rnd() % 10 + 1;
    cout << n << '\n';
    vector<int> vec(n - 1);
    vector<int> p(n);
    for (int i = 1; i < n; i++)
        p[i] = rnd() % i;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++)
        g[p[i]].push_back(i);
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin() + 1, perm.end(), rnd);
//    for (int i : perm)
//        cout << i + 1 << ' ';
//    cout << '\n';
//    for (int i : p)
//        cout << i + 1 << ' ';
//    cout << '\n';
//    for (int i = 0; i < n; i++) {
//        cout << g[i].size() << ' ';
//        for (int j : g[i])
//            cout << j + 1 << ' ';
//        cout << '\n';
//    }
//    cout << '\n';
    for (int i : perm){
        cout << g[i].size() << " ";
        shuffle(g[i].begin(), g[i].end(), rnd);
        for (int j : g[i])
            cout << perm[j] + 1 << ' ';
        cout << '\n';
    }
}
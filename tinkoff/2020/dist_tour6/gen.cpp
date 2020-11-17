#include <bits/stdc++.h>


using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 5;
    const int MAXL = 100;
    const int MAXC = 1e9;
    int n = rnd() % MAXN + 1;
    int l = rnd() % MAXL + 20;
    cout << l << '\n' << n << '\n';
    set<int> ans;
    while (ans.size() < n)
        ans.insert(rnd() % MAXC + 1);
    vector<int> kek{ans.begin(), ans.end()};
    shuffle(kek.begin(), kek.end(), rnd);
    for (int i : kek)
        cout << i << '\n';


}
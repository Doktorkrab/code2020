#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXC = 10;
    const int MAXT = 1;
    const int MAXN = 3;
    int t = rnd() % MAXT + 1;
    cout << t << '\n';
    for (int tt = 0; tt < t; tt++) {
        int n = rnd() % MAXN + 4;
        set<pair<int, int>> was;
        vector<pair<int, int>> ans;
        cout << n << '\n';
        while (ans.size() < n){
            int a = rnd() % MAXC + 1;
            int b = rnd() % MAXC + 1;
            if (was.count({a, b}))
                continue;
            was.insert({a, b});
            ans.emplace_back(a, b);
        }
        for (auto [a, b] : ans)
            cout << a << ' ' << b << '\n';
    }
}
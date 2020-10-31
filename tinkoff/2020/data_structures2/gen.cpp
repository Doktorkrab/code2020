#include <bits/stdc++.h>


using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 5 + 1;
    int s = rnd() % 5 + 1;
    vector<vector<bool>> have(s, vector<bool>(n));
    for (int i = 0; i < s; i++)
        for (int j = 0; j < n; j++)
            have[i][j] = rnd() % 2;

    vector<pair<int, pair<int, int>>> segments;
    for (int i = 0; i < s; i++){
        int len = 0;
        for (int j = 0; j < n; j++){
            if (!have[i][j]){
                if (len)
                    segments.push_back({i + 1, {j - len + 1, j + 1}});
                len = 0;
            }
            else
                len++;
        }
    }
    cout << n << ' ' << s << ' ' << segments.size() << '\n';
    for (auto [a, b] : segments)
        cout << a << ' ' << b.first << ' ' << b.second << '\n';
    int q = 1;
    cout << q << '\n';
    for (int i = 0; i < q; i++){
        int l = rnd() % n + 1;
        int r = rnd() % n + 1;
        if (r < l)
            swap(l, r);
        cout << l << ' ' << r << '\n';
    }

}
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>

using namespace std;
int n;
string s;

inline void init(){
    s += '$';
    n = s.size();
}

inline void solve(){
    init();
    vector<int> arr(n);
    vector<int> p(n), c(n);
    vector<int> np(n), nc(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int a, int b){ return s[a] < s[b];});
    int cl = 0;
    for (int i = 0; i < n; i++){
        if (i == 0 || s[p[i]] == s[p[i - 1]])
            c[p[i]] = cl;
        else
            c[p[i]] = ++cl;
    }
    // for (int i : p)
    //     cerr << i << ' ';
    // cerr << '\n';
    // for (int i : c)
    //     cerr << i << ' ';
    // cerr << '\n';
    // cerr << '\n';
    vector<int> cnt(n + 1);
    for (int k = 0; (1 << k) <= n; k++){
        int pk = (1 << k);
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++)
            cnt[c[i] + 1]++;
        for (int i = 1; i < n; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++){
            int j = p[i] - pk;
            if (j < 0)
                j += n;
            np[cnt[c[j]]++] = j;
        }
        cl = 0;
        for (int i = 0; i < n; i++)
            if (i == 0 || make_pair(c[np[i]], c[(np[i] + pk) % n]) == make_pair(c[np[i - 1]], c[(np[i - 1] + pk) % n]))
                nc[np[i]] = cl;
            else
                nc[np[i]] = ++cl;
        swap(nc, c);
        swap(np, p);
    // for (int i : p)
    //     cerr << i << ' ';
    // cerr << '\n';
    // for (int i : c)
    //     cerr << i << ' ';
    // cerr << '\n';
    // cerr << '\n';
    }
    for (int i = 1; i < n; i++)
        cout << p[i] + 1 << " \n"[i == n - 1];
}


int main(){
	//#ifdef LOCAL
		//freopen("A.in", "r", stdin);
		//freopen("A.out", "w", stdout);
	//#endif
	
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> s)
        solve();

}

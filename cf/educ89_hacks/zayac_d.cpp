#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> ans1, ans2;
   //vector<int>lst;
    vector<int> isp;
    isp.assign(10000001, 1);
    for (int i = 2; i < isp.size(); i++){
        if (isp[i] == 1){
            for (int j = i * i; j < isp.size(); j += i){
                if (isp[j] == 1) isp[j] = i;
            }
        }
    }
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        if (isp[x] == 1){
            ans1.push_back(-1);
            ans2.push_back(-1);
            continue;
        }
        int xx = x;
        while(x % isp[xx] == 0){
            x /= isp[xx];
        }
        if (x == 1){
            ans1.push_back(-1);
            ans2.push_back(-1);
            continue;
        }
        ans1.push_back(isp[xx]);
        ans2.push_back(x);
    }
    for (int i =0; i <n;  i++){
        cout << ans1[i] <<  " ";
    }
    cout << '\n';
    for (int i =0; i <n;  i++){
        cout << ans2[i] <<  " ";
    }
    cout << '\n';
    return 0;
}

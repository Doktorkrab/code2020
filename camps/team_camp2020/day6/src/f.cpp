#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define int long long

const int K = 62;

int p[K];
pair<int, int> dp[K];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    p[0] = 1;
    dp[0] = {0, 1};
    for (int i = 1; i < K; ++i) {
        p[i] = p[i - 1] * (-2);
        dp[i] = dp[i - 1];
        if (p[i] > 0) {
            dp[i].second += p[i];
        } else {
            dp[i].first += p[i];
        }
    }
    int x;
    cin >> x;
    vector<int> ans(K);
    for (int i = K - 1; i >= 0; --i) {
        if (i != 0 && dp[i - 1].first <= x && x <= dp[i - 1].second ||
            i == 0 && x == 0) {
            continue;
        } else {
            ans[i] = 1;
            x -= p[i];
        }
    }
    assert(x == 0);
    while (ans.back() == 0) {
        ans.pop_back();
    }
    cout << ans.size() << '\n';
    for (int d : ans) {
        cout << d << ' ';
    }
    cout << '\n';
    return 0;
}
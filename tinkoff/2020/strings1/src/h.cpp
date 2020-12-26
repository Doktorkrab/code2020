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
#define int int64_t
int n, m;
vector<int> p, c, nc, np, cnt, arr, lcp;
vector<int> ans;

void calc() {
    vector<pair<int, int>> stack;
    for (int i = 0; i < n; i++) {
        while (stack.size() && stack.back().second > lcp[i]) {
            auto top = stack.back();
            stack.pop_back();
            ans[top.first] += i - top.first;
        }
        stack.push_back({i, lcp[i]});
    }
    for (auto i : stack)
        ans[i.first] += n - i.first;
}

inline void solve() {
    p.resize(n + 1);
    iota(p.begin(), p.end(), 0);
    c.resize(n + 1);
    nc.resize(n + 1);
    np.resize(n + 1);
    cnt.resize(n + 2);
    arr.resize(n + 1);
    ans.resize(n);
    arr.back() = -1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(p.begin(), p.end(), [&](int a, int b) { return arr[a] < arr[b]; });
    int cl = 0;
    ++n;
    for (int i = 0; i < n; i++) {
        if (i == 0 || arr[p[i]] == arr[p[i - 1]])
            c[p[i]] = cl;
        else
            c[p[i]] = ++cl;
    }
    for (int k = 0; (1 << k) < n; k++) {
        int pk = (1 << k);

        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++)
            cnt[c[i] + 1]++;
        for (int i = 1; i < n; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) {
            int j = (p[i] - pk);
            if (j < 0)
                j += n;
            np[cnt[c[j]]++] = j;
        }
        cl = 0;
        for (int i = 0; i < n; i++) {
            if (i == 0 || make_pair(c[np[i]], c[(np[i] + pk) % n]) == make_pair(c[np[i - 1]], c[(np[i - 1] + pk) % n]))
                nc[np[i]] = cl;
            else
                nc[np[i]] = ++cl;
        }
        swap(nc, c);
        swap(np, p);
    }
    lcp.resize(n);
    vector<int> pos(n);
    for (int i = 0; i < n; i++)
        pos[p[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (k > 0)
            --k;
        if (pos[i] == n - 1) {
            lcp[n - 1] = 0;
            k = 0;
            continue;
        }
        int j = p[pos[i] + 1];
        while (i + k < n && j + k < n && arr[i + k] == arr[j + k])
            k++;
        lcp[pos[i]] = k;
    }
    int maxH = n - 1;
    int maxW = 1;
    int start = 0;
    vector<pair<int, pair<int, int>>> stack;
    for (int i = 0; i < n; i++) {
        int x = 1;
        while (!stack.empty() && lcp[i] <= stack.back().first) {
            auto top = stack.back();
            stack.pop_back();
            x += top.second.first;
            if (x * top.first > maxW * maxH) {
                maxW = x;
                maxH = top.first;
                start = p[top.second.second];
            }
        }
        if (stack.empty() || lcp[i] > stack.back().first)
            stack.push_back({lcp[i], {x, i}});
    }
    cout << maxW * maxH << '\n';
    cout << maxH << '\n';
    cerr << maxH << ' ' << maxW << '\n';
    for (int i = 0; i < maxH; i++)
        cout << arr[start + i] << " \n"[i == maxH - 1];
}


int32_t main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
    freopen("h.out", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n >> m)
        solve();
}

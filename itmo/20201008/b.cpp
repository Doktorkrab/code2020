#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//#pragma optimise("O3")

using namespace std;
using namespace __gnu_pbds;

template<typename T>
tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> indexed_set(T obj) {
    return tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>();
}

#define ALL(v) v.begin(), v.end()
#define eb emplace_back
#define fi first
#define se second
//#define int long long
#define pii pair<int, int>
#define speed cin.tie(0); cout.tie(0); iostream::sync_with_stdio(false)

const long double pi = acos(-1);

mt19937 rnd(time(nullptr));

int32_t main() {
    speed;
    int n;
    cin >> n;
    set<pair<int, int>> berries;
    set<pair<int, int>> ready_to_relax;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        berries.insert(make_pair(i, a));
        arr[i] = a;
    }
    auto relax = [&](int pos, int act) {
        int prv = -1;
        auto now = berries.lower_bound({pos, -1});
        if (now == berries.begin()) {
            prv = prev(berries.end())->second;
        } else {
            prv = prev(now)->second;
        }

        int nxt = -1;
        if (now == prev(berries.end())) {
            nxt = berries.begin()->second;
        } else {
            nxt = next(now)->second;
        }
        int x = now->second;
        if (act == -1) {
            if (prv == x + 1)
                ready_to_relax.erase({x, pos});
            if (nxt == x + 1)
                ready_to_relax.erase({x, pos});
        }
        if (act == 1) {
            if (prv == x + 1)
                ready_to_relax.insert({x, pos});
            if (nxt == x + 1)
                ready_to_relax.insert({x, pos});
        }
    };
    for (int i = 0; i < n; i++)
        relax(i, 1);
    while (!ready_to_relax.empty()) {
//        for (auto [x, pos] : ready_to_relax)
//            cout << pos << ' ' << x << '\n';
//        for (auto [pos, x] : berries)
//            cout << x << ' ';
//        cout << '\n';
        auto[x, pos] = (*ready_to_relax.begin());
        ready_to_relax.erase(ready_to_relax.begin());
        relax(pos, -1);
        auto now = berries.lower_bound({pos, x});
        vector<int> poses;
        if (now == berries.begin())
            poses.push_back(prev(berries.end())->first);
        else
            poses.push_back(prev(now)->first);
        if (now == prev(berries.end()))
            poses.push_back(berries.begin()->first);
        else
            poses.push_back(next(now)->first);
        berries.erase(now);
//        for (int i : poses)
//            cout << i << ' ';
//        cout << '\n';
        for (int i : poses)
            relax(i, 1);
    }
    cout << (berries.size() == 1 ? "YES" : "NO") << '\n';
}

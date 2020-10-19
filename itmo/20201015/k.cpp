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
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    vector<long long> as0 = {a, b, c, d};
    vector<int> kek(4);
    iota(kek.begin(), kek.end(), 0);
    do {
        vector<long long> as(4);
        for (int i = 0; i < 4; i++)
            as[i] = as0[kek[i]];
        long long dx = as[1] - as[0];
        long long dy = as[2] - as[1];
        if (as[2] - dx == as[3] && as[3] - dy == as[0]) {
            cout << "YES\n";
            return 0;
        }
    } while (next_permutation(ALL(kek)));
    cout << "NO\n";
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

//#define int long long
#define INF 1e12
struct pt {
    int x, y;
};

long long dis(pt a, pt b) {
    return (long long) abs(a.x - b.x) + (long long) abs(a.y - b.y);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;

    for (int q = 0; q < t; q++) {
        vector<int> pos = {0, 1, 2, 3};
        vector<int> trx, tryy;

        vector<pt> lst;
        vector<int> aa;
        for (int i = 0; i < 4; i++) {
            pt x;
            cin >> x.x >> x.y;
            lst.push_back(x);
            tryy.push_back(x.y);

            trx.push_back(x.x);
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) continue;
                aa.push_back(lst[i].x - lst[j].x);
                aa.push_back(lst[i].y - lst[j].y);
            }
        }
        bool bl = true;
        long long ans = INF;

        while (bl) {
            for (int x: trx) {
                for (int y: tryy) {
                    for (int i = 0; i < aa.size(); i++) {
                        int a = aa[i];
                        long long cur = 0;
                        cur += dis(lst[pos[0]], {x, y});
                        cur += dis(lst[pos[1]], {x, y + a});
                        cur += dis(lst[pos[2]], {x + a, y + a});
                        cur += dis(lst[pos[3]], {x + a, y});
                        if (cur == 12)
                            cout << x << ' ' << y << ' ' << a << '\n';
                        ans = min(ans, cur);
                    }
                }
            }
            bl = next_permutation(pos.begin(), pos.end());
        }
        cout << ans << '\n';

    }
    //cerr << "Edf of sucking dick";
    return 0;
}
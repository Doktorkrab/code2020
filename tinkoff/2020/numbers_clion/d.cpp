#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;


#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif

int n;
const int MAXN = 5e4 + 7;

struct Segment {
    int g = 1;
    deque<pair<int, ll>> stack;
    multiset<ll> mins;

    Segment() = default;

    Segment(int x, ll sm) {
        stack.emplace_back(x, sm);
        mins.insert(x + sm);
        g = abs(x);
    }

    void merge(Segment &oth) {
        if (!SZ(oth.stack))
            return;

        oth.mins.erase(oth.mins.find(oth.stack.front().first + oth.stack.front().second));
        while (SZ(stack) && stack.back().first <= oth.stack.front().first) {
            auto[a, b] = stack.back();
            oth.stack.front().second = min(oth.stack.front().second, b);
            mins.erase(mins.find(a + b));
            stack.pop_back();
        }
        oth.mins.insert(oth.stack.front().first + oth.stack.front().second);
//        cout << "SZ " << SZ(stack) << ' ' << SZ(oth.stack) << '\n';
        if (SZ(stack) < SZ(oth.stack)) {
            reverse(ALL(stack));
            for (const auto &x : stack) {
                oth.stack.push_front(x);
                oth.mins.insert(x.first + x.second);
            }
            swap(stack, oth.stack);
            swap(mins, oth.mins);
        } else {
            for (const auto &x : oth.stack) {
                stack.push_back(x);
                mins.insert(x.first + x.second);
            }
        }
    }
};

int arr[MAXN];
ll sum[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sum[i + 1] = sum[i] + arr[i];
    }
    ll ans = 0;
    vector<Segment> have;
    for (int i = 0; i < n; i++) {
        vector<Segment> now = {Segment(arr[i], sum[i])};
        reverse(ALL(have));
        for (Segment &oth : have) {
//            cout << "!" << oth.g << ' ' << now.back().g << '\n';
            ll g = gcd(oth.g, now.back().g);
//            cout << '\t' << g << '\n';
            if (g == now.back().g) {
                oth.g = g;
                oth.merge(now.back());
                swap(oth, now.back());
            } else {
                oth.g = g;
                now.push_back(oth);
            }
        }
        for (int j = 1; j < SZ(now); j++) {
            ll mn = TMAX(ll) / 2;
            int cnt = 0;
            Segment &seg = now[j];
            while (SZ(seg.stack) && seg.stack.back().first <= now[j - 1].stack.back().first) {
                cnt++;
                auto[a, b] = seg.stack.back();
                seg.mins.erase(seg.mins.find(a + b));
                mn = min(mn, b);
                seg.stack.pop_back();
            }
            if (cnt) {
                seg.mins.insert(mn + now[j - 1].stack.back().first);
                seg.stack.emplace_back(now[j - 1].stack.back().first, mn);
            }
        }
        reverse(ALL(now));
        swap(now, have);
        for (Segment &s : have) {
//            cout << sum[i + 1] - (*s.mins.begin()) << ' ' << (*s.mins.begin()) << ' ' << s.g << '\n';
//            for (auto[a, b] : s.stack)
//                cout << a << ' ' << b << '\n';
            ans = max(ans, s.g * (sum[i + 1] - (*s.mins.begin())));
        }
//        cout << "------\n";
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

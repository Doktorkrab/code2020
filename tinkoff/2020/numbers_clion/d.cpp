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
    int l = 0, r = MAXN; // [l;r)
    int min = 0, max = 0;
    int g = 0, sum = 0;
    int max_sum = 0;
};

vector<Segment> segments[MAXN];
int arr[MAXN];
inline Segment merge(const Segment& a, const Segment& b){

}
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++){
        segments[i + 1].push_back({i, i + 1, arr[i], arr[i], arr[i], arr[i]});
        for (int j = SZ(segments[i]) - 1; j >= 0; j--){
            int new_g = gcd(segments[i][j].g, segments[i + 1].back().g);
            if (new_g == segments[i + 1].back().g){

            }

        }
    }
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

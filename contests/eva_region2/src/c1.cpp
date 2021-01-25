#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ld = long double;

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

struct Vector{
    ld x, y;
    Vector() = default;
    Vector(ld x, ld y) : x(x), y(y) {}

    Vector operator+(const Vector& oth) const {
        return Vector(x + oth.x, y + oth.y);
    }
    Vector operator-(const Vector& oth) const {
        return Vector(x - oth.x, y - oth.y);
    }
    ld len() const {
//        assert(x * x + y * y < 9e18);
        return sqrt(x * x + y * y);
    }
};
istream& operator>>(istream& is, Vector& v){
    is >> v.x >> v.y;
    return is;
}
ostream& operator<<(ostream& os, const Vector& v){
    os << v.x << ' ' << v.y;
    return os;
}

int n;
ld l;
int k;
const int MAXN = 1e5 + 7;
Vector polygon[MAXN];
bool hole[MAXN];


int solve() {
    if (!(cin >> n >> l >> k))
        return 1;
    fill(hole, hole + n, false);
    ld have = 0;
    for (int i = 0; i < k; i++){
        int x;
        cin >> x;
        hole[x - 1] = true;
    }
    for (int i = 0; i < n; i++)
        cin >> polygon[i];
    for (int i = 0; i < n; i++)
        if (hole[i])
            have += (polygon[(i + 1) % n] - polygon[i]).len();
    ld best = have;
    for (int i = 0; i < n; i++){
        bool was = false;
        ld now_a = 0, now = 0;
        for (int j = i; !was || j != i; j = (j + 1) % n){
            was = true;
            ld took = min((polygon[(j + 1) % n] - polygon[j]).len(), l - now);
            if (hole[j])
                now_a += took;
            now += took;
        }
        best = min(best, have - now_a);
    }
    cout << fixed << setprecision(20) << best << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#endif
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

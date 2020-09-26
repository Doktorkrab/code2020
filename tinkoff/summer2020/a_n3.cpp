#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
#define int ll

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

struct Vector{
    int x, y;
    
    // constructors
    Vector() : x(0), y(0) {}
    Vector(int _x, int _y) : x(_x), y(_y) {}
    Vector(const Vector& a, const Vector& b) : x(b.x - a.x), y(b.y - a.y) {}

    // operators

    Vector operator+(const Vector& a) const {
        return Vector(x + a.x, y + a.y);
    }
    Vector operator-(const Vector& a) const {
        return Vector(x - a.x, y - a.y);
    }
    Vector operator*(int k) const {
        return Vector(k * x, k * y);
    }
    //Vector operator/(double k) const {}
    
    Vector operator-() const {
        return Vector(-x, -y);
    }

    Vector& operator+=(const Vector& oth){
        return (*this) = (*this) + oth;
    }
    Vector& operator-=(const Vector& oth){
        return (*this) = (*this) - oth;
    }
    Vector& operator*=(int k){
        return (*this) = (*this) * k;
    }

    // input/output operator

    friend istream& operator>>(istream& is, Vector& v){
        is >> v.x >> v.y;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Vector& v){
        os << v.x << ' ' << v.y;
        return os;
    }

    // methods
    
    ll len2() const {
        return x * x + y * y;
    }
    double len() const {
        return sqrt(len2());
    }

    Vector rotate90() const {
        return Vector(-y, x);
    }

    int dot_product(const Vector& a) const {
        return x * a.x + y * a.y;
    }

    int cross_product(const Vector& b) const {
        return x * b.y - b.x * y;
    }
};

struct Line{
    int a, b, c;

    // constructors
    Line() : a(1), b(1), c(0) {}
    Line(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}

    Line (const Vector& p1, const Vector& p2){
        Vector normal = Vector(p1, p2).rotate90();
        a = normal.x, b = normal.y;
        c = -(a * p1.x + b * p1.y);
    }
    // input/output operator

    friend ostream& operator<<(ostream& os, const Line& l){
        os << l.a << ' ' << l.b << ' ' << l.c;
        return os;
    }

    // methods

    int dist_sign(const Vector& v) const {
        int dist = a * v.x + b * v.y + c;
        if (dist == 0)
            return 0;
        else if (dist < 0)
            return -1;
        return 1;
    }

    double dist(const Vector& v) const {
        assert(abs(a) + abs(b) != 0);
        return 1. * (a * v.x + b * v.y + c) / sqrt(a * a + b * b);
    }
    bool operator<(const Line& l) const {
        //cerr << a << ' ' << b << ' ' << c << '\n';
        assert(abs(a) + abs(b) != 0);
        assert(abs(l.a) + abs(l.b) != 0);
        if (a == 0 || l.a == 0){
            if (l.a != 0 && a == 0)
                return true;
            if (a != 0 && l.a != 0)
                return false;
            ll c1 = c;
            ll b1 = b;
            if (b < 0)
                c1 *= -1, b1 *= -1;
            ll c2 = l.c;
            ll b2 = l.b;
            if (b2 < 0)
                c2 *= -1, b2 *= -1;
            return 1LL * c1 * b2 < 1LL * c2 * b1;
        }
        Line t = (*this);
        if (t.a < 0)
            t.a *= -1, t.b *= -1, t.c *= -1;
        Line t1 = l;
        if (t1.a < 0)
            t1.a *= -1, t1.b *= -1, t1.c *= -1;
        ll tmp1 = 1LL * t1.b * t.a;
        ll tmp = 1LL * t.b * t1.a;
        if (tmp != tmp1)
            return tmp < tmp1;
        return 1LL * t.c * t1.a < 1LL * t1.c * t.a;
    }
};

const int MAXN = 1005;
Vector arr[MAXN];
Vector center;

int solve() {
    if (!(cin >> n >> center))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    set<Line> ans;
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if ((arr[j] - arr[i]).dot_product(center - arr[i]) <= 0 || (arr[i] - arr[j]).dot_product(center - arr[j]) <= 0)
                continue;
            Line l = Line(arr[i], arr[j]);
            //cout << arr[i] << " | " << arr[j] << " | " << l << '\n';
            int sign = l.dist_sign(center);
            //cout << sign << '\n';
            bool good = true;
            for (int k = 0; k < n; k++){
                int sign_now = l.dist_sign(arr[k]);
                //cout << arr[k] << " | " << sign_now << '\n';
                if (sign_now == 0)
                    continue;
                if (sign == 0)
                    sign = sign_now;
                if (sign != sign_now){
                    good = false;
                    //break;
                }
            }
            if (good){
                ans.insert(l);
                //cout << arr[i] << " | " << arr[j] << '\n';
            }
        }
    }
    cout << ans.size() << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

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

struct Vector {
    ll x, y;

    ll operator*(const Vector &oth) const {
        return x * oth.x + y * oth.y;
    }

    ll operator^(const Vector &oth) const {
        return x * oth.y - oth.x * y;
    }

    Vector operator-(const Vector &oth) const {
        return {x - oth.x, y - oth.y};
    }

    Vector operator+(const Vector &oth) const {
        return {x + oth.x, y + oth.y};
    }

    bool operator<(const Vector &oth) const {
        return tie(x, y) < tie(oth.x, oth.y);
    }

    bool operator==(const Vector &oth) const {
        return tie(x, y) == tie(oth.x, oth.y);
    }
};

istream &operator>>(istream &is, Vector &v) {
    is >> v.x >> v.y;
    return is;
}

ostream &operator<<(ostream &os, Vector &v) {
    os << v.x << ' ' << v.y;
    return os;
}

struct Node {
    Node *prev = nullptr;
    Node *next = nullptr;
    Vector val;
    int index = 0;

    Node(Vector val, int index) : val(val), index(index) {}
};


ll trap_square(Vector a, Vector b) {
    return (a.y + b.y) * (b.x - a.x);
}

ll find_square(const vector<Vector> &points) {
    ll ans = 0;
    int n = SZ(points);
    for (int i = 0; i < n; i++) {
        int nxt = (i + 1) % n;
        ans += trap_square(points[i], points[nxt]);
    }
    return ans;
}

int n;

int solve() {
    if (!(cin >> n))
        return 1;
    vector<pair<Vector, int>> polygon_index(n);
    vector<Vector> polygon(n);
    int index = 0;
    for (auto&[x, i] : polygon_index)
        cin >> x, i = index++;
    for (int i = 0; i < n; i++)
        polygon[i] = polygon_index[i].first;
    ll square = find_square(polygon);
    if (square < 0)
        reverse(ALL(polygon_index));
    Node *first = new Node(polygon_index[0].first, polygon_index[0].second);
    first->next = first->prev = first;
    Node *back = first;
    for (int i = 1; i < n; i++) {
        Node *new_node = new Node(polygon_index[i].first, polygon_index[i].second);
        new_node->prev = back;
        new_node->next = first;
        first->prev = new_node;
        back->next = new_node;
        back = new_node;
    }
    auto is_convex = [&](const Vector &a, const Vector &b, const Vector &c) {
        int tmp = (a - b) ^(c - b);
        return tmp > 0;
    };
    auto in_triangle = [&](const Vector &a, const Vector &b, const Vector &c, const Vector &d) {
        if (d == a || d == b || d == c)
            return false;
        ll sq = (b - a) ^(c - a);
        ll sq1 = (b - a) ^(d - a);
        ll sq2 = (c - a) ^(d - a);
        ll sq3 = (c - b) ^(d - b);
        return abs(sq) == abs(sq1) + abs(sq2) + abs(sq3);
    };
    int sz = n;
    vector<pair<int, int>> ans;
    while (sz > 3) {
        Node *now = first;
        for (int i = 0; i < sz; i++, now = now->next) {
            Vector v_now = now->val;
            Vector v_prev = now->prev->val;
            Vector v_next = now->next->val;
            if (!is_convex(v_prev, v_now, v_next))
                continue;
            if (in_triangle(v_prev, v_now, v_next, first->val))
                continue;
            bool good = true;
            for (Node *to_check = first->next; to_check != first; to_check = to_check->next)
                good &= !in_triangle(v_prev, v_now, v_next, to_check->val);
            if (!good)
                continue;
            ans.emplace_back(now->prev->index, now->next->index);
            --sz;
            if (first == now)
                first = now->next;
            if (back == now)
                back = now->prev;
            now->prev->next = now->next;
            now->next->prev = now->prev;
            break;
        }
    }
    for (auto[a, b] : ans)
        cout << a << ' ' << b << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
#else
    freopen("triang.in", "r", stdin);
    freopen("triang.out", "w", stdout);
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

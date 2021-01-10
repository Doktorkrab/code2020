#include <iostream>
#include <string>
#include "testlib.h"
#include <vector>

using namespace std;
using ll = long long;
struct Vector {
    int x, y;
    ll operator^(const Vector& oth) const {
        return 1LL * x * oth.y - oth.x * y;
    }
};

int halfplane(const Vector &a) {
    if (a.y != 0)
        return (a.y > 0 ? 1 : -1);
    return (a.x < 0 ? -1 : 1);
}

bool operator<(const Vector &a, const Vector &b) {
    if (halfplane(a) != halfplane(b))
        return halfplane(a) < halfplane(b);
    return (a ^ b) < 0;
}


int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>("n");
//    int outer = opt<int>("outer");
    const int MAX = 2e5;
    int t = MAX / n;
    std::cout << t << '\n';
    for (int tt = 0; tt < t; tt++) {
        vector<Vector> vectors;
        ll x_sum = 0, y_sum = 0;
        for (int i = 0; i < n - 1; i++){
            int x = rnd.next(-3000, 3000);
            int y = rnd.next(-3000, 3000);
            x_sum += x;
            y_sum += y;
            vectors.push_back({x, y});
        }
        vectors.push_back({-(int)x_sum, -(int)y_sum});
        sort(vectors.begin(), vectors.end());
        int x_now = 0;
        int y_now = 0;
        vector<Vector> points = {{x_now, y_now}};
        for (Vector& v : vectors){
            x_now += v.x;
            y_now += v.y;
            points.push_back({x_now, y_now});
        }
        int x_min = 0, y_min = 0;
        for (auto [a, b] : points)
            x_min = min(x_min, a), y_min = min(y_min, b);
        for (auto& [a, b] : points)
            a -= x_min, b -= y_min;
        points.pop_back();
        set<pair<int, int>> all_points;
        for (auto [a, b] : points)
            all_points.insert({a, b});
        vector<pair<int, int>> kek = {all_points.begin(), all_points.end()};
        shuffle(kek.begin(), kek.end());
        cout << kek.size() << '\n';
        for (auto [a, b] : kek)
            cout << a << ' ' << b << '\n';
    }
    return 0;
}

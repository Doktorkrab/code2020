#include <bits/stdc++.h>

using namespace std;

pair<bool, long long> make_higher(long long a) {
    long long prev_pow = 0;
    long long pow_ten = 1;
    while(pow_ten <= a) {
        long long dig = ((a) % (10 * pow_ten)) / pow_ten;
        if (dig != 9) {
            prev_pow = pow_ten;
        }
        pow_ten *= 10;
    }
    if (prev_pow == 0) {
        return {false, a};
    } else {
        long long dig = ((a) % (10 * prev_pow)) / prev_pow;
        a -= dig * prev_pow;
        a += 9 * prev_pow;
        return {true, a};
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    long long mxw, mxp, a, b;
    cin >> mxw >> mxp >> a >> b;
    vector<pair<long long, long long>> ass(n);
    for (int i = 0; i < n; ++i) {
        int aa, bb;
        cin >> aa >> bb;
        ass[i] = {aa, bb};
    }
    vector<pair<long long, pair<int, int>>> vigods;   //
    for (int i = 0; i < n; ++i) {
        pair<bool, long long> res_wei = make_higher(ass[i].first);
        pair<bool, long long> res_pri = make_higher(ass[i].second);
        bool f1 = false, f2 = false;
        if (res_wei.second > mxw) {
            if (res_wei.first) {
//                f1 = true;
//                vigods.emplace_back(make_pair(100 * a * (res_wei.second - mxw), make_pair(i, 1)));
                vigods.emplace_back(make_pair((100 * a * (res_wei.second - mxw) - max(0LL, 100 * a * (ass[i].first - mxw))), make_pair(i, 1)));
            } else {
                vigods.emplace_back(make_pair(100 * a * (res_wei.second - mxw), make_pair(i, -1)));
            }
        }
        if (res_pri.second > mxp) {
            if (res_pri.first) {
//                f2 = true;
//                vigods.emplace_back(make_pair(b * ((res_pri.second - mxp)), make_pair(i, 2)));
                vigods.emplace_back(make_pair((b * ((res_pri.second - mxp)) - max(0ll, b * ((ass[i].second - mxp)))), make_pair(i, 2)));
            } else {
                vigods.emplace_back(make_pair(b * (res_pri.second - mxp), make_pair(i, -2)));
            }
        }
//        if (f1 && !f2) {
//            vigods.emplace_back(make_pair(100 * a * (res_wei.second - mxw), make_pair(i, 1)));
//        } else if (!f1 && f2) {
//            vigods.emplace_back(make_pair(b * ((res_pri.second - mxp)), make_pair(i, 2)));
//        } else if (f1 && f2) {
//            if ((100 * a * (res_wei.second - mxw) - max(0LL, 100 * a * (ass[i].first - mxw))) > (b * ((res_pri.second - mxp)) - max(0ll, b * ((ass[i].second - mxp))))) {
//                vigods.emplace_back(make_pair(100 * a * (res_wei.second - mxw), make_pair(i, 1)));
//            } else {
//                vigods.emplace_back(make_pair(b * ((res_pri.second - mxp)), make_pair(i, 2)));
//            }
//        }
    }
    sort(vigods.begin(), vigods.end());
    reverse(vigods.begin(), vigods.end());

    vector<bool> used = vector(n, false);
    vector<pair<long long, long long>> new_values(n);
    for (int i = 0; i < n; ++i) {
        new_values[i] = ass[i];
    }

    int cnt_taken = 0;
    for (int i = 0; i < vigods.size(); ++i) {
        if (vigods[i].second.second < 0) {
            used[vigods[i].second.first] = true;
        } else {
            if (used[vigods[i].second.first] || cnt_taken >= k) continue;
            used[vigods[i].second.first] = true;
            if (vigods[i].second.second == 1) {
                new_values[vigods[i].second.first] = {make_higher(ass[vigods[i].second.first].first).second, ass[vigods[i].second.first].second};
            } else {
                new_values[vigods[i].second.first] = {ass[vigods[i].second.first].first, make_higher(ass[vigods[i].second.first].second).second};
            }
            cnt_taken++;
        }
    }
    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        answer += max(0LL, (new_values[i].first - mxw) * a * 100);
        answer += max(0LL, ((new_values[i].second - mxp) * b));
        cout << (answer) / 100 << '.';
        if (answer % 100 < 10)
            cout << '0';
        cout << answer % 100 << '\n';
    }
    for (int i = 0; i < n; ++i) {
        cout << new_values[i].first << ' ' << new_values[i].second << '\n';
    }
}
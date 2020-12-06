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

int k, n;
vector<int> normal = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Date {
    int day = 1, month = 1, year = 1700;

    Date() = default;

    Date(int d, int m, int y) : day(d - 1), month(m - 1), year(y) {}

    explicit Date(const string &s) {
        year = stoi(s.substr(0, 4));
        month = stoi(s.substr(4, 2)) - 1;
        day = stoi(s.substr(6)) - 1;
    }

    Date next_day() const {
        Date nxt(day + 2, month + 1, year);
        if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
            normal[1]++;
        if (normal[month] == nxt.day) {
            nxt.month++;
            nxt.day = 0;
        }
        if (nxt.month == 12) {
            nxt.year++;
            nxt.month = 0;
        }
        if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
            normal[1]--;
        return nxt;
    }

    string to_string() const {
        return std::to_string(day + 1) + "/" + std::to_string(month + 1) + "/" + std::to_string(year);
    }

    bool operator==(const Date &oth) const {
        return tie(day, month, year) == tie(oth.day, oth.month, oth.year);
    }

    bool operator!=(const Date &oth) const {
        return tie(day, month, year) != tie(oth.day, oth.month, oth.year);
    }

    bool operator<(const Date &oth) const {
        return tie(day, month, year) < tie(oth.day, oth.month, oth.year);
    }
};

const int MAXN = 1.5e5 + 7;
int days[MAXN];
int days1[MAXN];
Date dates[MAXN];
map<Date, int> id;

int solve() {
    if (!(cin >> k >> n))
        return 1;
    Date start(1, 1, 1700), finish(31, 1, 2101);
    int pnt = 0;
    Date now = start;
    while (now != finish) {
        dates[pnt] = now;
        id[now] = pnt++;
        now = now.next_day();

    }
    dates[pnt] = now;
    id[finish] = pnt++;
    for (int i = 0; i < k; i++) {
        string a, b;
        cin >> a >> b;
        Date aa = Date(a), bb = Date(b);
        int l = id[aa], r = id[bb];
        while (l <= r)
            days[l++] = 1;
    }
    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        int l = id[Date(a)], r = id[Date(b)];
        while (l <= r)
            days1[l++] = 1;
    }
    int s = -1;
    int l = 0;
    bool was = false;
    for (int i = 0; i < pnt; i++) {
        if (days1[i] && !days[i]) {
            if (s == -1)
                s = i;
            l++;
        } else {
            if (l == 1) {
                cout << dates[s].to_string() << '\n';
                was = true;
            } else if (l > 1) {
                cout << dates[s].to_string() << " to " << dates[i - 1].to_string() << '\n';
                was = true;
            }
            s = -1;
            l = 0;
        }
    }
    if (!was)
        cout << "No new information\n";
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

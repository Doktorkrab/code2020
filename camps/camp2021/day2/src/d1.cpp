// coool, nlogn

#define _CRT_SECURE_NO_DEPRECATE

#include <algorithm>
#include <iostream>
#include <utility>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

const int nmax = 100001;

int x[nmax], y[nmax];
int n, m;
vector < pair < int, int > > a, b;
map < int, int > maxy, miny;

void solve() {
    for (int i = 0; i < n; ++i) {
        if (maxy.count(x[i]) == 0) maxy[x[i]] = y[i]; else
        if (maxy[x[i]] < y[i]) maxy[x[i]] = y[i];
        if (miny.count(x[i]) == 0) miny[x[i]] = y[i]; else
        if (miny[x[i]] > y[i]) miny[x[i]] = y[i];
    }
    sort(x, x + n);
    a.reserve(n);
    b.reserve(n);

    int cury = miny[x[0]];
    a.push_back(make_pair(x[0], cury));
    for (int i = 1; i < n; ++i) {
        if (miny[x[i]] < cury) {
            a.push_back(make_pair(x[i], cury));
            cury = miny[x[i]];
            a.push_back(make_pair(x[i], cury));
        }
    }

    cury = miny[x[n - 1]];
    b.push_back(make_pair(x[n - 1], cury));
    for (int i = n - 2; i >= 0; --i) {
        if (miny[x[i]] < cury) {
            b.push_back(make_pair(x[i], cury));
            cury = miny[x[i]];
            b.push_back(make_pair(x[i], cury));
        }
    }
    if (a.back() == b.back()) b.pop_back();
    a.insert(a.end(), b.rbegin(), b.rend());

    b.clear();
    cury = maxy[x[n - 1]];
    if (cury > a.back().second) b.push_back(make_pair(x[n - 1], cury));
    for (int i = n - 2; i >= 0; --i) {
        if (maxy[x[i]] > cury) {
            b.push_back(make_pair(x[i], cury));
            cury = maxy[x[i]];
            b.push_back(make_pair(x[i], cury));
        }
    }
    a.insert(a.end(), b.begin(), b.end());

    b.clear();
    cury = maxy[x[0]];
    if (cury > a[0].second) b.push_back(make_pair(x[0], cury));
    for (int i = 1; i < n; ++i) {
        if (maxy[x[i]] > cury) {
            b.push_back(make_pair(x[i], cury));
            cury = maxy[x[i]];
            b.push_back(make_pair(x[i], cury));
        }
    }
    a.insert(a.end(), b.rbegin(), b.rend());
}

void init() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &x[i], &y[i]);
    }
}

void writeanswer() {
    printf("%d\n", (int)a.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        printf("%d %d\n", a[i].first, a[i].second);
    }
}

int main() {

    init();
    solve();
    writeanswer();

    return 0;
}

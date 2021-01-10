#include <iostream>
#include <string>
#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>("n");
    const int MAX = 2e5;
    int t = MAX / n;
    auto coords = opt<std::string>("type");
    int border = 0;
    if (coords == "small") {
        border = 10;
    }
    if (coords == "medium") {
        border = 100;
    }
    if (coords == "large") {
        border = 1e9;
    }
    std::cout << t << '\n';
    for (int tt = 0; tt < t; tt++) {
        cout << n << '\n'
        for (int i = 0; i < n / 2; i++)
            cout << i << ' ' << i << '\n';
        for (int i = 0; i < n / 2; i++)
            cout << i << ' ' << border - i << '\n';
    }
    return 0;
}

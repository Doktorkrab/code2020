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
        int each_type = n / 4;
        cout << n << '\n';
        for (int i = 0; i < each_type; i++)
            cout << i << ' ' << each_type - i - 1 << '\n';
        for (int i = 0; i < each_type; i++)
            cout << i << ' ' << border - each_type + i + 1 << '\n';
        for (int i = 0; i < each_type; i++)
            cout << i + each_type + 2 << ' ' << i << '\n';
        for (int i = 0; i < each_type; i++)
            cout << i + each_type + 2 << ' ' << border - i << '\n';
    }
    return 0;
}

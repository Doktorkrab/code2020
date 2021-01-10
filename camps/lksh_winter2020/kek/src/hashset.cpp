#include <ctime>
#include <iostream>
#include <unordered_map>
using namespace std;

const int N = 5e4;

void insert_numbers(long long x) {
    for (int i = 1; i <= N; i++)
        cout << (1LL) * i * x << " \n"[i == N];
}

int main() {
    cout << N << '\n';
    insert_numbers(107897);
}
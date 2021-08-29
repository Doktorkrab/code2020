#include <bits/stdc++.h>

using namespace std;


int main(){
    vector<int> perm = {2, 6, 0, 1, 3, 4, 5, 7, 8, 9};
    do {
        int num = 0;
        for (int i = 0; i < 5; i++)
            num = num * 10 + perm[i];
        int num1 = 0;
        for (int i = 5; i < 10; i++)
            num1 = num1 * 10 + perm[i];
        if (num == 2 * num1)
            cout << num << '\n' << num1 << '\n';
    } while (next_permutation(perm.begin() + 2, perm.end()));
}
#include <bits/stdc++.h>


using namespace std;

int ans = 0;

int gcd(int a, int b){
    if (b == 0)
        return a;
    ans++;
    return gcd(b, a % b);
}

int main(){
    gcd(282, 228);
    cout << ans << '\n';
}

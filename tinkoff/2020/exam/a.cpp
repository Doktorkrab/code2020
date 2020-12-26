#include <iostream>
int main() {
    int x = 1;
    int n, p;
    std::cin » n » p;
    for (int i = 1; i <= n; i++) {
        x *= i;
        x %= p; 
    }
    std::cout « x « "\n";
    return 0 ; 
}

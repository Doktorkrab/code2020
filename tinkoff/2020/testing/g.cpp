#ifdef LOCAL
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#else
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#endif

#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;
using ll = long long;


#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()

unsigned SegMinSum(unsigned *a, unsigned *b, int n) {
    __m256i sum_avx = _mm256_set1_epi32(0);
    int i = 0;
    for (; i + 8 <= n; i += 8) {
        __m256i cur_block_a = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(a + i));
        __m256i cur_block_b = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(b + i));
        sum_avx = _mm256_add_epi32(sum_avx, _mm256_min_epi32(cur_block_a, cur_block_b));
    }
    unsigned sum = 0;
    for (; i < n; i++)
        sum += min(a[i], b[i]);
    auto *sums = (unsigned *) &sum_avx;
    for (i = 0; i < 8; i++)
        sum += sums[i];
    return sum;
}

#ifdef LOCAL

int main() {
    unsigned a[] = {TMAX(unsigned), 1};
    unsigned b[] = {TMAX(unsigned), 1};
    cout << SegMinSum(a, b, 2) << '\n';
}
#endif
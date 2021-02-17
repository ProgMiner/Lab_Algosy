#include <iostream>

#define TREE_SIZE (131072)

constexpr int soldiersLength = TREE_SIZE * 2 - 1;
unsigned int soldiers[soldiersLength];

template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}

void build(unsigned int n, unsigned int i = 0, unsigned int l = 0, unsigned int r = TREE_SIZE) {
    while (n > 0) {
        soldiers[i] = n;

        if (r - l <= 1) {
            return;
        }

        unsigned int m = (l + r) >> 1U;
        unsigned int leftN = min(n, m - l);
        build(leftN, (i << 1U) + 1, l, m);

        n -= leftN;
        i = (i << 1U) + 2;
        l = m;
    }
}

unsigned int findAndRemove(unsigned int n) {
    unsigned int i = 0, l = 0, r = TREE_SIZE;

    while (r - l > 1) {
        --soldiers[i];

        unsigned int m = (l + r) >> 1U;
        unsigned int leftN = soldiers[(i << 1U) + 1];
        if (leftN > n) {
            i = (i << 1U) + 1;
            r = m;
        } else {
            n -= leftN;
            i = (i << 1U) + 2;
            l = m;
        }
    }

    --soldiers[i];
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, k;
    std::cin >> n >> k;
    --k;

    build(n);
    for (unsigned int i = k; soldiers[0] > 1; i = (i + k) % soldiers[0]) {
        std::cout << findAndRemove(i) << ' ';
    }

    std::cout << findAndRemove(0);
    return 0;
}

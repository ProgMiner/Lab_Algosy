#include <iostream>

int main() {
    unsigned int T;
    std::cin >> T;

    while (T-- > 0) {
        unsigned int n, k;
        std::cin >> n >> k;

        register unsigned int r = n % k, m = (n - r) / k;
        register unsigned int a = r * (r - 1) / 2, b = (k - r) * (k - r - 1) / 2;
        std::cout << m * m * b + (m + 1) * (m + 1) * a + m * (m + 1) * (k * (k - 1) / 2 - a - b) << '\n';
    }

    return 0;
}

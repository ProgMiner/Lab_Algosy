#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;

    auto w = new unsigned int[n];
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> w[i];
    }

    unsigned int C = 10000000;
    unsigned long N = 1UL << (n - 1);
    for (unsigned long i = 0; i < N; ++i) {
        int c = -w[0];

        for (unsigned int j = 1, J = 1; j < n; ++j, J <<= 1U) {
            if (i & J) {
                c += w[j];
            } else {
                c -= w[j];
            }
        }

        if (c < 0) {
            c *= -1;
        }

        if (c < C) {
            C = c;
        }
    }

    std::cout << C;
    return 0;
}

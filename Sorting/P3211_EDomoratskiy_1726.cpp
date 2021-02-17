#include <algorithm>
#include <iostream>

unsigned long X[1000001];
unsigned long Y[1000001];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;

    auto x = new unsigned long long[n];
    auto y = new unsigned long long[n];

    if (n < 80000) {
        for (unsigned int i = 0; i < n; ++i) {
            std::cin >> x[i] >> y[i];
        }

        std::sort(x, x + n);
        std::sort(y, y + n);
    } else {
        unsigned minX = 1000000, maxX = 0, minY = 1000000, maxY = 0;

        for (unsigned int i = 0; i < n; ++i) {
            unsigned long tmp;

            std::cin >> tmp;
            ++X[tmp];

            if (tmp < minX) {
                minX = tmp;
            }

            if (tmp > maxX) {
                maxX = tmp;
            }

            std::cin >> tmp;
            ++Y[tmp];

            if (tmp < minY) {
                minY = tmp;
            }

            if (tmp > maxY) {
                maxY = tmp;
            }
        }

        for (unsigned int i = minX, j = 0; i < maxX + 1; ++i) {
            for (; X[i] > 0; --X[i], ++j) {
                x[j] = i;
            }
        }

        for (unsigned int i = minY, j = 0; i < maxY + 1; ++i) {
            for (; Y[i] > 0; --Y[i], ++j) {
                y[j] = i;
            }
        }
    }

    unsigned long long sum = 0;
    for (unsigned int i = 1; i < n; ++i) {
        sum += (x[i] - x[i - 1] + y[i] - y[i - 1]) * i * (n - i);
    }

    std::cout << 2 * sum / n / (n - 1);
    return 0;
}

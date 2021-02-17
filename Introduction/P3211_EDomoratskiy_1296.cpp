#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, p, c = 0, s = 0, m = 0, C;
    std::cin >> n;

    while (--n >= 0) {
        std::cin >> p;
        s += p;

        C = s - m;
        if (C > c) {
            c = C;
        }

        if (s < m) {
            m = s;
        }
    }

    std::cout << c;
    return 0;
}

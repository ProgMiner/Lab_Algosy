#include <iostream>

bool edges[100][100] {}, colors[100] {}, colored[100] {};

bool paint(unsigned int n, unsigned int i = 1, bool prevColor = true) {
    if (colored[i]) {
        return colors[i] != prevColor;
    }

    colored[i] = true;
    bool color = colors[i] = !prevColor;

    for (unsigned int node = 1; node <= n; ++node) {
        if (!edges[i][node]) {
            continue;
        }

        if (!paint(n, node, color)) {
            return false;
        }
    }

    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;

    unsigned int node;
    for (unsigned int i = 1; i <= n; ++i) {
        std::cin >> node;

        if (node == 0) {
            continue;
        }

        while (node > 0) {
            edges[i][node] = true;
            edges[node][i] = true;

            std::cin >> node;
        }
    }

    if (!paint(n)) {
        std::cout << "-1";
        return 0;
    }

    std::cout << std::noboolalpha;
    for (unsigned int i = 1; i <= n; ++i) {
        std::cout << colors[i];
    }

    return 0;
}

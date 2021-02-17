#include <algorithm>
#include <iostream>

unsigned int w[8];

int main() {
    std::cin >> w[0] >> w[1] >> w[2] >> w[3] >> w[4] >> w[5] >> w[6] >> w[7];

    if (w[0] + w[2] + w[5] + w[7] != w[1] + w[3] + w[4] + w[6]) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }

    while (w[0] != 0 && w[1] != 0 && w[2] != 0)

    return 0;
}

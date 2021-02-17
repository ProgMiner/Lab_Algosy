#include <functional>
#include <iostream>
#include <vector>
#include <queue>

struct Sign {

    int i, n;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int k;
    std::cin >> k;

    std::priority_queue<Sign, std::vector<Sign>, std::function<bool(const Sign &, const Sign &)>> signs(
        [] (const Sign & a, const Sign & b) {
            return a.n < b.n;
        }
    );

    for (int i = 0, j = 1; i < k; ++i, ++j) {
        short n;

        std::cin >> n;
        signs.push({j, n});
    }

    for (int prev = -1; !signs.empty(); ) {
        auto max = signs.top();
        signs.pop();

        if (max.i == prev && signs.size() > 1) {
            auto tmp = signs.top();
            signs.pop();
            signs.push(max);
            max = tmp;
        }

        std::cout << max.i << ' ';

        if (max.n > 1) {
            signs.push({max.i, max.n - 1});
        }

        prev = max.i;
    }

    return 0;
}

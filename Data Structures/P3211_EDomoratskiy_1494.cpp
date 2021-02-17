#include <iostream>

struct Interval {

    unsigned int l, r;
};

Interval ballsContainer[50001];
Interval * balls = ballsContainer;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    ++n;

    unsigned int time = 0, a;
    while (--n > 0) {
        std::cin >> a;

        if (a > time) {
            if (a > time + 1) {
                (++balls)->l = time + 1;
                balls->r = a - 1;
                time = a;
            } else {
                ++time;
            }
        } else {
            if (a != balls->r) {
                std::cout << "Cheater";
                return 0;
            }

            if (--balls->r < balls->l) {
                --balls;
            }
        }
    }

    std::cout << "Not a proof";
    return 0;
}

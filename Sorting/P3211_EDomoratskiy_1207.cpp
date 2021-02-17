#include <algorithm>
#include <iostream>

struct Point {

    unsigned int i;
    int x, y;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;

    unsigned int firstI = 0;
    auto points = new Point[n];
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
        points[i].i = i;

        if (points[i].x < points[firstI].x || (points[i].x == points[firstI].x && points[i].y < points[firstI].y)) {
            firstI = i;
        }
    }

    auto first = points[firstI];
    points[firstI] = points[0];
    points[0] = first;

    // for (unsigned int i = 0; i < n; ++i) {
    //     std::cout << points[i].i << ' ' << points[i].x << ' ' << points[i].y << '\n';
    // }

    auto angles = new double[n];
    for (unsigned int i = 1; i < n; ++i) {
        angles[points[i].i] = points[i].x - first.x != 0
                              ? (double) (points[i].y - first.y) / (points[i].x - first.x)
                              : 1000000000;
    }

    std::sort(points + 1, points + n, [&] (auto & a, auto & b) {
        return angles[a.i] < angles[b.i];
    });

    // for (unsigned int i = 0; i < n; ++i) {
    //     std::cout << points[i].i << ' ' << points[i].x << ' ' << points[i].y << ' ' << angles[points[i].i] << '\n';
    // }

    std::cout << points[0].i + 1 << ' ' << points[n / 2].i + 1;
    return 0;
}

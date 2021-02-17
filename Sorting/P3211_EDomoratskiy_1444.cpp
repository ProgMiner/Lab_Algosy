#include <algorithm>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

struct Point {

    unsigned int i;
    int x, y;
};

inline int area(const Point & a, const Point & b, const Point & c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool intersect_1(int a, int b, int c, int d) {
	if (a > b) std::swap (a, b);
	if (c > d) std::swap (c, d);
	return std::max(a, c) <= std::min(b, d);
}

bool intersect(const Point & a, const Point & b, const Point & c, const Point & d) {
	return intersect_1 (a.x, b.x, c.x, d.x)
		&& intersect_1 (a.y, b.y, c.y, d.y)
		&& area(a, b, c) * area(a, b, d) <= 0
		&& area(c, d, a) * area(c, d, b) <= 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;

    auto points = new Point[n];
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
        points[i].i = i;
    }

    auto angles = new double[n];
    auto distances = new unsigned int[n];
    for (unsigned int i = 1; i < n; ++i) {
        const int dx = points[i].x - points[0].x;
        const int dy = points[i].y - points[0].y;

        angles[i] = std::atan2(dy, dx);
        distances[i] = dx * dx + dy * dy;
    }

    std::sort(points + 1, points + n, [&] (const Point & a, const Point & b) {
        if (angles[a.i] == angles[b.i]) {
            return distances[a.i] < distances[b.i];
        }

        return angles[a.i] < angles[b.i];
    });

    unsigned int bad = 1;
    if (std::abs(angles[points[1].i] - angles[points[2].i]) == M_PI) {
        bad = 2;
    } else {
        for (unsigned int i = 3; i < n; ++i) {
            if (intersect(points[0], points[1], points[i - 1], points[i])) {
                bad = i;
                break;
            }
        }
    }

    std::cout << n << "\n1\n";
    for (unsigned int i = bad; i < n; ++i) {
        std::cout << points[i].i + 1 << '\n';
    }

    for (unsigned int i = 1; i < bad; ++i) {
        std::cout << points[i].i + 1 << '\n';
    }

    return 0;
}

#include <iostream>
#include <map>

using Line = std::map<unsigned int, unsigned int, std::greater<>>;

Line rows[30000] {}, cols[30000] {};

std::pair<Line::iterator, Line::iterator> split(Line & line, unsigned int x) {
    auto it = line.lower_bound(x);

    if (it == line.end() || it->second <= x) {
        return {line.end(), line.end()};
    }

    auto start = line.end(), end = it;
    if (it->second > x + 1) {
        start = line.insert({x + 1, it->second}).first;
    }

    if (it->first >= x) {
        line.erase(it);
        end = line.end();
    } else {
        it->second = x;
    }

    return {start, end};
}

inline bool isCollide(const Line & line, unsigned int x) {
    auto it = line.lower_bound(x);

    return it != line.end() && it->second > x;
}

inline void repairRow(const Line::iterator & it, unsigned int x) {
    if (it != rows[x].end() && it->second - it->first == 1) {
        if (isCollide(cols[it->first], x)) {
            rows[x].erase(it);
        }
    }
}

inline void repairCol(const Line::iterator & it, unsigned int y) {
    if (it != cols[y].end() && it->second - it->first == 1) {
        if (isCollide(rows[it->first], y)) {
            cols[y].erase(it);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int m, n, k;
    std::cin >> m >> n >> k;

    if (m == 1 && n == 1) {
        std::cout << 1 - k;
        return 0;
    }

    if (n > 1) {
        for (unsigned int i = 0; i < m; ++i) {
            rows[i][0] = n;
        }
    }

    if (m > 1) {
        for (unsigned int i = 0; i < n; ++i) {
            cols[i][0] = m;
        }
    }

    unsigned int x, y;
    for (unsigned int i = 0; i < k; ++i) {
        std::cin >> x >> y;
        --x; --y;

        auto rowIts = split(rows[x], y);
        repairRow(rowIts.first, x);
        repairRow(rowIts.second, x);

        auto colIts = split(cols[y], x);
        repairCol(colIts.first, y);
        repairCol(colIts.second, y);
    }

    unsigned int c = 0;
    for (unsigned int i = 0; i < m; ++i) {
        c += rows[i].size();
    }

    for (unsigned int i = 0; i < n; ++i) {
        c += cols[i].size();
    }

    std::cout << c;
    return 0;
}

#include <algorithm>
#include <iostream>
#include <string>

struct Char {

    char c;
    unsigned int i;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    --n;

    char c;
    Char s[100001];
    unsigned int sLength = 0;
    while (std::cin.get(c)) {
        if (sLength > 0 && (c == '\n' || c == '\r')) {
            break;
        } else if (isspace(c)) {
            continue;
        }

        s[sLength] = { c, sLength };
        ++sLength;
    }

    std::stable_sort(s, s + sLength, [] (const auto & a, const auto & b) {
        return a.c < b.c;
    });

    for (unsigned int i = 0, j = n; i < sLength; ++i, j = s[j].i) {
        std::cout << s[j].c;
    }

    return 0;
}

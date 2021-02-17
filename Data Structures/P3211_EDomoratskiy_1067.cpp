#include <iostream>
#include <string>
#include <set>

struct Directory {

    std::string name;
    std::set<Directory> content;
};

bool operator < (const Directory & a, const Directory & b) {
    return a.name < b.name;
}

void renderTree(const Directory & root, int offset = 0) {
    for (const auto & it : root.content) {
        for (int i = 0; i < offset; ++i) {
            std::cout << ' ';
        }

        std::cout << it.name << '\n';
        renderTree(it, offset + 1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    Directory root {"", std::set<Directory>()};
    for (int i = 0; i < n; ++i) {
        std::string path;
        std::cin >> path;

        int pos = 0;
        Directory * directory = &root;
        for (int j = 0; j <= path.size(); ++j) {
            if (j == path.size() || path[j] == '\\') {
                Directory current {
                    std::string(path, pos, j - pos),
                    std::set<Directory>()
                };

                auto it = directory->content.find(current);
                if (it == directory->content.end()) {
                    it = directory->content.insert(current).first;
                }

                directory = const_cast<Directory *>(&*it);
                pos = j + 1;
            }
        }
    }

    renderTree(root);
    return 0;
}

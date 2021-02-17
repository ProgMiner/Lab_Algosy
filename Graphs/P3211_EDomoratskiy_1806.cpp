#include <unordered_map>
#include <functional>
#include <iostream>
#include <string>
#include <queue>

#define INF 12499750000000

using NodeLength = std::pair<unsigned long long, unsigned int>;

extern std::string candidates[135];
extern void produceCandidates(const std::string & str) noexcept;

unsigned long long minLength[50001];
std::priority_queue<NodeLength, std::vector<NodeLength>, std::function<bool(const NodeLength &, const NodeLength &)>> lengths([] (const NodeLength & a, const NodeLength & b) {
    return a.first > b.first;
});
bool finalMinLength[50001] {};
unsigned int path[50001] {};

unsigned int n, weights[10];
std::unordered_map<std::string, unsigned int> nodes(5000);
std::string s[50001];

void dijkstra() noexcept {
    unsigned int node, newLength, weight;

    for (unsigned int i = 1; i < n; ++i) {
        minLength[i] = INF;
    }

    lengths.push({0, n});
    while (!lengths.empty()) {
        node = lengths.top().second;
        lengths.pop();

        finalMinLength[node] = true;
        if (node == 1) {
            return;
        }

        produceCandidates(s[node]);
        for (const auto & candidate : candidates) {
            auto it = nodes.find(candidate);

            if (it == nodes.end()) {
                continue;
            }

            unsigned int end = it->second;
            if (!finalMinLength[end]) {
                unsigned int prefix = 0;

                for (unsigned int k = 0; k < 9; ++k) {
                    if (s[node][k] != candidate[k]) {
                        break;
                    }

                    ++prefix;
                }

                weight = weights[prefix];
                newLength = minLength[node] + weight;
                if (minLength[end] > newLength) {
                    lengths.push({newLength, end});
                    minLength[end] = newLength;
                    path[end] = node;
                }
            }
        }
    }
}

int main() noexcept {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> weights[0]
             >> weights[1] >> weights[2] >> weights[3]
             >> weights[4] >> weights[5] >> weights[6]
             >> weights[7] >> weights[8] >> weights[9];

    for (unsigned int i = 1; i <= n; ++i) {
        std::cin >> s[i];
        nodes.insert({s[i], i});
    }

    dijkstra();
    if (minLength[1] == INF) {
        std::cout << "-1\n";
        return 0;
    }

    std::cout << minLength[1] << '\n';

    unsigned int resultLength = 1;
    for (unsigned int i = 1; i < n; i = path[i]) {
        resultLength++;
    }

    std::cout << resultLength << '\n';
    for (unsigned int i = 1; i < n; i = path[i]) {
        std::cout << i << ' ';
    }

    std::cout << n << '\n';
    return 0;
}

std::string candidates[135] {
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          ",
    "          ", "          ", "          ", "          ", "          "
};

void produceCandidates(const std::string & str) noexcept {
    unsigned int index = 0;

    for (unsigned int i = 0; i < 10; ++i) {
        for (char c = '0'; c < '0' + 10; ++c) {
            if (c == str[i]) {
                continue;
            }

            for (unsigned int k = 0; k < 10; ++k) {
                if (k == i) {
                    candidates[index][k] = c;
                } else {
                    candidates[index][k] = str[k];
                }
            }

            ++index;
        }
    }

    for (unsigned int i = 0; i < 10; ++i) {
        for (unsigned int j = i + 1; j < 10; ++j) {
            for (unsigned int k = 0; k < 10; ++k) {
                if (k == i) {
                    candidates[index][k] = str[j];
                } else if (k == j) {
                    candidates[index][k] = str[i];
                } else {
                    candidates[index][k] = str[k];
                }
            }

            ++index;
        }
    }
}

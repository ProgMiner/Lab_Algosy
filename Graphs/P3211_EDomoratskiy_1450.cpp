#include <iostream>

struct Edge {

    Edge * prev;
    unsigned int end, weight;
};

Edge edgeBuffer[124750] {};
Edge * edgeBufferPointer = edgeBuffer;

Edge * edges[501] {};
unsigned long long sum[501] {};
bool visited[501] {};
unsigned int f;

unsigned long long findMaxSum(unsigned int s) {
    if (visited[s]) {
        return sum[s];
    }

    unsigned long long max = 0;
    for (Edge * edge = edges[s]; edge != nullptr; edge = edge->prev) {
        unsigned long long acc = 0;

        if (edge->end != f) {
            acc = findMaxSum(edge->end);

            if (acc == 0) {
                continue;
            }
        }

        acc += edge->weight;
        if (max < acc) {
            max = acc;
        }
    }

    visited[s] = true;
    return sum[s] = max;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;

    unsigned int a, b, c;
    for (unsigned int i = 0; i < m; ++i) {
        std::cin >> a >> b >> c;
        edges[a] = new(edgeBufferPointer++) Edge {edges[a], b, c};
    }

    unsigned int s;
    std::cin >> s >> f;

    unsigned long long result = findMaxSum(s);

    if (result == 0) {
        std::cout << "No solution\n";
    } else {
        std::cout << result << '\n';
    }

    return 0;
}

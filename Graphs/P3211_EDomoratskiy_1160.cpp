#include <functional>
#include <iostream>
#include <queue>

struct Edge {

    Edge * prev;
    unsigned int start, end, weight;
};

Edge edges[30000] {};
Edge * lastEdge = edges;

bool visited[1001] {};
Edge * edgesByNode[1001] {};
std::priority_queue<Edge *, std::vector<Edge *>, std::function<bool(Edge *, Edge*)>> candidates(
    [](Edge * a, Edge * b) {
        return (a->weight == b->weight) ? a->end > b->end : a->weight > b->weight;
    }
);

Edge * result[30000] {};
Edge ** lastResult = result;
unsigned int resultMax = 0;

void build() {
    for (unsigned int i = 1; ; ) {
        visited[i] = true;

        for (Edge * edge = edgesByNode[i]; edge != nullptr; edge = edge->prev) {
            if (!visited[edge->end]) {
                candidates.push(edge);
            }
        }

        Edge * candidate;
        do {
            if (candidates.empty()) {
                return;
            }

            candidate = candidates.top();
            candidates.pop();
        } while (visited[candidate->end]);

        if (resultMax < candidate->weight) {
            resultMax = candidate->weight;
        }

        *(lastResult++) = candidate;
        i = candidate->end;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;

    unsigned int a, b, c;
    for (unsigned int i = 0; i < m; ++i) {
        std::cin >> a >> b >> c;
        edgesByNode[a] = new(lastEdge++) Edge {edgesByNode[a], a, b, c};
        edgesByNode[b] = new(lastEdge++) Edge {edgesByNode[b], b, a, c};
    }

    build();
    std::cout << resultMax << '\n' << lastResult - result;
    for (Edge ** edge = result; edge != lastResult; ++edge) {
        std::cout << '\n' << (*edge)->start << ' ' << (*edge)->end;
    }

    return 0;
}

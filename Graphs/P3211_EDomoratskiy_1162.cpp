#include <iostream>

struct Edge {

    Edge * prev;
    unsigned int end;
    float rate, commission;
};

Edge edges[200] {};
Edge * lastEdge = edges;

Edge * edgesByNode[101] {};
float currencyBalance[101] {};

bool hasProfit(float balance, unsigned int currency) {
    if (balance <= 0) {
        return false;
    }

    if (currencyBalance[currency] != 0) {
        return balance > currencyBalance[currency];
    }

    currencyBalance[currency] = balance;
    for (Edge * edge = edgesByNode[currency]; edge != nullptr; edge = edge->prev) {
        if (hasProfit((balance - edge->commission) * edge->rate, edge->end)) {
            return true;
        }
    }

    currencyBalance[currency] = 0;
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    float v;
    unsigned int n, m, s;
    std::cin >> n >> m >> s >> v;

    unsigned int a, b;
    float rab, cab, rba, cba;
    for (unsigned int i = 0; i < m; ++i) {
        std::cin >> a >> b >> rab >> cab >> rba >> cba;
        edgesByNode[a] = new(lastEdge++) Edge {edgesByNode[a], b, rab, cab};
        edgesByNode[b] = new(lastEdge++) Edge {edgesByNode[b], a, rba, cba};
    }

    if (hasProfit(v, s)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}

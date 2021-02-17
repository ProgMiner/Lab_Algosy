#include <iostream>

enum Type {

    HOLE, RIGHT_DOWN, LEFT_DOWN, LEFT_UP, RIGHT_UP
};

struct Tile {

    Type type;
    unsigned int x, y, offset;
};

int main() {
    unsigned int n;
    std::cin >> n;

    auto x = new unsigned int[n + 1], y = new unsigned int[n + 1];
    std::cin >> y[n] >> x[n];

    --x[n];
    --y[n];
    for (unsigned int i = n; i > 0; --i) {
        x[i - 1] = x[i] / 2;
        y[i - 1] = y[i] / 2;
    }

    unsigned int tilesSize = 1;
    auto tiles = new Tile[1] {{HOLE, 0, 0, 0}};
    for (unsigned int k = 0; k < n; ++k) {
        unsigned int newTilesSize = (tilesSize - 1) * 4 + 2;
        auto newTiles = new Tile[newTilesSize] {};

        while (tilesSize-- > 0) {
            const auto & tile = tiles[tilesSize];
            unsigned int oX = tile.x * 2, oY = tile.y * 2, oO = (tile.offset - 1) * 4 + 2;

            switch (tile.type) {
                case HOLE: {
                    unsigned int X = x[k + 1], Y = y[k + 1];
                    newTiles[0] = {HOLE, X, Y, 0};

                    if (oX == X && oY == Y) {
                        newTiles[1] = {LEFT_UP, oX + 1, oY + 1, 1};
                    } else if (oX < X && oY == Y) {
                        newTiles[1] = {RIGHT_UP, oX, oY + 1, 1};
                    } else if (oX < X && oY < Y) {
                        newTiles[1] = {RIGHT_DOWN, oX, oY, 1};
                    } else if (oX == X && oY < Y) {
                        newTiles[1] = {LEFT_DOWN, oX + 1, oY, 1};
                    }
                    break;
                }

                case RIGHT_DOWN:
                    newTiles[oO] = {RIGHT_DOWN, oX, oY, oO};
                    newTiles[oO + 1] = {RIGHT_DOWN, oX + 1, oY + 1, oO + 1};
                    newTiles[oO + 2] = {LEFT_DOWN, oX + 3, oY, oO + 2};
                    newTiles[oO + 3] = {RIGHT_UP, oX, oY + 3, oO + 3};
                    break;

                case LEFT_DOWN:
                    newTiles[oO] = {LEFT_DOWN, oX + 1, oY, oO};
                    newTiles[oO + 1] = {LEFT_DOWN, oX, oY + 1, oO + 1};
                    newTiles[oO + 2] = {RIGHT_DOWN, oX - 2, oY, oO + 2};
                    newTiles[oO + 3] = {LEFT_UP, oX + 1, oY + 3, oO + 3};
                    break;

                case LEFT_UP:
                    newTiles[oO] = {LEFT_UP, oX + 1, oY + 1, oO};
                    newTiles[oO + 1] = {LEFT_UP, oX, oY, oO + 1};
                    newTiles[oO + 2] = {RIGHT_UP, oX - 2, oY + 1, oO + 2};
                    newTiles[oO + 3] = {LEFT_DOWN, oX + 1, oY - 2, oO + 3};
                    break;

                case RIGHT_UP:
                    newTiles[oO] = {RIGHT_UP, oX, oY + 1, oO};
                    newTiles[oO + 1] = {RIGHT_UP, oX + 1, oY, oO + 1};
                    newTiles[oO + 2] = {RIGHT_DOWN, oX, oY - 2, oO + 2};
                    newTiles[oO + 3] = {LEFT_UP, oX + 3, oY + 1, oO + 3};
                    break;
            }
        }

        delete[] tiles;
        tiles = newTiles;
        tilesSize = newTilesSize;
    }

    unsigned int N = 1U << n;
    auto m = new unsigned int[N * N];
    while (tilesSize-- > 0) {
        const auto & tile = tiles[tilesSize];
        unsigned int i = tile.x + tile.y * N;

        switch (tile.type) {
            case HOLE:
                m[i] = tile.offset;
                break;

            case RIGHT_DOWN:
                m[i] = tile.offset;
                m[i + 1] = tile.offset;
                m[i + N] = tile.offset;
                break;

            case LEFT_DOWN:
                m[i] = tile.offset;
                m[i - 1] = tile.offset;
                m[i + N] = tile.offset;
                break;

            case LEFT_UP:
                m[i] = tile.offset;
                m[i - 1] = tile.offset;
                m[i - N] = tile.offset;
                break;

            case RIGHT_UP:
                m[i] = tile.offset;
                m[i + 1] = tile.offset;
                m[i - N] = tile.offset;
                break;
        }
    }

    for (unsigned int i = 0, k = 0; i < N; ++i) {
        for (unsigned int j = 0; j < N; ++j, ++k) {
            std::cout << m[k] << ' ';
        }

        std::cout << '\n';
    }

    return 0;
}

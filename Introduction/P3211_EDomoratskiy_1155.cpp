#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <sstream>

std::ostringstream buf;
unsigned int w[8];

void remove() {
    unsigned int c;

    do {
        c = 0;

        if (w[0] > 0 && w[1] > 0) {
            buf << "AB-\n";
            --w[0];
            --w[1];
            ++c;
        }

        if (w[1] > 0 && w[2] > 0) {
            buf << "BC-\n";
            --w[1];
            --w[2];
            ++c;
        }

        if (w[2] > 0 && w[3] > 0) {
            buf << "CD-\n";
            --w[2];
            --w[3];
            ++c;
        }

        if (w[0] > 0 && w[3] > 0) {
            buf << "AD-\n";
            --w[0];
            --w[3];
            ++c;
        }

        if (w[0] > 0 && w[4] > 0) {
            buf << "AE-\n";
            --w[0];
            --w[4];
            ++c;
        }

        if (w[1] > 0 && w[5] > 0) {
            buf << "BF-\n";
            --w[1];
            --w[5];
            ++c;
        }

        if (w[2] > 0 && w[6] > 0) {
            buf << "CG-\n";
            --w[2];
            --w[6];
            ++c;
        }

        if (w[3] > 0 && w[7] > 0) {
            buf << "DH-\n";
            --w[3];
            --w[7];
            ++c;
        }

        if (w[4] > 0 && w[5] > 0) {
            buf << "EF-\n";
            --w[4];
            --w[5];
            ++c;
        }

        if (w[5] > 0 && w[6] > 0) {
            buf << "FG-\n";
            --w[5];
            --w[6];
            ++c;
        }

        if (w[6] > 0 && w[7] > 0) {
            buf << "GH-\n";
            --w[6];
            --w[7];
            ++c;
        }

        if (w[4] > 0 && w[7] > 0) {
            buf << "EH-\n";
            --w[4];
            --w[7];
            ++c;
        }
    } while (c > 0);
}

void addAndRemove() {
    unsigned int P[12], p[12];

    for (unsigned int i = 0; i < 12; ++i) {
        P[i] = i;
        p[i] = 0;
    }

    if (w[0] > 0 || w[6] > 0) {
        ++p[1];
        ++p[2];
        ++p[5];
        ++p[7];
        ++p[8];
        ++p[11];
    }

    if (w[1] > 0 || w[7] > 0) {
        ++p[2];
        ++p[3];
        ++p[4];
        ++p[6];
        ++p[8];
        ++p[9];
    }

    if (w[2] > 0 || w[4] > 0) {
        ++p[0];
        ++p[3];
        ++p[5];
        ++p[7];
        ++p[9];
        ++p[10];
    }

    if (w[3] > 0 || w[5] > 0) {
        ++p[0];
        ++p[1];
        ++p[4];
        ++p[6];
        ++p[10];
        ++p[11];
    }

    std::sort(P, P + 12, [&] (unsigned int a, unsigned int b) {
        return p[a] > p[b];
    });

    switch (P[0]) {
        case 0:
            buf << "AB+\n";
            ++w[0];
            ++w[1];

            if (w[3] > 0) {
                buf << "AD-\n";
                --w[0];
                --w[3];
            } else if (w[4] > 0) {
                buf << "AE-\n";
                --w[0];
                --w[4];
            }

            if (w[2] > 0) {
                buf << "BC-\n";
                --w[1];
                --w[2];
            } else if (w[5] > 0) {
                buf << "BF-\n";
                --w[1];
                --w[5];
            }
            break;

        case 1:
            buf << "BC+\n";
            ++w[1];
            ++w[2];

            if (w[0] > 0) {
                buf << "AB-\n";
                --w[0];
                --w[1];
            } else if (w[5] > 0) {
                buf << "BF-\n";
                --w[1];
                --w[5];
            }

            if (w[3] > 0) {
                buf << "CD-\n";
                --w[2];
                --w[3];
            } else if (w[6] > 0) {
                buf << "CG-\n";
                --w[2];
                --w[6];
            }
            break;

        case 2:
            buf << "CD+\n";
            ++w[2];
            ++w[3];

            if (w[1] > 0) {
                buf << "BC-\n";
                --w[1];
                --w[2];
            } else if (w[6] > 0) {
                buf << "CG-\n";
                --w[2];
                --w[6];
            }

            if (w[0] > 0) {
                buf << "AD-\n";
                --w[0];
                --w[3];
            } else if (w[7] > 0) {
                buf << "DH-\n";
                --w[3];
                --w[7];
            }
            break;

        case 3:
            buf << "AD+\n";
            ++w[0];
            ++w[3];

            if (w[1] > 0) {
                buf << "AB-\n";
                --w[0];
                --w[1];
            } else if (w[4] > 0) {
                buf << "AE-\n";
                --w[0];
                --w[4];
            }

            if (w[2] > 0) {
                buf << "CD-\n";
                --w[2];
                --w[3];
            } else if (w[7] > 0) {
                buf << "DH-\n";
                --w[3];
                --w[7];
            }
            break;

        case 4:
            buf << "AE+\n";
            ++w[0];
            ++w[4];

            if (w[1] > 0) {
                buf << "AB-\n";
                --w[0];
                --w[1];
            } else if (w[3] > 0) {
                buf << "AD-\n";
                --w[0];
                --w[3];
            }

            if (w[5] > 0) {
                buf << "EF-\n";
                --w[4];
                --w[5];
            } else if (w[7] > 0) {
                buf << "EH-\n";
                --w[4];
                --w[7];
            }
            break;

        case 5:
            buf << "BF+\n";
            ++w[1];
            ++w[5];

            if (w[0] > 0) {
                buf << "AB-\n";
                --w[0];
                --w[1];
            } else if (w[2] > 0) {
                buf << "BC-\n";
                --w[1];
                --w[2];
            }

            if (w[4] > 0) {
                buf << "EF-\n";
                --w[4];
                --w[5];
            } else if (w[6] > 0) {
                buf << "FG-\n";
                --w[5];
                --w[6];
            }
            break;

        case 6:
            buf << "CG+\n";
            ++w[2];
            ++w[6];

            if (w[1] > 0) {
                buf << "BC-\n";
                --w[1];
                --w[2];
            } else if (w[3] > 0) {
                buf << "CD-\n";
                --w[2];
                --w[3];
            }

            if (w[5] > 0) {
                buf << "FG-\n";
                --w[5];
                --w[6];
            } else if (w[7] > 0) {
                buf << "GH-\n";
                --w[6];
                --w[7];
            }
            break;

        case 7:
            buf << "DH+\n";
            ++w[3];
            ++w[7];

            if (w[0] > 0) {
                buf << "AD-\n";
                --w[0];
                --w[3];
            } else if (w[2] > 0) {
                buf << "CD-\n";
                --w[2];
                --w[3];
            }

            if (w[4] > 0) {
                buf << "EH-\n";
                --w[4];
                --w[7];
            } else if (w[6] > 0) {
                buf << "GH-\n";
                --w[6];
                --w[7];
            }
            break;

        case 8:
            buf << "EF+\n";
            ++w[4];
            ++w[5];

            if (w[0] > 0) {
                buf << "AE-\n";
                --w[0];
                --w[4];
            } else if (w[7] > 0) {
                buf << "EH-\n";
                --w[4];
                --w[7];
            }

            if (w[1] > 0) {
                buf << "BF-\n";
                --w[1];
                --w[5];
            } else if (w[6] > 0) {
                buf << "FG-\n";
                --w[5];
                --w[6];
            }
            break;

        case 9:
            buf << "FG+\n";
            ++w[5];
            ++w[6];

            if (w[1] > 0) {
                buf << "BF-\n";
                --w[1];
                --w[5];
            } else if (w[4] > 0) {
                buf << "EF-\n";
                --w[4];
                --w[5];
            }

            if (w[2] > 0) {
                buf << "CG-\n";
                --w[2];
                --w[6];
            } else if (w[7] > 0) {
                buf << "GH-\n";
                --w[6];
                --w[7];
            }
            break;

        case 10:
            buf << "GH+\n";
            ++w[6];
            ++w[7];

            if (w[2] > 0) {
                buf << "CG-\n";
                --w[2];
                --w[6];
            } else if (w[5] > 0) {
                buf << "FG-\n";
                --w[5];
                --w[6];
            }

            if (w[3] > 0) {
                buf << "DH-\n";
                --w[3];
                --w[7];
            } else if (w[4] > 0) {
                buf << "EH-\n";
                --w[4];
                --w[7];
            }
            break;

        case 11:
            buf << "EH+\n";
            ++w[4];
            ++w[7];

            if (w[0] > 0) {
                buf << "AE-\n";
                --w[0];
                --w[4];
            } else if (w[5] > 0) {
                buf << "EF-\n";
                --w[4];
                --w[5];
            }

            if (w[3] > 0) {
                buf << "DH-\n";
                --w[3];
                --w[7];
            } else if (w[6] > 0) {
                buf << "GH-\n";
                --w[6];
                --w[7];
            }
            break;
    }
}

int main() {
    std::cin >> w[0] >> w[1] >> w[2] >> w[3] >> w[4] >> w[5] >> w[6] >> w[7];
    remove();

    std::unordered_set<unsigned int> D;
    while (true) {
        unsigned int c = 0, d = 0;

        for (unsigned int W : w) {
            if (W > 0) {
                ++c;
            }

            if (W == 1) {
                d = (d | 1U);
            }

            d <<= 1U;
        }

        if (c == 0) {
            break;
        }

        if (c == 1 || D.find(d) != D.end()) {
            std::cout << "IMPOSSIBLE";
            return 0;
        }

        if (d > 0) {
            D.insert(d);
        }

        addAndRemove();
    }

    std::cout << buf.str();
    return 0;
}

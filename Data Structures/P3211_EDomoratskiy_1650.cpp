#include <unordered_map>
#include <iostream>
#include <map>
#include <set>

using Volumes = std::map<unsigned long long, std::set<std::string>, std::greater<>>;
using Cities = std::unordered_map<std::string, unsigned long long>;
using Answer = std::map<std::string, unsigned int>;

inline void updateCityVolume(Cities & cities, Volumes & volumes, const std::string & city, unsigned long long volume) {
    auto & cityVolume = cities[city];

    auto cityVolumeIt = volumes.find(cityVolume);
    if (cityVolumeIt != volumes.end()) {
        if (cityVolumeIt->second.size() > 1) {
            cityVolumeIt->second.erase(city);
        } else {
            volumes.erase(cityVolumeIt);
        }
    }

    cityVolume += volume;
    volumes[cityVolume].insert(city);
}

inline void updateAnswer(const Volumes & volumes, Answer & answer, unsigned int days) {
    if (days == 0) {
        return;
    }

    auto maxCity = volumes.begin();
    if (maxCity->second.size() == 1) {
        answer[*maxCity->second.begin()] += days;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m, k;
    std::cin >> n;

    Cities cities;
    std::unordered_map<std::string, std::pair<std::string, unsigned long long>> billioners;
    for (unsigned int i = 0; i < n; ++i) {
        std::string name, city;
        unsigned long long volume;
        std::cin >> name >> city >> volume;

        billioners[name] = {city, volume};
        cities[city] += volume;
    }

    Volumes volumes;
    for (auto & city : cities) {
        volumes[city.second].insert(city.first);
    }

    std::cin >> m >> k;

    Answer answer;
    unsigned int prevDay = 0, day;
    for (unsigned int i = 0; i < k; ++i, prevDay = day) {
        std::string name, city;
        std::cin >> day >> name >> city;

        updateAnswer(volumes, answer, day - prevDay);

        auto & billioner = billioners[name];
        updateCityVolume(cities, volumes, billioner.first, -billioner.second);
        updateCityVolume(cities, volumes, city, billioner.second);
        billioner.first = city;
    }

    updateAnswer(volumes, answer, m - prevDay);
    for (auto & top : answer) {
        std::cout << top.first << ' ' << top.second << '\n';
    }

    return 0;
}

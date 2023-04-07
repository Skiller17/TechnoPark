#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "ActorTitles.h"
#include "NamesOfTitles.h"

void NamesOfTitles::SearchRuLocalizedTitles(const std::string &file) {//Смотрим есть ли у фильма русскоязычное название
    std::string localizedTitles;
    std::string title;
    std::vector<std::string> ruLocalizedTitles{};
    std::string ruLanguage = "RU";
    std::string suhhLanguage = "SUHH";
    std::ifstream inputFile(file);

    while (getline(inputFile, localizedTitles)) {

        for (int i = 0; i < nonAdultMovie.size(); ++i) {
            title = nonAdultMovie[i];

            if (localizedTitles.find(title) != -1 &&
                (localizedTitles.find(ruLanguage) != -1 || localizedTitles.find(suhhLanguage) != -1)) {
                ruLocalizedTitles.push_back(title);
            }
        }
    }
    inputFile.close();
    SortRuTitlesAndSearchNoRuTitles(file, ruLocalizedTitles);
}

void NamesOfTitles::SortRuTitlesAndSearchNoRuTitles(const std::string &file, std::vector<std::string> &ruLocalizedTitles) {
    std::vector<std::string> noRuLocalizedTitles{};
    int k = 0;

    std::sort(ruLocalizedTitles.begin(), ruLocalizedTitles.end());
    ruLocalizedTitles.erase(std::unique(ruLocalizedTitles.begin(), ruLocalizedTitles.end()),
                            ruLocalizedTitles.end());

    for (int i = 0; i < nonAdultMovie.size(); i++) {

        for (int j = 0; j < ruLocalizedTitles.size(); j++) {

            if (nonAdultMovie[i] != ruLocalizedTitles[j]) {
                k++;
            }

            if (k == ruLocalizedTitles.size()) {
                noRuLocalizedTitles.push_back(nonAdultMovie[i]);
                k = 0;
            }
        }
        k = 0;
    }

    InputLocalizedNames(file, ruLocalizedTitles, noRuLocalizedTitles);
}

void NamesOfTitles::InputLocalizedNames(const std::string &file, std::vector<std::string> &ruLocalizedTitles, std::vector<std::string> &noRuLocalizedTitles) {
    std::string localizedTitles;
    std::ifstream inputFile(file);

    while (getline(inputFile, localizedTitles)) {

        SearchRuTitlesNames(localizedTitles, ruLocalizedTitles);
        SearchNoRuTitlesNames(localizedTitles, noRuLocalizedTitles);
    }

    OutputAndSortRuNames();
    OutputNoRuNames();
}

void NamesOfTitles::SearchRuTitlesNames(const std::string &localizedTitles, std::vector<std::string> &ruLocalizedTitles) {
    std::vector<std::string> informationAboutRuLocalizedTitle{};
    std::string title;
    std::string ruLanguage = "RU";
    std::string suhhLanguage = "SUHH";
    int nameTitle = 2;

    for (int i = 0; i < ruLocalizedTitles.size(); ++i) {
        title = ruLocalizedTitles[i];

        if (localizedTitles.find(title) != -1 &&
            (localizedTitles.find(ruLanguage) != -1 || localizedTitles.find(suhhLanguage) != -1)) {
            informationAboutRuLocalizedTitle = Split(localizedTitles, '\t');
            ruTitlesNames.push_back(informationAboutRuLocalizedTitle[nameTitle]);
        }
    }
}

void NamesOfTitles::SearchNoRuTitlesNames(const std::string &localizedTitles, std::vector<std::string> &noRuLocalizedTitles) {
    std::vector<std::string> informationAboutNoRuLocalizedTitles{};
    std::string title;
    std::string original = "original";
    int nameTitle = 2;

    for (int i = 0; i < noRuLocalizedTitles.size(); ++i) {
        title = noRuLocalizedTitles[i];

        if (localizedTitles.find(title) != -1 && localizedTitles.find(original) != -1) {
            informationAboutNoRuLocalizedTitles = Split(localizedTitles, '\t');
            noRuTitlesNames.push_back(informationAboutNoRuLocalizedTitles[nameTitle]);
        }
    }
}
void NamesOfTitles::OutputAndSortRuNames() {
    std::sort(ruTitlesNames.begin(), ruTitlesNames.end());
    ruTitlesNames.erase(std::unique(ruTitlesNames.begin(), ruTitlesNames.end()), ruTitlesNames.end());

    for (int i = 0; i < ruTitlesNames.size(); ++i) {
        std::cout << ruTitlesNames[i] << std::endl;
    }
}

void NamesOfTitles::OutputNoRuNames() {
    for (int i = 0; i < noRuTitlesNames.size(); ++i) {
        std::cout << noRuTitlesNames[i] << std::endl;
    }
}
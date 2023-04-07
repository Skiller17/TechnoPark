#pragma once
#include <iostream>
#include <vector>

class NamesOfTitles {
public:
    void SearchRuLocalizedTitles(const std::string &file);

    void SortRuTitlesAndSearchNoRuTitles(const std::string &file, std::vector<std::string> &ruLocalizedTitles);

    void InputLocalizedNames(const std::string &file, std::vector<std::string> &ruLocalizedTitles, std::vector<std::string> &noRuLocalizedTitles);

    void SearchRuTitlesNames(const std::string &localizedTitles, std::vector<std::string> &ruLocalizedTitles);

    void SearchNoRuTitlesNames(const std::string &localizedTitles, std::vector<std::string> &noRuLocalizedTitles);

    void OutputAndSortRuNames();

    void OutputNoRuNames();

    std::vector<std::string> nonAdultMovie{};
private:
    std::vector<std::string> ruTitlesNames{};
    std::vector<std::string> noRuTitlesNames{};
};
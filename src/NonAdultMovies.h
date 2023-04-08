#pragma once
#include <iostream>
#include <vector>

class NonAdultMovies {
public:
    void InputInformationAboutTitles(const std::string &file);

    void SearchNonAdultMovies(const std::string &informationAboutTitle);

    std::vector<std::string> idMovie{};
    std::vector<std::string> nonAdultMovie{};
};


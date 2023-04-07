#pragma once
#include <iostream>
#include <vector>

std::vector<std::string> Split(const std::string &str, char separator);

class ActorTitles {
public:
    void InputInformationAboutActor(const std::string &file);

    void SearchTitles(const std::string &informationAboutActor);

    std::string actor;
    std::vector<std::string> idMovie{};
};


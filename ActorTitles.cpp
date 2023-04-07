#include <iostream>
#include <fstream>
#include <vector>
#include "ActorTitles.h"

std::vector<std::string>
Split(const std::string &str, char separator) {
    std::vector<std::string> result{};
    std::string curr = " ";

    for (int i = 0; i < str.length(); ++i) {

        if (str[i] != separator) {
            curr.push_back(str[i]);
        }

        else {
            result.push_back(curr);
            curr = " ";
        }
    }

    result.push_back(curr);
    return result;
}


void ActorTitles::InputInformationAboutActor(const std::string &file) {//Находим в каких произведениях был актёр
    std::ifstream inputFile(file);
    std::string informationAboutActor;

    while (getline(inputFile, informationAboutActor)) {
        SearchTitles(informationAboutActor);
    }
}

void ActorTitles::SearchTitles(const std::string &informationAboutActor) {
    std::vector<std::string> Titles{};
    int firstTitle = 0;
    int actorTitles = 5;

    if (informationAboutActor.find(actor) != -1) {
        Titles = Split(informationAboutActor, '\t');
        idMovie = Split(Titles[actorTitles], ',');
        idMovie[firstTitle] = idMovie[firstTitle].substr(1, '\n');
    }
}
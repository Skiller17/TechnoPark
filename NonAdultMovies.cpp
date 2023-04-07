#include <iostream>
#include <fstream>
#include <vector>
#include "ActorTitles.h"
#include "NonAdultMovies.h"

void NonAdultMovies::InputInformationAboutTitles(const std::string &file) {
    std::string informationAboutTitle;
    std::ifstream inputFile(file);

    while (getline(inputFile, informationAboutTitle)) {
        SearchNonAdultMovies(informationAboutTitle);
    }
}

void NonAdultMovies::SearchNonAdultMovies(const std::string &informationAboutTitle) {
    std::string title;
    std::vector<std::string> movies{};
    std::string movie = "movie";
    int isAdult = 4;
    std::string nonAdultStatus = " 0";

    for (int i = 0; i < idMovie.size(); ++i) {
        title = idMovie[i];
        title = title.substr(1, '\n');

        if (informationAboutTitle.find(movie) != -1 && informationAboutTitle.find(title) != -1) {
            movies = Split(informationAboutTitle, '\t');

            if (movies[isAdult] == nonAdultStatus) {
                nonAdultMovie.push_back(title);
            }
        }
    }
}

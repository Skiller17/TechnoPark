#include <iostream>
#include "ActorTitles.h"
#include "NonAdultMovies.h"
#include "NamesOfTitles.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <name> <file1> <file2> <file3>";
    }

    ActorTitles actorTitles;
    std::string act = argv[1];
    actorTitles.actor = act;
    actorTitles.InputInformationAboutActor(argv[2]);

    NonAdultMovies nonAdultMovies;
    nonAdultMovies.idMovie = actorTitles.idMovie;
    nonAdultMovies.InputInformationAboutTitles(argv[3]);

    NamesOfTitles namesOfTitles;
    namesOfTitles.nonAdultMovie = nonAdultMovies.nonAdultMovie;
    namesOfTitles.SearchRuLocalizedTitles(argv[4]);
    return 0;
}

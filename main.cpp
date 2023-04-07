#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>


std::vector<std::string>
Split(const std::string &str, char separator) {
    std::vector<std::string> result{};
    std::string curr = " ";

    for (int i = 0; i < str.length(); ++i) {

        if (str[i] != separator) {
            curr.push_back(str[i]);
        } else {
            result.push_back(curr);
            curr = " ";
        }
    }
    result.push_back(curr);
    return result;
}

class NamesOfTitles {
public:
    void InputInformationAboutActor(const std::string &file) {//Находим в каких произведениях был актёр
        std::ifstream inputFile(file);
        std::string informationAboutActor;

        while (getline(inputFile, informationAboutActor)) {
            SearchTitles(informationAboutActor);
        }
    }

    void SearchTitles(const std::string &informationAboutActor) {
        std::vector<std::string> Titles{};
        int firstTitle = 0;
        int actorTitles = 5;

        if (informationAboutActor.find(actor) != -1) {
            Titles = Split(informationAboutActor, '\t');
            idMovie = Split(Titles[actorTitles], ',');
            idMovie[firstTitle] = idMovie[firstTitle].substr(1, '\n');
        }
    }

    void InputInformationAboutTitles(const std::string &file) {
        std::string informationAboutTitle;
        std::ifstream inputFile(file);

        while (getline(inputFile, informationAboutTitle)) {
            SearchNonAdultMovies(informationAboutTitle);
        }
    }

    void SearchNonAdultMovies(const std::string &informationAboutTitle) {
        std::string title;
        std::string movie = "movie";
        std::vector<std::string> movies{};
        int isAdult = 4;

        for (int i = 0; i < idMovie.size(); ++i) {
            title = idMovie[i];
            title = title.substr(1, '\n');

            if (informationAboutTitle.find(movie) != -1 && informationAboutTitle.find(title) != -1) {
                movies = Split(informationAboutTitle, '\t');

                if (movies[isAdult] == " 0") {
                    nonAdultMovie.push_back(title);
                }
            }
        }
    }

    void SearchRuLocalizedTitles(const std::string &file) {//Смотрим есть ли у фильма русскоязычное название
        std::string localizedTitles;
        std::string title;
        std::vector<std::string> ruLocalizedTitles{};
        std::string titleNoRU;
        std::ifstream inputFile(file);

        while (getline(inputFile, localizedTitles)) {

            for (int i = 0; i < nonAdultMovie.size(); ++i) {
                title = nonAdultMovie[i];

                if (localizedTitles.find(title) != -1 &&
                    (localizedTitles.find("RU") != -1 || localizedTitles.find("SUHH") != -1)) {
                    ruLocalizedTitles.push_back(title);
                }
            }
        }
        inputFile.close();
        SortRuTitlesAndSearchNoRuTitles(file, ruLocalizedTitles);
    }

    void SortRuTitlesAndSearchNoRuTitles(const std::string &file, std::vector<std::string> &ruLocalizedTitles) {
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

    void InputLocalizedNames(const std::string &file, std::vector<std::string> &ruLocalizedTitles, std::vector<std::string> &noRuLocalizedTitles) {
        std::string localizedTitles;
        std::ifstream inputFile(file);

        while (getline(inputFile, localizedTitles)) {

            SearchRuTitlesNames(localizedTitles, ruLocalizedTitles);
            SearchNoRuTitlesNames(localizedTitles, noRuLocalizedTitles);
        }

        OutputAndSortRuNames();
        OutputNoRuNames();
    }

    void SearchRuTitlesNames(const std::string &localizedTitles, std::vector<std::string> &ruLocalizedTitles) {
        std::vector<std::string> informationAboutRuLocalizedTitle{};
        std::string title;

        for (int i = 0; i < ruLocalizedTitles.size(); ++i) {
            title = ruLocalizedTitles[i];

            if (localizedTitles.find(title) != -1 &&
                (localizedTitles.find("RU") != -1 || localizedTitles.find("SUHH") != -1)) {
                informationAboutRuLocalizedTitle = Split(localizedTitles, '\t');
                ruTitlesNames.push_back(informationAboutRuLocalizedTitle[2]);
            }
        }
    }

    void SearchNoRuTitlesNames(const std::string &localizedTitles, std::vector<std::string> &noRuLocalizedTitles) {
        std::vector<std::string> informationAboutNoRuLocalizedTitles{};
        std::string title;

        for (int i = 0; i < noRuLocalizedTitles.size(); ++i) {
            title = noRuLocalizedTitles[i];

            if (localizedTitles.find(title) != -1 && localizedTitles.find("original") != -1) {
                informationAboutNoRuLocalizedTitles = Split(localizedTitles, '\t');
                noRuTitlesNames.push_back(informationAboutNoRuLocalizedTitles[2]);
            }
        }
    }
    void OutputAndSortRuNames() {
        std::sort(ruTitlesNames.begin(), ruTitlesNames.end());
        ruTitlesNames.erase(std::unique(ruTitlesNames.begin(), ruTitlesNames.end()), ruTitlesNames.end());

        for (int i = 0; i < ruTitlesNames.size(); ++i) {
            std::cout << ruTitlesNames[i] << std::endl;
        }
    }

    void OutputNoRuNames() {
        for (int i = 0; i < noRuTitlesNames.size(); ++i) {
            std::cout << noRuTitlesNames[i] << std::endl;
        }
    }

    std::string actor;
private:
    std::vector<std::string> idMovie{};
    std::vector<std::string> nonAdultMovie{};
    std::vector<std::string> ruTitlesNames{};
    std::vector<std::string> noRuTitlesNames{};
};

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <name> <file1> <file2> <file3>";
        return 1;
    }
    NamesOfTitles namesOfTitles;
    std::string act = argv[1];
    namesOfTitles.actor = act;

    namesOfTitles.InputInformationAboutActor(argv[2]);
    namesOfTitles.InputInformationAboutTitles(argv[3]);
    namesOfTitles.SearchRuLocalizedTitles(argv[4]);
    return 0;
}

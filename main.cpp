#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


std::vector<std::string>
Split(const std::string str, char sep) { //Функция, убирающая разделители и создающая вектор из частей строки
    std::vector<std::string> result;
    std::string curr = " ";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != sep) {
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
    void Titles(const std::string &file)  //Находим в каких произведениях был актёр
    {
        std::ifstream inputFile(file);
        std::string actorInfo;
        std::vector<std::string> Titles;
        while (getline(inputFile, actorInfo)) {
            if (actorInfo.find(actor) != -1) {
                Titles = Split(actorInfo, '\t');
                idMovie = Split(Titles[5], ',');
                idMovie[0] = idMovie[0].substr(1, '\n');
            }
        }
        inputFile.close();
    }

    void Movies(const std::string &file)  //Смотрим фильмы не для взрослых этого актёра
    {
        std::string titlesInfo;
        std::vector<std::string> movies;
        std::string title;
        std::ifstream inputFile(file);
        std::string movie = "movie";
        while (getline(inputFile, titlesInfo)) {
            for (int i = 0; i < idMovie.size(); i++) {
                title = idMovie[i];
                title = title.substr(1, '\n');
                if (titlesInfo.find(movie) != -1 && titlesInfo.find(title) != -1) {
                    movies = Split(titlesInfo, '\t');
                    if (movies[4] == " 0") {
                        nonAdultMovie.push_back(title);
                    }
                }
            }
        }
        inputFile.close();
    }

    std::string Local(const std::string &file) //Смотрим есть ли у фильма русскоязычное название
    {
        std::string nameInfo;
        std::string title;
        int k = 0;
        std::vector<std::string> vectRU;
        std::vector<std::string> vectNoRU;
        std::vector<std::string> nameRU;
        std::vector<std::string> name;
        std::vector<std::string> ListOfRU;
        std::vector<std::string> ListOfNoRU;
        std::string titleNoRU;
        nameRU.reserve(8);
        name.reserve(8);
        std::ifstream inputFile(file);
        while (getline(inputFile, nameInfo)) {
            for (int i = 0; i < nonAdultMovie.size(); i++) {
                title = nonAdultMovie[i];
                if (nameInfo.find(title) != -1 && (nameInfo.find("RU") != -1 || nameInfo.find("SUHH") != -1)) {
                    vectRU.push_back(title);
                }
            }
        }
        std::sort(vectRU.begin(), vectRU.end());
        vectRU.erase(std::unique(vectRU.begin(), vectRU.end()), vectRU.end());
        for (int i = 0; i < nonAdultMovie.size(); i++) {
            for (int j = 0; j < vectRU.size(); j++) {
                if (nonAdultMovie[i] != vectRU[j]) {
                    k++;
                }
                if (k == vectRU.size()) {
                    vectNoRU.push_back(nonAdultMovie[i]);
                    k = 0;
                }
            }
            k = 0;
        }
        inputFile.close();
        inputFile.open(file);
        while (getline(inputFile, nameInfo)) {
            for (int i = 0; i < vectRU.size(); i++) {
                title = vectRU[i];
                if (nameInfo.find(title) != -1 && (nameInfo.find("RU") != -1 || nameInfo.find("SUHH") != -1)) {
                    nameRU = Split(nameInfo, '\t');
                    ListOfRU.push_back(nameRU[2]);
                }

            }
            for (int i = 0; i < vectNoRU.size(); i++) {
                title = vectNoRU[i];
                if (nameInfo.find(title) != -1 && nameInfo.find("original") != -1) {
                    name = Split(nameInfo, '\t');
                    ListOfNoRU.push_back(name[2]);
                }
            }
        }
        inputFile.close();
        std::sort(ListOfRU.begin(), ListOfRU.end());
        ListOfRU.erase(std::unique(ListOfRU.begin(), ListOfRU.end()), ListOfRU.end());
        for (int i = 0; i < ListOfRU.size(); i++) {
            std::cout << ListOfRU[i] << std::endl;
        }
        for (int i = 0; i < ListOfNoRU.size(); i++) {
            std::cout << ListOfNoRU[i] << std::endl;
        }
    }
    std::vector<std::string> idMovie;
    std::vector<std::string> nonAdultMovie;
    std::string actor;
};

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <name> <file1> <file2> <file3>" << std::endl;
        return 1;
    }
    NamesOfTitles namesOfTitles;
    std::string act = argv[1];
    namesOfTitles.actor = act;

    namesOfTitles.Titles(argv[2]);
    namesOfTitles.Movies(argv[3]);
    namesOfTitles.Local(argv[4]);
    return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


std::vector<std::string> Split(const std::string str, char sep) { //Функция, убирающая разделители и создающая вектор из частей строки
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

class Solution {

public:
    std::vector <std::string> id_mov;
    std::vector <std::string> non_adult_mov;
    std::string actor;

    void Titles(const std::string &f1)  //Находим в каких произведениях был актёр
    {
        std::ifstream input_file(f1);
        std::string actorInfo;
        std::vector <std::string> listOfTitles;
        while(getline(input_file, actorInfo)) {
            if(actorInfo.find(actor, 0)!=-1) {
                listOfTitles = Split(actorInfo,'\t');
                id_mov = Split(listOfTitles[5],',');
                id_mov[0] = id_mov[0].substr(1,'\n');
            }
        }
        input_file.close();
    }

    void Movies(const std::string &f2)  //Смотрим фильмы не для взрослых этого актёра
    {
        std::string titlesInfo;
        std::vector<std::string> movies;
        std::string title;
        std::ifstream input_file(f2);
        while (getline(input_file, titlesInfo)) {
            for (int i = 0; i < id_mov.size(); i++) {
                title = id_mov[i];
                title = title.substr(1,'\n');
                if (titlesInfo.find("movie", 0) != -1 && titlesInfo.find(title, 0) != -1) {
                    movies = Split(titlesInfo,'\t');
                    if(movies[4]==" 0") {
                        non_adult_mov.push_back(title);
                    }
                }
            }
        }
        input_file.close();
    }

    std::string Local(const std::string &f3) //Смотрим есть ли у фильма русскоязычное название
    {
        std::string nameInfo;
        std::string title;
        int k = 0;
        int t = 0;
        std::vector<std::string> vectRU;
        std::vector<std::string> vectNoRU;
        std::vector<std::string> nameRU;
        std::vector<std::string> name;
        std::vector<std::string> ListOfRU;
        std::vector<std::string> ListOfNoRU;
        std::string titleNoRU;
        nameRU.reserve(8);
        name.reserve(8);
        std::ifstream input_file(f3);
        while (getline(input_file, nameInfo)) {
            for (int i = 0; i < non_adult_mov.size(); i++) {
                title = non_adult_mov[i];
                if (nameInfo.find(title, 0) != -1 && (nameInfo.find("RU", 0) != -1 || nameInfo.find("SUHH", 0) != -1)) {
                    vectRU.push_back(title);
                }
            }
        }
        std::sort(vectRU.begin(), vectRU.end());
        vectRU.erase(std::unique(vectRU.begin(), vectRU.end()), vectRU.end());
        for (int i = 0; i < non_adult_mov.size(); i++) {
            for (int j = 0; j < vectRU.size(); j++) {
                if (non_adult_mov[i] != vectRU[j]) {
                    k++;
                }
                if (k == vectRU.size()) {
                    vectNoRU.push_back(non_adult_mov[i]);
                    k = 0;
                }
            }
            k = 0;
        }
        input_file.close();
        input_file.open(f3);
        while (getline(input_file, nameInfo)) {
            for (int i = 0; i < vectRU.size(); i++) {
                title = vectRU[i];
                if (nameInfo.find(title, 0) != -1 && (nameInfo.find("RU", 0) != -1 || nameInfo.find("SUHH", 0) != -1)) {
                    nameRU = Split(nameInfo, '\t');
                    ListOfRU.push_back(nameRU[2]);
                }

            }
            for (int i = 0; i < vectNoRU.size(); i++) {
                title = vectNoRU[i];
                if (nameInfo.find(title, 0) != -1 && nameInfo.find("original", 0) != -1) {
                    name = Split(nameInfo, '\t');
                    ListOfNoRU.push_back(name[2]);
                }
            }
        }
        input_file.close();
        std::sort(ListOfRU.begin(), ListOfRU.end());
        ListOfRU.erase(std::unique(ListOfRU.begin(), ListOfRU.end()), ListOfRU.end());
        for(int i=0; i<ListOfRU.size();i++){
            std::cout << ListOfRU[i] << std::endl;
        }
        for(int i=0; i<ListOfNoRU.size();i++){
            std::cout << ListOfNoRU[i] << std::endl;
        }
    }
};

int main(int argc, char *argv[]){
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <name> <file1> <file2> <file3>" << std::endl;
        return 1;
    }
    Solution solution;
    std::string act = argv[1];
    solution.actor = act;

    solution.Titles(argv[2]);
    solution.Movies(argv[3]);
    solution.Local(argv[4]);
    return 0;
}

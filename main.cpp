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
    }

    std::string Local(const std::string &f3) //Смотрим есть ли у фильма русскоязычное название
    {
        std::string nameInfo;
        std::string title;
        int k = 0;
        std::vector<std::string> vectRU;
        std::vector<std::string> vectNoRU;
        std::vector<std::string> nameRU;
        std::vector<std::string> name;
        std::string titleNoRU;
//        nameRU.reserve(8);
//        name.reserve(8);
        std::ifstream input_file(f3);
        while (getline(input_file, nameInfo)) {
            for (int i = 0; i < non_adult_mov.size(); i++) {
                title = non_adult_mov[i];
                if (nameInfo.find(title, 0) != -1 && (nameInfo.find("RU", 0) != -1 || nameInfo.find("ru", 0) != -1)) {
                    vectRU.push_back(title);
                }
            }
        }
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

        while (getline(input_file, nameInfo)) {
            for (int i = 0; i < vectRU.size(); i++) {
                title = vectRU[i];
                if (nameInfo.find(title, 0) != -1 && (nameInfo.find("RU", 0) != -1 || nameInfo.find("ru", 0) != -1)) {
                    nameRU = Split(nameInfo, '\t');
                    std::cout << nameRU[2] << std::endl;
                }

            }
            for (int i = 0; i < non_adult_mov.size(); i++) {
                title = non_adult_mov[i];
                if (nameInfo.find(title, 0) != -1 && nameInfo.find("original", 0) != -1) {
                    name = Split(nameInfo, '\t');
                    std::cout << name[2] << std::endl;
                }
            }
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


////Дальше будут мои размышления насчёт методов

/*int main(int argc, char* argv[]) { //разработка метода Titles
    std::ifstream f1("name.basics.tsv");
    std::string stroka;
    std::vector <std::string> word;
    std::vector <std::string> titles;
    std::string actor;
    actor = "Mark Ayzenberg";
    while(getline(f1, stroka)) {
        if(stroka.find(actor, 0)!=-1) {
            word = Split(stroka,'\t');
            titles = Split(word[5],',');
            titles[0] = titles[0].substr(1,'\n');
            for(int i=0; i < 4; i++){
                std::cout << titles[i] << std::endl;
            }
        }
    }
}*/
/*int main(int argc, char *argv[]) { //разработка метода Movies
    std::ifstream f2("title.basics.tsv");
    std::string stroka2;
    std::vector<std::string> vect = {"tt2860568", "tt0101495", "tt0265499", "tt0000869"};
    std::vector<std::string> vect3;
    std::string title;
    std::vector<std::string> vect2;
    while (getline(f2, stroka2)) {
        for (int i = 0; i < vect.size(); i++) {
            title = vect[i];
            vect3 = Split(stroka2,'\t');
            if (stroka2.find("movie", 0) != -1 && stroka2.find(title, 0) != -1) {
                if(vect3[4]==" 0") {
                    vect2.push_back(title);
                }
            }
        }
    }

    for (int i = 0; i < vect2.size(); i++) {
        std::cout << vect2[i] << std::endl;
    }
}*/

/*int main(int argc, char* argv[]) { //разработка метода Local
    std::string stroka3;
    std::string title;
    std::vector<std::string> vect = {"tt2860568", "tt0101495", "tt0265499", "tt0000869"};
    std::vector<std::string> vectRU;
    std::vector<std::string> vectNoRU;
    std::vector<std::string> nameRU;
    std::vector<std::string> name;
    std::string titleNoRU;
    int k = 0;
    nameRU.reserve(8);
    name.reserve(8);
    std::ifstream f3;
    f3.open("title.akas.tsv");
    while (getline(f3, stroka3)) {
        for (int i = 0; i < vect.size(); i++) {
            title = vect[i];
            if (stroka3.find(title, 0) != -1 && (stroka3.find("RU", 0) != -1 || stroka3.find("ru", 0) != -1)) {
                vectRU.push_back(title);
            }
        }
    }
    for(int i=0;i<vect.size();i++){
        for(int j=0;j<vectRU.size();j++){
            if(vect[i]!=vectRU[j]){
                k++;
            }
            if(k==vectRU.size()){
                vectNoRU.push_back(vect[i]);
                k = 0;
            }
        }
        k = 0;
    }
    for(int i = 0;i<vectNoRU.size();i++) {
        std::cout << vectNoRU[i] << std::endl;
    }
    f3.close();*/
    /*f3.open("title.akas.tsv");
    while (getline(f3, stroka3)) {
        for (int i = 0; i < vectRU.size(); i++) {
            title = vectRU[i];
            if (stroka3.find(title, 0) != -1 && (stroka3.find("RU", 0) != -1 || stroka3.find("ru", 0) != -1)) {
                nameRU = Split(stroka3, '\t');
                std::cout << nameRU[2] << std::endl;
            }

        }
        for (int i = 0; i < vect.size(); i++) {
            title = vect[i];
            if (stroka3.find(title, 0) != -1 && stroka3.find("original", 0) != -1) {
                name = Split(stroka3, '\t');
                std::cout << name[2] << std::endl;
            }
        }
    }
    f3.close();
}*/

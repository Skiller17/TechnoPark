#include <iostream>
#include <vector>

std::vector<std::string> Split(const std::string &str, char separator) {
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

class Conveyor {
public:
    void Parser(const std::string &str) {
        commands = Split(str, " | ");
    }

private:
    std::vector<std::string> commands;
};


#include <iostream>
#include <fstream>
#include <regex>


std::string
Replacer(const std::string &inputStr, const std::string &initialSubstring, const std::string &replacementSubstring) {
    std::regex rx(initialSubstring.c_str());
    return std::regex_replace(inputStr, rx, replacementSubstring);
}

class IOperation {
public:
    virtual void ProcessLine(const std::string &str);

    virtual void HandleEndOfInput() = 0;

    virtual void SetNextOperation(IOperation *nextOp) = 0;
};

class CatOperation : public IOperation {
public:
    void ProcessLine(const std::string &str) override {
        std::string fileStrings;

        inputString = str;

        fileStrings = FileOutput();

        outputString = str + '\n' + fileStrings;

        if (nextOperation == nullptr) {
            HandleEndOfInput();
        } else {
            nextOperation->ProcessLine(outputString);
        }
    }

    std::string FileOutput() {
        std::string str;
        std::string glueStr = "";
        std::ifstream inputFile(fileName);

        while (getline(inputFile, str)) {
            glueStr = glueStr + '\n' + str;
        }
        return glueStr;
    }

    void HandleEndOfInput() override {
        std::cout << outputString << std::endl;
    }

    void SetNextOperation(IOperation *nextOp) override {
        nextOperation = nextOp;
    }

    std::string fileName;
private:
    IOperation *nextOperation;
    std::string inputString;
    std::string outputString;
};

class EchoOperation : public IOperation {
public:
    void ProcessLine(const std::string &str) override {
        if (nextOperation == nullptr) {
            HandleEndOfInput();
        } else {
            nextOperation->ProcessLine(argument);
        }
    }

    void HandleEndOfInput() override {
        std::cout << argument << std::endl;
    }

    void SetNextOperation(IOperation *nextOp) override {
        nextOperation = nextOp;
    }

    std::string argument;
private:
    IOperation *nextOperation;
};

class ReplaceOperation : public IOperation {
public:
    void ProcessLine(const std::string &str) override {

        if (str.find(initialSubstring)) {
            output = Replacer(str, initialSubstring, replacementSubstring);

            if(nextOperation == nullptr) {
                HandleEndOfInput();
            } else {
                nextOperation->ProcessLine(output);
            }
        } else {
            output = str;

            if(nextOperation == nullptr) {
                HandleEndOfInput();
            } else {
                nextOperation->ProcessLine(str);
            }
        }
    }

    void HandleEndOfInput() override {
        std::cout << output << std::endl;
    }

    void SetNextOperation(IOperation *nextOp) override {
        nextOperation = nextOp;
    }

    std::string initialSubstring;
    std::string replacementSubstring;
private:
    IOperation *nextOperation;
    std::string output;
};
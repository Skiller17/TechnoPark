#include <iostream>
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
        inputString = str;
        nextOperation->ProcessLine(str);
    }

    void HandleEndOfInput() override {
        std::cout << inputString << std::endl;
    }

    void SetNextOperation(IOperation *nextOp) override {
        nextOperation = nextOp;
    }

private:
    IOperation *nextOperation;
    std::string inputString;
};

class EchoOperation : public IOperation {
public:
    void ProcessLine(const std::string &str) override {
        nextOperation->ProcessLine(str);
        output = str;
    }

    void HandleEndOfInput() override {
        std::cout << output << std::endl;
    }

    void SetNextOperation(IOperation *nextOp) override {
        nextOperation = nextOp;
    }

private:
    IOperation *nextOperation;
    std::string output;
};

class ReplaceOperation : public IOperation {
public:
    void ProcessLine(const std::string &str) override {

        if (str.find(initialSubstring)) {
            output = Replacer(str, initialSubstring, replacementSubstring);
            nextOperation->ProcessLine(output);
        } else {
            output = str;
            nextOperation->ProcessLine(str);
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
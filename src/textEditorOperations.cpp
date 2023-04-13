#include <fstream>
#include <iostream>

class IOperation {
public:
    virtual void ProcessLine(const std::string &str);

    virtual void HandleEndOfInput() = 0;

    virtual void SetNextOperation(IOperation *nextOp) = 0;
};

class CatOperation : public IOperation {
public:
    void ProcessLine(const std::string &str) {
        file = str;

        nextOperation->ProcessLine(file);
    }

    void HandleEndOfInput() {
        std::ifstream inputFile(file);
        std::string outputStrings;

        while(getline(inputFile, outputStrings)) {
            std::cout << outputStrings << std::endl;
        }
    }

    void SetNextOperation(IOperation *nextOp) {
        if (nextOp == nullptr) {
            HandleEndOfInput();
        }
        nextOperation = nextOp;
    }

private:
    IOperation *nextOperation;
    std::string output;
    std::string &file;
};

class EchoOperation : public IOperation {
public:
    void ProcessLine(const std::string &str) {
        nextOperation->ProcessLine(str);
        output = str;
    }

    void HandleEndOfInput() {
        std::cout << output << std::endl;
    }

    void SetNextOperation(IOperation *nextOp) {
        if(nextOp == nullptr) {
            HandleEndOfInput();
        }
        nextOperation = nextOp;
    }
private:
    IOperation *nextOperation;
    std::string output;
};

class ReplaceOperation : public IOperation {
public:
    void ProcessLine(const std::string &str) {}

    void HandleEndOfInput() {}

    void SetNextOperation(IOperation *nextOp) {}
};
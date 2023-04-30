#include <iostream>
#include <vector>
#include "textEditorOperations.cpp"

std::vector<std::string> Split(const std::string &str, char separator) {
    std::vector<std::string> result{};
    std::string curr = "";

    for (int i = 0; i < str.length(); ++i) {

        if (str[i] != separator) {
            curr.push_back(str[i]);
        } else if (curr != "") {
            result.push_back(curr);
            curr = "";
        }
    }
    if (curr != "") {
        result.push_back(curr);
    }
    return result;
}

class Conveyor {
public:
    void Parser(const std::string &str) {
        commands = Split(str, '|');
        for (int i = 0; i < commands.size(); i++) {
            CommandsAndNames(commands[i]);
        }

    }

    void CommandsAndNames(const std::string &str) {
        std::vector<std::string> command;
        int nameCommand = 0;
        int inputCommand = 1;

        command = Split(str, ' ');

        commandName.push_back(command[nameCommand]);

        commandInput.push_back(command[inputCommand]);
    }

    void OutputNames() {
        for (int i = 0; i < commandName.size(); i++) {
            std::cout << commandName[i] << std::endl;
        }
    }

    void OutputInputs() {
        for (int i = 0; i < commandInput.size(); i++) {
            std::cout << commandInput[i] << std::endl;
        }
    }

    void ConveyorAlgorithm(const std::string &str) {
        std::string echoCommand = "echo";
        std::string catCommand = "cat";
        std::string replaceCommand = "replace";

    }

private:
    std::vector<std::string> commands;
    std::vector<std::string> commandName;
    std::vector<std::string> commandInput;
    int startCommand = 0;
    int commandCounter = 0;
};

/////

if(commandName[startCommand] == echo) {
EchoCommand echoCommand;

echoCommand.
AccomplishmentEchoCommand(echoCommand, str
);
}

else if(commandName[startCommand] == cat) {
CatCommand catCommand;

catCommand.
AccomplishmentCatCommand(catCommand, str
);
}

else if(commandName[startCommand] == replace) {
ReplaceCommand replaceCommand;

replaceCommand.
AccomplishmentReplaceCommand(replaceCommand, str
);
}

else std::cout << "Invalid input";

void AccomplishmentEchoCommand(IOperation *ioperation, cosnt std::string &str) {

    if (commandCounter < commandName.size()) {

        if (commandName[commandCounter + 1] == echo) {
            EchoCommand echo;
            SetNextOpearation(echo);
            ProcessLine(str);
            AccomplishmentEchoCommand(echo, str);
        } else if (commandName[commandCounter + 1] == cat) {
            CatCommand cat;
            SetNextOpearation(CatCommand
            cat);
            ProcessLine(str);
            AccomplishmentCatCommand(cat, str);
        } else if (commandName[commandCounter + 1] == replace) {
            ReplaceCommand replace;
            SetNextOpearation(ReplaceCommand
            replace);
            ProcessLine(str);
            AccomplishmentReplaceCommand(replace, str);
        }
    } else {
        SetNextOpearation(nullptr);
        ProcessLine(str);
        HandleOutput();
    }
}

void AccomplishmentCatCommand(IOperation *ioperation, const std::string &str) {


    if (commandCounter < commandName.size()) {

        if (commandName[commandCounter + 1] == echo) {

        } else if (commandName[commandCounter + 1] == cat) {

        } else if (commandName[commandCounter + 1] == replace) {

        }
    }
}

void AccomplishmentReplaceCommand(IOperation *ioperation, const std::string &str) {


    if (commandCounter < commandName.size()) {

        if (commandName[commandCounter + 1] == echo) {

        } else if (commandName[commandCounter + 1] == cat) {

        } else if (commandName[commandCounter + 1] == replace) {

        }
    }
}

if(commandName[commandCounter] == cat) {

    while(getline(dadsd, "file_1.txt")) {

    }

}
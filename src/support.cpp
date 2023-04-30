#include <iostream>
#include <vector>
#include "textEditorOperations.cpp"

std::vector<std::string> Split(const std::string &str, char separator) {
    std::vector<std::string> result{};
    std::string curr;

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
        std::string replaceCommand = "replace";
        int nameCommand = 0;
        int inputCommand = 1;

        command = Split(str, ' ');

        commandName.push_back(command[nameCommand]);

        if (command[nameCommand] == replaceCommand) {
            commandInput.push_back(command[inputCommand] + " " + command[inputCommand + 1]);
        } else {
            commandInput.push_back(command[inputCommand]);
        }
        ConveyorAlgorithm();
    }

    static IOperation *GetOperationFromName(std::string &operationName, std::string &arguments) {
        std::string echoCommand = "echo";
        std::string catCommand = "cat";

        if (operationName == echoCommand) {
            auto *echoOperation = new EchoOperation;

            echoOperation->argument = arguments;
            return echoOperation;
        } else if (operationName == catCommand) {
            auto *catOperation =  new CatOperation;

            catOperation->fileName = arguments;
            return catOperation;
        } else {
            auto *replaceOperation = new ReplaceOperation;
            std::vector<std::string> replaceStrings;

            replaceStrings = Split(arguments, ' ');
            replaceOperation->initialSubstring = replaceStrings[0];
            replaceOperation->replacementSubstring = replaceStrings[1];
            return replaceOperation;
        }
    }

    void ConveyorAlgorithm() {
        int startCommand = 0;

        IOperation *prevOperation = GetOperationFromName(commandName[startCommand], commandInput[startCommand]);
        IOperation *firstOperation = prevOperation;

        for (int i = 1; i < commandName.size(); i++) {
            IOperation *iOperation = GetOperationFromName(commandName[i], commandInput[i]);
            prevOperation->SetNextOperation(iOperation);
            prevOperation = iOperation;
        }

        firstOperation->ProcessLine("");
    }

private:
    std::vector<std::string> commands;
    std::vector<std::string> commandName;
    std::vector<std::string> commandInput;
};
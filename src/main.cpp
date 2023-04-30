#include <iostream>
#include "support.cpp"

int main() {
    Conveyor conveyor;
    conveyor.Parser("echo 1 | cat file_1.txt | cat file_2.txt");
    conveyor.OutputNames();
    conveyor.OutputInputs();
}

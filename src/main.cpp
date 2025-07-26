// src/main.cpp
#include <iostream>
#include "Database.h"
#include "Parser.h"

int main() {
    Database db;
    Parser parser(db);
    std::string line;

    std::cout << "In-Memory Hamza DB Shell. Type 'exit' to quit.\n";
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line) || line == "exit") break;
        try {
            parser.parseAndExecute(line);
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << "\n";
        }
    }
    return 0;
}

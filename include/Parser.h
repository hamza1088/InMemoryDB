// include/Parser.h
#pragma once
#include <string>
#include "Database.h"

class Parser {
public:
    Parser(Database& db) : db(db) {}
    void parseAndExecute(const std::string& input);

private:
    Database& db;
};

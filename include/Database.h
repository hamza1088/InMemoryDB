#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Table.h"

class Database {
public:
    void createTable(const std::string& name, const std::vector<std::string>& columns);
    Table* getTable(const std::string& name);

private:
    std::unordered_map<std::string, std::unique_ptr<Table>> tables;
};
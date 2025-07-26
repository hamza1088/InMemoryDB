#include "Database.h"
#include <stdexcept>

void Database::createTable(const std::string& name, const std::vector<std::string>& columns) {
    if (tables.count(name)) throw std::runtime_error("Table already exists");
    tables[name] = std::make_unique<Table>(columns);
}

Table* Database::getTable(const std::string& name) {
    if (!tables.count(name)) throw std::runtime_error("Table not found");
    return tables[name].get();
}
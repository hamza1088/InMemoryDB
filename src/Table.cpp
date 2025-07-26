// src/Table.cpp
#include "Table.h"
#include <stdexcept>
#include <algorithm>

Table::Table(const std::vector<std::string>& cols)
  : columns(cols) {}

void Table::insert(const Row& row) {
    if (row.size() != columns.size())
        throw std::runtime_error("Column count mismatch");
    rows.push_back(row);
}

std::vector<Row> Table::selectAll() const {
    return rows;
}

void Table::update(const std::string& col,
                   const std::string& newVal,
                   const std::string& whereCol,
                   const std::string& whereVal)
{
    auto itCol    = std::find(columns.begin(), columns.end(), col);
    auto itWhere  = std::find(columns.begin(), columns.end(), whereCol);
    if (itCol == columns.end() || itWhere == columns.end())
        throw std::runtime_error("Unknown column in UPDATE");
    size_t idxCol   = std::distance(columns.begin(), itCol);
    size_t idxWhere = std::distance(columns.begin(), itWhere);

    for (auto &row : rows) {
        if (row[idxWhere] == whereVal) {
            row[idxCol] = newVal;
        }
    }
}

void Table::deleteRows(const std::string& col,
                       const std::string& val)
{
    auto itCol = std::find(columns.begin(), columns.end(), col);
    if (itCol == columns.end())
        throw std::runtime_error("Unknown column in DELETE");
    size_t idxCol = std::distance(columns.begin(), itCol);

    rows.erase(
      std::remove_if(rows.begin(), rows.end(),
        [&](const Row& r){ return r[idxCol] == val; }),
      rows.end());
}

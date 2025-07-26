// include/Table.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using Row = std::vector<std::string>;

class Table {
public:
    Table(const std::vector<std::string>& cols);

    void insert(const Row& row);
    std::vector<Row> selectAll() const;

    // New:
    // Update all rows where column `whereCol` equals `whereVal`,
    // setting column `col` = `newVal`
    void update(const std::string& col,
                const std::string& newVal,
                const std::string& whereCol,
                const std::string& whereVal);

    // Delete all rows where column `col` equals `val`
    void deleteRows(const std::string& col,
                    const std::string& val);

    const std::vector<std::string>& getColumns() const { return columns; }

private:
    std::vector<std::string> columns;
    std::vector<Row> rows;
};

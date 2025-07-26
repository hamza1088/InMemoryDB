// src/Parser.cpp
#include "Parser.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// helper: uppercase a string
static std::string up(const std::string& s) {
    std::string t=s;
    std::transform(t.begin(), t.end(), t.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return t;
}

void Parser::parseAndExecute(const std::string& input) {
    std::istringstream ss(input);
    std::string cmd; ss >> cmd;
    cmd = up(cmd);

    if (cmd == "CREATE") {
        // CREATE TABLE name (col1,col2,...)
        ss >> cmd; // should be TABLE
        std::string tbl; ss >> tbl;
        std::string cols; 
        std::getline(ss, cols, ')'); // read " (col1,col2"
        auto p = cols.find('(');
        cols = cols.substr(p+1);
        // split on commas
        std::vector<std::string> columns;
        std::istringstream cs(cols);
        std::string col;
        while (std::getline(cs, col, ',')) {
            columns.push_back(col);
        }
        db.createTable(tbl, columns);
        std::cout << "Table '"<<tbl<<"' created\n";
    }
    else if (cmd == "INSERT") {
        // INSERT INTO name VALUES (v1,v2,...)
        ss >> cmd; // INTO
        std::string tbl; ss >> tbl;
        ss >> cmd; // VALUES
        std::string vals;
        std::getline(ss, vals, ')'); // " (v1,v2"
        auto p = vals.find('(');
        vals = vals.substr(p+1);
        std::vector<std::string> row;
        std::istringstream vs(vals);
        std::string v;
        while (std::getline(vs, v, ',')) {
            // trim leading spaces / quotes
            v.erase(0, v.find_first_not_of(" '\""));
            v.erase(v.find_last_not_of(" '\"")+1);
            row.push_back(v);
        }
        db.getTable(tbl)->insert(row);
        std::cout << "1 row inserted\n";
    }
    else if (cmd == "SELECT") {
        // only supports: SELECT * FROM name
        ss >> cmd; // *
        ss >> cmd; // FROM
        std::string tbl; ss >> tbl;
        auto rows = db.getTable(tbl)->selectAll();
        // print header
        for (auto &c: db.getTable(tbl)->getColumns())
            std::cout << c << "\t";
        std::cout<<"\n";
        // print rows
        for (auto &r: rows) {
            for (auto &f: r) std::cout<<f<<"\t";
            std::cout<<"\n";
        }
    }
    else if (cmd == "UPDATE") {
        // UPDATE name SET col=newVal WHERE col2=val2
        std::string tbl; ss >> tbl; 
        ss >> cmd; // SET
        std::string assignment; 
        ss >> assignment; // "col=newVal"
        auto eq = assignment.find('=');
        std::string col   = assignment.substr(0, eq);
        std::string newV  = assignment.substr(eq+1);

        ss >> cmd; // WHERE
        std::string condition; 
        ss >> condition; // "col2=val2"
        auto eq2 = condition.find('=');
        std::string whereCol = condition.substr(0, eq2);
        std::string whereVal = condition.substr(eq2+1);

        db.getTable(tbl)->update(col, newV, whereCol, whereVal);
        std::cout<<"Rows updated\n";
    }
    else if (cmd == "DELETE") {
        // DELETE FROM name WHERE col=val
        ss >> cmd; // FROM
        std::string tbl; ss >> tbl;
        ss >> cmd; // WHERE
        std::string condition; ss >> condition;
        auto eq = condition.find('=');
        std::string col = condition.substr(0, eq);
        std::string val = condition.substr(eq+1);

        db.getTable(tbl)->deleteRows(col, val);
        std::cout<<"Rows deleted\n";
    }
    else {
        std::cout<<"Unknown command\n";
    }
}

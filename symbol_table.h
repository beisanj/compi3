//
// Created by Rooya on 7/8/2024.
//

#ifndef COMPIHW3_SYMBOL_TABLE_H
#define COMPIHW3_SYMBOL_TABLE_H
#include <string>
#include <vector>
using std::vector;
using std::string;

class symbol{
public:
    string name;
    string type;
    int offset;
    int val;
};
class symbolSubTable {
public:
    std::vector<symbol*> symbols;
    int curr_offset;
    symbolSubTable(int curr_off){
        curr_offset = curr_off;
    }
};


#endif //COMPIHW3_SYMBOL_TABLE_H

//
// Created by Rooya on 7/8/2024.
//

#ifndef COMPIHW3_SYMBOL_TABLE_H
#define COMPIHW3_SYMBOL_TABLE_H
#include <string>
#include <vector>
#include "hw3_output.hpp"
#include "types.h"
using std::vector;
using std::string;
extern int lineno;
class symbol{
public:
    string name;
    string type;
    int offset;
    int val;
    symbol(string name,string type,int offset,int val):name(name),type(type),offset(offset),val(val){}
};
class symbolSubTable {
public:
    std::vector<symbol*> symbols;
    int curr_offset;
    symbolSubTable(int curr_off){
        curr_offset = curr_off;
    }
    void printContent(){
        for(auto& s : symbols)
            output::printID(s->name ,s->offset, s->type);
    }
    bool checkIfAlreadyExists(string name){
        for(auto& s : symbols){
            if(s->name == name){
                return true;
            }
        }
        return false;
    }
    bool addSymbol(string name,string type,int val){
        if(checkIfAlreadyExists(name)){
            return false;
        }
        symbol* new_symbol = new symbol(name,type,curr_offset,val);
        symbols.push_back(new_symbol);
        curr_offset++;
    }
};

class symbolTable{
    std::vector<symbolSubTable*> SubTables;
    /// std::vector<symbolSubTable*> functions;
    symbolSubTable* addSubTable(){
        int cur_offset = SubTables.back()->curr_offset;
        symbolSubTable* new_subtable = new symbolSubTable(cur_offset);
        SubTables.push_back(new_subtable);
    }
    bool checkIfAlreadyExists(string name){
        for (auto& s : SubTables){
            if(s->checkIfAlreadyExists(name)){
                return true;
            }
        }
        return false;
    }
    bool checkIfLegalFunction(string funcName,Node arg) {
        if (funcName == "print") {
            if (arg.value == "STRING") {
                return true;
            } else {
                output::errorPrototypeMismatch(lineno,funcName,"string");
                exit(0);
            }

        }
        else if (funcName =="printi"){
            if(arg.value == "INT"){
                return true;
            } else {
                output::errorPrototypeMismatch(lineno,funcName,"int");
                exit(0);
            }
        }
        else if (funcName == "readi"){
            if(arg.value == "INT"){
                return true;
            } else {
                output::errorPrototypeMismatch(lineno,funcName,"int");
                exit(0);
            }

        }
        return false;
    }

};


#endif //COMPIHW3_SYMBOL_TABLE_H

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
extern int yylineno;
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
    symbol* retSymbol(string name){
        for(auto& s : symbols){
            if(s->name == name){
                return s;
            }
        }
        return nullptr;
    }
    bool addSymbol(string name,string type,int val){
        if(checkIfAlreadyExists(name)){
            return false;
        }
        symbol* new_symbol = new symbol(name,type,curr_offset,val);
        symbols.push_back(new_symbol);
        curr_offset++;
      //  cout<< "reached addSymbol"<<endl;
        return true;
    }
};

class symbolTable{
public:
    std::vector<symbolSubTable*> SubTables;
    /// std::vector<symbolSubTable*> functions;
    symbolSubTable* addSubTable(){
        int cur_offset=0;
        if(!SubTables.empty()){
         //   cout<<"68"<<endl;

            cur_offset = SubTables.back()->curr_offset;
        }
        symbolSubTable* new_subtable = new symbolSubTable(cur_offset);
        SubTables.push_back(new_subtable);
        return SubTables.back();
    }
    symbolTable(){
     //   cout<<"75"<<endl;
        addSubTable();
    }
    bool checkIfAlreadyExists(string name){
        if(SubTables.empty())
            return false;
        for (auto& s : SubTables){
          //  cout<<"checkIfAlreadyExists"<<endl;
            if(s->checkIfAlreadyExists(name)){
                return true;
            }
        }

        return false;
    }
    symbol* getSymbol(string name){
        for (auto& s : SubTables){
            if(s->retSymbol(name)){
                return s->retSymbol(name);
            }
        }
        return nullptr;
    }
    Node* checkIfLegalFunction(string funcName,Node* arg/*, Node*& res*/) {
        string typeofarg=arg->name;
       // cout<<"func name"<<funcName<<endl;
        Node *n11=dynamic_cast<IDClass*>(arg);
        if(n11){
            typeofarg=getSymbol(arg->name)->type;
        }
        if (funcName == "print") {
            if (typeofarg == "STRING") {
                return new Node("print","VOID");
            } else {
                output::errorPrototypeMismatch(yylineno,funcName,"string");
                exit(0);
            }

        }
        else if (funcName =="printi"){
            if(typeofarg == "INT"){
                return new Node("printi","VOID");

            } else {
                output::errorPrototypeMismatch(yylineno,funcName,"int");
                exit(0);
            }
        }
        else if (funcName == "readi"){
            if(typeofarg == "INT"){
                return new Node("readi","INT");
              //  cout<<"success line 128"<<endl;
               // return true;
            } else {
                output::errorPrototypeMismatch(yylineno,funcName,"int");
                exit(0);
            }

        }
        return nullptr;
    }
    void removeSubTable(){
        if(SubTables.size()==0){
            return;
        }

        symbolSubTable *toRemove=SubTables.back();
        output::endScope();
        if(SubTables.size()==1){
            output::printID("print",0,output::makeFunctionType("STRING","VOID"));
            output::printID("printi",0,output::makeFunctionType("INT","VOID"));
            output::printID("readi",0,output::makeFunctionType("INT","INT"));
        }
        for(auto &s : toRemove->symbols){
            output::printID(s->name, s->offset,s->type);
        }
        SubTables.pop_back();
        //
    }

};


#endif //COMPIHW3_SYMBOL_TABLE_H
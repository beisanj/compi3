#include <iostream>
#include "types.h"
#define YYSTYPE Node*
#include "hw3_output.hpp"
#include "symbol_table.h"
using namespace output;
using namespace  std;
/// global variables

symbolTable* table;
bool isLoop=false;


///



void checkIfBool(Node* n){
    string castToType=n->name;
    Node *node1=dynamic_cast<ID*>(n);
    if(node1){
        castToType=table->getSymbol(n->name)->type;
    }
    if(castToType=="BOOL"){
        return;
    }

    output::errorMismatch(yylineno);
    exit(0);

}


void checkIfLegalByte(Node* n){
    if(std::stoi(n->value)>255){
        errorByteTooLarge(yylineno,n->value);
        exit(0);
    }

}

void checkIfDefinedID(Node *n){

    if(!table->checkIfAlreadyExists(n->name)){
        errorUndef(yylineno,n->name);
        exit(0);
    }

}


void checkIfAndOperandsAreBool(Node* n1, Node* n2){
    string typeofn1=n1->name;
    string typeofn2=n2->name;
    Node *n11=dynamic_cast<ID*>(n1);
    Node *n22=dynamic_cast<ID*>(n2);
    if(n11){
        typeofn1=table->getSymbol(n1->name)->type;
    }
    if(n22){
        typeofn2=table->getSymbol(n2->name)->type;
    }

    if(typeofn1!="BOOL"||typeofn2!="BOOL") {
        output::errorMismatch(yylineno);
        exit(0);}

}

bool calculateOp1AndOp2(Node* n1, Node* n2){
    if(n1->value=="false"|| n2->value=="false"){
        return false;
    }
    return true;

}
bool calculateOp1OrOp2(Node* n1, Node* n2){
    if(n1->value=="false"&& n2->value=="false"){
        return false;
    }
    return true;

}


void checkIfOpIsIntOrByte(Node* n1){
    string typeofn=n1->name;
    Node *to=dynamic_cast<ID*>(n1);
    if(n1){
        typeofn=table->getSymbol(n1->name)->type;
    }
    if(typeofn!="INT"||typeofn!="BYTE"){
        errorMismatch(yylineno);
        exit(0);
    }
}
void createRes(Node* op1,Node* op2,Node*& res){
    string op1type=op1->name;
    string op2type=op2->name;
    Node *to=dynamic_cast<ID*>(op1);
    Node *from=dynamic_cast<ID*>(op2);
    if(to){
        op1type=table->getSymbol(op1->name)->type;
    }
    if(from){
        op2type=table->getSymbol(op2->name)->type;
    }
    if(op1type=="INT" || op2type == "INT"){
        res= new Num("1");
        return;
    }
    else{
        res= new NumB("1");
        return;
    }

}



Node* checkIfLegalCasting(Node* castTo,Node* castFrom/*,Node*& finalExp*/){
    string castToType=castTo->name;
    string castFromType=castFrom->name;
    Node *to=dynamic_cast<ID*>(castTo);
    Node *from=dynamic_cast<ID*>(castFrom);
    if(to){
        castToType=table->getSymbol(castTo->name)->type;
    }
    if(from){
        castFromType=table->getSymbol(castFrom->name)->type;
    }
    if(castToType=="BYTE" &&( castFromType == "INT" || castFromType == "BYTE")){
        int realVal= stoi(castFrom->value);
            if(!from) castFrom->name="BYTE";
             return new NumB(castFrom->value);

    }
    if(castToType=="INT"&&( castFromType == "INT" || castFromType == "BYTE")){
        if(!from) castFrom->name="INT"; ///
        return new Num(castFrom->value);

    }
    else {
        errorMismatch(yylineno);
        exit(0);
    }
}



void calculateResOfComparison(Node* op1, Node* op2, Node* operation/*, Node*& res)*/){
    if((op1->name=="INT"||op1->name=="BYTE") &&(op2->name=="INT"||op2->name=="BYTE")){
        if(operation->value=="=="){
            bool realVal= stoi(op1->value) == stoi(op2->value);
            string stringVal=(realVal) ? "true":"false";
        }
        if(operation->value==">="){
            bool realVal= stoi(op1->value) >= stoi(op2->value);
            string stringVal=(realVal) ? "true":"false";
            //res= new Bool(stringVal);
        }
        if(operation->value=="<="){
            bool realVal= stoi(op1->value) <= stoi(op2->value);
            string stringVal=(realVal) ? "true":"false";
            //res= new Bool(stringVal);
        }
        if(operation->value==">"){
            bool realVal= stoi(op1->value) > stoi(op2->value);
            string stringVal=(realVal) ? "true":"false";
            //res= new Bool(stringVal);
        }
        if(operation->value=="<"){
            bool realVal= stoi(op1->value) < stoi(op2->value);
            string stringVal=(realVal) ? "true":"false";
           // res= new Bool(stringVal);
        }
        if(operation->value=="!="){
            bool realVal= stoi(op1->value) != stoi(op2->value);
            string stringVal=(realVal) ? "true":"false";
        //    res= new Bool(stringVal);
        }
    }
}

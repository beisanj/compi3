#include <iostream>
#include "types.h"
#define YYSTYPE Node*
#include "hw3_output.hpp"
#include "symbol_table.h"
using namespace output;
using namespace  std;
/// global variables

extern symbolTable* table;
bool isLoop=false;


///



void checkIfBool(Node* n){
    string castToType=n->name;
    IDClass *node1=dynamic_cast<IDClass*>(n);
    if(node1){
        castToType=table->getSymbol(n->name)->type;
    }
/*    cout<<"n->val:"<<n->value<<endl;
    cout<<"n->name:"<<n->name<<endl;
    cout << "castToType: " <<castToType <<endl;*/
    if(castToType=="BOOL"){
        return;
    }

    output::errorMismatch(yylineno);
    exit(0);

}


void checkIfLegalByte(string num){

    if(std::stoi(num)>255){
        errorByteTooLarge(yylineno,num);
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
    IDClass *n11=dynamic_cast<IDClass*>(n1);
    IDClass *n22=dynamic_cast<IDClass*>(n2);
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

string calculateOp1AndOp2(Node* n1, Node* n2){
    if(n1->value=="false"|| n2->value=="false"){
        return "false";
    }
    return "true";

}
string calculateOp1OrOp2(Node* n1, Node* n2){
    if(n1->value=="false"&& n2->value=="false"){
        return "false";
    }
    return "true";

}


void checkIfOpIsIntOrByte(Node* n1){
    string typeofn=n1->name;
    IDClass *to=dynamic_cast<IDClass*>(n1);
    if(to) {
        typeofn = table->getSymbol(n1->name)->type;
    }
    if(typeofn!="INT"&&typeofn!="BYTE"){
        errorMismatch(yylineno);
        exit(0);
    }
}
void createRes(Node* op1,Node* op2,Node*& res){
    string op1type=op1->name;
    string op2type=op2->name;
    IDClass *to=dynamic_cast<IDClass*>(op1);
    IDClass *from=dynamic_cast<IDClass*>(op2);
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


//for assignment purposes
Node* checkIfLegalCastingWithBool(Node* castTo,Node* castFrom/*,Node*& finalExp*/){
    string castToType=castTo->name;
    string castFromType=castFrom->name;
    IDClass *to=dynamic_cast<IDClass*>(castTo);
    IDClass *from=dynamic_cast<IDClass*>(castFrom);
    if(to){
        castToType=table->getSymbol(castTo->name)->type;
    }
    if(from){
        castFromType=table->getSymbol(castFrom->name)->type;
    }

   /* cout<<"castToType: "<<castToType<<endl;
    cout<<"castFromType: "<<castFromType<<endl;
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
    }*/
   Node* n= checkIfLegalCasting(castTo,castFrom);

   if(n){
       return n;
   }
   else if(castToType=="BOOL"&& castFromType=="BOOL"){
        return new Bool("false"); /// again the value wont really matter.
   }
   else{ /// HUGGEEEEE MISTAKE!!1
       errorMismatch(yylineno);
       exit(0);
   }
   return nullptr;

}


Node* checkIfLegalCasting(Node* castTo,Node* castFrom/*,Node*& finalExp*/){
    string castToType=castTo->name;
    string castFromType=castFrom->name;
    IDClass *to=dynamic_cast<IDClass*>(castTo);
    IDClass *from=dynamic_cast<IDClass*>(castFrom);
    if(to){
        castToType=table->getSymbol(castTo->name)->type;
    }
    if(from){
        castFromType=table->getSymbol(castFrom->name)->type;
    }

    //cout<<"castToType: "<<castToType<<endl;
     //   cout<<"castFromType: "<<castFromType<<endl;
    if(castToType=="BYTE" &&( castFromType == "INT" || castFromType == "BYTE")){
        int realVal= stoi(castFrom->value);
            if(!from) castFrom->name="BYTE"; /// i dont think we should change this! it doesnt matter anyway we wont need it later presumably and if we had to use ti again we'll have to go through the recursive process all over again with $1, so we'll derive a new node entirely which wont have the faulty values
             return new NumB(castFrom->value);

    }
    if(castToType=="INT"&&( castFromType == "INT" || castFromType == "BYTE")){
        if(!from) castFrom->name="INT"; ///
        return new Num(castFrom->value);

    }
    else {

        return nullptr;
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

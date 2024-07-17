//
// Created by bisan on 7/8/2024.
//

#ifndef UNTITLED24_TYPES_H
#define UNTITLED24_TYPES_H

#include <string>
#include <iostream>
using std::string;
extern int yylineno;
extern bool isBreakLegal;
#define YYSTYPE Node*


class Node {
public:

    string value; // the type
    string name; // the var's name
    virtual ~Node()=default;
    Node(string val, string nm):value(val),name(nm){}
     Node(string nm): name(nm){}
    Node(Node *n):value(n->value),name(n->name){}

};
class Type : public Node {
public:
    Type(string val): Node(val,"TYPE"){}
    Type(Node* n):Node(n->value,n->name){};

};
class IDClass : public Node {
public:
    IDClass(string nm): Node("ID",nm){}
    IDClass(Node* n):Node(n->value,n->name){}
};
class Bool: public Node{
public:
    Bool(string val): Node(val,"BOOL"){}
   Bool(Node* n):Node(n->value,n->name){};
};
class Num: public Node{
public:
    Num(string val): Node(val,"INT"){}
    Num(Node* n):Node(n->value,n->name){}

};
class NumB: public Node{
public:
    NumB(string val): Node(val,"BYTE"){}
    NumB(Node* n):Node(n->value,n->name){}
};
class STRINGClass: public Node{
public:
    STRINGClass(string val): Node(val,"STRING"){}
    STRINGClass(Node* n):Node(n->value,n->name){}
};
class EXP: public Node{
    public:
    EXP(string val,string name): Node(val,"EXP"){}
    EXP(Node* n):Node(n->value,n->name){};
};

void checkIfBool(Node* n);
void checkIfLegalByte(string n);
void checkIfDefinedID(Node *n);
Node* checkIfLegalCastingWithBool(Node* castTo,Node* castFrom/*,Node*& finalExp*/);
void checkIfAndOperandsAreBool(Node* n1, Node* n2);
string calculateOp1AndOp2(Node* n1, Node* n2);
string calculateOp1OrOp2(Node* n1, Node* n2);
void checkIfOpIsIntOrByte(Node* n1);
void createRes(Node* op1,Node* op2,Node*& res);
Node* checkIfLegalCasting(Node* castTo,Node* castFrom);
void calculateResOfComparison(Node* op1, Node* op2, Node* operation);

#endif //UNTITLED24_TYPES_H
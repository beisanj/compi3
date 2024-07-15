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

    string value; // the valur, in the case of id the value is its name
    string name; // the type
    Node(string val, string nm):value(val),name(nm){}
    Node(string nm):name(nm){};
    virtual ~Node()= default;

};
class Type : public Node {
public:
    Type(string val): Node(val,"TYPE"){}

};
class ID : public Node {
public:
    ID(string val, string nm): Node(val,nm){}
};
class Bool: public Node{
public:
    Bool(string val): Node(val,"BOOL"){}

};
class Num: public Node{
public:
    Num(string val): Node(val,"INT"){}
};
class NumB: public Node{
public:
    NumB(string val): Node(val,"BYTE"){}
};
class STRING: public Node{
public:
    STRING(string val,string name): Node(val,"STRING"){}
};
class EXP: public Node{
public:
    EXP(string val,string name): Node(val,"EXP"){}
};




#endif //UNTITLED24_TYPES_H
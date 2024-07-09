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
    Node(string val, string nm):value(val),name(nm){}

};
class Type : public Node {
    Type(string val): Node(val,"TYPE"){}

};
class ID : public Node {
    ID(string val, string nm): Node(val,nm){}
};
class Bool: public Node{
    Bool(string val): Node(val,"BOOL"){}

};
class Num: public Node{
    Num(string val,string name): Node(val,"INT"){}
};
class NumB: public Node{
    NumB(string val,string name): Node(val,"BYTE"){}
};
class STRING: public Node{
    STRING(string val,string name): Node(val,"STRING"){}
};
class EXP: public Node{
    EXP(string val,string name): Node(val,"EXP"){}
};




#endif //UNTITLED24_TYPES_H
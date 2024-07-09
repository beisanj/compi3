%{
/* Declaration Section */
#include <stdio.h>
    #include "hw3_output.hpp"
    #include "parser.tab.hpp"
%}

%option yylineno
%option noyywrap
%x STR
digit            ([0-9])
letter           ([a-zA-Z])
letterdigit      ([a-zA-Z0-9])
string           ([ !#-\[\]-~])
escape           ([\\ntr\"0])
hex              (\\x[0-7][0-9A-Fa-f])
whitespace       ([\t\n\r ])

%%
int                                                                                 return INT;
byte                                                                                return BYTE;
b                                                                                   return B;
bool                                                                                return BOOL;
and                                                                                 return AND;
or                                                                                  return OR;
not                                                                                 return NOT;
true                                                                                return TRUE;
false                                                                               return FALSE;
return                                                                              return RETURN;
if                                                                                  return IF;
else                                                                                return ELSE;
while                                                                               return WHILE;
break                                                                               return BREAK;
continue                                                                            return CONTINUE;
;                                                                                   return SC;
\(                                                                                  return LPAREN;
\)                                                                                  return RPAREN;
\}                                                                                  return RBRACE;
\{                                                                                  return LBRACE;
=                                                                                   return ASSIGN;
\<|\>|\<\=|\>\=                                                          return RELOP_GREATER;
\=\=|\!\=                                                          return RELOP_EQUAL;
\*|\/                                                                              return MULT_DIV;
\+|\-                                                                               return ADD_SUB;

\/\/[^\n\r]*[\n|\r|\n\r]?                                                                        ;
{letter}{letterdigit}*                                                              return ID;
([1-9]+{digit}*)|0                                                                  return NUM;
\"([^\n\r\"\\]|\\[rnt"\\])+\"                                            return STRING;

{whitespace}                                                                        ;
.                                                                                   {output::errorLex(yylineno); exit(0);}

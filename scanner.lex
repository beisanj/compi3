%{
/* Declaration Section */
#include <stdio.h>
    #include "hw3_output.hpp"
    #include "parser.tab.hpp"
#include "types.h"



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
int                                                                                { yylval = new Node(yytext); return INT;}
byte                                                                               { yylval = new Node(yytext); return BYTE;}
b                                                                                  {yylval = new Node(yytext); return B;}
bool                                                                               {yylval = new Node(yytext); return BOOL;}
and                                                                                 {yylval = new Node(yytext);return AND;}
or                                                                                  {yylval = new Node(yytext);return OR;}
not                                                                                 {yylval = new Node(yytext);return NOT;}
true                                                                               {yylval = new Node(yytext); return TRUE;}
false                                                                              {yylval = new Node(yytext); return FALSE;}
return                                                                              {yylval = new Node(yytext);return RETURN;}
if                                                                                 {yylval = new Node(yytext); return IF;}
else                                                                                {yylval = new Node(yytext);return ELSE;}
while                                                                               {yylval = new Node(yytext);return WHILE;}
break                                                                               {yylval = new Node(yytext); return BREAK;}
continue                                                                            {yylval = new Node(yytext);return CONTINUE;}
;                                                                                   {yylval = new Node(yytext); return SC;}
\(                                                                                 { yylval = new Node(yytext); return LPAREN;}
\)                                                                                {yylval = new Node(yytext); return RPAREN;}
\}                                                                                {yylval = new Node(yytext); return RBRACE;}
\{                                                                                 {yylval = new Node(yytext); return LBRACE;}
=                                                                                {   yylval = new Node(yytext);  return ASSIGN;}
\<|\>|\<\=|\>\=                                                       {  yylval = new Node(yytext); return RELOP_GREATER;}
\=\=|\!\=                                                       {  yylval = new Node(yytext);    return RELOP_EQUAL;}
\*|\/                                                                           {  yylval = new Node(yytext);    return MULT_DIV;}
\+|\-                                                                            {  yylval = new Node(yytext);    return ADD_SUB;}

\/\/[^\n\r]*[\n|\r|\n\r]?                                                                        ;
{letter}{letterdigit}*                                                            {  yylval = new Node(yytext);   return ID;}
([1-9]+{digit}*)|0                                                                 {  yylval = new Node(yytext);  return NUM;}
\"([^\n\r\"\\]|\\[rnt"\\])+\"                                         {  yylval = new Node(yytext);    return STRING;}

{whitespace}                                                                        ;
.                                                                                   {output::errorLex(yylineno); exit(0);}

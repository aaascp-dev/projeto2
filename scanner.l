%{
#include <string>
#include "ast.h"
#include "parser.h"
extern int yylineno;
void yyerror(const char* s, ...);
%}

%option noyywrap nodefault yylineno

digs [0-9]+
nome [a-z]+

%%

[ \t]               ; //ignores spaces

"int"				{return T_DINT;}
"real"				{return T_DREAL;}
"bool"				{return T_DBOOL;}

{digs}              {yylval.integer = std::atoi(yytext); return T_INT;}

{digs}\.{digs}		{yylval.doubler = std::atof(yytext); return T_DOUBLE;}
\.{digs} 			{yylval.doubler = std::atof(yytext); return T_DOUBLE;}
{digs}\.		 	{yylval.doubler = std::atof(yytext); return T_DOUBLE;}

"TRUE"				{return T_BOOLTRUE;}
"FALSE"				{return T_BOOLFALSE;}

"+"                 {return T_PLUS;}
"-"                 {return T_SUB;}
"*"                 {return T_TIMES;}
"/"                 {return T_DIV;}

":"                 {return T_DEF;}
","                 {return T_COMMA;}
":="                {return T_ASSIGN;}
"~="				{return T_DIFERENTE;}
">"					{return T_MAIOR;}
"<"					{return T_MENOR;}
"="					{return T_IGUAL;}
">="				{return T_MAIORIGUAL;}
"<="				{return T_MENORIGUAL;}

"AND"				{return T_AND;}
"OR"				{return T_OR;}

"~"					{return T_UNIBOOL;}

"("					{return T_PARA;}
")"					{return T_PARAF;}
"["					{return T_ARRA;}
"]"					{return T_ARRAF;}

"while"				{return T_WHILE;}
"do"				{return T_DO;}
"if"				{return T_IF;}
"then"				{return T_THEN;}
"else"				{return T_ELSE;}
"end"				{return T_END;}

"def"				{return T_DEFI;}
"type"				{return T_TYPE;}

"fun" 				{return T_FUN;}
"return" 			{return T_RETO;}
"decl" {return T_DECL;}



";"					{return T_FINALEXP;}
"\n"                {return T_NL;}
{nome}              {yylval.name = strdup(yytext); return T_ID;}
.                   {yyerror("Erro lexico: simbolo desconhecido %c\n", *yytext);} 

%%

void yyerror(const char *s, ...){
    va_list ap;
    va_start(ap, s);
    std::fprintf(stderr, "Line %d: error: ", yylineno);
    std::vfprintf(stderr, s, ap);
}
/*Ja previamente definido por Laércio Lima Pilla e ampliado para aceitar funcoes e outros tipos de estruturas*/
#pragma once

#include <map>
#include "ast.h"

extern void yyerror(const char* s, ...);
namespace AST {class Node;}
namespace ST {

class Symbol;
enum Kind { variable, arranjo,  function };

typedef std::map<std::string,Symbol> SymbolList; //Set of Symbols

class Symbol {
    public:
        Tipos::Tipo type = Tipos::indefinido;              /*[Return] type of Symbol: integer, double.*/
        Kind kind;              /*Kind of symbol: variable, function, etc.*/
        int64_t value;        /*Space to store a value while we are doing interpretation.*/
        bool initialized;       /*Defines if symbol has been initialized or not.*/
        std::vector<ST::Symbol*> parametros; /*Stores the parameters of function*/
        
        /*Construtor de simbolos para variaveis*/
        Symbol(Tipos::Tipo type, Kind kind, int64_t value, bool initialized) :
            type(type), kind(kind), value(value), initialized(initialized) {  }
        Symbol() {type = Tipos::indefinido; kind = variable; value = 0; initialized = false;}
        
        /*Construtor de simbolos para funcoes*/
        Symbol(Tipos::Tipo type, Kind kind, std::vector<ST::Symbol*> parametros, bool initialized) :
            type(type), kind(kind), parametros(parametros), initialized(initialized) { }
};

class SymbolTable {
    public:
        SymbolList entryList;
        SymbolTable() {}
        bool checkId(std::string id) {return entryList.find(id) != entryList.end();}
        void addSymbol(std::string id, Symbol newsymbol) {entryList[id] = newsymbol;}
        AST::Node* newVariable(std::string id, Tipos::Tipo tipo,  AST::Node* next);
        AST::Node* assignVariable(std::string id);
        AST::Node* useVariable(std::string id);
        Tipos::Tipo returnType(std::string id);
        void realizaCoercao(std::string id);
        void defineTabelaOrigem(ST::SymbolTable* to) {tabelaOrigem = to;};
        ST::SymbolTable* tabelaOrigem = NULL;

        ST::Symbol getFunction(std::string id){return entryList[id];};
        AST::Node* newFunction(std::string id, Tipos::Tipo tipoVariavel, std::vector<ST::Symbol*> parametros);
        AST::Node* assignFunction(std::string id, Tipos::Tipo tipoVariavel, std::vector<ST::Symbol*> next, AST::Node* body);
};

}

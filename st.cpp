/*Ja previamente definido por Laércio Lima Pilla e ampliado para aceitar funcoes e outros tipos de estruturas*/
#include "st.h"

using namespace ST;

extern SymbolTable symtab;

AST::Node* SymbolTable::newVariable(std::string id, Tipos::Tipo tipoVariavel, AST::Node* next){
    if ( checkId(id) ) yyerror("Erro semantico: redefinicao da variavel %s\n", id.c_str());
    else {
      	Symbol entry(tipoVariavel, variable, 0, false);
    	addSymbol(id,entry);
    }
        return new AST::Variable(id, tipoVariavel, next); //Creates variable node anyway
}

AST::Node* SymbolTable::assignVariable(std::string id){
    if(!checkId(id)){
        if(tabelaOrigem != NULL){
            return tabelaOrigem->assignVariable(id);
           } else{
            yyerror("Variável ainda não definida! %s\n", id.c_str());
        }
    }
    entryList[id].initialized = true;
    return new AST::Variable(id, entryList[id].type, NULL); //Creates variable node anyway
}

AST::Node* SymbolTable::useVariable(std::string id){

    if(!checkId(id)){
        if(tabelaOrigem != NULL){
            return tabelaOrigem->useVariable(id);
        } else{
            yyerror("Erro semantico: variavel %s ainda nao declarada.\n", id.c_str());
        }
        return new AST::Variable(id, entryList[id].type, NULL); //forca a criacao de um nodo
    }
    if (  !entryList[id].initialized && !(entryList[id].type == Tipos::complexo)) {yyerror("Erro semantico: variavel %s ainda nao inicializada.\n", id.c_str());}

    return new AST::Variable(id, entryList[id].type, NULL); //Creates variable node anyway
}

/*Retorna o tipo de simbolo, passando um id como parametro*/
Tipos::Tipo SymbolTable::returnType(std::string id){
    return entryList[id].type;
}

/*Realiza a coersao de um tipo na tabela de simbolos*/
void SymbolTable::realizaCoercao(std::string id){
    if(!checkId(id)){
        return;
    }
    entryList[id].type = Tipos::real;
}

/*Cria uma nova funcao na tabela de simbolos*/
AST::Node* SymbolTable::newFunction(std::string id, Tipos::Tipo tipoVariavel, std::vector<ST::Symbol*> parametros){
    if( checkId(id) )
        yyerror("Erro semantico: função %s já existe.\n", id.c_str());
    else {
        Symbol entry(tipoVariavel, function, parametros, false);
        addSymbol(id,entry);
    }
    return NULL;
}

/*Define o corpo da funcao e caso ela nao foi declarada, a mesma eh criada*/
AST::Node* SymbolTable::assignFunction(std::string id, Tipos::Tipo tipoVariavel, std::vector<ST::Symbol*> next, AST::Node* body){
    if ( ! checkId(id) ) {
        this->newFunction(id, tipoVariavel, next);
    }
    ST::Symbol tmp = this->getFunction(id);
    for (int i = 0; i < next.size(); i++)
    {
        if (tmp.parametros.at(i)->type != next.at(i)->type)
        {
            std::cout<<"Atenção: tipo de parametro incompativel."<<std::endl;
        }
    }
    entryList[id].initialized = true;
    return NULL;
}
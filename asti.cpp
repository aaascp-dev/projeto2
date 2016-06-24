#include "ast.h"

using namespace AST;

/*Metodos de interpretacao*/
/*Interpreta o valor do nodo quando o mesmo for inteiro*/
int Integer::computeTree(){
    return value;
}

/*Interpreta o valor do nodo quando o mesmo for real*/
double Doubler::computeTree(){
    return value;
}

/*Interpreta o valor do nodo quando o mesmo for booleano*/
bool Boolean::computeTree(){
    return value;
}

/*Interpreta o arranjo, seu tipo e seu indice quando o nodo for do tipo arranjo*/
void Arranjo::computeTree(){
    std::cout << "arranjo "<<
    Tipos::tipoParaString(dynamic_cast<Variable*>(var)->tipo, true)
    << std::endl << "{+indice: ";
    indice->computeTree;
    std::cout << "}";
}

/*Interpreta o valor das operacoes binarias criadas na gramatica. Cada case influencia em uma operacao diferente*/
void BinOp::computeTree(){

    switch(op){
        case Tipos::assign:
            left->computeTree()
             =
            right->computeTree();
        break;

        case Tipos::plus:
            left->computeTree()
            +
            right->computeTree();
        break;

        case Tipos::sub:
            left->computeTree()
             -
            right->computeTree();
        break;

        case Tipos::times:
            left->computeTree()
            *
            right->computeTree();
        break;

        case Tipos::divi:
            left->computeTree()
            /
            right->computeTree();

        break;

        case Tipos::maior:
            left->computeTree()
            >
            right->computeTree();
        break;

        case Tipos::menor:
            left->computeTree()
            <
            right->computeTree();
        break;


        case Tipos::maiorigual:
            left->computeTree()
            >=
            right->computeTree();
        break;

        case Tipos::menorigual:
            left->computeTree()
            <=
            right->computeTree();
        break;

        case Tipos::ande:
            left->computeTree();
            &
            right->computeTree();
        break;

        case Tipos::ore:
            left->computeTree()
            |
            right->computeTree();
        break;

        case Tipos::igual:
            left->computeTree()
            ==
            right->computeTree();
        break;

        case Tipos::diferente:
            left->computeTree()
            !=
            right->computeTree();
        break;

        default: std::cout << "Operador nao tratado" << std::endl; break;
    }
}

/*Interpteta cada linha de insercao respectivamente*/
void Block::computeTree(){
    for (Node* line: lines) {
        line->computeTree();
        std::cout << std::endl;
    }
}

/*Interpreta as informacoes das variaveis criadas no programa, juntamente com seu tipo*/
void Variable::computeTree(){
    if (next != NULL){
        next->computeTree();
    }
}

/*Interpreta uma operacao unaria. A unica por enquanto no programa eh a operacao de declaracao (tanto de arranjos como variaveis "comuns")*/
void UniOp::computeTree(){
    switch(op){
        case Tipos::declaracao:
            std::cout << "Declaracao de ";
            node->computeTree();
        break;

        case Tipos::unario:
            std::cout << "(menor unario" << Tipos::tipoParaString(node->tipo, true) << ")";
            node->computeTree();
        break;

        case Tipos::unibool:
            std::cout << "(menor unario booleano)";
            node->computeTree();
        break;

        case Tipos::coercao:
            std::cout << "(coercao de valor de ";
            node->computeTree();
            std::cout << " para real)";
            node->tipo = Tipos::real;
        break;

        default: std::cout << "Operacao nao reconhecida!!!" << std::endl;
    }
}

/*Interpreta a condicao, quando a mesma aparecer na arvore.
Deve-se atentar ao fato de que a mesma imprimira o corpo do else somente
se ha algum nodo compondo este corpo*/
void Condicao::computeTree(){
    if(condicao->computeTree()){
      corpoIf->computeTree();
    }
    else {
      if(corpoElse != NULL){
        corpoElse->computeTree();
      }
    }
}

/*Realiza coercao dos nodos necessarios*/
AST::Node* AST::realizaCoercao(std::string id, AST::Node* left, AST::Node* right, ST::SymbolTable* symtab){
    if(Tipos::necessitaCoersao(left->tipo, right->tipo)){
        symtab->realizaCoercao(id);
        std::cout << "Erro semantico: operacao de assign esperava dois tipos compativeis, mas recebeu " << Tipos::tipoParaString(right->tipo, true) << " e " << Tipos::tipoParaString(left->tipo, true) << std::endl;
        return new AST::UniOp(left, Tipos::coercao, Tipos::real);
    }
   return left;
}

/*Interpreta o laco while declarado pelo usuario. O mesmo imprime tanto a condicao quanto o corpo da estrutura na ordem em que os mesmos aparecem*/
void Laco::computeTree(){
    while (condicaoLaco->computeTree()) {
      corpoLaco->computeTree();
    }
}

/*Interpreta quando ocorre a declaração de um função.*/
void Funcao::computeTree(){
    std::cout << "Declaração da função "<< Tipos::tipoParaString(tipo, false)<<": "<<id<<std::endl;
    std::cout<<"+parametros:"<<std::endl;

    if(parametros.size() == 0) {
        std::cout<<"sem parametros"<<std::endl;
    }else if (parametros.at(parametros.size() - 1) != NULL && parametros.size() > 0){
        parametros.at(parametros.size() - 1)->computeTree;
        std::cout<<" "<<std::endl;
    }
    std::cout<<"Fim declaração."<<std::endl;
}

/*Interpreta quando ocorre uma definição de uma função.*/
void DefineFuncao::computeTree(){
    std::cout << "Definição de função "<< Tipos::tipoParaString(tipo, false)<<": "<<id<<std::endl;
}

/*Interpreta sempre que houver um retorno em uma função.*/
void Retorno::computeTree(){
    std::cout<<"Retorno de função: "<<std::endl;
     if (ret != NULL){
        ret->computeTree();
    }
}

#include "TratamentoErros.h"
using namespace Tipos;


/*Verifica se dois nodos precisam realizar coersao de real para inteiro a partir do tipo dos mesmos*/
bool Tipos::necessitaCoersao(Tipo tipoNodoEsquerda, Tipo tipoNodoDireita){
	if(tipoNodoEsquerda == real || tipoNodoDireita == real){
		if(tipoNodoEsquerda == inteiro || tipoNodoDireita == inteiro){
			return true;
		}
	}
	return false;
}

/*Verifica erros semanticos em operacoes unitarias, como operador unario, unario para booleano e definicoes de indices de arranjo e de condicoes de lacos do tipo if e while*/
Tipo Tipos::opUnaria(Tipo tipoRecebido, Operation op){
	switch(op){
		case defineIndiceArranjo:
			if(tipoRecebido != inteiro){
				Tipos::erroIndiceArranjo(inteiro, tipoRecebido);
			}
		break;
		case defineCondicaoLaco:
			if(tipoRecebido != booleano){
				Tipos::erroCondicaoLaco(booleano, tipoRecebido);
			}
		break;
		case unario:
		if(tipoRecebido != real || tipoRecebido != inteiro){
			Tipos::erroTipagem(unario, inteiro, real, tipoRecebido);
		}
		break;
		case unibool:
		if(tipoRecebido != booleano){
			Tipos::erroTipagem(unibool, booleano, indefinido, tipoRecebido);
		}
		break;
	default:
		std::cout << "Operacao nao suportada em operacoes unarias!" << std::endl;
	}
	return tipoRecebido;
}

/*Verifica erros semanticos em operacoes binarias*/
Tipo Tipos::opBinaria(Tipo tipoNodoEsquerda, Tipo tipoNodoDireita, Operation op){
	switch(op){
	case assign:
			if(tipoNodoEsquerda != tipoNodoDireita){
				Tipos::tiposIncompativeis(tipoNodoEsquerda, tipoNodoDireita, op);
			}
		return tipoNodoEsquerda;
	case ande:
		if(tipoNodoEsquerda != booleano){
			Tipos::erroTipagem(ande, booleano, indefinido, tipoNodoEsquerda);
			break;
		}	
		if(tipoNodoDireita != booleano){
			Tipos::erroTipagem(ande, booleano, indefinido, tipoNodoEsquerda);
			break;
		}	
	 break;

		default:
		if(op == plus || op == sub || op == times || op == divi){
			if(tipoNodoEsquerda == real || tipoNodoDireita == real){
					return real;
			}

			if(tipoNodoEsquerda != inteiro && tipoNodoEsquerda != real){
				Tipos::erroTipagem(op, inteiro, real, booleano);
				break;
			}

			if(tipoNodoDireita != inteiro && tipoNodoDireita != real){
				Tipos::erroTipagem(op, inteiro, real, booleano);
				break;
			}
		} 

		else if(op == maior || op == menor || op == maiorigual || op == menorigual){
				if(tipoNodoEsquerda == inteiro || tipoNodoEsquerda == real){
					if(tipoNodoDireita == booleano){
						erroCondicao(op, tipoNodoEsquerda, tipoNodoDireita, inteiro, booleano);
					}
				}
				return booleano;

		} else if(op == igual || op == diferente){
				if(tipoNodoEsquerda != tipoNodoDireita){
					Tipos::tiposIncompativeis(tipoNodoEsquerda, tipoNodoDireita, op);
				}
				return booleano;

		}else {
				std::cout << "Operacao nao suportada em operacoes binarias!" << std::endl;
		}
	}

	return inteiro;
}

/*Mostra na tela erros de condicoes em lacos*/
void Tipos::erroCondicao(Operation operacao, Tipo primeiroRecebido, Tipo segundoRecebido, Tipo primeiroEsperado, Tipo segundoEsperado){
	std::cout << "A condicao do laco obteve uma operacao de " << opParaString(operacao) << " esperava " << tipoParaString(primeiroEsperado, true);
	if(segundoEsperado != indefinido){
		std::cout << " ou " + tipoParaString(segundoEsperado, true);
	}
	std::cout << " mas recebeu " << tipoParaString(primeiroRecebido, true) << " e " << tipoParaString(segundoRecebido, true) << std::endl;
}

/*Mostra na tela erros de condicoes de tipagem*/
void Tipos::erroTipagem(Operation operacao, Tipo primeiroTipo, Tipo segundoTipo, Tipo recebido){
	std::cout<< "A operacao de " + opParaString(operacao) + " esperava " + tipoParaString(primeiroTipo, true);
	if(segundoTipo != indefinido){
		std::cout << " ou " + tipoParaString(segundoTipo, true);
	}
	std::cout << " como parâmetro, mas recebeu " << tipoParaString(recebido, true) << "." << std::endl;
}

/*Mostra na tela erros de tipos incompativeis entre variavei*/
void Tipos::tiposIncompativeis(Tipo primeiroTipo, Tipo segundoTipo, Operation operacao){
	std::cout << "Erro semantico: operacao de " << opParaString(operacao) << " esperava dois tipos compativeis, mas recebeu " <<
	tipoParaString(primeiroTipo, true) << " e " << tipoParaString(segundoTipo, true) << std::endl;
}

/*Mostra na tela erros de indice dos arranjos*/
void Tipos::erroIndiceArranjo(Tipo primeiroTipo, Tipo segundoTipo){
	std::cout << "Erro semantico: indice do arranjo esperava  " <<
	tipoParaString(primeiroTipo, true) << " mas recebeu " << tipoParaString(segundoTipo, true) << std::endl;
}

/*Mostra na tela erros de condicao dos lacos*/
void Tipos::erroCondicaoLaco(Tipo esperado, Tipo recebido){
	std::cout << "Erro semantico: laco da condicao esperava " <<
	tipoParaString(esperado, true) << " mas recebeu " << tipoParaString(recebido, true) << std::endl;
}

/*Converte um tipo passado como parametro para string a fim de ser impresso*/
std::string Tipos::tipoParaString(Tipo tipo, bool ehMasc){
	std::string retorno;
	switch(tipo){
		case inteiro: retorno =  "inteir"; break;
		case real: return "real";
		case booleano: retorno = "boolean"; break;
		default: retorno = "indefinid"; break;
	}
	if(ehMasc) return retorno += "o";
	return retorno += "a";


}

/*Converte uma operacao passada como parametro para string a fim de ser impressa*/
std::string Tipos::opParaString(Operation op){
	switch(op){
		case assign: return "assign";
		case plus: return "soma";
		case sub: return "subtracao";
		case maior: return "maior";
		case maiorigual: return "maior ou igual";
		case menor : return "menor";
		case menorigual : return "menor ou igual";
		case ande : return "and";
		case ore : return "or";
		case igual : return "igual";
		case diferente : return "diferente";
		default: return "indefinida";
	}
}

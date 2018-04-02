#pragma once
#include "ExcessaoBase.h"
#include <iostream>
#include <string>
#include <istream>

/** Classe Input.
  * @brief Uma classe que no fundo é um conjunto de funções static que operam sobre istreams extraindo os vários tipos de estruturas e dados usados no programa.
  * @note Lança excessões quando necessário ao contrário das istreams.
  */
class Input {
private:
	/** @brief Construtor privado de modo a que a classe não possa ser instanciada. É uma classe "puramente static" e portanto não faria sentido ter um objeto dela. */
	Input() {}
public:
	/** @brief Ler um Inteiro 
	  * @param data Uma istream a partir da qual é obtido o valor de retorno.
	  * @param useGetLine bool que indica se a leitura será baseada no getline(datastream) em oposição ao operador de extração.
	  * @return Retorna um inteiro */
	static int readInt(std::istream & data, bool useGetLine = false);

	/** @brief Ler um Float 
	  * @param data Uma istream a partir da qual é obtido o valor de retorno.
	  * @return Retorna um float */
	static float readFloat(std::istream & data);

	/** @brief Ler um Nome 
	  * @param data Uma istream a partir da qual é obtido o valor de retorno.
	  * @param delimitador Char que delimita o nome do resto da "linha".
	  * @return Retorna o nome sob o formato de uma string da stl */
	static std::string readNome(std::istream & data, char delimitador = ';');
	
	/** @brief Ler um separador (;). 
	  * @param data Uma istream. */
	static void readSeparador(std::istream & data);

	/** @brief Limpa o estado de uma stream de modo a que fique novamente válida. 
	  * @param data Uma istream. */
	static void limpaStream(std::istream & data);

	/** @brief Remove espaços da string no início e no fim. 
	    @param argString String que vai ter o espaçamento inicial e final removidos. */
	static void removeEspacamento(std::string& argString);
};


// Exceptions                ========================================

/** @brief Usada no método Input::readNome */
class ErrorNome : public ExcessaoBase {
public:
	ErrorNome(std::string argRazao) : ExcessaoBase(argRazao) { };
};

/** @brief Usada no método Input::readSeparador */
class ErroSeparador : public ExcessaoBase {
public:
	ErroSeparador(std::string argRazao) : ExcessaoBase(argRazao) { };
};

/** @brief É usada em todos os métodos da class Input. É lançada uma excessão desta classe quando ocorreu algum erro que invalide as istreams. */
class ErroStream : public ExcessaoBase {
public:
	ErroStream(std::string argRazao) : ExcessaoBase(argRazao) { };
};
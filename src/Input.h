#pragma once
#include "ExcessaoBase.h"
#include <iostream>
#include <string>
#include <istream>

/** Classe Input.
  * @brief Uma classe que no fundo � um conjunto de fun��es static que operam sobre istreams extraindo os v�rios tipos de estruturas e dados usados no programa.
  * @note Lan�a excess�es quando necess�rio ao contr�rio das istreams.
  */
class Input {
private:
	/** @brief Construtor privado de modo a que a classe n�o possa ser instanciada. � uma classe "puramente static" e portanto n�o faria sentido ter um objeto dela. */
	Input() = default;

public:
	/** @brief Ler um Inteiro 
	  * @param data Uma istream a partir da qual � obtido o valor de retorno.
	  * @param useGetLine bool que indica se a leitura ser� baseada no getline(datastream) em oposi��o ao operador de extra��o.
	  * @return Retorna um inteiro */
	static int readInt(std::istream & data, bool useGetLine = false);

	/** @brief Ler um Float 
	  * @param data Uma istream a partir da qual � obtido o valor de retorno.
	  * @return Retorna um float */
	static float readFloat(std::istream & data);

	/** @brief Ler um Nome 
	  * @param data Uma istream a partir da qual � obtido o valor de retorno.
	  * @param delimitador Char que delimita o nome do resto da "linha".
	  * @return Retorna o nome sob o formato de uma string da stl */
	static std::string readNome(std::istream & data, char delimitador = ';');
	
	/** @brief Ler um separador (;). 
	  * @param data Uma istream. */
	static void readSeparador(std::istream & data);

	/** @brief Limpa o estado de uma stream de modo a que fique novamente v�lida. 
	  * @param data Uma istream. */
	static void limpaStream(std::istream & data);

	/** @brief Remove espa�os da string no in�cio e no fim. 
	    @param argString String que vai ter o espa�amento inicial e final removidos. */
	static void removeEspacamento(std::string& argString);
};


// Exceptions                ========================================

/** @brief Usada no m�todo Input::readNome */
class ErrorNome : public ExcessaoBase {
public:
	explicit ErrorNome(const std::string &argRazao) : ExcessaoBase(argRazao) { };
};

/** @brief Usada no m�todo Input::readSeparador */
class ErroSeparador : public ExcessaoBase {
public:
	explicit ErroSeparador(const std::string &argRazao) : ExcessaoBase(argRazao) { };
};

/** @brief � usada em todos os m�todos da class Input. � lan�ada uma excess�o desta classe quando ocorreu algum erro que invalide as istreams. */
class ErroStream : public ExcessaoBase {
public:
	explicit ErroStream(const std::string &argRazao) : ExcessaoBase(argRazao) { };
};
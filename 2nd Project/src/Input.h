#pragma once
#include "ExcessaoBase.h"
#include <iostream>
#include <string>
#include <istream>

/**
 * Class that operates istreams
 */
class Input {
private:
	/** @brief Default constructor */
	Input() = default;

public:
	/** @brief Reads an int
	  * @param data
	  * @param useGetLine bool
	  * @return int
	  */
	static int readInt(std::istream & data, bool useGetLine = false);

	/** @brief Reads a float
	  * @param data
	  * @return float
	  * */
	static float readFloat(std::istream & data);

	/** @brief Reads a name
	  * @param data
	  * @param delimitador Char
	  * @return string - returns the name */
	static std::string readNome(std::istream & data, char delimitador = ';');
	
	/** @brief Reads a separator (;).
	  * @param data - istream. */
	static void readSeparador(std::istream & data);

	/** @brief Cleans the state of a stream and puts it valid
	  * @param data - istream. */
	static void limpaStream(std::istream & data);

	/** @brief Removes spaces in string
	    @param argString - string */
	static void removeEspacamento(std::string& argString);
};


// Exceptions                ========================================

/** @brief used in mode Input::readNome */
class ErrorNome : public ExcessaoBase {
public:
	explicit ErrorNome(const std::string &argRazao) : ExcessaoBase(argRazao) { };
};

/** @brief used in mode Input::readSeparador */
class ErroSeparador : public ExcessaoBase {
public:
	explicit ErroSeparador(const std::string &argRazao) : ExcessaoBase(argRazao) { };
};

/** @brief Used in all methods of class Input*/
class ErroStream : public ExcessaoBase {
public:
	explicit ErroStream(const std::string &argRazao) : ExcessaoBase(argRazao) { };
};
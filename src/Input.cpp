#include <iostream>
#include <sstream>
#include <string>
#include "Input.h"

using namespace std;

int Input::readInt(istream & data, bool useGetLine)
{
	int x = 0;
	if (useGetLine) {
		string temp;
		getline(data, temp);
		x = stoi(temp);
	}
	else {
		data >> x;
	}
	if (!data.good() && !data.eof()) {
		limpaStream(data);
		throw ErroStream("A leitura do n�mero falhou.");
	}
	return x;
}

float Input::readFloat(istream & data)
{
	float x = 0;
	data >> x;
	if (!data.good() && !data.eof()) {
		limpaStream(data);
		throw ErroStream("A leitura do numero em virgula flutuante falhou.");
	}
	return x;
}

string Input::readNome(istream & data, char delimitador)
{
	string nome;
	getline(data, nome, delimitador);
	if (!data.good()) {
		limpaStream(data);
		throw ErroStream("A leitura do Nome falhou.");
	}
	else if (nome.empty()) {
		throw ErrorNome("O nome nao e valido.");
	}
	else {
		removeEspacamento(nome);
		return nome;
	}
}

void Input::readSeparador(istream& in)
{
	string separador;
	in >> separador;

	if (!in.good() && !in.eof()) {
		limpaStream(in);
		throw ErroStream("A leitura do separador falhou.");
	}

	if (separador != ";") throw ErroSeparador("Separador (;) mal posicionado.");
	return;
}

void Input::limpaStream(istream & in) {
	in.clear();
	in.ignore(1000, '\n');
}

void Input::removeEspacamento(string &argString) {
	size_t startpos = argString.find_first_not_of(' ');
	size_t endpos = argString.find_last_not_of(' ');

	if (endpos != string::npos) {
		argString = argString.substr(0, endpos + 1);
		argString = argString.substr(startpos);
	}
}
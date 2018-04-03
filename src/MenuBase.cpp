#include "Menus.h"
#include "Input.h"

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

void MenuBase::limpaEcran() {
#ifdef _WIN32
	std::system("cls");
#else /* LINUX OR MAC */
	std::system("clear");
#endif
}

void MenuBase::imprimeOpcoes(const std::string& titulo, const std::vector<std::string>& opcoes) {
	size_t n = opcoes.size();
	vector<string> opcoes_nonconst(opcoes);
	opcoes_nonconst.emplace_back("Voltar");
	unsigned char x1 = 186;	//Vertical Lines
	unsigned char x2 = 187;	//Top-Right Corner
	unsigned char x3 = 188;	//Bottom-Right Corner
	unsigned char x4 = 200;	//Bottom-Left Corner
	unsigned char x5 = 201;	//Top-Left Corner
	unsigned char x6 = 205;	//Horizontal Lines
	unsigned char x0 = 255;	//Empty spaces

	size_t maxOptionSize = 0;
	for (auto &i : opcoes_nonconst) {
		if (i.size() > maxOptionSize) {
			maxOptionSize = i.size();
		}
	}
	maxOptionSize += 10;

	for (auto &i : opcoes_nonconst) {
        i.resize(maxOptionSize, ' ');
	}

	string separateFromBorder = "         ";
	string separateMenu = "    ";

	size_t emptyLine = 4 + 4 + maxOptionSize; //Tamanho de uma linha vazia;
	string emptySpaces;
	emptySpaces.resize(emptyLine, ' ');
	string spaceLine = emptySpaces;
	spaceLine.insert(spaceLine.begin(), x1);
	spaceLine.push_back(x1);

	double halfsize = (emptyLine - titulo.size()) / 2.0;


	//Primeira Linha
	cout << separateFromBorder << x5;
	for (int i = 0; i < emptyLine; i++) {
		cout << x6;
	}
	cout << x2 << endl;

	//Linha do Menu
	cout << separateFromBorder << x1;
	double num;
	modf(halfsize, &num);
	for (int i = 0; i < num; i++) {
		cout << x0;
	}
	cout << titulo;
	if (modf(halfsize, &num) != 0.0) {
		num++;
	}
	for (int i = 0; i < num; i++) {
		cout << x0;
	}
	cout << x1 << endl << separateFromBorder << spaceLine << endl;

	//Opcoes Numeradas
	for (int i = 0; i < n; i++) {
		cout << separateFromBorder << x1 << separateMenu << i + 1 << " - " << opcoes_nonconst[i] << x1 << endl;
		cout << separateFromBorder << spaceLine << endl;
	}

	//Opcao Voltar
	cout << separateFromBorder << x1 << separateMenu << "V - " << opcoes_nonconst.back() << x1 << endl << separateFromBorder << spaceLine << endl;

	//Ultima linha
	cout << separateFromBorder << x4;
	for (int i = 0; i < emptyLine; i++) {
		cout << x6;
	}
	cout << x3 << endl << endl;
}

char MenuBase::processaOpcoes(const std::vector<char>& opcoes)
{
	cout << "# Por favor selecione uma opcao: ";
	char opcao;

	while (true) {
		string temp;
		getline(cin, temp);
		Input::removeEspacamento(temp);

		std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper); /* CONVERTER STRING PARA MAISCULAS. Importante porque v == V (voltar) */


		if (temp.size() != 1) {
			cout << "# Input invalido. Por favor selecione uma opcao: ";
		}
		else if (find(opcoes.begin(), opcoes.end(), temp[0]) == opcoes.end()) {
			cout << "# Opcao invalida. Por favor selecione uma opcao: ";
		}
		else {
			opcao = temp[0]; // Seleção válida
			break;
		}
	}

	return opcao;
}
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Manager.h"
#include "Input.h"
/**
* @brief Classe abstrata usada como classe base para todos os menus que comp�em a interface do programa.
*/
class MenuBase {
public:
	/** @brief Fun��o virtual pura. Obriga os menus derivados a implementarem o seu m�todo de visualiza��o. */
	virtual void display() = 0;

	/** @brief Faz clear ao ecran. Deve preceder ao display de um menu. */
	static void CleanScreen();

	/** @brief Imprime um menu bem formatado com as v�rias op��es que o utilizador pode escolher.
	* @param titulo T�tulo do Menu
	* @param opcoes Vetor de strings que representa as op��es que o utilizador pode escolher.
	*/
	static void printOptions(const std::string& titulo, const std::vector<std::string>& opcoes);

	/** @brief Processa as op��es de um menu. Pede ao utilizador para fazer uma sele��o e repete o processo at� ao input ser v�lido.
	* @param opcoes Possiveis op��es que o utilizador pode escolher no formato de um vetor de chars em que cada char � uma poss�vel sele��o.
	* @return Devolve o char com a op��o que o utilizador escolheu.
	*/
	static char processOptions(const std::vector<char>& opcoes);
};

class MainMenu : public MenuBase {

public:
	static void displayMenu(GraphViewer *gv);



};
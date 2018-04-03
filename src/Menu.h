#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Manager.h"
#include "Input.h"
/**
* @brief Classe abstrata usada como classe base para todos os menus que compõem a interface do programa.
*/
class MenuBase {
public:
	/** @brief Função virtual pura. Obriga os menus derivados a implementarem o seu método de visualização. */
	virtual void display() = 0;

	/** @brief Faz clear ao ecran. Deve preceder ao display de um menu. */
	static void CleanScreen();

	/** @brief Imprime um menu bem formatado com as várias opções que o utilizador pode escolher.
	* @param titulo Título do Menu
	* @param opcoes Vetor de strings que representa as opções que o utilizador pode escolher.
	*/
	static void printOptions(const std::string& titulo, const std::vector<std::string>& opcoes);

	/** @brief Processa as opções de um menu. Pede ao utilizador para fazer uma seleção e repete o processo até ao input ser válido.
	* @param opcoes Possiveis opções que o utilizador pode escolher no formato de um vetor de chars em que cada char é uma possível seleção.
	* @return Devolve o char com a opção que o utilizador escolheu.
	*/
	static char processOptions(const std::vector<char>& opcoes);
};

class MainMenu : public MenuBase {

public:
	static void displayMenu();



};
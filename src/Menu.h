#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Manager.h"
#include "Input.h"
/**
 *
* @brief Abstract class used as base class for the menu of the program
*/
class MenuBase {
public:
	/**
	 *  @brief Virtual pure function. All of its derived methods must follow its rules
	 */
	virtual void display() = 0;

	/** @brief Clears the screen*/
	static void CleanScreen();

	/** @brief Prints a menu with the chosen options.
	* @param titulo title of the menu
	* @param opcoes vector of strings that contains the options chosen by the user
	*/
	static void printOptions(const std::string& titulo, const std::vector<std::string>& opcoes);

	/** @brief Processes the menu options. Repeats selection of option until it's valid
	* @param opcoes - Possible options
	* @return char - option chosen by user
	*/
	static char processOptions(const std::vector<char>& opcoes);
};

class MainMenu : public MenuBase {

public:
	/**
	 * @brief Displays the menu of the program
	 * @param gv
	 */
	static void displayMenu(GraphViewer *gv);



};
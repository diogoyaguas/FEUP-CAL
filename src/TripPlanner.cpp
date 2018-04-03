#include <iostream>
#include "Manager.h"
#include "Menu.h"

using namespace std;

int main() {

    Manager::loadData();
	MainMenu::displayMenu();

    return 0;
}
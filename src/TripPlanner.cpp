#include <iostream>
#include "Manager.h"
#include "Menu.h"

using namespace std;

int main() {
    Manager manager;

    manager.loadData();
    manager.printGraph();
    MainMenu::displayMenu();

    return 0;
}
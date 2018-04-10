#include <iostream>
#include "Manager.h"
#include "Menu.h"

using namespace std;

int main() {
    Manager manager;

	GraphViewer *gv = new GraphViewer(800,800, false);

    manager.loadData();


    manager.printGraph(gv);
    MainMenu::displayMenu(gv);

    return 0;
}
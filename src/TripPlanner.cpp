#include <iostream>
#include "Manager.h"
#include "Menu.h"

using namespace std;

int main() {
    Manager manager;

	GraphViewer *gv = new GraphViewer(1000, 1000, false);
	manager.initGv(gv);

    manager.loadData();
    //MainMenu::displayMenu();

   manager.printGraph(gv);


    return 0;
}
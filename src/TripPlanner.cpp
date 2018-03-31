#include <iostream>
#include "Manager.h"

using namespace std;

Manager* Manager::singleton_instance = nullptr;

int main() {

    Manager::instance()->loadData();
    Manager::instance()->mainMenu();

    return 0;
}
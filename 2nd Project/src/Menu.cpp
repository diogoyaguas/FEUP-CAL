#include "Menu.h"


using namespace std;

void MenuBase::CleanScreen() {

    cout << string(50, '\n');
}

void MenuBase::printOptions(const string &title, const vector<string> &options) {
    size_t n = options.size();
    vector<string> options_nonconst(options);
    options_nonconst.emplace_back("Exit");
    unsigned char x1 = 186;    //Vertical Lines
    unsigned char x2 = 187;    //Top-Right Corner
    unsigned char x3 = 188;    //Bottom-Right Corner
    unsigned char x4 = 200;    //Bottom-Left Corner
    unsigned char x5 = 201;    //Top-Left Corner
    unsigned char x6 = 205;    //Horizontal Lines
    unsigned char x0 = 255;    //Empty spaces

    size_t maxOptionSize = 0;

    for (auto &i : options_nonconst) {
        if (i.size() > maxOptionSize) {
            maxOptionSize = i.size();
        }
    }
    maxOptionSize += 10;


    for (auto &i : options_nonconst) {
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

    double halfsize = (emptyLine - title.size()) / 2.0;


    //Primeira Linha
    cout << separateFromBorder << x5;
    for (size_t i = 0; i < emptyLine; i++) {
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

    cout << title;
    if (modf(halfsize, &num) != 0.0) {

        num++;
    }
    for (int i = 0; i < num; i++) {
        cout << x0;
    }
    cout << x1 << endl << separateFromBorder << spaceLine << endl;

    //Opcoes Numeradas
    for (size_t i = 0; i < n; i++) {
        cout << separateFromBorder << x1 << separateMenu << i + 1 << " - " << options_nonconst[i] << x1 << endl;
        cout << separateFromBorder << spaceLine << endl;
    }

    //Opcao Sair
    cout << separateFromBorder << x1 << separateMenu << "E - " << options_nonconst.back() << x1 << endl
         << separateFromBorder << spaceLine << endl;

    //Ultima linha
    cout << separateFromBorder << x4;
    for (size_t i = 0; i < emptyLine; i++) {
        cout << x6;
    }
    cout << x3 << endl << endl;
}

char MenuBase::processOptions(const std::vector<char> &options) {
    cout << "# Please select an option: ";
    char option;

    while (true) {
        string temp;
        getline(cin, temp);
        Input::removeEspacamento(temp);

        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);


        if (temp.size() != 1) {
            cout << "# Invalid input. Please select an option: ";
        } else if (find(options.begin(), options.end(), temp[0]) == options.end()) {
            cout << "# Invalid input. Please select an option: ";
        } else {
            option = temp[0];
            break;
        }
    }

    return option;
}

void MenuModeChoice::displayMenu() {
    while (true) {

        CleanScreen();
        printOptions("OPTIONS",
                     {"Calculate Route",
                      "Check what lines run through a certain stop"});

        vector<char> options = {'1', '2', 'E'};

        char option = processOptions(options);

        switch (option) {

            case '1':
                CleanScreen();
                MenuStopOrLine::displayMenu();
                break;
            case '2':
                CleanScreen();
                MenuCheckLines::displayMenu();
                break;
            case 'E':
                exit(0);
            default:
                break;

        }
    }
}

void MenuStopOrLine::displayMenu() {

    printOptions("OPTIONS",
                 {"Pick origin and destination from all stops",
                  "Pick origin and destination from certain lines"});

    vector<char> options = {'1', '2', 'E'};

    char option = processOptions(options);

    switch (option) {

        case '1':
            CleanScreen();
            MenuChoosePath::displayMenu();
            break;
        case '2':
            CleanScreen();
            MenuPickFromLine::displayMenu();
            break;
        case 'E':
            break;
        default:
            break;

    }
}

void MenuChoosePath::displayMenu() {

    string idOrigin, idDestination;

    idOrigin = Manager::chooseOrigin();
    idDestination = Manager::chooseDestination();

    while (idOrigin == idDestination) {

        CleanScreen();
        cout << "<<< Stations are the same, choose again >>>\n" << endl;
        idOrigin = Manager::chooseOrigin();
        idDestination = Manager::chooseDestination();
    }

    printOptions("OPTIONS",
                 {"Check path by minimum deslocation time",
                  "Check path by lowest ticket price",
                  "Check path by shortest distance",
                  "Check path by number of stops"});

    vector<char> options = {'1', '2', '3', '4', 'E'};

    cin.ignore(1000, '\n');
    char option = processOptions(options);

    switch (option) {

        case '1':
            //call function to calculate path by deslocation time
            //the function called will ask the user where he is and where he wants to go and then, if the
            //choice is valid, will call the algorithm needed
            CleanScreen();
            Manager::chooseFastestPath(idOrigin, idDestination);
            break;
        case '2':
            //call funtion to calculate path by ticket price
            CleanScreen();
            Manager::chooseCheaperPath(idOrigin, idDestination);
            break;
        case '3':
            //call function to calculate path by distance
            CleanScreen();
            Manager::chooseShorterPath(idOrigin, idDestination);
            break;
        case '4':
            //call function to calculate path by number of stops
            CleanScreen();
            Manager::chooseLessTranshipmentPath(idOrigin, idDestination);
            break;
        case 'E':
            break;
        default:
            break;

    }

}

void MenuPickFromLine::displayMenu() {

    Line lineOrigin, lineDestination;
    string idOrigin, idDestination;

    lineOrigin = Manager::chooseOriginLine();
    idOrigin = Manager::chooseOrigin(lineOrigin);

    lineDestination = Manager::chooseDestinationLine();
    idDestination = Manager::chooseDestination(lineDestination);

    while (idOrigin == idDestination) {

        CleanScreen();
        cout << "<<< Stations are the same, choose again >>>\n" << endl;
        lineOrigin = Manager::chooseOriginLine();
        idOrigin = Manager::chooseOrigin(lineOrigin);

        lineDestination = Manager::chooseDestinationLine();
        idDestination = Manager::chooseDestination(lineDestination);
    }

    printOptions("OPTIONS",
                 {"Check path by minimum deslocation time",
                  "Check path by lowest ticket price",
                  "Check path by shortest distance",
                  "Check path by number of stops"});

    vector<char> options = {'1', '2', '3', '4', 'E'};

    char option = processOptions(options);

    switch (option) {

        case '1':
            //call function to calculate path by deslocation time
            //the function called will ask the user where he is and where he wants to go and then, if the
            //choice is valid, will call the algorithm needed
            CleanScreen();
            Manager::chooseFastestPath(idOrigin, idDestination);
            break;
        case '2':
            //call funtion to calculate path by ticket price
            CleanScreen();
            Manager::chooseCheaperPath(idOrigin, idDestination);
            break;
        case '3':
            //call function to calculate path by distance
            CleanScreen();
            Manager::chooseShorterPath(idOrigin, idDestination);
            break;
        case '4':
            //call function to calculate path by number of stops
            CleanScreen();
            Manager::chooseLessTranshipmentPath(idOrigin, idDestination);
            break;
        case 'E':
            break;
        default:
            break;

    }
}

void MenuCheckLines::displayMenu() {
    string idOrigin, idDestination;

    idOrigin = Manager::chooseOrigin();

    vector<Line> lines = Manager::getLinesFromStation(idOrigin);

    if (lines.empty()) cout << "\nNo lines run through this station!\n";
    else {
        cout << "\nThe following lines run through this station:\n\n";

        for (const Line &line : lines) {
            cout << " | " << line.getLineID().name << endl;
        }

        cin.ignore(1000, '\n');
        Manager::continueFunction();
    }
}

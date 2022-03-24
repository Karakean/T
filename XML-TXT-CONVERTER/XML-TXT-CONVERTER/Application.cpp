#include "Application.h"
void Application::run() {
    std::string input;
    MyFile* myFile;
    std::cout << "Enter the xml/txt file. For example: \"file.txt\" or \"file.xml\"\n";

    for (;;) {
        std::cin >> input;

        std::fstream check;
        check.open(input);
        if (check.fail()) {
            std::cout << "File cannot be opened or doesn\'t exist.\n";
            check.close();
            continue;
        }
        check.close();

        std::string extension = input.substr(input.find_last_of("."));
        if (extension == ".xml") {
            myFile = new MyXML(input.erase(input.length() - 4));
            break;
        }
        else if (extension == ".txt") {
            myFile = new MyTXT(input.erase(input.length() - 4));
            break;
        }
        else {
            std::cout << "It's not a valid file.\n";
        }
    }

    try {
        myFile->convert();
        std::cout << "Conversion succeeded.\n";
    }
    catch (const char* ex) {
        std::cout << ex;
    }
    
    delete myFile;
    return;
}

#include "Application.h"

void Application::run_app() {
    std::string input;
    MyFile* myFile;
    std::cout << "Enter the xml/txt file. For example: \"file.txt\" or \"file.xml\"\n";

    std::string path = "";
    std::string extension;

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

        std::size_t path_end = input.find_last_of("/\\");
        if (path_end != std::string::npos) {
            path = input.substr(0, path_end + 1);
            input.erase(0, path_end + 1);
        }
        extension = input.substr(input.find_last_of("."));
        if (extension == ".xml") {
            myFile = new MyXML(input.erase(input.length() - 4), path, path);
            extension = ".txt"; //extension which will be after conversion
            break;
        }
        else if (extension == ".txt") {
            myFile = new MyTXT(input.erase(input.length() - 4), path, path);
            //std::cout << input << std::endl << path << std::endl;
            extension = ".xml";
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
        std::ofstream invalid_output;
        //this opening will remove content of output from invalid file
        invalid_output.open(path+myFile->get_filename() +
            extension);
        invalid_output.close();
        std::cout << ex;
    }
    delete myFile;
    return;
}

void Application::run_tests() {
    bool result;
    for (int i = 0; i < 3; i++) {
        result = test("testtxt" + std::to_string(i + 1), ".txt");
        if (!result) {
            std::cout << "Wrong output with test: testtxt" << std::to_string(i + 1);
            return;
        }
    }
    for (int i = 0; i < 3; i++) {
        result = test("testxml" + std::to_string(i + 1), ".xml");
        if (!result) {
            std::cout << "Wrong output with test: testxml" << std::to_string(i + 1);
            return;
        }
    }
    std::cout << "All tests passed.\n";
    return;
}

bool Application::test(std::string filename, std::string extension) {
    MyFile* myFile;
    std::string in_path = "tests/";
    std::string out_path = "tests/results/";

    std::fstream check;
    check.open(in_path + filename + extension);
    if (check.fail()) {
        std::cout << "Something\'s wrong, test cannot be opened.\n";
        check.close();
        return false;
    }
    check.close();

    if (extension == ".xml") {
        myFile = new MyXML(filename, in_path, out_path);
        extension = ".txt";
    }
    else { //txt
        myFile = new MyTXT(filename, in_path, out_path);
        extension = ".xml";
    } 

    try {
        myFile->convert();
    }
    catch (const char* ex) {
        std::ofstream invalid_output;
        //this opening will remove content of output from invalid file
        invalid_output.open(out_path + myFile->get_filename() +
            extension); 
        invalid_output.close();
    }

    delete myFile;

    return compare_file(out_path + filename + extension,
        "tests/expected_results/" + filename + extension);
}

bool Application::compare_file(std::string path1, std::string path2) {
    std::ifstream file1(path1);
    std::ifstream file2(path2);
    std::string line1, line2;
    bool isLine1, isLine2;
    for (;;) {
        isLine1 = false;
        isLine2 = false;
        if (getline(file1, line1)) 
            isLine1 = true;
        if (getline(file2, line2))
            isLine2 = true;

        if (!isLine1 && !isLine2)
            break;
        else if ((!isLine1 && isLine2) || (isLine1 && !isLine2))
            return false;

        if (line1 != line2) 
            return false;
    }
    return true;
}
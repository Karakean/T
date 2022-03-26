#pragma once
#include <iostream>
#include "MyFile.h"
#include "MyXML.h"
#include "MyTXT.h"
class Application {
public:
	void run_app();
	void run_tests();
	bool test(std::string file, std::string extension);
	bool compare_file(std::string path1, std::string path2);
};
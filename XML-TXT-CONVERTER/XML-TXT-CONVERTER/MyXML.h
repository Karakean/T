#pragma once
#include "MyFile.h"
class MyXML :public MyFile {
public:
	MyXML(std::string filename);
	void convert() override;
};
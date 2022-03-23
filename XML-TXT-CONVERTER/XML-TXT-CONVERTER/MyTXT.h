#pragma once
#include "MyFile.h"
class MyTXT :public MyFile {
public:
	MyTXT(std::string filename);
	void convert() override;
};
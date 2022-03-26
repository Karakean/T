#pragma once
#include "MyFile.h"
class MyTXT :public MyFile {
public:
	MyTXT(std::string filename, std::string in_dir, std::string out_dir);
	void convert() override;
};
// en vez de #pragma once podemos usar los "define o include guards"
#ifndef OPENFILECLASS_HPP
#define OPENFILECLASS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class OpenFile {
	std::ifstream* infile;
private:
	std::string fileName;
	OpenFile(); // lo declaramos privado para que nadie lo pueda usar
public:
	OpenFile(std::string fileName);
	~OpenFile();

	void ReadLines();
};

#endif

#include "OpenFile.h"

OpenFile::OpenFile(std::string fileName)
{ 
	std::cout << "Open the file " << fileName << std::endl;
	this->fileName = fileName;						   	
	this->infile = new std::ifstream(this->fileName, std::ifstream::in);
}

OpenFile::OpenFile()  {	
	std::cerr << "No implementado" << std::endl;
}

void OpenFile::ReadLines() {

	std::string line;
	while (std::getline(*this->infile, line))
	{
		std::istringstream iss(line);
		int a, b;
		if (!(iss >> a >> b)) { break; } // error

										 // process pair (a,b)
	}

}

OpenFile::~OpenFile() {
	std::cout << "Destroying a file " << this->fileName << std::endl;
	this->infile->close();
}

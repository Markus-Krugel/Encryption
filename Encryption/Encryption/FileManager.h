#pragma once
#include <string>
#include <fstream>
#include <iostream>

class FileManager
{
public:
	void openFile(const char* filePath);
	std::string getFileContent();
private:
	std::string fileContent = "";
};


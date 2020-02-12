#include "FileManager.h"

void FileManager::openFile(const char* filePath)
{
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		fileContent.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&fileContent[0], fileContent.size());
		in.close();
	}
	else
		std::cout << "Could not open file !" << std::endl;
}

std::string FileManager::getFileContent()
{
	return fileContent;
}

#include "EncryptCommand.h"
#include "ULanguage.cpp"
#include <iostream>
#include "BiLanguage.cpp"

int main()
{
	 BiLanguage encrpyt;

	std::cout << encrpyt.Encode(&std::string("Dies ist ein Beispielssatz.")) << std::endl;
	std::cout << encrpyt.EncodeFromeFile("encrypted.txt") << std::endl;
}
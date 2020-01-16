#include "EncryptCommand.h"
#include "USprache.cpp"
#include <iostream>

int main()
{
	USprache encrpyt;

	std::cout << encrpyt.Encode(&std::string("Dies ist ein Beispielssatz.")) << std::endl;
	std::cout << encrpyt.EncodeFromeFile("encrypted.txt") << std::endl;
}
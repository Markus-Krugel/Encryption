#include "EncryptCommand.h"
#include "ULanguage.cpp"
#include <iostream>
#include "BiLanguage.cpp"
#include "RorLanguage.cpp"
#include "Atbasch.cpp"
#include "PolybiosCode.cpp"
#include "Ceaser.cpp"
#include "BaconCode.cpp"
#include "VigenereCipher.cpp"

int main()
{
	VigenereCipher encrpyt;

	std::cout << encrpyt.Encode(&std::string("a simple example"), &std::string("battista")) << std::endl;
	//std::cout << encrpyt.EncodeFromeFile("encrypted.txt") << std::endl;
}
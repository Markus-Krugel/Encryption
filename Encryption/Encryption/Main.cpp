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
#include "Transposition.cpp"

int main()
{
	Transposition encrpyt;

	//std::cout << encrpyt.Encode(&std::string("Dies ist ein Beispielssatz.")) << std::endl;
	//std::cout << encrpyt.EncodeFromeFile("encrypted.txt") << std::endl;

	std::cout << encrpyt.Decode(&std::string("Diiilzisnss.et pss Bia eeet")) << std::endl;
	//std::cout << encrpyt.DecodeFromeFile("decrypted.txt") << std::endl;
}


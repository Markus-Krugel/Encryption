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
	Caeser encrpyt;

	//std::cout << encrpyt.Encode(&std::string("Dies ist ein Beispielssatz.")) << std::endl;
	//std::cout << encrpyt.EncodeFromeFile("encrypted.txt") << std::endl;

	std::cout << encrpyt.Decode(&std::string("Glhv lvw hlq Ehlvslhovvdwc.")) << std::endl;
	std::cout << encrpyt.DecodeFromeFile("decrypted.txt") << std::endl;
}
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
	VigenereCipher encrpyt;

	//std::cout << encrpyt.Encode(&std::string("Dies ist ein Beispielssatz."), &std::string("Hello")) << std::endl;
	//std::cout << encrpyt.EncodeFromeFile("encrypted.txt", &std::string("Hello")) << std::endl;

	std::cout << encrpyt.Decode(&std::string("Kmpd wzx ptb Iitddpiwdghxk."), &std::string("Hello")) << std::endl;
	std::cout << encrpyt.DecodeFromeFile("decrypted.txt", &std::string("Hello")) << std::endl;

}


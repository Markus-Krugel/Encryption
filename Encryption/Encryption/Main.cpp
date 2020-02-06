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
#include "Window.h"

bool isRunning = true;
Window* m_Window;


int main()
{
	VigenereCipher encrpyt;

	//std::cout << encrpyt.Encode(&std::string("Dies ist ein Beispielssatz."), &std::string("Hello")) << std::endl;
	//std::cout << encrpyt.EncodeFromeFile("encrypted.txt", &std::string("Hello")) << std::endl;

	//std::cout << encrpyt.Decode(&std::string("Kmpd wzx ptb Iitddpiwdghxk."), &std::string("Hello")) << std::endl;
	//std::cout << encrpyt.DecodeFromeFile("decrypted.txt", &std::string("Hello")) << std::endl;

	m_Window = new Window(WindowProps());

	while (isRunning)
	{
		m_Window->OnUpdate();
	}

	delete m_Window;
}


#pragma once
#include <iostream>
#include "EncryptCommand.h"
#include "ULanguage.cpp"
#include "BiLanguage.cpp"
#include "RorLanguage.cpp"
#include "Atbasch.cpp"
#include "PolybiosCode.cpp"
#include "Ceaser.cpp"
#include "BaconCode.cpp"
#include "VigenereCipher.cpp"
#include "Transposition.cpp"

#include "Window.h"
#include "EventDispatcher.h";

class Application
{
public:
	void Run();

private:
	bool isRunning = true;
	int currentAlgorithm;
	Window* m_Window;
	EncryptCommand algorithm;
	std::shared_ptr<EventDispatcher> dispatcher = std::make_shared<EventDispatcher>();

	void handleEvent(int eventID);

	void onEncryptEvent();

	void onDecryptEvent();

	void onAlgorithmChangedEvent(char& newAlgorithm);
};
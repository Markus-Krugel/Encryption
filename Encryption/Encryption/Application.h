#pragma once
#include <iostream>
#include "EncryptCommand.h"
#include "ULanguage.h"
#include "BiLanguage.h"
#include "RorLanguage.h"
#include "Atbasch.h"
#include "PolybiosCode.h"
#include "Ceaser.h"
#include "BaconCode.h"
#include "VigenereCipher.h"
#include "Transposition.h"

#include "Window.h"
#include "EventDispatcher.h";
#include "FileManager.h"


class Application
{
public:
	void Run();

private:
	bool isRunning = true;
	int currentAlgorithm = -1;
	Window* m_Window;
	EncryptCommand* algorithm;
	std::shared_ptr<EventDispatcher> dispatcher = std::make_shared<EventDispatcher>();
	FileManager fileManager;

	void handleEvent(EventID id);

	void onEncryptEvent();

	void onDecryptEvent();

	void onAlgorithmChangedEvent(int& newAlgorithm);
};
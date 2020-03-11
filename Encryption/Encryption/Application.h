#pragma once
#include <iostream>
#include "Commands/EncryptCommand.h"
#include "Commands/ULanguage.h"
#include "Commands/BiLanguage.h"
#include "Commands/RorLanguage.h"
#include "Commands/Atbasch.h"
#include "Commands/PolybiosCode.h"
#include "Commands/Ceaser.h"
#include "Commands/BaconCode.h"
#include "Commands/VigenereCipher.h"
#include "Commands/Transposition.h"

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
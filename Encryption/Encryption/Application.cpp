#include "Application.h"

// "Ror Language", "U Language","Bacon Code",  "Polybios Code", "Ceaser Cipher", "Transposition", "Vigenere Cipher" 

void Application::onEncryptEvent()
{
	int newAlgorithm = m_Window->GetCurrentComboIndex();

	if (newAlgorithm == currentAlgorithm)
	{
		std::string currentInput = m_Window->GetInputText();
		//m_Window->setOutputText(algorithm.Encode(currentInput));
	}
	else
	{
		switch (newAlgorithm)
		{
		case 0:
			algorithm = RorLanguage();
			break;
		case 1:
			algorithm = ULanguage();
			break;
		case 2:
			algorithm = BaconCode();
			break;
		case 3:
			algorithm = PolybiosCode();
			break;
		case 4:
			algorithm = Caeser();
			break;
		case 5:
			algorithm = Transposition();
			break;
		case 6:
			algorithm = VigenereCipher();
			break;
		}

		currentAlgorithm = newAlgorithm;

		std::string currentInput = m_Window->GetInputText();
		if (currentAlgorithm < 4)
			//m_Window->setOutputText(algorithm.Encode(currentInput));
			std::cout << "Algorithm changed" << std::endl;
		else
		{
			// get additional window data
			// use encode with additional data
		}
	}
}

void Application::onDecryptEvent()
{
	//if (typeid(algorithm).name == "VigenereCipher")
	//{
	//
	//}
	//else if (typeid(algorithm).name == "Ceaser" || typeid(algorithm).name == "Transposition")
	//{
	//
	//}
	//else
	//{
	//	std::string text = m_Window->GetInputText();
	//	m_Window->setOutputText(algorithm.Decode(text));
	//}
}

void Application::onAlgorithmChangedEvent(char& newAlgorithm)
{
	switch (newAlgorithm)
	{
	case 0:
		algorithm = BaconCode();
		break;
	case 1:
		algorithm = Caeser();
		break;
	case 2:
		algorithm = PolybiosCode();
		break;
	case 3:
		algorithm = RorLanguage();
		break;
	case 4:
		algorithm = Transposition();
		break;
	case 5:
		algorithm = ULanguage();
		break;
	case 6:
		algorithm = VigenereCipher();
		break;
	}
}

void Application::Run()
{
	m_Window = new Window(WindowProps(), dispatcher);
	
	EventData data;
	while (isRunning)
	{
		m_Window->OnUpdate();

		data = dispatcher->hasEventStarted();
		if (data.hasEventStarted)
		{
			handleEvent(data.EventID);
		}
	}

	delete m_Window;
}


void Application::handleEvent(int eventID)
{

	std::cout << eventID << std::endl;
	
	switch (eventID)
	{
	case 1:
		onEncryptEvent();
		break;
	}

	dispatcher->handledEvent(eventID);
}

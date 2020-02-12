#include "Application.h"

void Application::onEncryptEvent()
{
	int newAlgorithm = m_Window->GetCurrentComboIndex();

	if (newAlgorithm == currentAlgorithm)
	{
		std::string currentInput = m_Window->GetInputText();
		std::string encoded = algorithm->Encode(currentInput);
		m_Window->SetOutputText(encoded);
	}
	else
	{
		onAlgorithmChangedEvent(newAlgorithm);

		currentAlgorithm = newAlgorithm;

		std::string currentInput = m_Window->GetInputText();
		if (currentAlgorithm < 4)
		{
			std::string encoded = algorithm->Encode(currentInput);
			m_Window->SetOutputText(encoded);
			std::cout << "Algorithm changed" << std::endl;
		}
		//else
		//{
		//	// get additional window data
		//	// use encode with additional data
		//}
	}
}

void Application::onDecryptEvent()
{
	int newAlgorithm = m_Window->GetCurrentComboIndex();

	if (newAlgorithm == currentAlgorithm)
	{
		std::string currentInput = m_Window->GetInputText();
		std::string decoded = algorithm->Decode(currentInput);
		m_Window->SetOutputText(decoded);
	}
	else
	{
		onAlgorithmChangedEvent(newAlgorithm);

		currentAlgorithm = newAlgorithm;

		std::string currentInput = m_Window->GetInputText();
		if (currentAlgorithm < 4)
		{
			std::string decoded = algorithm->Decode(currentInput);
			m_Window->SetOutputText(decoded);
			std::cout << "Algorithm changed" << std::endl;
		}
		//else
		//{
		//	// get additional window data
		//	// use encode with additional data
		//}
	}
}

void Application::onAlgorithmChangedEvent(int& newAlgorithm)
{
	switch (newAlgorithm)
	{
	case 0:
		algorithm = new Atbasch();
		break;
	case 1:
		algorithm = new BiLanguage();
		break;
	case 2:
		algorithm = new RorLanguage();
		break;
	case 3:
		algorithm = new ULanguage();
		break;
	case 4:
		algorithm = new BaconCode();
		break;
	case 5:
		algorithm = new PolybiosCode();
		break;
	case 6:
		algorithm = new Ceaser();
		break;
	case 7:
		algorithm = new Transposition();
		break;
	case 8:
		algorithm = new VigenereCipher();
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
	case 0:
		isRunning = false;
		break;
	case 1:
		onEncryptEvent();
		break;
	case 2:
		onDecryptEvent();
		break;
	case 3:
		m_Window->SwitchText();
		break;
	}

	dispatcher->handledEvent(eventID);
}

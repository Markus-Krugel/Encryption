#include "Application.h"

void Application::onEncryptEvent()
{
	int newAlgorithm = m_Window->GetCurrentComboIndex();

	// Return if no algorithm chosen
	if (newAlgorithm == -1)
	{
		m_Window->SetOutputText("Select an algorithm !");
		return;
	}

	std::string currentInput = m_Window->GetInputText();

	// for not changing simple algorithms with one input
	if (newAlgorithm == currentAlgorithm && currentAlgorithm < 6)
	{
		std::string encoded = algorithm->Encode(currentInput);
		m_Window->SetOutputText(encoded);
	}
	// for changing to another algorithm or using complex algorithm
	else
	{
		onAlgorithmChangedEvent(newAlgorithm);

		currentAlgorithm = newAlgorithm;

		if (currentAlgorithm < 6)
		{
			std::string encoded = algorithm->Encode(currentInput);
			m_Window->SetOutputText(encoded);
			std::cout << "Algorithm changed" << std::endl;
		}
		else
		{
			if (currentAlgorithm != newAlgorithm)
			{
				currentAlgorithm = newAlgorithm;
				onAlgorithmChangedEvent(currentAlgorithm);
			}

			int additionalValue = m_Window->GetAdditionalValue();
			std::string encoded;

			if (currentAlgorithm == 6)
			{
				Ceaser ceaser = dynamic_cast<Ceaser&>(*algorithm);
				encoded = ceaser.Encode(currentInput, additionalValue);
			}
			else if (currentAlgorithm == 7)
			{
				Transposition trans = dynamic_cast<Transposition&>(*algorithm);
				encoded = trans.Encode(currentInput, additionalValue);
			}
			else
			{
				std::string codeword = m_Window->GetCodeWord();
				VigenereCipher vig = dynamic_cast<VigenereCipher&>(*algorithm);
				encoded = vig.Encode(currentInput, codeword);
			}
			m_Window->SetOutputText(encoded);
		}
	}
}

void Application::onDecryptEvent()
{
	int newAlgorithm = m_Window->GetCurrentComboIndex();

	// Return if no algorithm chosen
	if (newAlgorithm == -1)
	{
		m_Window->SetOutputText("Select an algorithm !");
		return;
	}

	std::string currentInput = m_Window->GetInputText();

	// for not changing simple algorithms with one input
	if (newAlgorithm == currentAlgorithm && currentAlgorithm < 6)
	{
		std::string decoded = algorithm->Decode(currentInput);
		m_Window->SetOutputText(decoded);
	}
	// for changing to another algorithm or using complex algorithm
	else
	{
		onAlgorithmChangedEvent(newAlgorithm);

		currentAlgorithm = newAlgorithm;

		if (currentAlgorithm < 6)
		{
			std::string decoded = algorithm->Decode(currentInput);
			m_Window->SetOutputText(decoded);
			std::cout << "Algorithm changed" << std::endl;
		}
		else
		{
			if (currentAlgorithm != newAlgorithm)
			{
				currentAlgorithm = newAlgorithm;
				onAlgorithmChangedEvent(currentAlgorithm);
			}

			int additionalValue = m_Window->GetAdditionalValue();

			std::string decoded;

			if (currentAlgorithm == 6)
			{
				Ceaser ceaser = dynamic_cast<Ceaser&>(*algorithm);
				decoded = ceaser.Decode(currentInput, additionalValue);
			}
			else if (currentAlgorithm == 7)
			{
				Transposition trans = dynamic_cast<Transposition&>(*algorithm);
				decoded = trans.Decode(currentInput, additionalValue);
			}
			else
			{
				std::string codeword = m_Window->GetCodeWord();
				VigenereCipher vig = dynamic_cast<VigenereCipher&>(*algorithm);
				decoded = vig.Decode(currentInput, codeword);
			}
			m_Window->SetOutputText(decoded);
		}
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
			handleEvent(data.id);
		}
	}

	delete m_Window;


	//std::cout << dbg_metrics.CurrentUsage() << std::endl;

}


void Application::handleEvent(EventID id)
{

	switch (id)
	{
	case WindowCloseEvent:
		isRunning = false;
		break;
	case EncryptionEvent:
		onEncryptEvent();
		break;
	case DecryptionEvent:
		onDecryptEvent();
		break;
	case SwitchTextEvent:
		m_Window->SwitchText();
		break;
	}

	dispatcher->handledEvent(id);
}

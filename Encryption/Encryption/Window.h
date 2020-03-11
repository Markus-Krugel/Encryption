#pragma once

#include <glad.h>
#include <iostream>
#include "Windows.h"
#include "glad.h"
#include "glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <functional>
#include "WordHelper.h"
#include "EventDispatcher.h"
#include "vendor/imgui/misc/cpp/imgui_stdlib.h"


struct WindowProps
{
	std::string Title;
	unsigned int Width;
	unsigned int Height;

	WindowProps(const std::string& title = "Encryption Tool",
		unsigned int width = 1280,
		unsigned int height = 720)
		: Title(title), Width(width), Height(height)
	{
	}
};

struct InputData
{
	const char* m_label;
	TextData text;
	ImVec2 size;

	InputData(const char* label,std::string newContent, ImVec2 size = {100, 100}) : m_label(label)
	{
		text.SetContent(newContent);
	}
};

class Window
{
public:

	Window(const WindowProps& props, std::shared_ptr<EventDispatcher> dispatcher);
	~Window();

	void OnUpdate();

	inline unsigned int GetWidth() const { return m_Data.Width; }
	inline unsigned int GetHeight() const { return m_Data.Height; }

	bool wrappedEnabled = true;

	// Window attributes

	void SetVSync(bool enabled);
	bool IsVSync() const ;

	inline void* GetNativeWindow() const { return m_Window; }

	//Gets the ID of the Encryption algorithm
	int GetCurrentComboIndex();
	// Gets the user Input for the Encryption
	std::string GetInputText();

	// Sets the result text
	void SetOutputText(std::string text);

	// Updates the data of the window, when the window size changes
	void UpdateData(int width, int heigth);

	// Switches the input text with the output text
	void SwitchText();

	// Get the codeword needed for Vigenere
	std::string GetCodeWord();

	// Get thed additional number needed for ceaser and transposition
	int GetAdditionalValue();

	// Gets the output text
	TextData* GetOutputText();

	int GetInputDataWidth();

private:

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
	};

	GLFWwindow* m_Window;
	WindowData m_Data;
	std::shared_ptr<EventDispatcher> dispatcher;

	bool s_GLFWInitialized;

	static const int comboItemSize = 9;
	const char* comboItems[comboItemSize] = { "Atbasch", "BiLanguage", "Ror Language", "U Language","Bacon Code",  "Polybios Code", "Ceaser Cipher", "Transposition", "Vigenere Cipher" };
	const char* currentComboItem;
	int currentComboIndex = -1;

	InputData input = InputData("Your text", "This is an example Text.");
	InputData output = InputData("Output", "");

	int additionalValue = 3;
	static const int maxCodeWordSize = 50;
	char codeWord[maxCodeWordSize];

	// this programm does not need different fonts and therefore dont need dynamic calculation
	static const int charPixelSize = (440 / 62);

	void UpdateWidgetSizes();
	void Init(const WindowProps& props);

	void DrawEncryptionWindow();
	void DrawHelpWindow();
};

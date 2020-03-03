#pragma once

#include <glad.h>
#include <iostream>
#include "Windows.h"
#include "glad.h"
#include "glfw3.h"
#include "imgui.h"
#include "vendor/imgui/examples/imgui_impl_glfw.h"
#include "vendor/imgui/examples/imgui_impl_opengl3.h"
#include <string>
#include <functional>
#include "WordHelper.h"
#include "EventDispatcher.h"


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
	};
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
	bool wrapped = false;
	bool needToWrapOutput = false;

	// Window attributes
	void SetVSync(bool enabled);
	bool IsVSync() const;

	inline void* GetNativeWindow() const { return m_Window; }
	int GetCurrentComboIndex();
	std::string GetInputText();

	void SetOutputText(std::string text);
	void UpdateData(int width, int heigth);
	void SwitchText();
	std::string GetCodeWord();
	int GetAdditionalValue();
	void ActivateOutputWrap();

	std::string GetOutputText();
	void UpdateWidgetSizes();


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

	void Init(const WindowProps& props);
	void Shutdown();

	void DrawEncryptionWindow();
	void DrawHelpWindow();
	void FormatOutput(std::string ToFormat = "");
};

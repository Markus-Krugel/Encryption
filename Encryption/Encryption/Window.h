#pragma once

#include "Windows.h"
#include "vendor/glad/include/glad/glad.h"
#include "vendor/glfw/include/glfw3.h"
#include <string>
#include <functional>

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

class Window
{
public:
	Window(const WindowProps& props);
	~Window();

	void OnUpdate();

	inline unsigned int GetWidth() const { return m_Data.Width; }
	inline unsigned int GetHeight() const { return m_Data.Height; }

	// Window attributes
	void SetVSync(bool enabled);
	bool IsVSync() const;

	inline void* GetNativeWindow() const { return m_Window; }
private:
	void Init(const WindowProps& props);
	void Shutdown();
private:
	GLFWwindow* m_Window;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
	};

	WindowData m_Data;
};

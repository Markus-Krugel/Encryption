#include "Window.h"

#include <glad.h>
#include <iostream>


static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description)
{
	std::cout << "GLFW Error( " << error << "," << description << ")";
}

Window::Window(const WindowProps& props)
{
	Init(props);
}

Window::~Window()
{
	Shutdown();
}

void Window::Init(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	if (!s_GLFWInitialized)
	{
		// TODO: glfwTerminate on system shutdown
		int success = glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);
		s_GLFWInitialized = true;
	}

	m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	// Set GLFW callbacks
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			break;
		}
		case GLFW_RELEASE:
		{
			break;
		}
		case GLFW_REPEAT:
		{
			break;
		}
		}
	});

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			break;
		}
		case GLFW_RELEASE:
		{
			break;
		}
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	});
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Window);
}

void Window::OnUpdate()
{
	glClearColor(86, 134, 196, 1);
	glClear(GL_COLOR_BUFFER_BIT);


	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_Data.VSync = enabled;
}

bool Window::IsVSync() const
{
	return m_Data.VSync;
}

#include "Window.h"

static bool s_GLFWInitialized = false;

const char* comboItems[] = {"Atbasch", "BiLanguage", "Ror Language", "U Language","Bacon Code",  "Polybios Code", "Ceaser Cipher", "Transposition", "Vigenere Cipher" };
static const char* currentComboItem = "Encryption Algorithm";
int currentComboIndex;
static const int comboItemSize = 7;

static const int maxTextSize = 1000;

static const char* textInputLabel = "Your Text";
char textInput[maxTextSize]  = "This is an example text.";

static const char* textOutputLabel = "Output";
char textOutput[maxTextSize] = "";


static void GLFWErrorCallback(int error, const char* description)
{
	std::cout << "GLFW Error( " << error << "," << description << ")";
}

Window::Window(const WindowProps& props, std::shared_ptr<EventDispatcher> dispatcherInput)
{
	Init(props);
	dispatcher = dispatcherInput;
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

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

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
	glfwSetWindowUserPointer(m_Window, this);
	SetVSync(true);

	// Set GLFW callbacks
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	{
		Window& windowObj = *(Window*)glfwGetWindowUserPointer(window);
		windowObj.UpdateData(width, height);
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		Window& windowObj = *(Window*)glfwGetWindowUserPointer(window);
		windowObj.dispatcher->startEvent({ true,0 });
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
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

	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
	{
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
		
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		
	});

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);

	auto temp = (const char*)glGetString(GL_VERSION);
	ImGui_ImplOpenGL3_Init(glsl_version);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
}

void Window::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Window::OnUpdate()
{ 
	glfwPollEvents();
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT);

	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowSize({(float) m_Data.Width,(float)m_Data.Width });

	// render your GUI
	DrawEncryptionWindow();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	int display_w, display_h;
	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
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

int Window::GetCurrentComboIndex()
{
	return currentComboIndex;
}

std::string Window::GetInputText()
{
	return textInput;
}

void Window::SetOutputText(std::string text)
{
	WordHelper::transformStringToChar(text, textOutput);
}

void Window::UpdateData(int width, int heigth)
{
	m_Data.Width = width;
	m_Data.Height = width;
}

void Window::DrawEncryptionWindow()
{
	ImGui::Begin("Encryption", (bool*)0, ImGuiWindowFlags_NoDecoration);

	if (ImGui::BeginCombo(currentComboItem, currentComboItem, ImGuiComboFlags_NoPreview))
	{
		for (int n = 0; n < comboItemSize; n++)
		{
			bool is_selected = (currentComboItem == comboItems[n]);
			if (ImGui::Selectable(comboItems[n], is_selected))
			{
				currentComboItem = comboItems[n];
				currentComboIndex = n;
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	//if certain algorithm then add textinput(or intInput if possible) in same line

	// would need an int to store last position of bool array
	// another button, which when clicked adds a true to a bool[] and remove for opposite
	// add button disable if last possible position, disable remove at first position
	// checks bool[] and then add accordingly the amount of additional combo boxes

	ImGui::InputTextMultiline(textInputLabel, textInput, maxTextSize, { (float)(m_Data.Width / 2) - 200, (float)(m_Data.Width / 4) });
	ImGui::SameLine(0, 80);
	if (ImGui::Button("Encrypt!"))
		dispatcher->startEvent({ true,1 });
	ImGui::SameLine(0, 80);
	ImGui::InputTextMultiline(textOutputLabel, textOutput, maxTextSize, { (float)(m_Data.Width / 2) - 200, (float)(m_Data.Width / 4) });


	ImGui::End();
}

void Window::DrawHelpWindow()
{
}

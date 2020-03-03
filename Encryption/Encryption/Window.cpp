#include "Window.h"
#pragma warning(disable : 4996)

static bool s_GLFWInitialized = false;

const char* comboItems[] = {"Atbasch", "BiLanguage", "Ror Language", "U Language","Bacon Code",  "Polybios Code", "Ceaser Cipher", "Transposition", "Vigenere Cipher" };
static const char* currentComboItem = "Encryption Algorithm";
int currentComboIndex;
static const int comboItemSize = 9;

InputData input = InputData("Your text", "This is an example Text. \nHello second line.");
InputData output = InputData("Output", "");

int additionalValue = 3;
static const int maxCodeWordSize = 50;
char codeWord[maxCodeWordSize];

static const int charPixelSize = (440 / 62);

#define EmptySpace(x , y) ImGui::Dummy({x,y});

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

	UpdateWidgetSizes();

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

		std::string outputText = windowObj.GetOutputText();

		WordHelper::EraseNewLines(outputText);
		if(windowObj.wrappedEnabled)
			windowObj.FormatOutput(outputText);
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
	ImGui::SetNextWindowPos({ 0,0 });

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
	return input.text.GetContent();
}

void Window::SetOutputText(std::string text)
{
	output.text.SetContent(text);
	if(wrappedEnabled)
		ActivateOutputWrap();
}

void Window::UpdateData(int width, int heigth)
{
	m_Data.Width = width;
	m_Data.Height = heigth;

	UpdateWidgetSizes();
}

void Window::SwitchText()
{
	input.text.SetContent(output.text.GetContent());
	output.text.SetContent("");
}

std::string Window::GetCodeWord()
{
	return codeWord;
}

int Window::GetAdditionalValue()
{
	return additionalValue;
}

void Window::ActivateOutputWrap()
{
	needToWrapOutput = true;
	wrapped = true;
}

std::string Window::GetOutputText()
{
	return output.text.GetContent();
}

void Window::UpdateWidgetSizes()
{
	input.size = { (float)(m_Data.Width / 2) - 200, (float) m_Data.Height / 2 };
	output.size = { (float)(m_Data.Width / 2) - 200, (float) m_Data.Height / 2 };
}

void Window::FormatOutput(std::string ToFormat)
{
	if (ToFormat != "")
		output.text.SetContent(ToFormat);

	WordHelper::SolveWordWrap(output.text, (output.size.x / charPixelSize) + 1);
	output.text.SetContent(output.text.GetContent());
}

void Window::DrawEncryptionWindow()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(30,0));
	ImGui::Begin("Encryption", (bool*)0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

	EmptySpace(0, 10);

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

	if (currentComboIndex > 5 && currentComboIndex < 8)
	{
		// change value to 2 if transposition selected as 1 would do nothíng
		if (currentComboIndex == 7 && additionalValue == 1)
			additionalValue = 2;
		// if you switch from Ceaser to Transposition and value is over 10 then set it back to 10
		if (currentComboIndex == 7 && additionalValue > 10)
			additionalValue = 10;

		ImGui::SameLine(0, 80);
		// decided to do index -5 so that if it is transposition the minimum would be 2 and for ceaser 1
		// For Transposition max is 10 for Ceaser 25
		ImGui::SliderInt("Value", &additionalValue, currentComboIndex - 5, currentComboIndex == 6 ? 25 : 10);
	}
	else if (currentComboIndex == 8)
	{
		ImGui::SameLine(0, 80);

		ImGui::PushItemWidth(400);
		// +1 for null terminator
		ImGui::InputText("Codeword", codeWord, maxCodeWordSize + 1, ImGuiInputTextFlags_OnlyLetters);
		ImGui::PopItemWidth();
	}

	EmptySpace(0, 20);

	// would need an int to store last position of bool array
	// another button, which when clicked adds a true to a bool[] and remove for opposite
	// add button disable if last possible position, disable remove at first position
	// checks bool[] and then add accordingly the amount of additional combo boxes

	// omly wrap the output if it has changed
	if (needToWrapOutput && wrappedEnabled)
	{
		FormatOutput();
		needToWrapOutput = false;
	}

	ImGui::InputTextMultiline(input.m_label, (char*)input.text.GetContent().c_str(), input.text.maxTextSize, input.size);
	ImGui::SameLine(0, 40); 
	ImGui::BeginGroup();

	EmptySpace(0, (float)(m_Data.Width / 8) - 50);
	ImGui::Checkbox("Word Wrapping for Output", &wrappedEnabled);
	EmptySpace(0, 5);
	if (ImGui::Button("Encrypt!"))
		dispatcher->startEvent({ true,1 });
	EmptySpace(0, 5);
	if (ImGui::Button("Decrypt!"))
		dispatcher->startEvent({ true,2 });
	EmptySpace(0, 5);
	if (ImGui::Button("<-------"))
		dispatcher->startEvent({ true,3 });

	ImGui::EndGroup();

	
	ImGui::SameLine(0, 80);
	ImGui::InputTextMultiline(output.m_label, (char*)output.text.GetContent().c_str(), output.text.maxTextSize, output.size, ImGuiInputTextFlags_ReadOnly);

	ImGui::End();
	ImGui::PopStyleVar();
}

void Window::DrawHelpWindow()
{
}

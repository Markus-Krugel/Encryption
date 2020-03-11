#include "Window.h"
#pragma warning(disable : 4996)

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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

// Inititalizes glfw and dear imgui window
void Window::Init(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	currentComboItem = "Encryption Algorithm";

	UpdateWidgetSizes();

	// glfw initialization

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

		// recalculate word wrapping when window sizes changes
		if (windowObj.wrappedEnabled)
		{
			TextData* outputText = windowObj.GetOutputText();

			WordHelper::EraseNewLinesAndSpaces(outputText->GetContent());
			outputText->UpdateContent();
			WordHelper::SolveWordWrap(*outputText, (windowObj.GetInputDataWidth() / charPixelSize) - 2);
		}
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		Window& windowObj = *(Window*)glfwGetWindowUserPointer(window);
		windowObj.dispatcher->startEvent({ true, WindowCloseEvent });
	});

	glfwSetWindowSizeLimits(m_Window, 800, 300, GLFW_DONT_CARE, GLFW_DONT_CARE);

	// imgui initialization

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);

	ImGui_ImplOpenGL3_Init(glsl_version);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
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
	ImGui::SetNextWindowSize({ (float)m_Data.Width,(float)m_Data.Width });
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
	if (text != output.text.GetContent())
		output.text.SetContent(text);

	if (wrappedEnabled)
	{
		// do not erase unneccassary spaces if you use tansposition as it alters the result
		WordHelper::EraseNewLinesAndSpaces(output.text.GetContent(), currentComboIndex == 7 ? false : true);
		output.text.UpdateContent();
		WordHelper::SolveWordWrap(output.text, (output.size.x / charPixelSize) - 2);
		output.text.SetContent(output.text.GetContent());
	}
	else
		output.text.SetContent(text);
}

void Window::UpdateData(int width, int heigth)
{
	m_Data.Width = width;
	m_Data.Height = heigth;

	UpdateWidgetSizes();
}

void Window::SwitchText()
{
	auto text = output.text.GetContent();

	// Return if output is empty
	if (text == "")
		return;

	input.text.SetContent(text);
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

TextData* Window::GetOutputText()
{
	return &output.text;
}

void Window::UpdateWidgetSizes()
{
	input.size = { (float)(m_Data.Width / 2) - 200, (float)m_Data.Height / 2 };
	output.size = { (float)(m_Data.Width / 2) - 200, (float)m_Data.Height / 2 };
}

int Window::GetInputDataWidth()
{
	return input.size.x;
}

void Window::DrawEncryptionWindow()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(30, 0));
	ImGui::Begin("Encryption", (bool*)0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

	EmptySpace(0, 10);

	// Selection for the algorithm
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

	// add an int slider when transposition or ceaser is selected
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
	// adss an inputtext for vigenere
	else if (currentComboIndex == 8)
	{
		ImGui::SameLine(0, 80);

		ImGui::PushItemWidth(400);
		// +1 for null terminator
		ImGui::InputText("Codeword", codeWord, maxCodeWordSize + 1, ImGuiInputTextFlags_OnlyLetters);
		ImGui::PopItemWidth();
	}

	EmptySpace(0, 20);

	ImGui::InputTextMultiline(input.m_label, &input.text.GetContent(), input.size);
	ImGui::SameLine(0, 40);
	ImGui::BeginGroup();

	EmptySpace(0, (float)m_Data.Height / 11);
	ImGui::Checkbox("Enable Word Wrapping for Output", &wrappedEnabled);

	EmptySpace(0, 5);
	if (ImGui::Button("Encrypt!"))
	{
		dispatcher->startEvent({ true, EncryptionEvent });
	}
	EmptySpace(0, 5);
	if (ImGui::Button("Decrypt!"))
	{
		dispatcher->startEvent({ true, DecryptionEvent });
	}
	EmptySpace(0, 5);
	if (ImGui::Button("<-------"))
		dispatcher->startEvent({ true, SwitchTextEvent });

	ImGui::EndGroup();


	ImGui::SameLine(0, 80);
	ImGui::InputTextMultiline(output.m_label, &output.text.GetContent(), output.size, ImGuiInputTextFlags_ReadOnly);

	ImGui::End();
	ImGui::PopStyleVar();
}

void Window::DrawHelpWindow()
{
}